/* Easy-ISLisp (ISLisp)
written by kenichi sasagawa 2016/4
*/
/*
memory map
M&S GC mode
address
0        -  19999999  Heap area

Copying GC mode
       0 -   5999999  Heap area
 6000000 -  12999999  Work1 area
12999999 -  19999999  Wrok2 area
*/
#include <setjmp.h>
#define VERSION     1.66
#define HEAPSIZE    20000000
#define CELLSIZE    20000000
#define WORK1        6000000
#define WORK2       13000000
#define FREESIZE    900
#define STACKSIZE   300000
#define SYMSIZE     32
#define BUFSIZE     256
#define STRSIZE     500000
#define CHARSIZE    2   //ascii char. add \0 to tail
#define MATSIZE     256
#define NIL         0
#define T           2
#define UNDEF       4
#define FEND        6
#define HASHTBSIZE  107
#define BIGNUM_BASE 1000000000
#define SMALL_INT_MAX       1000000000
#define SMALL_INT_MIN       -1000000000
#define INT_FLAG    1073741824 //#b1000000000000000000000000000000
#define INT_MASK    1073741823 //#b0111111111111111111111111111111
#define PI          3.141592653589793
#define CTRLSTK     200
#define BACKSIZE    30

typedef enum {EMP,INTN,FLTN,LONGN,BIGX,VEC,ARR,CHR,STR,SYM,LIS,DUMMY,
              SUBR,FSUBR,FUNC,MACRO,CLASS,INSTANCE,GENERIC,METHOD,
              STREAM} tag;
typedef enum {FRE,USE} flag;


typedef enum {AROUND,BEFORE,PRIORITY,AFTER,EISL_OPEN,EISL_INPUT,EISL_OUTPUT,EISL_INSTR,EISL_OUTSTR} option;


typedef struct{
    union{
        double fltnum;
        long long int lngnum;
        struct {
            union{
                int intnum;
                int     ( *subr) ();
                FILE    *port;
                int     *dyna_vec;
            } car;
            union{
                int intnum;
            } cdr;
        };
    } val;
    int     aux;
    int     prop;
    char    *name;
    char    tag;
    char    flag;
    signed char    option;
    char    trace;
} cell;


typedef enum {LPAREN,RPAREN,QUOTE,DOT,BACKQUOTE,COMMA,ATMARK,STRING,SYMBOL,
              FUNCTION,INTEGER,FLOAT_N,BIGNUM,VECTOR,ARRAY,CHARACTER,
              BINARY,OCTAL,DECNUM,HEXNUM,EXPTNUM,FILEEND,OTHER} toktype;
typedef enum {GO,BACK} backtrack;

typedef struct{
    char ch;
    backtrack flag;
    toktype type;
    char buf[BUFSIZE];
} token;

typedef struct{
    char sepch;
    char before[BUFSIZE];
    char after[BUFSIZE];
} septoken;


struct position{
    int row;
    int col;
};


#define DEBUG               printf("debug\n"); longjmp(buf,2);
#define GET_FLT(addr)       heap[addr].val.fltnum
#define GET_CAR(addr)       heap[addr].val.car.intnum
#define GET_CDR(addr)       heap[addr].val.cdr.intnum
#define GET_AUX(addr)       heap[addr].aux
#define GET_PROP(addr)      heap[addr].prop
#define GET_SUBR(addr)      heap[addr].val.car.subr
#define GET_PORT(addr)      heap[addr].val.car.port
#define GET_INT(addr)       heap[addr].val.car.intnum
#define GET_FLT(addr)       heap[addr].val.fltnum
#define GET_LONG(addr)      heap[addr].val.lngnum
#define GET_NAME(addr)      heap[addr].name
#define GET_NAME_ELT(addr,n)    heap[addr].name[n]
#define GET_CHAR(addr)      heap[addr].name[0]
#define GET_TR(addr)        heap[addr].trace
#define GET_TAG(addr)       heap[addr].tag
#define GET_CAR(addr)       heap[addr].val.car.intnum
#define GET_OPT(addr)       heap[addr].option
#define GET_FLAG(addr)      heap[addr].flag
#define SET_TAG(addr,x)     heap[addr].tag = x
#define SET_CAR(addr,x)     heap[addr].val.car.intnum = x
#define SET_CDR(addr,x)     heap[addr].val.cdr.intnum = x
#define SET_AUX(addr,x)     heap[addr].aux = x
#define SET_PROP(addr,x)    heap[addr].prop = x
#define SET_INT(addr,x)     heap[addr].val.car.intnum = x
#define SET_FLT(addr,x)     heap[addr].val.fltnum = x
#define SET_LONG(addr,x)    heap[addr].val.lngnum = x
#define SET_CAR(addr,x)     heap[addr].val.car.intnum = x
#define SET_SUBR(addr,x)    heap[addr].val.car.subr = x
#define SET_PORT(addr,x)    heap[addr].val.car.port = x
#define SET_OPT(addr,x)     heap[addr].option = x
#define SET_FLAG(addr,x)    heap[addr].flag = x
#define SET_CHAR(addr,x)    heap[addr].name[0] = x
#define SET_NAME(addr,x)    heap[addr].name = x
#define SET_TR(addr,x)      heap[addr].trace = x
#define SET(addr,x)         heap[addr] = heap[x]
#define IS_SYMBOL(addr)     heap[addr].tag == SYM
#define IS_INTEGER(addr)    heap[addr].tag == INTN
#define IS_BIGXNUM(addr)    heap[addr].tag == BIGX
#define IS_LONGNUM(addr)    heap[addr].tag == LONGN
#define IS_FLOAT(addr)      heap[addr].tag == FLTN
#define IS_LIST(addr)       heap[addr].tag == LIS
#define IS_STRING(addr)     heap[addr].tag == STR
#define IS_CHARACTER(addr)  heap[addr].tag == CHR
#define IS_NIL(addr)        (addr == 0)
#define IS_T(addr)          (addr == 2)
#define IS_VECTOR(addr)     heap[addr].tag == VEC
#define IS_ARRAY(addr)      heap[addr].tag == ARR
#define IS_SUBR(addr)       heap[addr].tag == SUBR
#define IS_FSUBR(addr)      heap[addr].tag == FSUBR
#define IS_FUNC(addr)       heap[addr].tag == FUNC
#define IS_MACRO(addr)      heap[addr].tag == MACRO
#define IS_EMPTY(addr)      heap[addr].tag  == EMP
#define IS_CLASS(addr)      heap[addr].tag == CLASS
#define IS_GENERIC(addr)    heap[addr].tag == GENERIC
#define IS_METHOD(addr)     heap[addr].tag == METHOD
#define IS_STREAM(addr)     heap[addr].tag == STREAM
#define IS_INSTANCE(addr)   heap[addr].tag == INSTANCE
#define HAS_NAME(addr,x)    strcmp(heap[addr].name,x) == 0
#define SAME_NAME(addr1,addr2) strcmp(heap[addr1].name, heap[addr2].name) == 0
#define GREATER_NAME(addr1,addr2) strcmp(heap[addr1].name, heap[addr2].name) > 0
#define SMALLER_NAME(addr1,addr2) strcmp(heap[addr1].name, heap[addr2].name) < 0
#define EQUAL_STR(x,y)      strcmp(x,y) == 0
#define EQUAL_STR(x,y)      strcmp(x,y) == 0
#define STRING_REF(addr,k)   heap[addr].name[k]
#define STRING_SET(addr,k,c) heap[addr].name[k] = c
#define MARK_CELL(addr)     heap[addr].flag = USE
#define NOMARK_CELL(addr)   heap[addr].flag = FRE
#define USED_CELL(addr)     heap[addr].flag == USE
#define FREE_CELL(addr)     heap[addr].flag == FRE

#define GET_VEC_ELT(addr,i)         heap[addr].val.car.dyna_vec[i]
#define SET_VEC_ELT(addr,i,x)       heap[addr].val.car.dyna_vec[i] = x
#define SET_VEC(addr,x)             heap[addr].val.car.dyna_vec = x
#define GET_VEC(addr)               heap[addr].val.car.dyna_vec

//------pointer----
extern int ep; //environment pointer
extern int dp; //dynamic pointer
extern int hp; //heap pointer
extern int sp; //stack pointer
extern int fc; //free counter
extern int ap; //arglist pointer
extern int lp; //shelter pointer
extern int wp; //working pointer

//------class-----
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
extern int cfixnum;
extern int clongnum;
extern int cbignum;

#define CLASS_SYMBOL    1


//stream
extern int standard_input;
extern int standard_output;
extern int standard_error;
extern int input_stream;
extern int output_stream;
extern int error_stream;
extern char stream_str[STRSIZE];
extern char stream_str1[STRSIZE];
extern int charcnt;


//read scaner
extern token stok;
extern int line;
extern int column;
extern int buffer[256][10];
extern int buffer1[256];


//heap and stack
extern cell heap[CELLSIZE];
extern int stack[STACKSIZE];
extern int argstk[STACKSIZE];
extern int cell_hash_table[HASHTBSIZE];
extern int shelter[STACKSIZE];

//object oriented
extern int generic_func;
extern int generic_vars;
extern int next_method;
extern int generic_list;


//flag
extern int gbc_flag;
extern int genint;
extern int simp_flag;
extern int ignore_flag;
extern int open_flag;
extern int str_flag;
extern int top_flag;
extern int redef_flag;
extern int start_flag;
extern int back_flag;
extern int ignore_topchk;
extern int repl_flag;
extern int exit_flag;
extern int debug_flag;
extern int greeting_flag;
extern int script_flag;

//switch
extern int gc_sw;
extern int area_sw;

//longjmp control
extern jmp_buf buf;
extern jmp_buf block_buf[50];
extern int block_env[50][2];
extern jmp_buf catch_buf[10][50];
extern int catch_env[10][50];
extern jmp_buf ignore_buf; //jump address for ignore-error
extern int block_tag[CTRLSTK]; //array to sotre tag address
extern int catch_tag[CTRLSTK];
extern int catch_symbols;
extern int block_pt;  //pointer for block
extern int catch_pt;  //catch counter
extern int unwind_pt; //lambda address for unwind-protect
extern int block_arg; //argument that block will recieve
extern int catch_arg; //argument that catch will recieve
extern int tagbody_tag; //tag symbol address in tagbody
extern int error_handler;
extern int trace_list;
extern int trace_sym;
extern int backtrace[BACKSIZE];


extern int ed_lparen_col;
extern int ed_rparen_col;
extern char ed_candidate[50][30];
extern int ed_candidate_pt;
extern int ed_syntax_color;
extern int ed_builtin_color;
extern int ed_extended_color;
extern int ed_string_color;
extern int ed_comment_color;
extern int ed_incomment;
extern char special[40][12];
extern char syntax[60][30];
extern char builtin[200][30];
extern char extended[50][30];



//option
#define CONSTN      1
#define IMMUTABLE   2
#define SYSTEM      3 //class of provided by system
#define USER        4 //class of user' definition
#define GLOBAL      5 //global variable
#define CONTINUABLE 6 //continuable condition
#define NOTCONT     7 //no continuable condition

//special charactor
#define EOL     '\n'
#define RET     '\r'
#define TAB     '\t'
#define SPACE   ' '
#define ESC     27
#define NUL     '\0'
#define BEL     '\a'
#define BS      '\b'
#define DEL     127

#if __linux
#define LEFT    'D'
#define UP          'A'
#define RIGHT   'C'
#define DOWN    'B'
#define INSERT  '2'
#define DELETE  '3'
#define PAGEUP  '5'
#define PAGEDN  '6'
#define HOME    'H'
#define END     'F'
#endif

//-------error code---
#define UNDEF_VAR       101
#define UNDEF_FUN       102
#define NOT_COMPUTABLE  103
#define OUT_OF_RANGE    104
#define MALLOC_OVERF    105
#define UNDEF_CLASS     106
#define WRONG_ARGS      107
#define NOT_NUM         108
#define NOT_STR         109
#define NOT_LIST        110
#define NOT_SYM         111
#define ILLEGAL_INPUT   112
#define NOT_FUNC        113
#define UNDEF_TAG       115
#define CANT_OPEN       116
#define ILLEGAL_ARGS    117
#define NOT_VEC         118
#define NOT_ARR         119
#define NOT_CLASS       120
#define NOT_METHOD      121
#define NOT_CONS        122
#define CANT_MODIFY     123
#define NOT_INT         124
#define NOT_STREAM      125
#define NOT_OUT_STREAM  126
#define NOT_IN_STREAM   127
#define NOT_CHAR        128
#define NOT_FLT         129
#define NOT_INSTANCE    130
#define CTRL_OVERF      131
#define ILLEGAL_RPAREN  133
#define END_STREAM      134
#define ILLEGAL_FORM    135
#define DIV_ZERO        136
#define NOT_VECARR      137
#define CANT_CREATE     138
#define CANT_PARSE      139
#define CANT_ASSURE     140
#define NOT_ARITHMETIC  141
#define NOT_EXIST_METHOD 142
#define HAS_COMMON_CLASS 143
#define NOT_TOP_LEVEL   144
#define NOT_POSITIVE    145
#define FLT_OVERF       146
#define FLT_UNDERF      147
#define CANT_REDEFINE   148
#define STACK_OVERF     149
#define SHELTER_OVERF	150
#define STACK_UNDERF	151
#define SHELTER_UNDERF	152
#define SYSTEM_ERR	    153
#define RESOURCE_ERR    154


#define ESCHOME printf("\33[1;1H")
#define ESCTOP  printf("\33[2;1H")
#define ESCCLS  printf("\33[2J")
#define ESCCLS1 printf("\33[0J")
#define ESCCLSL printf("\33[0K")
#define ESCCLSLA printf("\33[2K")
#define ESCMVLEFT(x) printf("\33[%dG", x)
#define ESCMVR  printf("\33[C")
#define ESCMVL  printf("\33[D")
#define ESCMVU  printf("\33[A")
#define ESCMVD  printf("\33[B")
#define ESCSCR  printf("\33[S")
#define ESCMVLN(x) printf("\33[%dD", x)
#define ESCMOVE(x,y)    printf("\33[%d;%df", x,y)
#define ESCFBLACK printf("\33[30m")
#define ESCFRED  printf("\33[31m")
#define ESCFGREEN printf("\33[32m")
#define ESCFYELLOW printf("\33[33m")
#define ESCFBLUE printf("\33[34m")
#define ESCFMAGENTA printf("\33[35m")
#define ESCFCYAN printf("\33[36m")
#define ESCFWHITE printf("\33[37m")
#define ESCFORG  printf("\33[39m")

#define ESCBCYAN printf("\33[46m")
#define ESCBORG  printf("\33[49m")
#define ESCREV  printf("\33[7m")
#define ESCRST  printf("\33[0m")
#define ESCBOLD printf("\33[1m")


double getETime(void);
int readc(void);
int absolute(int x);
int addsym(char *name, int index);
int angle(int x, int y);
int append(int x, int y);
int apply(int func, int arg);
int argpop(void);
int array(int n, int ls);
int array_dim(int n, int ls);
int array_length(int obj);
int array_ref(int obj, int ls);
int array_set(int obj, int ls, int val);
int arrayp(int addr);
int assoc(int sym, int lis);
int assoclistp(int ls);
int assq(int x, int y);
int atomp(int addr);
int bignump(int x);
int bignumtoken(char buf[]);
int bigx_abs(int x);
int bigx_big_to_flt(int x);
int bigx_eqp(int x, int y);
int bigx_flt_to_big(int x);
int bigx_greaterp(int arg1, int arg2);
int bigx_int_to_big(int x);
int bigx_length(int x);
int bigx_long_to_big(int x);
int bigx_minus(int arg1, int arg2);
int bigx_minus1(int arg1, int arg2);
int bigx_mult(int arg1, int arg2);
int bigx_mult_i(int x, int y);
int bigx_mult1(int arg1, int arg2);
int bigx_negativep(int x);
int bigx_plus(int arg1, int arg2);
int bigx_plus1(int arg1, int arg2);
int bigx_positivep(int x);
int bigx_div(int arg1, int arg2);
int bigx_div_i(int x, int y);
int bigx_div1(int arg1, int arg2);
int bigx_remainder_i(int x, int y);
int bigx_shift(int x, int n);
int bigx_simplify(int x);
int bigx_smallerp(int arg1, int arg2);
int bind_args(int x);
int bintoken(char buf[]);
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
int dectoken(char buf[]);
int divide(int arg1, int arg2);
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
int expttoken(char buf[]);
int f_abs(int x);
int f_address(int arglist);
int f_and(int addr);
int f_append(int addr);
int f_apply(int addr);
int f_aref(int x);
int f_arithmetic_error_operands(int arglist);
int f_arithmetic_error_operation(int arglist);
int f_array_dimensions(int x);
int f_assoc(int addr);
int f_assure(int arglist);
int f_atan(int x);
int f_atan2(int x);
int f_atanh(int x);
int f_atomp(int addr);
int f_basic_array_p(int x);
int f_basic_array_star_p(int arglist);
int f_basic_vector_p(int arglist);
int f_debug(int arglist);
int f_block(int x);
int f_break(int arglist);
int f_call_next_method(int arglist);
int f_car(int addr);
int f_case(int x);
int f_case_using(int x);
int f_catch(int x);
int f_cdr(int addr);
int f_ceiling(int x);
int f_cerror(int x);
int f_char_eqgreaterp(int x);
int f_char_eqp(int x);
int f_char_eqsmallerp(int x);
int f_char_greaterp(int x);
int f_char_index(int arglist);
int f_char_noteqp(int x);
int f_char_smallerp(int x);
int f_characterp(int addr);
int f_class(int x);
int f_class_of(int arglist);
int f_close(int x);
int f_cond(int addr);
int f_condition_continuable(int arglist);
int f_cons(int addr);
int f_consp(int addr);
int f_continue_condition(int arglist);
int f_convert(int arglist);
int f_cos(int addr);
int f_cosh(int x);
int f_create_array(int x);
int f_create_list(int addr);
int f_create_star(int x);
int f_create_string(int arglist);
int f_create_string_input_stream(int x);
int f_create_string_output_stream(int x);
int f_create_vector(int x);
int f_defclass(int x);
int f_defconstant(int addr);
int f_defdynamic(int addr);
int f_defgeneric(int x);
int f_defgeneric_star(int arglist);
int f_defglobal(int addr);
int f_defmacro(int addr);
int f_defmethod(int x);
int f_defun(int addr);
int f_div(int x);
int f_domain_error_expected_class(int arglist);
int f_domain_error_object(int arglist);
int f_dummyp(int arglist);
int f_dynamic(int addr);
int f_dynamic_let(int x);
int f_elt(int arglist);
int f_eq(int addr);
int f_eqgreater(int addr);
int f_eql(int addr);
int f_eqsmaller(int addr);
int f_equal(int addr);
int f_error(int x);
int f_error_output(int x);
int f_eval(int addr);
int f_exp(int x);
int f_expt(int x);
int f_file_length(int arglist);
int f_file_position(int arglist);
int f_finish_output(int x);
int f_flet(int arglist);
int f_float(int x);
int f_floatp(int addr);
int f_floor(int x);
int f_for(int x);
int f_format(int x);
int f_format_char(int x);
int f_format_float(int x);
int f_format_fresh_line(int arglist);
int f_format_integer(int x);
int f_format_object(int arglist);
int f_format_tab(int arglist);
int f_funcall(int addr);
int f_function(int addr);
int f_function_star(int addr);
int f_functionp(int addr);
int f_garef(int arglist);
int f_gbc(int addr);
int f_gcd(int x);
int f_general_array_star_p(int arglist);
int f_general_vector_p(int arglist);
int f_generic_function_p(int arglist);
int f_gensym(int addr);
int f_get_internal_real_time(int arglist);
int f_get_internal_run_time(int arglist);
int f_get_output_stream_string(int x);
int f_get_universal_time(int arglist);
int f_go(int x);
int f_greater(int addr);
int f_heapdump(int addr);
int f_identity(int arglist);
int f_if(int addr);
int f_ignore_errors(int arglist);
int f_initialize_object_star(int arglist);
int f_input_stream_p(int x);
int f_instance(int x);
int f_instancep(int x);
int f_integerp(int x);
int f_internal_time_units_per_second(int arglist);
int f_isqrt(int arglist);
int f_labels(int addr);
int f_lambda(int addr);
int f_lcm(int x);
int f_length(int addr);
int f_let(int addr);
int f_letstar(int addr);
int f_list(int addr);
int f_listp(int addr);
int f_load(int arglist);
int f_log(int x);
int f_logistic(int arglist);
int f_macroexpand_1(int arglist);
int f_map_into(int arglist);
int f_mapc(int addr);
int f_mapcan(int arglist);
int f_mapcar(int addr);
int f_mapcon(int x);
int f_mapl(int x);
int f_maplist(int addr);
int f_mapvec(int arglist);
int f_max(int x);
int f_member(int addr);
int f_min(int x);
int f_minus(int addr);
int f_mod(int x);
int f_mult(int addr);
int f_nconc(int arglist);
int f_next_method_p(int arglist);
int f_not(int addr);
int f_notnumeqp(int x);
int f_nreverse(int addr);
int f_nullp(int addr);
int f_numberp(int addr);
int f_numeqp(int addr);
int f_open_input_file(int x);
int f_open_io_file(int x);
int f_open_output_file(int x);
int f_open_stream_p(int x);
int f_or(int addr);
int f_output_stream_p(int x);
int f_parse_error_expected_class(int arglist);
int f_parse_error_string(int arglist);
int f_parse_number(int arglist);
int f_plus(int addr);
int f_preview_char(int x);
int f_prin1(int addr);
int f_print(int addr);
int f_probe_file(int arglist);
int f_progn(int x);
int f_property(int addr);
int f_quit(int addr);
int f_quotient(int addr);
int f_random_real(int arglist);
int f_random(int arglist);
int f_read(int addr);
int f_read_byte(int arglist);
int f_read_char(int x);
int f_read_line(int x);
int f_reciprocal(int x);
int f_remove_property(int arglist);
int f_return_from(int x);
int f_reverse(int addr);
int f_round(int arglist);
int f_set_aref(int arglist);
int f_set_car(int x);
int f_set_cdr(int x);
int f_set_dynamic(int arglist);
int f_set_elt(int arglist);
int f_set_file_position(int arglist);
int f_set_garef(int arglist);
int f_set_property(int addr);
int f_set_slot_value(int arglist);
int f_setf(int addr);
int f_setq(int addr);
int f_signal_condition(int arglist);
int f_simple_error_format_arguments(int arglist);
int f_simple_error_format_string(int arglist);
int f_sin(int addr);
int f_sinh(int x);
int f_slot_value(int x);
int f_smaller(int addr);
int f_sqrt(int x);
int f_standard_input(int x);
int f_standard_output(int x);
int f_stream_error_stream(int arglist);
int f_stream_ready_p(int arglist);
int f_streamp(int x);
int f_string_append(int arglist);
int f_string_eqgreaterp(int arglist);
int f_string_eqp(int x);
int f_string_eqsmallerp(int arglist);
int f_string_greaterp(int arglist);
int f_string_index(int arglist);
int f_string_noteqp(int x);
int f_string_smallerp(int arglist);
int f_stringp(int addr);
int f_subclassp(int x);
int f_subseq(int arglist);
int f_symbolp(int addr);
int f_tagbody(int x);
int f_tan(int addr);
int f_tanh(int x);
int f_the(int arglist);
int f_throw(int x);
int f_time(int arglist);
int f_trace(int arglist);
int f_truncate(int x);
int f_undefined_entity_name(int arglist);
int f_undefined_entity_namespace(int arglist);
int f_untrace(int arglist);
int f_unwind_protect(int x);
int f_vector(int x);
int f_while(int x);
int f_with_error_output(int x);
int f_with_handler(int arglist);
int f_with_open_input_file(int x);
int f_with_open_io_file(int x);
int f_with_open_output_file(int x);
int f_with_standard_input(int x);
int f_with_standard_output(int x);
int f_write_byte(int arglist);
int finddyn(int sym);
int findenv(int sym);
int flatten(int n, int ls);
int floatp(int x);
int flttoken(char buf[]);
int fprintr(FILE *p, int r ,int n);
int freshcell(void);
int fsubrp(int addr);
int functionp(int addr);
int gbcsw(void);
int gcd(int x, int y);
int getwp(void);
int gen_big(void);
int gen_n(int n);
int genericp(int addr);
int genlamlis_to_lamlis(int varlist);
int get_msb(int x);
int get_nth(int x, int n);
int get_sign(int x);
int getsym(char *name, int index);
int greaterp(int x, int y);
int hascommonp(int ls);
int hascommonp1(int x, int y);
int hash(char *name);
int hassamep(int ls);
int hassysclassp(int ls);
int hcons(int x, int y);
int happend(int x, int y);
int hreverse(int x);
int hlist1(int x);
int hextoken(char buf[]);
int hfreshcell(void);
int high_priority_p(int x, int y);
int illegallambdap(int ls);
int improperlistp(int ls);
int includep(int x, int y);
int initinst(int x, int initls);
int initinst1(int ls, int sc);
int initinst2(int inst_vars, int class_vars);
int input_stream_p(int x);
int inrangep(int x, int y);
int int_gcd(int x, int y);
int integerp(int x);
int intlcm(int x, int y);
int inttoken(char buf[]);
int inttoken_nsgn(char buf[]);
int isqrt(int x);
int isqrt1(int s, int s2, int x);
int issymch(char c);
int last(int x);
int laststr(char buf[]);
int lcm(int x, int y);
int length(int addr);
int list(int addr);
int list_drop(int ls, int n);
int list_take(int ls, int n);
int list1(int x);
int list10(int x1, int x2, int x3, int x4, int x5,int x6, int x7, int x8 ,int x9 ,int x10);
int list11(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8 ,int x9 ,int x10, int x11);
int list2(int x, int y);
int list3(int x, int y, int z);
int list4(int x1, int x2, int x3, int x4);
int list5(int x1, int x2, int x3, int x4, int x5);
int list6(int x1, int x2, int x3, int x4, int x5, int x6);
int list8(int x1, int x2, int x3, int x4, int x5,int x6, int x7, int x8);
int listcopy(int x);
int listp(int addr);
int listref(int lis, int n);
int listref1(int lis, int n);
int long_int_div(int x, int y);
int long_int_remainder(int x, int y);
int long_long_div(int x, int y);
int long_long_remainder(int x, int y);
int longnump(int x);
int macrop(int addr);
int makearray(int lis, int obj);
int makebigx(char *bignum);
int makechar(char *pname);
int makeclass(char *pname, int superclass);
int makedummy(void);
int makedoubleflt(double x);
int makeflt(double floatn);
int makefunc(char *pname, int addr);
int makegeneric(char *pname, int lamlist, int body);
int makegeneric_star(int lamlist,int body);
int makeinstance(int class, int ls);
int makeint(int intn);
int makelong(long long int x);
int makemethod(int x);
int makenum(int num);
int makestr(char *string);
int makestream(FILE *port, int type);
int makesym(char *pname);
int makesym1(char *pname);
int makeusercond(int class, int str, int arg);
int makevec(int n, int obj);
int mapc(int x, int y);
int mapcan(int x, int y);
int mapcar(int x, int y);
int mapcon(int x, int y);
int mapl(int x, int y);
int maplist(int x, int y);
int maplist1(int y);
int mapvec(int x, int y);
int mat_mult(int x, int y);
int mat_vec_mult(int x, int y);
int matchp(int varlist, int arglist);
int math_integerp(int x);
int matrix_ref(int x, int n, int i, int j);
int matrix_set(int obj, int n, int i, int j, int val);
int member(int x, int y);
int member1(int x, int y, int z);
int minus(int arg1, int arg2);
int mult(int arg1, int arg2);
int nconc(int x, int y);
int negative_zerop(int x);
int negativep(int x);
int next(int x);
int notexistclassp(int ls);
int nreverse(int x);
int nullp(int addr);
int numberp(int addr);
int numeqp(int x, int y);
int octtoken(char buf[]);
int output_stream_p(int x);
int plus(int arg1, int arg2);
int pop(void);
int positive_zerop(int x);
int positivep(int x);
int prev(int x);
int quasi_transfer(int x, int n);
int quotient(int x, int y);
int sread(void);
int readlist(void);
int remove_list(int x, int y);
int remove_prop(int x,int lis);
int reverse(int x);
int shelterpop(void);
int s_remainder(int x, int y);
int slotvars(int class);
int smallerp(int x, int y);
int sprintr(char *str, int r, int n);
int streamp(int x);
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
int symbolp(int addr);
int symboltoken(char buf[]);
int symnamep(int addr, char *name);
int vec_minus(int x, int y);
int vec_plus(int x, int y);
int vector(int lis);
int vector_length(int x);
int vector_ref(int v, int n);
int vector_to_list(int x);
int vectorp(int x);
int zerop(int addr);
septoken separater(char buf[], char sep);
void adddynenv(int sym, int val);
void addlexenv(int sym, int val);
void argpush(int addr);
void bigx_gbc(int x);
void bigx_minus2(int arg, int c, int msb);
void bigx_plus2(int arg, int c, int msb);
void bindarg(int lambda, int arglist);
void bindclass(char *name, int class);
void bindconst(char *name, int obj);
void bindfunc(char *name, tag tag, int(*func)(int));
void bindmacro(char *name, int addr);
void cellprint(int addr);
void checkgbc(void);
void clrcell(int addr);
void copygbc(void);
void copy_hash(int x);
void cut_zero(int x);
void deffsubr(char *symname, int(*func)(int));
void defsubr(char *symname, int(*func)(int));
void dropchar(char buf[]);
void error(int errnum, char *fun, int arg);
void gbc(void);
void gbcmark(void);
void gbcsweep(void);
void gettoken(void);
void heapdump(int start, int end);
void initcell(void);
void initclass(void);
void initerrargs(int class);
void initexsubr(void);
void initgeneric(void);
void initpt(void);
void initstream(void);
void initsubr(void);
void initsyntax(void);
void insert_method(int x, int func);
void insertstr(char ch, char buf[]);
void markcell(int addr);
void print(int addr);
void print_bigx(int x);
void printarray(int x);
void printchar(int addr);
void printclass(int x);
void printflt(double x);
void printint(int x);
void printlist(int addr);
void printlong(int x);
void printobj(char *str);
void printstr(int addr);
void printstream(int x);
void printsym(int x);
void printvec(int addr);
void push(int pt);
void redef_generic(void);
void resort_method(int func);
void set_sign(int x, int y);
void setdynenv(int sym, int val);
void setlexenv(int sym, int val);
void setval(int sym, int val, int ls);
void shelterpush(int addr);
void signal_condition(int x, int y);
void signal_handler_c(int signo);
void unbind(void);
void unreadc(char c);
void vector_set(int v, int n, int obj);
void store_backtrace(int x);

int f_backtrace(int arglist);
int f_symbol_function(int arglist);
int f_symbol_class(int arglist);

void setcolor(int n);
int getch();
int f_edit(int arglist);
#ifdef __arm__
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

//Fast project
void shelterpush(int addr);
int shelterpop(void);
int freecell(void);
int get_int(int addr);
long long int get_long(int addr);
int nth(int n, int addr);
int f_freedll(int arglist);
int f_system(int arglist);
int set_car(int x, int y);
int set_cdr(int x, int y);
int set_aux(int x, int y);
int set_opt(int x, int y);
int callsubr(int func, int arglist);
int f_subrp(int arglist);
int makeintlong(int n);
int makestrflt(char *str);
int makedoubleflt(double x);
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
int adaptp(int x, int y);
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
char* get_name(int x);
double get_flt(int x);


void display_buffer(void);
int check_token_buffer(int col);
int findlparen_buffer(int col);
int findrparen_buffer(int col);
void emphasis_lparen_buffer(int col);
void emphasis_rparen_buffer(int col);
void reset_paren_buffer();
void restore_paren_buffer(int col);
char *get_fragment_buffer(int col);
void find_candidate_buffer(int col);
int replace_fragment_buffer(char* newstr, int col);
void insertcol_buffer(int col);
void backspace_buffer(int col);
int read_line(int flag);

