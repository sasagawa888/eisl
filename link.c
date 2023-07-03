/*
 * dynamic link for compiled code
 * <dynamic linking mechanism>
 * f_load calls dynamic_link when it receives file with extension o.
 * fast.h header file has dynamically linked code. 
 * compiler uses it to generate compiled code. 
 * compiled lisp code is dynamically linkable code.
 */


#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "eisl.h"
#include "mem.h"
#include "str.h"


static void *hmod;

/*
 * dynamic-link functions
 * compiled code link following functions
 */
typedef void (*initdeftfunc_t)(tfunc);
typedef void (*voidfunc_t)(void);

typedef int (*initfunc0)(int, fn0);
typedef int (*initfunc1)(int, fn1);
typedef int (*initfunc2)(int, fn2);
typedef int (*initfunc3)(int, fn3);
typedef int (*initfunc4)(int, fn4);
typedef int (*initfunc5)(int, fn5);
typedef int (*initfunc6)(int, fn6);
typedef int (*initfunc7)(int, fn7);
typedef int (*initfunc8)(int, fn8);

void dynamic_link(int x)
{
    char *str;
    initfunc0 init_f0;
    initfunc1 init_f1;
    initfunc2 init_f2;
    initfunc3 init_f3;
    initfunc4 init_f4;
    initfunc5 init_f5;
    initfunc6 init_f6;
    initfunc7 init_f7;
    initfunc8 init_f8;
    initdeftfunc_t init_deftfunc;
    voidfunc_t init_tfunctions, init_declare;

    if (Str_chr(GET_NAME(x), 1, 0, '/') != 0) {
	str = Str_dup(GET_NAME(x), 1, 0, 1);
    } else {
	str = Str_cat("./", 1, 0, GET_NAME(x), 1, 0);
    }

    hmod = dlopen(str, RTLD_LAZY);

    FREE(str);
    if (hmod == NULL)
	error(ILLEGAL_ARGS, "load", x);

    init_f0 = (initfunc0) dlsym(hmod, "init0");
    init_f1 = (initfunc1) dlsym(hmod, "init1");
    init_f2 = (initfunc2) dlsym(hmod, "init2");
    init_f3 = (initfunc3) dlsym(hmod, "init3");
    init_f4 = (initfunc4) dlsym(hmod, "init4");
    init_f5 = (initfunc5) dlsym(hmod, "init5");
    init_f6 = (initfunc6) dlsym(hmod, "init6");
    init_f7 = (initfunc7) dlsym(hmod, "init7");
    init_f8 = (initfunc8) dlsym(hmod, "init8");
    init_deftfunc = (initdeftfunc_t) dlsym(hmod, "init_deftfunc");
    init_tfunctions = (voidfunc_t) dlsym(hmod, "init_tfunctions");
    init_declare = (voidfunc_t) dlsym(hmod, "init_declare");

    int arg_pop1(int th)
    {
        return(arg_pop(0));
    }

    /* argument-0 type */
    init_f0(CHECKGBC_IDX, check_gbc);
    init_f0(GBC_IDX, gbc);
    init_f0(FRESHCELL_IDX, freshcell);
    init_f0(FREECELL_IDX, freecell);
    init_f0(ARGPOP_IDX, arg_pop1);
    init_f0(SHELTERPOP_IDX, shelter_pop);
    init_f0(POP_IDX, pop);
    init_f0(GETDYNPT_IDX, get_dynpt);
    init_f0(GET_ERROR_HANDLER_IDX, get_error_handler);
    init_f0(GET_ERROR_FLAG_IDX, get_error_flag);
    init_f0(RESTORE_ERROR_HANDLER_IDX, restore_error_handler);

    /* argument-1 type */
    int find_dyn1(int x)
    {
        return(find_dyn(x,0));
    }

    int arg_push1(int x)
    {
        return(arg_push(x,0));
    }

    init_f1(CAR_IDX, car);
    init_f1(CDR_IDX, cdr);
    init_f1(CADR_IDX, cadr);
    init_f1(CADDR_IDX, caddr);
    init_f1(CAAR_IDX, caar);
    init_f1(CADAR_IDX, cadar);
    init_f1(LIST1_IDX, list1);
    init_f1(EVAL_IDX, eval);
    init_f1(AUX_IDX, get_aux);
    init_f1(LENGTH_IDX, fast_length);
    init_f1(SUBRP_IDX, subrp);
    init_f1(FSUBRP_IDX, fsubrp);
    init_f1(FUNCTIONP_IDX, functionp);
    init_f1(MACROP_IDX, macrop);
    init_f1(INTEGERP_IDX, integerp);
    init_f1(LONGNUMP_IDX, longnump);
    init_f1(BIGNUMP_IDX, bignump);
    init_f1(GETINT_IDX, get_int);
    init_f1(MAKEINT_IDX, make_int);
    init_f1(MAKEINTLONG_IDX, make_int_long);
    init_f1(VECTOR_IDX, vector);
    init_f1(FASTCAR_IDX, fast_car);
    init_f1(FASTCDR_IDX, fast_cdr);
    init_f1(FINDENV_IDX, find_env);
    init_f1(FINDDYN_IDX, find_dyn1);
    init_f1(ARGPUSH_IDX, arg_push1);
    init_f1(SHELTERPUSH_IDX, shelter_push);
    init_f1(PUSH_IDX, push);
    init_f1(GETOPT_IDX, get_opt);
    init_f1(GETPROP_IDX, get_prop);
    init_f1(SETDYNPT_IDX, set_dynpt);
    init_f1(SETCATCHSYMBOLS_IDX, set_catch_symbols);
    init_f1(BIGNTOPARMANENT_IDX, big_to_parmanent);
    init_f1(SET_ERROR_HANDLER_IDX, set_error_handler);
    init_f1(SET_ERROR_FLAG_IDX, set_error_flag);

    /* argument-2 type */
    /* compiler generate should generate following code while in plet compile
     * *plet(*arg){
     * Fsetdynenv(x,y,cellarg->th)
     }
     * compile set flag while compiling plet. and generate Pthread code.
    */
    void set_dyn_env1(int x, int y)
    {
        set_dyn_env(x, y, 0);
    }
    void add_dyn_env1(int x, int y)
    {
        add_dyn_env(x, y, 0);
    }
    void set_dynamic1(int x, int y)
    {
        set_dynamic(x,y,0);
    }
    
    init_f2(CONS_IDX, cons);
    init_f2(NTH_IDX, nth);
    init_f2(SETCAR_IDX, set_car);
    init_f2(SETCDR_IDX, set_cdr);
    init_f2(SETAUX_IDX, set_aux);
    init_f2(SETOPT_IDX, set_opt);
    init_f2(CALLSUBR_IDX, call_subr);
    init_f2(LIST2_IDX, list2);
    init_f2(NTHCDR_IDX, nth_cdr);
    init_f2(APPLY_IDX, apply);
    init_f2(PLUS_IDX, plus);
    init_f2(MINUS_IDX, minus);
    init_f2(MULT_IDX, mult);
    init_f2(QUOTIENT_IDX, quotient);
    init_f2(REMAINDER_IDX, s_remainder);
    init_f2(DIVIDE_IDX, divide);
    init_f2(EQP_IDX, eqp);
    init_f2(EQLP_IDX, eqlp);
    init_f2(NUMEQP_IDX, numeqp);
    init_f2(SMALLERP_IDX, smallerp);
    init_f2(EQSMALLERP_IDX, eqsmallerp);
    init_f2(GREATERP_IDX, greaterp);
    init_f2(EQGREATERP_IDX, eqgreaterp);
    init_f2(MEMBER_IDX, member);
    init_f2(CONVERT_IDX, convert);
    init_f2(ARRAY_IDX, array);
    init_f2(SETDYNENV_IDX, set_dyn_env1);
    init_f2(ADDDYNENV_IDX, add_dyn_env1);
    init_f2(SETDYNAMIC_IDX, set_dynamic1);
    init_f2(SETPROP_IDX, set_prop);
    init_f2(ADAPTP_IDX, a_adaptp);
    init_f2(MATCHP_IDX, a_matchp);
    init_f2(ILOSERR_IDX, ILOSerror);



    /* argument-1 string type */
    init_f3(MAKESTR_IDX, (fn3) make_str);
    init_f3(MAKESYM_IDX, (fn3) make_sym);
    init_f3(MAKECHAR_IDX, (fn3) make_char);
    init_f3(MAKESTRFLT_IDX, (fn3) make_str_flt);
    init_f3(MAKEBIG_IDX, make_big);
    init_f3(MAKESTRLONG_IDX, (fn3) make_str_long);
    init_f3(MAKEFASTSTRLONG_IDX, (fn3) make_fast_str_long);

    /* argument-1 long long int type */
    init_f4(GETLONG_IDX, get_long);

    /* argument-3 type */
    init_f5(STRINGSET_IDX, string_set);
    init_f5(ARRAYSET_IDX, array_set);
    init_f5(MEMBER1_IDX, member1);

    /* string output type */
    init_f6(GETNAME_IDX, get_name);

    /* float output type */
    init_f7(GETFLT_IDX, get_flt);

    /* float input type */
    init_f8(MAKEDOUBLEFLT_IDX, make_double_flt);

    init_deftfunc((tfunc) def_subr);
    init_tfunctions();
    init_declare();

    return;
}


/* -----for FAST compiler------
 * compiler access cell data by dynamic linked function
 * following are dynamic linked from compiled function.
 */
int get_aux(int x)
{
    return (GET_AUX(x));
}


int set_car(int x, int y)
{
    SET_CAR(x, y);
    return (y);
}

int set_cdr(int x, int y)
{
    SET_CDR(x, y);
    return (y);
}

int set_aux(int x, int y)
{
    SET_AUX(x, y);
    return (y);
}

int set_opt(int x, int y)
{
    SET_OPT(x, y);
    return (x);
}

int set_prop(int x, int y)
{
    SET_PROP(x, y);
    return (y);
}

int set_dynpt(int x)
{
    dp[0] = x;
    return (x);
}


int get_opt(int x)
{
    return (GET_OPT(x));
}


int get_prop(int x)
{
    return (GET_PROP(x));
}

int get_dynpt(void)
{
    return (dp[0]);
}


int call_subr(int func, int arglist)
{
    return ((GET_SUBR(func)) (arglist,0));
}

int make_int_long(int n)
{
    int addr;

    addr = freshcell();
    SET_TAG(addr, LONGN);
    SET_LONG(addr, (long long int) n);
    SET_AUX(addr, cinteger);	/* class integer */
    return (addr);
}

int make_str_flt(const char *str)
{
    return (make_flt(atof(str)));
}

int make_double_flt(double x)
{
    return (make_flt(x));
}

int make_str_long(const char *str)
{
    return (make_long(atol(str)));
}

static inline int HexDigitToNybble(char c)
{
    if (!isdigit(c)) {
	static const int codesToSkip = 'A' - '9' - 1;
	c -= codesToSkip;
    }
    return c - '0';
}

int make_fast_str_long(const char *str)
{
    uint64_t u = 0;
    for (int i = 0; i < 8; i++) {
	uint8_t hi_nybble = HexDigitToNybble(str[14 - (i << 1)]);
	uint8_t lo_nybble = HexDigitToNybble(str[15 - (i << 1)]);
	uint64_t byte = (hi_nybble << 4) | lo_nybble;
	u |= (byte << (i << 3));
    }
    return make_long(u);
}

int nth_cdr(int n, int x)
{
    if (n == 0)
	return (x);
    else
	return (nth_cdr(n - 1, cdr(x)));
}



int a_adaptp(int x, int y)
{

    if (!CELLRANGE(x)) {
	/* fixnum is immediate. so fixnum data is out of cellrange */
	if (cfixnum == GET_AUX(y))	/* cfixnum is <class fixnum> */
	    return (1);
	else if (subclassp(cfixnum, GET_AUX(y)))
	    return (1);
	else
	    return (0);
    }
    if (x >= CELLSIZE) {
	error(ILLEGAL_ARGS, "a_adaptp", x);
	return (0);
    } else if (GET_AUX(x) == GET_AUX(y))
	return (1);
    else if (subclassp(GET_AUX(x), GET_AUX(y)))
	return (1);
    else
	return (0);
}


int a_matchp(int x, int y)
{

    if (!CELLRANGE(x)) {
	/* when x is out of cell range, x is fixnum */
	if (cfixnum == GET_AUX(y))
	    return (1);
	else if (GET_OPT(y) == SYSTEM && subclassp(cfixnum, GET_AUX(y)))
	    /* when built-in class, subclass is also eqclass. */
	    return (1);
	else
	    return (0);
    }
    if (x >= CELLSIZE) {
	error(ILLEGAL_ARGS, "a-matchp", x);
	return (0);
    } else if (GET_AUX(x) == GET_AUX(y))
	return (1);
    else if (GET_OPT(y) == SYSTEM && subclassp(GET_AUX(x), GET_AUX(y)))
	return (1);
    else
	return (0);
}



int fast_length(int x)
{
    int res;

    if (!listp(x) && !vectorp(x) && !stringp(x)) {
	error(ILLEGAL_ARGS, "length", x);
    }

    if (listp(x))
	res = length(x);
    else if (vectorp(x))
	res = vector_length(x);
    else
	res = string_length(x);

    return (INT_FLAG | res);
}


int fast_car(int x)
{
    if (!(IS_LIST(x)))
	error(NOT_LIST, "car", x);
    if (IS_NIL(x))
	error(NOT_LIST, "car", x);

    return (GET_CAR(x));
}


int fast_cdr(int x)
{
    if (!(IS_LIST(x)))
	error(NOT_LIST, "cdr", x);
    if (IS_NIL(x))
	error(NOT_LIST, "cdr", x);

    return (GET_CDR(x));
}


int set_dynamic(int x, int y, int th)
{
    if (find_dyn(x,0) != FAILSE)
	set_dyn_env(x, y, 0);
    else
	error(UNDEF_VAR, "set-dynamic", x);

    return (y);
}

int set_catch_symbols(int x)
{
    //catch_symbols = x;
    return (x);
}


char *get_name(int x)
{
    return (GET_NAME(x));
}

double get_flt(int x)
{
    return (GET_FLT(x));
}
