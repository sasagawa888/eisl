/*
 * garbage collenction
 * Easy-ISLisp has two garbage collection system. mark&sweep and copying GC.
 * default is mark&sweep gc.
 * function (gbc x) switch each method.
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "eisl.h"
#include "compat/nana_stubs.h"
#include "mem.h"
#include "except.h"
#include "fmt.h"

#define DBG_PRINTF(msg,arg)     if(gbc_flag) printf(msg,arg)

/* mark&sweep garbage collection */
DEF_PREDICATE(EMPTY, EMP)
int gbc(void)
{
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

void gbc_mark(void)
{
    int i;

    /* mark nil and t */
    MARK_CELL(NIL);
    MARK_CELL(T);
    /* mark local environment */
    mark_cell(ep);
    /* mark dynamic environment */
    mark_cell(dp);
    /* mark stack */
    for (i = 0; i < sp; i++)
	mark_cell(stack[i]);
    /* mark cell binded by argstack */
    for (i = 0; i < ap; i++)
	mark_cell(argstk[i]);

    /* mark cell chained from hash table */
    for (i = 0; i < HASHTBSIZE; i++)
	mark_cell(cell_hash_table[i]);

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
    for (i = 1; i <= dp; i++)
	mark_cell(dynamic[i][1]);


    /* mark generic_list */
    mark_cell(generic_list);

}

static inline void NOMARK_CELL(int addr)
{
    heap[addr].flag = FRE;
}

void gbc_sweep(void)
{
    int addr;

    addr = 0;
    while (addr < CELLSIZE) {
	if (USED_CELL(addr))
	    NOMARK_CELL(addr);
	else {
	    clr_cell(addr);
	    SET_CDR(addr, hp);
	    hp = addr;
	}
	addr++;
    }
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
    if (gc_sw == 0 && fc < FREESIZE)
	(void) gbc();
    else if (gc_sw == 1 && wp < WORK2 && wp > WORK2 - FREESIZE)
	(void) gbc();
    else if (gc_sw == 1 && wp > WORK2 && wp > CELLSIZE - FREESIZE)
	(void) gbc();
    return 0;
}



int freecell(void)
{
    return (fc);
}



