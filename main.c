/*
 * Easy-ISLisp (ISLisp) written by kenichi sasagawa 2016/4~ 
 * main functions read,eval,print (REPL)
 *
 * <files>
 * main.c        REPL
 * cell.c        generate cells. 
 * link.c		 interface functions for dynamic-linked code.
 * data.c        predicate for data structure. operation of data structure.
 * compute.c     computation numeric
 * bignum.c      computation of bignum
 * function.c    builtin functions
 * syntax.c      syntax functions
 * extension.c   extended functions (non ISLisp standard)
 * gbc.c         garbage collenction
 * parallel.c    parallel functions (non ISLisp standard)
 * edlis.c       Edlis simple CUI editor
 *
 * <cell type summary>
 * sym   symbol
 * int   integer
 * flt   float
 * str   string
 * stm   stream
 * arr   array
 * vec   vector
 * char  character
 * big   bignum 
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "eisl.h"
#include "mem.h"
#include "fmt.h"
#include "except.h"
#include "str.h"
#include "long.h"


/* pointer */
int ep[PARASIZE];		/* environment pointer */
int dp[PARASIZE];		/* dynamic pointer */
int hp[PARASIZE];		/* heap pointer for mark and sweep */
int sp[PARASIZE];		/* stack pointer */
int fc[PARASIZE];		/* free counter */
int ap[PARASIZE];		/* arglist pointer */
int lp[PARASIZE];		/* shelter pointer */
int cp;				/* tag pointer for catch & throw */

/* class */
int cobject;
int cbasic_array;
int cbasic_array_star;
int cgeneral_array_star;
int cbasic_vector;
int cgeneral_vector;
int cstring;
int cbuilt_in_class;
int ccharacter;
int cfunction;
int cgeneric_function;
int cstandard_generic_function;
int clist;
int ccons;
int cnull;
int csymbol;
int cnumber;
int cfloat;
int cinteger;
int cserious_condition;
int cerror;
int carithmetic_error;
int cdivision_by_zero;
int cfloating_point_overflow;
int cfloating_point_underflow;
int ccontrol_error;
int cparse_error;
int cprogram_error;
int cdomain_error;
int cclass_error;
int cundefined_entity;
int cunbound_variable;
int cundefined_function;
int csimple_error;
int cstream_error;
int cend_of_stream;
int cstorage_exhausted;
int cstandard_class;
int cstandard_object;
int cstream;
int cinvalid;
int cfixnum;
int clongnum;
int cbignum;


/* stream */
int standard_input;
int standard_output;
int standard_error;
int input_stream;
int output_stream;
int error_stream;
char stream_str[STRSIZE];
int charcnt;			/* for format-tab. store number of chars up to now. */


/* read scaner */
token stok;

int line;
int column;
char buffer[COL_SIZE + 1][NUM_HISTORY];
char buffer1[COL_SIZE + 1];
char buffer2[COL_SIZE + 1] = { 0 };	//for read_stdin()
char buffer3[STRSIZE] = { 0 };	//for Multi-Process 

/* heap ,stack and bignum */
cell heap[CELLSIZE];
int stack[STACKSIZE][PARASIZE];
int argstk[STACKSIZE][PARASIZE];
int cell_hash_table[HASHTBSIZE];
int shelter[STACKSIZE][PARASIZE];
int dynamic[DYNSIZE][2][PARASIZE];
int bigcell[BIGSIZE];

/* object oriented */
int generic_func;		/* generic function in eval. */
int generic_vars;		/* args list of generic function in eval. */
int next_method;		/* head address of finded method. */
int generic_list = NIL;		/* symbol list of generic function. */
int setf_list = NIL;		/* generic function related setf */

/* system global variable */
int gArgC;
char **gArgV;
int genint = 1;			/* integer of gensym */

/* flag */
bool gbc_flag = false;		/* false=GC not display ,true= do display. */
bool simp_flag = true;		/* true=simplify, false=Not for bignum */
bool ignore_flag = false;	/* false=normal,true=ignore error */
bool open_flag = false;		/* false=normal,true=now loading */
bool top_flag = true;		/* true=top-level,false=not-top-level */
bool redef_flag = false;	/* true=redefine-class,false=not-redefine */
bool start_flag = true;		/* true=line-start,false=not-line-start */
bool back_flag = true;		/* for backtrace,true=on,false=off */
bool ignore_topchk = false;	/* for FAST-compiler true=ignore,false=normal */
bool repl_flag = true;		/* for REPL read_line true=on,false=off */
bool org_repl_flag = true;	/* original val for restore */
bool option_flag = false;	/* while handling command line option it is true, else false */
volatile sig_atomic_t ctrl_c_flag = 0;	/* true= ctrl+C */
bool greeting_flag = true;	/* for greeting */
bool script_flag = false;	/* for -s option */
bool handling_resource_err = false;	/* stop infinite recursion */
bool looking_for_shebang = false;	/* skip over #! */
bool multiple_call_next_method;	/* method body has multiple (call-next-method) */
bool error_flag = false;	/* invoked error? */
bool parallel_flag = false;	/* while executing parallel */
bool parallel_exit_flag = false;	/* To exit parallel threads */
bool process_flag = false;	/* when invoke as child process, flag is true */
bool thread_flag = false;	/* when invoke as multi thread, flag is true */
bool parent_flag = false;	/* when invoke as parent, flag is true */
bool child_flag = false;	/* when invoke as network child, flag is true */
bool connect_flag = false;	/* when child listen, connect_flag is true */
bool receiver_exit_flag = false;	/* to exit child TCP/IP receiver */
bool shutdown_flag = false;	/* shutdown OS on child */
/* try function (try time s-exp binary) */
bool try_flag;			/* true or false */
double try_timer;		/* limit timer */
int try_res;			/* argument list */


/* bignum pointer */
int big_pt0 = 0;		/* pointer of temporaly bignum */
int big_pt1 = BIGNUM_PARMA;	/* pointer of parmanent bignum */


/* longjmp control and etc */
Except_T Restart_Repl = { "Restart REPL" },
    Exit_Interp = { "Exit interpreter" };
jmp_buf block_buf[CTRLSTK];
jmp_buf catch_buf[CTRLSTK];
jmp_buf cont_buf;
Except_T Ignored_Error = { "Ignored error" };	/* for ignore-errors */
Except_T Exit_Thread = { "Exit thread" };	/* for Multi-thread */
Except_T Exit_Process = { "Exit Process" };	/* for Multi-process */
Except_T Exit_Network = { "Exit Network" };	/* for Distributed parallel */

int signal_condition_x;
int signal_condition_y;

int block_tag_check[CTRLSTK];
int block_data[CTRLSTK][3];
int catch_data[CTRLSTK][4];	/* new data type for catch tag */
int unwind_buf[CTRLSTK];
int block_pt;			/* index of block. following are similer */
int catch_pt = 0;		/* catch counter */
int unwind_pt;			/* lambda address for unwind-protect */
int block_arg;			/* receive argument of block */
int catch_arg;			/* receive argument of catch */
int cont_arg;			/* receive argument of continue-condition */
int tagbody_tag = NIL;		/* tag address fo tagbody */
int error_handler = NIL;	/* for store first argument of with-handler */
int error_handler1 = NIL;	/* for restore error_handler */
int trace_list = NIL;		/* function list of trace */
int backtrace[BACKSIZE];
int unwind_nest;		/* unwind-protect nest level */
int process_arg;		/* when -p option child process number */


/* multi thread */
pthread_mutex_t mutex;
pthread_mutex_t mutex1;
int mt_queue[PARASIZE];
int mt_queue_pt;
int mt_queue_num;
int thread_num = 1;
int para_input[PARASIZE];
int para_output[PARASIZE];
pthread_t mt_para_thread[PARASIZE];
pthread_cond_t mt_cond_para[PARASIZE];
pthread_cond_t mt_cond_main;
pthread_cond_t mt_cond_queue;
pthread_attr_t mt_para_attr[PARASIZE];
size_t mt_para_size[PARASIZE];

/*multi proccess*/
int pipe_p2c[PROCSIZE][2];
int pipe_c2p[PROCSIZE][2];
pid_t pid[PROCSIZE];
int process_pt = 0;
int process_num;
struct sigaction child_action;
int child_signal[PROCSIZE];
int child_signal1[PROCSIZE];

/* -----distributed parallel & TCPIP------*/
pthread_mutex_t mutex2;
pthread_cond_t md_cond;
int child_buffer_ready;
int parent_sockfd[2];
int child_sockfd[PARASIZE];
socklen_t parent_len;
struct sockaddr_in parent_addr, child_addr[PARASIZE];
int child_num;
int child_id;
pthread_t receiver_thread;
pthread_t preceiver_thread[PARASIZE];
pthread_t creceiver_thread;
int child_result[PARASIZE];
char parent_buffer[BUFSIZE][PARASIZE];
char child_buffer[BUFSIZE];
char transfer[BUFSIZE];
char input_buffer[BUFSIZE];
char output_buffer[BUFSIZE];

/* -----TCPIP for server----------------*/
socklen_t server_len;
struct sockaddr_in server_addr, client_addr;





/* -----debugger----- */
int examin_sym;
int stepper_flag = 0;


/* -----profiler----- */
int prof_sw = 0;		/* 0= not profiler, 1=system-function 2=user-function */
int prof_sym[PROFSIZE];
int prof_pt = 1;
double prof_dt0[PROFSIZE];
int prof_dt1[PROFSIZE];

/* -----editor------- */
int ed_lparen_col;
int ed_rparen_col;
const char *ed_candidate[COMPLETION_CANDIDATES_MAX];
int ed_candidate_pt;
const short ed_syntax_color = COLOR_RED;
const short ed_builtin_color = COLOR_CYAN;
const short ed_extended_color = COLOR_MAGENTA;
const short ed_string_color = COLOR_YELLOW;
const short ed_comment_color = COLOR_BLUE;
int ed_incomment = -1;		/* #|...|# comment */

/* Defaults, should be filled in later */
char ed_key_up = 'A';
char ed_key_down = 'B';
char ed_key_right = 'C';
char ed_key_left = 'D';

static void usage(void)
{
    puts("List of options:\n"
	 "-c           -- EISL starts after reading compiler.lsp.\n"
	 "-f           -- EISL starts after reading formatter.lsp.\n"
	 "-h           -- display help.\n"
	 "-l filename  -- EISL starts after reading the file.\n"
	 "-n           -- EISL starts as network child mode.\n"
	 "-r           -- EISL does not use editable REPL.\n"
	 "-s filename  -- EISL runs the file with script mode.\n"
	 "-v           -- display version number.");
}

static inline void maybe_greet(void)
{
    if (greeting_flag)
	Fmt_print("Easy-ISLisp Ver%1.2f\n", VERSION);

    greeting_flag = false;
}

static inline void disable_repl_flag(void)
{
    repl_flag = false;
    org_repl_flag = false;
}

int main(int argc, char *argv[])
{
    int errret;

    Fmt_register('D', cvt_D);
    if (setupterm((char *) 0, 1, &errret) == ERR ||
	key_up == NULL || key_down == NULL ||
	key_right == NULL || key_left == NULL) {
	disable_repl_flag();
    } else {
	ed_key_down = key_down[2];
	ed_key_left = key_left[2];
	ed_key_right = key_right[2];
	ed_key_up = key_up[2];
    }

    init_stok();
    init_cell();
    init_class();
    init_stream();
    init_subr();
    init_exsubr();
    init_syntax();
    init_generic();
    init_dp();
    init_pointer();
    /* ctrl+c */
    signal(SIGINT, signal_handler_c);
    signal(SIGSTOP, SIG_IGN);
    /* signal for read_from_pipe_part() */
    memset(&child_action, 0, sizeof(child_action));
    child_action.sa_sigaction = &signal_handler_child;
    child_action.sa_flags = SA_SIGINFO;
    sigaction(SIGRTMIN, &child_action, NULL);
    if (setenv("EASY_ISLISP", STRQUOTE(SHAREDIR), /* overwrite = */ 0) ==
	-1) {
	perror("setenv");
	exit(EXIT_FAILURE);
    }

    input_stream = standard_input;
    output_stream = standard_output;
    error_stream = standard_error;

    int ch;
    char *script_arg;

    /* handle command line options */
    option_flag = true;
    TRY {
	if (access("startup.lsp", R_OK) == 0)
	    f_load(list1(make_str("startup.lsp")), 0);

	while ((ch = getopt(argc, argv, "l:s:p:cfrhvn")) != -1) {
	    char *str;

	    switch (ch) {
	    case 'l':
		if (f_probe_file(list1(make_str(optarg)), 0) == T) {
		    f_load(list1(make_str(optarg)), 0);
		} else {
		    puts("File doesn't exist.");
		    exit(EXIT_FAILURE);
		}
		break;
	    case 'c':
		str = library_file("compiler.lsp");
		f_load(list1(make_str(str)), 0);
		FREE(str);
		break;
	    case 'f':
		str = library_file("formatter.lsp");
		f_load(list1(make_str(str)), 0);
		FREE(str);
		break;
	    case 's':
		if (access(optarg, R_OK) == -1) {
		    puts("File doesn't exist.");
		    exit(EXIT_FAILURE);
		}
		disable_repl_flag();
		script_flag = true;
		looking_for_shebang = true;
		script_arg = optarg;
		break;
	    case 'r':
		disable_repl_flag();
		break;
	    case 'p':
		process_flag = true;
		process_num = strtol(optarg, NULL, 10);
		break;
	    case 'n':
		puts("EISL runs with network mode.");
		child_flag = true;
		init_parent();
		init_creceiver();
		str = library_file("compiler.lsp");
		f_load(list1(make_str(str)), 0);
		FREE(str);
		break;
	    case 'v':
		Fmt_print("Easy-ISLisp Ver%1.2f\n", VERSION);
		exit(EXIT_SUCCESS);
	    case 'h':
		usage();
		exit(EXIT_SUCCESS);
	    default:
		usage();
		exit(EXIT_FAILURE);
	    }
	}
	gArgC = argc - optind;
	gArgV = argv + optind;
	if (script_flag) {
	    f_load(list1(make_str(script_arg)), 0);
	    exit(EXIT_SUCCESS);
	}
    }
    EXCEPT(Restart_Repl) exit(EXIT_FAILURE);
    END_TRY;

    option_flag = false;


    /* REPL */
    volatile bool quit = false;
    do {
	maybe_greet();
	TRY while (1) {
	    init_pointer();
	    if (!process_flag && !child_flag) {
		fputs("> ", stdout);
		print(eval(sread(), 0));
		putchar('\n');
	    } else if (process_flag) {
		TRY print(eval(sread(), 0));
		putchar('\n');
		fflush(stdout);
		union sigval value;
		value.sival_int = (int) process_num;
		sigqueue(getppid(), SIGRTMIN, value);
		EXCEPT(Exit_Process);
		END_TRY;
	    } else if (child_flag) {
		pthread_mutex_lock(&mutex2);
		while (!child_buffer_ready) {
		    pthread_cond_wait(&md_cond, &mutex2);
		}
		child_buffer_ready = 0;
		pthread_mutex_unlock(&mutex2);
		int exp, res;
		exp = str_to_sexp(receive_from_parent());
		printf("receive_from_parent ");
		print(exp);
		printf("\n");
		fflush(stdout);
		TRY res = eval(exp, 0);
		printf("send_to_parent ");
		print(res);
		printf("\n");
		fflush(stdout);
		send_to_parent(sexp_to_str(res));
		EXCEPT(Exit_Network);
		END_TRY;
	    }

	    if (redef_flag)
		redef_generic();
	}
	EXCEPT(Restart_Repl);
	EXCEPT(Exit_Interp) {
	    quit = true;
	    exit_thread();
	    close_socket();
	    if (shutdown_flag) {
		printf("Shutting down the system...\n");
		int ret = system("sudo shutdown now");
		if (ret == -1)
		    error(SYSTEM_ERR, "dp-halt shatdown", NIL, 0);
	    }
	}
	END_TRY;
    }
    while (!quit);
}

char *library_file(const char *basename)
{
    char *prefix;

    if ((prefix = getenv("EASY_ISLISP")) != NULL) {
	return Str_catv(prefix, 1, 0, "/library/", 1, 0, basename, 1, 0,
			NULL);
    }
    return Str_cat(STRQUOTE(SHAREDIR) "/library/", 1, 0, basename, 1, 0);
}

void init_dp(void)
{
    int i;
    for (i = 0; i < PARASIZE; i++)
	dp[i] = 0;
}

void init_pointer(void)
{
    int i, ls;

    for (i = 0; i < PARASIZE; i++) {
	ep[i] = 0;
	sp[i] = 0;
	ap[i] = 0;
	lp[i] = 0;
    }
    cp = 0;
    block_pt = 0;
    catch_pt = 0;
    unwind_pt = 0;
    error_handler = NIL;
    top_flag = true;
    start_flag = true;
    error_flag = false;
    charcnt = 0;
    generic_func = NIL;
    generic_vars = NIL;
    big_pt0 = 0;
    unwind_nest = 0;
    /* clear nest level of tracing function. */
    ls = trace_list;
    while (!nullp(ls)) {
	SET_TR(GET_CAR(car(ls)), 0);
	ls = cdr(ls);
    }
}


void exit_thread(void)
{

    /* exit parallel function thread */
    exit_para();
}


void signal_handler_c(int signo __unused)
{
    ctrl_c_flag = 1;
}

void signal_handler_child(int sig, siginfo_t * siginfo, void *context)
{
    int n;

    n = siginfo->si_value.sival_int;
    child_signal[n] = 1;

}





/* -------read()-------- */

int string_readc(int stm __unused)
{
    int c;

    c = GET_NAME(input_stream)[GET_CDR(input_stream)];
    SET_CDR(input_stream, GET_CDR(input_stream) + 1);
    if (c == '\\') {
	c = GET_NAME(input_stream)[GET_CDR(input_stream)];
	SET_CDR(input_stream, GET_CDR(input_stream) + 1);
    } else if (c == NUL) {
	c = EOF;
	SET_CDR(input_stream, GET_CDR(input_stream) - 1);
    }
    return (c);
}

int readc(void)
{
    int c;

    if (string_input_stream_p(input_stream)) {
	/* string-input-stream */
	return (string_readc(input_stream));
    } else if (process_flag == true) {
	/* EISL as child process */
	return (read_stdin());
    } else if (input_stream == standard_input && repl_flag) {
	/* REPL-mode and standard-input */
	c = read_line(1);
    } else {
	/* not REPL-mode and standard-input */
	c = getc(GET_PORT(input_stream));
	if (!script_flag && input_stream == standard_input && c == EOF) {
	    /* ctrl+D and not script-mode quit system */
	    putchar('\n');
	    RAISE(Exit_Interp);
	} else if (script_flag)
	    /* on script-mode only retrun c */
	    return (c);

    }

    if (c == EOL) {
	line++;
	column = 0;
    } else
	column++;

    return (c);
}

void unreadc(char c)
{
    if (c == EOL)
	line--;
    else
	column--;
    if (input_stream == standard_input && repl_flag)
	(void) read_line(-1);
    else if (GET_OPT(input_stream) != EISL_INSTR)
	ungetc(c, GET_PORT(input_stream));
    else if (c != EOF)
	SET_CDR(input_stream, GET_CDR(input_stream) - 1);
}

void init_stok()
{
    stok.ch = '\0';
    stok.flag = GO;
    stok.type = OTHER;
    stok.bufsize = BUFSIZE;
    stok.buf = ALLOC(BUFSIZE * sizeof(char));
    stok.buf[0] = '\0';
}

void set_stok_buf(int index, char c)
{
    if (index >= stok.bufsize) {
	int new_bufsize = index + 1;
	RESIZE(stok.buf, sizeof(char) * new_bufsize);
	stok.bufsize = new_bufsize;

    }
    stok.buf[index] = c;
    return;
}

void replace_stok_buf(char *str)
{
    if (strlen(str) > (size_t) stok.bufsize) {
	int new_bufsize = strlen(str);
	RESIZE(stok.buf, sizeof(char) * new_bufsize);
	stok.bufsize = new_bufsize;
    }
    strcpy(stok.buf, str);
}

void get_token(void)
{
    int c;
    int pos;
    int res;

    if (stok.flag == BACK) {
	stok.flag = GO;
	return;
    }

    if (stok.ch == ')') {
	stok.type = RPAREN;
	stok.ch = NUL;
	return;
    }

    if (stok.ch == '(') {
	stok.type = LPAREN;
	stok.ch = NUL;
	return;
    }

    c = readc();

  skip:
    while (c == SPACE || c == EOL || c == TAB || c == RET)
	c = readc();

    /* skip comment line
     * if find EOF at end of line, return FILEEND.
     */
    if (c == ';') {
	while (!(c == EOL)) {
	    c = readc();
	    if (c == EOF) {
		stok.type = FILEEND;
		return;
	    }
	}
	goto skip;
    }
    /* if end of file,return FILEEND. */
    if (c == EOF) {
	stok.type = FILEEND;
	return;
    }

    switch (c) {
    case '(':
	stok.type = LPAREN;
	break;
    case ')':
	stok.type = RPAREN;
	break;
    case '\'':
	stok.type = QUOTE;
	break;
    case '.':
	stok.type = DOT;
	break;
    case '`':
	stok.type = BACKQUOTE;
	break;
    case ',':
	stok.type = COMMA;
	break;
    case '@':
	stok.type = ATMARK;
	break;
    case '"':
	{
	    c = readc();
	    pos = 0;
	    while (c != '"') {
		set_stok_buf(pos++, c);
		if (c == '\\') {
		    c = readc();
		    set_stok_buf(pos++, c);
		}
		if (c == EOF) {
		    error(SYSTEM_ERR, "not exist right hand double quote",
			  NIL, 0);
		}
		c = readc();
	    }
	    set_stok_buf(pos, NUL);
	    stok.type = STRING;
	    break;
	}
    case '#':
	{
	    c = readc();
	    if (c == '\'') {
		stok.type = FUNCTION;
		break;
	    } else if (c == '(') {
		stok.type = VECTOR;
		break;
	    } else if (c == '\\') {
		c = readc();
		pos = 0;
		set_stok_buf(pos++, c);
		if (c == ' ')
		    goto chskip;

		while (((c = readc()) != EOL) && (c != EOF)
		       && (pos < stok.bufsize - 1) && (c != SPACE)
		       && (c != '(')
		       && (c != ')')) {
		    set_stok_buf(pos++, c);
		}

	      chskip:
		set_stok_buf(pos, NUL);
		stok.type = CHARACTER;
		if (c == EOF)
		    stok.ch = ' ';
		else
		    stok.ch = c;
		break;
	    } else if (isdigit(c)) {
		pos = 0;
		while (isdigit(c)) {
		    set_stok_buf(pos, c);
		    pos++;
		    c = readc();
		}
		stok.buf[pos] = NUL;
		set_stok_buf(pos, c);
		if (c == 'a' || c == 'A') {
		    stok.type = ARRAY;
		    break;
		} else {
		    stok.type = OTHER;
		    return;
		}
	    }
	    if (c == '|') {
	      reskip:
		c = readc();
		while (c != '|') {
		    if (c == EOF)
			error(SYSTEM_ERR,
			      "not exist right hand #| comment |#", NIL,
			      0);
		    c = readc();
		}
		c = readc();
		if (c == '#') {
		    c = readc();
		    goto skip;
		} else
		    goto reskip;
	    } else
		unreadc(c);
	    c = '#';
	}
     /*FALLTHROUGH*/ default:
	{
	    pos = 0;
	    set_stok_buf(pos++, c);
	    while (((c = readc()) != EOL) && (c != EOF)
		   && (pos < stok.bufsize - 1) && (c != SPACE)
		   && (c != '(')
		   && (c != ')') && (c != '`') && (c != ',') && (c != '@'))
		set_stok_buf(pos++, c);

	    set_stok_buf(pos, NUL);
	    stok.ch = c;

	    if (flt_token(stok.buf)) {
		stok.type = FLOAT_N;
		break;
	    }
	    /* first step,check bignum_token() and second int_token() ignores number of digits. */
	    if (bignum_token(stok.buf)) {
		stok.type = BIGNUM;
		break;
	    }
	    if (int_token(stok.buf)) {
		stok.type = INTEGER;
		break;
	    }
	    if (int_token_nsgn(stok.buf)) {
		stok.type = INTEGER;
		break;
	    }
	    if (bin_token(stok.buf)) {
		stok.type = BINARY;
		break;
	    }
	    if (oct_token(stok.buf)) {
		stok.type = OCTAL;
		break;
	    }
	    if (dec_token(stok.buf)) {
		stok.type = DECNUM;
		break;
	    }
	    if (hex_token(stok.buf)) {
		stok.type = HEXNUM;
		break;
	    }
	    if ((res = expt_token(stok.buf))) {
		if (res == 2)
		    stok.type = EXPTOVERF;
		else if (res == 3)
		    stok.type = EXPTUNDERF;
		else
		    stok.type = EXPTNUM;
		break;
	    }
	    if (symbol_token(stok.buf)) {
		stok.type = SYMBOL;
		break;
	    }
	    stok.type = OTHER;
	}
    }
}

septoken separater(char buf[], char sep)
{
    int i, j;
    char c;
    septoken res;

    res.sepch = NUL;
    res.after[0] = NUL;

    res.before[0] = buf[0];
    i = 1;
    j = 1;
    while ((c = buf[i]) != NUL)
	if (c == sep) {
	    res.before[j] = NUL;
	    res.sepch = sep;
	    i++;
	    j = 0;
	    while ((c = buf[i]) != NUL) {
		res.after[j] = c;
		i++;
		j++;
	    }
	    res.after[j] = NUL;
	} else {
	    res.before[j] = c;
	    i++;
	    j++;
	}
    return (res);
}

void insert_str(char ch, char buf[])
{
    int i;

    i = last_str(buf) + 1;
    while (i >= 0) {
	buf[i + 1] = buf[i];
	i--;
    }
    buf[0] = ch;
}

int last_str(char buf[])
{
    int i;

    i = 0;
    while (buf[i] != NUL)
	i++;
    return (i - 1);
}


/* remove #\ from char, for example #\a -> a */
void drop_char(char buf[])
{
    int i, j;

    j = last_str(buf);
    for (i = 2; i <= j; i++)
	buf[i - 2] = buf[i];
    buf[i - 2] = NUL;
}


/* integer of sign. ignore number of digits. */
int int_token(char buf[])
{
    int i;
    char c;

    if (buf[0] == NUL)		/* null string */
	return (0);

    if (((buf[0] == '+') || (buf[0] == '-'))) {
	if (buf[1] == NUL)
	    return (0);		/* case {+,-} => symbol */
	i = 1;
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;		/* case {+123..., -123...} */
	    else
		return (0);
    } else {
	i = 0;			/* {1234...} */
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;
	    else
		return (0);
    }
    return (1);
}

/* integer without sign */
int int_token_nsgn(char buf[])
{
    int i;
    char c;

    i = 0;
    while ((c = buf[i]) != NUL) {
	if (isdigit(c))
	    i++;
	else
	    return (0);
    }
    return (1);
}

int flt_token(char buf[])
{
    septoken tok;

    if (buf[0] == '.') {
	char bufcp[SYMSIZE];

	if (buf[1] == '0')
	    return (0);
	strncpy(bufcp, buf, SYMSIZE - 1);
	bufcp[SYMSIZE - 1] = '\0';
	insert_str('0', bufcp);
	if (flt_token(bufcp))
	    return (1);
    }


    tok = separater(buf, '.');

    if (tok.sepch == NUL)
	return (0);

    if (tok.after[0] == NUL)	/* ""."" */
	return (0);
    else if (int_token(tok.before) && int_token_nsgn(tok.after))
	return (1);
    else
	return (0);
}

int bignum_token(char buf[])
{
    int i;
    char c;

    if (((buf[0] == '+') || (buf[0] == '-'))) {
	if (buf[1] == NUL)
	    return (0);		/* case {+,-} => symbol */
	i = 1;
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;		/* case {+123..., -123...} */
	    else
		return (0);
	if (strlen(buf) <= 10)
	    return (0);		/* case not bignum */
    } else {
	i = 0;			/* {1234...} */
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;
	    else
		return (0);
	if (strlen(buf) <= 9)
	    return (0);		/* case not bignum */
    }
    return (1);			/* bignum */
}


int symbol_token(char buf[])
{
    int i;
    char c;

    i = 0;
    while ((c = buf[i]) != NUL)
	if ((isalpha(c)) || (isdigit(c)) || (is_symbol_char(c)))
	    i++;
	else
	    return (0);

    /* fold to upper letter. */
    i = 0;
    while ((c = buf[i]) != NUL) {
	buf[i] = toupper(c);
	i++;
    }
    return (1);
}

int bin_token(char buf[])
{
    int i;
    char c;

    if (!(buf[0] == '#' && (buf[1] == 'b' || buf[1] == 'B')))
	return (0);

    if (buf[2] == '+' || buf[2] == '-')
	i = 3;
    else
	i = 2;

    while ((c = buf[i]) != NUL)
	if (c == '0' || c == '1')
	    i++;
	else
	    return (0);

    if (i == 3 && (buf[2] == '+' || buf[2] == '-'))
	return (0);
    else if (i != 2) {
	drop_char(buf);
	return (1);
    } else
	return (0);
}

int oct_token(char buf[])
{
    int i;
    char c;

    if (!(buf[0] == '#' && (buf[1] == 'o' || buf[1] == 'O')))
	return (0);
    if (buf[2] == '+' || buf[2] == '-')
	i = 3;
    else
	i = 2;

    while ((c = buf[i]) != NUL)
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
	    c == '5' || c == '6' || c == '7')
	    i++;
	else
	    return (0);

    if (i == 3 && (buf[2] == '+' || buf[2] == '-'))
	return (0);
    else if (i != 2) {
	drop_char(buf);
	return (1);
    } else
	return (0);
}

int dec_token(char buf[])
{
    int i;
    char c;

    if (!(buf[0] == '#' && (buf[1] == 'd' || buf[1] == 'D')))
	return (0);
    if (buf[2] == '+' || buf[2] == '-')
	i = 3;
    else
	i = 2;

    while ((c = buf[i]) != NUL)
	if (isdigit(c))
	    i++;
	else
	    return (0);

    if (i != 2) {
	drop_char(buf);
	return (1);
    } else
	return (0);
}

int hex_token(char buf[])
{
    int i;
    char c;

    if (!(buf[0] == '#' && (buf[1] == 'x' || buf[1] == 'X')))
	return (0);
    if (buf[2] == '+' || buf[2] == '-')
	i = 3;
    else
	i = 2;

    while ((c = buf[i]) != NUL)
	if (isxdigit(c))
	    i++;
	else
	    return (0);

    if (i == 3 && (buf[2] == '+' || buf[2] == '-'))
	return (0);
    else if (i != 2) {
	drop_char(buf);
	return (1);
    } else
	return (0);
}


int expt_token(char buf[])
{
    septoken tok;
    char buf1[BUFSIZE];

    if (buf[0] == '.')		/* e.g. ".2E3" */
	return (0);

    strncpy(buf1, buf, BUFSIZE - 1);
    buf1[BUFSIZE - 1] = '\0';
    tok = separater(buf, 'e');
    if (tok.sepch != NUL &&
	(int_token(tok.before) || flt_token(tok.before)) &&
	int_token(tok.after)) {
	if (atoi(tok.after) > 999)
	    return (2);		/* overflow */
	else if (atoi(tok.after) < -999)
	    return (3);		/* underflow */
	else
	    return (1);		/* regular */
    }

    strncpy(buf, buf1, BUFSIZE - 1);
    buf[BUFSIZE - 1] = '\0';
    tok = separater(buf, 'E');
    if (tok.sepch == NUL)
	return (0);
    if ((int_token(tok.before) || flt_token(tok.before)) &&
	int_token(tok.after)) {
	if (atoi(tok.after) > 999)
	    return (2);		/* overflow */
	else if (atoi(tok.after) < -999)
	    return (3);		/* underflow */
	else
	    return (1);		/* regular */
    } else
	return (0);
}


int is_symbol_char(char c)
{
    switch (c) {
    case '!':
    case '?':
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
    case '<':
    case '>':
    case '_':
    case '.':
    case ':':
    case '#':
    case '$':
    case '@':
    case '%':
    case '&':
    case '~':
    case '^':
    case '|':
    case '\\':
    case '{':
    case '}':
    case '[':
    case ']':
	return (1);
    default:
	return (0);
    }
}

/*
 * read S-expression from input stream
 * to avoid name confliction sread() (not read()).
 *
 */
int sread(void)
{
    int n;
    char *e;

    get_token();
    switch (stok.type) {
    case FILEEND:
	return (FEND);
    case INTEGER:
	return (make_int(atoi(stok.buf)));
    case FLOAT_N:
	return (make_flt(atof(stok.buf)));
    case BIGNUM:
	return (make_big(stok.buf));
    case DECNUM:
	return (make_int((int) strtol(stok.buf, &e, 10)));
    case BINARY:
	return (read_bin(stok.buf));
    case OCTAL:
	return (read_oct(stok.buf));
    case HEXNUM:
	return (read_hex(stok.buf));
    case EXPTNUM:
	return (make_flt(atof(stok.buf)));
    case EXPTOVERF:
	error(FLT_OVERF, "read", NIL, 0);
	break;
    case EXPTUNDERF:
	error(FLT_UNDERF, "read", NIL, 0);
	break;
    case VECTOR:
	return (vector(read_list()));
    case ARRAY:
	n = atoi(stok.buf);
	return (array(n, sread()));
    case STRING:
	return (make_str(stok.buf));
    case CHARACTER:
	return (make_char(stok.buf));
    case SYMBOL:
	return (make_sym(stok.buf));
    case QUOTE:
	return (cons(make_sym("QUOTE"), cons(sread(), NIL)));
    case BACKQUOTE:
	return (cons(make_sym("QUASI-QUOTE"), cons(sread(), NIL)));
    case COMMA:
	{
	    get_token();
	    if (stok.type == ATMARK)
		return (cons
			(make_sym("UNQUOTE-SPLICING"),
			 cons(sread(), NIL)));
	    else {
		stok.flag = BACK;
		return (cons(make_sym("UNQUOTE"), cons(sread(), NIL)));
	    }
	}
    case FUNCTION:
	return (cons(make_sym("FUNCTION"), cons(sread(), NIL)));
    case LPAREN:
	return (read_list());
    case RPAREN:
	error(ILLEGAL_RPAREN, "read", NIL, 0);
    default:
	break;
    }
    error(ILLEGAL_INPUT, "read", NIL, 0);
    return (0);
}

int read_list(void)
{
    int rl_car, rl_cdr;

    get_token();
    if (stok.type == RPAREN)
	return (NIL);
    else if (stok.type == DOT) {
	rl_cdr = sread();
	if (rl_cdr == FEND) {
	    error(ILLEGAL_RPAREN, "read", make_sym("file end"), 0);
	}
	get_token();
	return (rl_cdr);
    } else {
	stok.flag = BACK;
	rl_car = sread();
	if (rl_car == FEND) {
	    error(ILLEGAL_RPAREN, "read", make_sym("file end"), 0);
	}
	rl_cdr = read_list();
	return (cons(rl_car, rl_cdr));
    }
}

int read_bin(char *buf)
{
    char str[BUFSIZE], *e;
    int pos, n, res, inc;

    n = strlen(buf);
    if (n <= 31)
	return (make_int((int) strtol(buf, &e, 2)));

    pos = 0;
    res = make_int(0);
    inc = make_int(2);

    while (pos < n) {
	int part;

	str[0] = buf[pos];
	str[1] = NUL;
	pos++;
	part = make_int((int) strtol(str, &e, 2));
	res = plus(mult(res, inc), part);
    }
    return (res);
}

int read_oct(char *buf)
{
    char str[BUFSIZE], *e;
    int pos, n, res, inc;

    n = strlen(buf);
    if (n <= 10)
	return (make_int((int) strtol(buf, &e, 8)));

    pos = 0;
    res = make_int(0);
    inc = make_int(8);

    while (pos < n) {
	int part;

	str[0] = buf[pos];
	str[1] = NUL;
	pos++;
	part = make_int((int) strtol(str, &e, 8));
	res = plus(mult(res, inc), part);
    }
    return (res);
}


int read_hex(char *buf)
{
    char str[BUFSIZE], *e;
    int pos, n, res, inc;

    n = strlen(buf);
    if (n <= 7)
	return (make_int((int) strtol(buf, &e, 16)));

    pos = 0;
    res = make_int(0);
    inc = make_int(16);

    while (pos < n) {
	int part;

	str[0] = buf[pos];
	str[1] = NUL;
	pos++;
	part = make_int((int) strtol(str, &e, 16));
	res = plus(mult(res, inc), part);
    }
    return (res);
}

/* -----print------------------ */
void print(int addr)
{
    switch (GET_TAG(addr)) {
    case INTN:
	print_int(addr);
	break;
    case FLTN:
	print_flt(GET_FLT(addr));
	break;
    case LONGN:
	print_long(addr);
	break;
    case BIGN:
	print_big(addr);
	break;
    case VEC:
	print_vec(addr);
	break;
    case ARR:
	print_arr(addr);
	break;
    case STR:
	print_str(addr);
	break;
    case CHR:
	print_char(addr);
	break;
    case SYM:
	print_sym(addr);
	break;
    case SUBR:
	print_obj("<subr>");
	break;
    case FSUBR:
	print_obj("<fsubr>");
	break;
    case FUNC:
	print_obj("<function>");
	break;
    case MACRO:
	print_obj("<macro>");
	break;
    case CLASS:
	print_class(addr);
	break;
    case STREAM:
	print_stm(addr);
	break;
    case GENERIC:
	print_obj("<generic>");
	break;
    case METHOD:
	print_obj("<method>");
	break;
    case INSTANCE:
	print_obj("<instance>");
	break;
    case LIS:
	output_char(output_stream, '(');
	print_list(addr);
	break;
    case DUMMY:
	print_obj("<undef*>");
	break;
    default:
	print_obj("<undef>");
	break;
    }
}

void print_int(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR)
	Fmt_fprint(GET_PORT(output_stream), "%d", GET_INT(addr));
    else {
	char str[SHORT_STRSIZE];
	Fmt_sfmt(str, SHORT_STRSIZE, "%d", GET_INT(addr));
	append_str(output_stream, str);
    }
}

void print_flt(double x)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	fprintf(GET_PORT(output_stream), "%g", x);
	if ((x - (int) x) == 0.0)
	    fprintf(GET_PORT(output_stream), ".0");
    } else {
	char str[SHORT_STRSIZE];
	snprintf(str, SHORT_STRSIZE, "%g", x);
	append_str(output_stream, str);
	if ((x - (int) x) == 0.0)
	    append_str(output_stream, ".0");
    }
}


void print_long(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
#ifdef __rpi__
	fprintf(GET_PORT(output_stream), "%lld", GET_LONG(addr));
#else
	Fmt_fprint(GET_PORT(output_stream), "%D", GET_LONG(addr));
#endif
    } else {
	char str[SHORT_STRSIZE];
#ifdef __rpi__
	sprintf(str, SHORT_STRSIZE, "%lld", GET_LONG(addr));
#else
	Fmt_sfmt(str, SHORT_STRSIZE, "%D", GET_LONG(addr));
#endif
	append_str(output_stream, str);
    }
}


void print_list(int addr)
{
    if (IS_NIL(addr)) {
	output_char(output_stream, ')');
    } else if ((!(listp(cdr(addr)))) && (!(nullp(cdr(addr))))) {
	print(car(addr));
	output_str(output_stream, " . ");
	print(cdr(addr));
	output_char(output_stream, ')');
    } else {
	print(GET_CAR(addr));
	if (!(IS_NIL(GET_CDR(addr)))) {
	    output_char(output_stream, ' ');
	}
	print_list(GET_CDR(addr));
    }
}

void print_vec(int x)
{
    int len, i;

    output_str(output_stream, "#(");
    len = cdr(x);

    for (i = 0; i < len; i++) {
	print(GET_VEC_ELT(x, i));
	if (i != len - 1) {
	    output_char(output_stream, ' ');
	}
    }
    output_char(output_stream, ')');
}

void print_arr(int x)
{
    int i, size, st, ls, dim;

    st = ls = GET_CDR(x);
    size = 1;
    dim = length(ls);
    while (!nullp(ls)) {
	size = GET_INT(car(ls)) * size;
	ls = cdr(ls);
    }
    ls = NIL;
    for (i = 0; i < size; i++)
	ls = cons(GET_VEC_ELT(x, i), ls);
    ls = reverse(ls);
    if (GET_OPT(output_stream) != EISL_INSTR)
	Fmt_fprint(GET_PORT(output_stream), "#%da", dim);
    else {
	char str[SHORT_STRSIZE];
	Fmt_sfmt(str, SHORT_STRSIZE, "#%da", dim);
	append_str(output_stream, str);
    }
    if (dim == 0)
	print(car(ls));
    else
	print(structured(ls, st));
}


void print_str(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	Fmt_fprint(GET_PORT(output_stream), "\"%s\"", GET_NAME(addr));
    } else {
	Fmt_sfmt(stream_str, STRSIZE, "\"%s\"", GET_NAME(addr));
	append_str(output_stream, stream_str);
    }
}

void print_char(int addr)
{
    output_str(output_stream, "#\\");
    switch (GET_CHAR(addr)) {
    case BEL:
	output_str(output_stream, "alarm");
	break;
    case BS:
	output_str(output_stream, "backspace");
	break;
    case DEL:
	output_str(output_stream, "delete");
	break;
    case ESC:
	output_str(output_stream, "escape");
	break;
    case RET:
	output_str(output_stream, "return");
	break;
    case SPACE:
	output_str(output_stream, "space");
	break;
    case EOL:
	output_str(output_stream, "newline");
	break;
    case NUL:
	output_str(output_stream, "null");
	break;
    case TAB:
	output_str(output_stream, "tab");
	break;
    case 1:
	output_str(output_stream, "^A");
	break;
    case 2:
	output_str(output_stream, "^B");
	break;
    case 3:
	output_str(output_stream, "^C");
	break;
    case 4:
	output_str(output_stream, "^D");
	break;
    case 5:
	output_str(output_stream, "^E");
	break;
    case 6:
	output_str(output_stream, "^F");
	break;
    case 11:
	output_str(output_stream, "^K");
	break;
    case 12:
	output_str(output_stream, "^L");
	break;
    case 14:
	output_str(output_stream, "^N");
	break;
    case 15:
	output_str(output_stream, "^O");
	break;
    case 16:
	output_str(output_stream, "^P");
	break;
    case 17:
	output_str(output_stream, "^Q");
	break;
    case 18:
	output_str(output_stream, "^R");
	break;
    case 19:
	output_str(output_stream, "^S");
	break;
    case 20:
	output_str(output_stream, "^T");
	break;
    case 21:
	output_str(output_stream, "^U");
	break;
    case 22:
	output_str(output_stream, "^V");
	break;
    case 23:
	output_str(output_stream, "^W");
	break;
    case 24:
	output_str(output_stream, "^X");
	break;
    case 25:
	output_str(output_stream, "^Y");
	break;
    case 26:
	output_str(output_stream, "^Z");
	break;
    default:
	output_str(output_stream, GET_NAME(addr));
    }
}

void print_sym(int addr)
{
    output_str(output_stream, GET_NAME(addr));
}

void print_obj(const char *str)
{
    output_str(output_stream, str);
}

void print_class(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR)
	Fmt_fprint(GET_PORT(output_stream), "<class %s>", GET_NAME(addr));
    else {
	Fmt_sfmt(stream_str, STRSIZE, "<class %s>", GET_NAME(addr));
	append_str(output_stream, stream_str);
    }
}

void print_stm(int addr)
{
    const char *name;

    REQUIRE(GET_TAG(addr) == STREAM);
    const signed char opt = GET_OPT(addr);
    if (opt == EISL_OUTSTR || opt == EISL_INSTR) {
	name = "<string>";
    } else {
	name = GET_NAME(addr);
    }
    if (GET_OPT(output_stream) != EISL_OUTSTR)
	Fmt_fprint(GET_PORT(output_stream), "<stream %s>", name);
    else {
	Fmt_sfmt(GET_NAME(output_stream), STRSIZE, "<stream %s>", name);
	append_str(output_stream, stream_str);
    }
}

static void clean_stdin(void)
{
    int c;
    do {
	c = getchar();
    }
    while (c != '\n' && c != EOF);
}

/* --------eval--------------- */
int eval(int addr, int th)
{
    int val, res, temp;
    char c;
    double st, en;

    (void) check_gbc(th);

    if (IS_NIL(addr) || IS_T(addr))
	return (addr);
    else if (numberp(addr))
	return (addr);
    else if (vectorp(addr))
	return (addr);
    else if (arrayp(addr))
	return (addr);
    else if (stringp(addr))
	return (addr);
    else if (charp(addr))
	return (addr);
    else if (symbolp(addr)) {
	res = find_env(addr, th);
	if (res != FAILSE)
	    return (res);
	else {
	    if (GET_OPT(addr) == GLOBAL)
		return (GET_CDR(addr));
	    else if (GET_OPT(addr) == CONSTN)
		return (GET_CDR(addr));
	    else
		error(UNDEF_VAR, "eval", addr, th);

	}
    } else if (listp(addr)) {
	if (back_flag)
	    store_backtrace(addr);
	if (stepper_flag) {
	    print(addr);
	    putchar('\n');
	    clean_stdin();
	    c = getc(stdin);
	    if (c == 'q')
		debugger(th);
	}

	if ((symbolp(car(addr))) && (HAS_NAME(car(addr), "QUOTE"))) {
	    if (improper_list_p(cdr(addr)))
		error(ILLEGAL_ARGS, "quote", cdr(addr), th);
	    else if (length(cdr(addr)) != 1)
		error(ILLEGAL_ARGS, "quote", cdr(addr), th);
	    else
		return (cadr(addr));
	} else if ((symbolp(car(addr)))
		   && (HAS_NAME(car(addr), "QUASI-QUOTE"))) {
	    temp = quasi_transfer(cadr(addr), 0);
	    shelter_push(temp, th);
	    res = eval(temp, th);
	    shelter_pop(th);
	    return (res);
	} else if (subrp(car(addr))) {
	    st = getETime();
	    res = apply(caar(addr), evlis(cdr(addr), th), th);
	    en = getETime();
	    if (prof_sw == 1)
		profiler(car(addr), en - st);
	    return (res);
	} else if (fsubrp(car(addr))) {
	    st = getETime();
	    res = apply(caar(addr), cdr(addr), th);
	    en = getETime();
	    if (prof_sw == 1)
		profiler(car(addr), en - st);
	    return (res);
	} else if ((val = functionp(car(addr)))) {
	    if (GET_CDR(car(addr)) != NIL)
		error(UNDEF_FUN, "eval", addr, th);
	    temp = evlis(cdr(addr), th);
	    examin_sym = car(addr);
	    st = getETime();
	    res = apply(val, temp, th);
	    en = getETime();
	    if (prof_sw == 2)
		profiler(car(addr), en - st);
	    return (res);
	} else if (macrop(car(addr))) {
	    examin_sym = car(addr);
	    return (apply(caar(addr), cdr(addr), th));
	} else if (genericp(car(addr))) {
	    examin_sym = car(addr);
	    st = getETime();
	    res = apply(caar(addr), evlis(cdr(addr), th), th);
	    en = getETime();
	    if (prof_sw == 2)
		profiler(car(addr), en - st);
	    return (res);
	} else if (listp(car(addr)))
	    return (apply(eval(car(addr), th), evlis(cdr(addr), th), th));
	else
	    error(UNDEF_FUN, "eval", car(addr), th);

    }
    error(UNDEF_FUN, "eval", addr, th);
    return (0);
}

DEF_GETTER(char, TR, trace, NIL)
int apply(int func, int args, int th)
{
    int varlist, body, res, i, n, pexist, qexist, trace;
    REQUIRE((GET_TAG(func) == FSUBR || GET_TAG(func) == SUBR
	     || GET_TAG(func) == FUNC || GET_TAG(func) == MACRO
	     || GET_TAG(func) == GENERIC) && (GET_TAG(args) == LIS
					      || GET_TAG(args) == SYM));


    res = NIL;
    pexist = 0;
    qexist = 0;
    trace = 0;

    if (try_flag == true && getETime() >= try_timer)
	return (FEND);

    switch (GET_TAG(func)) {
    case SUBR:
	return ((GET_SUBR(func)) (args, th));
    case FSUBR:
	return ((GET_SUBR(func)) (args, th));
    case FUNC:


	if (try_flag == true)
	    try_res = cons(args, try_res);
	if (GET_TR(examin_sym) == 1) {
	    trace = examin_sym;
	    n = GET_TR(func);
	    SET_TR(func, n + 1);
	    for (i = 0; i < n; i++)
		putchar(' ');
	    fputs("ENTERING: ", stdout);
	    print(trace);
	    putchar(' ');
	    print(args);
	    putchar('\n');
	}
	shelter_push(func, th);
	shelter_push(args, th);
	push(ep[th], th);
	push(cp, th);
	ep[th] = GET_CDR(func);


	/* if lambda is generated during eval method, lambda saved method
	 * and argument
	 * restore the method and argument.
	 */
	if (GET_PROP(func) != NIL) {
	    next_method = car(GET_PROP(func));
	    generic_vars = cdr(GET_PROP(func));
	    generic_func = T;	/* to avoid error check in (call-next-method) */
	}

	varlist = car(GET_CAR(func));
	if (GET_OPT(func) >= 0) {
	    if (length(args) != (int) GET_OPT(func))
		error(WRONG_ARGS, GET_NAME(func), args, th);
	} else {
	    if (length(args) < (-1 * (int) GET_OPT(func) - 2))
		error(WRONG_ARGS, GET_NAME(func), args, th);
	}
	body = cdr(GET_CAR(func));
	bind_arg(varlist, args, th);
	while (!(IS_NIL(body))) {
	    res = eval(car(body), th);
	    body = cdr(body);
	}
	unbind(th);
	if (trace != NIL) {
	    n = GET_TR(func);
	    n = n - 1;
	    SET_TR(func, n);
	    for (i = 0; i < n; i++)
		putchar(' ');
	    fputs("EXITING:  ", stdout);
	    print(trace);
	    putchar(' ');
	    print(res);
	    putchar('\n');
	}
	cp = pop(th);
	ep[th] = pop(th);
	shelter_pop(th);
	shelter_pop(th);
	return (res);
    case MACRO:
	{
	    int macrofunc;

	    if (improper_list_p(args))
		error(IMPROPER_ARGS, "apply", args, th);
	    macrofunc = GET_CAR(func);
	    varlist = car(GET_CAR(macrofunc));
	    if (GET_OPT(func) >= 0) {
		if (length(args) != (int) GET_OPT(func))
		    error(WRONG_ARGS, GET_NAME(func), args, th);
	    } else {
		if (length(args) < (-1 * (int) GET_OPT(func) - 2))
		    error(WRONG_ARGS, GET_NAME(func), args, th);
	    }
	    body = cdr(GET_CAR(macrofunc));
	    bind_arg(varlist, args, th);
	    while (!(IS_NIL(body))) {
		shelter_push(body, th);
		res = eval(car(body), th);
		if (listp(res) && car(res) == make_sym("DEFMACRO")) {
		    //if defmacro has inner defmacro, not occur error 
		    ignore_topchk = true;
		}
		shelter_pop(th);
		body = cdr(body);
	    }
	    unbind(th);
	    shelter_push(res, th);
	    res = eval(res, th);
	    shelter_pop(th);
	    return (res);
	}

    case GENERIC:
	{
	    int save1, save2, save3;
	    if (GET_OPT(func) >= 0) {
		if (length(args) != (int) GET_OPT(func))
		    error(WRONG_ARGS, GET_NAME(func), args, th);
	    } else {
		if (length(args) < (-1 * (int) GET_OPT(func) - 2))
		    error(WRONG_ARGS, GET_NAME(func), args, th);
	    }
	    save1 = generic_func;
	    save2 = generic_vars;
	    save3 = next_method;
	    generic_func = func;
	    generic_vars = copy(args);
	    next_method = GET_CDR(func);
	    push(make_int(cp), th);
	    if (GET_TR(examin_sym) == 1) {
		trace = examin_sym;
		n = GET_TR(func);
		SET_TR(func, n + 1);
		for (i = 0; i < n; i++)
		    putchar(' ');
		fputs("ENTERING: ", stdout);
		print(trace);
		putchar(' ');
		print(args);
		putchar('\n');
	    }
	    while (!nullp(next_method)) {
		varlist = car(GET_CAR(car(next_method)));
		/* adaptp(x,y) if sameclass or x is super-classs return 1 else 0 */
		if (adaptp(varlist, args)) {
		    /* if only qualifier or sameclass-primary, eval method; */
		    if ((GET_OPT(car(next_method)) == AROUND
			 || GET_OPT(car(next_method)) == BEFORE
			 || GET_OPT(car(next_method)) == AFTER)
			|| (GET_OPT(car(next_method)) == PRIMARY
			    && adaptp(varlist, args) && pexist == 0)) {

			if (GET_OPT(car(next_method)) == PRIMARY) {
			    /* primary method must executes only once. */
			    if (pexist == 1) {
				goto exit;
			    }
			    pexist = 1;
			} else {
			    qexist = 1;
			}
			varlist = genlamlis_to_lamlis(varlist);
			body = cdr(GET_CAR(car(next_method)));
			multiple_call_next_method =
			    has_multiple_call_next_method_p(body);
			bind_arg(varlist, args, th);
			while (!nullp(body)) {
			    res = eval(car(body), th);
			    body = cdr(body);
			}
			unbind(th);
		    }
		    if (GET_OPT(car(next_method)) == AROUND) {
			goto exit;
		    }
		}
		next_method = cdr(next_method);
	    }
	    if (pexist == 0 && qexist == 0) {
		error(NOT_EXIST_METHOD, GET_NAME(generic_func), args, th);
	    }
	  exit:
	    generic_func = save1;
	    generic_vars = save2;
	    next_method = save3;
	    cp = pop(th);
	    return (res);
	}
    default:
	error(NOT_FUNC, "apply", list2(func, args), th);
    }
    return (0);
}

void bind_arg(int varlist, int arglist, int th)
{
    int arg1, arg2;

    push(ep[th], th);
    push(cp, th);
    while (!(IS_NIL(varlist))) {
	if (cddr(varlist) == NIL && (car(varlist) == make_sym(":REST")
				     || car(varlist) == make_sym("&REST"))) {
	    arg1 = cadr(varlist);
	    arg2 = arglist;
	    add_lex_env(arg1, arg2, th);
	    return;
	} else {
	    arg1 = car(varlist);
	    arg2 = car(arglist);
	    add_lex_env(arg1, arg2, th);
	    varlist = cdr(varlist);
	    arglist = cdr(arglist);
	}
    }
}

void unbind(int th)
{
    cp = pop(th);
    ep[th] = pop(th);
}


int evlis(int addr, int th)
{
    arg_push(addr, th);
    top_flag = false;
    if (IS_NIL(addr)) {
	arg_pop(th);
	return (addr);
    } else {
	int car_addr, cdr_addr;

	car_addr = eval(car(addr), th);
	arg_push(car_addr, th);
	cdr_addr = evlis(cdr(addr), th);
	car_addr = arg_pop(th);
	(void) arg_pop(th);
	return (tcons(car_addr, cdr_addr, th));
    }
}

/*
 * check class matching of argument of lambda and received argument. 
 * if sameclass or varlist is super-class of arglist return 1, else return 0. 
 */
int adaptp(int varlist, int arglist)
{

    if (nullp(varlist) && nullp(arglist))
	return (1);
    else if (symbolp(car(varlist)))
	return (adaptp(cdr(varlist), cdr(arglist)));
    else if (eqp(make_sym(":rest"), car(varlist)))
	return (1);
    else if (eqp(make_sym("&rest"), car(varlist)))
	return (1);
    else if (GET_AUX(cadar(varlist)) == GET_AUX(car(arglist)))	/* equal class */
	return (adaptp(cdr(varlist), cdr(arglist)));
    else if (subclassp(GET_AUX(car(arglist)), GET_AUX(cadar(varlist))))	/* subclass */
	return (adaptp(cdr(varlist), cdr(arglist)));
    else
	return (0);
}


/*
 * check class matching of argument of lambda and received argument. 
 * only if same class return 1 else return 0.
 * built-in class, if varlist is subclass of arglist return 1. 
 */
int matchp(int varlist, int arglist)
{

    if (nullp(varlist) && nullp(arglist))
	return (1);
    else if (symbolp(car(varlist)))
	return (matchp(cdr(varlist), cdr(arglist)));
    else if (eqp(make_sym(":rest"), car(varlist)))
	return (1);
    else if (eqp(make_sym("&rest"), car(varlist)))
	return (1);
    else if (GET_AUX(cadar(varlist)) == GET_AUX(car(arglist)))	/* match class */
	return (matchp(cdr(varlist), cdr(arglist)));
    /* when built-in class, subclass is also eqclass. */
    else if (GET_OPT(cadar(varlist)) == SYSTEM
	     && subclassp(GET_AUX(car(arglist)), GET_AUX(cadar(varlist))))
	return (matchp(cdr(varlist), cdr(arglist)));
    else
	return (0);
}



/*
 * change lambda list of function to normal argument. ex ((x <number>)(y
 * <list>)) -> (x y) 
 */
int genlamlis_to_lamlis(int varlist)
{
    int res;

    res = NIL;
    while (!nullp(varlist)) {
	if (symbolp(car(varlist)))
	    res = cons(car(varlist), res);
	else
	    res = cons(caar(varlist), res);

	varlist = cdr(varlist);
    }
    return (reverse(res));
}


/* for stack to store ep(environment) */
int push(int pt, int th)
{
    if (sp[th] >= STACKSIZE)
	error(STACK_OVERF, "push", NIL, th);

    stack[sp[th]++][th] = pt;
    return (T);
}

int pop(int th)
{
    int res;

    if (sp[th] <= 0)
	error(STACK_UNDERF, "pop", NIL, th);
    res = stack[--sp[th]][th];
    return (res);
}

/* push/pop of arglist */
int arg_push(int addr, int th)
{

    argstk[ap[th]++][th] = addr;
    return (T);
}

int arg_pop(int th)
{
    int res;

    res = argstk[--ap[th]][th];
    return (res);
}

/* shelter push/pop */
int shelter_push(int addr, int th)
{
    if (lp[th] >= STACKSIZE)
	error(SHELTER_OVERF, "shelter_push", NIL, th);

    shelter[lp[th]++][th] = addr;
    return (T);
}

int shelter_pop(int th)
{
    int res;

    if (lp[th] <= 0)
	error(SHELTER_UNDERF, "shelter_pop", NIL, th);

    res = shelter[--lp[th]][th];
    return (res);
}

/* system function regist subr to environment. */
void def_subr(const char *symname, int (*func)(int, int))
{
    bind_func(symname, SUBR, func);
}

/* regist fsubr(not eval argument) */
void def_fsubr(const char *symname, int (*func)(int, int))
{
    bind_func(symname, FSUBR, func);
}


static inline void SET_SUBR(int addr, subr_t x)
{
    REQUIRE(CELLRANGE(addr) &&
	    (GET_TAG(addr) == SUBR || GET_TAG(addr) == FSUBR));
    heap[addr].val.car.subr = x;
}

void bind_func(const char *name, tag_t tag, int (*func)(int, int))
{
    int sym, val;

    sym = make_sym(name);
    val = freshcell();
    SET_TAG(val, tag);
    SET_SUBR(val, func);
    SET_CDR(val, 0);
    SET_AUX(val, cfunction);	/* class function */
    SET_CAR(sym, val);
}

void bind_macro(char *name, int addr)
{
    int sym, val1, val2;

    sym = make_sym(name);
    val1 = freshcell();
    SET_TAG(val1, FUNC);
    SET_CAR(val1, addr);
    SET_CDR(val1, 0);
    val2 = freshcell();
    SET_TAG(val2, MACRO);
    TRY heap[val2].name = Str_dup(name, 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "makemacro", NIL, 0);
    END_TRY;
    SET_CAR(val2, val1);
    SET_CDR(val2, 0);
    SET_AUX(val2, cfunction);	/* class */
    SET_OPT(val2, (signed char) count_args(car(addr)));	/* count of args */
    SET_CAR(sym, val2);
}

void bind_const(const char *name, int obj)
{
    int sym;

    sym = make_sym(name);
    SET_CDR(sym, obj);
    SET_OPT(sym, CONSTN);
}


void store_backtrace(int x)
{
    int i;

    for (i = 1; i < BACKSIZE; i++) {
	int y;

	y = backtrace[i];
	backtrace[i - 1] = y;
    }
    backtrace[BACKSIZE - 1] = x;
}


/* --------qusi quote--------------- */
int quasi_transfer(int x, int n)
{
    // printf("%d",n); print(x);putchar('\n');

    if (nullp(x))
	return (NIL);
    else if (vectorp(x))
	return (quasi_vector_transfer(x, n));
    else if (arrayp(x))
	return (quasi_array_transfer(x, n));
    else if (atomp(x))
	return (list2(make_sym("QUOTE"), x));
    else if (listp(x) && eqp(car(x), make_sym("UNQUOTE")) && n == 0)
	return (cadr(x));
    else if (listp(x) && eqp(car(x), make_sym("UNQUOTE-SPLICING"))
	     && n == 0)
	return (cadr(x));
    else if (listp(x) && eqp(car(x), make_sym("QUASI-QUOTE")))
	return (list3(make_sym("LIST"),
		      list2(make_sym("QUOTE"), make_sym("QUASI-QUOTE")),
		      quasi_transfer(cadr(x), n + 1)));
    else if (listp(x) && eqp(caar(x), make_sym("UNQUOTE")) && n == 0)
	return (list3
		(make_sym("CONS"), cadar(x), quasi_transfer(cdr(x), n)));
    else if (listp(x) && eqp(caar(x), make_sym("UNQUOTE-SPLICING"))
	     && n == 0)
	return (list3
		(make_sym("APPEND"), cadar(x), quasi_transfer(cdr(x), n)));
    else if (listp(x) && eqp(caar(x), make_sym("UNQUOTE")))
	return (list3(make_sym("CONS"),
		      list3(make_sym("LIST"),
			    list2(make_sym("QUOTE"), make_sym("UNQUOTE")),
			    quasi_transfer(cadar(x), n - 1)),
		      quasi_transfer(cdr(x), n)));
    else if (listp(x) && eqp(caar(x), make_sym("UNQUOTE-SPLICING")))
	return (list3(make_sym("CONS"),
		      list3(make_sym("LIST"),
			    list2(make_sym("QUOTE"),
				  make_sym("UNQUOTE-SPLICING")),
			    quasi_transfer(cadar(x), n - 1)),
		      quasi_transfer(cdr(x), n)));
    else
	return (list3
		(make_sym("CONS"), quasi_transfer(car(x), n),
		 quasi_transfer(cdr(x), n)));
}

int quasi_vector_transfer(int x, int n)
{
    int y;

    y = vector(eval(quasi_transfer(vector_to_list(x), n), 0));
    return (y);
}


int quasi_array_transfer(int x, int n)
{
    int i, size, ls;

    ls = GET_CDR(x);
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
    } else {
	size = 1;
    }

    for (i = 0; i < size; i++) {
	SET_VEC_ELT(x, i, eval(quasi_transfer(GET_VEC_ELT(x, i), n), 0));
    }
    return (x);
}
