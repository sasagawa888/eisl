#ifndef FAST_H
#define FAST_H

#include <stdio.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "ffi.h"

pthread_mutex_t plock_mutex;

const int INT_PSQRT = 1073773446;	// INT_FLAG+sqrt(999999999)
const int INT_MSQRT = -31622;	// - sqrt(999999999)
#define FASTSTRLONG_SIZE 17
#define PARASIZE 10
static tfunc deftfunc;
static fn0 f0[NUM_FN0S];
static fn1 f1[NUM_FN1S];
static fn2 f2[NUM_FN2S];
static fn3 f3[NUM_FN3S];
static fn4 f4[NUM_FN4S];
static fn5 f5[NUM_FN5S];
static fn6 f6[NUM_FN6S];
static fn7 f7[NUM_FN7S];
static fn8 f8[NUM_FN8S];
volatile sig_atomic_t exit_flag = 0;


void signal_handler_c(int signo)
{
    exit_flag = 1;
}


void init0(int n, fn0 x)
{
    f0[n] = x;
}

void init1(int n, fn1 x)
{
    f1[n] = x;
}

void init2(int n, fn2 x)
{
    f2[n] = x;
}

void init3(int n, fn3 x)
{
    f3[n] = x;
}

void init4(int n, fn4 x)
{
    f4[n] = x;
}

void init5(int n, fn5 x)
{
    f5[n] = x;
}

void init6(int n, fn6 x)
{
    f6[n] = x;
}

void init7(int n, fn7 x)
{
    f7[n] = x;
}

void init8(int n, fn8 x)
{
    f8[n] = x;
}

void init_deftfunc(tfunc x)
{
    deftfunc = (tfunc) x;
}

static int catch_arg;		// recieve argument of catch

static int block_arg;		// recieve argument of block


static inline int Fgbc(void)
{
    return f0[GBC_IDX] ();
}


static inline int Fwait_para(void)
{
    return f0[WAIT_PARA_IDX] ();
}

static inline int Fjump_to_repl(void)
{
    return f0[JUMP_TO_REPL_IDX] ();
}

static inline int Fclear_child_signal(void)
{
    return f0[CLEAR_CHILD_SIGNAL_IDX] ();
}



static inline int Fpargpop(int x)
{
    return f1[PARGPOP_IDX] (x);
}



static inline int Fpop(int x)
{
    return f1[PPOP_IDX] (x);
}

static inline int Fpshelterpop(int x)
{
    return f1[PSHELTERPOP_IDX] (x);
}

static inline int Fgetdynpt(void)
{
    return f0[GETDYNPT_IDX] ();
}

static inline int Fget_error_handler(void)
{
    return f0[GET_ERROR_HANDLER_IDX] ();
}

static inline int Fget_error_flag(void)
{
    return f0[GET_ERROR_FLAG_IDX] ();
}

static inline int Frestore_error_handler(void)
{
    return f0[RESTORE_ERROR_HANDLER_IDX] ();
}

static inline int Fcar(int x)
{
    return f1[CAR_IDX] (x);
}

static inline int Fcdr(int x)
{
    return f1[CDR_IDX] (x);
}

static inline int Fcadr(int x)
{
    return f1[CADR_IDX] (x);
}

static inline int Fcaddr(int x)
{
    return f1[CADDR_IDX] (x);
}

static inline int Fcaar(int x)
{
    return f1[CAAR_IDX] (x);
}

static inline int Fcadar(int x)
{
    return f1[CADAR_IDX] (x);
}

static inline int Flist1(int x)
{
    return f1[LIST1_IDX] (x);
}

static inline int Fpeval(int x, int y)
{
    return f2[PEVAL_IDX] (x, y);
}

static inline int Faux(int x)
{
    return f1[AUX_IDX] (x);
}

static inline int Flength(int x)
{
    return f1[LENGTH_IDX] (x);
}

static inline int Fsubrp(int x)
{
    return f1[SUBRP_IDX] (x);
}

static inline int Ffsubrp(int x)
{
    return f1[FSUBRP_IDX] (x);
}

static inline int Ffunctionp(int x)
{
    return f1[FUNCTIONP_IDX] (x);
}

static inline int Fmacrop(int x)
{
    return f1[MACROP_IDX] (x);
}

static inline int Fintegerp(int x)
{
    return f1[INTEGERP_IDX] (x);
}

static inline int Flongnump(int x)
{
    return f1[LONGNUMP_IDX] (x);
}

static inline int Fbignump(int x)
{
    return f1[BIGNUMP_IDX] (x);
}

static inline int Fgetint(int x)
{
    return f1[GETINT_IDX] (x);
}

static inline int Fmakeint(int x)
{
    return f1[MAKEINT_IDX] (x);
}

static inline int Fmakeintlong(int x)
{
    return f1[MAKEINTLONG_IDX] (x);
}

static inline int Fvector(int x)
{
    return f1[VECTOR_IDX] (x);
}

static inline int fast_car(int x)
{
    return f1[FASTCAR_IDX] (x);
}

static inline int fast_cdr(int x)
{
    return f1[FASTCDR_IDX] (x);
}

static inline int Fcheckgbc(int x)
{
    return f1[CHECKGBC_IDX] (x);
}


static inline int Fpfindenv(int x, int y)
{
    return f2[PFINDENV_IDX] (x, y);
}

static inline int Fpfinddyn(int x, int y)
{
    return f2[PFINDDYN_IDX] (x, y);
}

static inline int Fpargpush(int x, int y)
{
    return f2[PARGPUSH_IDX] (x, y);
}

static inline int Fpshelterpush(int x, int y)
{
    return f2[PSHELTERPUSH_IDX] (x, y);
}

static inline int Fpush(int x, int y)
{
    return f2[PPUSH_IDX] (x, y);
}

static inline int Fgetopt(int x)
{
    return f1[GETOPT_IDX] (x);
}

static inline int Fgetprop(int x)
{
    return f1[GETPROP_IDX] (x);
}

static inline int Fsetdynpt(int x)
{
    return f1[SETDYNPT_IDX] (x);
}

static inline int Fsetcatchsymbols(int x)
{
    return f1[SETCATCHSYMBOLS_IDX] (x);
}

static inline int Fbigxtoparmanent(int x)
{
    return f1[BIGNTOPARMANENT_IDX] (x);
}

static inline int Fset_error_handler(int x)
{
    return f1[SET_ERROR_HANDLER_IDX] (x);
}

static inline int Fset_error_flag(int x)
{
    return f1[SET_ERROR_FLAG_IDX] (x);
}

static inline int Feval_para(int x)
{
    return f1[EVAL_PARA_IDX] (x);
}

static inline int Fget_para_output(int x)
{
    return f1[GET_PARA_OUTPUT_IDX] (x);
}

static inline int Fsexp_to_str(int x)
{
    return f1[SEXP_TO_STR_IDX] (x);
}

static inline int Fstr_to_sexp(int x)
{
    return f1[STR_TO_SEXP_IDX] (x);
}

static inline int Fread_from_pipe(int x)
{
    return f1[READ_FROM_PIPE_IDX] (x);
}

static inline int Freceive_from_child(int x)
{
    return f1[RECEIVE_FROM_CHILD_IDX] (x);
}


static inline int Fkill_rest_process(int x)
{
    return f1[KILL_REST_PROCESS_IDX] (x);
}

static inline int Fread_from_pipe_part(int x)
{
    return f1[READ_FROM_PIPE_PART_IDX] (x);
}


static inline int Fcons(int x, int y)
{
    return f2[CONS_IDX] (x, y);
}

static inline int Fnth(int x, int y)
{
    return f2[NTH_IDX] (x, y);
}

static inline int Fset_car(int x, int y)
{
    return f2[SETCAR_IDX] (x, y);
}

static inline int Fset_cdr(int x, int y)
{
    return f2[SETCDR_IDX] (x, y);
}

static inline int Fset_aux(int x, int y)
{
    return f2[SETAUX_IDX] (x, y);
}

static inline int Fset_opt(int x, int y)
{
    return f2[SETOPT_IDX] (x, y);
}


static inline int Fpcallsubr(int x, int y, int z)
{
    return f5[PCALL_SUBR_IDX] (x, y, z);
}

static inline int Flist2(int x, int y)
{
    return f2[LIST2_IDX] (x, y);
}

static inline int Flist3(int x, int y, int z)
{
    return f5[LIST3_IDX] (x, y, z);
}

static inline int Fnthcdr(int x, int y)
{
    return f2[NTHCDR_IDX] (x, y);
}


static inline int Fpapply(int x, int y, int z)
{
    return f5[PAPPLY_IDX] (x, y, z);
}

static inline int Fplus(int x, int y)
{
    return f2[PLUS_IDX] (x, y);
}

static inline int Fminus(int x, int y)
{
    return f2[MINUS_IDX] (x, y);
}

static inline int Fmult(int x, int y)
{
    return f2[MULT_IDX] (x, y);
}

static inline int Fquotient(int x, int y)
{
    return f2[QUOTIENT_IDX] (x, y);
}

static inline int Fremainder(int x, int y)
{
    return f2[REMAINDER_IDX] (x, y);
}

static inline int Fdivide(int x, int y)
{
    return f2[DIVIDE_IDX] (x, y);
}

static inline int Feqp(int x, int y)
{
    return f2[EQP_IDX] (x, y);
}

static inline int Feqlp(int x, int y)
{
    return f2[EQLP_IDX] (x, y);
}

static inline int Fnumeqp(int x, int y)
{
    return f2[NUMEQP_IDX] (x, y);
}

static inline int Fsmallerp(int x, int y)
{
    return f2[SMALLERP_IDX] (x, y);
}

static inline int Feqsmallerp(int x, int y)
{
    return f2[EQSMALLERP_IDX] (x, y);
}

static inline int Fgreaterp(int x, int y)
{
    return f2[GREATERP_IDX] (x, y);
}

static inline int Feqgreaterp(int x, int y)
{
    return f2[EQGREATERP_IDX] (x, y);
}

static inline int Fmember(int x, int y)
{
    return f2[MEMBER_IDX] (x, y);
}

static inline int Fconvert(int x, int y)
{
    return f2[CONVERT_IDX] (x, y);
}

static inline int Farray(int x, int y)
{
    return f2[ARRAY_IDX] (x, y);
}

static inline int Fpsetdynenv(int x, int y, int z)
{
    return f5[PSETDYNENV_IDX] (x, y, z);
}

static inline int Fpadddynenv(int x, int y, int z)
{
    return f5[PADDDYNENV_IDX] (x, y, z);
}

static inline int Fpsetdynamic(int x, int y, int z)
{
    return f5[PSET_DYNAMIC_IDX] (x, y, z);
}

static inline int Fsetprop(int x, int y)
{
    return f2[SETPROP_IDX] (x, y);
}

static inline int Fadaptp(int x, int y)
{
    return f2[ADAPTP_IDX] (x, y);
}

static inline int Fmatchp(int x, int y)
{
    return f2[MATCHP_IDX] (x, y);
}


static inline int FILOSerror(int x, int y)
{
    return f2[ILOSERR_IDX] (x, y);
}

static inline int Fwrite_to_pipe(int x, int y)
{
    return f2[WRITE_TO_PIPE_IDX] (x, y);
}

static inline int Fsend_to_child(int x, int y)
{
    return f2[SEND_TO_CHILD_IDX] (x, y);
}

static inline int Freceive_from_child_part(int x, int y)
{
    return f2[RECEIVE_FROM_CHILD_PART_IDX] (x, y);
}


static inline int Fmakestr(const char *x)
{
    return f3[MAKESTR_IDX] ((char *) x);
}

static inline int Fmakesym(const char *x)
{
    return f3[MAKESYM_IDX] ((char *) x);
}

static inline int Fmakechar(const char *x)
{
    return f3[MAKECHAR_IDX] ((char *) x);
}

static inline int Fmakestrflt(const char *x)
{
    return f3[MAKESTRFLT_IDX] ((char *) x);
}

static inline int Fmakebig(char *x)
{
    return f3[MAKEBIG_IDX] (x);
}

static inline int Fmakestrlong(const char *x)
{
    return f3[MAKESTRLONG_IDX] ((char *) x);
}

static inline int Fmakefaststrlong(const char *x)
{
    return f3[MAKEFASTSTRLONG_IDX] ((char *) x);
}

static inline long long int Fgetlong(int x)
{
    return f4[GETLONG_IDX] (x);
}

static inline int Fstringset(int x, int y, int z)
{
    return f5[STRINGSET_IDX] (x, y, z);
}

static inline int Farrayset(int x, int y, int z)
{
    return f5[ARRAYSET_IDX] (x, y, z);
}

static inline int Fmember1(int x, int y, int z)
{
    return f5[MEMBER1_IDX] (x, y, z);
}

static inline char *Fgetname(int x)
{
    return f6[GETNAME_IDX] (x);
}

static inline double Fgetflt(int x)
{
    return f7[GETFLT_IDX] (x);
}

static inline int Fmakedoubleflt(double x)
{
    return f8[MAKEDOUBLEFLT_IDX] (x);
}

static inline int fast_immediate(int x)
{
    if (x >= 0)
	return (x | INT_FLAG);
    else
	return (x);
}


static int fast_numeqp(int x, int y)
{
    if (x >= INT_FLAG && y >= INT_FLAG)
	if (x == y)
	    return (T);
	else
	    return (0);
    else if (x < 0 && y < 0)
	if (x == y)
	    return (T);
	else
	    return (0);
    else if (x >= INT_FLAG && y < 0)
	return (0);
    else if (x < 0 && y >= INT_FLAG)
	return (0);
    else
	return (Fnumeqp(x, y));
}


static int fast_smallerp(int x, int y)
{
    if (x >= INT_FLAG && y >= INT_FLAG)
	if (x < y)
	    return (T);
	else
	    return (0);
    else if (x < 0 && y < 0)
	if (x < y)
	    return (T);
	else
	    return (0);
    else if (x >= INT_FLAG && y < 0)
	return (0);
    else if (x < 0 && y >= INT_FLAG)
	return (T);
    else
	return (Fsmallerp(x, y));
}


static int fast_eqsmallerp(int x, int y)
{
    if (x >= INT_FLAG && y >= INT_FLAG)
	if (x <= y)
	    return (T);
	else
	    return (0);
    else if (x < 0 && y < 0)
	if (x <= y)
	    return (T);
	else
	    return (0);
    else if (x >= INT_FLAG && y < 0)
	return (0);
    else if (x < 0 && y >= INT_FLAG)
	return (T);
    else
	return (Feqsmallerp(x, y));
}


static inline int fast_greaterp(int x, int y)
{
    return (fast_smallerp(y,x));
}


static inline int fast_eqgreaterp(int x, int y)
{
    return (fast_eqsmallerp(x,y));
}

static int fast_plus(int x, int y)
{
    int intx, inty, res;
    if (x >= INT_FLAG && y >= INT_FLAG) {
	intx = (x & INT_MASK);
	inty = (y & INT_MASK);
	res = intx + inty;
	if (res >= SMALL_INT_MAX)
	    return (Fmakeintlong(res));
	else
	    return (res | INT_FLAG);
    } else if (x >= INT_FLAG && y < 0) {
	intx = (x & INT_MASK);
	inty = y;
	res = intx + inty;
	if (res >= 0)
	    res = res | INT_FLAG;
	return (res);
    } else if (x < 0 && y >= INT_FLAG) {
	intx = x;
	inty = (y & INT_MASK);
	res = intx + inty;
	if (res >= 0)
	    res = res | INT_FLAG;
	return (res);
    } else
	return (Fplus(x, y));
}


static int fast_minus(int x, int y)
{
    int intx, inty, res;
    if (x >= INT_FLAG && y >= INT_FLAG) {
	intx = (x & INT_MASK);
	inty = (y & INT_MASK);
	res = intx - inty;
	if (res >= 0)
	    res = res | INT_FLAG;
	return (res);
    } else if (x >= INT_FLAG && y < 0) {
	intx = (x & INT_MASK);
	inty = y;
	res = intx - inty;
	if (res >= 0)
	    res = res | INT_FLAG;
	return (res);
    } else if (x < 0 && y >= INT_FLAG) {
	intx = x;
	inty = (y & INT_MASK);
	res = intx - inty;
	if (res >= 0)
	    return (res | INT_FLAG);
	else if (res <= SMALL_INT_MAX)
	    return (Fmakeintlong(res));
	else
	    return (res);
    } else
	return (Fminus(x, y));
}


static int fast_mult(int x, int y)
{
    int intx, inty, res;
    if (x == INT_FLAG) return(x);
    else if (y == INT_FLAG) return(y);
    else if (x >= INT_FLAG && x <= INT_PSQRT && y >= INT_FLAG && y <= INT_PSQRT) {
	intx = (x & INT_MASK);
	inty = (y & INT_MASK);
	res = intx * inty;
	return (res | INT_FLAG);
    } else if (x >= INT_FLAG && x <= INT_PSQRT && y < 0 && y >= INT_MSQRT) {
	intx = (x & INT_MASK);
	inty = y;
	res = intx * inty;
	return (res);
    } else if (x < 0 && x >= INT_MSQRT && y >= INT_FLAG && y <= INT_PSQRT) {
	intx = x;
	inty = (y & INT_MASK);
	res = intx * inty;
	return (res);
    } else
	return (Fmult(x, y));
}


static int fast_mod(int x, int y)
{
    int intx, inty, res;
    long long int longx, longy;

    if (x >= INT_FLAG && y >= INT_FLAG) {
	intx = (x & INT_MASK);
	inty = (y & INT_MASK);
	res = intx % inty;
	res = res | INT_FLAG;
	return (res);
    } else if (x >= INT_FLAG && y < 0) {
	intx = (x & INT_MASK);
	inty = y;
	res = -1 * (intx % inty);
	if (res >= 0)
	    res = res | INT_FLAG;
	return (res);
    } else if (x < 0 && y >= INT_FLAG) {
	intx = x;
	inty = (y & INT_MASK);
	res = inty + (intx % inty);
	if (res >= 0)
	    res = res | INT_FLAG;
	return (res);
    } else if (x < 0 && y < 0) {
	res = -1 * ((-1 * x) % (-1 * y));
	return (res);
    } else if ((CELLRANGE(x) && Flongnump(x)) && !CELLRANGE(y)) {
	longx = Fgetlong(x);
	if (y >= INT_FLAG)
	    inty = (y & INT_MASK);
	longy = (long long int) inty;
	res = (int) (longx % longy);
	if (res >= 0)
	    res = res | INT_FLAG;
	return (res);
    } else
	return (Fpcallsubr(Fcar(Fmakesym("MOD")), Flist2(x, y),0));
}


static inline int fast_not(int x)
{
    if (x == NIL)
	return (T);
    else
	return (NIL);
}


static inline int fast_eq(int x, int y)
{
    if (x == y)
	return (T);
    else
	return (NIL);
}


static int fast_setnth(int x, int n, int y)
{
    while (n > 0) {
	x = Fcdr(x);
	n--;
    }
    Fset_car(x, y);
    return (y);
}

static char *fast_sprint_hex_long(long int n)
{
    static char res[FASTSTRLONG_SIZE];
    static const char *hex_digits = "0123456789ABCDEF";
    uint64_t u = n;
    for (int i = 0; i < 8; i++) {
	uint8_t byte = (u >> (i << 3)) & 0xFF;
	uint8_t hi_nybble = (byte >> 4) & 0x0F, lo_nybble = byte & 0x0F;
	res[14 - (i << 1)] = hex_digits[hi_nybble];
	res[15 - (i << 1)] = hex_digits[lo_nybble];
    } return res;
}


    // ---------------OPenGL-----------------
static int displayfunc;
static inline void display_callback(void)
{
    Fpeval(displayfunc,0);
}

static int keyboardfunc;

static void keyboard_callback(unsigned char key, int x, int y)
{
    Fset_cdr(Fmakesym("gl::key"), Fmakeint((int) key));
    Fset_cdr(Fmakesym("gl::x"), Fmakeint(x));
    Fset_cdr(Fmakesym("gl::y"), Fmakeint(y));
    Fpeval(keyboardfunc,0);
}

static int mousefunc;

static void mouse_callback(int button, int state, int x, int y)
{
    Fset_cdr(Fmakesym("gl::button"), Fmakeint(button));
    Fset_cdr(Fmakesym("gl::state"), Fmakeint(state));
    Fset_cdr(Fmakesym("gl::x"), Fmakeint(x));
    Fset_cdr(Fmakesym("gl::y"), Fmakeint(y));
    Fpeval(mousefunc,0);
}
#endif				/* */


//----------tcl/tk
static char *str_to_lower(char *s)
{
    char *p;

    for (p = s; *p; p++)
	*p = tolower(*p);
    return (s);
}
