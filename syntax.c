#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "eisl.h"

#define TAGBODY_LEN_MAX 100

void initsyntax(void){
    deffsubr("LAMBDA",f_lambda);
    deffsubr("LABELS",f_labels);
    deffsubr("FLET",f_flet);
    deffsubr("LET",f_let);
    deffsubr("LET*",f_letstar);
    deffsubr("SETQ",f_setq);
    deffsubr("SETF",f_setf);
    deffsubr("SET-DYNAMIC",f_set_dynamic);
    deffsubr("DEFCONSTANT",f_defconstant);
    deffsubr("DEFUN",f_defun);
    deffsubr("DEFMACRO",f_defmacro);
    deffsubr("DEFGLOBAL",f_defglobal);
    deffsubr("DEFDYNAMIC",f_defdynamic);
    deffsubr("DYNAMIC",f_dynamic);
    deffsubr("FUNCTION",f_function);
    deffsubr("FUNCTION*",f_function_star);
    deffsubr("SYMBOL-FUNCTION",f_symbol_function);
    deffsubr("CLASS",f_class);
    deffsubr("SYMBOL-CLASS",f_symbol_class);
    deffsubr("AND",f_and);
    deffsubr("OR",f_or);
    deffsubr("IF",f_if);
    deffsubr("COND",f_cond);
    deffsubr("WHILE",f_while);
    deffsubr("FOR",f_for);
    deffsubr("BLOCK",f_block);
    deffsubr("RETURN-FROM",f_return_from);
    deffsubr("CASE",f_case);
    deffsubr("CASE-USING",f_case_using);
    deffsubr("PROGN",f_progn);
    deffsubr("DEFCLASS",f_defclass);
    deffsubr("DEFGENERIC",f_defgeneric);
    deffsubr("DEFGENERIC*",f_defgeneric_star);
    deffsubr("DEFMETHOD",f_defmethod);
    deffsubr("DYNAMIC-LET",f_dynamic_let);
    deffsubr("IGNORE-ERRORS",f_ignore_errors);
    deffsubr("CATCH",f_catch);
    deffsubr("THROW",f_throw);
    deffsubr("TAGBODY",f_tagbody);
    deffsubr("GO",f_go);
    deffsubr("UNWIND-PROTECT",f_unwind_protect);
    deffsubr("WITH-STANDARD-INPUT",f_with_standard_input);
    deffsubr("WITH-STANDARD-OUTPUT",f_with_standard_output);
    deffsubr("WITH-ERROR-OUTPUT",f_with_error_output);
    deffsubr("WITH-HANDLER",f_with_handler);
    deffsubr("CONVERT",f_convert);
    deffsubr("WITH-OPEN-INPUT-FILE",f_with_open_input_file);
    deffsubr("WITH-OPEN-OUTPUT-FILE",f_with_open_output_file);
    deffsubr("WITH-OPEN-IO-FILE",f_with_open_io_file);
    deffsubr("THE",f_the);
    deffsubr("ASSURE",f_assure);
    deffsubr("TIME",f_time);
    deffsubr("TRACE",f_trace);
    deffsubr("UNTRACE",f_untrace);
    deffsubr("DEFMODULE",f_defmodule);
}

//--FSUBR-----------
int f_lambda(int arglist){

    if(nullp(arglist))
        error(NOT_EXIST_ARG, "lambda", NIL);
    if(duplicatelistp(car(arglist)))
        error(IMPROPER_ARGS, "lambda", car(arglist));
    if(improperlistp(car(arglist)))
        error(IMPROPER_ARGS, "lambda", car(arglist));
    if(illegallambdap(car(arglist)))
        error(ILLEGAL_ARGS, "lambda", car(arglist));
    if(!symbollistp(car(arglist)))
        error(OUT_OF_DOMAIN, "lambda", car(arglist));
    
       
    return(makefunc("",arglist));
}

int f_labels(int arglist){
    int arg1,arg2,save,func,res,temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "labels", arglist);
    if(nullp(arglist))
        error(NOT_EXIST_ARG, "labels", NIL);
    if(!listp(arg1))
        error(IMPROPER_ARGS, "labels", arg1);
    temp = arg1;
    while(!nullp(temp)){
        int temparg1,temparg2;

        temparg1 = car(car(temp));
        temparg2 = cdr(car(temp));
        if(length(car(temp)) < 2)
            error(IMPROPER_ARGS, "labels", car(temp));
        if(!symbolp(temparg1))
            error(NOT_SYM, "labels", temparg1);
        if(STRING_REF(temparg1,0) == ':' || STRING_REF(temparg1,0) == '&')
            error(WRONG_ARGS, "labels", temparg1);
        if(duplicatelistp(car(temparg2)))
            error(IMPROPER_ARGS, "labels", car(temparg2));
        if(improperlistp(car(temparg2)))
            error(IMPROPER_ARGS, "labels", car(temparg2));
        if(illegallambdap(car(temparg2)))
            error(ILLEGAL_ARGS, "labels", car(temparg2));
        if(!symbollistp(car(temparg2)))
            error(OUT_OF_DOMAIN, "labels", car(temparg2));

        temp = cdr(temp);
    }
    

    save = ep;
    func = NIL;
    res = NIL;
    while(arg1 != NIL){
        int sym,val;

        sym = caar(arg1);
        if(!symbolp(sym))
            error(NOT_SYM, "labels", sym);
        addlexenv(sym,NIL);
        val = makefunc("",cdar(arg1));
        setlexenv(sym,val);
        func = cons(val,func);
        arg1 = cdr(arg1);
    }
    while(func != NIL){
        SET_CDR(car(func),ep);
        func = cdr(func);
    }
    while(arg2 != NIL){
        res = eval(car(arg2));
        arg2 = cdr(arg2);
    }
    ep = save;
    return(res);
}

int f_flet(int arglist){
    int arg1,arg2,save,ep1,res,temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "flet", arglist);
    if(nullp(arglist))
        error(NOT_EXIST_ARG, "flet", NIL);
    if(!listp(arg1))
        error(IMPROPER_ARGS, "flet", arg1);
    temp = arg1;
    while(!nullp(temp)){
        int temparg1,temparg2;

        temparg1 = car(car(temp));
        temparg2 = cdr(car(temp));
        if(length(car(temp)) < 2)
            error(IMPROPER_ARGS, "flet", car(temp));
        if(!symbolp(temparg1))
            error(NOT_SYM, "flet", temparg1);
        if(STRING_REF(temparg1,0) == ':' || STRING_REF(temparg1,0) == '&')
            error(WRONG_ARGS, "flet", temparg1);
        if(duplicatelistp(car(temparg2)))
            error(IMPROPER_ARGS, "flet", car(temparg2));
        if(improperlistp(car(temparg2)))
            error(IMPROPER_ARGS, "flet", car(temparg2));
        if(illegallambdap(car(temparg2)))
            error(ILLEGAL_ARGS, "flet", car(temparg2));
        if(!symbollistp(car(temparg2)))
            error(OUT_OF_DOMAIN, "flet", car(temparg2));

        temp = cdr(temp);
    }
    
    save = ep;
    ep1 = ep;
    res = NIL;
    while(arg1 != NIL){
        int sym,val;

        sym = caar(arg1);
        if(!symbolp(sym))
            error(NOT_SYM, "flet", sym);
        ep = save;
        val = makefunc("",cdar(arg1));
        ep = ep1;
        addlexenv(sym,val);
        ep1 = ep;
        arg1 = cdr(arg1);
    }
    while(arg2 != NIL){
        res = eval(car(arg2));
        arg2 = cdr(arg2);
    }
    ep = save;
    return(res);
}

int f_let(int arglist){
    int arg1,arg2,save,res,temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(length(arglist) == 0)
        error(WRONG_ARGS, "let", arglist);
    if(!listp(arg1))
        error(IMPROPER_ARGS, "let", arg1);
    temp = arg1;
    while(!nullp(temp)){
        int temparg1;

        temparg1 = car(car(temp));
        if(improperlistp(car(temp)))
            error(IMPROPER_ARGS, "let", car(temp));
        if(length(car(temp)) != 2)
            error(IMPROPER_ARGS, "let", car(temp));
        if(!symbolp(temparg1))
            error(NOT_SYM, "let" ,temparg1);
        if(temparg1 == T || temparg1 == NIL || temparg1 == makesym("*PI*") || 
           temparg1 == makesym("*MOST-POSITIVE-FLOAT*") || temparg1 == makesym("*MOST-NEGATIVE-FLOAT*"))
            error(WRONG_ARGS, "let", arg1);
        if(STRING_REF(temparg1,0) == ':' || STRING_REF(temparg1,0) == '&')
            error(WRONG_ARGS, "let", arg1);
        
        temp = cdr(temp);
    }

    save = ep;
    res = NIL;
    while(arg1 != NIL){
        int ep1,sym,val;

        ep1 = ep;
        ep = save;
        sym = caar(arg1);
        if(!symbolp(sym))
            error(NOT_SYM, "let", sym);
        shelterpush(ep1);
        val = eval(cadar(arg1));
        shelterpop();
        ep = ep1;
        addlexenv(sym,val);
        arg1 = cdr(arg1);
    }
    while(arg2 != NIL){
        shelterpush(arg2);
        res = eval(car(arg2));
        shelterpop();
        arg2 = cdr(arg2);
    }
    ep = save;
    return(res);
}

int f_letstar(int arglist){
    int arg1,arg2,save,res,temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(length(arglist) == 0)
        error(WRONG_ARGS, "let*", arglist);
    if(!listp(arg1))
        error(IMPROPER_ARGS, "let*", arg1);
    temp = arg1;
    while(!nullp(temp)){
        int temparg1;

        temparg1 = car(car(temp));
        if(improperlistp(car(temp)))
            error(IMPROPER_ARGS, "let*", car(temp));
        if(length(car(temp)) != 2)
            error(IMPROPER_ARGS, "let*", car(temp));
        if(!symbolp(temparg1))
            error(NOT_SYM, "let*" ,temparg1);
        if(temparg1 == T || temparg1 == NIL || temparg1 == makesym("*PI*") || 
           temparg1 == makesym("*MOST-POSITIVE-FLOAT*") || temparg1 == makesym("*MOST-NEGATIVE-FLOAT*"))
            error(WRONG_ARGS, "let*", arg1);
        if(STRING_REF(temparg1,0) == ':' || STRING_REF(temparg1,0) == '&')
            error(WRONG_ARGS, "let*", arg1);
        
        temp = cdr(temp);
    }

    save = ep;
    res = NIL;
    while(arg1 != NIL){
        int sym;

        sym = caar(arg1);
        if(!symbolp(sym))
            error(NOT_SYM, "let*", sym);
        addlexenv(sym,eval(cadar(arg1)));
        arg1 = cdr(arg1);
    }
    while(arg2 != NIL){
        res = eval(car(arg2));
        arg2 = cdr(arg2);
    }
    ep = save;
    return(res);
}

int f_dynamic_let(int arglist){
    int arg1,arg2,save,res,temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(length(arglist) == 0)
        error(WRONG_ARGS, "dynamic-let", arglist);
    if(!listp(arg1))
        error(IMPROPER_ARGS, "dynamic-let", arg1);
    temp = arg1;
    while(!nullp(temp)){
        int temparg1;

        temparg1 = car(car(temp));
        if(improperlistp(car(temp)))
            error(IMPROPER_ARGS, "dynamic-let", car(temp));
        if(length(car(temp)) != 2)
            error(IMPROPER_ARGS, "dynamic-let", car(temp));
        if(!symbolp(temparg1))
            error(NOT_SYM, "dynamic-let" ,temparg1);
        if(temparg1 == T || temparg1 == NIL || temparg1 == makesym("*PI*") || 
           temparg1 == makesym("*MOST-POSITIVE-FLOAT*") || temparg1 == makesym("*MOST-NEGATIVE-FLOAT*"))
            error(WRONG_ARGS, "dynamic-let", arg1);
        if(STRING_REF(temparg1,0) == ':' || STRING_REF(temparg1,0) == '&')
            error(WRONG_ARGS, "dynamic-let", arg1);
        
        temp = cdr(temp);
    }
    
    save = dp;
    res = NIL;
    while(arg1 != NIL){
        int dp1,sym,val;

        dp1 = dp;
        dp = save;
        shelterpush(dp1);
        sym = caar(arg1);
        if(!symbolp(sym))
            error(NOT_SYM, "dynamic-let", sym);
        val = eval(cadar(arg1));
        dp = dp1;
        shelterpop();
        adddynenv(sym,val);
        arg1 = cdr(arg1);
    }
    while(arg2 != NIL){
        res = eval(car(arg2));
        arg2 = cdr(arg2);
    }
    dp = save;
    return(res);
}


int f_setf(int arglist){
    int arg1,arg2,newform,var,res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    newform = NIL;
    if(length(arglist) != 2)
        error(WRONG_ARGS, "setf", arglist);
    if(arg1 == T || arg1 == NIL)
    	error(CANT_MODIFY,"setf",arg1);
    if(listp(arg1) && eqlp(makeint(1),cdr(assoc(makesym("read"),GET_AUX(car(arg1))))))
       error(CANT_MODIFY,"setf",arg1);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "setf", arglist);

    if(listp(arg1) && eqp(car(arg1),makesym("AREF"))){
        newform = cons(makesym("SET-AREF"),cons(arg2,cdr(arg1)));
    }
    else if(listp(arg1) && eqp(car(arg1),makesym("GAREF"))){
    	newform = cons(makesym("SET-GAREF"),cons(arg2,cdr(arg1)));
    }
    else if(listp(arg1) && eqp(car(arg1),makesym("ELT"))){
        newform = cons(makesym("SET-ELT"),cons(arg2,cdr(arg1)));
    }
    else if(listp(arg1) && eqp(car(arg1),makesym("PROPERTY"))){
    	newform = cons(makesym("SET-PROPERTY"),cons(arg2,cdr(arg1)));
    }
	else if(listp(arg1) && eqp(car(arg1),makesym("CAR"))){
    	newform = cons(makesym("SET-CAR"),cons(arg2,cdr(arg1)));
    }
    else if(listp(arg1) && eqp(car(arg1),makesym("CDR"))){
    	newform = cons(makesym("SET-CDR"),cons(arg2,cdr(arg1)));
    }
    else if(listp(arg1) && eqp(car(arg1),makesym("DYNAMIC"))){
        if(improperlistp(arg1))
            error(IMPROPER_ARGS, "dynamic", arg1);
        if(length(arg1) != 2)
            error(IMPROPER_ARGS, "dynamic", arg1);
    	newform = cons(makesym("SET-DYNAMIC"),list2(cadr(arg1),arg2));
    }
    else if(listp(arg1) && macrop(car(arg1))){
        var = f_macroexpand_1(list1(arg1));
        return(f_setf(list2(var,arg2)));
    }
    // (setf (slot-value instance slot-name) value)
    else if(listp(arg1) && eqp(car(arg1),makesym("SLOT-VALUE"))){
    	newform = cons(makesym("SET-SLOT-VALUE"),cons(arg2,cdr(arg1)));
    }
    //e.g. (setf (access-foo-a x) 100) 
    else if(listp(arg1) && length(arg1) == 2){
        //a method returns it's variable name 
        var = eval(list2(car(arg1),NIL));
    	newform = cons(makesym("SET-SLOT-VALUE"),cons(arg2,list2(cadr(arg1),list2(makesym("QUOTE"),var))));
    }
    else if(symbolp(arg1)){
    	newform = cons(makesym("SETQ"),list2(arg1,arg2));
    }
    else
    	error(IMPROPER_ARGS,"setf",arglist);

    shelterpush(newform);
    res = eval(newform);
    shelterpop();
    return(res);
}



int f_set_dynamic(int arglist){
	int arg1,arg2;

    arg1 = car(arglist);
    arg2 = eval(cadr(arglist));
    if(nullp(arglist))
        error(IMPROPER_ARGS, "set-dynamic", arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "set-dynamic", arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "set-dynamic", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "set-dynamic", arg1);
    if(STRING_REF(arg1,0) == ':' || STRING_REF(arg1,0) == '&')
        error(WRONG_ARGS, "set-dynamic", arg1);

    if(finddyn(arg1) != FAILSE){
        setdynenv(arg1,arg2);
        return(arg2);
    }
    else
    	error(UNDEF_VAR, "set-dynamic", arg1);

    return(arg2);
}


int f_setq(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "setq", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "setq", arg1);
    if(GET_OPT(arg1) == CONSTN)
        error(CANT_MODIFY, "setq" ,arg1);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "setq", arglist);

    arg2 = eval(arg2);
    if(findenv(arg1) != FAILSE)
        setlexenv(arg1,arg2);
    else if(GET_OPT(arg1) == GLOBAL)
        SET_CDR(arg1,arg2);
    else
        error(UNDEF_VAR, "setq", arg1);

    return(arg2);
}

int f_defconstant(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "defconstant", arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "defconstant", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "defconstant", arg1);
    if(arg1 == T || arg1 == NIL || arg1 == makesym("*PI*") || 
      arg1 == makesym("*MOST-POSITIVE-FLOAT*") || arg1 == makesym("*MOST-NEGATIVE-FLOAT*"))
        error(WRONG_ARGS, "defconstant", arg1);
    if(STRING_REF(arg1,0) == ':' || STRING_REF(arg1,0) == '&')
        error(WRONG_ARGS, "defconstant", arg1);
    if(!top_flag && !ignore_topchk)
        error(NOT_TOP_LEVEL, "defconstant", arglist);

    SET_CDR(arg1,eval(arg2));
    SET_OPT(arg1,CONSTN); //constant
    return(arg1);

}

int f_defun(int arglist){
    int arg1,arg2,val;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(length(arglist) < 2)
        error(WRONG_ARGS, "defun", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "defun", arg1);
    if(IS_SUBR(GET_CAR(arg1)))
        error(CANT_MODIFY, "defun", arg1);
    if(IS_FSUBR(GET_CAR(arg1)))
        error(CANT_MODIFY, "defun", arg1);
    if(STRING_REF(arg1,0) == ':' || STRING_REF(arg1,0) == '&')
        error(WRONG_ARGS, "defun", arg1);
    if(duplicatelistp(car(arg2)))
        error(IMPROPER_ARGS, "defun", car(arg2));
    if(improperlistp(car(arg2)))
        error(IMPROPER_ARGS, "defun", car(arg2));
    if(illegallambdap(car(arg2)))
        error(ILLEGAL_ARGS,"defun", car(arg2));
    if(!symbollistp(car(arg2)))
        error(OUT_OF_DOMAIN, "defun", car(arg2));
    

    val = makefunc(GET_NAME(arg1),arg2);
    SET_CAR(arg1,val);
    return(arg1);
}

int f_defmacro(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    
    if(!symbolp(arg1))
        error(NOT_SYM, "defmacro", arg1);
    if(GET_OPT(arg1) == CONSTN)
        error(CANT_MODIFY, "defmacro", arg1);
    if(IS_SUBR(GET_CAR(arg1)))
        error(CANT_MODIFY, "defmacro", arg1);
    if(IS_FSUBR(GET_CAR(arg1)))
        error(CANT_MODIFY, "defmacro", arg1);
    if(improperlistp(arg2))
        error(IMPROPER_ARGS,"defmacro", arg2);
    if(length(arglist) < 2)
        error(WRONG_ARGS, "defmacro", arglist);
    if(length(arglist) < 3)
        error(IMPROPER_ARGS, "defmacro", arglist);
    if(illegallambdap(car(arg2)))
        error(ILLEGAL_ARGS,"defmacro", car(arg2));

    bindmacro(GET_NAME(arg1),arg2);
    return(arg1);
}

int f_defglobal(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "defglobal", arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "defglobal", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "defglobal", arg1);
    if(GET_OPT(arg1) == CONSTN)
        error(CANT_MODIFY, "defglobal", arg1);
    if(STRING_REF(arg1,0) == ':' || STRING_REF(arg1,0) == '&')
        error(WRONG_ARGS, "defglobal", arg1);

    SET_CDR(arg1,eval(arg2));
    SET_OPT(arg1,GLOBAL);
    return(arg1);
}

int f_defdynamic(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(improperlistp(cdr(arglist)))
        error(IMPROPER_ARGS, "defdynamic", arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "defdynamic", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "defdynamic", arg1);
    if(STRING_REF(arg1,0) == ':' || STRING_REF(arg1,0) == '&')
        error(WRONG_ARGS, "defdynamic", arg1);
    

    setdynenv(arg1,eval(arg2));
    return(arg1);
}

int f_dynamic(int arglist){
    int arg1,res;

    arg1 = car(arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "dynamic", arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "dynamic", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "dynamic", arg1);
    
    res = finddyn(arg1);
    if(res == FAILSE)
        error(UNDEF_DYN, "dynamic", arg1);

    return(res);
}

int f_and(int arglist){

    if(nullp(arglist))
        return(T);
    else if(nullp(cdr(arglist)))
        return(eval(car(arglist)));
    else if(eval(car(arglist)) != NIL)
        return(f_and(cdr(arglist)));
    else
        return(NIL);

}

int f_or(int arglist){
    int temp;

    if(nullp(arglist))
        return(NIL);
    else if(nullp(cdr(arglist)))
        return(eval(car(arglist)));
    else if((temp=eval(car(arglist))) == NIL)
        return(f_or(cdr(arglist)));
    else
        return(temp);

    return(UNDEF);
}

int f_function(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "function", arglist);
    if(improperlistp(arglist))
        error(ILLEGAL_ARGS, "function", arglist);

    if(symbolp(arg1)){
        int res;

        res = findenv(arg1);
        if(IS_FUNC(res))
            return(res);
        else if(GET_CAR(arg1) != NIL)
            return(GET_CAR(arg1));
        else
            error(UNDEF_FUN,"function",arg1);
    }
    else if(listp(arg1) && eqp(car(arg1),makesym("lambda")))
        return(eval(arg1));
    else
        error(NOT_FUNC, "function", arg1);
    return(UNDEF);
}
//function* diffrence of function is that return nil
//defclass uses this function*
int f_function_star(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "function*", arglist);
    if(improperlistp(arglist))
        error(ILLEGAL_ARGS, "function*", arglist);

    if(symbolp(arg1)){
        int res;

        res = findenv(arg1);
        if(IS_FUNC(res))
            return(res);
        else if(GET_CAR(arg1) != NIL)
            return(GET_CAR(arg1));
        else
            return(NIL);
    }
    else if(listp(arg1) && eqp(car(arg1),makesym("lambda")))
        return(eval(arg1));
    else
        return(NIL);
    return(UNDEF);
}

int f_symbol_function(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "symbol-function", arglist);

    if(symbolp(arg1)){
        int sym,res;

        sym = findenv(arg1);
        if(sym == FAILSE && GET_CDR(arg1) != NIL)
            sym = GET_CDR(arg1);

        if(!symbolp(sym))
            error(UNDEF_FUN,"symbol-function",arg1);

        res = findenv(sym);
        if(IS_FUNC(res))
            return(res);
        else if(GET_CAR(sym) != NIL)
            return(GET_CAR(sym));
        else
            error(UNDEF_FUN,"symbol-function",sym);
    }
    else
        error(ILLEGAL_ARGS, "symbol-function", arg1);
    return(UNDEF);
}

int f_class(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "class", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "class", arglist);
    if(GET_AUX(arg1) == NIL)
        error(UNDEF_CLASS,"class",arg1);
    if(GET_AUX(arg1) == csymbol && GET_OPT(arg1) != SYSTEM)
        error(UNDEF_CLASS,"class",arg1);

    return(GET_AUX(arg1));
}

int f_symbol_class(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "symbol-class", arglist);

    if(symbolp(arg1)){
        int sym;

    	sym = findenv(arg1);
        if(sym == FAILSE && GET_CDR(arg1) != NIL)
            sym = GET_CDR(arg1);

        if(!symbolp(sym))
            error(UNDEF_CLASS,"symbol-class",arg1);

    	if(GET_AUX(sym) == NIL)
        	error(UNDEF_CLASS,"symbol-class",sym);
    	if(GET_AUX(sym) == csymbol && GET_OPT(sym) != SYSTEM)
        	error(UNDEF_CLASS,"class",sym);

    	return(GET_AUX(sym));
   }
   else{
    	error(ILLEGAL_ARGS, "symbol-class", arg1);
    	return(UNDEF);
   }
}



int f_if(int arglist){
    int arg1,arg2,arg3,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if((n=length(arglist)) < 2 || n > 3)
        error(WRONG_ARGS, "if", arglist);
    if(improperlistp(arglist))
        error(WRONG_ARGS, "if", arglist);

    if(length(arglist) == 3)
        arg3 = car(cdr(cdr(arglist)));
    else
        arg3 = NIL;

    if(! (nullp(eval(arg1))))
        return(eval(arg2));
    else{
        return(eval(arg3));
    }
}

int f_cond(int arglist){
    int arg1,arg2,arg3;

    if(nullp(arglist))
        return(NIL);

    arg1 = car(arglist);
    arg2 = car(arg1);
    arg3 = cdr(arg1);
    if(nullp(arg1))
        error(IMPROPER_ARGS, "cond", arglist);
    if(improperlistp(arg1))
        error(IMPROPER_ARGS, "cond", arg1);
    

    if(length(arg1) == 1 && atomp(arg2) && !nullp(eval(arg2)))
        return(arg2);
    else if(!nullp(eval(arg2)))
        return(f_progn(arg3));
    else
        return(f_cond(cdr(arglist)));
}

int f_while(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    while(eval(arg1) != NIL){
        f_progn(arg2);
    }
    return(NIL);
}

int f_for(int arglist){
    int arg1,arg2,arg3,iter,temp,save,res,temparg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);
    if(length(arglist) < 2)
        error(WRONG_ARGS, "for", arglist);
    if(!listp(arg1))
        error(NOT_LIST, "for", arg1);   
    if(!listp(arg2))
        error(NOT_LIST, "for", arg2);
    if(nullp(arg2))
        error(IMPROPER_ARGS, "for", arg2); 
    
    temp = arg1;
    temparg2 = NIL;
    while(!nullp(temp)){
        int temp1,temparg1;

        temp1 = car(temp);
        if(!listp(temp1))
            error(IMPROPER_ARGS, "for", temp1);
        temparg1 = car(temp1);

        if(!symbolp(temparg1))
            error(NOT_SYM, "for", temparg1);
        if(STRING_REF(temparg1,0) == ':' || STRING_REF(temparg1,0) == '&')
            error(WRONG_ARGS, "for", arg1);
        if(temparg1 == T || temparg1 == NIL || temparg1 == makesym("*PI*") || 
           temparg1 == makesym("*MOST-POSITIVE-FLOAT*") || temparg1 == makesym("*MOST-NEGATIVE-FLOAT*"))
            error(WRONG_ARGS, "for", temparg1);
        if(length(temp1) !=2 && length(temp1) != 3)
            error(IMPROPER_ARGS, "for", temp1);
        if(member(temparg1,temparg2))
            error(IMPROPER_ARGS, "for", temparg1);

        temparg2 = cons(temparg1,temparg2);
        temp = cdr(temp);
    }

    save = ep;

    iter = arg1;
    //initilize local variable
    while(iter != NIL){
        addlexenv(caar(iter),eval(cadar(iter)));
        iter = cdr(iter);
    }
    //check condition of end
    while(eval(car(arg2)) == NIL){
        int save1;

        save1 = ep;
        shelterpush(arg3);
        f_progn(arg3);// do body
        shelterpop();
        ep = save1;
        iter = arg1;  //update local variable
        temp = NIL;
        while(iter != NIL){
            if(!nullp(caddar(iter))){ //update part is not null
                shelterpush(iter);
                shelterpush(temp);
                temp = cons(cons(caar(iter),eval(caddar(iter))),temp);
                shelterpop();
                shelterpop();
            }
            iter = cdr(iter);
        }
        while(temp != NIL){
            setlexenv(caar(temp),cdar(temp));
            temp = cdr(temp);
        }
    }
    res = f_progn(cdr(arg2));
    ep = save;
    return(res);
}

int f_block(int arglist){
    int arg1,arg2,tag,ret,res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(nullp(arglist))
        error(WRONG_ARGS, "block", arglist);
    if(improperlistp(arglist) && nullp(arg1))
        error(WRONG_ARGS, "block", arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "block", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "block", arg1);
    
    tag = arg1;

    if(block_pt >= 50)
        error(CTRL_OVERF, "block buffer over fllow", NIL);

    block_env[block_pt][0] = ep; //save environment
	block_env[block_pt][1] = tag; //save tag symbol
    block_pt++;
    ret = setjmp(block_buf[block_pt - 1]);


    if(ret == 0){
        res = f_progn(arg2);
        block_pt--;
        return(res);
    }
    else if(ret == 1){
        if(unwind_pt > 0){
            unwind_pt--;
            while(unwind_pt >= 0){
			    apply(unwind_buf[unwind_pt],NIL);
                unwind_pt--;
            }
            unwind_pt = 0;
        }
        res = block_arg;
        return(res);
    }
    return(UNDEF);
}

int f_return_from(int arglist){
    int arg1,arg2,tag;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "return-from", arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "return-from", arg1);
    tag = arg1;
    block_pt--;
    if(block_env[block_pt][1] != tag)
    	error(ILLEGAL_ARGS, "return-from tag not exist", tag);
    block_arg = f_progn(arg2);
    ep = block_env[block_pt][0]; //restore environment
    longjmp(block_buf[block_pt],1);
}



int f_catch(int arglist){
    int arg1,arg2,i,tag,ret,res,save;

    save = sp;
    arg1 = car(arglist); //tag
    arg2 = cdr(arglist); //body
    if(nullp(arglist))
        error(WRONG_ARGS,"catch",arglist);
    if(arg1 == makesym("catch"))
        error(WRONG_ARGS,"catch",arglist);
    if(nullp(arg1))
        error(WRONG_ARGS,"catch",arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS,"catch",arglist);
    tag = eval(arg1);    //tag symbol
    if(!symbolp(tag))
    	error(IMPROPER_ARGS,"catch",tag);


    if(!member(tag,catch_symbols))
        catch_symbols = cons(tag,catch_symbols);
    if(GET_OPT(tag) == 0){
    	catch_pt++; //opt is 1~5, when 0 symbol is not tag
    	SET_OPT(tag,catch_pt);
        if(catch_pt > CTRLSTK)
        error(CTRL_OVERF, "catch tag count", NIL);
    }
    i = GET_PROP(tag);
    SET_PROP(tag,GET_PROP(tag)+1); //nest level +1
    if(GET_PROP(tag) > CTRLSTK)
        error(CTRL_OVERF, "catch tag nest", tag);

    catch_env[GET_OPT(tag)-1][i] = ep; //save environment
    ret = setjmp(catch_buf[GET_OPT(tag)-1][i]);


    if(ret == 0){
        res = f_progn(arg2);
        SET_PROP(tag,GET_PROP(tag)-1); //nest level -1
        return(res);
    }
    else if(ret == 1){
        if(unwind_pt > 0){
            unwind_pt--;
            while(unwind_pt >= 0){
			    apply(unwind_buf[unwind_pt],NIL);
                unwind_pt--;
            }
            unwind_pt = 0;
        }
        res = catch_arg;
        catch_arg = NIL;
        sp = save; //restore stack pointer. longjump destroy sp
        return(res);
    }
    return(UNDEF);
}


int f_throw(int arglist){
    int arg1,arg2,tag,i;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    tag = eval(arg1);

    if(!symbolp(tag))
        error(IMPROPER_ARGS, "throw" , tag);
    if(GET_OPT(tag) == 0) //tag opt has 1~4
    	error(UNDEF_TAG, "throw", tag);
    if(GET_PROP(tag) == 0)
    	error(CTRL_OVERF,"throw",NIL);

    catch_arg = f_progn(arg2);
    i = GET_PROP(tag);
    SET_PROP(tag,i-1);
    ep = catch_env[GET_OPT(tag)-1][i-1]; //restore environment
    longjmp(catch_buf[GET_OPT(tag)-1][i-1],1);
}

int f_tagbody(int arglist){
    int prog[TAGBODY_LEN_MAX],tb_line,end,i;
    
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "tagbody", arglist);

    end = 0;
    while(!nullp(arglist)){
        prog[end] = car(arglist);
        arglist = cdr(arglist);
        end++;
    }

    tb_line = 0;
    while(tb_line < end){
        if(symbolp(prog[tb_line]))
            tb_line++;
        else{
            tagbody_tag = NIL;
            eval(prog[tb_line]);
            tb_line++;
            //when go was evaled
            if(tagbody_tag != NIL){
                for(i=0;i<end;i++){
                    if(tagbody_tag == prog[i]){
                        tagbody_tag = NIL;
                        tb_line = i;
                        break;
                    }
                }
                if (tagbody_tag != NIL) {
                    error(UNDEF_TAG,"tagbody",tagbody_tag);
                } else {
                    continue;
                }
            }
        }
    }

    return(NIL);
}

int f_go(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(!symbolp(arg1))
        error(NOT_SYM, "go", arg1);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "go", arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "go", arglist);

    tagbody_tag = arg1;
    return(T);
}


int f_unwind_protect(int arglist){
    int arg1,args,res;

    arg1 = car(arglist);
    args = cdr(arglist);
    if(nullp(arglist))
        error(WRONG_ARGS, "unwind-protect", arglist);
    if(improperlistp(arglist))
        error(WRONG_ARGS, "unwind-protect", arglist);

    unwind_buf[unwind_pt] = makefunc("",cons(NIL,args)); //make thunk
    unwind_pt++;
    res = eval(arg1);
    if(unwind_pt > 0){
        unwind_pt--;
        while(unwind_pt >= 0){
			apply(unwind_buf[unwind_pt],NIL);
            unwind_pt--;
        }
        unwind_pt = 0;
    }
    return(res);
}


int f_case(int arglist){
    int arg1,arg2,key,res,temp;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(nullp(car(arg2)))
        error(IMPROPER_ARGS, "case", arg2);
    temp = arg2;
    while(!nullp(temp)){
        int temparg1;

        temparg1 = car(temp);
        if(!listp(temparg1))
            error(WRONG_ARGS, "case", temparg1);
        if(car(temparg1) == T && length(temp) != 1)
            error(IMPROPER_ARGS, "case", temparg1);
        if(atomp(car(temparg1)) && car(temparg1) != T)
            error(IMPROPER_ARGS, "case", temparg1);
        temp = cdr(temp);
    }

    res = NIL;
    key = eval(arg1);
    while(arg2 != NIL){
        if(caar(arg2) == T){
            res = f_progn(cdar(arg2));
            break;
        }
        else if(member(key,caar(arg2)) != NIL){
            res = f_progn(cdar(arg2));
            break;
        }
        else{
            arg2 = cdr(arg2);
        }
    }
    return(res);
}

int f_case_using(int arglist){
    int arg1,arg2,arg3,key,fun,res,temp;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);
     if(nullp(car(arg3)))
        error(IMPROPER_ARGS, "case-using", arg3);
    temp = arg3;
    while(!nullp(temp)){
        int temparg1;

        temparg1 = car(temp);
        if(!listp(temparg1))
            error(WRONG_ARGS, "case-using", temparg1);
        if(car(temparg1) == T && length(temp) != 1)
            error(IMPROPER_ARGS, "case-using", temparg1);
        if(atomp(car(temparg1)) && car(temparg1) != T)
            error(IMPROPER_ARGS, "case-using", temparg1);
        temp = cdr(temp);
    }

    res = NIL;
    key = eval(arg2);
    fun = eval(arg1);
    while(arg3 != NIL){
        if(caar(arg3) == T){
            res = f_progn(cdar(arg3));
            break;
        }
        else if(member1(key,caar(arg3),fun) != NIL){
            res = f_progn(cdar(arg3));
            break;
        }
        else{
            arg3 = cdr(arg3);
        }
    }
    return(res);
}


int f_progn(int arglist){
    int res;

    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "progn", arglist);
    res = NIL;
    while(arglist != NIL){
        res = eval(car(arglist));
        arglist = cdr(arglist);
    }
    return(res);
}

int f_defclass(int arglist){
    int arg1,arg2,arg3,arg4,sc,var,val,cl,form,
        initargs;

    arg1 = car(arglist);  //class-name
    arg2 = cadr(arglist); //super-class
    arg3 = caddr(arglist);//slot-spec
    arg4 = cdddr(arglist);//class-opt

    if(!symbolp(arg1))
        error(NOT_SYM, "defclass", arg1);
    if(GET_OPT(arg1) == SYSTEM)
        error(CANT_REDEFINE, "defclass", arg1);
    if(GET_OPT(arg1) == CONSTN)
        error(CANT_MODIFY, "defclass", arg1);
    if(IS_FSUBR(GET_CAR(arg1)))
        error(CANT_MODIFY, "defclass", arg1);
    if((STRING_REF(arg1,0) == '&') || (STRING_REF(arg1,0) == ':'))
        error(CANT_MODIFY, "defclass", arg1);
    if(!listp(arg2))
        error(NOT_LIST, "defclass", arg2);
    if(hassamep(arg2))
        error(IMPROPER_ARGS,"defclass",arg2);
    if(hassysclassp(arg2))
        error(IMPROPER_ARGS,"defclass",arg2);
    if(notexistclassp(arg2))
        error(UNDEF_CLASS,"defclass",arg2);
    if(hascommonp(arg2))
        error(HAS_COMMON_CLASS,"defclass", arg2);
    if(!listp(arg3))
        error(NOT_LIST, "defclass", arg3);
    if(!top_flag && !ignore_topchk)
        error(NOT_TOP_LEVEL, "defclass", arglist);

    sc = arg2;
    if(subclassp(GET_AUX(arg1),cobject))
        redef_flag = true; //flag for check redefinition of class

    var = NIL;
    val = UNDEF;
    initargs = NIL;
    while(!nullp(arg3)){
        int sym,ls,reader,writer,accessor,boundp,initform,initarg;

        reader = writer = accessor = boundp = initform = initarg = NIL;
        if(!listp(car(arg3)))
            arg3 = list1(arg3); // if form=(a :reader a-read) => ((a :reader a-read))
        sym = caar(arg3);
        if((STRING_REF(sym,0) == '&') || (STRING_REF(sym,0) == ':'))
            error(ILLEGAL_FORM, "defclass", sym);
        ls = cdar(arg3);
        if(!listp(car(arg3)))
            error(ILLEGAL_FORM, "defclass", arg3);
        while(!nullp(ls)){
            if(eqp(car(ls),makesym(":READER"))){
                reader = cadr(ls);
                //(if (not (generic-function-p (function* name)))
                //         (defgeneric name (x)))
                //(defmethod name ((x arg1))
                //  (slot-value x 'var))
                //(defmethod name ((x <null>))  for setf syntax
                //     'var)
                //(set-property 1 'reader 'read))
                form = list3(makesym("IF"),
                             list2(makesym("NOT"),list2(makesym("GENERIC-FUNCTION-P"),
                                                       list2(makesym("FUNCTION*"),reader))),
                             list3(makesym("DEFGENERIC"),reader,list1(makesym("x"))));
                eval(form);
                form = list4(makesym("DEFMETHOD"),reader,list1(list2(makesym("x"),arg1)),
                        list3(makesym("SLOT-VALUE"),makesym("x"),list2(makesym("QUOTE"),sym)));
                eval(form);
                form = list4(makesym("DEFMETHOD"),reader,list1(list2(makesym("x"),makesym("<NULL>"))),
                        list2(makesym("QUOTE"),sym));
                eval(form);
                form = list4(makesym("SET-PROPERTY"),
                             makeint(1),
                             list2(makesym("QUOTE"),reader),
                             list2(makesym("QUOTE"),makesym("READ")));
                eval(form);
            }
            else if(eqp(car(ls),makesym(":WRITER"))){
                writer = cadr(ls);
                //(if (not (generic-function-p (function* name)))
                //    (defgeneric name (x y)))
                //(defmethod name (x (y arg1))
                //  (setf (slot-value y 'var) x))
                //(defmethod name ((x <null>))  for setf syntax
                //     'var)
                form = list3(makesym("IF"),
                             list2(makesym("NOT"),list2(makesym("GENERIC-FUNCTION-P"),
                                                       list2(makesym("FUNCTION*"),writer))),
                             list3(makesym("DEFGENERIC"),writer,list2(makesym("x"),list2(makesym("y"),arg1))));
                eval(form);
                form = list4(makesym("DEFMETHOD"),writer,list2(makesym("x"),list2(makesym("y"),arg1)),
                            list3(makesym("SETF"),
                                list3(makesym("SLOT-VALUE"),makesym("y"),list2(makesym("QUOTE"),sym)),
                                    makesym("x")));
                eval(form);
                form = list4(makesym("DEFMETHOD"),writer,list1(list2(makesym("x"),makesym("<NULL>"))),
                        list2(makesym("QUOTE"),sym));
                eval(form);
            }
            else if(eqp(car(ls),makesym(":ACCESSOR"))){
                accessor = cadr(ls);
                //(if (not (generic-function-p (function* name)))
                //    (defgeneric name (x)))
                //(defmethod name ((x arg1))
                //  (slot-value x 'var))
                //(defmethod name ((x <null>))  for setf syntax
                //     'var)
                form = list3(makesym("IF"),
                             list2(makesym("NOT"),list2(makesym("GENERIC-FUNCTION-P"),
                                                       list2(makesym("FUNCTION*"),accessor))),
                             list3(makesym("DEFGENERIC"),accessor,list1(makesym("x"))));
                eval(form);
                form = list4(makesym("DEFMETHOD"),accessor,list1(list2(makesym("x"),arg1)),
                        list3(makesym("SLOT-VALUE"),makesym("x"),list2(makesym("QUOTE"),sym)));
                eval(form);
                form = list4(makesym("DEFMETHOD"),accessor,list1(list2(makesym("x"),makesym("<NULL>"))),
                        list2(makesym("QUOTE"),sym));
                eval(form);
            }
            else if(eqp(car(ls),makesym(":BOUNDP"))){
                boundp = cadr(ls);
                //(if (not (generic-function-p (function* name)))
                //    (defgeneric name (x)))
                //(defmethod name ((x arg1))
                //  (not (dummyp (slot-value x 'var))))
                form = list3(makesym("IF"),
                             list2(makesym("NOT"),list2(makesym("GENERIC-FUNCTION-P"),
                                                       list2(makesym("FUNCTION*"),boundp))),
                             list3(makesym("DEFGENERIC"),boundp,list1(makesym("x"))));
                eval(form);
                form = list4(makesym("DEFMETHOD"),boundp,list1(list2(makesym("x"),arg1)),
                            list2(makesym("NOT"),
                                list2(makesym("DUMMYP"),
                                             list3(makesym("SLOT-VALUE"),makesym("x"),list2(makesym("QUOTE"),sym))
                                             )));
                eval(form);
            }
            else if(eqp(car(ls),makesym(":INITFORM"))){
                initform = eval(cadr(ls));
                val = initform;
            }
            else if(eqp(car(ls),makesym(":INITARG"))){
                initarg = cadr(ls);
            }
            else
                error(ILLEGAL_FORM, "defclass", ls);

            ls = cddr(ls);
        }

        var = cons(cons(caar(arg3),val),var);
        initargs = cons(cons(initarg,sym),initargs);
        arg3 = cdr(arg3);
    }

    while(!nullp(arg4)){

    }
    cl = makeclass(GET_NAME(arg1),sc);
    SET_OPT(cl,USER); //standard-class;
    SET_CDR(cl,var);
    SET_AUX(cl,initargs);
    SET_AUX(arg1,cl);
    return(arg1);
}


int f_defgeneric(int arglist){
    int arg1,arg2,arg3,val;

    arg1 = car(arglist); //func-name
    arg2 = cadr(arglist); //lambda-list
    arg3 = cddr(arglist); //body
    if(!symbolp(arg1))
        error(NOT_SYM, "defgeneric", arg1);
    if(GET_OPT(arg1) == CONSTN)
        error(CANT_MODIFY, "defgeneric", arg1);
    if(IS_FUNC(GET_CAR(arg1)))
        error(CANT_MODIFY, "defgeneric", arg1);
    if(IS_SUBR(GET_CAR(arg1)))
        error(CANT_MODIFY, "defgeneric", arg1);
    if(!listp(arg2))
        error(NOT_LIST, "defgeneric",arg2);


    if(!member(arg1,generic_list))
        generic_list = hcons(arg1,generic_list);

    val = makegeneric(GET_NAME(arg1),arg2,arg3);
    SET_CAR(arg1,val);
    return(arg1);
}

int f_defgeneric_star(int arglist){
    int arg1,arg2,arg3,val;

    arg1 = car(arglist); //func-name
    arg2 = cadr(arglist); //lambda-list
    arg3 = cddr(arglist); //body
    if(!symbolp(arg1))
        error(NOT_SYM, "defgeneric", arg1);
    if(GET_OPT(arg1) == CONSTN)
        error(CANT_MODIFY, "defgeneric", arg1);
    if(IS_FUNC(GET_CAR(arg1)))
        error(CANT_MODIFY, "defgeneric", arg1);
    if(IS_SUBR(GET_CAR(arg1)))
        error(CANT_MODIFY, "defgeneric", arg1);
    if(!listp(arg2))
        error(NOT_LIST, "defgeneric",arg2);

    if(!member(arg1,generic_list))
        generic_list = hcons(arg1,generic_list);

    val = makegeneric_star(arg2,arg3);
    SET_CAR(arg1,val);
    return(arg1);
}

/*
if Generic function, set CDR area method object with insert sorting.
*/
int f_defmethod(int arglist){
    int arg1,arg2,gen;

    arg1 = car(arglist); //method-name
    arg2 = cdr(arglist); //parameter-profile
    if(!(IS_GENERIC(GET_CAR(arg1))))
        error(NOT_FUNC, "defmethod", arg1);

    gen = GET_CAR(arg1);
    insert_method(makemethod(arg2),gen);
    return(arg1);
}

int f_ignore_errors(int arglist){
    int ret;

    ignore_flag = true;
    ret = setjmp(ignore_buf);

    if(ret == 0){
        int res;

        res = f_progn(arglist);
        ignore_flag = false;
        return(res);
    }
    else{
        ignore_flag = false;
        return(NIL);
    }
}

int f_with_open_input_file(int arglist){
    int arg1,arg2,sym,str,val,ep1,res;
    FILE *port;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    sym = car(arg1); // stream-name;
    str = eval(cadr(arg1)); //file-name;
    if(!symbolp(sym))
        error(NOT_SYM, "with-open-input-file", sym);
    if(!stringp(str))
        error(NOT_STR, "with-open-input-file", str);
    port = fopen(GET_NAME(str),"r");
    if(port == NULL) {
        error(CANT_OPEN, "with-open-input-file", str);
        return NIL;
    }
    val = makestream(port,EISL_INPUT);
    ep1 = ep;
    addlexenv(sym,val);
    res = f_progn(arg2);
    fclose(port);
    ep = ep1;
    return(res);
}

int f_with_open_output_file(int arglist){
    int arg1,arg2,sym,str,val,ep1,res;
    FILE *port;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    sym = car(arg1); // stream-name;
    str = eval(cadr(arg1)); //file-name;
    if(!symbolp(sym))
        error(NOT_SYM, "with-open-output-file", sym);
    if(!stringp(str))
        error(NOT_STR, "with-open-output-file", str);
    port = fopen(GET_NAME(str),"w");
    if(port == NULL) {
        error(CANT_OPEN, "with-open-output-file", str);
        return NIL;
    }
    val = makestream(port,EISL_OUTPUT);
    ep1 = ep;
    addlexenv(sym,val);
    res = f_progn(arg2);
    fclose(port);
    ep = ep1;
    return(res);
}

int f_with_open_io_file(int arglist){
    int arg1,arg2,sym,str,val,ep1,res;
    FILE *port;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    sym = car(arg1); // stream-name;
    str = eval(cadr(arg1)); //file-name;
    if(!symbolp(sym))
        error(NOT_SYM, "with-open-io-file", sym);
    if(!stringp(str))
        error(NOT_STR, "with-open-io-file", str);
    port = fopen(GET_NAME(str),"r+");
    if(port == NULL) {
        error(CANT_OPEN, "with-open-io-file", str);
        return NIL;
    }
    val = makestream(port,EISL_OPEN);
    ep1 = ep;
    addlexenv(sym,val);
    res = f_progn(arg2);
    fclose(port);
    ep = ep1;
    return(res);
}

int f_with_standard_input(int arglist){
    int arg1,arg2,stream,save,res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    stream = eval(arg1);
    if(!input_stream_p(stream))
        error(NOT_STREAM, "with-standard-input, stream", stream);

    save = input_stream;
    input_stream = stream;
    res = f_progn(arg2);
    input_stream = save;
    return(res);
}

int f_with_standard_output(int arglist){
    int arg1,arg2,stream,save,res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    stream = eval(arg1);
    if(!output_stream_p(stream))
        error(NOT_STREAM, "with-standard-output, stream", stream);

    save = output_stream;
    output_stream = stream;
    res = f_progn(arg2);
    output_stream = save;
    return(res);
}

int f_with_error_output(int arglist){
    int arg1,arg2,stream,save,res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    stream = eval(arg1);
    if(!output_stream_p(stream))
        error(NOT_STREAM, "with-error-output, stream", stream);

    save = output_stream;
    output_stream = stream;
    res = f_progn(arg2);
    output_stream = save;
    return(res);
}

int f_with_handler(int arglist){
    int arg1,arg2,res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    error_handler = cons(eval(arg1),error_handler);
    res = f_progn(arg2);
    return(res);
}

int f_convert(int arglist){
    int arg1,arg2;
    double x;
    char str[STRSIZE],*e;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(IMPROPER_ARGS, "convert", arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS, "convert", arglist);
    if(!symbolp(arg2))
        error(NOT_SYM, "convert", arg2);
    if(GET_OPT(arg2) != SYSTEM)
        error(NOT_CLASS, "convert", arg2);

    arg1 = eval(arg1);
    switch(GET_TAG(arg1)){
        case INTN:
            if (GET_AUX(arg2) == cinteger){
                return(arg1);
            }
            else if(GET_AUX(arg2) == ccharacter){
                str[0] = GET_INT(arg1);
                str[1] = NUL;
                return(makechar(str));
            }
            else if(GET_AUX(arg2) == cfloat){
                return(exact_to_inexact(arg1));
            }
            else if(GET_AUX(arg2) == cstring){
                snprintf(str, STRSIZE, "%d", GET_INT(arg1));
                return(makestr(str));
            }
            break;
        case LONGN:
            if(GET_AUX(arg2) == cinteger){
                return(arg1);
            }
            else if(GET_AUX(arg2) == cfloat){
                return(exact_to_inexact(arg1));
            }
            else if(GET_AUX(arg2) == cstring){
                #if __linux || __APPLE__ || defined(__OpenBSD__)
                snprintf(str, STRSIZE, "%lld", GET_LONG(arg1));
                #endif
                #if _WIN32
                sprintf(str,"%I64d",GET_LONG(arg1));
                #endif 
                return(makestr(str));
            }
            break;
        case BIGX:
            if(GET_AUX(arg2) == cinteger){
                return(arg2);
            }
            else if(GET_AUX(arg2) == cfloat){
                return(exact_to_inexact(arg1));
            }
            break;
        case CHR:
            if(GET_AUX(arg2) == cinteger){
                return(makeint(STRING_REF(arg1,0)));
            }
            else if(GET_AUX(arg2) == csymbol){
                return(makesym(GET_NAME(arg1)));
            }
            else if(GET_AUX(arg2) == ccharacter){
                return(arg1);
            }
            else if(GET_AUX(arg2) == cstring){
                return(makestr(GET_NAME(arg1)));
            }
            break;
        case FLTN:
            if(GET_AUX(arg2) == cfloat){
                return(arg1);
            }
            else if(GET_AUX(arg2) == cstring){
                x = GET_FLT(arg1);
                if(x - ceil(x) != 0 ||  x >= SMALL_INT_MAX)
                    snprintf(str, STRSIZE, "%0.16g", x);
                else
                    snprintf(str, STRSIZE, "%0.1f", x);
                return(makestr(str));
            }
            break;
        case SYM:
            if(GET_AUX(arg2) == csymbol){
                return(arg1);
            }
            else if(GET_AUX(arg2) == cstring){
                return(makestr(GET_NAME(arg1)));
            }
            else if(nullp(arg1) && GET_AUX(arg2) == cgeneral_vector){
                return(vector(arg1));
            }
            else if(nullp(arg1) && GET_AUX(arg2) == clist){
                return(arg1);
            }
            break;
        case STR:
            if(GET_AUX(arg2) == cstring){
                return(arg1);
            }
            else if(GET_AUX(arg2) == cinteger){
                strncpy(stok.buf, GET_NAME(arg1), BUFSIZE - 1);
                stok.buf[BUFSIZE - 1] = '\0';

                if(bignumtoken(stok.buf)){
                    return(makebigx(stok.buf));
                }
                else if(inttoken(stok.buf)){
                    return(makeint(strtol(stok.buf,&e,10)));
                }
                else if(bintoken(stok.buf)){
                    return(makeint((int)strtol(stok.buf,&e,2)));
                }
                else if(octtoken(stok.buf)){
                    return(makeint((int)strtol(stok.buf,&e,8)));
                }
                else if(dectoken(stok.buf)){
                    return(makeint((int)strtol(stok.buf,&e,10)));
                }
                else if(hextoken(stok.buf)){
                    return(makeint((int)strtol(stok.buf,&e,16)));
                }
                break;
            }
            else if(GET_AUX(arg2) == cfloat){
                if(flttoken(GET_NAME(arg1)))
                    return(makeflt(atof(GET_NAME(arg1))));
            }
            else if(GET_AUX(arg2) == csymbol){
                return(makesym(GET_NAME(arg1)));
            }
            else if(GET_AUX(arg2) == cgeneral_vector){
                return(string_to_vector(arg1));
            }
            else if(GET_AUX(arg2) == clist){
                return(string_to_list(arg1));
            }
            break;
        case LIS:
            if(GET_AUX(arg2) == clist){
                return(arg1);
            }
            else if(GET_AUX(arg2) == cgeneral_vector){
                return(vector(arg1));
            }
            break;
        case VEC:
            if(GET_AUX(arg2) == cgeneral_vector){
                return(arg1);
            }
            else if(GET_AUX(arg2) == clist){
                return(vector_to_list(arg1));
            }
            break;
    }
    error(OUT_OF_DOMAIN,"convert",arg1);
    return(UNDEF);
}

int f_the(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(IMPROPER_ARGS,"the",arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS,"the",arglist);

    if(GET_AUX(arg1) != NIL)
        return(eval(arg2));
    else
        error(NOT_CLASS,"the",arg1);

    return(UNDEF);
}

int f_assure(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(IMPROPER_ARGS,"assure",arglist);
    if(improperlistp(arglist))
        error(IMPROPER_ARGS,"assure",arglist);

    arg2 = eval(arg2);
    if(GET_AUX(arg1) == GET_AUX(arg2))
        return(arg2);
    else if(subclassp(GET_AUX(arg2),GET_AUX(arg1)))
        return(arg2);
    else
        error(CANT_ASSURE,"assure",arg2);

    return(UNDEF);
}

double getETime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec*1e-6;
}



int f_time(int arglist){
    int arg1;
    double st,en;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "time", arglist);

    st = getETime();
    eval(arg1);
    en = getETime();
    printf("Elapsed Time(second)=%.6f\n",en-st);
    return(UNDEF);
}

int f_trace(int arglist){

    if(nullp(arglist)){
        return(trace_list);
    }
    else{
        while(!nullp(arglist)){
            if(!symbolp(car(arglist)))
                error(NOT_SYM,"trace",car(arglist));
            if(!member(car(arglist),trace_list)){
                SET_TR(car(arglist),1);
                trace_list= cons(car(arglist),trace_list);
            }
            arglist = cdr(arglist);
        }
        return(T);
    }
}

int f_untrace(int arglist){

    if(nullp(arglist)){
        while(!nullp(trace_list)){
            SET_TR(car(trace_list),0); // reset trace tag of symbol
            SET_TR(GET_CAR(car(trace_list)),0);// reset trace nest level
            trace_list = cdr(trace_list);
        }
    }
    else{
        while(!nullp(arglist)){
            if(!symbolp(car(arglist)))
                error(NOT_SYM,"untrace",car(arglist));
            SET_TR(car(arglist),0);
            SET_TR(GET_CAR(car(arglist)),0);
            arglist = cdr(arglist);
        }
        trace_list = remove_list(trace_list,arglist);
    }
    return(T);
}

int f_defmodule(int arglist){
    int arg1,arg2,exports;

    arg1 = car(arglist); //module name
    arg2 = cdr(arglist); //body
    exports = NIL;

    while(!nullp(arg2)){
        int sexp;
        
        sexp = car(arg2);
        if(symbolp(car(sexp)) && HAS_NAME(car(sexp),"DEFPUBLIC"))
            exports = cons(cadr(sexp),exports);

        eval(substitute(car(arg2),arg1,exports));
        arg2 = cdr(arg2);
    }
    return(T);
}


int substitute(int addr, int module, int fname){
    int temp;

    if(IS_NIL(addr) || IS_T(addr))
        return(addr);
    else if(numberp(addr))
        return(addr);
    else if(vectorp(addr))
        return(addr);
    else if(arrayp(addr))
        return(addr);
    else if(farrayp(addr))
        return(addr);
    else if(stringp(addr))
        return(addr);
    else if(charp(addr))
        return(addr);
    else if(class_symbol_p(addr))
        return(addr);
    else if(symbolp(addr)){
        if(!member(addr,fname) && !eqp(addr,makesym(":REST")) && !eqp(addr,makesym("&REST")))
            return(substitute1(addr,module));
        else
            return(addr);
    }
    else if(listp(addr)){
        if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"QUOTE"))){
            temp = cadr(addr);
            if(listp(temp) && symbolp(car(temp)) &&(HAS_NAME(car(temp),"UNQUOTE")))
                return(cons(car(addr),substitute(cdr(addr),module,fname)));
            else
                return(addr);
        }
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"QUASI-QUOTE")))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"UNQUOTE")))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"UNQUOTE-SPLICING")))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));    
        else if(subrp(car(addr)))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"DEFPUBLIC")))
            return(cons(makesym("DEFUN"),cons(cadr(addr),substitute(cddr(addr),module,fname))));
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"DEFUN")))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),":METHOD")))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"CASE")))
            return(cons(car(addr),cons(substitute(cadr(addr),module,fname),substitute_case(cddr(addr),module,fname))));
        else if((symbolp(car(addr))) &&(HAS_NAME(car(addr),"CASE-USING")))
            return(cons(car(addr),cons(substitute(cadr(addr),module,fname),substitute_case(cddr(addr),module,fname))));
        else if(fsubrp(car(addr)))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else if(macrop(car(addr)))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else if(genericp(car(addr)))
            return(cons(car(addr),substitute(cdr(addr),module,fname)));
        else
            return(cons(substitute(car(addr),module,fname),substitute(cdr(addr),module,fname)));
        
    }
    return(T);
}

int substitute1(int x, int module){
    char str[SYMSIZE];

    snprintf(str, SYMSIZE, "%s::%s", GET_NAME(module), GET_NAME(x));
    return(makesym(str));
}


int substitute_case(int addr, int module, int fname){
    int bodies,newbodies;

    bodies = addr;
    newbodies = NIL;

    while(!nullp(bodies)){
        int body, newbody;
        
        body = car(bodies);
        newbody = cons(car(body),substitute(cdr(body),module,fname));
        newbodies = cons(newbody,newbodies);

        bodies = cdr(bodies);
    }
    newbodies = reverse(newbodies);
    return(newbodies);
}
