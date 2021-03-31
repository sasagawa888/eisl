#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include "eisl.h"


//---------garbage collection-----------
int gbc(void){
    debug_flag = 1;

    if(gc_sw == 0){
        int addr;

        if(gbc_flag){
            printf("enter M&S-GC free=%d\n", fc); 
            fflush(stdout);
        }
        gbcmark();
        gbcsweep();
        fc = 0;
        for(addr=0; addr < HEAPSIZE; addr++)
            if(IS_EMPTY(addr))
                fc++;
        if(gbc_flag){
            printf("exit  M&S-GC free=%d\n", fc);
            fflush(stdout);
        }
    }
    else{
        if(gbc_flag){
            if(area_sw == 1)
                printf("enter COPY-GC free=%d\n", WORK2 - wp); 
            else    
                printf("enter COPY-GC free=%d\n", CELLSIZE - wp);

            fflush(stdout);
        }
        copygbc();
        if(gbc_flag){
            if(area_sw == 1)
                printf("exit  COPY-GC free=%d\n", WORK2 - wp); 
            else    
                printf("exit  COPY-GC free=%d\n", CELLSIZE - wp);
    
            fflush(stdout);
        }
    }
    return 0;
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
                    markcell(cdr(addr)); // dimension
                    return;
        
        case FARR:  markcell(cdr(addr)); // dimension
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

    //mark tagbody symbol
    markcell(tagbody_tag);

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
    
    #ifdef DYN
    for(i=0;i<dp;i++)
        markcell(dynamic[i][1]);
    #endif

    //mark generic_list
    markcell(generic_list);

    //mark symbol list for catch
    markcell(catch_symbols);
	
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
    if(IS_VECTOR(addr) || IS_ARRAY(addr))
        free(heap[addr].val.car.dyna_vec);
    
    
    if(IS_FARRAY(addr)){
        free(heap[addr].val.car.dyna_vec);
        ac = ac - GET_OPT(addr);
    }
    

    SET_TAG(addr,EMP);
    free(heap[addr].name);
    heap[addr].name = NULL;
    SET_CAR(addr,0);
    SET_CDR(addr,0);
    SET_AUX(addr,0);
    SET_PROP(addr,0);
    SET_OPT(addr,0);
    SET_TR(addr,0);
}

//when free cells are less FREESIZE, invoke gbc()
int checkgbc(void){
    if(exit_flag == 1){
	    exit_flag = 0;
        longjmp(buf,1);
    }
    if(gc_sw == 0 && fc < FREESIZE)
      (void)gbc();
    else if(gc_sw == 1 && wp < WORK2 && wp > WORK2 - FREESIZE)
      (void)gbc();
    else if(gc_sw == 1 && wp > WORK2 && wp > CELLSIZE - FREESIZE)
      (void)gbc();
    else if(ac > FARRMAX){
      (void)gbc();
        ac = 0;
    }
    return 0;
}



int freecell(void){
	return(fc);
}

int gbcsw(void){
    return(gc_sw);
}

int getwp(void){
    return(wp);
}


void copygbc(void){
    int i;

    if(area_sw == 1){
        area_sw = 2;
        wp = WORK2;
    }
    else{
        area_sw = 1;
        wp = WORK1;
    }

    //copy local environment
    ep = copy_work(ep);
    //copy dynamic environment
    dp = copy_work(dp);
    //copy stack
    for(i=0; i<sp; i++)
        stack[i] = copy_work(stack[i]);
    //copy cell binded by argstack
    for(i=0; i<ap; i++)
        argstk[i] = copy_work(argstk[i]);

    //copy tagbody symbol
    tagbody_tag = copy_work(tagbody_tag);

    //copy thunk for unwind-protect
    unwind_pt = copy_work(unwind_pt);

    
    //copy shelter
    for(i=0;i<lp;i++)
        shelter[i] = copy_work(shelter[i]);

    //copy generic_list
    generic_list = copy_work(generic_list);

    //copy symbol list for catch
    catch_symbols = copy_work(catch_symbols);

    //copy cell chained from hash table
    for(i=0; i<HASHTBSIZE; i++)
        copy_hash(cell_hash_table[i]);

	
}
