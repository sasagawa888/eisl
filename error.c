#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include "eisl.h"


//-------error------
void error(int errnum, char *fun, int arg){
    int initargs;

    
    switch(errnum){ 
        case DIV_ZERO:  initargs = list6(makesym("format-string"),makestr("division by zero at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cdivision_by_zero,initargs),NIL);
                        break;
        case UNDEF_VAR: initargs = list6(makesym("format-string"),makestr("Unbound variable at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cunbound_variable,initargs),NIL);
                        break;
        case UNDEF_FUN: initargs = list6(makesym("format-string"),makestr("Unbound function at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cundefined_function,initargs),NIL);
                        break;
        case UNDEF_CLASS:
                        initargs = list6(makesym("format-string"),makestr("Unbound class at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cundefined_entity,initargs),NIL);
                        break;
        case UNDEF_TAG: initargs = list6(makesym("format-string"),makestr("Unbound tag at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(ccontrol_error,initargs),NIL);
                        break;
        case WRONG_ARGS:initargs = list6(makesym("format-string"),makestr("Wrong number of arguments at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case NOT_NUM:   initargs = list10(makesym("format-string"),makestr("Not a number at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cnumber);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_POSITIVE:
                       initargs = list10(makesym("format-string"),makestr("Not a positive number at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cnumber);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case FLT_OVERF:
                       initargs = list10(makesym("format-string"),makestr("Floating number overflow at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cfloat);
                        signal_condition(makeinstance(cfloating_point_overflow,initargs),NIL);
                        break;
        case FLT_UNDERF:
                       initargs = list10(makesym("format-string"),makestr("Floating number underflow at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cfloat);
                        signal_condition(makeinstance(cfloating_point_underflow,initargs),NIL);
                        break;
        case NOT_INT:   initargs = list10(makesym("format-string"),makestr("Not an integer at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cinteger);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_FLT:   initargs = list10(makesym("format-string"),makestr("Not a float number at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cfloat);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_STR:   initargs = list10(makesym("format-string"),makestr("Not a string at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cstring);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_CHAR:  initargs = list10(makesym("format-string"),makestr("Not a character at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),ccharacter);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_LIST:  initargs = list10(makesym("format-string"),makestr("Not a list at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),clist);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_CONS:  initargs = list10(makesym("format-string"),makestr("Not a cons at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),ccons);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_VEC:   initargs = list10(makesym("format-string"),makestr("Not a vector at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cbasic_vector);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_ARR:   initargs = list10(makesym("format-string"),makestr("Not an array at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cbasic_array);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_VECARR:initargs = list10(makesym("format-string"),makestr("Not a vector or an array at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cbasic_array);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_SYM:   initargs = list10(makesym("format-string"),makestr("Not a symbol at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),csymbol);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_FUNC:  initargs = list10(makesym("format-string"),makestr("Not a function at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cfunction);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_STREAM:initargs = list10(makesym("format-string"),makestr("Not a stream at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cstream);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_IN_STREAM:
                        initargs = list10(makesym("format-string"),makestr("Not an input stream at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cstream);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_OUT_STREAM:
                        initargs = list10(makesym("format-string"),makestr("Not an output stream at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cstream);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_INSTANCE:
                        initargs = list10(makesym("format-string"),makestr("Not an instance at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cobject);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_CLASS: initargs = list10(makesym("format-string"),makestr("Not a class at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),cobject);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case NOT_ARITHMETIC:
                        initargs = list10(makesym("format-string"),makestr("Not a arithmetic condition at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("object"),arg,
                                          makesym("expected-class"),carithmetic_error);
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case ILLEGAL_RPAREN:
                        initargs = list6(makesym("format-string"),makestr("Illegal right parenthesis at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case ILLEGAL_INPUT:
                        initargs = list6(makesym("format-string"),makestr("Illegal input at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case ILLEGAL_FORM:
                        initargs = list6(makesym("format-string"),makestr("Illegal form at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case ILLEGAL_ARGS:
                        initargs = list6(makesym("format-string"),makestr("Illegal argument at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;
        case OUT_OF_RANGE:
                        initargs = list6(makesym("format-string"),makestr("Out of range at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;  
        case NOT_COMPUTABLE:
                        initargs = list6(makesym("format-string"),makestr("Not computable at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break;  
        case CANT_MODIFY:
                        initargs = list6(makesym("format-string"),makestr("Can't modify at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break; 
        case CANT_OPEN: initargs = list6(makesym("format-string"),makestr("Can't open a file at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break; 
        case CANT_CREATE:
                        initargs = list6(makesym("format-string"),makestr("Can't create instance for system defined class at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break; 
        case CANT_PARSE:initargs = list10(makesym("format-string"),makestr("Can't parse number at "),
                                          makesym("format-arguments"),arg,
                                          makesym("function"),makesym(fun),
                                          makesym("string"),arg,
                                          makesym("expected-class"),cobject);
                        signal_condition(makeinstance(cparse_error,initargs),NIL);
                        break;
        case CANT_ASSURE:
                        initargs = list6(makesym("format-string"),makestr("Can't assure at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cdomain_error,initargs),NIL);
                        break; 
        case CTRL_OVERF:initargs = list6(makesym("format-string"),makestr("Control stack over flow at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(ccontrol_error,initargs),NIL);
                        break; 
        case END_STREAM:initargs = list8(makesym("format-string"),makestr("End of stream at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun),
                                         makesym("stream"),arg);
                        signal_condition(makeinstance(cend_of_stream,initargs),NIL);
                        break; 
        case MALLOC_OVERF:
                        initargs = list6(makesym("format-string"),makestr("Memory allocate over flow at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cstorage_exhausted,initargs),NIL);
                        break;
        case NOT_EXIST_METHOD:
                        initargs = list6(makesym("format-string"),makestr("Not exist matched method at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break; 
        case HAS_COMMON_CLASS:
                        initargs = list6(makesym("format-string"),makestr("Super class has common parents at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case NOT_TOP_LEVEL:
                        initargs = list6(makesym("format-string"),makestr("Definition must be on top level at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case CANT_REDEFINE:
                        initargs = list6(makesym("format-string"),makestr("Can't modify system defined class at "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cerror,initargs),NIL);
                        break; 
        case STACK_OVERF:
                        initargs = list6(makesym("format-string"),makestr("Stack over flow "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case SHELTER_OVERF:
                        initargs = list6(makesym("format-string"),makestr("Shelter over flow "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case STACK_UNDERF:
                        initargs = list6(makesym("format-string"),makestr("Stack under flow "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case SHELTER_UNDERF:
                        initargs = list6(makesym("format-string"),makestr("Shelter under flow "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;
        case SYSTEM_ERR:
                        initargs = list6(makesym("format-string"),makestr("system error "),
                                         makesym("format-arguments"),arg,
                                         makesym("function"),makesym(fun));
                        signal_condition(makeinstance(cprogram_error,initargs),NIL);
                        break;                               
    }
}
/*
x = class
y = continuable string/NIL
*/
void signal_condition(int x, int y){
    int str,args,fun,handler;
    char *pname;
    
    if(y == NIL)
        SET_OPT(x,NOTCONT);
    else{
        SET_OPT(x,CONTINUABLE);
        pname = (char *)malloc(strlen(GET_NAME(y)+1));
        if(pname == NULL)
            error(MALLOC_OVERF,"signal-condition",NIL);
        heap[x].name = pname;
        strcpy(heap[x].name,GET_NAME(y));
    }
    if(ignore_flag)
        longjmp(ignore_buf,1);
    if(open_flag && error_handler==NIL){
        fclose(GET_PORT(input_stream));
        open_flag = 0;  
        printf("around here line=%d column=%d\n", line, column); 
    } 
    if(error_handler != NIL){
        handler = car(error_handler);
        error_handler = cdr(error_handler); 
        print(apply(handler,list1(x)));
        printf("\n");
        longjmp(buf,1);
    }
    str = cdr(assoc(makesym("a"),GET_CDR(x)));
    args = cdr(assoc(makesym("b"),GET_CDR(x)));
    fun = cdr(assoc(makesym("c"),GET_CDR(x)));
    output_stream = error_stream;
    fprintf(stderr,"%s",GET_NAME(str)); 
    print(fun);
    fprintf(stderr,"%s"," ");
    print(args);
    fprintf(stderr,"\n");
    fflush(stderr);
    input_stream = standard_input;
    output_stream = standard_output;
    debugger();
    longjmp(buf,1);
    
} 

int makeusercond(int class, int str, int arg){
    int initarg;
    
    initarg = list6(makesym("format-string"),str,
                    makesym("format-arguments"),arg,
                    makesym("function"),makesym(""));
    return(makeinstance(class,initarg));
}
