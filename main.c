/*
 * Easy-ISLisp (ISLisp) written by kenichi sasagawa 2016/4~ 
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
#include <curses.h>
#include <term.h>
#include "eisl.h"
#include "mem.h"
#include "fmt.h"
#include "except.h"
#include "str.h"
#include "long.h"
#include "eiffel.h"

// ------pointer----
int             ep;		// environment pointer
int             dp;		// dynamic pointer
int             hp;		// heap pointer for mark and sweep
int             sp;		// stack pointer
int             fc;		// free counter
int             ap;		// arglist pointer
int             lp;		// shelter pointer
int             wp;		// working pointer for copy GC


// ------class-----
int             cobject;
int             cbasic_array;
int             cbasic_array_star;
int             cgeneral_array_star;
int             cbasic_vector;
int             cgeneral_vector;
int             cstring;
int             cbuilt_in_class;
int             ccharacter;
int             cfunction;
int             cgeneric_function;
int             cstandard_generic_function;
int             clist;
int             ccons;
int             cnull;
int             csymbol;
int             cnumber;
int             cfloat;
int             cinteger;
int             cserious_condition;
int             cerror;
int             carithmetic_error;
int             cdivision_by_zero;
int             cfloating_point_overflow;
int             cfloating_point_underflow;
int             ccontrol_error;
int             cparse_error;
int             cprogram_error;
int             cdomain_error;
int             cclass_error;
int             cundefined_entity;
int             cunbound_variable;
int             cundefined_function;
int             csimple_error;
int             cstream_error;
int             cend_of_stream;
int             cstorage_exhausted;
int             cstandard_class;
int             cstandard_object;
int             cstream;
int             cinvalid;
int             cfixnum;
int             clongnum;
int             cbignum;


// stream
int             standard_input;
int             standard_output;
int             standard_error;
int             input_stream;
int             output_stream;
int             error_stream;
char            stream_str[STRSIZE];
int             charcnt;	// for format-tab. store number of chars
				// up to now.


// read scaner
token           stok = { '\0', GO, OTHER, {'\0'} };

int             line;
int             column;
int             buffer[COL_SIZE + 1][NUM_HISTORY];
int             buffer1[COL_SIZE + 1];


// heap and stack
cell            heap[CELLSIZE];
int             stack[STACKSIZE];
int             argstk[STACKSIZE];
int             cell_hash_table[HASHTBSIZE];
int             shelter[STACKSIZE];
int             dynamic[DYNSIZE][2];

// object oriented
int             generic_func;	// generic function in eval.
int             generic_vars;	// args list of generic function in eval.
int             next_method;	// head address of finded method.
int             generic_list = NIL;	// symbol list of generic
					// function.

// flag
int             gArgC;
char          **gArgV;
bool            gbc_flag = false;	// false=GC not display ,true= do
					// display.
int             genint = 1;	// integer of gensym.
bool            simp_flag = true;	// true=simplify, false=Not for
					// bignum
bool            ignore_flag = false;	// false=normal,true=ignore error
bool            open_flag = false;	// false=normal,true=now loading
bool            top_flag = true;	// true=top-level,false=not-top-level
bool            redef_flag = false;	// true=redefine-class,false=not-redefine
bool            start_flag = true;	// true=line-start,false=not-line-start
bool            back_flag = true;	// for backtrace,
					// true=on,false=off
bool            ignore_topchk = false;	// for FAST
					// compilertrue=ignore,false=normal
bool            repl_flag = true;	// for REPL read_line 1=on, 0=off
volatile sig_atomic_t exit_flag = 0;	// true= ctrl+C
bool            greeting_flag = true;	// for (quit)
bool            script_flag = false;	// for -s option
bool            handling_resource_err = false;	// stop infinite recursion
bool            looking_for_shebang = false;	// skip over #!

// switch
int             gc_sw = 0;	// 0= mark-and-sweep-GC 1= copy-GC
int             area_sw = 1;	// 1= lower area 2=higher area

// longjmp control and etc
Except_T        Restart_Repl = { "Restart REPL" }, Exit_Interp =
    { "Exit interpreter" };
jmp_buf         block_buf[NESTED_BLOCKS_MAX];
int             block_env[NESTED_BLOCKS_MAX][2];
jmp_buf         catch_buf[10][50];
int             catch_env[10][50];
Except_T        Ignored_Error = { "Ignored error" };	// for
							// ignore-errors

int             block_tag[CTRLSTK];	// array of tag
int             catch_tag[CTRLSTK];
int             unwind_buf[CTRLSTK];
int             catch_symbols = NIL;	// to clear tag data
int             block_pt;	// index of block. following are similer
int             catch_pt = 0;	// catch counter
int             unwind_pt;	// lambda address for unwind-protect
int             block_arg;	// receive argument of block
int             catch_arg;	// receive argument of catch
int             tagbody_tag = NIL;	// tag address fo tagbody
int             error_handler;	// for store first argument of
				// with-handler
int             trace_list = NIL;	// function list of trace
int             backtrace[BACKSIZE];

// -----debugger-----
int             examin_sym;
int             stepper_flag = 0;


int             ed_lparen_col;
int             ed_rparen_col;
const char     *ed_candidate[COMPLETION_CANDIDATES_MAX];
int             ed_candidate_pt;
const short     ed_syntax_color = COLOR_RED;
const short     ed_builtin_color = COLOR_CYAN;
const short     ed_extended_color = COLOR_MAGENTA;
const short     ed_string_color = COLOR_YELLOW;
const short     ed_comment_color = COLOR_BLUE;
int             ed_incomment = -1;	// #|...|# comment

// Defaults, should be filled in later
char            ed_key_up = 'A';
char            ed_key_down = 'B';
char            ed_key_right = 'C';
char            ed_key_left = 'D';

static void
usage(void)
{
    puts("List of options:\n"
	 "-c           -- EISL starts after reading compiler.lsp.\n"
	 "-f           -- EISL starts after reading formatter.lsp.\n"
	 "-h           -- display help.\n"
	 "-l filename  -- EISL starts after reading the file.\n"
	 "-r           -- EISL does not use editable REPL.\n"
	 "-s filename  -- EISL runs the file with script mode.\n"
	 "-v           -- display version number.");
}

static inline void
maybe_greet(void)
{
    if (greeting_flag)
	Fmt_print("Easy-ISLisp Ver%1.2f\n", VERSION);
}

int
main(int argc, char *argv[])
{
    int             errret;

    Fmt_register('D', cvt_D);
    if (setupterm((char *) 0, 1, &errret) == ERR ||
	key_up == NULL || key_down == NULL ||
	key_right == NULL || key_left == NULL) {
	repl_flag = false;
    } else {
	ed_key_down = key_down[2];
	ed_key_left = key_left[2];
	ed_key_right = key_right[2];
	ed_key_up = key_up[2];
    }

    initcell();
    initclass();
    initstream();
    initsubr();
    initexsubr();
    initsyntax();
    initgeneric();
    signal(SIGINT, signal_handler_c);

    input_stream = standard_input;
    output_stream = standard_output;
    error_stream = standard_error;

    int             ch;
    char           *script_arg;

    if (access("startup.lsp", R_OK) == 0) {
	f_load(list1(makestr("startup.lsp")));
    }
    while ((ch = getopt(argc, argv, "l:cfs:rhv")) != -1) {
	char           *str;

	switch (ch) {
	case 'l':
	    f_load(list1(makestr(optarg)));
	    break;
	case 'c':
	    str = library_file("compiler.lsp");
	    f_load(list1(makestr(str)));
	    FREE(str);
	    break;
	case 'f':
	    str = library_file("formatter.lsp");
	    f_load(list1(makestr(str)));
	    FREE(str);
	    break;
	case 's':
	    if (access(optarg, R_OK) == -1) {
		puts("File doesn't exist.");
		exit(EXIT_FAILURE);
	    }
	    repl_flag = false;
	    script_flag = true;
	    looking_for_shebang = true;
	    script_arg = optarg;
	    break;
	case 'r':
	    repl_flag = false;
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
	f_load(list1(makestr(script_arg)));
	exit(EXIT_SUCCESS);
    }
    volatile bool   quit = false;
    do {
	maybe_greet();
	TRY while       (1) {
	    initpt();
	    fputs("> ", stdout);
	    print(eval(sread()));
	    putchar('\n');
	    if (redef_flag)
		redef_generic();
	}
	EXCEPT(Restart_Repl);
	EXCEPT(Exit_Interp)
	    quit = true;
	END_TRY;
    } while (!quit);
}

char           *
library_file(const char *basename)
{
    char           *prefix;

    if ((prefix = getenv("EASY_ISLISP")) != NULL) {
	return Str_catv(prefix, 1, 0, "/library/", 1, 0, basename, 1, 0,
			NULL);
    }
    return Str_catv(getenv("HOME"), 1, 0, "/eisl/library/", 1, 0, basename,
		    1, 0, NULL);
}

void
initpt(void)
{
    int             ls;

    ep = 0;
    sp = 0;
    ap = 0;
    lp = 0;
    ls = catch_symbols;
    while (!nullp(ls)) {
	SET_PROP(car(ls), 0);
	SET_OPT(car(ls), 0);
	ls = cdr(ls);
    }
    block_pt = 0;
    catch_pt = 0;
    unwind_pt = 0;
    error_handler = NIL;
    top_flag = true;
    start_flag = true;
    charcnt = 0;
    // clear nest level of tracing function.
    ls = trace_list;
    while (!nullp(ls)) {
	SET_TR(GET_CAR(car(ls)), 0);
	ls = cdr(ls);
    }
}


void
signal_handler_c(int signo __unused)
{
    exit_flag = 1;
}




// -------read()--------
int
readc(void)
{
    int             c;
    if (input_stream == standard_input && repl_flag)
	c = read_line(1);
    else if (GET_OPT(input_stream) != EISL_INSTR) {
	c = getc(GET_PORT(input_stream));
	// ctrl+D
	// if not script-mode quit system
	if (!script_flag && input_stream == standard_input && c == EOF) {
	    greeting_flag = false;
	    putchar('\n');
	    RAISE(Exit_Interp);
	} else			// if script-mode return(EOF)
	    return (c);

    } else {
	c = GET_NAME(input_stream)[GET_CDR(input_stream)];
	SET_CDR(input_stream, GET_CDR(input_stream) + 1);
	if (c == '\\') {
	    c = GET_NAME(input_stream)[GET_CDR(input_stream)];
	    SET_CDR(input_stream, GET_CDR(input_stream) + 1);
	} else if (c == NUL) {
	    c = EOF;
	    SET_CDR(input_stream, GET_CDR(input_stream) - 1);
	}
    }

    if (c == EOL) {
	line++;
	column = 0;
    } else
	column++;

    return (c);
}

void
unreadc(char c)
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



void
gettoken(void)
{
    int             c;
    int             pos;
    int             res;

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

    // skip comment line
    // if find EOF at end of line, return FILEEND.
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
    // if end of file,return FILEEND.
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
    case '"':{
	    c = readc();
	    pos = 0;
	    while (c != '"') {
		stok.buf[pos++] = c;
		if (c == '\\') {
		    c = readc();
		    stok.buf[pos++] = c;
		}
		if (c == EOF) {
		    error(SYSTEM_ERR, "not exist right hand double quote",
			  NIL);
		}
		c = readc();
	    }
	    stok.buf[pos] = NUL;
	    stok.type = STRING;
	    break;
	}
    case '#':{
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
		stok.buf[pos++] = c;
		if (c == ' ')
		    goto chskip;

		while (((c = readc()) != EOL) && (c != EOF)
		       && (pos < BUFSIZE - 1) && (c != SPACE) && (c != '(')
		       && (c != ')')) {
		    stok.buf[pos++] = c;
		}

	      chskip:
		stok.buf[pos] = NUL;
		stok.type = CHARACTER;
		if (c == EOF)
		    stok.ch = ' ';
		else
		    stok.ch = c;
		break;
	    } else if (isdigit(c)) {
		pos = 0;
		while (isdigit(c)) {
		    stok.buf[pos] = c;
		    pos++;
		    c = readc();
		}
		stok.buf[pos] = NUL;
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
     /*FALLTHROUGH*/ default:{
	    pos = 0;
	    stok.buf[pos++] = c;
	    while (((c = readc()) != EOL) && (c != EOF)
		   && (pos < BUFSIZE - 1) && (c != SPACE) && (c != '(')
		   && (c != ')') && (c != '`') && (c != ',') && (c != '@'))
		stok.buf[pos++] = c;

	    stok.buf[pos] = NUL;
	    stok.ch = c;

	    if (flttoken(stok.buf)) {
		stok.type = FLOAT_N;
		break;
	    }
	    // first step,check bignum. inttoken() ignores number of
	    // digits.
	    if (bignumtoken(stok.buf)) {
		stok.type = BIGNUM;
		break;
	    }
	    if (inttoken(stok.buf)) {
		stok.type = INTEGER;
		break;
	    }
	    if (inttoken_nsgn(stok.buf)) {
		stok.type = INTEGER;
		break;
	    }
	    if (bintoken(stok.buf)) {
		stok.type = BINARY;
		break;
	    }
	    if (octtoken(stok.buf)) {
		stok.type = OCTAL;
		break;
	    }
	    if (dectoken(stok.buf)) {
		stok.type = DECNUM;
		break;
	    }
	    if (hextoken(stok.buf)) {
		stok.type = HEXNUM;
		break;
	    }
	    if ((res = expttoken(stok.buf))) {
		if (res == 2)
		    stok.type = EXPTOVERF;
		else if (res == 3)
		    stok.type = EXPTUNDERF;
		else
		    stok.type = EXPTNUM;
		break;
	    }
	    if (symboltoken(stok.buf)) {
		stok.type = SYMBOL;
		break;
	    }
	    stok.type = OTHER;
	}
    }
}

septoken
separater(char buf[], char sep)
{
    int             i,
                    j;
    char            c;
    septoken        res;

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

void
insertstr(char ch, char buf[])
{
    int             i;

    i = laststr(buf) + 1;
    while (i >= 0) {
	buf[i + 1] = buf[i];
	i--;
    }
    buf[0] = ch;
}

int
laststr(char buf[])
{
    int             i;

    i = 0;
    while (buf[i] != NUL)
	i++;
    return (i - 1);
}


// remove #\ from char, for example #\a -> a.
void
dropchar(char buf[])
{
    int             i,
                    j;

    j = laststr(buf);
    for (i = 2; i <= j; i++)
	buf[i - 2] = buf[i];
    buf[i - 2] = NUL;
}


// integer of sign. ignore number of digits.
int
inttoken(char buf[])
{
    int             i;
    char            c;

    if (buf[0] == NUL)		// null string
	return (0);

    if (((buf[0] == '+') || (buf[0] == '-'))) {
	if (buf[1] == NUL)
	    return (0);		// case {+,-} => symbol
	i = 1;
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;		// case {+123..., -123...}
	    else
		return (0);
    } else {
	i = 0;			// {1234...}
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;
	    else
		return (0);
    }
    return (1);
}

// integer without sign
int
inttoken_nsgn(char buf[])
{
    int             i;
    char            c;

    i = 0;
    while ((c = buf[i]) != NUL) {
	if (isdigit(c))
	    i++;
	else
	    return (0);
    }
    return (1);
}

int
flttoken(char buf[])
{
    septoken        tok;

    if (buf[0] == '.') {
	char            bufcp[SYMSIZE];

	if (buf[1] == '0')
	    return (0);
	strncpy(bufcp, buf, SYMSIZE - 1);
	bufcp[SYMSIZE - 1] = '\0';
	insertstr('0', bufcp);
	if (flttoken(bufcp))
	    return (1);
    }


    tok = separater(buf, '.');

    if (tok.sepch == NUL)
	return (0);

    if (tok.after[0] == NUL)	// "".""
	return (0);
    else if (inttoken(tok.before) && inttoken_nsgn(tok.after))
	return (1);
    else
	return (0);
}

int
bignumtoken(char buf[])
{
    int             i;
    char            c;

    if (((buf[0] == '+') || (buf[0] == '-'))) {
	if (buf[1] == NUL)
	    return (0);		// case {+,-} => symbol
	i = 1;
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;		// case {+123..., -123...}
	    else
		return (0);
	if (strlen(buf) <= 10)
	    return (0);		// case not bignum
    } else {
	i = 0;			// {1234...}
	while ((c = buf[i]) != NUL)
	    if (isdigit(c))
		i++;
	    else
		return (0);
	if (strlen(buf) <= 9)
	    return (0);		// case not bignum
    }
    return (1);			// bignum
}


int
symboltoken(char buf[])
{
    int             i;
    char            c;

    i = 0;
    while ((c = buf[i]) != NUL)
	if ((isalpha(c)) || (isdigit(c)) || (issymch(c)))
	    i++;
	else
	    return (0);

    // fold to upper letter.
    i = 0;
    while ((c = buf[i]) != NUL) {
	buf[i] = toupper(c);
	i++;
    }
    return (1);
}

int
bintoken(char buf[])
{
    int             i;
    char            c;

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
	dropchar(buf);
	return (1);
    } else
	return (0);
}

int
octtoken(char buf[])
{
    int             i;
    char            c;

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
	dropchar(buf);
	return (1);
    } else
	return (0);
}

int
dectoken(char buf[])
{
    int             i;
    char            c;

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
	dropchar(buf);
	return (1);
    } else
	return (0);
}

int
hextoken(char buf[])
{
    int             i;
    char            c;

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
	dropchar(buf);
	return (1);
    } else
	return (0);
}


int
expttoken(char buf[])
{
    septoken        tok;
    char            buf1[BUFSIZE];

    if (buf[0] == '.')		// e.g. ".2E3"
	return (0);

    strncpy(buf1, buf, BUFSIZE - 1);
    buf1[BUFSIZE - 1] = '\0';
    tok = separater(buf, 'e');
    if (tok.sepch != NUL &&
	(inttoken(tok.before) || flttoken(tok.before)) &&
	inttoken(tok.after)) {
	if (atoi(tok.after) > 999)
	    return (2);		// overflow
	else if (atoi(tok.after) < -999)
	    return (3);		// underflow
	else
	    return (1);		// regular
    }

    strncpy(buf, buf1, BUFSIZE - 1);
    buf[BUFSIZE - 1] = '\0';
    tok = separater(buf, 'E');
    if (tok.sepch == NUL)
	return (0);
    if ((inttoken(tok.before) || flttoken(tok.before)) &&
	inttoken(tok.after)) {
	if (atoi(tok.after) > 999)
	    return (2);		// overflow
	else if (atoi(tok.after) < -999)
	    return (3);		// underflow
	else
	    return (1);		// regular
    } else
	return (0);
}


int
issymch(char c)
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


int
sread(void)
{
    int             n;
    char           *e;

    gettoken();
    switch (stok.type) {
    case FILEEND:
	return (FEND);
    case INTEGER:
	return (makeint(atoi(stok.buf)));
    case FLOAT_N:
	return (makeflt(atof(stok.buf)));
    case BIGNUM:
	return (makebigx(stok.buf));
    case DECNUM:
	return (makeint((int) strtol(stok.buf, &e, 10)));
    case BINARY:
	return (readbin(stok.buf));
    case OCTAL:
	return (readoct(stok.buf));
    case HEXNUM:
	return (readhex(stok.buf));
    case EXPTNUM:
	return (makeflt(atof(stok.buf)));
    case EXPTOVERF:
	error(FLT_OVERF, "read", NIL);
	break;
    case EXPTUNDERF:
	error(FLT_UNDERF, "read", NIL);
	break;
    case VECTOR:
	return (vector(readlist()));
    case ARRAY:
	n = atoi(stok.buf);
	return (array(n, sread()));
    case STRING:
	return (makestr(stok.buf));
    case CHARACTER:
	return (makechar(stok.buf));
    case SYMBOL:
	return (makesym(stok.buf));
    case QUOTE:
	return (cons(makesym("QUOTE"), cons(sread(), NIL)));
    case BACKQUOTE:
	return (cons(makesym("QUASI-QUOTE"), cons(sread(), NIL)));
    case COMMA:{
	    gettoken();
	    if (stok.type == ATMARK)
		return (cons
			(makesym("UNQUOTE-SPLICING"), cons(sread(), NIL)));
	    else {
		stok.flag = BACK;
		return (cons(makesym("UNQUOTE"), cons(sread(), NIL)));
	    }
	}
    case FUNCTION:
	return (cons(makesym("FUNCTION"), cons(sread(), NIL)));
    case LPAREN:
	return (readlist());
    case RPAREN:
	error(ILLEGAL_RPAREN, "read", NIL);
    default:
	break;
    }
    Fmt_fprint(GET_PORT(error_stream), "%d%s", (int) stok.type, stok.buf);
    error(ILLEGAL_INPUT, "read", NIL);
    return (0);
}

int
readlist(void)
{
    int             rl_car,
                    rl_cdr;

    gettoken();
    if (stok.type == RPAREN)
	return (NIL);
    else if (stok.type == DOT) {
	rl_cdr = sread();
	if (rl_cdr == FEND)
	    error(ILLEGAL_RPAREN, "read", makesym("file end"));
	gettoken();
	return (rl_cdr);
    } else {
	stok.flag = BACK;
	rl_car = sread();
	if (rl_car == FEND)
	    error(ILLEGAL_RPAREN, "read", makesym("file end"));
	rl_cdr = readlist();
	return (cons(rl_car, rl_cdr));
    }
}

int
readbin(char *buf)
{
    char            str[BUFSIZE],
                   *e;
    int             pos,
                    n,
                    res,
                    inc;

    n = strlen(buf);
    if (n <= 31)
	return (makeint((int) strtol(buf, &e, 2)));

    pos = 0;
    res = makeint(0);
    inc = makeint(2);

    while (pos < n) {
	int             part;

	str[0] = buf[pos];
	str[1] = NUL;
	pos++;
	part = makeint((int) strtol(str, &e, 2));
	res = plus(mult(res, inc), part);
    }
    return (res);
}

int
readoct(char *buf)
{
    char            str[BUFSIZE],
                   *e;
    int             pos,
                    n,
                    res,
                    inc;

    n = strlen(buf);
    if (n <= 10)
	return (makeint((int) strtol(buf, &e, 8)));

    pos = 0;
    res = makeint(0);
    inc = makeint(8);

    while (pos < n) {
	int             part;

	str[0] = buf[pos];
	str[1] = NUL;
	pos++;
	part = makeint((int) strtol(str, &e, 8));
	res = plus(mult(res, inc), part);
    }
    return (res);
}


int
readhex(char *buf)
{
    char            str[BUFSIZE],
                   *e;
    int             pos,
                    n,
                    res,
                    inc;

    n = strlen(buf);
    if (n <= 7)
	return (makeint((int) strtol(buf, &e, 16)));

    pos = 0;
    res = makeint(0);
    inc = makeint(16);

    while (pos < n) {
	int             part;

	str[0] = buf[pos];
	str[1] = NUL;
	pos++;
	part = makeint((int) strtol(str, &e, 16));
	res = plus(mult(res, inc), part);
    }
    return (res);
}

// -----print------------------
void
print(int addr)
{
    switch (GET_TAG(addr)) {
    case INTN:
	printint(addr);
	break;
    case FLTN:
	printflt(GET_FLT(addr));
	break;
    case LONGN:
	printlong(addr);
	break;
    case BIGX:
	print_bigx(addr);
	break;
    case VEC:
	printvec(addr);
	break;
    case ARR:
	printarray(addr);
	break;
    case STR:
	printstr(addr);
	break;
    case CHR:
	printchar(addr);
	break;
    case SYM:
	printsym(addr);
	break;
    case SUBR:
	printobj("<subr>");
	break;
    case FSUBR:
	printobj("<fsubr>");
	break;
    case FUNC:
	printobj("<function>");
	break;
    case MACRO:
	printobj("<macro>");
	break;
    case CLASS:
	printclass(addr);
	break;
    case STREAM:
	printstream(addr);
	break;
    case GENERIC:
	printobj("<generic>");
	break;
    case METHOD:
	printobj("<method>");
	break;
    case INSTANCE:
	printobj("<instance>");
	break;
    case LIS:
	output_char(output_stream, '(');
	printlist(addr);
	break;
    case DUMMY:
	printobj("<undef*>");
	break;
    default:
	printobj("<undef>");
	break;
    }
}

void
printint(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR)
	Fmt_fprint(GET_PORT(output_stream), "%d", GET_INT(addr));
    else {
	char            str[SHORT_STRSIZE];
	Fmt_sfmt(str, SHORT_STRSIZE, "%d", GET_INT(addr));
	append_str(output_stream, str);
    }
}

void
printflt(double x)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	fprintf(GET_PORT(output_stream), "%g", x);
	if ((x - (int) x) == 0.0)
	    fprintf(GET_PORT(output_stream), ".0");
    } else {
	char            str[SHORT_STRSIZE];
	snprintf(str, SHORT_STRSIZE, "%g", x);
	append_str(output_stream, str);
	if ((x - (int) x) == 0.0)
	    append_str(output_stream, ".0");
    }
}


void
printlong(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	Fmt_fprint(GET_PORT(output_stream), "%D", GET_LONG(addr));
    } else {
	char            str[SHORT_STRSIZE];
	Fmt_sfmt(str, SHORT_STRSIZE, "%D", GET_LONG(addr));
	append_str(output_stream, str);
    }
}


void
printlist(int addr)
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
	printlist(GET_CDR(addr));
    }
}

void
printvec(int x)
{
    int             len,
                    i;

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

void
printarray(int x)
{
    int             i,
                    size,
                    st,
                    ls,
                    dim;

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
	char            str[SHORT_STRSIZE];
	Fmt_sfmt(str, SHORT_STRSIZE, "#%da", dim);
	append_str(output_stream, str);
    }
    if (dim == 0)
	print(car(ls));
    else
	print(structured(ls, st));
}


void
printstr(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR) {
	Fmt_fprint(GET_PORT(output_stream), "\"%s\"", GET_NAME(addr));
    } else {
	Fmt_sfmt(stream_str, STRSIZE, "\"%s\"", GET_NAME(addr));
	append_str(output_stream, stream_str);
    }
}

void
printchar(int addr)
{
    output_str(output_stream, "#\\");
    switch (GET_CHAR(addr)) {
    case SPACE:
	output_str(output_stream, "space");
	break;
    case EOL:
	output_str(output_stream, "newline");
	break;
    default:
	output_str(output_stream, GET_NAME(addr));
    }
}

void
printsym(int addr)
{
    output_str(output_stream, GET_NAME(addr));
}

void
printobj(const char *str)
{
    output_str(output_stream, str);
}

void
printclass(int addr)
{
    if (GET_OPT(output_stream) != EISL_OUTSTR)
	Fmt_fprint(GET_PORT(output_stream), "<class %s>", GET_NAME(addr));
    else {
	Fmt_sfmt(stream_str, STRSIZE, "<class %s>", GET_NAME(addr));
	append_str(output_stream, stream_str);
    }
}

void
printstream(int addr)
{
    const char     *name;

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

static void
clean_stdin(void)
{
    int             c;
    do {
	c = getchar();
    } while (c != '\n' && c != EOF);
}

// --------eval---------------
int
eval(int addr)
{
    int             val,
                    res,
                    temp;
    char            c;

    (void) checkgbc();

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
	res = findenv(addr);
	if (res != FAILSE)
	    return (res);
	else {
	    if (GET_OPT(addr) == GLOBAL)
		return (GET_CDR(addr));
	    else if (GET_OPT(addr) == CONSTN)
		return (GET_CDR(addr));
	    else
		error(UNDEF_VAR, "eval", addr);

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
		debugger();
	}

	if ((symbolp(car(addr))) && (HAS_NAME(car(addr), "QUOTE"))) {
	    if (improperlistp(cdr(addr)))
		error(ILLEGAL_ARGS, "quote", cdr(addr));
	    else if (length(cdr(addr)) != 1)
		error(ILLEGAL_ARGS, "quote", cdr(addr));
	    else
		return (cadr(addr));
	} else if ((symbolp(car(addr)))
		   && (HAS_NAME(car(addr), "QUASI-QUOTE"))) {
	    temp = quasi_transfer(cadr(addr), 0);
	    shelterpush(temp);
	    res = eval(temp);
	    shelterpop();
	    return (res);
	} else if (subrp(car(addr)))
	    return (apply(caar(addr), evlis(cdr(addr))));
	else if (fsubrp(car(addr)))
	    return (apply(caar(addr), cdr(addr)));
	else if ((val = functionp(car(addr)))) {
	    temp = evlis(cdr(addr));
	    examin_sym = car(addr);
	    return (apply(val, temp));
	} else if (macrop(car(addr))) {
	    examin_sym = car(addr);
	    return (apply(caar(addr), cdr(addr)));
	} else if (genericp(car(addr))) {
	    examin_sym = car(addr);
	    return (apply(caar(addr), evlis(cdr(addr))));
	} else if (listp(car(addr)))
	    return (apply(eval(car(addr)), evlis(cdr(addr))));
	else
	    error(UNDEF_FUN, "eval", car(addr));

    }
    error(UNDEF_FUN, "eval", addr);
    return (0);
}

DEF_GETTER(char, TR, trace, NIL)
     int             apply(int func, int args)
{
    int             varlist,
                    body,
                    res,
                    pexist,
                    aexist,
                    i,
                    n,
                    trace;
    REQUIRE((GET_TAG(func) == FSUBR || GET_TAG(func) == SUBR
	     || GET_TAG(func) == FUNC || GET_TAG(func) == MACRO
	     || GET_TAG(func) == GENERIC) && (GET_TAG(args) == LIS
					      || GET_TAG(args) == SYM));
    res = NIL;
    pexist = 0;
    aexist = 0;
    trace = 0;

    switch (GET_TAG(func)) {
    case SUBR:
	return ((GET_SUBR(func)) (args));
    case FSUBR:
	return ((GET_SUBR(func)) (args));
    case FUNC:
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
	shelterpush(func);
	shelterpush(args);
	push(ep);
	ep = GET_CDR(func);
	varlist = car(GET_CAR(func));
	if (GET_OPT(func) >= 0) {
	    if (length(args) != (int) GET_OPT(func))
		error(WRONG_ARGS, GET_NAME(func), args);
	} else {
	    if (length(args) < (-1 * (int) GET_OPT(func) - 2))
		error(WRONG_ARGS, GET_NAME(func), args);
	}
	body = cdr(GET_CAR(func));
	bindarg(varlist, args);
	while (!(IS_NIL(body))) {
	    res = eval(car(body));
	    body = cdr(body);
	}
	unbind();
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
	shelterpop();
	shelterpop();
	ep = pop();
	return (res);
    case MACRO:{
	    int             macrofunc;

	    if (improperlistp(args))
		error(IMPROPER_ARGS, "apply", args);
	    macrofunc = GET_CAR(func);
	    varlist = car(GET_CAR(macrofunc));
	    if (GET_OPT(func) >= 0) {
		if (length(args) != (int) GET_OPT(func))
		    error(WRONG_ARGS, GET_NAME(func), args);
	    } else {
		if (length(args) < (-1 * (int) GET_OPT(func) - 2))
		    error(WRONG_ARGS, GET_NAME(func), args);
	    }
	    body = cdr(GET_CAR(macrofunc));
	    bindarg(varlist, args);
	    while (!(IS_NIL(body))) {
		shelterpush(body);
		res = eval(car(body));
		shelterpop();
		body = cdr(body);
	    }
	    unbind();
	    shelterpush(res);
	    res = eval(res);
	    shelterpop();
	    return (res);
	}

    case GENERIC:{
	    int             method;

	    if (GET_OPT(func) >= 0) {
		if (length(args) != (int) GET_OPT(func))
		    error(WRONG_ARGS, GET_NAME(func), args);
	    } else {
		if (length(args) < (-1 * (int) GET_OPT(func) - 2))
		    error(WRONG_ARGS, GET_NAME(func), args);
	    }
	    generic_func = func;
	    generic_vars = args;
	    method = GET_CDR(func);
	    while (!nullp(method)) {
		varlist = car(GET_CAR(car(method)));
		next_method = method;
		if (matchp(varlist, args)) {
		    if (GET_OPT(car(method)) == PRIORITY)
			pexist = 1;
		    if (GET_OPT(car(method)) == AROUND)
			aexist = 1;
		    varlist = genlamlis_to_lamlis(varlist);
		    body = cdr(GET_CAR(car(method)));
		    bindarg(varlist, args);
		    while (!nullp(body)) {
			res = eval(car(body));
			body = cdr(body);
		    }
		    unbind();
		}
		if (GET_OPT(car(next_method)) == AROUND) {
		    if (aexist == 1)
			break;
		    else
			method = cdr(method);
		} else if (GET_OPT(car(method)) == PRIORITY && pexist == 1) {
		    method = next_method;
		    while (GET_OPT(car(method)) == PRIORITY) {
			method = cdr(method);
		    }
		} else
		    method = cdr(next_method);

	    }
	    if (aexist == 0 && pexist == 0)
		error(NOT_EXIST_METHOD, "apply", args);

	    generic_func = NIL;
	    generic_vars = NIL;
	    return (res);
	}
    default:
	error(NOT_FUNC, "apply", list2(func, args));
    }
    return (0);
}

void
bindarg(int varlist, int arglist)
{
    int             arg1,
                    arg2;

    push(ep);
    while (!(IS_NIL(varlist))) {
	if (cddr(varlist) == NIL && (car(varlist) == makesym(":REST")
				     || car(varlist) == makesym("&REST"))) {
	    arg1 = cadr(varlist);
	    arg2 = arglist;
	    addlexenv(arg1, arg2);
	    return;
	} else {
	    arg1 = car(varlist);
	    arg2 = car(arglist);
	    addlexenv(arg1, arg2);
	    varlist = cdr(varlist);
	    arglist = cdr(arglist);
	}
    }
}

void
unbind(void)
{
    ep = pop();
}


int
evlis(int addr)
{
    argpush(addr);
    top_flag = false;
    if (IS_NIL(addr)) {
	argpop();
	return (addr);
    } else {
	int             car_addr,
	                cdr_addr;

	car_addr = eval(car(addr));
	argpush(car_addr);
	cdr_addr = evlis(cdr(addr));
	car_addr = argpop();
	(void) argpop();
	return (cons(car_addr, cdr_addr));
    }
}

/*
 * check class matching of argument of lambda and received argument. 
 */
int
matchp(int varlist, int arglist)
{

    if (nullp(varlist) && nullp(arglist))
	return (1);
    else if (symbolp(car(varlist)))
	return (matchp(cdr(varlist), cdr(arglist)));
    else if (eqp(makesym(":rest"), car(varlist)))
	return (1);
    else if (eqp(makesym("&rest"), car(varlist)))
	return (1);
    else if (GET_AUX(cadar(varlist)) == GET_AUX(car(arglist)))	// match
	// class
	return (matchp(cdr(varlist), cdr(arglist)));
    else if (subclassp(GET_AUX(car(arglist)), GET_AUX(cadar(varlist))))	// subclass
	return (matchp(cdr(varlist), cdr(arglist)));
    else
	return (0);
}

/*
 * change lambda list of function to normal argument. ex ((x <number>)(y
 * <list>)) -> (x y) 
 */
int
genlamlis_to_lamlis(int varlist)
{
    int             res;

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


// for stack to store ep(environment)
int
push(int pt)
{
    if (sp >= STACKSIZE)
	error(STACK_OVERF, "push", NIL);
    stack[sp++] = pt;

    return (T);
}

int
pop(void)
{
    if (sp <= 0)
	error(STACK_UNDERF, "pop", NIL);
    return (stack[--sp]);
}

// push/pop of arglist
int
argpush(int addr)
{
    argstk[ap++] = addr;

    return (T);
}

int
argpop(void)
{
    return (argstk[--ap]);
}

// shelter push/pop
int
shelterpush(int addr)
{
    if (lp >= STACKSIZE)
	error(SHELTER_OVERF, "shelterpush", NIL);
    shelter[lp++] = addr;

    return (T);
}

int
shelterpop(void)
{
    if (lp <= 0)
	error(SHELTER_UNDERF, "shelterpop", NIL);
    return (shelter[--lp]);
}

// --------system function
// regist subr to environment.
void
defsubr(const char *symname, int (*func)(int))
{
    bindfunc(symname, SUBR, func);
}

// regist fsubr(not eval argument)
void
deffsubr(const char *symname, int (*func)(int))
{
    bindfunc(symname, FSUBR, func);
}


static inline void
SET_SUBR(int addr, subr_t x)
{
    REQUIRE(CELLRANGE(addr) &&
	    (GET_TAG(addr) == SUBR || GET_TAG(addr) == FSUBR));
    heap[addr].val.car.subr = x;
}

void
bindfunc(const char *name, tag tag, int (*func)(int))
{
    int             sym,
                    val;

    sym = makesym(name);
    val = freshcell();
    SET_TAG(val, tag);
    SET_SUBR(val, func);
    SET_CDR(val, 0);
    SET_AUX(val, cfunction);	// class function
    SET_CAR(sym, val);
}

void
bindmacro(char *name, int addr)
{
    int             sym,
                    val1,
                    val2;

    sym = makesym(name);
    val1 = freshcell();
    SET_TAG(val1, FUNC);
    SET_CAR(val1, addr);
    SET_CDR(val1, 0);
    val2 = freshcell();
    SET_TAG(val2, MACRO);
    TRY             heap[val2].name = Str_dup(name, 1, 0, 1);
    EXCEPT(Mem_Failed)
	error(MALLOC_OVERF, "makemacro", NIL);
    END_TRY;
    SET_CAR(val2, val1);
    SET_CDR(val2, 0);
    SET_AUX(val2, cfunction);	// class
    SET_OPT(val2, (signed char) count_args(car(addr)));	// count of args
    SET_CAR(sym, val2);
}

void
bindconst(const char *name, int obj)
{
    int             sym;

    sym = makesym(name);
    SET_CDR(sym, obj);
    SET_OPT(sym, CONSTN);
}

// --------qusi quote---------------
int
quasi_transfer(int x, int n)
{
    // printf("%d",n); print(x);putchar('\n');

    if (nullp(x))
	return (NIL);
    else if (atomp(x))
	return (list2(makesym("QUOTE"), x));
    else if (listp(x) && eqp(car(x), makesym("UNQUOTE")) && n == 0)
	return (cadr(x));
    else if (listp(x) && eqp(car(x), makesym("UNQUOTE-SPLICING"))
	     && n == 0)
	return (cadr(x));
    else if (listp(x) && eqp(car(x), makesym("QUASI-QUOTE")))
	return (list3(makesym("LIST"),
		      list2(makesym("QUOTE"), makesym("QUASI-QUOTE")),
		      quasi_transfer(cadr(x), n + 1)));
    else if (listp(x) && eqp(caar(x), makesym("UNQUOTE")) && n == 0)
	return (list3
		(makesym("CONS"), cadar(x), quasi_transfer(cdr(x), n)));
    else if (listp(x) && eqp(caar(x), makesym("UNQUOTE-SPLICING"))
	     && n == 0)
	return (list3
		(makesym("APPEND"), cadar(x), quasi_transfer(cdr(x), n)));
    else if (listp(x) && eqp(caar(x), makesym("UNQUOTE")))
	return (list3(makesym("CONS"),
		      list3(makesym("LIST"),
			    list2(makesym("QUOTE"), makesym("UNQUOTE")),
			    quasi_transfer(cadar(x), n - 1)),
		      quasi_transfer(cdr(x), n)));
    else if (listp(x) && eqp(caar(x), makesym("UNQUOTE-SPLICING")))
	return (list3(makesym("CONSc"),
		      list3(makesym("LIST"),
			    list2(makesym("QUOTE"),
				  makesym("UNQUOTE-SPLICING")),
			    quasi_transfer(cadar(x), n - 1)),
		      quasi_transfer(cdr(x), n)));
    else
	return (list3
		(makesym("CONS"), quasi_transfer(car(x), n),
		 quasi_transfer(cdr(x), n)));
}

// --------debug---------------
void
debugger()
{
    int             i;

    puts("debug mode ?(help)");
    while (1) {
	fputs(">>", stdout);
	int             x = sread();
	if (eqp(x, makesym("?"))) {
	    puts("?  help\n"
		 ":a abort\n"
		 ":b backtrace\n"
		 ":d dynamic environment\n"
		 ":e environment\n"
		 ":i identify examining symbol\n"
		 ":q quit\n"
		 ":r room\n" ":s stepper ON/OFF\n" "other S exps eval");
	} else if (eqp(x, makesym(":A"))) {
	    RAISE(Restart_Repl);
	} else if (eqp(x, makesym(":B"))) {
	    for (i = 0; i < BACKSIZE; i++) {
		print(backtrace[i]);
		putchar('\n');
	    }
	} else if (eqp(x, makesym(":D"))) {
#ifdef DYN
	    for (i = 1; i <= dp; i++) {
		print(dynamic[i][1]);
		fputs(" = ", stdout);
		print(dynamic[1][1]);
		putchar('\n');
	    }
#else
	    print(dp);
	    putchar('\n');
#endif
	} else if (eqp(x, makesym(":E"))) {
	    print(ep);
	    putchar('\n');
	} else if (eqp(x, makesym(":I"))) {
	    print(examin_sym);
	    putchar('\n');
	} else if (eqp(x, makesym(":Q"))) {
	    return;
	} else if (eqp(x, makesym(":R"))) {
	    Fmt_print("EP = %d (environment pointer)\n"
		      "DP = %d (dynamic pointer)\n"
		      "HP = %d (heap pointer)\n"
		      "SP = %d (stack pointer)\n"
		      "FC = %d (free counter)\n"
		      "AP = %d (arglist pointer)\n"
		      "LP = %d (shelter pointer)\n"
		      "GC = %d (GC switch 0=m&sGC 1=copyGC)\n"
		      "WP = %d (work area pointer)\n"
		      "SW = %d (current work area 1or2)\n",
		      ep, dp, hp, sp, fc, ap, lp, gc_sw, wp, area_sw);
	} else if (eqp(x, makesym(":S"))) {
	    if (stepper_flag == 0) {
		puts("stepper ON. enter 'q' to quit stepper");
		stepper_flag = 1;
	    } else {
		puts("stepper OFF");
		stepper_flag = 0;
	    }
	} else {
	    print(eval(x));
	    putchar('\n');
	}
    }
}
