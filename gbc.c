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

#define DBG_PRINTF(msg,arg)     if(gbc_flag) printf(msg,arg)

/* mark&sweep garbage collection */
DEF_PREDICATE(EMPTY, EMP)
int gbc(void)
{
    if (gc_sw == 0) {
	int addr;

	DBG_PRINTF("enter M&S-GC free=%d\n", fc);
	gbc_mark();
	gbc_sweep();
	fc = 0;
	for (addr = 0; addr < CELLSIZE; addr++)
	    if (IS_EMPTY(addr))
		fc++;
	DBG_PRINTF("exit  M&S-GC free=%d\n", fc);
    } else {
	if (area_sw == 1) {
	    DBG_PRINTF("enter COPY-GC free=%d\n", WORK2 - wp);
	} else {
	    DBG_PRINTF("enter COPY-GC free=%d\n", CELLSIZE - wp);
	}
	copy_gbc();
	if (area_sw == 1) {
	    DBG_PRINTF("exit  COPY-GC free=%d\n", WORK2 - wp);
	} else {
	    DBG_PRINTF("exit  COPY-GC free=%d\n", CELLSIZE - wp);
	}
    }
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

    /* mark symbol list for catch */
    mark_cell(catch_symbols);

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


/*
 * copying garbage collection.
 * memory map M&S GC mode address 0 - 19999999 Heap area
 * 
 * Copying GC mode 0 - 5999999 Heap area 6000000 - 12999999 Work1 area
 * 12999999 - 19999999 Wrok2 area 
   
   |------------- 0  WP pointer
   |Heap area   save parmanent data
   |------------- 6000000
   |Work1 area  if Work1 has a lot of data, copy from work1 to work2   switch gc_sw = 0
   |------------- 13000000
   |Work2 area  if Work2 has a lot of data, copy from work2 to work1   gc_sw = 1  
   |------------- 20000000

 */

int gbcsw(void)
{
    return (gc_sw);
}

int getwp(void)
{
    return (wp);
}


void copy_gbc(void)
{
    int i;

    if (area_sw == 1) {
	area_sw = 2;
	wp = WORK2;
    } else {
	area_sw = 1;
	wp = WORK1;
    }

    /* copy local environment */
    ep = copy_work(ep);
    /* copy dynamic environment */
    dp = copy_work(dp);
    /* copy stack */
    for (i = 0; i < sp; i++)
	stack[i] = copy_work(stack[i]);
    /* copy cell binded by argstack */
    for (i = 0; i < ap; i++)
	argstk[i] = copy_work(argstk[i]);

    /* copy tagbody symbol */
    tagbody_tag = copy_work(tagbody_tag);

    /* copy thunk for unwind-protect */
    unwind_pt = copy_work(unwind_pt);


    /* copy shelter */
    for (i = 0; i < lp; i++)
	shelter[i] = copy_work(shelter[i]);

    /* copy generic_list */
    generic_list = copy_work(generic_list);

    /* copy symbol list for catch */
    catch_symbols = copy_work(catch_symbols);

    /* copy cell chained from hash table */
    for (i = 0; i < HASHTBSIZE; i++)
	copy_hash(cell_hash_table[i]);


}


/* ------------for copy GC----------------- */
int copy_work(int x)
{
    if (x < WORK1)		/* nil t ... */
	return (x);

    switch (GET_TAG(x)) {
    case INTN:
	return (copy_int(x));
    case FLTN:
	return (copy_flt(x));
    case LONGN:
	return (copy_long(x));
    case BIGN:
	return (copy_bignum(x));
    case VEC:
	return (copy_vec(x));
    case ARR:
	return (copy_array(x));
    case STR:
	return (copy_str(x));
    case CHR:
	return (copy_char(x));
    case SYM:
	return (x);
    case SUBR:
	return (x);
    case FSUBR:
	return (x);
    case FUNC:
	return (copy_func(x));
    case MACRO:
	return (copy_macro(x));
    case CLASS:
	return (copy_class(x));
    case STREAM:
	return (copy_stream(x));
    case GENERIC:
	return (copy_generic(x));
    case METHOD:
	return (x);		/* **** */
    case INSTANCE:
	return (x);		/* **** */
    case LIS:
	return (cons(copy_work(car(x)), copy_work(cdr(x))));
    case DUMMY:
	return (x);
    default:
	Fmt_print("error addr=%d  ", x);
	return (x);
    }

    return (x);
}


int copy_heap(int x)
{
    int save, res;

    save = gc_sw;
    gc_sw = 0;
    res = copy_work(x);
    gc_sw = save;
    return (res);
}

int copy_symbol(int x)
{

    SET_CAR(x, copy_work(GET_CAR(x)));
    SET_CDR(x, copy_work(GET_CDR(x)));
    SET_OPT(x, GET_OPT(x));
    return (x);
}

/*
 * copy_??? for copying GC 
 */
int copy_int(int x)
{
    return (x);
}

int copy_long(int x)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, LONGN);
    SET_LONG(addr, GET_LONG(x));
    SET_AUX(addr, clongnum);	/* class longnum */
    return (addr);
}


int copy_flt(int x)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, FLTN);
    SET_FLT(addr, GET_FLT(x));
    SET_AUX(addr, cfloat);	/* class float */
    return (addr);
}

static inline int *GET_VEC(int addr)
{
    return heap[addr].val.car.dyna_vec;
}

int copy_vec(int x)
{
    int addr;

    addr = freshcell();
    SET_VEC(addr, GET_VEC(x));	/* vector elements */
    SET_TAG(addr, VEC);
    SET_CDR(addr, GET_CDR(x));	/* vector size */
    SET_AUX(addr, cgeneral_vector);	/* class general-vector */
    return (addr);
}


int copy_array(int x)
{
    int addr;

    addr = freshcell();
    SET_VEC(addr, GET_VEC(x));	/* array or vector */
    SET_TAG(addr, GET_TAG(x));	/* tag ARR or VEC */
    SET_CDR(addr, GET_CDR(x));	/* dimension */
    SET_AUX(addr, GET_AUX(x));	/* class */
    return (addr);
}


int copy_str(int x)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, STR);		/* tag */
    heap[addr].name = heap[x].name;	/* string */
    SET_AUX(addr, GET_AUX(x));	/* class string */
    return (addr);
}


int copy_char(int x)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, CHR);
    heap[addr].name = heap[x].name;
    SET_AUX(addr, GET_AUX(x));
    return (addr);
}

int copy_func(int x)
{
    int val;

    val = freshcell();
    SET_TAG(val, FUNC);
    SET_NAME(val, GET_NAME(x));
    SET_CAR(val, copy_work(GET_CAR(x)));
    SET_CDR(val, copy_work(GET_CDR(x)));
    SET_AUX(val, GET_AUX(x));	/* class function */
    SET_OPT(val, GET_OPT(x));	/* amount of argument */
    return (val);
}

int copy_generic(int x)
{
    int val;

    val = freshcell();
    SET_TAG(val, GENERIC);
    SET_NAME(val, GET_NAME(x));
    SET_CAR(val, GET_CAR(x));
    SET_OPT(val, GET_OPT(x));	/* amount of argument */
    SET_CDR(val, copy_work(GET_CDR(x)));	/* method */
    SET_AUX(val, GET_AUX(x));
    return (val);
}

int copy_macro(int x)
{
    int val;

    val = freshcell();
    SET_TAG(val, MACRO);
    SET_CAR(val, copy_work(GET_CAR(x)));
    return (val);
}

int copy_stream(int x)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, STREAM);
    SET_PORT(addr, GET_PORT(x));
    SET_CDR(addr, GET_CDR(x));	/* string-stream-position */
    SET_AUX(addr, GET_AUX(x));	/* class */
    SET_OPT(addr, GET_OPT(x));	/* input/output/inout */
    return (addr);
}

int copy_class(int x)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, CLASS);
    SET_NAME(addr, GET_NAME(x));
    SET_CAR(addr, GET_CAR(x));
    SET_CDR(addr, GET_CAR(x));
    SET_AUX(addr, GET_CAR(x));
    return (addr);
}


int copy_bignum(int x)
{
    int addr, sign;

    sign = get_sign(x);
    addr = copy_gen_big();
    SET_TAG(addr, BIGN);
    set_sign(addr, sign);
    SET_AUX(addr, cbignum);
    return (addr);
}


/*
 * To check first cell, prop=-1. therefor when compute bignum, if it is
 * first cell, store data the cell. or else chain cell with cons_next.
 */
int copy_gen_big(void)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, BIGN);
    SET_AUX(addr, cbignum);
    return (addr);
}


/*
 * copy symbol of hash list 
 */

void copy_hash(int x)
{

    if (nullp(x))
	return;
    else {
	SET_CAR(x, copy_symbol(car(x)));
	copy_hash(cdr(x));
    }
}

