/*
 * generate basic symbol e.g. T nil ...
 * generate class 
 * functions that make cell for data structures.
 * functions to access cell data
 *
 * symbol data structure
 * ISLisp is lisp-2 
 * symbol-address car=function-addr, cdr=global-val closure
 * function-address car=arg+body, cdr=environment 
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include "eisl.h"
#include "compat/nana_stubs.h"
#include "mem.h"
#include "fmt.h"
#include "except.h"
#include "str.h"

void init_cell(void)
{
    int addr, x;

    /* initialize heap area */
    for (addr = 0; addr < CELLSIZE; addr++) {
    SET_CDR(addr,addr+1);
    }
    hp[0] = 0;
    fc[0] = CELLSIZE;

    /* hash table for symbol */
    for (x = 0; x < HASHTBSIZE; x++)
	cell_hash_table[x] = NIL;


    /* 0th address is for NIL, set initial environment */
    make_sym("NIL");		/* 0th address NIL */
    SET_AUX(NIL, CLASS_NULL);	/* class of nil is null */
    SET_OPT(NIL, CONSTN);
    make_sym("T");		/* 2nd address is T */
    SET_AUX(T, CLASS_SYMBOL);	/* class of t is symbol */
    SET_OPT(T, CONSTN);
    make_sym("<undef>");	/* 4th address is UNDEF */
    SET_AUX(UNDEF, CLASS_SYMBOL);	/* class of <undef> is symbol */
    make_sym("<file-end>");	/* 6th address is FEND */
    SET_AUX(FEND, CLASS_SYMBOL);	/* class of <end-of-file> is symbol */
    int i;
    for (i = 0; i < PARASIZE; i++) {
	ep[i] = 0;
	dp[i] = 0;
	sp[i] = 0;
	ap[i] = 0;
    }

}


void reinit_cell(void){
    int i,w;

    w = CELLSIZE/(queue_num+1);
    fc[0] = w; 
    for(i=1;i<=queue_num;i++){
        hp[i] = w*i + 1;
        fc[i] = w;
    }
}

void bind_class(const char *name, int cl)
{
    int sym;

    sym = make_sym(name);
    SET_AUX(sym, cl);
    SET_OPT(cl, SYSTEM);	/* built-in-class */
    SET_OPT(sym, SYSTEM);	/* symbol formated by <***> are built-in-classes */
}

/* class aux = ((format-string . error-msg)(format-arguments . args)) */
void init_err_args(int cl)
{
    int vars, args;

    vars = list11(cons(make_sym("a"), UNDEF),	// format-string
		  cons(make_sym("b"), UNDEF),	// format-arguments
		  cons(make_sym("c"), UNDEF),	// function
		  cons(make_sym("d"), UNDEF),	// operation
		  cons(make_sym("e"), UNDEF),	// operands
		  cons(make_sym("f"), UNDEF),	// object
		  cons(make_sym("g"), UNDEF),	// expected-class
		  cons(make_sym("h"), UNDEF),	// string
		  cons(make_sym("i"), UNDEF),	// stream
		  cons(make_sym("j"), UNDEF),	// name
		  cons(make_sym("k"), UNDEF));	// namespace

    SET_CDR(cl, vars);
    args = list11(cons(make_sym("format-string"), make_sym("a")),
		  cons(make_sym("format-arguments"), make_sym("b")),
		  cons(make_sym("function"), make_sym("c")),
		  cons(make_sym("operation"), make_sym("d")),
		  cons(make_sym("operands"), make_sym("e")),
		  cons(make_sym("object"), make_sym("f")),
		  cons(make_sym("expected-class"), make_sym("g")),
		  cons(make_sym("string"), make_sym("h")),
		  cons(make_sym("stream"), make_sym("i")),
		  cons(make_sym("name"), make_sym("j")),
		  cons(make_sym("namespace"), make_sym("k")));
    SET_AUX(cl, args);

}

void init_class(void)
{
    cobject = make_class("object", NIL);
    cbasic_array = make_class("basic-array", cobject);
    cbasic_array_star = make_class("basic-array*", cbasic_array);
    cgeneral_array_star = make_class("general-array*", cbasic_array_star);
    cbasic_vector = make_class("basic-vector", cbasic_array);
    cgeneral_vector = make_class("general-vector", cbasic_vector);
    cstring = make_class("string", cbasic_vector);
    cbuilt_in_class = make_class("built-in-class", cbuilt_in_class);
    ccharacter = make_class("character", cobject);
    cfunction = make_class("function", cobject);
    cgeneric_function = make_class("generic-function", cfunction);
    cstandard_generic_function =
	make_class("standard-generic-function", cgeneric_function);
    clist = make_class("list", cobject);
    ccons = make_class("cons", clist);
    cnull =
	make_class("null",
		   list2(make_sym("<SYMBOL>"), make_sym("<LIST>")));
    csymbol = make_class("symbol", cobject);
    cnumber = make_class("number", cobject);
    cfloat = make_class("float", cnumber);
    cinteger = make_class("integer", cnumber);
    cserious_condition = make_class("serious-condition", cobject);
    cerror = make_class("error", cserious_condition);
    carithmetic_error = make_class("arithmetic-condition", cerror);
    cdivision_by_zero = make_class("division-by-zero", carithmetic_error);
    cfloating_point_overflow =
	make_class("floating-point-overflow", carithmetic_error);
    cfloating_point_underflow =
	make_class("floating-point-underflow", carithmetic_error);
    ccontrol_error = make_class("control-error", cerror);
    cparse_error = make_class("parse-error", cerror);
    cprogram_error = make_class("program-error", cerror);
    cdomain_error = make_class("domain-error", cprogram_error);
    cclass_error = make_class("class-error", cprogram_error);
    cundefined_entity = make_class("undefined-entity", cprogram_error);
    cunbound_variable = make_class("unbound-variable", cundefined_entity);
    cundefined_function =
	make_class("undefined-function", cundefined_entity);
    csimple_error = make_class("simple-error", cerror);
    cstream_error = make_class("stream-error", cerror);
    cend_of_stream = make_class("end-of-stream", cstream_error);
    cstorage_exhausted =
	make_class("storage-exhausted", cserious_condition);

    cstandard_class = make_class("standard-class", cobject);
    cstandard_object = make_class("standard-object", cobject);
    cstream = make_class("stream", cobject);
    cinvalid = make_class("invalid", cinvalid);
    cfixnum = make_class("fixnum", cinteger);
    clongnum = make_class("longnum", cinteger);
    cbignum = make_class("bignum", cinteger);

    bind_class("<OBJECT>", cobject);
    bind_class("<BASIC-ARRAY>", cbasic_array);
    bind_class("<GENERAL-ARRAY*>", cgeneral_array_star);
    bind_class("<BASIC-ARRAY*>", cbasic_array_star);
    bind_class("<BASIC-VECTOR>", cbasic_vector);
    bind_class("<GENERAL-VECTOR>", cgeneral_vector);
    bind_class("<STRING>", cstring);
    bind_class("<BUILT-IN-CLASS>", cbuilt_in_class);
    bind_class("<CHARACTER>", ccharacter);
    bind_class("<FUNCTION>", cfunction);
    bind_class("<GENERIC-FUNCTION>", cgeneric_function);
    bind_class("<STANDARD-GENERIC-FUNCTION>", cstandard_generic_function);
    bind_class("<LIST>", clist);
    bind_class("<CONS>", ccons);
    bind_class("<NULL>", cnull);
    bind_class("<SYMBOL>", csymbol);
    bind_class("<NUMBER>", cnumber);
    bind_class("<FLOAT>", cfloat);
    bind_class("<INTEGER>", cinteger);
    bind_class("<SERIOUS-CONDITION>", cserious_condition);
    bind_class("<ERROR>", cerror);
    bind_class("<ARITHMETIC-ERROR>", carithmetic_error);
    bind_class("<DIVISION-BY-ZERO>", cdivision_by_zero);
    bind_class("<FLOATING-POINT-OVERFLOW>", cfloating_point_overflow);
    bind_class("<FLOATING-POINT-UNDERFLOW>", cfloating_point_underflow);
    bind_class("<CONTROL-ERROR>", ccontrol_error);
    bind_class("<PARSE-ERROR>", cparse_error);
    bind_class("<PROGRAM-ERROR>", cprogram_error);
    bind_class("<DOMAIN-ERROR>", cdomain_error);
    bind_class("<CLASS-ERROR>", cclass_error);
    bind_class("<UNDEFINED-ENTITY>", cundefined_entity);
    bind_class("<UNBOUND-VARIABLE>", cunbound_variable);
    bind_class("<UNDEFINED-FUNCTION>", cundefined_function);
    bind_class("<SIMPLE-ERROR>", csimple_error);
    bind_class("<STREAM-ERROR>", cstream_error);
    bind_class("<END-OF-STREAM>", cend_of_stream);
    bind_class("<STORAGE-EXHAUSTED>", cstorage_exhausted);
    bind_class("<STANDARD-CLASS>", cstandard_class);
    bind_class("<STANDARD-OBJECT>", cstandard_object);
    bind_class("<STREAM>", cstream);
    bind_class("<INVALID>", cinvalid);
    bind_class("<FIXNUM>", cfixnum);
    bind_class("<LONGNUM>", clongnum);
    bind_class("<BIGNUM>", cbignum);

    init_err_args(cserious_condition);
    init_err_args(cerror);
    init_err_args(carithmetic_error);
    init_err_args(cdivision_by_zero);
    init_err_args(cfloating_point_overflow);
    init_err_args(cfloating_point_underflow);
    init_err_args(ccontrol_error);
    init_err_args(cparse_error);
    init_err_args(cprogram_error);
    init_err_args(cdomain_error);
    init_err_args(cclass_error);
    init_err_args(cundefined_entity);
    init_err_args(cunbound_variable);
    init_err_args(cundefined_function);
    init_err_args(csimple_error);
    init_err_args(cstream_error);
    init_err_args(cend_of_stream);
    init_err_args(cstorage_exhausted);

    ENSURE(cnull == CLASS_NULL && csymbol == CLASS_SYMBOL);
}

void init_stream(void)
{
    standard_input = make_stm(stdin, EISL_INPUT, "standard-input");
    standard_output = make_stm(stdout, EISL_OUTPUT, "standard-output");
    standard_error = make_stm(stderr, EISL_OUTPUT, "error-output");
}

int freshcell(void)
{
    int res;


    if (concurrent_stop_flag) {
	/* while remarking stop the world */
	pthread_mutex_lock(&mutex);
	while (concurrent_stop_flag) {
	    pthread_mutex_unlock(&mutex);
	    pthread_mutex_lock(&mutex);
	}
	res = hp[0];
	hp[0] = GET_CDR(hp[0]);
	SET_CDR(res, 0);
	fc[0]--;
	pthread_mutex_unlock(&mutex);
    } else if (concurrent_flag && fc[0] > 50) {
	pthread_mutex_lock(&mutex);
	res = hp[0];
	hp[0] = GET_CDR(hp[0]);
	SET_CDR(res, 0);
	fc[0]--;
	remark[remark_pt++] = res;
	pthread_mutex_unlock(&mutex);
	if (remark_pt > REMKSIZE) {
	    handling_resource_err = true;
	    error(RESOURCE_ERR, "freshcell remark", NIL, 0);
	}
    } else if (!concurrent_flag) {
	pthread_mutex_lock(&mutex);
	res = hp[0];
	hp[0] = GET_CDR(hp[0]);
	SET_CDR(res, 0);
	fc[0]--;
	pthread_mutex_unlock(&mutex);
	if (fc[0] <= 50 && !handling_resource_err) {
	    handling_resource_err = true;
	    error(RESOURCE_ERR, "freshcell rest", NIL, 0);
	}
    }

    else {
	error(RESOURCE_ERR, "freshcell other case", NIL, 0);
    }

    return (res);
}

int tfreshcell(int th)
{
    int res;


    if (concurrent_stop_flag) {
	/* while remarking stop the world */
	pthread_mutex_lock(&mutex);
	while (concurrent_stop_flag) {
	    pthread_mutex_unlock(&mutex);
	    pthread_mutex_lock(&mutex);
	}
	res = hp[th];
	hp[th] = GET_CDR(hp[th]);
	SET_CDR(res, 0);
	fc[th]--;
	pthread_mutex_unlock(&mutex);
    } else if (concurrent_flag && fc[th] > 50) {
	//pthread_mutex_lock(&mutex);
	res = hp[th];
	hp[th] = GET_CDR(hp[th]);
	SET_CDR(res, 0);
	fc[th]--;
	remark[remark_pt++] = res;
	//pthread_mutex_unlock(&mutex);
	if (remark_pt > REMKSIZE) {
	    handling_resource_err = true;
	    error(RESOURCE_ERR, "freshcell remark", NIL, 0);
	}
    } else if (!concurrent_flag) {
	//pthread_mutex_lock(&mutex);
	res = hp[th];
	hp[th] = GET_CDR(hp[th]);
	SET_CDR(res, 0);
	fc[th]--;
	//pthread_mutex_unlock(&mutex);
	if (fc[th] <= 50 && !handling_resource_err) {
	    handling_resource_err = true;
	    error(RESOURCE_ERR, "freshcell rest", NIL, 0);
	}
    }

    else {
	error(RESOURCE_ERR, "freshcell other case", NIL, 0);
    }

    return (res);
}



/* set value to environment by destructive by deep-bind */
void set_lex_env(int sym, int val, int th)
{
    int addr;

    addr = assq(sym, ep[th]);
    if (addr == FAILSE)
	add_lex_env(sym, val, th);
    else {
	SET_CDR(addr, val);
    }
}


/* bind value to dynamic environment */
int set_dyn_env(int sym, int val, int th)
{
    int i;

    for (i = dp[th] - 1; i >= 0; i--) {
	if (dynamic[i][0][th] == sym) {
	    dynamic[i][1][th] = val;
	    return (T);
	}
    }
    dynamic[dp[th]][0][th] = sym;
    dynamic[dp[th]][1][th] = val;
    dp[th]++;
    if (dp[th] >= DYNSIZE)
	error(VARIABLE_OVERF, "set_dyn_env", NIL, 0);
    return (T);
}


/* additinal of lexical variable */
void add_lex_env(int sym, int val, int th)
{

    ep[th] = cons(cons(sym, val), ep[th]);

}


/* addition of dynamic variable */
int add_dyn_env(int sym, int val, int th)
{
    dynamic[dp[th]][0][th] = sym;
    dynamic[dp[th]][1][th] = val;
    dp[th]++;
    if (dp[th] >= DYNSIZE)
	error(VARIABLE_OVERF, "add_dyn_env", NIL, th);
    return (T);
}


/*
 * environment is association list
 * env = ((sym1 . val1) (sym2 . val2) ...)
 * find value with assq
 * when not find return FAILSE
 */
int find_env(int sym, int th)
{
    int addr;

    addr = assq(sym, ep[th]);

    if (addr == FAILSE)
	return (FAILSE);
    else
	return (cdr(addr));
}


/* find in dynamic environment */
int find_dyn(int sym, int th)
{
    int i;

    for (i = dp[th] - 1; i >= 0; i--) {
	if (dynamic[i][0][th] == sym)
	    return (dynamic[i][1][th]);
    }
    return (FAILSE);
}

/* find tag in tag environment 
* catch_data structure
* [tag_addr,ep,unwind_nest]
* if find tag, return the index else return FAILSE
*/
int find_tag(int tag)
{
    int i;

    for (i = cp; i >= 0; i--) {
	if (catch_data[i][0] == tag)
	    return (i);
    }
    return (FAILSE);
}

/* bind to association list destructively */
void set_val(int sym, int val, int ls)
{
    int addr;

    addr = assq(sym, ls);
    if (addr != FAILSE)
	SET_CDR(addr, val);
}


/* for uniqueness of symbol */
int get_sym(const char *name, int index)
{
    int addr;

    addr = cell_hash_table[index];

    while (addr != NIL) {
	if (strcmp(name, GET_NAME(car(addr))) == 0)
	    return (car(addr));
	else
	    addr = cdr(addr);
    }
    return (-1);
}

/*
 * link list is generated in hheap area allways 
 */
int add_sym(const char *name, int index)
{
    int addr, res;

    addr = cell_hash_table[index];
    addr = cons(res = make_sym1(name), addr);
    pthread_mutex_lock(&mutex);
    cell_hash_table[index] = addr;
    pthread_mutex_unlock(&mutex);
    return (res);
}

/*
 * symbol car = function addr cdr = global value aux = class symbol option 
 * = CONSTN(constant ) 
 */
int make_sym1(const char *pname)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, SYM);
    TRY heap[addr].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "make_sym", NIL, 0);
    END_TRY;
    SET_CAR(addr, NIL);
    SET_CDR(addr, NIL);
    SET_AUX(addr, csymbol);	// class symbol
    return (addr);
}

/* calculate hash number
 * modulo sum of each charactor's ASCII code with
 * HASHTBSIZE(107)
 */
int hash(const char *name)
{
    int res;

    res = 0;
    while (*name != NUL) {
	res = res + (int) *name;
	name++;
    }
    return (res % HASHTBSIZE);
}


/*
 * make_ generate cell for data structures
 * make_int           make integer
 * make_long          make long integer
 * make_flt           make float number
 * make_sym           make symbol
 * make_func          make function (lambda)
 * make_generic       make generic function
 * make_generic_star  make generic function
 * make_method        make method for generic function
 * make_vec           make vector
 * make_arr           maker array
 * make_stm           make stream
 * make_str           make string
 * make_char          make character
 * make_class         make class
 * make_instance      make instance
 * make_dummy         make dummy
 * make_big           make bignum (bignum.c)
 */


/*
 * integer is immediate
 * positive integer, set 1 second bit from MSB.
 * negative integer is only negative.
 * integer is out of cell address.  so, integer does not require cell.
 */
int make_int(int intn)
{
    if (intn >= 0)
	return (INT_FLAG | intn);
    else
	return (intn);
}

int make_long(long long int lngnum)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, LONGN);
    SET_LONG(addr, lngnum);
    SET_AUX(addr, clongnum);	/* class longnum */
    return (addr);
}

int make_flt(double floatn)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, FLTN);
    SET_FLT(addr, floatn);
    SET_AUX(addr, cfloat);	/* class float */
    return (addr);
}

/*
 * symbol car = function cdr = global value aux = class 
 */
int make_sym(const char *pname)
{
    int index, res;

    index = hash(pname);
    if ((res = get_sym(pname, index)) != -1)
	return (res);
    else
	return (add_sym(pname, index));
}

/*
 * function car = args&body cdr = environment aux = null func object is
 * generated in heap area. 
 * note, if ep(environment) has bignum, convert to parmanent)
 */

int make_func(const char *pname, int addr)
{
    int val;

    val = freshcell();
    SET_TAG(val, FUNC);
    TRY heap[val].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "make_func", NIL, 0);
    END_TRY;
    SET_CAR(val, addr);
    SET_CDR(val, ep[0]);	/* local environment */
    SET_AUX(val, cfunction);	/* class function */
    /* if lambda is generated in method, save the method and given argument */
    if (generic_func != NIL)
	SET_PROP(val, cons(next_method, generic_vars));	/* method of generic-function and argument */
    SET_OPT(val, count_args(car(addr)));	/* amount of argument */
    return (val);
}

/* amount of argument. if it has :rest or &rest, it is minus number */
int count_args(int ls)
{
    int ls1, n, res;

    ls1 = reverse(ls);
    n = length(ls);
    if (eqp(cadr(ls1), make_sym(":REST")))
	res = -1 * n;
    else if (eqp(cadr(ls1), make_sym("&REST")))
	res = -1 * n;
    else
	res = n;

    return (res);
}


/*
 * ILOS generic function
 * generic car = args cdr = method aux = class 
 */
int make_generic(char *pname, int lamlist, int body)
{
    int val;

    val = freshcell();
    SET_TAG(val, GENERIC);
    TRY heap[val].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "make_generic", NIL, 0);
    END_TRY;
    SET_CAR(val, lamlist);
    SET_OPT(val, count_args(lamlist));	/* amount of argument */
    SET_CDR(val, NIL);
    SET_PROP(val, T);		/* method-combination default is T */
    SET_AUX(val, cstandard_generic_function);
    if (illegal_lambda_p(lamlist))
	error(ILLEGAL_ARGS, "make_generic", lamlist, 0);

    while (!nullp(body)) {
	/* (:method method-qualifier* parameter-profile form*) */
	if (eqp(caar(body), make_sym(":METHOD"))) {
	    if (method_qualifier_p(cadar(body)) && GET_PROP(val) == NIL) {
		error(ILLEGAL_FORM, "defgeneric", body, 0);
	    }
	    if (symbolp(cadar(body)) && !method_qualifier_p(cadar(body))) {
		error(ILLEGAL_FORM, "defgeneric", body, 0);
	    }
	    if (listp(cadar(body)) && undef_parameter_p(cadar(body))) {
		error(UNDEF_ENTITY, "defgeneric", body, 0);
	    }
	    if (listp(cadar(body))
		&& !unified_parameter_p(lamlist, cadar(body))) {
		error(ILLEGAL_FORM, "defgeneric", body, 0);
	    }
	    if (nullp(cadar(body))) {
		error(ILLEGAL_FORM, "defgeneric", body, 0);
	    }
	    insert_method(make_method(cdar(body)), val);
	} else if (eqp(caar(body), make_sym(":METHOD-COMBINATION"))) {
	    if (cadar(body) == NIL || cadar(body) == T)
		SET_PROP(val, cadar(body));
	    else
		error(ILLEGAL_FORM, "defgeneric", body, 0);
	} else if (eqp(caar(body), make_sym(":GENERIC-FUNCTION-CLASS"))) {
	    if (!(listp(cadar(body))
		  && eqp(car(cadar(body)), make_sym("CLASS")))) {
		error(ILLEGAL_FORM, "defgeneric", body, 0);
	    }
	    SET_AUX(val, eval(cadar(body), 0));
	} else {
	    error(ILLEGAL_FORM, "defgeneric", body, 0);
	}
	body = cdr(body);
    }
    return (val);
}

/*
 * diffrence is class. the class is generic-function use in defgeneric* 
 */
int make_generic_star(int lamlist, int body)
{
    int val;

    val = freshcell();
    SET_TAG(val, GENERIC);
    SET_CAR(val, lamlist);
    SET_OPT(val, count_args(lamlist));	/* amount of argument */
    SET_CDR(val, NIL);
    SET_PROP(val, T);		/* method-combination default is T */
    SET_AUX(val, cgeneric_function);	/* difference. only this. */
    while (!nullp(body)) {
	if (eqp(caar(body), make_sym(":METHOD")))
	    insert_method(make_method(cdar(body)), val);

	body = cdr(body);
    }
    return (val);
}

/*
 * method car = args&body cdr = environment aux = null opt = priority 
 */
int make_method(int addr)
{
    int val;

    val = freshcell();
    SET_TAG(val, METHOD);
    if (eqp(car(addr), make_sym(":AROUND"))) {
	SET_CAR(val, cdr(addr));
	SET_OPT(val, AROUND);
    } else if (eqp(car(addr), make_sym(":BEFORE"))) {
	SET_CAR(val, cdr(addr));
	SET_OPT(val, BEFORE);
    } else if (eqp(car(addr), make_sym(":AFTER"))) {
	SET_CAR(val, cdr(addr));
	SET_OPT(val, AFTER);
    } else {
	SET_CAR(val, addr);
	SET_OPT(val, PRIMARY);
    }
    SET_CDR(val, ep[0]);
    SET_AUX(val, NIL);
    return (val);
}

/* vector */
int make_vec(int n, int obj)
{
    int res, i, *vec;

    res = freshcell();
    TRY vec = (int *) ALLOC(sizeof(int) * n);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "make_vector", NIL, 0);
    END_TRY;
    SET_TAG(res, VEC);
    SET_VEC(res, vec);
    for (i = 0; i < n; i++)
	SET_VEC_ELT(res, i, copy(obj));
    SET_CDR(res, n);
    SET_AUX(res, cgeneral_vector);	/* class general-vector */
    return (res);
}



int vector(int lis)
{
    int len, i, res;

    len = length(lis);
    i = 0;
    res = make_vec(len, UNDEF);
    while (!nullp(lis)) {
	vector_set(res, i, car(lis));
	i++;
	lis = cdr(lis);
    }

    return (res);
}


/*
 * stream data structure
 * <OPT part>
 * EISL_INPUT input-stream text-mode
 * EISL_OUTPUT output-stream text-mode
 * EISL_INOUT io-stream text-mode
 * EISL_INPUT_BIN input-stream binary-mode
 * EISL_OUTPUT_BIN output-stream binary-mode
 * EISL_INOUT_BIN io-stream binary-mode
 * EISL_INSTR input-stream string-stream
 * EISL_OUTSTR output-stream string-stream
 * <PROF part>
 * EISL_OPEN  stream state is open
 * EISL_CLOSE stream state is close
 */

int make_stm(FILE * port, int type, const char *name)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, STREAM);
    SET_PORT(addr, port);	/* port for file stream */
    SET_CDR(addr, 0);		/* string-stream-position */
    SET_AUX(addr, cstream);	/* class */
    SET_OPT(addr, type);	/* EISL_INPUT/EISL_OUTPUT/EISL_INOUT/EISL_INSTR/EISL_OUTSTR/
				 * EISL_INPUT_BIN/EISL_OUTPUT_BIN/EISL_INOUT_BIN */
    SET_NAME(addr, name);
    SET_PROP(addr, 0);		/* output-string-stream charcount from */
    SET_PROF(addr, EISL_OPEN);	/* EISL_OPEN/EISL_CLOSE initial value is EISL_OPEN */
    return (addr);
}

// --------array-------
int make_arr(int ls, int obj)
{
    int size, res, i, ls1, *vec;

    ls1 = ls;
    if (!nullp(ls)) {
	size = 1;
	while (!nullp(ls)) {
	    int n;

	    n = GET_INT(car(ls));
	    if (n == 0)
		n = 1;
	    size = n * size;
	    ls = cdr(ls);
	}
	size++;
    } else
	size = 1;

    res = freshcell();
    TRY vec = (int *) ALLOC(sizeof(int) * size);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "array", NIL, 0);
    END_TRY;
    if (nullp(ls1)) {
	SET_TAG(res, ARR);
	SET_CDR(res, ls1);
	SET_AUX(res, cgeneral_array_star);	/* class */
    } else if (length(ls1) == 1) {
	SET_TAG(res, VEC);
	SET_CDR(res, GET_INT(car(ls1)));
	SET_AUX(res, cgeneral_vector);
    } else {
	SET_TAG(res, ARR);
	SET_CDR(res, ls1);
	SET_AUX(res, cgeneral_array_star);	/* class */
    }
    SET_VEC(res, vec);
    for (i = 0; i < size; i++)
	SET_VEC_ELT(res, i, copy(obj));

    return (res);
}


int make_str(const char *string)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, STR);
    TRY heap[addr].name = Str_dup(string, 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "make_str", NIL, 0);
    END_TRY;
    SET_AUX(addr, cstring);	/* class string */
    return (addr);
}

int make_char(const char *pname)
{
    int addr, pos;
    char low_name[SYMSIZE], char_entity;


    pos = 0;
    while (pname[pos] != NUL) {
	low_name[pos] = tolower(pname[pos]);
	pos++;
    }
    low_name[pos] = NUL;
    char_entity = pname[0];

    if (strcmp(low_name, "alarm") == 0) {
	char_entity = BEL;
    } else if (strcmp(low_name, "backspace") == 0) {
	char_entity = BS;
    } else if (strcmp(low_name, "delete") == 0) {
	char_entity = DEL;
    } else if (strcmp(low_name, "escape") == 0) {
	char_entity = ESC;
    } else if (strcmp(low_name, "return") == 0) {
	char_entity = RET;
    } else if (strcmp(low_name, "newline") == 0) {
	char_entity = EOL;
    } else if (strcmp(low_name, "null") == 0) {
	char_entity = NUL;
    } else if (strcmp(low_name, "space") == 0) {
	char_entity = SPACE;
    } else if (strcmp(low_name, "tab") == 0) {
	char_entity = TAB;
    } else if (strcmp(low_name, "^a") == 0) {
	char_entity = 1;
    } else if (strcmp(low_name, "^b") == 0) {
	char_entity = 2;
    } else if (strcmp(low_name, "^c") == 0) {
	char_entity = 3;
    } else if (strcmp(low_name, "^d") == 0) {
	char_entity = 4;
    } else if (strcmp(low_name, "^e") == 0) {
	char_entity = 5;
    } else if (strcmp(low_name, "^f") == 0) {
	char_entity = 6;
    } else if (strcmp(low_name, "^k") == 0) {
	char_entity = 11;
    } else if (strcmp(low_name, "^l") == 0) {
	char_entity = 12;
    } else if (strcmp(low_name, "^n") == 0) {
	char_entity = 14;
    } else if (strcmp(low_name, "^o") == 0) {
	char_entity = 15;
    } else if (strcmp(low_name, "^p") == 0) {
	char_entity = 16;
    } else if (strcmp(low_name, "^q") == 0) {
	char_entity = 17;
    } else if (strcmp(low_name, "^r") == 0) {
	char_entity = 18;
    } else if (strcmp(low_name, "^s") == 0) {
	char_entity = 19;
    } else if (strcmp(low_name, "^t") == 0) {
	char_entity = 20;
    } else if (strcmp(low_name, "^u") == 0) {
	char_entity = 21;
    } else if (strcmp(low_name, "^v") == 0) {
	char_entity = 22;
    } else if (strcmp(low_name, "^w") == 0) {
	char_entity = 23;
    } else if (strcmp(low_name, "^x") == 0) {
	char_entity = 24;
    } else if (strcmp(low_name, "^y") == 0) {
	char_entity = 25;
    } else if (strcmp(low_name, "^z") == 0) {
	char_entity = 26;
    }


    addr = freshcell();
    SET_TAG(addr, CHR);
    TRY heap[addr].name = (char *) ALLOC(CHARSIZE);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "make_char", NIL, 0);
    END_TRY;
    if (!isUni2(pname[0]) && !isUni3(pname[0]) && !isUni4(pname[0])
	&& !isUni5(pname[0]) && !isUni6(pname[0])) {
	heap[addr].name[0] = char_entity;
	heap[addr].name[1] = NUL;
    } else {
	pos = 0;
	while (pname[pos] != NUL) {
	    heap[addr].name[pos] = pname[pos];
	    pos++;
	}
	heap[addr].name[pos] = NUL;
    }
    SET_AUX(addr, ccharacter);
    return (addr);
}

/*
 * class obj car = super class cdr = class variable aux = method name =
 * class name 
 */
int make_class(const char *pname, int superclass)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, CLASS);
    TRY heap[addr].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "make_class", NIL, 0);
    END_TRY;
    SET_CAR(addr, superclass);
    SET_CDR(addr, NIL);
    SET_AUX(addr, NIL);
    return (addr);
}

/*
 * initls ((format-string a)(format-argments b))...(initarg var) ) 
 */
int make_instance(int cl, int initls)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, INSTANCE);
    SET_CAR(addr, GET_CAR(cl));	/* super class */
    SET_CDR(addr, slotvars(cl));	/* slot vars with super class */
    SET_AUX(addr, cl);		/* class of instance */
    while (!nullp(initls)) {
	set_val(cdr(assq(car(initls), GET_AUX(cl))), cadr(initls),
		GET_CDR(addr));
	initls = cddr(initls);
    }
    return (addr);
}

int slotvars(int x)
{
    if (nullp(x))
	return (NIL);
    else if (atomp(x) && nullp(GET_CAR(x)))
	return (copy(GET_CDR(x)));
    else if (atomp(x) && atomp(GET_CAR(x)))
	return (append(copy(GET_CDR(x)), copy(GET_CDR(GET_CAR(x)))));
    else if (atomp(x) && listp(GET_CAR(x)))
	return (append(copy(GET_CDR(x)), slotvars(GET_CAR(x))));
    else
	return (append(slotvars(GET_AUX(car(x))), slotvars(cdr(x))));
}



/* initialize instance
 * x is class-instance
 * initls is list for initialize value
 */

int initinst(int x, int initls)
{
    int cl, class_vars, inst_vars, initargs, n, temp;

    cl = GET_AUX(x);		/* class of x */
    class_vars = GET_CDR(cl);	/* class variable list. 
				   This is assoc list ((initarg1 . accessor1)(initarg2 . accesor2)...) */
    inst_vars = GET_CDR(x);	/* instance variable list. 
				   This is assoc list ((accessor1 . val1)(accessor2 . val2) ...) */
    initargs = GET_AUX(cl);	/* list to set (initarg1 val1 initarg2 val2 ...) */
    while (!nullp(class_vars)) {
	if ((n = assq(caar(class_vars), inst_vars)) != FAILSE)
	    SET_CDR(n, copy(cdar(class_vars)));
	class_vars = cdr(class_vars);
    }
    temp = initls;
    while (!nullp(initls)) {
	if (length(initls) < 2) {
	    error(WRONG_ARGS, "initinst", initls, 0);
	}
	n = assq(car(initls), initargs);
	if (n != 0 && n != FAILSE) {
	    int n2 = assq(GET_CDR(n), inst_vars);
	    if (n2 != 0 && n2 != FAILSE) {
		SET_CDR(n2, cadr(initls));
	    }
	}
	initls = cddr(initls);
    }

    SET_CDR(x, initinst1(inst_vars, GET_CAR(cl), temp));
    /* GET_CAR(cl) is super-class of cl temp is initls */
    return (x);
}

/* initialize variables of super class of instance */
int initinst1(int inst_vars, int sc, int initls)
{
    int class_vars;


    if (nullp(sc))
	return (inst_vars);
    else if (atomp(sc) && nullp(GET_CAR(GET_AUX(sc)))) {
	/* when not exist super-class of super-class */
	class_vars = GET_AUX(GET_AUX(sc));
	return (initinst2(inst_vars, class_vars, initls));
    } else if (atomp(sc) && !atomp(GET_CAR(GET_AUX(sc)))) {
	/* when exists super-class of superclass */
	class_vars = GET_AUX(GET_AUX(sc));
	int temp1;
	temp1 = initinst2(inst_vars, class_vars, initls);
	int sc1;
	sc1 = GET_CAR(GET_AUX(sc));
	int temp2;
	temp2 =
	    initinst1(initinst1(temp1, car(sc1), initls), cdr(sc1),
		      initls);
	return (initinst1(temp2, cdr(sc), initls));
    } else {
	return (initinst1
		(initinst1(inst_vars, car(sc), initls), cdr(sc), initls));
    }
}

int initinst2(int inst_vars, int class_vars, int initls)
{
    int n;

    while (!nullp(initls)) {
	n = assq(car(initls), class_vars);
	if (n != 0 && n != FAILSE) {
	    int n2 = assq(GET_CDR(n), inst_vars);
	    if (n2 != 0 && n2 != FAILSE) {
		SET_CDR(n2, cadr(initls));
	    }
	}
	initls = cddr(initls);
    }
    return (inst_vars);
}

int make_dummy(void)
{
    int res;

    res = freshcell();
    SET_TAG(res, DUMMY);
    SET_AUX(res, cnull);
    return (res);
}
