/*
 * garbage collenction
 * Easy-ISLisp has concurrent mark&sweep garbage collection system.
 * in cuncurrent mode if remain cell < FREESIZE, invoke gc.
 * <memo concurrent>
 * cell.c freshcell provide cell. while executing GC thread concurrent_flag = 1.
 * while remark&sweep concurrent_stop_flag = 1;
 * freshcell provide cell and save the address to remark array.
 * current thread remark cell with remark array data. 
 * rc means real count. While executing concurrent GC, rc has real remain cell count.
 * if define GCTIME print GC time and stop time 
 * sweep 
 * now, sweep is not concurrent. because it is difficult for paralell function. 
 *   
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "eisl.h"
#include "compat/nana_stubs.h"
#include "mem.h"
#include "except.h"
#include "fmt.h"

#define DBG_PRINTF(msg,arg)     if(gbc_flag) printf(msg,arg)
#define DEBUG error(RESOURCE_ERR,"debug",NIL);


/* concurrent mark&sweep garbage collection */
DEF_PREDICATE(EMPTY, EMP)
int gbc(void)
{
    gbc_concurrent();
    return 0;
}


static inline void MARK_CELL(int addr)
{
    heap[addr].flag = USE;
}

static inline bool USED_CELL(int addr)
{
    return (heap[addr].flag == USE);
}

void mark_cell(int addr)
{
    int i, m, n, x;

    if (addr < 0 || addr >= CELLSIZE)
	return;

    if (USED_CELL(addr))
	return;

    MARK_CELL(addr);
    switch (GET_TAG(addr)) {
    case EMP:
    case INTN:
    case FLTN:
    case LONGN:
    case CHR:
    case STR:
    case STREAM:
    case BIGN:
	return;
    case VEC:
	n = vector_length(addr);
	for (i = 0; i < n; i++) {
	    x = GET_VEC_ELT(addr, i);
	    mark_cell(x);
	}
	return;

    case ARR:
	m = array_length(addr);
	n = 1;
	while (!nullp(m)) {
	    n = n * GET_INT(car(m));
	    m = cdr(m);
	}
	for (i = 0; i < n; i++) {
	    x = GET_VEC_ELT(addr, i);
	    mark_cell(x);
	}
	mark_cell(cdr(addr));	/* dimension */
	return;

    case SYM:
	mark_cell(car(addr));
	mark_cell(cdr(addr));
	mark_cell(GET_AUX(addr));
	mark_cell(GET_PROP(addr));
	return;
    case FUNC:
	mark_cell(car(addr));
	mark_cell(cdr(addr));
	mark_cell(GET_AUX(addr));
	mark_cell(GET_PROP(addr));
	return;
    case MACRO:
    case GENERIC:
    case METHOD:
    case CLASS:
    case INSTANCE:
    case LIS:
	mark_cell(car(addr));
	mark_cell(cdr(addr));
	mark_cell(GET_AUX(addr));
	return;
    case SUBR:
    case FSUBR:
	mark_cell(GET_AUX(addr));
	return;
    default:
	IP(false, "mark_cell tag switch default action");
    }
}


static inline void NOMARK_CELL(int addr)
{
    heap[addr].flag = FRE;
}


void *concurrent(void *arg)
{
    int addr, fc1, i, j;

    while (1) {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond_gc, &mutex);
	pthread_mutex_unlock(&mutex);
	if (concurrent_exit_flag)
	    goto exit;

	DBG_PRINTF("enter  concurrent M&S-GC free=%d\n", fc);
	concurrent_flag = 1;
	
	/* mark hash table */
	for (i = 0; i < HASHTBSIZE; i++)
	    mark_cell(cell_hash_table[i]);

	/* stop the world */
	concurrent_stop_flag = 1;

	/* mark nil and t */
	MARK_CELL(NIL);
	MARK_CELL(T);

	/* mark local environment */
	for (j = 0; j < PARASIZE; j++)
	    mark_cell(ep[j]);
	/* mark dynamic environment */
	for (j = 0; j < PARASIZE; j++)
	    mark_cell(dp[j]);
	/* mark stack */
	for (j = 0; j < PARASIZE; j++) {
	    for (i = 0; i < sp[j]; i++)
		mark_cell(stack[i][j]);
	}
	/* mark cell binded by argstack */
	for (j = 0; j < PARASIZE; j++) {
	    for (i = 0; i < ap[j]; i++)
		mark_cell(argstk[i][j]);
	}
	/* mark tagbody symbol */
	mark_cell(tagbody_tag);
	/* mark thunk for unwind-protect */
	for (i = 0; i < unwind_pt; i++)
	    mark_cell(unwind_buf[i]);
	/* mark error_handler */
	mark_cell(error_handler);
	/* mark stream */
	mark_cell(standard_input);
	mark_cell(standard_output);
	mark_cell(standard_error);
	mark_cell(input_stream);
	mark_cell(output_stream);
	mark_cell(error_stream);
	/* mark shelter */
	for (j = 0; j < PARASIZE; j++) {
	    for (i = 0; i < lp[j]; i++)
		mark_cell(shelter[i][j]);
	}
	/* mark dynamic environment */
	for (j = 0; j < PARASIZE; j++) {
	    for (i = 0; i <= dp[j]; i++)
		mark_cell(dynamic[i][j]);
	}
	/* mark generic_list */
	mark_cell(generic_list);

	/* remark hash table */
	for (i = 0; i < remark_pt; i++)
	    mark_cell(remark[i]);

	remark_pt = 0;
	
	concurrent_sweep_flag = 1;
	addr = 0;
	hp = NIL;
	fc = 0;
	while (addr < CELLSIZE) {
	    if (USED_CELL(addr))
		NOMARK_CELL(addr);
	    else {
		clr_cell(addr);
		SET_CDR(addr, hp);
		hp = addr;
		fc++;
	    }
	    addr++;
	}

	/* end of stop the world and into sweep mode*/
	concurrent_stop_flag = 0;
	concurrent_sweep_flag = 0;
	concurrent_flag = 0;
	DBG_PRINTF("exit   concurrent M&S-GC free=%d\n", fc);

    }
  exit:
    pthread_exit(NULL);
}

int gbc_concurrent(void)
{
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond_gc);
    pthread_mutex_unlock(&mutex);
    return 0;
}


void clr_cell(int addr)
{
    if (IS_VECTOR(addr) || IS_ARRAY(addr))
	FREE(heap[addr].val.car.dyna_vec);


    SET_TAG(addr, EMP);
    FREE(heap[addr].name);
    SET_CAR(addr, 0);
    SET_CDR(addr, 0);
    SET_AUX(addr, 0);
    SET_PROP(addr, 0);
    SET_OPT(addr, 0);
    SET_TR(addr, 0);
}

/* when free cells are less FREESIZE, invoke gbc() */
int check_gbc(void)
{
    int temp;

    if (exit_flag) {
	exit_flag = 0;
	RAISE(Restart_Repl);
    }

    if (!concurrent_flag && fc < FREESIZE)
	gbc();

    return 0;
}



int freecell(void)
{
    return (fc);
}
