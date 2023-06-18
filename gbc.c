/*
 * garbage collenction
 * Easy-ISLisp has mark&sweep garbage collection system.
 * Testing parallel GC. if define PARALLEL, use parallel GC. still testing.
 * Now I'm making concurrent GC. if define 
 */
#define PARALLEL
//#define CONCURRENT 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
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
    int* free;
    int* flag;
};


/* mark&sweep garbage collection */
DEF_PREDICATE(EMPTY, EMP)
int gbc(void)
{
    int addr;

    DBG_PRINTF("enter M&S-GC free=%d\n", fc);
    gbc_mark();
    #ifdef PARALLEL
    gbc_sweep_thread();
    #else
    gbc_sweep();
    #endif
    fc = 0;
    for (addr = 0; addr < CELLSIZE; addr++)
	if (IS_EMPTY(addr))
	    fc++;
    DBG_PRINTF("exit  M&S-GC free=%d\n", fc);
    return 0;
}

void *concurrent(void *arg);
void *concurrent(void *arg){
    int addr,fc1;
    struct data *pd = (struct data *)arg;

    pd->free = CELLSIZE;
    pd->flag = 1;
    DBG_PRINTF("enter M&S-GC free=%d\n", fc);
    gbc_mark();
    gbc_sweep();
    fc1 = 0;
    for (addr = 0; addr < CELLSIZE; addr++)
	if (IS_EMPTY(addr))
	    fc1++;
    DBG_PRINTF("exit  M&S-GC free=%d\n", fc);
    pd->free = fc1;
    pd->flag = 0;
    return NULL;
}

int gbc_concurrent(void)
{
    pthread_t t[1];
    struct data d[1];

    d[0].free = &fc;
    d[0].flag = &concurrent_flag;
    pthread_create(&t[0], NULL, concurrent, &d[0]);

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

void *mark(void *arg);
void *mark(void *arg){
    int i;
    struct data *pd = (struct data *)arg;

    for(i = pd->start; i < pd->end; i++){
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
    #ifdef PARALLEL
    gbc_hash_mark();
    #else 
    for (i = 0; i < HASHTBSIZE; i++)
	mark_cell(cell_hash_table[i]);
    #endif

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

void *sweep(void *arg);
void *sweep(void *arg){
    int addr,free;
    bool init;
    struct data *pd = (struct data *)arg;

    addr = pd->start;
    free = NIL;
    init = true;
    
    while (addr < pd->end) {
	if (USED_CELL(addr))
	    NOMARK_CELL(addr);
	else {
        if(init){
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

void gbc_sweep_thread(void){
    pthread_t t[NUM_THREAD];
    struct data d[NUM_THREAD];

    d[0].start = 0;
    d[0].end = 5000000;
    pthread_create(&t[0], NULL, sweep, &d[0]);

    d[1].start = 5000000;
    d[1].end =  10000000;
    pthread_create(&t[1], NULL, sweep, &d[1]);

    d[2].start = 10000000;
    d[2].end =   15000000;
    pthread_create(&t[2], NULL, sweep, &d[2]);

    d[3].start = 15000000;
    d[3].end =   CELLSIZE;
    pthread_create(&t[3], NULL, sweep, &d[3]);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);

    SET_CDR(d[3].tail,d[2].head);
    SET_CDR(d[2].tail,d[1].head);
    SET_CDR(d[1].tail,d[0].head);
    SET_CDR(d[0].tail,NIL);
    hp = d[3].head;
    return;
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
    if (fc < FREESIZE)
    #ifdef CONCURRENT 
    gbc_concurrent();
    #else
	(void) gbc();
    #endif

    return 0;
}



int freecell(void)
{
    return (fc);
}
