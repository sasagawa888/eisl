/*
 * garbage collenction
 * Easy-ISLisp has mark&sweep garbage collection system.
 * if GC == 0 , concurrent mark&sweep
 * if GC == 1 , paralell mark and paralell sweep (4 threads)
 * if GC == 2 , sequential mark&sweep
 * in sequential or paralell mode if remain cell < FREESIZE, invoke gc.
 * in cuncurrent mode if remain cell < CONCSIZE, invoke gc.
 * <memo concurrent>
 * cell.c freshcell provide cell. while executing GC thread concurrent_flag = 1.
 * while remark&sweep concurrent_stop_flag = 1;
 * freshcell provide cell and save the address to remark array.
 * current thread remark cell with remark array data.
 * if CONCSIZE is small(900), occure error. Now CONCSIZE is 90000. 
 * rc means real count. While executing concurrent GC, rc has real remain cell count.
 * if define GCTIME print GC time and stop time 
 * concurrent sweep 
 * first step, sweep sequential 0~SEQUENT cells while stop_flag = 1
 * second step, sweep concurrent SEQUENT~CELLSOZE cells while stop_flag=0, sweep_flag=1.  
 */

/*  GC = 0 concurrent
 *  GC = 1 parallel
 *  GC = 2 sequential
*/
#define GC  0
#define SEQUENT 4000000
//#define GCTIME

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

struct data {
    int start;
    int end;
    int head;
    int tail;
};


/* mark&sweep garbage collection */
DEF_PREDICATE(EMPTY, EMP)
int gbc(void)
{


#if   GC == 0
    gbc_concurrent();
    return 0;

#elif GC == 1
    int addr;

    DBG_PRINTF("enter parallel M&S-GC free=%d\n", fc);
    gbc_mark();
    gbc_sweep_thread();
    fc = 0;
    for (addr = 0; addr < CELLSIZE; addr++)
	if (IS_EMPTY(addr))
	    fc++;
    DBG_PRINTF("exit  parallel M&S-GC free=%d\n", fc);
    return 0;
#elif GC == 2
    int addr;

    DBG_PRINTF("enter M&S-GC free=%d\n", fc);
    gbc_mark();
    gbc_sweep();
    fc = 0;
    for (addr = 0; addr < CELLSIZE; addr++)
	if (IS_EMPTY(addr))
	    fc++;
    DBG_PRINTF("exit  M&S-GC free=%d\n", fc);
    return 0;
#endif
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

void *mark(void *arg);
void *mark(void *arg)
{
    int i;
    struct data *pd = (struct data *) arg;

    for (i = pd->start; i < pd->end; i++) {
	mark_cell(cell_hash_table[i]);
    }
    return NULL;
}


#define NUM_THREAD 4
/* mark symbol hash-table with thread*/
void gbc_hash_mark(void)
{
    pthread_t t[NUM_THREAD];
    struct data d[NUM_THREAD];

    d[0].start = 0;
    d[0].end = 35;
    pthread_create(&t[0], NULL, mark, &d[0]);

    d[1].start = 35;
    d[1].end = 70;
    pthread_create(&t[1], NULL, mark, &d[1]);

    d[2].start = 70;
    d[2].end = 106;
    pthread_create(&t[2], NULL, mark, &d[2]);

    d[3].start = 106;
    d[3].end = 137;
    pthread_create(&t[3], NULL, mark, &d[3]);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);

    return;
}

void gbc_mark(void)
{
    int i;

    /* mark nil and t */
    MARK_CELL(NIL);
    MARK_CELL(T);

    /* mark cell chained from hash table */
#if GC == 1
    gbc_hash_mark();
#else
    for (i = 0; i < HASHTBSIZE; i++)
	mark_cell(cell_hash_table[i]);
#endif

    /* mark local environment */
    mark_cell(ep);
    /* mark dynamic environment */
    mark_cell(dp[0]);
    /* mark stack */
    for (i = 0; i < sp; i++)
	mark_cell(stack[i]);
    /* mark cell binded by argstack */
    for (i = 0; i < ap; i++)
	mark_cell(argstk[i]);

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
    for (i = 0; i < lp; i++)
	mark_cell(shelter[i]);

    /* mark dynamic environment */
    for (i = 1; i <= dp[0]; i++)
	mark_cell(dynamic[i][1]);


    /* mark generic_list */
    mark_cell(generic_list);

}

static inline void NOMARK_CELL(int addr)
{
    heap[addr].flag = FRE;
}

void *sweep(void *arg);
void *sweep(void *arg)
{
    int addr, free;
    bool init;
    struct data *pd = (struct data *) arg;

    addr = pd->start;
    free = NIL;
    init = true;

    while (addr < pd->end) {
	if (USED_CELL(addr))
	    NOMARK_CELL(addr);
	else {
	    if (init) {
		pd->tail = addr;
		init = false;
	    }
	    clr_cell(addr);
	    SET_CDR(addr, free);
	    free = addr;
	}
	addr++;
    }
    pd->head = free;
    return NULL;
}

void gbc_sweep_thread(void)
{
    pthread_t t[NUM_THREAD];
    struct data d[NUM_THREAD];

    d[0].start = 0;
    d[0].end = 5000000;
    pthread_create(&t[0], NULL, sweep, &d[0]);

    d[1].start = 5000000;
    d[1].end = 10000000;
    pthread_create(&t[1], NULL, sweep, &d[1]);

    d[2].start = 10000000;
    d[2].end = 15000000;
    pthread_create(&t[2], NULL, sweep, &d[2]);

    d[3].start = 15000000;
    d[3].end = CELLSIZE;
    pthread_create(&t[3], NULL, sweep, &d[3]);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);

    SET_CDR(d[3].tail, d[2].head);
    SET_CDR(d[2].tail, d[1].head);
    SET_CDR(d[1].tail, d[0].head);
    SET_CDR(d[0].tail, NIL);
    hp = d[3].head;
    return;
}



void *concurrent(void *arg);
void *concurrent(void *arg)
{
    int addr, fc1, i, free;
    struct data *pd = (struct data *) arg;
#ifdef GCTIME
    double stop, go, st, en;
#endif

    DBG_PRINTF("enter concurrent M&S-GC free=%d\n", rc);
    pthread_mutex_lock(&mutex);
    concurrent_flag = 1;
    pthread_mutex_unlock(&mutex);
#ifdef GCTIME
    st = getETime();
#endif

    /* mark hash table */
    for (i = 0; i < HASHTBSIZE; i++)
	mark_cell(cell_hash_table[i]);

    /* stop the world */
    pthread_mutex_lock(&mutex);
    concurrent_stop_flag = 1;
    pthread_mutex_unlock(&mutex);
#ifdef GCTIME
    stop = getETime();
#endif

    /* mark nil and t */
    MARK_CELL(NIL);
    MARK_CELL(T);

    /* mark local environment */
    mark_cell(ep);
    /* mark dynamic environment */
    mark_cell(dp[0]);
    /* mark stack */
    for (i = 0; i < sp; i++)
	mark_cell(stack[i]);
    /* mark cell binded by argstack */
    for (i = 0; i < ap; i++)
	mark_cell(argstk[i]);
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
    for (i = 0; i < lp; i++)
	mark_cell(shelter[i]);
    /* mark dynamic environment */
    for (i = 1; i <= dp[0]; i++)
	mark_cell(dynamic[i][1]);
    /* mark generic_list */
    mark_cell(generic_list);

    /* remark hash table */
    for (i = 0; i < remark_pt; i++)
	mark_cell(remark[i]);

    remark_pt = 0;

    addr = 0;
    hp = NIL;
    while (addr < SEQUENT) {
	if (USED_CELL(addr))
	    NOMARK_CELL(addr);
	else {
	    clr_cell(addr);
	    SET_CDR(addr, hp);
	    hp = addr;
	    rc++;
	}
	addr++;
    }
#ifdef GCTIME
    go = getETime();
#endif
    /* end of stop the world */
    pthread_mutex_lock(&mutex);
    concurrent_stop_flag = 0;
    pthread_mutex_unlock(&mutex);

    /* concurrent sweep */
    pthread_mutex_lock(&mutex);
    concurrent_sweep_flag = 1;
    pthread_mutex_unlock(&mutex);
    addr = SEQUENT;
    free = NIL;
    while (addr < CELLSIZE) {
	if (USED_CELL(addr))
	    NOMARK_CELL(addr);
	else {
	    clr_cell(addr);
	    SET_CDR(addr, free);
	    free = addr;
	}
	addr++;
    }
    fc1 = 0;
    for (addr = SEQUENT; addr < CELLSIZE; addr++)
	if (IS_EMPTY(addr))
	    fc1++;
    fc = fc1;
    rc = fc1;

    pthread_mutex_lock(&mutex);
    hp = free;
    concurrent_sweep_flag = 0;
    pthread_mutex_unlock(&mutex);


#ifdef GCTIME
    en = getETime();
    Fmt_print("GC (within stop) %.6f (%.6f)(second)\n", en - st,
	      go - stop);
#endif

    pthread_mutex_lock(&mutex);
    concurrent_flag = 0;
    pthread_mutex_unlock(&mutex);
    DBG_PRINTF("exit  concurrent M&S-GC free=%d\n", fc);
    return NULL;
}

int gbc_concurrent(void)
{
    struct data d[1];

    /* to avoid gbc set fc dummy. set rc real-count */
    rc = fc;
    fc = CELLSIZE;
    pthread_create(&concurrent_thread, NULL, concurrent, &d[0]);

    return 0;
}

void gbc_sweep(void)
{
    int addr, free;

    addr = 0;
    free = NIL;
    while (addr < CELLSIZE) {
	if (USED_CELL(addr))
	    NOMARK_CELL(addr);
	else {
	    clr_cell(addr);
	    SET_CDR(addr, free);
	    free = addr;
	}
	addr++;
    }
    hp = free;
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
    if (exit_flag) {
	exit_flag = 0;
	RAISE(Restart_Repl);
    }
#if GC == 0
    if (fc < CONCSIZE)
	gbc();
#else
    if (fc < FREESIZE)
	(void) gbc();
#endif

    return 0;
}



int freecell(void)
{
    return (fc);
}
