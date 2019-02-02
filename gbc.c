#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include "eisl.h"


//---------garbage collection-----------
void gbc(void){
    int addr;

    if(gbc_flag){
        printf("enter GBC free=%d\n", fc); 
        fflush(stdout);
    }
    gbcmark();
    gbcsweep();
    fc = 0;
    for(addr=0; addr < HEAPSIZE; addr++)
        if(IS_EMPTY(addr))
            fc++;
    if(gbc_flag){
        printf("exit  GBC free=%d\n", fc);
         fflush(stdout);
    }
}


void markcell(int addr){
    int i,m,n,x;

    if(addr < 0 || addr >= HEAPSIZE)
		return;

    if(USED_CELL(addr))
        return;

    MARK_CELL(addr);
    switch(GET_TAG(addr)){
        case EMP:
        case INTN:
        case FLTN:
        case LONGN:
        case CHR:
        case STR:
        case STREAM:return;
        case BIGX:  x=addr;
                    do{
                        MARK_CELL(x);
                        x = next(x);
                    }while(!nullp(x));
                    return;
        case VEC:   n = vector_length(addr);
                    for(i=0; i<n; i++){
                        x = GET_VEC_ELT(addr,i);
                        markcell(x);
                    }
                    return;

        case ARR:   m = array_length(addr);
                    n = 1;
                    while(!nullp(m)){
                        n = n * GET_INT(car(m));
                        m = cdr(m);
                    }
                    for(i=0; i<n; i++){
                        x = GET_VEC_ELT(addr,i);
                        markcell(x);
                    }
                    markcell(cdr(addr));
                    return;

        case SYM:   markcell(car(addr));
                    markcell(cdr(addr));
                    markcell(GET_AUX(addr));
                    markcell(GET_PROP(addr));
                    return;
        case FUNC:
        case MACRO:
        case GENERIC:
        case METHOD:
        case CLASS:
        case INSTANCE:
        case LIS:   markcell(car(addr));
                    markcell(cdr(addr));
                    markcell(GET_AUX(addr));
                    return;
        case SUBR:
        case FSUBR: markcell(GET_AUX(addr));
                    return;

    }
}

void gbcmark(void){
    int i;

    //mark nil and t
    MARK_CELL(NIL);
    MARK_CELL(T);
    //mark local environment
    markcell(ep);
    //mark dynamic environment
    markcell(dp);
    //mark stack
    for(i=0; i<sp; i++)
        markcell(stack[i]);
    //mark cell binded by argstack
    for(i=0; i<ap; i++)
        markcell(argstk[i]);

    //mark cell chained from hash table
    for(i=0; i<HASHTBSIZE; i++)
        markcell(cell_hash_table[i]);

    //mark thunck of tagbody
    for(i=0; i<tagbody_pt; i++)
    	markcell(tagbody_tag[i][1]);

    //mark thunk for unwind-protect
    markcell(unwind_pt);

    //mark error_handler
    markcell(error_handler);

    //mark stream
    markcell(standard_input);
    markcell(standard_output);
    markcell(standard_error);
    markcell(input_stream);
    markcell(output_stream);
    markcell(error_stream);

    //mark shelter
    for(i=0;i<lp;i++)
        markcell(shelter[i]);

    //mark generic_list
    markcell(generic_list);

    //mark symbol list for catch
    markcell(catch_symbols);
	
	#if __linux
    //mark edit file name
    markcell(ed_name);
	#endif
}

void gbcsweep(void){
    int addr;

    addr = 0;
    while(addr < HEAPSIZE){
        if(USED_CELL(addr))
            NOMARK_CELL(addr);
        else{
            clrcell(addr);
            SET_CDR(addr,hp);
            hp = addr;
        }
        addr++;
    }
}

void clrcell(int addr){
    SET_TAG(addr,EMP);
    free(heap[addr].name);
    if(IS_VECTOR(addr) || IS_ARRAY(addr))
        free(heap[addr].val.car.dyna_vec);
    heap[addr].name = NULL;
    SET_CAR(addr,0);
    SET_CDR(addr,0);
    SET_AUX(addr,0);
    SET_OPT(addr,0);
    SET_TR(addr,0);
}

//when free cells are less FREESIZE, invoke gbc()
void checkgbc(void){
    if(exit_flag == 1){
	exit_flag = 0;
        longjmp(buf,1);
    }
	#if _WIN32
	//ctrl+d terminate intepreter
    if(exit_flag == 2)
    	longjmp(buf,2);
    #endif
    if(fc < FREESIZE)
        gbc();
}



int freecell(void){
	return(fc);
}
