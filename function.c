
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <setjmp.h>
#include <math.h>
#include <float.h>
#include <time.h>
#if __linux
#include <dlfcn.h>
#endif
#if _WIN32
#include <windows.h>
#endif
#include "eisl.h"

#if _WIN32
extern HMODULE loadeddll;
#endif

void initsubr(void){
    //constant
    bindconst("*PI*",makeflt(3.141592653589793));
    bindconst("*MOST-POSITIVE-FLOAT*",makeflt(DBL_MAX));
    bindconst("*MOST-NEGATIVE-FLOAT*",makeflt(-DBL_MAX));

    //function
    defsubr("-",f_minus);
    defsubr("*",f_mult);
    defsubr("/=",f_notnumeqp);
    defsubr("+",f_plus);
    defsubr("<",f_smaller);
    defsubr("<=",f_eqsmaller);
    defsubr("=",f_numeqp);
    defsubr(">",f_greater);
    defsubr(">=",f_eqgreater);
    defsubr("ABS",f_abs);
    defsubr("APPEND",f_append);
    defsubr("APPLY",f_apply);
    defsubr("AREF",f_aref);
    defsubr("ARITHMETIC-ERROR-OPERANDS",f_arithmetic_error_operands);
    defsubr("ARITHMETIC-ERROR-OPERATION",f_arithmetic_error_operation);
    defsubr("ARRAY-DIMENSIONS",f_array_dimensions);
    defsubr("ASSOC",f_assoc);
    defsubr("ATAN",f_atan);
    defsubr("ATAN2",f_atan2);
    defsubr("ATANH",f_atanh);
    defsubr("ATOM",f_atomp);
    defsubr("BASIC-ARRAY-P",f_basic_array_p);
    defsubr("BASIC-ARRAY*-P",f_basic_array_star_p);
    defsubr("BASIC-VECTOR-P",f_basic_vector_p);
    defsubr("CALL-NEXT-METHOD",f_call_next_method);
    defsubr("CAR",f_car);
    defsubr("CDR",f_cdr);
    defsubr("CEILING",f_ceiling);
    defsubr("CERROR",f_cerror);
    defsubr("CHAR-INDEX",f_char_index);
    defsubr("CHAR/=",f_char_noteqp);
    defsubr("CHAR<",f_char_smallerp);
    defsubr("CHAR<=",f_char_eqsmallerp);
    defsubr("CHAR=",f_char_eqp);
    defsubr("CHAR>",f_char_greaterp);
    defsubr("CHAR>=",f_char_eqgreaterp);
    defsubr("CHARACTERP",f_characterp);
    defsubr("CLASS-OF",f_class_of);
    defsubr("CLOSE",f_close);
    defsubr("CONDITION-CONTINUABLE",f_condition_continuable);
    defsubr("CONS",f_cons);
    defsubr("CONSP",f_consp);
    defsubr("CONSTINUE-CONDITION",f_continue_condition);
    defsubr("COS",f_cos);
    defsubr("COSH",f_cosh);
    defsubr("CREATE-ARRAY",f_create_array);
    defsubr("CREATE-LIST",f_create_list);
    defsubr("CREATE-STRING-INPUT-STREAM",f_create_string_input_stream);
    defsubr("CREATE-STRING-OUTPUT-STREAM",f_create_string_output_stream);
    defsubr("CREATE-STRING",f_create_string);
    defsubr("CREATE-VECTOR",f_create_vector);
    defsubr("CREATE*",f_create_star);
    defsubr("DIV",f_div);
    defsubr("DOMAIN-ERROR-OBJECT",f_domain_error_object);
    defsubr("DOMAIN-ERROR-EXPECTED-CLASS",f_domain_error_expected_class);
    defsubr("DUMMYP",f_dummyp);
    defsubr("ELT",f_elt);
    defsubr("EQ",f_eq);
    defsubr("EQL",f_eql);
    defsubr("EQUAL",f_equal);
    defsubr("ERROR-OUTPUT",f_error_output);
    defsubr("ERROR",f_error);
    defsubr("EVAL",f_eval);
    defsubr("EXP",f_exp);
    defsubr("EXPT",f_expt);
    defsubr("FILE-LENGTH",f_file_length);
    defsubr("FILE-POSITION",f_file_position);
    defsubr("FINISH-OUTPUT",f_finish_output);
    defsubr("FLOAT",f_float);
    defsubr("FLOATP",f_floatp);
    defsubr("FLOOR",f_floor);
    defsubr("FORMAT-CHAR",f_format_char);
    defsubr("FORMAT-FRESH-LINE",f_format_fresh_line);
    defsubr("FORMAT-FLOAT",f_format_float);
    defsubr("FORMAT-INTEGER",f_format_integer);
    defsubr("FORMAT-OBJECT",f_format_object);
    defsubr("FORMAT-TAB",f_format_tab);
    defsubr("FORMAT",f_format);
    defsubr("FUNCALL",f_funcall);
    defsubr("FUNCTIONP",f_functionp);
    defsubr("GAREF",f_garef);
    defsubr("GBC",f_gbc);
    defsubr("GCD",f_gcd);
    defsubr("GENERAL-ARRAY*-P",f_general_array_star_p);
    defsubr("GENERAL-VECTOR-P",f_general_vector_p);
    defsubr("GENERIC-FUNCTION-P",f_generic_function_p);
    defsubr("GENSYM",f_gensym);
    defsubr("GET-INTERNAM-RUN-TIME",f_get_internal_run_time);
    defsubr("GET-OUTPUT-STREAM-STRING",f_get_output_stream_string);
    defsubr("GET-UNIVERSAL-TIME",f_get_universal_time);
    defsubr("HDMP",f_heapdump);
    defsubr("IDENTITY",f_identity);
    defsubr("INITIALIZE-OBJECT*",f_initialize_object_star);
    defsubr("INPUT-STREAM-P",f_input_stream_p);
    defsubr("INSTANCEP",f_instancep);
    defsubr("INTEGERP",f_integerp);
    defsubr("INTERNAL-TIME-UNITS-PER-SECOND internal",f_internal_time_units_per_second);
    defsubr("ISQRT",f_isqrt);
    defsubr("LCM",f_lcm);
    defsubr("LENGTH",f_length);
    defsubr("LIST",f_list);
    defsubr("LISTP",f_listp);
    defsubr("LOAD",f_load);
    defsubr("LOG",f_log);
    defsubr("MAP-INTO",f_map_into);
    defsubr("MAPC",f_mapc);
    defsubr("MAPCAR",f_mapcar);
    defsubr("MAPCAN",f_mapcan);
    defsubr("MAPCON",f_mapcon);
    defsubr("MAPL",f_mapl);
    defsubr("MAPLIST",f_maplist);
    defsubr("MAX",f_max);
    defsubr("MEMBER",f_member);
    defsubr("MIN",f_min);
    defsubr("MOD",f_mod);
    defsubr("NEXT-METHOD-P",f_next_method_p);
    defsubr("NOT",f_not);
    defsubr("NREVERSE",f_nreverse);
    defsubr("NULL",f_nullp);
    defsubr("NUMBERP",f_numberp);
    defsubr("OPEN-INPUT-FILE",f_open_input_file);
    defsubr("OPEN-IO-FILE",f_open_io_file);
    defsubr("OPEN-OUTPUT-FILE",f_open_output_file);
    defsubr("OPEN-STREAM-P",f_open_stream_p);
    defsubr("OUTPUT-STREAM-P",f_output_stream_p);
    defsubr("PARSE-ERROR-STRING",f_parse_error_string);
    defsubr("PARSE-ERROR-EXPECTED-CLASS",f_parse_error_expected_class);
    defsubr("PARSE-NUMBER",f_parse_number);
    defsubr("PREVIEW-CHAR",f_preview_char);
    defsubr("PRIN1",f_prin1);
    defsubr("PRINT",f_print);
    defsubr("PROBE-FILE",f_probe_file);
    defsubr("PROPERTY",f_property);
    defsubr("QUIT",f_quit);
    defsubr("QUOTIENT",f_quotient);
    defsubr("READ-BYTE",f_read_byte);
    defsubr("READ-CHAR",f_read_char);
    defsubr("READ-LINE",f_read_line);
    defsubr("READ",f_read);
    defsubr("RECIPROCAL",f_reciprocal);
    defsubr("REMOVE-PROPERTY",f_remove_property);
    defsubr("REVERSE",f_reverse);
    defsubr("ROUND",f_round);
    defsubr("SET-AREF",f_set_aref);
    defsubr("SET-CAR",f_set_car);
    defsubr("SET-CDR",f_set_cdr);
    defsubr("SET-ELT",f_set_elt);
    defsubr("SET-FILE-POSITION",f_set_file_position);
    defsubr("SET-GAREF",f_set_garef);
    defsubr("SET-PROPERTY",f_set_property);
    defsubr("SET-SLOT-VALUE",f_set_slot_value);
    defsubr("SIGNAL-CONDITION",f_signal_condition);
    defsubr("SIMPLE-ERROR-FORMAT-ARGUMENTS",f_simple_error_format_arguments);
    defsubr("SIMPLE-ERROR-FORMAT-STRING",f_simple_error_format_string);
    defsubr("SIN",f_sin);
    defsubr("SINH",f_sinh);
    defsubr("SLOT-VALUE",f_slot_value);
    defsubr("SQRT",f_sqrt);
    defsubr("STANDARD-INPUT",f_standard_input);
    defsubr("STANDARD-OUTPUT",f_standard_output);
    defsubr("STREAM-ERROR-STREAM",f_stream_error_stream);
    defsubr("STREAMP",f_streamp);
    defsubr("STREAM-READY-P",f_stream_ready_p);
    defsubr("STRING-APPEND",f_string_append);
    defsubr("STRING-INDEX",f_string_index);
    defsubr("STRING/=",f_string_noteqp);
    defsubr("STRING<",f_string_smallerp);
    defsubr("STRING<=",f_string_eqsmallerp);
    defsubr("STRING=",f_string_eqp);
    defsubr("STRING>",f_string_greaterp);
    defsubr("STRING>=",f_string_eqgreaterp);
    defsubr("STRINGP",f_stringp);
    defsubr("SUBCLASSP",f_subclassp);
    defsubr("SUBSEQ",f_subseq);
    defsubr("SYMBOLP",f_symbolp);
    defsubr("TAN",f_tan);
    defsubr("TANH",f_tanh);
    defsubr("TRUNCATE",f_truncate);
    defsubr("UNDEFINED-ENTITY-NAME",f_undefined_entity_name);
    defsubr("UNDEFINED-ENTITY-NAMESPACE",f_undefined_entity_namespace);
    defsubr("VECTOR",f_vector);
    defsubr("WRITE-BYTE",f_write_byte);
}

#if __linux
typedef int (*fn0)();
typedef void (*tfunc)(char*, int(*func)(int));

void dynamic_link(int x){
    char str[256] = {"./"};
    void* hmod;
    int (*init_f0)(int x, tfunc y);
    int (*init_f1)(int x, tfunc y);
    int (*init_f2)(int x, tfunc y);
    int (*init_f3)(int x, tfunc y);
    int (*init_f4)(int x, tfunc y);
    int (*init_f5)(int x, tfunc y);
    int (*init_f6)(int x, tfunc y);
    int (*init_f7)(int x, tfunc y);
    int (*init_f8)(int x, tfunc y);
    void (*init_deftfunc)(tfunc x);
    void (*init_tfunctions)(void);
    void (*init_declare)(void);

    if(strstr(GET_NAME(x),"/"))
        strcpy(str,GET_NAME(x));
    else
        strcat(str,GET_NAME(x));

    hmod = dlopen(str, RTLD_LAZY);

    if(hmod == NULL)
        error(ILLEGAL_ARGS, "load", x);

    init_f0 = dlsym(hmod, "init0");
    init_f1 = dlsym(hmod, "init1");
    init_f2 = dlsym(hmod, "init2");
    init_f3 = dlsym(hmod, "init3");
    init_f4 = dlsym(hmod, "init4");
    init_f5 = dlsym(hmod, "init5");
    init_f6 = dlsym(hmod, "init6");
    init_f7 = dlsym(hmod, "init7");
    init_f8 = dlsym(hmod, "init8");
    init_deftfunc = dlsym(hmod, "init_deftfunc");
    init_tfunctions = dlsym(hmod, "init_tfunctions");
    init_declare = dlsym(hmod, "init_declare");
#endif

#if _WIN32
typedef void (*tfunc)(char*, int(*func)(int));                        
typedef void (*p_f0)(int, tfunc);
typedef void (*p_f1)(int, tfunc);
typedef void (*p_f2)(int, tfunc);
typedef void (*p_f3)(int, tfunc);
typedef void (*p_f4)(int, tfunc);
typedef void (*p_f5)(int, tfunc);
typedef void (*p_f6)(int, tfunc);
typedef void (*p_f7)(int, tfunc);
typedef void (*p_f8)(int, tfunc);
typedef void (*p_def)(tfunc);
typedef void (*p_init)(void);
typedef void (*p_declare)(void);

void dynamic_link(int x){
	HMODULE hmod;

    hmod = LoadLibrary((LPCSTR)(GET_NAME(x)));
    if(hmod == NULL)
    	error(ILLEGAL_ARGS,"LOAD",x);
    loadeddll = hmod;
	  p_f0 init_f0 = (p_f0)GetProcAddress(hmod, (LPCSTR)"init0");
    p_f1 init_f1 = (p_f1)GetProcAddress(hmod, (LPCSTR)"init1");
    p_f2 init_f2 = (p_f2)GetProcAddress(hmod, (LPCSTR)"init2");
    p_f3 init_f3 = (p_f3)GetProcAddress(hmod, (LPCSTR)"init3");
    p_f4 init_f4 = (p_f4)GetProcAddress(hmod, (LPCSTR)"init4");
    p_f5 init_f5 = (p_f5)GetProcAddress(hmod, (LPCSTR)"init5");
    p_f6 init_f6 = (p_f6)GetProcAddress(hmod, (LPCSTR)"init6");
    p_f7 init_f7 = (p_f7)GetProcAddress(hmod, (LPCSTR)"init7");
    p_f8 init_f8 = (p_f8)GetProcAddress(hmod, (LPCSTR)"init8");
    p_def init_deftfunc = (p_def)GetProcAddress(hmod, (LPCSTR)"init_deftfunc");
    p_init init_tfunctions = (p_init)GetProcAddress(hmod, (LPCSTR)"init_tfunctions");
    p_declare init_declare = (p_declare)GetProcAddress(hmod, (LPCSTR)"init_declare");

#endif

    //argument-0 type
    init_f0(0,(tfunc)checkgbc);
    init_f0(1,(tfunc)gbc);
    init_f0(2,(tfunc)freshcell);
    init_f0(3,(tfunc)freecell);
    init_f0(10,(tfunc)shelterpop);
    init_f0(11,(tfunc)pop);
    init_f0(12,(tfunc)get_dynpt);

    //argument-1 type
    init_f1(0,(tfunc)car);
    init_f1(1,(tfunc)cdr);
    init_f1(2,(tfunc)cadr);
    init_f1(3,(tfunc)caddr);
    init_f1(4,(tfunc)caar);
    init_f1(5,(tfunc)cadar);
    init_f1(6,(tfunc)list1);
    init_f1(7,(tfunc)eval);
    init_f1(8,(tfunc)get_aux);
    init_f1(9,(tfunc)fast_length);
    init_f1(10,(tfunc)subrp);
    init_f1(11,(tfunc)fsubrp);
    init_f1(12,(tfunc)functionp);
    init_f1(13,(tfunc)macrop);
    init_f1(14,(tfunc)integerp);
    init_f1(15,(tfunc)longnump);
    init_f1(16,(tfunc)bignump);
    init_f1(20,(tfunc)get_int);
    init_f1(21,(tfunc)makeint);
    init_f1(22,(tfunc)makeintlong);
    init_f1(23,(tfunc)vector);
    init_f1(24,(tfunc)fast_car);
    init_f1(25,(tfunc)fast_cdr);
    init_f1(30,(tfunc)findenv);
    init_f1(31,(tfunc)finddyn);
    init_f1(40,(tfunc)shelterpush);
    init_f1(41,(tfunc)push);
    init_f1(42,(tfunc)get_opt);
    init_f1(43,(tfunc)get_prop);
    init_f1(44,(tfunc)set_dynpt);
    init_f1(45,(tfunc)set_catch_symbols);

    //argument-2 type
    init_f2(0,(tfunc)cons);
    init_f2(1,(tfunc)nth);
    init_f2(2,(tfunc)set_car);
    init_f2(3,(tfunc)set_cdr);
    init_f2(4,(tfunc)set_aux);
    init_f2(5,(tfunc)set_opt);
    init_f2(6,(tfunc)callsubr);
    init_f2(7,(tfunc)list2);
    init_f2(8,(tfunc)nth_cdr);
    init_f2(9,(tfunc)apply);
    init_f2(10,(tfunc)plus);
    init_f2(11,(tfunc)minus);
    init_f2(12,(tfunc)mult);
    init_f2(13,(tfunc)divide);
    init_f2(14,(tfunc)s_remainder);
    init_f2(15,(tfunc)quotient);
    init_f2(16,(tfunc)eqp);
    init_f2(17,(tfunc)eqlp);
    init_f2(18,(tfunc)numeqp);
    init_f2(19,(tfunc)smallerp);
    init_f2(20,(tfunc)eqsmallerp);
    init_f2(21,(tfunc)greaterp);
    init_f2(22,(tfunc)eqgreaterp);
    init_f2(23,(tfunc)member);
    init_f2(30,(tfunc)convert);
    init_f2(31,(tfunc)array);
    init_f2(32,(tfunc)setdynenv);
    init_f2(33,(tfunc)adddynenv);
    init_f2(34,(tfunc)set_dynamic);
    init_f2(35,(tfunc)set_prop);
    init_f2(36,(tfunc)adaptp);


    //argument-1 string type
    init_f3(0,(tfunc)makestr);
    init_f3(1,(tfunc)makesym);
    init_f3(2,(tfunc)makechar);
    init_f3(3,(tfunc)makestrflt);
    init_f3(4,(tfunc)makebigx);

    //argument-1 long long int type
    init_f4(0,(tfunc)get_long);

    //argument-3 type
    init_f5(0,(tfunc)string_set);
    init_f5(1,(tfunc)array_set);
    init_f5(2,(tfunc)member1);

    //string output type
    init_f6(0,(tfunc)get_name);

    //float output type
    init_f7(0,(tfunc)get_flt);

    //float input type
    init_f8(0,(tfunc)makedoubleflt);

    init_deftfunc((tfunc)defsubr);
    init_tfunctions();
    init_declare();

    return;
}




void initgeneric(void){
    int lamlis,body;

    lamlis = list3(makesym("x"),makesym(":REST"),makesym("y"));
    body = list3(makesym(":METHOD"),list3(makesym("x"),makesym(":REST"),makesym("y")),
                list4(makesym("LET"),list1(list2(makesym("obj"),list3(makesym("CREATE*"),makesym("x"),NIL))),
                                     list3(makesym("INITIALIZE-OBJECT"),makesym("obj"),makesym("y")),
                                     makesym("obj")));
    eval(list4(makesym("DEFGENERIC*"),makesym("CREATE"),lamlis,body));
    /*
    (defgeneric create(x :rest y)
        (:method (x y)
           (let ((obj (create* x '())))
              (initialize-object obj y)
              obj)))

    */

    lamlis = list2(makesym("x"),makesym("y"));
    body = list3(makesym(":METHOD"),list2(makesym("x"),makesym("y")),
                 list3(makesym("INITIALIZE-OBJECT*"),makesym("x"),makesym("y")));
    eval(list4(makesym("DEFGENERIC*"),makesym("INITIALIZE-OBJECT"),lamlis,body));
    /*
    (defgeneric initialize-object(x y)
        (:method (x y)
           (initialize-object* x y)))
    */

    lamlis = list2(makesym("x"),makesym("y"));
    body = NIL;
    eval(list4(makesym("DEFGENERIC*"),makesym("REPORT-CONDITION"),lamlis,body));
    /*
    (defgeneric report-condition (x y))
    */
}


//arithmetic function
int f_plus(int arglist){
    int arg,res;

    if(nullp(arglist))
        res = makeint(0);
    else{
        res = car(arglist);
        arglist = cdr(arglist);
    }
    while(!(IS_NIL(arglist))){
        arg = car(arglist);
        if(!numberp(arg) && !vectorp(arg) && !arrayp(arg))
            error(NOT_NUM, "+", arg);
        arglist = cdr(arglist);
        res = plus(res,arg);
    }
    return(res);
}

int f_minus(int arglist){
    int arg,res,n;

    res = car(arglist);
    if((n=length(arglist)) == 0)
        error(WRONG_ARGS,"-",arglist);
    if(n==1)
        return(mult(res,makeint(-1)));

    arglist = cdr(arglist);
    while(!(IS_NIL(arglist))){
        arg = car(arglist);
        if(!numberp(arg) && !vectorp(arg) && !arrayp(arg))
            error(NOT_NUM, "-", arg);
        arglist = cdr(arglist);
        res = minus(res,arg);
    }
    return(res);
}

int f_mult(int arglist){
    int arg,res;

    if(nullp(arglist))
        res = makeint(1);
    else{
        res = car(arglist);
        arglist = cdr(arglist);
    }
    while(!(IS_NIL(arglist))){
        arg = car(arglist);
        if(!numberp(arg) && !arrayp(arg) && !vectorp(arg))
            error(NOT_NUM, "*", arg);
        arglist = cdr(arglist);
        res = mult(res,arg);
    }
    return(res);
}

int f_quotient(int arglist){
    int arg,res;

    res = car(arglist);
    arglist = cdr(arglist);
    while(!(IS_NIL(arglist))){
        arg = car(arglist);
        if(!numberp(arg))
            error(NOT_NUM, "quotient", arg);
        arglist = cdr(arglist);
        res = divide(res,arg);
    }
    return(res);
}

int f_smaller(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "<", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "<", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "<", arg2);

    if(smallerp(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_eqsmaller(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "<=", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "<=", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "<=", arg2);

    if(eqsmallerp(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_greater(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, ">", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, ">", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, ">", arg2);

    if(greaterp(arg1,arg2))
        return(T);
    else
        return(NIL);
}


int f_eqgreater(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, ">=", arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, ">=", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, ">=", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, ">=", arg2);

    if(eqgreaterp(arg1,arg2))
        return(T);
    else
        return(NIL);
}
int f_sin(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "sin", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "sin", arg1);
    val = sin(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_cos(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "cos", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "cos", arg1);
    val = cos(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_tan(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "tan", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "tan", arg1);
    val = tan(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_atan(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "atan", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "atan", arg1);
    val = atan(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_sinh(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "sinh", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "sinh", arg1);
    val = sinh(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_cosh(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "cosh", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "cosh", arg1);
    val = cosh(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_tanh(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "tanh", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "tanh", arg1);
    val = tanh(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_atanh(int arglist){
    int arg1;
    double val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "atanh", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "atanh", arg1);
    val = atanh(GET_FLT(exact_to_inexact(arg1)));
    return(makeflt(val));
}

int f_floor(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "floor", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "floor", arg1);


    if(floatp(arg1))
        return(makeflt(floor(GET_FLT(arg1))));
    else
        return(arg1);
}

int f_ceiling(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "ceiling", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "ceiling", arg1);

    if(floatp(arg1))
        return(makeflt(ceil(GET_FLT(arg1))));
    else
        return(arg1);
}

int f_truncate(int arglist){
    int arg1;
    double x;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "truncate", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "truncate", arg1);

    if(floatp(arg1)){
        x = GET_FLT(arg1);
        if(x >= 0)
            return(makeflt(floor(x)));
        else
            return(makeflt(ceil(x)));
    }
    else
        return(arg1);
}


int f_round(int arglist){
    int arg1;
    double x,f,c;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "round", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "round", arg1);

    if(floatp(arg1)){
        x = GET_FLT(arg1);
        f = floor(x);
        c = ceil(x);
        if(x == (f+c)/2)
            if(fmod(f,2.0) == 0.0)
                x = f;
            else
                x = c;
        else
            x = round(x);

        return(makeflt(x));
        }
    else
        return(arg1);
}

int f_gcd(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "gcd", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "gcd", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "gcd", arg2);

    return(gcd(arg1,arg2));
}

int f_lcm(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "lcm", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "lcm", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "lcm", arg2);

    return(lcm(arg1,arg2));
}

int f_max(int arglist){
    int arg1,res;

    res = car(arglist);
    if(!numberp(res))
        error(NOT_NUM, "max", res);
    arglist = cdr(arglist);
    while(!nullp(arglist)){
        arg1 = car(arglist);
        if(!numberp(arg1))
            error(NOT_NUM, "max", arg1);
        if(greaterp(arg1,res))
            res = arg1;
        arglist = cdr(arglist);
    }
    return(res);
}

int f_min(int arglist){
    int arg1,res;

    res = car(arglist);
    if(!numberp(res))
        error(NOT_NUM, "min", res);
    arglist = cdr(arglist);
    while(!nullp(arglist)){
        arg1 = car(arglist);
        if(!numberp(arg1))
            error(NOT_NUM, "min", arg1);
        if(smallerp(arg1,res))
            res = arg1;
        arglist = cdr(arglist);
    }
    return(res);

}

int f_float(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "float", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "float", arg1);
    return(exact_to_inexact(arg1));
}

int f_floatp(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "floatp", arglist);
    if(IS_FLOAT(arg))
        return(T);
    else
        return(NIL);
}


int f_div(int arglist){
    int arg1,arg2,q,r;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "div", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "div", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "div", arg2);
    if(zerop(arg2))
        error(DIV_ZERO, "div",arglist);

    q = quotient(arg1,arg2);
    r = s_remainder(arg1,arg2);
    if(zerop(r))
        return(q);
    else
        if(positivep(arg1) && negativep(arg2))
            return(minus(q,makeint(1)));
        else if(negativep(arg1) && positivep(arg2))
            return(minus(q,makeint(1)));
        else
            return(q);
}

int f_integerp(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "integerp", arglist);
    if(math_integerp(arg))
        return(T);
    else
        return(NIL);
}

int f_abs(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "abs", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "abs", arg1);
    return(absolute(arg1));
}

int f_mod(int arglist){
    int arg1,arg2,div;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "mod", arglist);
    if(!integerp(arg1) && !longnump(arg1) && !bignump(arg1))
        error(NOT_INT, "mod", arg1);
    if(!integerp(arg2) && !longnump(arg2) && !bignump(arg2))
        error(NOT_INT, "mod", arg2);

    div = f_div(arglist);
    return(minus(arg1,mult(arg2,div)));

}

int f_exp(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "exp", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "exp", arg1);
    return(makeflt(exp(GET_FLT(exact_to_inexact(arg1)))));
}

int f_log(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "log", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "log", arg1);
    if(!positivep(arg1))
        error(NOT_POSITIVE, "log", arglist);

    return(makeflt(log(GET_FLT(exact_to_inexact(arg1)))));
}

int f_expt(int arglist){
    int arg1,arg2;
    double x,y,z;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "expt", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "expt", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "expt", arg2);

    if((integerp(arg1) || longnump(arg1) || bignump(arg1)) && integerp(arg2) && GET_INT(arg2) == 0)
        return(makeint(1));

    if((integerp(arg1) || longnump(arg1) || bignump(arg1)) && (integerp(arg2) && GET_INT(arg2) > 0))
        return(expt(arg1,GET_INT(arg2)));

    if((integerp(arg1) || floatp(arg1)) &&
       (integerp(arg2) || floatp(arg2))){

        arg1 = exact_to_inexact(arg1);
        arg2 = exact_to_inexact(arg2);
        x = GET_FLT(arg1);
        y = GET_FLT(arg2);
        z = pow(x,y);
        return(makeflt(z));
    }
    if(integerp(arg1) && (integerp(arg2) || longnump(arg2) || bignump(arg2))){
        if(GET_INT(arg1) == 1)
            return(arg1);
        else if(GET_INT(arg1) == 0)
            return(arg1);
        else if(GET_INT(arg1) == -1){
            if(zerop(s_remainder(arg2,makeint(2))))
                return(makeint(1));
            else
                return(arg1);
        }
    }
    if(floatp(arg1) && (longnump(arg2) || bignump(arg2))){
        if(GET_FLT(arg1) == 1.0)
            return(arg1);
        else if(GET_FLT(arg1) == 0.0)
            return(arg1);
        else if(GET_FLT(arg1) == -1.0){
            if(zerop(s_remainder(arg2,makeint(2))))
                return(makeflt(1.0));
            else
                return(arg1);
        }
    }
    if(longnump(arg1) && integerp(arg2)){
        if(GET_INT(arg2) == 1){
            x = GET_FLT(exact_to_inexact(arg1));
            y = x;
            return(makeflt(y));
        }
        else if(GET_INT(arg2) == 2){
            x = GET_FLT(exact_to_inexact(arg1));
            y = x*x;
            return(makeflt(y));
        }
        else if(GET_INT(arg2) == -1){
            x = GET_FLT(exact_to_inexact(arg1));
            y = 1.0 / x;
            return(makeflt(y));
        }
        else if(GET_INT(arg2) == -2){
            x = GET_FLT(exact_to_inexact(arg1));
            y = 1.0 / (x*x);
            return(makeflt(y));
        }
    }
    if(longnump(arg1) && floatp(arg2)){
        if(GET_FLT(arg2) == 0.0){
            return(makeflt(1.0));
        }
        else if(GET_FLT(arg2) == 1.0){
            x = GET_FLT(exact_to_inexact(arg1));
            y = x;
            return(makeflt(y));
        }
        else if(GET_FLT(arg2) == 2.0){
            x = GET_FLT(exact_to_inexact(arg1));
            y = x*x;
            return(makeflt(y));
        }
        else if(GET_FLT(arg2) == -1.0){
            x = GET_FLT(exact_to_inexact(arg1));
            y = 1.0 / x;
            return(makeflt(y));
        }
        else if(GET_FLT(arg2) == -2.0){
            x = GET_FLT(exact_to_inexact(arg1));
            y = 1.0 / (x*x);
            return(makeflt(y));
        }
    }
    error(OUT_OF_RANGE,"expt",arglist);
    return(UNDEF);
}

int expt(int x, int y){
    int res,p;

    res = makeint(1);
    p = x;
    while(y > 0){
        if((y % 2) ==0){
            p = mult(p,p);
            y = y / 2;
        }
        else{
            res = mult(res,p);
            y = y -1;
        }
    }
    return(res);
}


int f_sqrt(int arglist){
    int arg1;
    double x;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "sqrt", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "sqrt", arg1);
    if(negativep(arg1))
        error(OUT_OF_RANGE, "sqrt", arg1);
    x = sqrt(GET_FLT(exact_to_inexact(arg1)));
    if(ceil(x) == floor(x) && x < BIGNUM_BASE)
        return(makeint((int)x));
    else
        return(makeflt(x));
}


int f_isqrt(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "isqrt", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "isqrt", arg1);
    if(negativep(arg1))
        error(OUT_OF_RANGE, "isqrt", arg1);
    return(isqrt(arg1));
}

int f_atan2(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "atan2", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "atan2", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "atan2", arg2);
    return(angle(arg1,arg2));
}

int f_reciprocal(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "resiprocal", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "resiprocal", arg1);
    return(divide(makeint(1),arg1));
}

int f_numeqp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "=", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "=", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "=", arg2);

    if(numeqp(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_notnumeqp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "/=", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "/=", arg1);
    if(!numberp(arg2))
        error(NOT_NUM, "/=", arg2);

    if(numeqp(arg1,arg2))
        return(NIL);
    else
        return(T);
}


//list function

int f_car(int arglist){
    int arg;

    arg = car(arglist);
    if(!(IS_LIST(arg)))
        error(NOT_CONS, "car", arg);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "car", arglist);
    return(car(arg));
}

int f_cdr(int arglist){
    int arg;

    arg = car(arglist);
    if(!(IS_LIST(arg)))
        error(NOT_CONS, "cdr", arg);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "cdr", arglist);
    return(cdr(arg));
}

int f_cons(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "cons", arglist);
    return(cons(arg1,arg2));
}

int f_eq(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "eq", arglist);
    if(eqp(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_eql(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "eql", arglist);
    if(eqlp(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_equal(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "equal", arglist);
    if(equalp(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_not(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "not", arglist);
    if(IS_NIL(arg))
        return(T);
    else
        return(NIL);
}

int f_nullp(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "not", arglist);
    if(nullp(arg))
        return(T);
    else
        return(NIL);
}

int f_atomp(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "atom", arglist);
    if(atomp(arg))
        return(T);
    else
        return(NIL);
}

int f_functionp(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "functionp", arglist);
    if(IS_FUNC(arg) || IS_SUBR(arg) || IS_GENERIC(arg))
        return(T);
    else
        return(NIL);
}

int f_consp(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "consp", arglist);
    if(IS_LIST(arg))
        return(T);
    else
        return(NIL);
}


int f_list(int arglist){
    return(list(arglist));
}

int f_append(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(!listp(arg1) && nullp(arglist))
        error(NOT_CONS, "append", arg1);
    if(length(arg1) >= fc){
        shelterpush(arglist);
        gbc();
        shelterpop();
    }
    if(nullp(arglist))
        return(NIL);
    else if(nullp(cdr(arglist)))
        return(car(arglist));
    else if(nullp(arg1))
        return(f_append(cdr(arglist)));
    else
        return(append(car(arglist),f_append(cdr(arglist))));
}


int f_symbolp(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "symbolp", arglist);
    if(symbolp(arg1))
        return(T);
    else
        return(NIL);
}

int f_numberp(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "numberp", arglist);
    if(numberp(arg1))
        return(T);
    else
        return(NIL);
}

int f_listp(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "listp", arglist);
    if(listp(arg1))
        return(T);
    else
        return(NIL);
}


int f_member(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    return(member(arg1,arg2));
}

int f_assoc(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "assoc", arglist);
    if(!listp(arg2))
        error(NOT_LIST, "assoc", arg2);
    if(!assoclistp(arg2))
        error(ILLEGAL_ARGS, "assoc", arg2);

    return(assoc(arg1,arg2));
}

int f_mapcar(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "mapcar", arg1);
    return(mapcar(arg1,arg2));
}

int f_mapc(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "mapc", arg1);

    return(mapc(arg1,arg2));
}

int f_maplist(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "maplist", arg1);

    return(maplist(arg1,arg2));
}

int f_mapl(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "mapl", arg1);

    return(mapl(arg1,arg2));
}

int f_mapcon(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "mapcon", arg1);

    return(mapcon(arg1,arg2));
}

int f_mapcan(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "mapcan", arg1);
    return(mapcan(arg1,arg2));
}


int f_map_into(int arglist){
    int arg1,arg2 ,arg3,val,res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);

    val = mapcar(arg2,arg3);
    res = arg1;
    while(!nullp(val)){
        SET_CAR(arg1,GET_CAR(val));
        arg1 = cdr(arg1);
        val = cdr(val);
    }
    return(res);
}


int f_reverse(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "reverse", arglist);
    if(!listp(arg1))
        error(NOT_LIST, "reverse", arg1);
    return(reverse(arg1));
}

int f_nreverse(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "nreverse", arglist);
    if(!listp(arg1))
        error(NOT_LIST, "nreverse", arg1);
    return(nreverse(arg1));
}

int f_create_list(int arglist){
    int arg1,arg2,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if((n=length(arglist)) != 1 && n != 2)
        error(WRONG_ARGS, "create-list", arglist);
    if(longnump(arg1) || bignump(arg1))
        error(MALLOC_OVERF, "create-list", arg1);
    if(!integerp(arg1))
        error(NOT_INT, "create-list", arg1);
    if(GET_INT(arg1) < 0)
        error(NOT_POSITIVE, "create-list", arg1);
    if(nullp(arg2))
        arg2 = UNDEF;
    return(create_list(GET_INT(arg1),arg2));
}

int f_property(int arglist){
    int arg1,arg2,arg3,res,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) != 2 && n != 3)
        error(ILLEGAL_ARGS,"property",arglist);
    if(!symbolp(arg1))
        error(NOT_SYM,"property",arg1);

    res = assoc(arg2,GET_PROP(arg1));
    if(res == 0)
        return(arg3);
    else
        return(cdr(res));
}

int f_set_property(int arglist){
    int arg1,arg2,arg3,res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    res = assoc(arg3,GET_PROP(arg2));
    if(nullp(res))
        SET_PROP(arg2,cons(cons(arg3,arg1),GET_PROP(arg2)));
    else
        SET_CDR(res,arg1);
    return(arg1);
}

int f_remove_property(int arglist){
    int arg1,arg2,val,res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS,"remove-property",arglist);
    if(!symbolp(arg1))
        error(NOT_SYM,"remove-property",arg1);

    val = assoc(arg2,GET_PROP(arg1));
    if(nullp(val))
        return(NIL);
    else{
        res = cdr(val);
        SET_CDR(val,NIL);
        return(res);
    }
}

int f_gensym(int arglist){
    int res;
    char str1[SYMSIZE],str2[10];

    strcpy(str1,"#:G");
    sprintf(str2, "%d",genint);
    genint++;
    strcat(str1,str2);
    res = makesym(str1);
    return(res);
}

int f_length(int arglist){
    int arg;

    arg = car(arglist);
    if(!nullp(cdr(arglist)))
        error(WRONG_ARGS, "length", arglist);
    if(!listp(arg) && !vectorp(arg) && !stringp(arg))
        error(ILLEGAL_ARGS, "length", arg);

    if(listp(arg))
        return(makeint(length(arg)));
    else if(vectorp(arg))
        return(makeint(vector_length(arg)));
    else
        return(makeint(string_length(arg)));

}


int f_set_car(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "set-car", arglist);
    if(!(IS_LIST(arg2)))
        error(NOT_CONS, "set-car", arg2);
    SET_CAR(arg2,arg1);
    return(arg1);
}

int f_set_cdr(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "set-cdr", arglist);
    if(!(IS_LIST(arg2)))
        error(NOT_CONS, "set-cdr", arg2);
    SET_CDR(arg2,arg1);
    return(arg1);
}



//input and output

int f_read(int arglist){
    int arg1,arg2,arg3,save,n,res;
    #if __linux
    int save1;
    #endif

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) > 3)
        error(WRONG_ARGS, "read", arglist);
    if(n>0 && !input_stream_p(arg1))
        error(NOT_IN_STREAM, "read", arg1);

    #if __linux
    save1 = repl_flag;
    repl_flag = 0;
    #endif
    if(n==0)
        res = sread();
    else if(n==1){
        save = input_stream;
        input_stream = arg1;
        res = sread();
        input_stream = save;
        if(res==FEND){
           #if __linux
            repl_flag = save1;
            #endif
            error(END_STREAM, "read", NIL);
        }

    }
    else{
        save = input_stream;
        input_stream = arg1;
        res =sread();
        input_stream = save;
        if(res==FEND){
        	#if __linux
            repl_flag = save1;
            #endif
            if(nullp(arg2) && n == 2)
                return(arg2);
            else if(nullp(arg2) && n == 3)
                return(arg3);
            else
                error(END_STREAM, "read", NIL);
        }
    }
    #if __linux
    repl_flag = save1;
    #endif
    return(res);
}

int f_read_char(int arglist){
    int arg1,arg2,arg3,save,n,res;
    char buf[CHARSIZE];
    #if __linux
    int save1;
    #endif

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) > 3)
        error(WRONG_ARGS, "read-char", arglist);
    if(n>0 && !input_stream_p(arg1))
        error(NOT_IN_STREAM, "read-char", arg1);

    #if __linux
    save1 = repl_flag;
    repl_flag = 0;
    #endif
    if(n==0){
        buf[0] = readc();
        buf[1] = NUL;
        res = makechar(buf);
    }
    else if(n==1){
        save = input_stream;
        input_stream = arg1;
        buf[0] = readc();
        buf[1] = NUL;
        if(buf[0] == EOF){
        	#if __linux
            repl_flag = save1;
            #endif
            error(END_STREAM, "read-char", NIL);
        }
        input_stream = save;
        res = makechar(buf);
    }
    else{
        save = input_stream;
        input_stream = arg1;
        buf[0] = readc();
        buf[1] = NUL;
        input_stream = save;
        if(buf[0] == EOF){
        	#if __linux
            repl_flag = save1;
            #endif
            if(nullp(arg2) && n == 2)
                return(arg2);
            else if(nullp(arg2) && n == 3)
                return(arg3);
            else
                error(END_STREAM, "read-char", NIL);
        }
        res = makechar(buf);
        if(res==FEND && arg2==NIL)
            res = arg3;
        else
            res = NIL;
    }
    #if __linux
    repl_flag = save1;
    #endif
    return(res);
}

int f_read_byte(int arglist){
    int arg1,arg2,arg3,save,n;
    unsigned char res;
    #if __linux
    int save1;
    #endif

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) > 3)
        error(WRONG_ARGS, "read-byte", arglist);
    if(n>0 && !input_stream_p(arg1))
        error(NOT_IN_STREAM, "read-byte", arg1);

    #if __linux
    save1 = repl_flag;
    repl_flag = 0;
    #endif
    if(n==0){
        res = readc();
    }
    else if(n==1){
        save = input_stream;
        input_stream = arg1;
        res = readc();
        if(res == EOF){
        	#if __linux
            repl_flag = save1;
            #endif
            error(END_STREAM, "read-byte", NIL);
        }
        input_stream = save;
    }
    else{
        save = input_stream;
        input_stream = arg1;
        res = readc();
        input_stream = save;
        if(res==EOF){
        	#if __linux
            repl_flag = save1;
            #endif
            if(nullp(arg2) && n == 2)
                return(arg2);
            else if(nullp(arg2) && n == 3)
                return(arg3);
            else
                error(END_STREAM, "read-byte", NIL);
        }
    }
    #if __linux
    repl_flag = save1;
    #endif
    return(makeint(res));
}



int f_preview_char(int arglist){
    int arg1,arg2,arg3,save,n,res;
    char buf[CHARSIZE];

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) > 3)
        error(WRONG_ARGS, "preview-char", arglist);
    if(n>0 && !input_stream_p(arg1))
        error(NOT_IN_STREAM, "preview-char", arg1);

    if(n==0){
        buf[0] = readc();
        buf[1] = NUL;
        unreadc(arg1);
        res = makechar(buf);
    }
    else if(n==1){
        save = input_stream;
        input_stream = arg1;
        buf[0] = readc();
        buf[1] = NUL;
        unreadc(arg1);
        if(buf[0] == EOF)
            error(END_STREAM, "preview-char", NIL);
        input_stream = save;
        res = makechar(buf);
    }
    else{
        save = input_stream;
        input_stream = arg1;
        buf[0] = readc();
        buf[1] = NUL;
        input_stream = save;
        if(buf[0] == EOF){
            if(nullp(arg2) && n == 2)
                return(arg2);
            else if(nullp(arg2) && n == 3)
                return(arg3);
            else
                error(END_STREAM, "preview-char", NIL);
        }
        unreadc(arg1);
        res = makechar(buf);
        if(res==FEND && arg2==NIL)
            res = arg3;
    }
    return(res);
}

int f_read_line(int arglist){
    int arg1,arg2,arg3,n,pos,save,res;
    char buf[STRSIZE],c;
    #if __linux
    int save1;
    #endif

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) > 3)
        error(WRONG_ARGS, "read-line", arglist);
    if(n>0 && !input_stream_p(arg1))
        error(NOT_IN_STREAM, "read-line", arg1);

	#if __linux
    save1 = repl_flag;
    repl_flag = 0;
    #endif
    if(n==0){
        pos = 0;
        c = readc();
        while(c != EOL){
            buf[pos] = c;
            pos++;
            c = readc();
        }
        buf[pos] = NUL;
        res = makestr(buf);
    }
    else if(n==1){
        pos = 0;
        save = input_stream;
        input_stream = arg1;
        c = readc();
        if(c == EOF){
        	#if __linux
            repl_flag = save1;
            #endif
            error(END_STREAM, "read-line", NIL);
        }
        while(c != EOL && c != EOF){
            buf[pos] = c;
            pos++;
            c = readc();
        }
        buf[pos] = NUL;
        input_stream = save;
        res = makestr(buf);
    }
    else{
        pos = 0;
        save = input_stream;
        input_stream = arg1;
        c = readc();
        if(c == EOF){
        	#if __linux
            repl_flag = save1;
            #endif
            if(nullp(arg2) && n == 2){
                input_stream = save;
                return(arg2);
            }
            else if(nullp(arg2) && n == 3){
                input_stream = save;
                return(arg3);
            }
            else
                error(END_STREAM, "read-line", NIL);
        }

        while(c != EOL && c != EOF){
            buf[pos] = c;
            pos++;
            c = readc();
        }
        buf[pos] = NUL;
        input_stream = save;
        res = makestr(buf);
        if(res==FEND && arg2==NIL)
            res = arg3;
    }
    #if __linux
    repl_flag = save1;
    #endif
    return(res);
}

int f_load(int arglist){
    int arg1,sexp,save,n;
    char str[STRSIZE];

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "load", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "load", arg1);

    //object file ex "foo.o"
    n = strlen(GET_NAME(arg1));
    strcpy(str,GET_NAME(arg1));
    if(str[n-1] == 'o' && str[n-2] == '.'){
        dynamic_link(arg1);
        return(T);
    }

    //text file
    save = input_stream;
    input_stream = makestream(fopen(GET_NAME(arg1),"r"),EISL_INPUT);

    if(GET_PORT(input_stream) == NULL){
        input_stream = save;
        error(CANT_OPEN, "load", arg1);
    }
    open_flag = 1;
    line = 1;
    column = 0;
    while(1){
        sexp = sread();
        if(sexp == FEND)
            break;
        top_flag = 1;
        eval(sexp);
    }
    open_flag = 0;
    fclose(GET_PORT(input_stream));
    input_stream = save;
    if(redef_flag)
        redef_generic();
    return(T);
}


int f_print(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "print", arglist);
    print(arg1);
    printf("\n");
    return(NIL);
}

int f_prin1(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "prin1", arglist);
    print(arg1);
    return(T);
}


int f_standard_input(int arglist){
    if(!nullp(arglist))
        error(WRONG_ARGS, "standard-input", arglist);
    return(standard_input);
}

int f_standard_output(int arglist){
    if(!nullp(arglist))
        error(WRONG_ARGS, "standard-output", arglist);
    return(standard_output);
}

int f_error_output(int arglist){
    if(!nullp(arglist))
        error(WRONG_ARGS, "error-output", arglist);
    return(standard_error);
}

int f_streamp(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "streamp", arglist);
    if(streamp(arg))
        return(T);
    else
        return(NIL);
}

int f_open_stream_p(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "open-stream-p", arglist);
    if(arg == standard_input || arg == standard_output || arg == standard_error)
        return(T);
    else if(GET_OPT(arg) == EISL_OPEN)
        return(T);
    else
        return(NIL);
}

int f_input_stream_p(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "input-stream-p", arglist);
    if(streamp(arg) && GET_CDR(arg)==EISL_INPUT)
        return(T);
    else
        return(NIL);
}

int f_output_stream_p(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "output-stream-p", arglist);
    if(streamp(arg) && GET_CDR(arg)==EISL_OUTPUT)
        return(T);
    else
        return(NIL);
}

int f_stream_ready_p(int arglist){
    int arg1,save;
    char c;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"stream-ready-p",arglist);
    if(!streamp(arg1))
        error(NOT_STREAM,"stream-ready-p",arg1);

    if(input_stream_p(arg1)){
        save = input_stream;
        input_stream = arg1;
        c = readc();
        if(c == EOF){
            input_stream = save;
            return(NIL);
        }
        else{
            unreadc(c);
            input_stream = save;
            return(T);
        }
    }
    else
        return(T);
}

//evaluation function

int f_eval(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "eval", arglist);
    return(eval(arg1));
}

int f_apply(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "apply", arg1);
    if(!listp(last(arg2)))
        error(NOT_LIST, "apply", last(arg2));

    return(apply(arg1,bind_args(arg2)));
}

int bind_args(int x){
    if(nullp(cdr(x)))
        return(car(x));
    else
        return(cons(car(x),bind_args(cdr(x))));
}

int f_funcall(int arglist){
    int arg1,arg2,res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "funcall", arg1);
    res = apply(arg1,arg2);
    return(res);
}



//character function


int f_characterp(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "characterp", arglist);
    if(charp(arg1))
        return(T);
    else
        return(NIL);
}



int f_char_eqp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "char=", arglist);
    if(!charp(arg1))
        error(NOT_CHAR, "char=", arg1);
    if(!charp(arg2))
        error(NOT_CHAR, "char=", arg2);


    if(SAME_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_char_noteqp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "char/=", arglist);
    if(!charp(arg1))
        error(NOT_CHAR, "char/=", arg1);
    if(!charp(arg2))
        error(NOT_CHAR, "char/=", arg2);


    if(SAME_NAME(arg1,arg2))
        return(NIL);
    else
        return(T);
}

int f_char_smallerp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "char<", arglist);
    if(!charp(arg1))
        error(NOT_CHAR, "char<", arg1);
    if(!charp(arg2))
        error(NOT_CHAR, "char<", arg2);


    if(SMALLER_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_char_eqsmallerp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "char<=", arglist);
    if(!charp(arg1))
        error(NOT_CHAR, "char<=", arg1);
    if(!charp(arg2))
        error(NOT_CHAR, "char<=", arg2);

    if(SMALLER_NAME(arg1,arg2) || SAME_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_char_greaterp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "char>", arglist);
    if(!charp(arg1))
        error(NOT_CHAR, "char>", arg1);
    if(!charp(arg2))
        error(NOT_CHAR, "char>", arg2);

    if(GREATER_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_char_eqgreaterp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "char>=", arglist);
    if(!charp(arg1))
        error(NOT_CHAR, "char>=", arg1);
    if(!charp(arg2))
        error(NOT_CHAR, "char>=", arg2);

    if(GREATER_NAME(arg1,arg2) || SAME_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_char_index(int arglist){
    int arg1,arg2,arg3,n,i,j,len;
    char c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) != 2 && n != 3)
        error(WRONG_ARGS, "char-index", arglist);
    if(!charp(arg1))
        error(NOT_CHAR, "char-index", arg1);
    if(!stringp(arg2))
        error(NOT_STR, "char-index", arg2);
    if(n == 3 && !integerp(arg3))
        error(NOT_INT, "char-index", arg3);
    if(n == 3 && GET_INT(arg3) < 0)
        error(NOT_POSITIVE, "char-index", arg3);
    if(n == 3 && GET_INT(arg3) >= string_length(arg2))
        error(ILLEGAL_ARGS, "char-index", arg3);

    if(string_length(arg2) == 0)
        return(NIL);

    if(arg3 != NIL)
        j = GET_INT(arg3);
    else
        j = 0;

    c = GET_CHAR(arg1);
    len = strlen(GET_NAME(arg2));
    for(i=j;i<len;i++){
        if(STRING_REF(arg2,i)==c)
            break;
    }
    if(i<len)
        return(makeint(i));
    else
        return(NIL);
}


//string function
int f_stringp(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "stringp", arglist);
    if(stringp(arg1))
        return(T);
    else
        return(NIL);
}

int f_string_eqp(int arglist){
    int arg1,arg2;

    if(length(arglist) != 2)
        error(WRONG_ARGS, "string=", arglist);
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(!stringp(arg1))
            error(NOT_STR, "string=", arg1);
    if(!stringp(arg2))
            error(NOT_STR, "string=", arg2);
    if(SAME_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_string_noteqp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "string=", arglist);
    if(!stringp(arg1))
            error(NOT_STR, "string=", arg1);
    if(!stringp(arg2))
            error(NOT_STR, "string=", arg2);
    if(SAME_NAME(arg1,arg2))
        return(NIL);
    else
        return(T);
}



int f_elt(int arglist){
    int arg1,arg2;
    char str[CHARSIZE];

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "elt", arglist);
    if(!integerp(arg2))
        error(NOT_INT, "elt", arg2);

    if(listp(arg1)){
        if(length(arg1) <= GET_INT(arg2) || GET_INT(arg2) < 0)
            error(OUT_OF_RANGE, "elt", arg2);
        return(listref(arg1,GET_INT(arg2)));
    }
    else if(vectorp(arg1)){
        if(vector_length(arg1) <= GET_INT(arg2) || GET_INT(arg2) < 0)
            error(OUT_OF_RANGE, "elt", arg2);
        return(vector_ref(arg1,GET_INT(arg2)));
    }
    else if(stringp(arg1)){
        if(strlen(GET_NAME(arg1)) <= GET_INT(arg2) || GET_INT(arg2) < 0)
            error(OUT_OF_RANGE, "elt", arg2);
        str[0] = GET_NAME_ELT(arg1,GET_INT(arg2));
        str[1] = NUL;
        return(makechar(str));
    }
    return(NIL);
}


int f_set_elt(int arglist){
    int arg1,arg2,arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if(length(arglist) != 3)
        error(WRONG_ARGS, "set-elt", arglist);
    if(!integerp(arg3))
        error(NOT_INT, "set-elt", arg3);

    if(listp(arg2))
        SET_CAR(listref1(arg2,GET_INT(arg3)),arg1);
    else if(vectorp(arg2))
        SET_VEC_ELT(arg2,GET_INT(arg3),arg1);
    else if(stringp(arg2))
        STRING_SET(arg2,GET_INT(arg3),GET_CHAR(arg1));

    return(arg1);
}



int f_string_smallerp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "string<", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "string<", arg1);
    if(!stringp(arg2))
        error(NOT_STR, "string<", arg2);

    if(SMALLER_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_string_greaterp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "string>", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "string>", arg1);
    if(!stringp(arg2))
        error(NOT_STR, "string>", arg2);

    if(GREATER_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);
}

int f_string_eqgreaterp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "string>=", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "string>=", arg1);
    if(!stringp(arg2))
        error(NOT_STR, "string>=", arg2);

    if(GREATER_NAME(arg1,arg2) || SAME_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);

}


int f_string_eqsmallerp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "string<=", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "string<=", arg1);
    if(!stringp(arg2))
        error(NOT_STR, "string<=", arg2);

    if(SMALLER_NAME(arg1,arg2) || SAME_NAME(arg1,arg2))
        return(T);
    else
        return(NIL);

}

int f_string_append(int arglist){
    int arg1,arg2;
    char str1[STRSIZE],str2[STRSIZE];

    if(nullp(arglist))
        return(makestr(""));
    else if(nullp(cdr(arglist)))
        return(car(arglist));

    arg1 = car(arglist);
    if(!stringp(arg1))
        error(NOT_STR, "string-append", arg1);
    arglist = cdr(arglist);
    str1[0] = NUL;
    str2[0] = NUL;
    strcpy(str1,GET_NAME(arg1));
    while(!nullp(arglist)){
        arg2 = car(arglist);
        if(!stringp(arg2))
            error(NOT_STR, "string-append", arg2);
        arglist = cdr(arglist);

        strcpy(str2,GET_NAME(arg2));
        strcat(str1,str2);
        strcpy(str2,str1);
    }
    return(makestr(str2));
}


int f_string_index(int arglist){
    int arg1,arg2,arg3,n,i,j,k,len1,len2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if((n=length(arglist)) != 2 && n != 3)
        error(WRONG_ARGS,"string-index", arglist);
    if(!stringp(arg1))
        error(NOT_STR,"string-index",arg1);
    if(!stringp(arg2))
        error(NOT_STR,"string-index",arg2);
    if(n==3 && !integerp(arg3))
        error(NOT_INT, "string-index",arg3);
    if(n == 3 && GET_INT(arg3) < 0)
        error(NOT_POSITIVE, "string-index", arg3);
    if(n == 3 && GET_INT(arg3) >= string_length(arg2))
        error(ILLEGAL_ARGS, "string-index", arg3);

    if(string_length(arg2) == 0)
        return(NIL);

    len1=strlen(GET_NAME(arg1));
    len2=strlen(GET_NAME(arg2));
    if(n==3)
        j = GET_INT(arg3);
    else
        j = 0;

    for(i=j;i<len2;i++)
        for(k=0;k<len1+1;k++)
            if(STRING_REF(arg1,k)==NUL)
                return(makeint(i));
            else if(STRING_REF(arg1,k)!=STRING_REF(arg2,i+k))
                break;


    return(NIL);
}


//vector and array

int f_aref(int arglist){
    int arg1,arg2,n;

    arg1 = car(arglist);
    arg2 = cdr(arglist);

    if(length(arglist) < 1)
        error(WRONG_ARGS,"aref",arglist);
    if(!vectorp(arg1) && !arrayp(arg1) && !stringp(arg1))
        error(ILLEGAL_ARGS, "aref", arg1);
    if(vectorp(arg1) && !inrangep(arg2,list1(makeint(vector_length(arg1)))))
        error(OUT_OF_RANGE,"aref",arg2);
    if(arrayp(arg1) && !inrangep(arg2,array_length(arg1)))
        error(OUT_OF_RANGE,"aref",arg2);
    if(stringp(arg1) &&
       ((n=GET_INT(car(arg2))) >= string_length(arg1) || n < 0))
        error(OUT_OF_RANGE,"aref",arg2);

    if(stringp(arg1))
        return(string_ref(arg1,car(arg2)));
    else
        return(array_ref(arg1,arg2));
}

int inrangep(int x, int y){

    while(!nullp(x)){
        if(longnump(car(x) || bignump(car(x))))
            return(0);
        else if(eqgreaterp(car(x),car(y)) || GET_INT(car(x))<0)
            return(0);
        else if(nullp(y))
            return(0);

        x = cdr(x);
        y = cdr(y);
    }
    if(nullp(y))
        return(1);
    else
        return(0);
}

int f_garef(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if(GET_AUX(arg1) != cgeneral_vector && GET_AUX(arg1) != cgeneral_array_star)
        error(NOT_VECARR, "garef", arg1);
    if(vectorp(arg1) && !inrangep(arg2,list1(makeint(vector_length(arg1)))))
        error(OUT_OF_RANGE,"garef",arg2);
    if(arrayp(arg1) && !inrangep(arg2,array_length(arg1)))
        error(OUT_OF_RANGE,"garef",arg2);

    return(array_ref(arg1,arg2));
}


int f_set_aref(int arglist){
    int arg1,arg2,arg3,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);
    if(!vectorp(arg2) && !arrayp(arg2) &&!stringp(arg2))
        error(ILLEGAL_ARGS, "set-aref", arg2);
    if(vectorp(arg2) && !inrangep(arg3,list1(makeint(vector_length(arg2)))))
        error(OUT_OF_RANGE,"set-aref",arg3);
    if(arrayp(arg2) && !inrangep(arg3,array_length(arg2)))
        error(OUT_OF_RANGE,"set-aref",arg3);
    if(stringp(arg2) &&
       ((n=GET_INT(car(arg3))) >= string_length(arg2) || n < 0))
        error(OUT_OF_RANGE,"set-aref",arg3);

    if(stringp(arg2))
        string_set(arg2,car(arg3),arg1);
    else
        array_set(arg2,arg3,arg1);
    return(arg1);
}

int f_set_garef(int arglist){
    int arg1,arg2,arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = cddr(arglist);
    if(GET_AUX(arg2) != cgeneral_vector && GET_AUX(arg2) != cgeneral_array_star)
        error(NOT_VECARR, "set-garef", arg2);
    if(vectorp(arg2) && !inrangep(arg3,list1(makeint(vector_length(arg2)))))
        error(OUT_OF_RANGE,"set-garef",arg3);
    if(arrayp(arg2) && !inrangep(arg3,array_length(arg2)))
        error(OUT_OF_RANGE,"set-garef",arg3);

    array_set(arg2,arg3,arg1);
    return(arg1);
}

int f_basic_vector_p(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "basic-vector-p", arglist);

    if(!symbolp(arg1) && GET_AUX(arg1) == cbasic_vector)
        return(T);
    else if(!symbolp(arg1) && subclassp(GET_AUX(arg1),cbasic_vector))
        return(T);
    else
        return(NIL);

    return(UNDEF);
}

int f_general_vector_p(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "general-vector-p", arglist);

    if(!symbolp(arg1) && GET_AUX(arg1) == cgeneral_vector)
        return(T);
    else if(!symbolp(arg1) && subclassp(GET_AUX(arg1),cgeneral_vector))
        return(T);
    else
        return(NIL);

    return(UNDEF);
}


int f_basic_array_p(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "basic-array-p", arglist);

    if(!symbolp(arg1) && GET_AUX(arg1) == cbasic_array)
        return(T);
    else if(!symbolp(arg1) && subclassp(GET_AUX(arg1),cbasic_array))
        return(T);
    else
        return(NIL);

    return(UNDEF);
}

int f_basic_array_star_p(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "basic-array-p", arglist);

    if(!symbolp(arg1) && GET_AUX(arg1) == cbasic_array_star)
        return(T);
    else if(!symbolp(arg1) && subclassp(GET_AUX(arg1),cbasic_array_star))
        return(T);
    else
        return(NIL);

    return(UNDEF);
}

int f_general_array_star_p(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "general-array*-p", arglist);

    if(!symbolp(arg1) && GET_AUX(arg1) == cgeneral_array_star)
        return(T);
    else if(!symbolp(arg1) && subclassp(GET_AUX(arg1),cgeneral_array_star))
        return(T);
    else
        return(NIL);

    return(UNDEF);
}


int f_array_dimensions(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "array-dimensions", arglist);
    if(!vectorp(arg1) && !arrayp(arg1) && !stringp(arg1))
        error(NOT_ARR, "array-dimensions", arg1);

    if(vectorp(arg1))
        return(list1(makeint(GET_CDR(arg1))));
    else if(arrayp(arg1))
        return(GET_CDR(arg1));
    else
        return(list1(makeint(strlen(GET_NAME(arg1)))));
}



int f_vector(int arglist){
    return(vector(arglist));
}


int f_create_star(int arglist){
    int arg1,arg2;

    arg1 = car(arglist); //class
    arg2 = cadr(arglist); //initargs,vals
    if(length(arglist) != 2)
        error(WRONG_ARGS,"create",arglist);
    if(!(IS_CLASS(arg1)))
        error(NOT_CLASS, "create", arg1);
    if(GET_OPT(arg1) == SYSTEM)
        error(CANT_CREATE, "create", arg1);

    return(makeinstance(arg1,arg2));
}

int f_slot_value(int arglist){
    int arg1,arg2,val;

    arg1 = car(arglist);  //instance
    arg2 = cadr(arglist); //var
    if(length(arglist) != 2)
        error(WRONG_ARGS, "slot-value", arglist);
    if(!(IS_INSTANCE(arg1)))
        error(NOT_INSTANCE, "slot-value", arg1);
    if(!symbolp(arg2))
        error(NOT_SYM, "slot-value", arg2);

    val = assoc(arg2,GET_CDR(arg1));
    if(nullp(val))
        error(UNDEF_VAR, "slot-value", arg2);

    return(cdr(val));
}

int f_set_slot_value(int arglist){
    int arg1,arg2,arg3,val;

    arg1 = car(arglist);  //value to set
    arg2 = cadr(arglist);  //instance
    arg3 = caddr(arglist); //var
    if(length(arglist) != 3)
        error(WRONG_ARGS, "set-slot-value", arglist);
    if(!(IS_INSTANCE(arg2)))
        error(NOT_INSTANCE, "set-slot-value", arg1);
    if(!symbolp(arg3))
        error(NOT_SYM, "set-slot-value", arg2);

    val = assoc(arg3,GET_CDR(arg2));
    if(nullp(val))
        error(UNDEF_VAR, "set-slot-value", arg3);

    set_cdr(val,arg1);
    return(arg1);
}


int f_format(int arglist){
    int arg1,arg2,args,i,save,n,quote_flag;
    char str[STRSIZE],c;

    arg1 = car(arglist);  //output-stream
    arg2 = cadr(arglist); //format-string
    args = cddr(arglist); //data
    quote_flag = 0;
    if(!output_stream_p(arg1))
        error(NOT_OUT_STREAM, "format", arg1);
    if(!stringp(arg2))
        error(NOT_STR, "format", arg2);

    save = output_stream;
    output_stream = arg1;
    strcpy(str,GET_NAME(arg2));
    i = 0;
    c = str[i];
    while(c != 0){
        if(c == '~' && quote_flag == 0){
            i++;
            c = str[i];
            if(c == 'A'){
                f_format_object(list3(arg1,car(args),NIL));
                args = cdr(args);
            }
            else if(c == 'B'){
                f_format_integer(list3(arg1,car(args),makeint(2)));
                args = cdr(args);
            }
            else if(c == 'C'){
                f_format_char(list2(arg1,car(args)));
                args = cdr(args);
            }
            else if(c == 'D'){
                f_format_integer(list3(arg1,car(args),makeint(10)));
                args = cdr(args);
            }
            else if(c == 'G'){
                f_format_float(list2(arg1,car(args)));
                args = cdr(args);
            }
            else if(c == 'O'){
                f_format_integer(list3(arg1,car(args),makeint(8)));
                args = cdr(args);
            }
            else if(c == 'S'){
                f_format_object(list3(arg1,car(args),T));
                args = cdr(args);
            }
            else if(c == 'X'){
                f_format_integer(list3(arg1,car(args),makeint(16)));
                args = cdr(args);
            }
            else if(isdigit(c)){
                n = 0;
                while(isdigit(c)){
                    n = n * 10 + (c - '0');
                    i++;
                    c = str[i];
                }
                if(c == 'R'){
                    f_format_integer(list3(arg1,car(args),makeint(n)));
                    args = cdr(args);
                }
                else if(c == 'T'){
                    f_format_tab(list2(arg1,makeint(n)));
                }
                else
                    error(ILLEGAL_ARGS,"format ~n?",NIL);


            }
            else if(c == '%'){
                if(GET_OPT(output_stream) != EISL_OUTSTR)
                    fprintf(GET_PORT(output_stream),"\n");
                else{
                    sprintf(stream_str,"\n");
                    strcat(GET_NAME(output_stream),stream_str);
                }
                start_flag = 0;
                charcnt = 0;
            }
            else if(c == '&'){
                f_format_fresh_line(list1(arg1));
            }
            else if(c == '~'){
                if(GET_OPT(output_stream) != EISL_OUTSTR)
                    fprintf(GET_PORT(output_stream),"~");
                else{
                    sprintf(stream_str,"~");
                    strcat(GET_NAME(output_stream),stream_str);
                }
                start_flag = 0;
                charcnt++;
            }
            i++;
        }
        else if(c == '\\' && quote_flag == 0)
            i++;
        else if(c == '\\' && quote_flag == 1){
        	if(GET_OPT(output_stream) != EISL_OUTSTR)
                fprintf(GET_PORT(output_stream), "%c", c);
            else{
                sprintf(stream_str, "%c", c);
                strcat(GET_NAME(output_stream),stream_str);
            }
            i++;
            c = str[i];
            if(GET_OPT(output_stream) != EISL_OUTSTR)
                fprintf(GET_PORT(output_stream), "%c", c);
            else{
                sprintf(stream_str, "%c", c);
                strcat(GET_NAME(output_stream),stream_str);
            }
            i++;
        }
        else{
            if(c == '\'' && str[i+1] == '\''){
            	if(quote_flag == 0)
                	quote_flag = 1;
                else
                	quote_flag = 0;
                c = '"';
                i++;
            }
            if(GET_OPT(output_stream) != EISL_OUTSTR)
                fprintf(GET_PORT(output_stream), "%c", c);
            else{
                sprintf(stream_str, "%c", c);
                strcat(GET_NAME(output_stream),stream_str);
            }
            i++;
            start_flag = 0;
            charcnt++;
        }
        c = str[i];
    }
    if(GET_OPT(output_stream) != EISL_INSTR)
        fflush(GET_PORT(output_stream));
    output_stream = save;
    return(NIL);
}

int fprintr(FILE *p, int r, int n){
    int i,sign,len;
    char b[1024];

    sign = 1;
    if(n == 0){
        b[0] = '0';
        i = 0;
        goto exit;
    }
    if(n >= 0)
        sign = 1;
    else{
        sign = -1;
        n = abs(n);
    }
    i=0;
    while(n > 0){
        switch(n % r){
            case 0: b[i] = '0'; break;
            case 1: b[i] = '1'; break;
            case 2: b[i] = '2'; break;
            case 3: b[i] = '3'; break;
            case 4: b[i] = '4'; break;
            case 5: b[i] = '5'; break;
            case 6: b[i] = '6'; break;
            case 7: b[i] = '7'; break;
            case 8: b[i] = '8'; break;
            case 9: b[i] = '9'; break;
            case 10: b[i] = 'A'; break;
            case 11: b[i] = 'B'; break;
            case 12: b[i] = 'C'; break;
            case 13: b[i] = 'D'; break;
            case 14: b[i] = 'E'; break;
            case 15: b[i] = 'F'; break;
            case 16: b[i] = 'G'; break;
            case 17: b[i] = 'H'; break;
            case 18: b[i] = 'I'; break;
            case 19: b[i] = 'J'; break;
            case 20: b[i] = 'K'; break;
            case 21: b[i] = 'L'; break;
            case 22: b[i] = 'M'; break;
            case 23: b[i] = 'N'; break;
            case 24: b[i] = 'O'; break;
            case 25: b[i] = 'P'; break;
            case 26: b[i] = 'Q'; break;
            case 27: b[i] = 'R'; break;
            case 28: b[i] = 'S'; break;
            case 29: b[i] = 'T'; break;
            case 30: b[i] = 'U'; break;
            case 31: b[i] = 'V'; break;
            case 32: b[i] = 'W'; break;
            case 33: b[i] = 'X'; break;
            case 34: b[i] = 'Y'; break;
            case 35: b[i] = 'Z'; break;
        }

        n = n / r;
        i++;
    }
    i--;
    exit:
    len = strlen(b);
    if(sign == -1){
        fprintf(p, "%c", '-');
        len++;
    }
    while(i >= 0){
        fprintf(p, "%c", b[i]);
        i--;
    }
    return(len);
}


int sprintr(char *str, int r, int n){
    int i,j,sign,len;
    char b[1024];

    sign = 1;
    if(n == 0){
        b[0] = '0';
        i = 0;
        goto exit;
    }
    if(n >= 0)
        sign = 1;
    else{
        sign = -1;
        n = abs(n);
    }
    i=0;
    while(n > 0){
        switch(n % r){
            case 0: b[i] = '0'; break;
            case 1: b[i] = '1'; break;
            case 2: b[i] = '2'; break;
            case 3: b[i] = '3'; break;
            case 4: b[i] = '4'; break;
            case 5: b[i] = '5'; break;
            case 6: b[i] = '6'; break;
            case 7: b[i] = '7'; break;
            case 8: b[i] = '8'; break;
            case 9: b[i] = '9'; break;
            case 10: b[i] = 'A'; break;
            case 11: b[i] = 'B'; break;
            case 12: b[i] = 'C'; break;
            case 13: b[i] = 'D'; break;
            case 14: b[i] = 'E'; break;
            case 15: b[i] = 'F'; break;
            case 16: b[i] = 'G'; break;
            case 17: b[i] = 'H'; break;
            case 18: b[i] = 'I'; break;
            case 19: b[i] = 'J'; break;
            case 20: b[i] = 'K'; break;
            case 21: b[i] = 'L'; break;
            case 22: b[i] = 'M'; break;
            case 23: b[i] = 'N'; break;
            case 24: b[i] = 'O'; break;
            case 25: b[i] = 'P'; break;
            case 26: b[i] = 'Q'; break;
            case 27: b[i] = 'R'; break;
            case 28: b[i] = 'S'; break;
            case 29: b[i] = 'T'; break;
            case 30: b[i] = 'U'; break;
            case 31: b[i] = 'V'; break;
            case 32: b[i] = 'W'; break;
            case 33: b[i] = 'X'; break;
            case 34: b[i] = 'Y'; break;
            case 35: b[i] = 'Z'; break;
        }

        n = n / r;
        i++;
    }
    i--;
    exit:
    len = strlen(b);
    j = 0;
    if(sign == -1){
        str[j] = '-';
        j++;
        len++;
    }
    while(i >= 0){
        str[j] = b[i];
        i--;
        j++;
    }
    str[j] = NUL;
    return(len);
}

int f_format_char(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "format-char", arglist);
    if(!output_stream_p(arg1))
        error(NOT_OUT_STREAM, "format-char", arg1);
    if(!charp(arg2))
        error(NOT_CHAR, "format-char", arg2);

    if(GET_OPT(arg1) != EISL_OUTSTR){
        fprintf(GET_PORT(arg1), "%s", GET_NAME(arg2));
        charcnt++;
    }
    else{
        sprintf(stream_str, "%s", GET_NAME(arg2));
        strcat(GET_NAME(arg1),stream_str);
        charcnt = charcnt + strlen(GET_NAME(arg2));
    }
    start_flag = 0;
    return(NIL);
}

int f_format_fresh_line(int arglist){
    int arg1,save;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"format-fresh-line",arglist);
    if(!output_stream_p(arg1))
        error(NOT_STREAM,"format-fresh-line",arg1);

    if(!start_flag){
        save = output_stream;
        output_stream = arg1;
        if(GET_OPT(output_stream) != EISL_OUTSTR)
            fprintf(GET_PORT(output_stream),"\n");
        else{
            sprintf(stream_str,"\n");
            strcat(GET_NAME(output_stream),stream_str);
        }
        start_flag = 0;
        charcnt = 0;
        output_stream = save;
    }
    return(NIL);
}


int f_format_float(int arglist){
    int arg1,arg2,save,flt;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "format-float", arglist);
    if(!output_stream_p(arg1))
        error(NOT_OUT_STREAM, "format-float", arg1);
    if(!numberp(arg2))
        error(NOT_FLT, "format-float", arg2);
    save = output_stream;
    output_stream = arg1;
    flt = exact_to_inexact(arg2);
    print(flt);
    start_flag = 0;
    //count character
    output_stream = save;
    charcnt = charcnt + strlen(stream_str);
    return(NIL);
}


int f_format_integer(int arglist){
    int arg1,arg2,arg3,n,save,len;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if(length(arglist) != 3)
        error(WRONG_ARGS,"format-integer",arglist);
    if(!output_stream_p(arg1))
        error(NOT_OUT_STREAM, "format-integer", arg1);
    if(!integerp(arg2) && !longnump(arg2) && !bignump(arg2))
        error(NOT_INT, "format-integer", arg2);
    if(!integerp(arg3))
        error(NOT_INT, "format-integer", arg3);
    if((n=GET_INT(arg3)) < 2 || n > 36)
        error(OUT_OF_RANGE, "format-integer", arg3);

    save = output_stream;
    output_stream = arg1;
    if(integerp(arg2)){
        if(GET_OPT(output_stream) != EISL_OUTSTR)
            len = fprintr(GET_PORT(arg1),GET_INT(arg3),GET_INT(arg2));
        else{
            len = sprintr(stream_str,GET_INT(arg3),GET_INT(arg2));
            strcat(GET_NAME(output_stream),stream_str);
        }
        charcnt = charcnt + len;
    }
    else{
        print(arg2);
        charcnt = charcnt + strlen(stream_str);
   }
    output_stream = save;
    start_flag = 0;
    return(NIL);
}

int f_format_object(int arglist){
    int arg1,arg2,arg3,save;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);

    if(length(arglist) != 3)
        error(WRONG_ARGS,"format-object",arglist);
    if(!output_stream_p(arg1))
        error(NOT_OUT_STREAM,"format-object",arglist);

    save = output_stream;
    output_stream = arg1;
    if(stringp(arg2)){
        if(nullp(arg3))
            if(GET_OPT(arg1) != EISL_OUTSTR){
                fprintf(GET_PORT(arg1),"%s",GET_NAME(arg2));
                charcnt = charcnt + strlen(GET_NAME(arg2));
            }
            else{
                sprintf(stream_str,"%s",GET_NAME(arg2));
                strcat(GET_NAME(arg1),stream_str);
                charcnt = charcnt + strlen(GET_NAME(arg2));
            }
        else
            if(GET_OPT(arg1) != EISL_OUTSTR){
                fprintf(GET_PORT(arg1),"\\\"%s\\\"",GET_NAME(arg2));
                charcnt = charcnt + 4 + strlen(GET_NAME(arg2));
            }
            else{
                sprintf(stream_str,"\\\"%s\\\"",GET_NAME(arg2));
                strcat(GET_NAME(arg1),stream_str);
                charcnt = charcnt + 4 + strlen(GET_NAME(arg2));
            }
        }
    else if(charp(arg2)){
        if(nullp(arg3)){
            if(GET_OPT(arg1) != EISL_OUTSTR)
                fprintf(GET_PORT(arg1),"%s",GET_NAME(arg2));
            else{
                sprintf(stream_str,"%s",GET_NAME(arg2));
                strcat(GET_NAME(arg1),stream_str);
            }
            charcnt = charcnt + strlen(GET_NAME(arg2));
        }
        else{
            if(GET_OPT(arg1) != EISL_OUTSTR)
                fprintf(GET_PORT(arg1),"#\\\\%s",GET_NAME(arg2));
            else{
                sprintf(stream_str,"#\\\\%s",GET_NAME(arg2));
                strcat(GET_NAME(arg1),stream_str);
            }
            charcnt = charcnt + 3 + strlen(GET_NAME(arg2));
        }
    }
    else{
        print(arg2);
        charcnt = charcnt + strlen(stream_str);
    }
    output_stream = save;
    start_flag = 0;
    return(NIL);
}

int f_format_tab(int arglist){
    int arg1,arg2,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS,"format-tab",arglist);
    if(!output_stream_p(arg1))
        error(NOT_OUT_STREAM,"format-tab",arg1);
    if(!integerp(arg2))
        error(NOT_INT,"format-tab",arg2);

    n = GET_INT(arg2) - charcnt;
    if(n < 0)
        n = 1;
    while(n>0){
        if(GET_OPT(arg1) != EISL_OUTSTR)
            fprintf(GET_PORT(arg1)," ");
        else{
            sprintf(stream_str,"%s"," ");
            strcat(GET_NAME(arg1),stream_str);
        }
        n--;
        charcnt++;
    }
    start_flag = 0;
    return(NIL);
}


int f_open_input_file(int arglist){
    int arg1,n;
    FILE *port;

    arg1 = car(arglist);
    if((n=length(arglist)) != 1 && n != 2)
        error(WRONG_ARGS, "open-input-file", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "open-input-file", arg1);

    if(n == 1)
        port = fopen(GET_NAME(arg1),"r");
    else
        port = fopen(GET_NAME(arg1),"rb");

    if(port == NULL)
        error(CANT_OPEN, "open-input-file", arg1);

    return(makestream(port,EISL_INPUT));
}

int f_open_output_file(int arglist){
    int arg1,n;
    FILE *port;

    arg1 = car(arglist);
    if((n=length(arglist)) != 1 && n != 2)
        error(WRONG_ARGS, "open-output-file", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "open-output-file", arg1);

    port = fopen(GET_NAME(arg1),"w");
    if(port == NULL)
        error(CANT_OPEN, "open-output-file", arg1);

    return(makestream(port,EISL_OUTPUT));
}

int f_open_io_file(int arglist){
    int arg1,n;
    FILE *port;

    arg1 = car(arglist);
    if((n=length(arglist)) != 1 && n != 2)
        error(WRONG_ARGS, "open-io-file", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "open-io-file", arg1);

    port = fopen(GET_NAME(arg1),"r+");
    if(port == NULL)
        error(CANT_OPEN, "open-io-file", arg1);

    return(makestream(port,EISL_OPEN));
}

int f_close(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "close", arglist);
    if(!streamp(arg1))
        error(NOT_STREAM, "close", arg1);
    fclose(GET_PORT(arg1));
    start_flag = 1;
    return(UNDEF);
}

int f_finish_output(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "finish-output", arglist);
    if(!(streamp(arg1) && GET_CDR(arg1) == EISL_OUTPUT))
        error(NOT_OUT_STREAM, "finish-output", arg1);
    fflush(GET_PORT(arg1));
    return(UNDEF);
}


int f_file_length(int arglist){
    int arg1,arg2,size,res;
    FILE *p;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS,"file-length",arglist);
    if(!stringp(arg1))
        error(NOT_STR,"file-length",arg1);
    if(!integerp(arg2))
        error(NOT_INT,"file-length",arg2);

    p = fopen(GET_NAME(arg1),"rb");
    if(p == NULL)
        error(CANT_OPEN,"file-length",arg1);

    fseek(p, 0, SEEK_END);
    size = ftell(p);
    fclose(p);
    res = size;
    return(makeint(res));
}

int f_probe_file(int arglist){
    int arg1,res;
    FILE *p;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"probe-file",arglist);
    if(!stringp(arg1))
        error(NOT_STR,"probe-file",arg1);

    res = T;
    p = fopen(GET_NAME(arg1),"rb");
    if(p == NULL)
        res = NIL;

    if(res != NIL)
        fclose(p);

    return(res);
}

int f_file_position(int arglist){
    int arg1;
    FILE *p;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"file-position",arglist);
    if(!streamp(arg1))
        error(NOT_STREAM,"file-position",arg1);

    p = GET_PORT(arg1);
    return(makeint(ftell(p)));

}

int f_set_file_position(int arglist){
    int arg1,arg2;
    FILE *p;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS,"set-file-position",arglist);
    if(!streamp(arg1))
        error(NOT_STREAM,"set-file-position",arg1);
    if(!integerp(arg2))
        error(NOT_INT,"set-file-position",arg2);
    if(negativep(arg2))
        error(NOT_POSITIVE,"set-file-position",arg2);

    p = GET_PORT(arg1);
    fseek(p,GET_INT(arg2),SEEK_SET);
    return(arg2);
}



int f_write_byte(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "write-byte", arglist);
    if(!integerp(arg1))
        error(NOT_INT, "write-byte", arg1);
    if(!(streamp(arg2) && GET_OPT(arg2)))
        error(NOT_OUT_STREAM, "write-byte", arg2);

    fprintf(GET_PORT(arg2), "%c", (char)GET_INT(arg1));
    return(arg1);
}



int f_create_vector(int arglist){
    int arg1,arg2,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    if((n=length(arglist)) != 1 && length(arglist) != 2)
        error(WRONG_ARGS,"create-vector", arglist);
    if(!integerp(arg1) || negativep(arg1))
        error(NOT_INT, "create-vector", arg1);
    if(length(arglist) == 1)
        arg2 = UNDEF;

    return(makevec(GET_INT(arg1),arg2));
}

int f_create_array(int arglist){
    int arg1,arg2,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    if((n=length(arglist)) != 1 && length(arglist) != 2)
        error(WRONG_ARGS,"create-array", arglist);
    if(!listp(arg1))
        error(NOT_LIST, "create-array", arg1);
    if(check_dimension(arg1))
        error(OUT_OF_RANGE,"create-array",arg1);
    if(length(arglist) == 1)
        arg2 = UNDEF;

    return(makearray(arg1,arg2));
}

int check_dimension(int ls){
    while(!nullp(ls)){
        if(!integerp(car(ls)))
            return(1);
        else if(negativep(car(ls)))
            return(1);
        else
            ls =cdr(ls);
    }
    return(0);
}

int f_create_string(int arglist){
    int arg1,arg2,n,i;
    char str[STRSIZE],c;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if((n=length(arglist)) != 1 && n != 2)
        error(WRONG_ARGS, "create-string", arglist);
    if(!integerp(arg1) || negativep(arg1))
        error(NOT_INT, "create-string", arg1);

    n=GET_INT(arg1);
    if(nullp(arg2))
        c = ' ';
    else
        c = GET_CHAR(arg2);

    for(i=0;i<n;i++)
        str[i] = c;
    str[i] = NUL;
    return(makestr(str));
}

int f_parse_number(int arglist){
    int arg1;
    char *e;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "parse-number", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "parse-number", arg1);

    strcpy(stok.buf,GET_NAME(arg1));

    if(bignumtoken(stok.buf))
            return(makebigx(stok.buf));

    if(inttoken(stok.buf))
        return(makeint(strtol(stok.buf,&e,10)));

    if(flttoken(stok.buf) || expttoken(stok.buf))
        return(makeflt(atof(stok.buf)));

    if(bintoken(stok.buf))
        return(makeint((int)strtol(stok.buf,&e,2)));

    if(octtoken(stok.buf))
        return(makeint((int)strtol(stok.buf,&e,8)));

    if(dectoken(stok.buf))
        return(makeint((int)strtol(stok.buf,&e,10)));

    if(hextoken(stok.buf))
        return(makeint((int)strtol(stok.buf,&e,16)));

    error(CANT_PARSE,"parse-number",arg1);
    return(UNDEF);
}

int f_create_string_input_stream(int arglist){
    int arg1,res;
    char *str;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "create-string-input-stream", arglist);
    if(!stringp(arg1))
        error(NOT_STR, "create-string-input-stream", arg1);

    res = makestream(stdin,EISL_INSTR);
    str = (char *)malloc(strlen(GET_NAME(arg1))+1);
    if(str == NULL)
        error(MALLOC_OVERF,"create-string-input-stream",NIL);
    heap[res].name = str;
    strcpy(heap[res].name,GET_NAME(arg1));
    return(res);
}

int f_create_string_output_stream(int arglist){
    int res;
    char *str;

    if(length(arglist) != 0)
        error(WRONG_ARGS, "create-string-output-stream", arglist);

    res = makestream(stdout,EISL_OUTSTR);
    str = (char *)malloc(STRSIZE);
    if(str == NULL)
        error(MALLOC_OVERF,"create-string-output-stream",NIL);
    heap[res].name = str;
    strcpy(heap[res].name,"");
    return(res);
}

int f_get_output_stream_string(int arglist){
    int arg1,res;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "get-output-stream-string", arglist);
    if(!output_stream_p(arg1))
        error(NOT_STR, "get-output-stream-string", arg1);

    res = makestr(GET_NAME(arg1));
    return(res);
}



int f_subseq(int arglist){
    int arg1,arg2,arg3;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    if(length(arglist) != 3)
        error(WRONG_ARGS, "subseq", arglist);
    if(greaterp(arg2,arg3))
        error(OUT_OF_RANGE, "subseq", arglist);
    if(negativep(arg2) || negativep(arg3))
        error(OUT_OF_RANGE, "subseq", arglist);


    if(stringp(arg1)){
        if(strlen(GET_NAME(arg1)) < GET_INT(arg3))
            error(OUT_OF_RANGE, "subseq", arglist);
        return(substr(arg1,GET_INT(arg2),GET_INT(arg3)));
    }
    else if(listp(arg1)){
        if(length(arg1) < GET_INT(arg3))
            error(OUT_OF_RANGE, "subseq", arglist);
        return(sublis(arg1,GET_INT(arg2),GET_INT(arg3)));
    }
    else if(vectorp(arg1)){
        if(vector_length(arg1) < GET_INT(arg3))
            error(OUT_OF_RANGE, "subseq", arglist);
        return(subvec(arg1,GET_INT(arg2),GET_INT(arg3)));
    }

    error(ILLEGAL_ARGS, "subseq", arg1);
    return(UNDEF);
}


int f_identity(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"identity",arglist);

    return(arg1);
}

int f_get_universal_time(int arglist){
    time_t t;

    if(length(arglist) != 0)
        error(WRONG_ARGS,"get-universal-time",arglist);

    t = time(NULL);
    return(makeint((int)t));
}

int f_get_internal_run_time(int arglist){
    clock_t t;

    if(length(arglist) != 0)
        error(WRONG_ARGS,"get-internal-run-time",arglist);

    t = clock();
    return(makeint((int)t));
}

int f_get_internal_real_time(int arglist){
    clock_t t;

    if(length(arglist) != 0)
        error(WRONG_ARGS,"get-internal-real-time",arglist);

    t = clock();
    return(makeint((int)t));
}

int f_internal_time_units_per_second(int arglist){

    if(length(arglist) != 0)
        error(WRONG_ARGS,"internal-time-units-per-second",arglist);

    return(makeint(CLOCKS_PER_SEC));
}


int f_initialize_object_star(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS,"initialize-object*",arglist);
    if(!(IS_INSTANCE(arg1)))
        error(NOT_INSTANCE,"initialize-object*",arg1);
    if(!listp(arg2))
        error(NOT_LIST,"initialize-object*",arg2);

    return(initinst(arg1,arg2));
}

//controle
int f_quit(int arglist){
    int addr;

    for(addr=0; addr< HEAPSIZE; addr++)
        free(heap[addr].name);

    printf("- good bye -\n");
    longjmp(buf,2);
}

//extension

int f_heapdump(int arglist){
    int arg;

    arg = GET_INT(car(arglist));
    heapdump(arg,arg+10);
    return(T);
}

int f_gbc(int arglist){
    int n;

    if((n=length(arglist)) != 0 && n != 1)
        error(WRONG_ARGS, "gbc", arglist);
    if(nullp(arglist))
        gbc();
    else if(car(arglist) == T)
        gbc_flag= 1;
    else if(car(arglist) == NIL)
        gbc_flag = 0;

    return(T);
}

int f_dummyp(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"dummyp",arg1);

    if(GET_TAG(arg1) == DUMMY)
        return(T);
    else
        return(NIL);
}

//object

int f_class_of(int arglist){
    int arg;

    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "class-of", arglist);
    if(GET_OPT(arg) == SYSTEM)
        return(cbuilt_in_class);
    else if(GET_OPT(arg) == USER)
        return(cstandard_class);
    else
        return(GET_AUX(arg));
}

int f_instancep(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "instancep", arglist);
    if(!classp(arg2))
        error(NOT_CLASS, "instancep", arg2);

    if(GET_AUX(arg1) == arg2)
        return(T);
    else if(subclassp(GET_AUX(arg1),arg2))
        return(T);
    else if(GET_OPT(arg1) == SYSTEM && arg2 == cbuilt_in_class)
        return(T);
    else
        return(NIL);
}

int f_subclassp(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "subclassp", arglist);
    if(!classp(arg1))
        error(NOT_CLASS, "subclassp", arg2);
    if(!classp(arg2))
        error(NOT_CLASS, "subclassp", arg2);


    if(subclassp(arg1,arg2))
        return(T);
    else
        return(NIL);
}


int f_generic_function_p(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"generic-function-p",arglist);

    if(IS_GENERIC(arg1))
        return(T);
    else
        return(NIL);
}



int f_next_method_p(int arglist){
    int method,varlist;

    if(length(arglist) != 0)
        error(WRONG_ARGS,"next-method-p",arglist);
    if(generic_func == NIL)
        error(OUT_OF_RANGE,"next-method-p",NIL);

    method = cdr(next_method);
    while(!nullp(method)){
        varlist = car(GET_CAR(car(method)));
        if(matchp(varlist,generic_vars))
            return(T);
        method = cdr(method);
    }
    return(NIL);
}

int f_call_next_method(int arglist){
    int method,varlist,body,res;

    if(length(arglist) != 0)
        error(WRONG_ARGS,"call-next-method",arglist);
    if(generic_func == NIL)
        error(OUT_OF_RANGE,"call-next-method",NIL);

    res = NIL;
    varlist = NIL;
    method = cdr(next_method);
    while(!nullp(method)){
        varlist = car(GET_CAR(car(method)));
        if(matchp(varlist,generic_vars))
            goto exit;
        method = cdr(method);
    }
    error(NOT_EXIST_METHOD,"call-next-method",NIL);

    exit:
    next_method = method;
    varlist = genlamlis_to_lamlis(varlist);
    body = cdr(GET_CAR(car(method)));
    bindarg(varlist,generic_vars);
    while(!nullp(body)){
        res = eval(car(body));
        body = cdr(body);
    }
    unbind();
    return(res);
}


//condition
int f_error(int arglist){
    int arg1,arg2;

    arg1 = car(arglist); //error-string
    arg2 = cdr(arglist); //obj

    if(!stringp(arg1))
        error(NOT_STR, "error", arg1);

    signal_condition(makeusercond(csimple_error,arg1,arg2),NIL);
    return(UNDEF);
}

int f_cerror(int arglist){
    int arg1,arg2,arg3,strstream,str;

    arg1 = car(arglist); //continue-string
    arg2 = cadr(arglist); //error-string
    arg3 = cddr(arglist); //obj
    if(!stringp(arg1))
        error(NOT_STR, "error", arg1);
    if(!stringp(arg2))
        error(NOT_STR, "error", arg2);

    strstream = f_create_string_output_stream(NIL);
    f_format(cons(strstream,cons(arg1,arg3)));
    str = f_get_output_stream_string(list1(strstream));
    signal_condition(makeusercond(csimple_error,arg2,str),arg1);
    return(UNDEF);
}

int f_signal_condition(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "signal-condition", arglist);

    signal_condition(arg1,arg2);
    return(UNDEF);
}

int f_simple_error_format_string(int arglist){
    int arg1,vars,val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"simple-error-format-string",arglist);
    if(GET_AUX(arg1) != csimple_error)
        error(NOT_CLASS,"simple-error-format-string",arg1);

    vars = GET_CDR(arg1);
    val = cdr(assq(makesym("a"),vars));
    return(val);
}

int f_simple_error_format_arguments(int arglist){
    int arg1,vars,val;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"simple-error-format-arguments",arglist);
    if(GET_AUX(arg1) != csimple_error)
        error(NOT_CLASS,"simple-error-format-arguments",arg1);

    vars = GET_CDR(arg1);
    val = cdr(assq(makesym("b"),vars));
    return(val);
}

int f_arithmetic_error_operation(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"arithmetic-error-operation",arg1);
    if(GET_AUX(arg1) != carithmetic_error &&
        !subclassp(GET_AUX(arg1),carithmetic_error))
        error(NOT_ARITHMETIC,"arithmetic-error-operation",arg1);

    fun = cdr(assoc(makesym("c"),GET_CDR(arg1)));
    return(fun);
}


int f_arithmetic_error_operands(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"arithmetic-error-operands",arg1);
    if(GET_AUX(arg1) != carithmetic_error &&
        !subclassp(GET_AUX(arg1),carithmetic_error))
        error(NOT_ARITHMETIC,"arithmetic-error-operands",arg1);

    fun = cdr(assoc(makesym("b"),GET_CDR(arg1)));
    return(fun);
}

int f_domain_error_object(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"domain-error-object",arg1);
    if(GET_AUX(arg1) != cdomain_error)
        error(NOT_ARITHMETIC,"domain-error-object",arg1);

    fun = cdr(assoc(makesym("f"),GET_CDR(arg1)));
    return(fun);
}

int f_domain_error_expected_class(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"domain-error-expected-class",arg1);
    if(GET_AUX(arg1) != cdomain_error)
        error(NOT_ARITHMETIC,"domain-error-expected-class",arg1);

    fun = cdr(assoc(makesym("g"),GET_CDR(arg1)));
    return(fun);
}

int f_parse_error_string(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"parse-error-string",arg1);
    if(GET_AUX(arg1) != cparse_error)
        error(NOT_ARITHMETIC,"parse-error-string",arg1);

    fun = cdr(assoc(makesym("h"),GET_CDR(arg1)));
    return(fun);
}


int f_parse_error_expected_class(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"parse-error-expected-class",arg1);
    if(GET_AUX(arg1) != cparse_error)
        error(NOT_ARITHMETIC,"parse-error-expected-class",arg1);

    fun = cdr(assoc(makesym("g"),GET_CDR(arg1)));
    return(fun);
}


int f_stream_error_stream(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"stream-error-stream",arg1);
    if(GET_AUX(arg1) != cstream_error)
        error(NOT_ARITHMETIC,"stream-error-stream",arg1);

    fun = cdr(assoc(makesym("i"),GET_CDR(arg1)));
    return(fun);
}

int f_undefined_entity_name(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"undefined-entity-name",arg1);
    if(GET_AUX(arg1) != cundefined_entity)
        error(NOT_ARITHMETIC,"undefined-entity-name",arg1);

    fun = cdr(assoc(makesym("j"),GET_CDR(arg1)));
    return(fun);
}

int f_undefined_entity_namespace(int arglist){
    int arg1,fun;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"undefined-entity-namespace",arg1);
    if(GET_AUX(arg1) != cundefined_entity)
        error(NOT_ARITHMETIC,"undefined-entity-namespace",arg1);

    fun = cdr(assoc(makesym("k"),GET_CDR(arg1)));
    return(fun);
}

int f_condition_continuable(int arglist){
    int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"condition-continuable",arglist);

    if(GET_OPT(arg1) == NOTCONT)
        return(NIL);
    else
        return(makestr(GET_NAME(arg1)));
}

int f_continue_condition(int arglist){
    int arg1,arg2,n;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(!((n=length(arglist)) == 1 || n == 2))
        error(WRONG_ARGS,"continue-condition",arglist);

    if(GET_OPT(arg1) == CONTINUABLE)
        return(arg2);
    else
        return(UNDEF);
}
