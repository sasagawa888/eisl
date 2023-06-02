/*
 * Easy-ISLisp (ISLisp) written by kenichi sasagawa 2016/4 
 */

#ifndef EISL_H
#define EISL_H

#include <setjmp.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include "compat/cdefs.h"
#include "ffi.h"
#include "term.h"
#include "except.h"
#include "compat/eiffel_stubs.h"

#define DYNSIZE 1000
#define STACKSIZE 400000
#define BUFSIZE 256
#define STRSIZE 10000
#define SHORT_STRSIZE 32
#define HASHTBSIZE 137
#define CTRLSTK 200
#define BACKSIZE 30
#define EISL_PATH_MAX 256
#if defined(__TINYC__) && defined(__riscv)
/* TCC in RISC-V cannot handle a larger number */
#define COL_SIZE 51
#else
#define COL_SIZE 255
#endif
#define NUM_HISTORY 10
#define BIGSIZE 20000000
#define NTTBASE 1000
#define PROFSIZE 1024

#define CPPQUOTE(x) #x
#define STRQUOTE(x) CPPQUOTE(x)

/* following are for unicode<=>UTF-8 transform */
#define UNI2ADD1    192		//#b11000000
#define UNI3ADD1    224		//#b11100000
#define UNI4ADD1    240		//#b11110000
#define UNIOADDO    128		//#b10000000
#define UNI2MSK1    1984	//#b0000011111000000
#define UNI2MSK2    63		//#b0000000000111111
#define UNI3MSK1    61440	//#b1111000000000000
#define UNI3MSK2    4032	//#b0000111111000000
#define UNI3MSK3    63		//#b0000000000111111
#define UNI4MSK1    1835008	//#b00000000000111000000000000000000
#define UNI4MSK2    258048	//#b00000000000000111111000000000000
#define UNI4MSK3    4032	//#b00000000000000000000111111000000
#define UNI4MSK4    63		//#b00000000000000000000000000111111
#define UTF2MSK1    63		//#b00111111
#define UTF3MSK1    31		//#b00011111
#define UTF4MSK1    15		//#b00001111
#define UTFOMSKO    127		//#b01111111

#define isUni1(c)   ((unsigned char)(c) <= 0x7f)

#define isUni2(c)   (((unsigned char)(c) >= 0xc2) && \
                     ((unsigned char)(c) <= 0xdf))

#define isUni3(c)   (((unsigned char)(c) >= 0xe0) && \
                     ((unsigned char)(c) <= 0xef))

#define isUni4(c)   (((unsigned char)(c) >= 0xf0) && \
                     ((unsigned char)(c) <= 0xf7))

#define isUni5(c)   (((unsigned char)(c) >= 0xf8) && \
                     ((unsigned char)(c) <= 0xfb))

#define isUni6(c)   (((unsigned char)(c) >= 0xfc) && \
                     ((unsigned char)(c) <= 0xfd))

#define isUniRest(c) (((unsigned char)(c) >= 0x80) && \
                     ((unsigned char)(c) <= 0xbf))



static const float VERSION = 2.98;
static const int WORK1 = ((int) ((CELLSIZE) / 20 * 6));
static const int WORK2 = ((int) ((CELLSIZE) / 20 * 13));
static const int FREESIZE = 900;
static const int SYMSIZE = 256;
static const int CHARSIZE = 7;	// unicode char. add \0 to tail
static const int MATSIZE = 256;
static const int UNDEF = 4;
static const int FEND = 6;

static const int BIGNUM_BASE = 1000000000;
static const int FAILSE = -1000000000;
static const int BIGNUM_WORK = BIGSIZE * 5 / 10;	// from 50% to 90% of bigcell area is working area.
// TCC does not have support for "static conts" as compile time constant
#ifdef __TINYC__
#define BIGNUM_PARMA  (BIGSIZE * 9 / 10)
#else
static const int BIGNUM_PARMA = BIGSIZE * 9 / 10;	//from 90% to 100% of bigcell area is parmanent area
#endif

typedef enum __packed { EMP, INTN, FLTN, LONGN, BIGN, VEC, ARR, CHR, STR,
	SYM,
    LIS, DUMMY,
    SUBR, FSUBR, FUNC, MACRO, CLASS, INSTANCE, GENERIC, METHOD,
    STREAM
} tag_t;
typedef enum __packed { FRE, USE } flag;

typedef int (*subr_t)(int args);
typedef struct __packed {
    union __packed {
	double fltnum;
	long long int lngnum;
	struct __packed {
	    union {
		int intnum;
		subr_t subr;
		FILE *port;
		int *dyna_vec;
		float *dyna_fvec;
	    } car;
	    union {
		int intnum;
	    } cdr;
	};
    } val;
    int aux;
    int prop;
    char *name;
    tag_t tag;
    flag flag;
    signed char option;
    char trace;
    int prof;
} cell;


typedef enum { LPAREN, RPAREN, QUOTE, DOT, BACKQUOTE, COMMA, ATMARK,
    STRING, SYMBOL,
    FUNCTION, INTEGER, FLOAT_N, BIGNUM, VECTOR, ARRAY, CHARACTER,
    BINARY, OCTAL, DECNUM, HEXNUM, EXPTNUM, EXPTOVERF, EXPTUNDERF, FILEEND,
	OTHER
} toktype;
typedef enum { GO, BACK } backtrack;

typedef struct {
    char ch;
    backtrack flag;
    toktype type;
    char buf[BUFSIZE];
} token;

typedef struct {
    char sepch;
    char before[BUFSIZE];
    char after[BUFSIZE];
} septoken;


/* ------pointer---- */
extern int ep;			// environment pointer
extern int dp;			// dynamic pointer
extern int hp;			// heap pointer
extern int sp;			// stack pointer
extern int fc;			// free counter
extern int ap;			// arglist pointer
extern int lp;			// shelter pointer
extern int wp;			// working pointer
extern int ac;			// allocate counter
extern int cp;          // catch tag pointer

/* ------class----- */
extern int cobject;
extern int cbasic_array;
extern int cbasic_array_star;
extern int cgeneral_array_star;
extern int cbasic_vector;
extern int cgeneral_vector;
extern int cstring;
extern int cbuilt_in_class;
extern int ccharacter;
extern int cfunction;
extern int cgeneric_function;
extern int cstandard_generic_function;
extern int clist;
extern int ccons;
extern int cnull;
extern int csymbol;
extern int cnumber;
extern int cfloat;
extern int cinteger;
extern int cserious_condition;
extern int cerror;
extern int carithmetic_error;
extern int cdivision_by_zero;
extern int cfloating_point_overflow;
extern int cfloating_point_underflow;
extern int ccontrol_error;
extern int cparse_error;
extern int cprogram_error;
extern int cdomain_error;
extern int cclass_error;
extern int cundefined_entity;
extern int cunbound_variable;
extern int cundefined_function;
extern int csimple_error;
extern int cstream_error;
extern int cend_of_stream;
extern int cstorage_exhausted;
extern int cstandard_class;
extern int cstandard_object;
extern int cstream;
extern int cinvalid;
extern int cfixnum;
extern int clongnum;
extern int cbignum;

static const int CLASS_NULL = 28;
static const int CLASS_SYMBOL = 29;


/* stream */
extern int standard_input;
extern int standard_output;
extern int standard_error;
extern int input_stream;
extern int output_stream;
extern int error_stream;
extern char stream_str[STRSIZE];
extern int charcnt;


/* read scanner */
extern token stok;
extern int line;
extern int column;
extern int buffer[COL_SIZE + 1][NUM_HISTORY];
extern int buffer1[COL_SIZE + 1];


/* heap and stack */
extern cell heap[CELLSIZE];
extern int stack[STACKSIZE];
extern int argstk[STACKSIZE];
extern int cell_hash_table[HASHTBSIZE];
extern int shelter[STACKSIZE];
extern int dynamic[DYNSIZE][2];
extern int bigcell[BIGSIZE];

/* bignum pointer, NTT(FFT) input_vector */
extern int big_pt0;
extern int big_pt1;

/* debugger */
extern int examin_sym;
extern int stepper_flag;


/* profiler */
extern int prof_sw;
extern int prof_sym[PROFSIZE];
extern int prof_pt;
extern double prof_dt0[PROFSIZE];
extern int prof_dt1[PROFSIZE];


#define DEF_GETTER(RETURN_TYPE, NAME, MEMBER, DEFAULT) \
    static inline RETURN_TYPE GET_ ## NAME (int addr)  \
    {                                                  \
        if (CELLRANGE(addr)) {                         \
            return heap[addr].MEMBER;                  \
        } else {                                       \
            return DEFAULT;                            \
        }                                              \
    }
DEF_GETTER(int, CAR, val.car.intnum, NIL)
DEF_GETTER(int, CDR, val.cdr.intnum, NIL)
DEF_GETTER(int, AUX, aux, cfixnum)
DEF_GETTER(int, PROP, prop, NIL)
DEF_GETTER(subr_t, SUBR, val.car.subr, NULL)
DEF_GETTER(tag_t, TAG, tag, INTN) DEF_GETTER(int, PROF, prof, NIL)
static inline FILE *GET_PORT(int addr)
{
    REQUIRE(CELLRANGE(addr) && GET_TAG(addr) == STREAM);
    FILE *res = heap[addr].val.car.port;
    ENSURE(res != NULL);
    return res;
}

static inline int GET_INT(int addr)
{
    return ((addr > 0) ? (INT_MASK & addr) : addr);
}

DEF_GETTER(double, FLT, val.fltnum, NIL)
DEF_GETTER(long long int, LONG, val.lngnum, NIL)
static inline void SET_NAME(int addr, const char *x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].name = (char *) x;
}

static inline char *GET_NAME(int addr)
{
    REQUIRE(CELLRANGE(addr));
    char *res = heap[addr].name;
    ENSURE(res != NULL);
    return res;
}

static inline char GET_CHAR(int addr)
{
    REQUIRE(CELLRANGE(addr) &&
	    GET_TAG(addr) == CHR && heap[addr].name != NULL);
    return heap[addr].name[0];
}

DEF_GETTER(signed char, OPT, option, 0)
static inline void SET_TAG(int addr, tag_t x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].tag = x;
}

static inline void SET_CAR(int addr, int x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].val.car.intnum = x;
}

static inline void SET_CDR(int addr, int x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].val.cdr.intnum = x;
}

static inline void SET_AUX(int addr, int x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].aux = x;
}

static inline int SET_PROP(int addr, int x)
{
    if (CELLRANGE(addr)) {
	return (heap[addr].prop = x);
    } else {
	return NIL;
    }
}

static inline int SET_PROF(int addr, int x)
{
    if (CELLRANGE(addr)) {
	return (heap[addr].prof = x);
    } else {
	return NIL;
    }
}

static inline void SET_FLT(int addr, double x)
{
    REQUIRE(CELLRANGE(addr) && GET_TAG(addr) == FLTN);
    heap[addr].val.fltnum = x;
}

static inline void SET_LONG(int addr, long long int x)
{
    REQUIRE(CELLRANGE(addr) && GET_TAG(addr) == LONGN);
    heap[addr].val.lngnum = x;
}

static inline void SET_PORT(int addr, FILE * x)
{
    REQUIRE(CELLRANGE(addr) && GET_TAG(addr) == STREAM);
    heap[addr].val.car.port = x;
}

static inline void SET_OPT(int addr, signed char x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].option = x;
}

static inline void SET_TR(int addr, char x)
{
    REQUIRE(CELLRANGE(addr));
    heap[addr].trace = x;
}

static inline void SET(int addr, int x)
{
    REQUIRE(CELLRANGE(addr) && CELLRANGE(x));
    heap[addr] = heap[x];
}

#define DEF_PREDICATE(NAME, TAG)                \
    static inline bool IS_ ## NAME (int addr)   \
    {                                           \
        if (CELLRANGE(addr)) {                  \
            return (heap[addr].tag == TAG);     \
        } else {                                \
            return NIL;                         \
        }                                       \
    }
static inline bool IS_INTEGER(int addr)
{
    return !CELLRANGE(addr);
}

DEF_PREDICATE(BIGNNUM, BIGN)
    DEF_PREDICATE(LONGNUM, LONGN)
    DEF_PREDICATE(FLOAT, FLTN)
    DEF_PREDICATE(LIST, LIS)
    DEF_PREDICATE(STRING, STR)
static inline bool IS_NIL(int addr)
{
    return (addr == NIL);
}

static inline bool IS_T(int addr)
{
    return (addr == T);
}

DEF_PREDICATE(VECTOR, VEC)
    DEF_PREDICATE(ARRAY, ARR)
    DEF_PREDICATE(SUBR, SUBR)
    DEF_PREDICATE(FSUBR, FSUBR)
    DEF_PREDICATE(FUNC, FUNC)
    DEF_PREDICATE(MACRO, MACRO)
    DEF_PREDICATE(CLASS, CLASS)
    DEF_PREDICATE(GENERIC, GENERIC)
static inline bool HAS_NAME(int addr, const char *x)
{
    REQUIRE(CELLRANGE(addr) && heap[addr].name != NULL);
    return (strcmp(heap[addr].name, x) == 0);
}

static inline bool SAME_NAME(int addr1, int addr2)
{
    REQUIRE(CELLRANGE(addr1) && CELLRANGE(addr2) &&
	    heap[addr1].name != NULL && heap[addr2].name != NULL);
    return (strcmp(heap[addr1].name, heap[addr2].name) == 0);
}

static inline char STRING_REF(int addr, int k)
{
    REQUIRE(CELLRANGE(addr) &&
	    (GET_TAG(addr) == STR || GET_TAG(addr) == SYM ||
	     (GET_TAG(addr) == CHR && k == 0)) && heap[addr].name != NULL);
    return heap[addr].name[k];
}

static inline void STRING_SET(int addr, int k, char c)
{
    REQUIRE(CELLRANGE(addr) &&
	    GET_TAG(addr) == STR && heap[addr].name != NULL);
    heap[addr].name[k] = c;
}

static inline int GET_VEC_ELT(int addr, int i)
{
    REQUIRE(CELLRANGE(addr) &&
	    (GET_TAG(addr) == VEC || GET_TAG(addr) == ARR) &&
	    heap[addr].val.car.dyna_vec != NULL);
    return heap[addr].val.car.dyna_vec[i];
}

static inline void SET_VEC_ELT(int addr, int i, int x)
{
    REQUIRE(CELLRANGE(addr) &&
	    (GET_TAG(addr) == VEC || GET_TAG(addr) == ARR) &&
	    heap[addr].val.car.dyna_vec != NULL);
    heap[addr].val.car.dyna_vec[i] = x;
}

static inline void SET_VEC(int addr, int *x)
{
    REQUIRE(CELLRANGE(addr) &&
	    (GET_TAG(addr) == VEC || GET_TAG(addr) == ARR));
    heap[addr].val.car.dyna_vec = x;
}

static inline int IDX2C(int i, int j, int ld)
{
    return (j * ld + i);
}

static inline int IDX2R(int i, int j, int ld)
{
    return (i * ld + j);
}

static inline void append_str(int output_stream, const char *from)
{
    char *to = GET_NAME(output_stream);
    strncat(to, from, STRSIZE - strlen(to) - 1);
    to[STRSIZE - 1] = '\0';
    SET_PROP(output_stream, GET_PROP(output_stream) + strlen(from));
}

static inline void output_str(int output_stream, const char *from)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	fputs(from, GET_PORT(output_stream));
    } else {
	append_str(output_stream, from);
    }
}

static inline void output_char(int output_stream, char c)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	fputc(c, GET_PORT(output_stream));
    } else {
	stream_str[0] = c;
	stream_str[1] = '\0';
	append_str(output_stream, stream_str);
    }
}

// object oriented
extern int generic_func;
extern int generic_vars;
extern int next_method;
extern int generic_list;


// flag
extern int gArgC;
extern char **gArgV;
extern bool gbc_flag;
extern int genint;
extern bool simp_flag;
extern bool ignore_flag;
extern bool open_flag;
extern bool top_flag;
extern bool redef_flag;
extern bool start_flag;
extern bool back_flag;
extern bool ignore_topchk;
#ifdef WITHOUT_CURSES
#define repl_flag false
#else
extern bool repl_flag;
extern bool org_repl_flag;
#endif
extern bool option_flag;
extern volatile sig_atomic_t exit_flag;
extern bool greeting_flag;
extern bool script_flag;
extern bool handling_resource_err;
extern bool looking_for_shebang;
extern bool multiple_call_next_method;
extern bool error_flag;

// try function
extern bool try_flag;
extern double try_timer;
extern int try_res;

// switch
extern int gc_sw;
extern int area_sw;

// longjmp control and etc
extern Except_T Restart_Repl, Exit_Interp;
extern jmp_buf block_buf[CTRLSTK];
extern jmp_buf catch_buf[CTRLSTK];
extern jmp_buf cont_buf;
extern Except_T Ignored_Error;	// for ignore-errors
extern int block_tag_check[CTRLSTK];
extern int block_data[CTRLSTK][3];
extern int catch_data[CTRLSTK][3];
extern int unwind_buf[CTRLSTK];
extern int block_pt;		// pointer for block
extern int catch_pt;		// catch counter
extern int unwind_pt;		// lambda address for unwind-protect
extern int block_arg;		// argument that block will recieve
extern int catch_arg;		// argument that catch will recieve
extern int cont_arg;        // argument that signal_condition will recieve
extern int tagbody_tag;		// tag symbol address in tagbody
extern int error_handler;
extern int error_handler1;
extern int trace_list;
extern int backtrace[BACKSIZE];
extern int unwind_nest;
extern int ed_lparen_col;
extern int ed_rparen_col;
extern const char *ed_candidate[COMPLETION_CANDIDATES_MAX];
extern int ed_candidate_pt;
extern const short ed_syntax_color;
extern const short ed_builtin_color;
extern const short ed_extended_color;
extern const short ed_string_color;
extern const short ed_comment_color;
extern int ed_incomment;

// -------error code---
enum {
    UNDEF_VAR = 101,
    UNDEF_FUN,
    NOT_COMPUTABLE,
    OUT_OF_RANGE,
    MALLOC_OVERF,
    UNDEF_CLASS,
    WRONG_ARGS,
    NOT_NUM,
    NOT_STR,
    NOT_LIST,
    NOT_SYM,
    ILLEGAL_INPUT,
    NOT_FUNC,
    UNDEF_TAG,
    CANT_OPEN,
    ILLEGAL_ARGS,
    NOT_VEC,
    NOT_ARR,
    NOT_CLASS,
    NOT_METHOD,
    NOT_CONS,
    CANT_MODIFY,
    NOT_INT,
    NOT_STREAM,
    NOT_STREAM_ERROR,
    NOT_OUT_STREAM,
    NOT_IN_STREAM,
    NOT_CHAR,
    NOT_FLT,
    NOT_INSTANCE,
    CTRL_OVERF,
    ILLEGAL_RPAREN,
    END_STREAM,
    ILLEGAL_FORM,
    IMPROPER_FORM,
    DIV_ZERO,
    NOT_VECARR,
    CANT_CREATE,
    CANT_PARSE,
    CANT_ASSURE,
    NOT_EXIST_METHOD,
    HAS_COMMON_CLASS,
    ILLEGAL_CLASS,
    NOT_TOP_LEVEL,
    NOT_POSITIVE,
    FLT_OVERF,
    FLT_UNDERF,
    CANT_REDEFINE,
    STACK_OVERF,
    SHELTER_OVERF,
    STACK_UNDERF,
    SHELTER_UNDERF,
    SYSTEM_ERR,
    RESOURCE_ERR,
    NOT_EXIST_ARG,
    IMPROPER_ARGS,
    OUT_OF_DOMAIN,
    FLT_OUT_OF_DOMAIN,
    OUT_OF_REAL,
    NOT_BASIC_ARRAY,
    SERIOUS_ERR,
    ARITHMETIC_ERR,
    DOMAIN_ERR,
    UNDEF_DYN,
    UNDEF_ENTITY,
    SIMPLE_ERR,
    EXHAUSTED_ERR,
    DYNAMIC_OVERF,
};

double getETime(void);
int readc(void);
int absolute(int x);
int add_dyn_env(int sym, int val);
int add_sym(const char *name, int index);
int adaptp(int varlist, int arglist);
int angle(int y, int x);
int append(int x, int y);
int apply(int func, int arg);
int arg_push(int addr);
int arg_pop(void);
int array(int n, int ls);
int array_dim(int n, int ls);
int array_length(int obj);
int array_ref(int obj, int ls);
int array_set(int obj, int ls, int val);
int arrayp(int addr);
int assoc(int sym, int lis);
int assoc_list_p(int ls);
int assq(int x, int y);
int atomp(int addr);
int bignump(int x);
int bignum_token(char buf[]);
int big_abs(int x);
int big_big_to_flt(int x);
int big_eqp(int x, int y);
int big_first_half(int x);
int big_flt_to_big(int x);
int big_int_to_big(int x);
int big_karatsuba_mult(int x, int y);
int big_karatsuba_mult1(int x, int y);
int big_length(int x);
int big_long_to_big(int x);
int big_minus(int arg1, int arg2);
int big_minus1(int arg1, int arg2);
int big_mult(int arg1, int arg2);
int big_mult_i(int x, int y);
int big_mult1(int arg1, int arg2);
int big_ntt_mult(int x, int y);
int big_negativep(int x);
int big_plus(int arg1, int arg2);
int big_plus1(int arg1, int arg2);
int big_positivep(int x);
int big_div(int arg1, int arg2);
int big_div_i(int x, int y);
int big_div1(int arg1, int arg2);
int big_remainder(int x, int y);
int big_remainder_i(int x, int y);
int big_second_half(int x);
int big_shift_left(int x, int n);
int big_shift_right(int x, int n);
int big_simplify(int x);
int big_smallerp(int arg1, int arg2);
int big_take_from_left(int x, int n);
int big_to_parmanent(int x);
int big_zero_supress(int x, int n);
int bind_args(int x);
int bin_token(char buf[]);
int binary_input_stream_p(int x);
int binary_output_stream_p(int x);
int caar(int addr);
int cadar(int addr);
int caddar(int addr);
int caddr(int addr);
int cadr(int addr);
int car(int addr);
int cdar(int addr);
int cdddr(int addr);
int cddr(int addr);
int cdr(int addr);
int charp(int x);
int check_dimension(int ls);
int classp(int x);
int class_symbol_p(int x);
int cons(int car, int cdr);
int cons_next(int x, int y);
int cons_prev(int x, int y);
int copy(int x);
int copy_work(int x);
int copy_heap(int x);
int copy_symbol(int x);
int copy_int(int x);
int copy_long(int x);
int copy_flt(int x);
int copy_vec(int x);
int copy_array(int x);
int copy_str(int x);
int copy_char(int x);
int copy_func(int x);
int copy_generic(int x);
int copy_macro(int x);
int copy_stream(int x);
int copy_class(int x);
int copy_bignum(int x);
int copy_cons_next(int x, int y);
int copy_gen_big(void);
int count_args(int ls);
int create_array(int x);
int create_list(int x, int y);
int dec_token(char buf[]);
int divide(int arg1, int arg2);
int duplicate_list_p(int ls);
int each_car(int x);
int each_cdr(int x);
int eqgreaterp(int x, int y);
int eqlp(int addr1, int addr2);
int eqp(int addr1, int addr2);
int eqsmallerp(int x, int y);
int equalp(int addr1, int addr2);
int eval(int addr);
int evlis(int addr);
int exact_to_inexact(int x);
int expt(int x, int y);
int expt_token(char buf[]);
int f_abs(int arglist);
int f_address(int arglist);
int f_and(int arglist);
int f_append(int arglist);
int f_apply(int arglist);
int f_aref(int arglist);
int f_arithmetic_error_operands(int arglist);
int f_arithmetic_error_operation(int arglist);
int f_array_dimensions(int arglist);
int f_assoc(int arglist);
int f_assure(int arglist);
int f_atan(int arglist);
int f_atan2(int arglist);
int f_atanh(int arglist);
int f_atomp(int arglist);
int f_basic_array_p(int arglist);
int f_basic_array_star_p(int arglist);
int f_basic_vector_p(int arglist);
int f_debug(int arglist);
int f_block(int arglist);
int f_break(int arglist);
int f_call_next_method(int arglist);
int f_car(int arglist);
int f_case(int arglist);
int f_case_using(int arglist);
int f_catch(int arglist);
int f_cdr(int arglist);
int f_ceiling(int arglist);
int f_cerror(int arglist);
int f_char_eqgreaterp(int arglist);
int f_char_eqp(int arglist);
int f_char_eqsmallerp(int arglist);
int f_char_greaterp(int arglist);
int f_char_index(int arglist);
int f_char_noteqp(int arglist);
int f_char_smallerp(int arglist);
int f_characterp(int arglist);
int f_class(int arglist);
int f_class_of(int arglist);
int f_close(int arglist);
int f_cond(int arglist);
int f_condition_continuable(int arglist);
int f_cons(int arglist);
int f_consp(int arglist);
int f_continue_condition(int arglist);
int f_convert(int arglist);
int f_cos(int arglist);
int f_cosh(int arglist);
int f_create_array(int arglist);
int f_create_list(int arglist);
int f_create_star(int arglist);
int f_create_string(int arglist);
int f_create_string_input_stream(int arglist);
int f_create_string_output_stream(int arglist);
int f_create_vector(int arglist);
int f_defclass(int arglist);
int f_defconstant(int arglist);
int f_defdynamic(int arglist);
int f_defgeneric(int arglist);
int f_defgeneric_star(int arglist);
int f_defglobal(int arglist);
int f_defmacro(int arglist);
int f_defmethod(int arglist);
int f_defmodule(int arglist);
int f_defun(int arglist);
int f_div(int arglist);
int f_domain_error_expected_class(int arglist);
int f_domain_error_object(int arglist);
int f_dummyp(int arglist);
int f_dynamic(int arglist);
int f_dynamic_let(int arglist);
int f_eisl_test(int arglist);
int f_elt(int arglist);
int f_eq(int arglist);
int f_eqgreater(int arglist);
int f_eql(int arglist);
int f_eqsmaller(int arglist);
int f_equal(int arglist);
int f_error(int arglist);
int f_error_output(int arglist);
int f_eval(int arglist);
int f_exp(int arglist);
int f_expt(int arglist);
int f_file_length(int arglist);
int f_file_position(int arglist);
int f_finish_output(int arglist);
int f_flet(int arglist);
int f_float(int arglist);
int f_floatp(int arglist);
int f_floor(int arglist);
int f_for(int arglist);
int f_format(int arglist);
int f_format_char(int arglist);
int f_format_float(int arglist);
int f_format_fresh_line(int arglist);
int f_format_integer(int arglist);
int f_format_object(int arglist);
int f_format_tab(int arglist);
int f_funcall(int arglist);
int f_function(int arglist);
int f_function_star(int arglist);
int f_functionp(int arglist);
int f_funcp(int arglist);
int f_garef(int arglist);
int f_gbc(int arglist);
int f_gcd(int arglist);
int f_general_array_star_p(int arglist);
int f_general_vector_p(int arglist);
int f_generic_function_p(int arglist);
int f_gensym(int arglist);
int f_get_internal_real_time(int arglist);
int f_get_internal_run_time(int arglist);
int f_get_myself(int arglist);
int f_get_output_stream_string(int arglist);
int f_get_universal_time(int arglist);
int f_go(int arglist);
int f_getenv(int arglist);
int f_greater(int arglist);
int f_heapdump(int arglist);
int f_identity(int arglist);
int f_if(int arglist);
int f_ignore_errors(int arglist);
int f_import(int arglist);
int f_initialize_object_star(int arglist);
int f_input_stream_p(int arglist);
int f_instance(int arglist);
int f_instancep(int arglist);
int f_integerp(int arglist);
int f_internal_time_units_per_second(int arglist);
int f_isqrt(int arglist);
int f_labels(int arglist);
int f_lambda(int arglist);
int f_lcm(int arglist);
int f_length(int arglist);
int f_let(int arglist);
int f_letstar(int arglist);
int f_list(int arglist);
int f_listp(int arglist);
int f_load(int arglist);
int f_log(int arglist);
int f_macroexpand_1(int arglist);
int f_macroexpand_all(int arglist);
int f_map_into(int arglist);
int f_mapc(int arglist);
int f_mapcan(int arglist);
int f_mapcar(int arglist);
int f_mapcon(int arglist);
int f_mapl(int arglist);
int f_maplist(int arglist);
int f_max(int arglist);
int f_member(int arglist);
int f_min(int arglist);
int f_minus(int arglist);
int f_mod(int arglist);
int f_mult(int arglist);
int f_nconc(int arglist);
int f_next_method_p(int arglist);
int f_not(int arglist);
int f_notnumeqp(int arglist);
int f_nreverse(int arglist);
int f_nullp(int arglist);
int f_numberp(int arglist);
int f_numeqp(int arglist);
int f_open_input_file(int arglist);
int f_open_io_file(int arglist);
int f_open_output_file(int arglist);
int f_open_stream_p(int arglist);
int f_or(int arglist);
int f_output_stream_p(int arglist);
int f_parse_error_expected_class(int arglist);
int f_parse_error_string(int arglist);
int f_parse_number(int arglist);
int f_plus(int arglist);
int f_preview_char(int arglist);
int f_print(int arglist);
int f_probe_file(int arglist);
int f_prof(int arglist);
int f_progn(int arglist);
int f_property(int arglist);
__dead int f_quit(int arglist);
int f_quotient(int arglist);
int f_random_real(int arglist);
int f_random(int arglist);
int f_set_random(int arglist);
int f_read(int arglist);
int f_read_byte(int arglist);
int f_read_char(int arglist);
int f_read_line(int arglist);
int f_reciprocal(int arglist);
int f_read_exp(int arglist);
int f_remove_property(int arglist);
int f_return_from(int arglist);
int f_reverse(int arglist);
int f_round(int arglist);
int f_set_aref(int arglist);
int f_set_car(int arglist);
int f_set_cdr(int arglist);
int f_set_dynamic(int arglist);
int f_set_elt(int arglist);
int f_set_file_position(int arglist);
int f_set_garef(int arglist);
int f_set_property(int arglist);
int f_set_slot_value(int arglist);
int f_setf(int arglist);
int f_setq(int arglist);
int f_signal_condition(int arglist);
int f_simple_error_format_arguments(int arglist);
int f_simple_error_format_string(int arglist);
int f_sin(int arglist);
int f_sinh(int arglist);
int f_slot_value(int arglist);
int f_smaller(int arglist);
int f_sqrt(int arglist);
int f_standard_input(int arglist);
int f_standard_output(int arglist);
int f_stream_error_stream(int arglist);
int f_stream_ready_p(int arglist);
int f_streamp(int arglist);
int f_string_append(int arglist);
int f_string_eqgreaterp(int arglist);
int f_string_eqp(int arglist);
int f_string_eqsmallerp(int arglist);
int f_string_greaterp(int arglist);
int f_string_index(int arglist);
int f_string_noteqp(int arglist);
int f_string_smallerp(int arglist);
int f_stringp(int arglist);
int f_subclassp(int arglist);
int f_subseq(int arglist);
int f_modulesubst(int arglist);
int f_symbolp(int arglist);
int f_tagbody(int arglist);
int f_tan(int arglist);
int f_tanh(int arglist);
int f_the(int arglist);
int f_throw(int arglist);
int f_time(int arglist);
int f_trace(int arglist);
int f_truncate(int arglist);
int f_try(int arglist);
int f_undefined_entity_name(int arglist);
int f_undefined_entity_namespace(int arglist);
int f_untrace(int arglist);
int f_unwind_protect(int arglist);
int f_vector(int arglist);
int f_while(int arglist);
int f_with_error_output(int arglist);
int f_with_handler(int arglist);
int f_with_open_input_file(int arglist);
int f_with_open_io_file(int arglist);
int f_with_open_output_file(int arglist);
int f_with_standard_input(int arglist);
int f_with_standard_output(int arglist);
int f_write_byte(int arglist);
int f_line_argument(int arglist);
int find_return_from_p(int x);
int find_dyn(int sym);
int find_env(int sym);
int flatten(int n, int ls);
int floatp(int x);
int flt_token(char buf[]);
int fprintr(FILE * p, int r, int n);
int freshcell(void);
int fsubrp(int addr);
int functionp(int addr);
int gbcsw(void);
int gcd(int x, int y);
int get_error_flag(void);
int get_error_handler(void);
int getwp(void);
int gen_big(void);
int gen_n(int n);
int genericp(int addr);
int genlamlis_to_lamlis(int varlist);
int get_msb(int x);
int get_nth(int x, int n);
int get_sign(int x);
int get_length(int x);
int get_pointer(int x);
int get_sym(const char *name, int index);
int greaterp(int x, int y);
int has_common_p(int ls);
int has_common_p1(int x, int y);
int has_danger_p(int x);
int hash(const char *name);
int has_multiple_call_next_method_p(int x);
int has_multiple_call_next_method_p1(int x);
int has_multiple_call_next_method_p2(int x);
int has_same_p(int ls);
int has_sys_class_p(int ls);
int hcons(int x, int y);
int happend(int x, int y);
int hreverse(int x);
int hlist1(int x);
int hex_token(char buf[]);
int hfreshcell(void);
int high_priority_p(int x, int y);
int illegal_lambda_p(int ls);
int improper_list_p(int ls);
int includep(int x, int y);
int initinst(int x, int initls);
int initinst1(int ls, int sc, int initls);
int initinst2(int inst_vars, int class_vars, int initls);
int input_stream_p(int x);
int indomainp(int ls);
int inrangep(int x, int y);
int int_gcd(int x, int y);
int integerp(int x);
int intlcm(int x, int y);
int int_token(char buf[]);
int int_token_nsgn(char buf[]);
int isqrt(int x);
int is_symbol_char(char c);
int ILOSerror(int fun, int arg);
int last(int x);
int last_str(char buf[]);
int lcm(int x, int y);
int length(int addr);
char *library_file(const char *basename);
int list(int addr);
int list_drop(int ls, int n);
int list_take(int ls, int n);
int list1(int x);
int list10(int x1, int x2, int x3, int x4, int x5, int x6,
	   int x7, int x8, int x9, int x10);
int list11(int x1, int x2, int x3, int x4, int x5, int x6,
	   int x7, int x8, int x9, int x10, int x11);
int list2(int x, int y);
int list3(int x, int y, int z);
int list4(int x1, int x2, int x3, int x4);
int list6(int x1, int x2, int x3, int x4, int x5, int x6);
int list8(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8);
int listcopy(int x);
int listp(int addr);
int listref(int lis, int n);
int listref1(int lis, int n);
int long_int_div(int x, int y);
int long_int_remainder(int x, int y);
int long_long_div(int x, int y);
int long_long_remainder(int x, int y);
int longnump(int x);
int macroexpand_1(int macsym, int args);
int macroexpand_all(int sexp);
int macrop(int addr);
int make_arr(int lis, int obj);
int make_big(char *bignum);
int make_char(const char *pname);
int make_class(const char *pname, int superclass);
int make_dummy(void);
int make_double_flt(double x);
int make_flt(double floatn);
int make_func(const char *pname, int addr);
int make_generic(char *pname, int lamlist, int body);
int make_generic_star(int lamlist, int body);
int make_instance(int cl, int ls);
int make_int(int intn);
int make_long(long long int x);
int make_method(int x);
int makenum(int num);
int make_str(const char *string);
int make_stm(FILE * port, int type, const char *name);
int make_sym(const char *pname);
int make_sym1(const char *pname);
int makeusercond(int cl, int str, int arg);
int make_vec(int n, int obj);
int mapc(int x, int y);
int mapcan(int x, int y);
int mapcar(int x, int y);
int mapcon(int x, int y);
int mapl(int x, int y);
int maplist(int x, int y);
int maplist1(int y);
int map_into_thunk(int x, int y);
int map_into_to_list(int x);
int matchp(int varlist, int arglist);
int math_integerp(int x);
int member(int x, int y);
int member1(int x, int y, int z);
int method_qualifier_p(int x);
int minus(int arg1, int arg2);
int modulesubst(int x, int module, int fname);
int modulesubst1(int x, int module);
int modulesubst_case(int addr, int module, int fname);
int mult(int arg1, int arg2);
int nconc(int x, int y);
int negative_zerop(int x);
int negativep(int x);
int next(int x);
int not_exist_class_p(int ls);
int nreverse(int x);
int nullp(int addr);
int numberp(int addr);
int numeqp(int x, int y);
int oct_token(char buf[]);
int output_stream_p(int x);
int plus(int arg1, int arg2);
int pop(void);
int positive_zerop(int x);
int positivep(int x);
int prev(int x);
int push(int x);
int quasi_transfer(int x, int n);
int quotient(int x, int y);
int set_error_flag(int x);
int signal_condition(int x, int y);
int sread(void);
int read_list(void);
int read_bin(char *buf);
int read_oct(char *buf);
int read_hex(char *buf);
int remove_list(int x, int y);
int remove_prop(int x, int lis);
int restore_error_handler(void);
int reverse(int x);
int set_dyn_env(int sym, int val);
int set_error_handler(int x);
int shelter_pop(void);
int s_remainder(int x, int y);
int slotvars(int cl);
int smallerp(int x, int y);
int sprintr(char *str, int r, int n);
int streamp(int x);
int string_input_stream_p(int x);
int string_length(int x);
int string_ref(int x, int y);
int string_set(int x, int y, int z);
int string_to_list(int x);
int string_to_vector(int x);
int stringp(int x);
int structured(int ls, int st);
int structured1(int ls, int st);
int structured2(int ls, int n);
int subclassp(int x, int y);
int subclassp1(int x, int y);
int sublis(int x, int s, int e);
int subrp(int addr);
int substr(int x, int s, int e);
int subvec(int x, int s, int e);
int symbol_list_p(int ls);
int symbolp(int addr);
int symbol_token(char buf[]);
int symnamep(int addr, char *name);
int superp(int x, int y);
int text_input_stream_p(int x);
int text_output_stream_p(int x);
int undef_parameter_p(int ls);
int unified_parameter_p(int lamlis, int ls);
int utf8_to_ucs4(char *p);
int vec_minus(int x, int y);
int vec_plus(int x, int y);
int vector(int lis);
int vector_length(int x);
int vector_ref(int v, int n);
int vector_to_list(int x);
int vectorp(int x);
int zerop(int addr);
septoken separater(char buf[], char sep);
void add_lex_env(int sym, int val);
void big_gbc(int x);
void big_minus2(int arg, int c, int msb);
void big_plus2(int arg, int c, int msb);
void bind_arg(int lambda, int arglist);
void bind_class(const char *name, int cl);
void bind_const(const char *name, int obj);
void bind_func(const char *name, tag_t tag, int (*func)(int));
void bind_macro(char *name, int addr);
void cellprint(int addr);
int check_gbc(void);
void clr_cell(int addr);
void copy_gbc(void);
void copy_hash(int x);
void cut_zero(int x);
void def_fsubr(const char *symname, int (*func)(int));
void def_subr(const char *symname, int (*func)(int));
void drop_char(char buf[]);
void error(int errnum, const char *fun, int arg);
int gbc(void);
void gbc_mark(void);
void gbc_sweep(void);
void get_token(void);
void heapdump(int start, int end);
void init_cell(void);
void init_class(void);
void init_err_args(int cl);
void init_exsubr(void);
void init_generic(void);
void init_pointer(void);
void init_stream(void);
void init_subr(void);
void init_syntax(void);
void insert_method(int x, int func);
void insert_str(char ch, char buf[]);
void mark_cell(int addr);
void print(int addr);
void print_big(int x);
void print_arr(int x);
void print_char(int addr);
void print_class(int x);
void print_flt(double x);
void print_int(int x);
void print_list(int addr);
void print_long(int x);
void print_obj(const char *str);
void print_str(int addr);
void print_stm(int x);
void print_sym(int x);
void print_vec(int addr);
void profiler(int sym, double time);
void profiler_clear();
void profiler_set(int sw);
void profiler_print();
void redef_generic(void);
void resort_method(int func);
void set_sign(int x, int y);
void set_length(int x, int len);
void set_pointer(int x, int pointer);
void set_lex_env(int sym, int val);
void set_val(int sym, int val, int ls);
void signal_handler_c(int signo);
void unbind(void);
void unreadc(char c);
void ucs4_to_utf8(int n, char *p);
void vector_set(int v, int n, int obj);
void store_backtrace(int x);

int f_backtrace(int arglist);
int f_symbol_function(int arglist);
int f_symbol_class(int arglist);

void setcolor(short n);
int eisl_getch(void);
int f_edit(int arglist);
#ifdef __rpi__
int f_wiringpi_setup_gpio(int arglist);
int f_wiringpi_spi_setup_ch_speed(int arglist);
int f_pwm_set_mode(int arglist);
int f_pwm_set_range(int arglist);
int f_pwm_set_clock(int arglist);
int f_pin_mode(int arglist);
int f_digital_write(int arglist);
int f_digital_write_byte(int arglist);
int f_pwm_write(int arglist);
int f_pull_up_dn_control(int arglist);
int f_digital_read(int arglist);
int f_delay(int arglist);
int f_delay_microseconds(int arglist);
#endif

void debugger(void);
void ntt_test();

// Fast project
int a_adaptp(int x, int y);
int a_matchp(int x, int y);
int shelter_push(int addr);
int shelter_pop(void);
int freecell(void);
int get_int(int addr);
long long int get_long(int addr);
int nth(int n, int addr);
int f_freedll(int arglist);
int f_system(int arglist);
void dynamic_link(int x);
int set_car(int x, int y);
int set_cdr(int x, int y);
int set_aux(int x, int y);
int set_opt(int x, int y);
int call_subr(int func, int arglist);
int f_subrp(int arglist);
int make_int_long(int n);
int make_str_flt(const char *str);
int make_double_flt(double x);
int make_str_long(const char *str);
int make_fast_str_long(const char *str);
int nth_cdr(int n, int x);
int f_macrop(int arglist);
int f_fixnump(int arglist);
int f_longnump(int arglist);
int f_bignump(int arglist);
int convert(int arg1, int arg2);
int get_aux(int x);
int f_readed_array_list(int arglist);
int f_get_method(int arglist);
int f_get_method_body(int arglist);
int f_get_method_priority(int arglist);
int f_ignore_toplevel_check(int arglist);
int fast_length(int x);
int fast_car(int x);
int fast_cdr(int x);
int f_self_introduction(int arglist);
int set_dynamic(int x, int y);
int set_prop(int x, int y);
int get_prop(int x);
int get_opt(int x);
int get_dynpt();
int set_dynpt(int x);
int set_catch_symbols(int x);
int f_ignore(int arglist);
int f_classp(int arglist);
int f_superp_for_compiler(int arglist);
char *get_name(int x);
double get_flt(int x);


void display_buffer(void);
enum HighlightToken check_token_buffer(int col);
int find_lparen_buffer(int col);
int find_rparen_buffer(int col);
void emphasis_lparen_buffer(int col, int uni_col);
void emphasis_rparen_buffer(int col, int uni_col);
void reset_paren_buffer();
void restore_paren_buffer(int col);
char *get_fragment_buffer(int col);
void find_candidate_buffer(int col);
int replace_fragment_buffer(const char *newstr, int col);
void insertcol_buffer(int col);
void backspace_buffer(int col);
int read_line(int flag);


#endif
