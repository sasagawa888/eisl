#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <ctype.h>
#include <ncurses.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include "compat/cdefs.h"
#include "edlis.h"


#ifndef CTRL
#define CTRL(X) ((X) & 0x1F)
#endif

#define NUM_STR_MAX 5
#define SHORT_STR_MAX 30

volatile sig_atomic_t ctrl_c = 0;
volatile sig_atomic_t ctrl_z = 0;

FILE *port;
char fname[256];		// file name 
bool cancel_flag;		// for CTRL+G 

// -----editor-----
int ed_scroll;
int ed_footer;
int ed_middle;
int ed_row;
int ed_col;			//position of buffer
int ed_col1;			//position of terminal when include unicode ed_col1 is different from ed_col
int ed_start;
int ed_end;
bool ed_ins = true;
int ed_tab = 0;
int ed_indent = 1;
char ed_data[ROW_SIZE][COL_SIZE];
char ed_copy[COPY_SIZE][COL_SIZE];
int ed_lparen_row;
int ed_lparen_col;
int ed_rparen_row;
int ed_rparen_col;
int ed_clip_start;
int ed_clip_end;
int ed_copy_end;
const char *ed_candidate[COMPLETION_CANDIDATES_MAX];
int ed_candidate_pt;
const enum Color ed_syntax_color = RED_ON_DFL;
const enum Color ed_builtin_color = CYAN_ON_DFL;
const enum Color ed_extended_color = MAGENTA_ON_DFL;
const enum Color ed_string_color = YELLOW_ON_DFL;
const enum Color ed_comment_color = BLUE_ON_DFL;
int ed_incomment = -1;		// #|...|# comment
bool modify_flag;

/*  buffer data structure   text is "abc" at first row
 *  0,1,2,3,4,5...255 
 * [a,b,c,EOL,0,0,0,....,0]
*/

int main(int argc, char *argv[])
{
    int i, j;

    /* to enable CTRL('S') */
    if (system("stty -ixon") == -1) {
	printf("terminal error\n");
	return (0);
    }

    setlocale(LC_ALL, "");
    if (argc == 2)
	strcpy(fname, argv[1]);

    signal(SIGINT, signal_handler_c);
    signal(SIGSTOP, signal_handler_z);
    signal(SIGTSTP, signal_handler_z);
    for (i = 0; i < ROW_SIZE; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = 0;
	}
    }

    load_data(fname);
    init_ncurses();
    ed_scroll = LINES - 3;
    ed_footer = LINES;
    ed_middle = LINES / 2;
    ESCCLS();
    display_header();
    display_screen();
    ed_row = ed_col = ed_col1 = 0;
    edit_screen();
    CHECK(endwin);
    /* restore CTRL('S') */
    if (system("stty ixon") == -1) {
	printf("terminal error\n");
    }
}

int getch1(void)
{
    int c;

  retry:
    timeout(0);
    c = getch();
    timeout(-1);
    if (ctrl_c == 1) {
	ctrl_c = 0;
	return (CTRL('C'));
    } else if (ctrl_z == 1) {
	ctrl_z = 0;
	return (CTRL('Z'));
    }

    if (c == ERR) {
	goto retry;
    }
    return (c);
}

__dead void errw(const char *msg)
{
    endwin();
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void clear_status()
{
    int i;
    ESCREV();
    ESCMOVE(ed_footer, 1);
    for (i = 0; i < COLS - 9; i++)
	CHECK(addstr, " ");
    ESCMOVE(ed_footer, 1);
}

void restore_cursol()
{
    if (ed_col1 < COLS - LEFT_MARGIN)
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
    else
	ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		ed_col1 - (COLS - LEFT_MARGIN) + LEFT_MARGIN);
}

void init_ncurses()
{
    if (initscr() == NULL) {
	fputs("initscr\n", stderr);
	exit(EXIT_FAILURE);
    }
    if (has_colors()) {
	CHECK(start_color);
#ifdef NCURSES_VERSION
	CHECK(use_default_colors);
#endif
    }
    CHECK(scrollok, stdscr, TRUE);
    CHECK(idlok, stdscr, TRUE);
    CHECK(noecho);
    CHECK(keypad, stdscr, TRUE);
    CHECK(cbreak);
    CHECK(nonl);
    CHECK(intrflush, NULL, FALSE);
    curs_set(1);
#ifdef NCURSES_VERSION
    set_tabsize(8);
#endif

    if (has_colors()) {
	// Colors
	CHECK(init_pair, RED_ON_DFL, COLOR_RED, -1);
	CHECK(init_pair, YELLOW_ON_DFL, COLOR_YELLOW, -1);
	CHECK(init_pair, BLUE_ON_DFL, COLOR_BLUE, -1);
	CHECK(init_pair, MAGENTA_ON_DFL, COLOR_MAGENTA, -1);
	CHECK(init_pair, CYAN_ON_DFL, COLOR_CYAN, -1);
	CHECK(init_pair, DFL_ON_CYAN, -1, COLOR_CYAN);
    }
}

void signal_handler_c(int signo __unused)
{
    ctrl_c = 1;
}

void signal_handler_z(int signo __unused)
{
    ctrl_z = 1;
}


// transform from UTF-8 to unicode
int utf8_to_ucs4(int row, int col)
{
    int x, x1, x2, x3, res;
    unsigned char uc;

    uc = (unsigned char) ed_data[row][col];
    if (uc <= 0x7f) {
	x = (int) uc;
	return (x);
    } else if (uc >= 0xc0 && uc <= 0xdf) {
	x = (int) (UTF2MSK1 & uc);
	x = x << 6;
	uc = (unsigned char) ed_data[row][col + 1];
	x1 = (int) (UTFOMSKO & uc);
	res = x | x1;
	return (res);
    } else if (uc >= 0xe0 && uc <= 0xef) {
	x = (int) (UTF3MSK1 & uc);
	x = x << 12;
	uc = (unsigned char) ed_data[row][col + 1];
	x1 = (int) (UTFOMSKO & uc);
	x1 = x1 << 6;
	uc = (unsigned char) ed_data[row][col + 2];
	x2 = (int) (UTFOMSKO & uc);
	res = x | x1 | x2;
	return (res);
    } else if (uc >= 0xf0 && uc <= 0xf7) {
	x = (int) (UTF4MSK1 & uc);
	x = x << 18;
	uc = (unsigned char) ed_data[row][col + 1];
	x1 = (int) (UTFOMSKO & uc);
	x1 = x1 << 12;
	uc = (unsigned char) ed_data[row][col + 2];
	x2 = (int) (UTFOMSKO & uc);
	x2 = x2 << 6;
	uc = (unsigned char) ed_data[row][col + 3];
	x3 = (int) (UTFOMSKO & uc);
	res = x | x1 | x2 | x3;
	return (res);
    } else
	return (-1);
}


bool is_word_char(char x)
{
    if (isalpha(x))
	return true;
    else if (isUni2(x))
	return true;
    else if (isUni3(x))
	return true;
    else if (isUni4(x))
	return true;

    return false;
}


// calculate buffer position to increase according to UTF8 unicode
int increase_buffer(int row, int col)
{
    int uc;

    uc = ed_data[row][col];
    if (isUni1(uc))
	return (1);
    else if (isUni2(uc))
	return (2);
    else if (isUni3(uc))
	return (3);
    else if (isUni4(uc))
	return (4);
    else
	return (-1);
}

// calculate terminal position to increase according to UTF8 unicode
int increase_terminal(int row, int col)
{
    int unicode;

    if (isUni3(ed_data[row][col])) {
	unicode = utf8_to_ucs4(row, col);
	// tai
	if (unicode >= 0x0e00 && unicode <= 0x0e7f) {
	    if ((unicode >= 0x0E31 && unicode <= 0x0E3A)
		|| (unicode >= 0x0E47 && unicode <= 0x0E4E))
		return (0);
	    else
		return (1);
	}
	// arabian
	else if (unicode >= 0x0600 && unicode <= 0x06ff)
	    return (1);
	// tamil
	else if (unicode >= 0xb80 && unicode <= 0xbff)
	    return (1);
	else
	    return (2);
    } else
	return (1);
}

// calculate buffer position to decrease according to UTF8 unicode
int decrease_buffer(int row, int col)
{

    if (isUni1(ed_data[row][col]))
	return (1);
    else if (isUni2(ed_data[row][col - 1]))
	return (2);
    else if (isUni3(ed_data[row][col - 2]))
	return (3);
    else if (isUni4(ed_data[row][col - 3]))
	return (4);
    else
	return (1);
}

// calculate terminal position to decrease according to UTF8 unicode
int decrease_terminal(int row, int col)
{
    int unicode;

    if (isUni3(ed_data[row][col - 2])) {
	unicode = utf8_to_ucs4(row, col - 2);
	//tai
	if (unicode >= 0x0e00 && unicode <= 0x0e7f) {
	    if ((unicode >= 0x0E31 && unicode <= 0x0E3A)
		|| (unicode >= 0x0E47 && unicode <= 0x0E4E))
		return (0);
	    else
		return (1);
	}
	// arabian
	else if (unicode >= 0x0600 && unicode <= 0x06ff)
	    return (1);
	// tamil
	else if (unicode >= 0xb80 && unicode <= 0xbff)
	    return (1);
	else
	    return (2);
    } else
	return (1);
}

// re calculate buffer position and terminal position at row
void recalculate_col(int row, int oldcol1)
{
    int new_col, new_col1;

    new_col = 0;
    new_col1 = 0;
    while (new_col < COL_SIZE) {
	if (new_col1 == oldcol1) {
	    break;
	} else if (ed_data[row][new_col] == EOL) {
	    break;
	} else if (ed_data[row][new_col] == 0) {
	    break;
	}
	new_col1 = new_col1 + increase_terminal(row, new_col);
	new_col = new_col + increase_buffer(row, new_col);
    }
    ed_col = new_col;
    ed_col1 = new_col1;
}


//---------------cursol control------------------------------

void right()
{
    int turn, new_col, new_col1;
    turn = COLS - LEFT_MARGIN;
    if (ed_col == find_eol(ed_row) || ed_col >= COL_SIZE)
	return;

    new_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
    new_col = ed_col + increase_buffer(ed_row, ed_col);

    if (ed_col1 < turn && new_col1 >= turn) {
	restore_paren();
	ed_col = new_col;
	ed_col1 = new_col1;
	display_screen();
	emphasis_lparen();
	emphasis_rparen();
    } else {
	restore_paren();
	ed_col = new_col;
	ed_col1 = new_col1;
	emphasis_lparen();
	emphasis_rparen();
    }
    restore_cursol();
}



void left()
{
    int turn, new_col, new_col1;
    turn = COLS - LEFT_MARGIN;
    if (ed_col1 == 0)
	return;

    new_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
    new_col = ed_col - decrease_buffer(ed_row, ed_col - 1);

    if (ed_col1 >= turn && new_col1 < turn) {
	ed_col = new_col;
	ed_col1 = new_col1;
	display_screen();
    } else {
	ed_col = new_col;
	ed_col1 = new_col1;
    }
    restore_paren();
    emphasis_lparen();
    emphasis_rparen();
    restore_cursol();
}

void up()
{
    int turn, oldcol1;
    turn = COLS - LEFT_MARGIN;

    if (ed_row == 0)
	return;
    else if (ed_clip_start != -1 && ed_row == ed_start) {
	if (ed_row == ed_clip_start)
	    ed_clip_start--;
	else
	    ed_clip_end--;
	ed_row--;
	ed_start--;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    } else if (ed_row == ed_start) {
	ed_row = ed_row - ed_middle;
	ed_start = ed_start - ed_middle;
	if (ed_row < 0)
	    ed_row = ed_start = 0;
	recalculate_col(ed_row, ed_col1);
	display_screen();
	restore_paren();
	emphasis_lparen();
	emphasis_rparen();
	ESCMOVE(2, ed_col1 + LEFT_MARGIN);
    } else if (ed_clip_start != -1) {
	if (ed_row == ed_clip_start)
	    ed_clip_start--;
	else
	    ed_clip_end--;
	ed_row--;
	recalculate_col(ed_row, ed_col1);
	display_screen();
	restore_paren();
	emphasis_lparen();
	emphasis_rparen();
	restore_cursol();
    } else {
	restore_paren();
	ed_row--;
	oldcol1 = ed_col1;
	recalculate_col(ed_row, ed_col1);
	if ((ed_col1 >= turn && oldcol1 < turn) ||
	    (ed_col1 < turn && oldcol1 >= turn)) {
	    display_screen();
	}
	emphasis_lparen();
	emphasis_rparen();
	restore_cursol();
    }
}

void down()
{
    int turn, oldcol1;
    turn = COLS - LEFT_MARGIN;

    if (ed_row == ed_end)
	return;
    else if (ed_clip_start != -1 && ed_row == ed_start + ed_scroll) {
	if (ed_row == ed_clip_end)
	    ed_clip_end++;
	else
	    ed_clip_start++;
	ed_row++;
	ed_start++;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    } else if (ed_row == ed_start + ed_scroll) {
	ed_row = ed_row + ed_middle;
	ed_start = ed_start + ed_middle;
	if (ed_row > ed_end)
	    ed_row = ed_start = ed_end - ed_scroll;
	display_screen();
	restore_paren();
	emphasis_lparen();
	emphasis_rparen();
	recalculate_col(ed_row, ed_col1);
	ESCMOVE(ed_footer - 1, ed_col1 + LEFT_MARGIN);
    } else if (ed_clip_start != -1) {
	if (ed_row == ed_clip_end)
	    ed_clip_end++;
	else
	    ed_clip_start++;
	ed_row++;
	recalculate_col(ed_row, ed_col1);
	display_screen();
	restore_paren();
	emphasis_lparen();
	emphasis_rparen();
	recalculate_col(ed_row, ed_col1);
	restore_cursol();
    } else {
	restore_paren();
	ed_row++;
	oldcol1 = ed_col1;
	recalculate_col(ed_row, ed_col1);
	if ((ed_col1 >= turn && oldcol1 < turn) ||
	    (ed_col1 < turn && oldcol1 >= turn)) {
	    display_screen();
	}
	emphasis_lparen();
	emphasis_rparen();
	restore_cursol();
    }
}

void return_key()
{
    int i;

    if (ed_row == ed_start + ed_scroll) {
	restore_paren();
	insert_row();
	ed_start++;
	ed_row++;
	ed_end++;
	ed_col = ed_col1 = 0;
	display_screen();
	ESCMOVE(ed_footer, LEFT_MARGIN);
    } else if (ed_col >= COLS) {
	restore_paren();
	insert_row();
	ed_start++;
	ed_row++;
	ed_end++;
	ed_col = ed_col1 = 0;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    } else {
	restore_paren();
	insert_row();
	ed_row++;
	ed_end++;
	ed_col = ed_col1 = 0;
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
    }
    if (ed_indent) {
	ed_col = ed_col1 = 0;
	remove_headspace(ed_row);
	i = calc_tabs();
	softtabs(i);
	display_screen();
	restore_cursol();
    }
    modify_flag = true;
}


void tab_key()
{
    int i;

    if (ed_tab == 0) {
	ed_col = ed_col1 = 0;
	i = calc_tabs();
	remove_headspace(ed_row);
	softtabs(i);
    } else {
	softtabs(ed_tab);
    }
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void backspace_key(void)
{

    if (ed_row == 0 && ed_col == 0)
	return;
    else if (ed_col == 0) {
	restore_paren();
	delete_row();
	if (ed_row < ed_start) {
	    ed_start = ed_row;
	}
	display_screen();
    } else {
	backspace();
	ESCCLSLA();
	restore_paren();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
    }
    restore_cursol();
    modify_flag = true;
}

void del(void)
{

    if (ed_data[ed_row][ed_col] == EOL)
	return;
    delete_char();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void line_begin()
{
    int turn;
    turn = COLS - LEFT_MARGIN;

    if (ed_col1 < turn) {
	ed_col = ed_col1 = 0;
    } else {
	ed_col = ed_col1 = 0;
	ESCCLSLA();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
    }
    restore_cursol();
}

void line_end()
{
    int turn, i;
    turn = COLS - LEFT_MARGIN;

    for (i = 0; i < COL_SIZE; i++) {
	if (ed_data[ed_row][i] == NUL)
	    break;
    }

    if (ed_col1 < turn && i < turn) {
	ed_col = ed_col1 = i - 1;
    } else {
	ed_col = ed_col1 = i - 1;
	ESCCLSLA();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
    }
    restore_cursol();
}


void sexp_next()
{
    int old_row, old_col, old_col1;
    struct position pos;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;


    /* skip space comment */
    while (1) {
	if (ed_data[ed_row][ed_col] == ' ') {
	    ed_col1++;
	    ed_col++;
	} else if (ed_data[ed_row][ed_col] == ')') {
	    ed_col1++;
	    ed_col++;
	} else if (ed_data[ed_row][ed_col] == ';') {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    goto skip;
	} else {
	    break;
	}
    }

    if (ed_data[ed_row][ed_col] == '(') {	/* list */
	pos = find_rparen(1);
	if (pos.row != -1) {
	    ed_row = pos.row;
	    ed_col = ed_col1 = pos.col + 1;
	}
    } else {			/* atom */
	while (ed_data[ed_row][ed_col] != ' ' &&
	       ed_data[ed_row][ed_col] != '(' &&
	       ed_data[ed_row][ed_col] != ')'
	       && ed_data[ed_row][ed_col] != EOL) {
	    ed_col++;
	    ed_col1++;
	}
    }

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void word_next()
{
    int old_row, old_col, old_col1;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;
    // skip word char 
    if (is_word_char(ed_data[ed_row][ed_col])) {
	while (is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
	    ed_col = ed_col + increase_buffer(ed_row, ed_col);
	}
    }
    // skip space 
    while (1) {
	if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    goto skip;
	} else if (!is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1++;
	    ed_col++;
	} else {
	    break;
	}
    }

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void list_next()
{
    int old_row, old_col, old_col1;
    struct position pos;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;
    /* skip space comment */
    while (1) {
	if (ed_data[ed_row][ed_col] == '(') {
	    break;
	} else if (ed_data[ed_row][ed_col] == ';') {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    goto skip;
	} else {
	    ed_col++;
	    ed_col1++;
	}
    }

    pos = find_rparen(1);
    if (pos.row != -1) {
	ed_row = pos.row;
	ed_col = ed_col1 = pos.col + 1;
    }

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}

void list_down()
{
    int old_row, old_col, old_col1;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;

    /* skip space comment */
    while (1) {
	if (ed_data[ed_row][ed_col] == '(') {
	    break;
	} else if (ed_data[ed_row][ed_col] == ')') {
	    ESCREV();
	    ESCMOVE(ed_footer, 1);
	    clear_status();
	    ESCMOVE(ed_footer, 1);
	    CHECK(addstr, "Can't find");
	    ESCRST();
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    return;
	} else if (ed_data[ed_row][ed_col] == ';') {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == EOL) {
	    ed_col = ed_col1 = 0;
	    ed_row++;
	} else if (ed_data[ed_row][ed_col] == 0) {
	    goto skip;
	} else {
	    ed_col++;
	    ed_col1++;
	}
    }

    ed_col++;
    ed_col1++;

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void sexp_prev()
{
    struct position pos;

    /* skip atom */
    if (ed_data[ed_row][ed_col] != ' ' &&
	ed_data[ed_row][ed_col] != '(' && ed_data[ed_row][ed_col] != ')') {
	while (ed_data[ed_row][ed_col] != ' ' &&
	       ed_data[ed_row][ed_col] != '(' &&
	       ed_data[ed_row][ed_col] != ')' && ed_col != 0) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
    }

    if (ed_data[ed_row][ed_col] == '(' && ed_col == 0) {
	goto skip;
    }

    /* skip space */
    while (1) {
	if (ed_col > 0 && ed_data[ed_row][ed_col] == ' ') {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == EOL) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == '(') {
	    ed_col1--;
	    ed_col--;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (ed_data[ed_row][ed_col] == ' ' ||
		    ed_data[ed_row][ed_col] == '(' ||
		    ed_data[ed_row][ed_col] == EOL)) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	} else {
	    break;
	}
    }

    if (ed_data[ed_row][ed_col] == ')'
	&& ed_data[ed_row][ed_col - 1] == ')') {
	ed_col--;
    }

    if (ed_data[ed_row][ed_col] == ')') {
	pos = find_lparen(1);
	if (pos.row != -1) {
	    ed_row = pos.row;
	    ed_col = ed_col1 = pos.col;
	}
    } else {
	while (ed_data[ed_row][ed_col] != ' ' &&
	       ed_data[ed_row][ed_col] != '(' &&
	       ed_data[ed_row][ed_col] != ')' && ed_col != 0) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
	ed_col1++;
	ed_col++;
    }

  skip:
    if (ed_row < ed_start) {
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0)
	    ed_start = 0;
    }
    display_screen();
    restore_cursol();
}


void word_prev()
{
    if (ed_row == 0 && ed_col == 0) {
	clear_status();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	return;
    }
    // skip word char 
    if (is_word_char(ed_data[ed_row][ed_col])) {
	while (is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
    }
    // skip space 
    while (1) {
	if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (!is_word_char(ed_data[ed_row][ed_col]))) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_col > 0 && !is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	} else {
	    break;
	}
    }

    // skip word char 
    if (is_word_char(ed_data[ed_row][ed_col])) {
	while (is_word_char(ed_data[ed_row][ed_col])) {
	    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
	    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
	}
    }

    ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
    ed_col = ed_col + increase_buffer(ed_row, ed_col);

  skip:
    if (ed_row > ed_start + ed_scroll) {
	ed_start = ed_row - ed_scroll / 2;
    }
    display_screen();
    restore_cursol();
}


void list_prev()
{
    struct position pos;

    /* skip space */
    while (1) {
	if (ed_data[ed_row][ed_col] == ')') {
	    break;
	} else if (ed_col > 0) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == EOL) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (ed_data[ed_row][ed_col] == ' ' ||
		    ed_data[ed_row][ed_col] == '(' ||
		    ed_data[ed_row][ed_col] == EOL)) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	}
    }

    pos = find_lparen(1);
    if (pos.row != -1) {
	ed_row = pos.row;
	ed_col = ed_col1 = pos.col;
    }

  skip:
    if (ed_row < ed_start) {
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0)
	    ed_start = 0;
    }
    display_screen();
    restore_cursol();
}

void list_up()
{
    int old_row, old_col, old_col1;

    old_row = ed_row;
    old_col = ed_col;
    old_col1 = ed_col1;
    if (ed_col > 0 && ed_data[ed_row][ed_col] == '(') {
	ed_col--;
	ed_col1--;
    }

    /* skip space */
    while (1) {
	if (ed_data[ed_row][ed_col] == '(') {
	    break;
	} else if (ed_data[ed_row][ed_col] == ')') {
	    ESCREV();
	    ESCMOVE(ed_footer, 1);
	    clear_status();
	    ESCMOVE(ed_footer, 1);
	    CHECK(addstr, "Can't find");
	    ESCRST();
	    ed_row = old_row;
	    ed_col = old_col;
	    ed_col1 = old_col1;
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    return;
	} else if (ed_col > 0) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_col > 0 && ed_data[ed_row][ed_col] == EOL) {
	    ed_col1--;
	    ed_col--;
	} else if (ed_row > 0 && ed_col == 0 &&
		   (ed_data[ed_row][ed_col] == ' ' ||
		    ed_data[ed_row][ed_col] == EOL)) {
	    ed_col = ed_col1 = 0;
	    ed_row--;
	    while (ed_data[ed_row][ed_col] != EOL) {
		ed_col1 = ed_col1 + increase_terminal(ed_row, ed_col);
		ed_col = ed_col + increase_buffer(ed_row, ed_col);
	    }
	} else if (ed_row == 0 && ed_col == 0) {
	    goto skip;
	}
    }


  skip:
    if (ed_row < ed_start) {
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0)
	    ed_start = 0;
    }
    display_screen();
    restore_cursol();
}

void redisplay_screen()
{
    ed_start = ed_row - ed_scroll / 2;
    if (ed_start < 0)
	ed_start = 0;

    display_screen();
    restore_cursol();
}

//-----------cut and paste-------------------------------
void cut_line()
{
    ed_clip_start = ed_clip_end = ed_row;
    copy_selection();
    delete_selection();
    ed_row = ed_clip_start;
    ed_clip_start = ed_clip_end = -1;
    restore_paren();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void mark_unmark(void)
{
    if (ed_clip_start == -1) {
	ed_clip_start = ed_clip_end = ed_row;
	ESCMOVE(ed_footer, 1);
	ESCREV();
	CHECK(addstr, "marked");
	ESCRST();
	restore_cursol();
	return;
    } else {
	ed_clip_start = ed_clip_end = -1;
	display_screen();
	ESCMOVE(ed_footer, 1);
	ESCREV();
	CHECK(addstr, "unmark");
	ESCRST();
	restore_cursol();
	return;
    }
}

void cut_selection()
{
    copy_selection();
    delete_selection();
    restore_paren();
    ed_start = ed_clip_start - ed_scroll / 2;
    if (ed_start < 0)
	ed_start = 0;
    ed_row = ed_clip_start - 1;
    if (ed_row < 0)
	ed_row = 0;
    ed_col = 0;
    ed_clip_start = ed_clip_end = -1;
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void uncut_selection()
{
    paste_selection();
    restore_paren();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void save_selection()
{
    copy_selection();
    ed_row = ed_clip_start;
    ed_clip_start = ed_clip_end = -1;
    restore_paren();
    display_screen();
    restore_cursol();
    modify_flag = true;
}

//-----------------command----------------------------

char *replace_tilde(char *fname)
{
    if (fname[0] == '~') {
	static char fname1[256];
	char *home = getenv("HOME");
	if (home == NULL)
	    return "";
	else {
	    strcpy(fname1, home);
	    strcat(fname1, fname + 1);
	    return fname1;
	}
    } else {
	return fname;
    }
}

bool quit_with_save(void)
{
    int c;
    if (!modify_flag) {
	ESCCLS();
	ESCMOVE(1, 1);
	return true;
    } else {
	do {
	    ESCREV();
	    ESCMOVE(ed_footer, 1);
	    CHECK(addstr, "save modified buffer? Yes/No ");
	    CHECK(refresh);
	    c = getch();
	    if (c == ERR) {
		errw("getch");
	    }
	    ESCRST();
	    switch (c) {
	    case 'y':
		if (strcmp(fname, "") != 0) {
		    save_data(fname);
		} else {
		    save_file_as();
		}
		ESCCLS();
		ESCMOVE(1, 1);
		return true;
		break;
	    case 'n':
		ESCCLS();
		ESCMOVE(1, 1);
		return true;
		break;
	    case CTRL('G'):
		clear_status();
		ESCRST();
		restore_cursol();
		ctrl_c = 0;
		return false;
		break;
	    }
	}
	while (c != 'y' && c != 'n');
    }

    return (false);
}

void save_file()
{
    if (strcmp(fname, "") == 0) {
	ESCMOVE(ed_footer, 1);
	clear_status();
	CHECK(addstr, "filename:  ");
	strcpy(fname, replace_tilde(getname()));
	if (cancel_flag) {
	    cancel_flag = 0;
	    clear_status();
	    ESCRST();
	    restore_cursol();
	    return;
	}
    }
    save_data(fname);
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    ESCMOVE(ed_footer, 1);
    CHECK(addstr, "saved ");
    CHECK(addstr, fname);
    ESCRST();
    restore_cursol();
    modify_flag = false;
}


void save_file_as()
{
    char str1[SHORT_STR_MAX];

    ESCMOVE(ed_footer, 1);
    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(str1, replace_tilde(getname()));
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    save_data(str1);
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    ESCMOVE(ed_footer, 1);
    CHECK(addstr, "saved ");
    CHECK(addstr, str1);
    ESCRST();
    restore_cursol();
    modify_flag = false;
}

void save_region()
{
    char str1[SHORT_STR_MAX];

    ESCMOVE(ed_footer, 1);
    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(str1, getname());
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    copy_selection();
    save_copy(str1);
    ed_copy_end = 0;
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    ESCMOVE(ed_footer, 1);
    CHECK(addstr, "saved ");
    CHECK(addstr, str1);
    ESCRST();
    restore_cursol();
}

void insert_file()
{
    char str1[SHORT_STR_MAX];
    int c, row, col;

    /* clear copy buffer */
    for (row = 0; row < COPY_SIZE; row++) {
	for (col = 0; col < COL_SIZE; col++) {
	    ed_copy[row][col] = 0;
	}
    }


    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(str1, getname());
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    ESCRST();
    port = fopen(str1, "r");
    if (port == NULL) {
	clear_status();
	CHECK(addstr, str1);
	CHECK(addstr, " doesn't exist");
	ESCRST();
	restore_cursol();
	return;
    }

    /* load file to copy buffer */
    row = col = 0;
    c = fgetc(port);
    while (c != EOF) {
	ed_copy[row][col] = c;
	if (c == EOL) {
	    row++;
	    col = 0;
	    if (row >= COPY_SIZE - 1) {
		CHECK(printw, "row %d over max-row", row);
	    }
	} else {
	    col++;
	    if (col >= COL_SIZE) {
		CHECK(printw, "column %d over max-column", col);
	    }
	}
	c = fgetc(port);
    }
    /* if get EOF without EOL 
     *  this is a pen[EOF] -> this is a pen[EOL]
     */
    if (col != 0) {
	ed_copy[ed_row][ed_col] = EOL;
	row++;
    }
    ed_copy_end = row;
    ed_copy[ed_copy_end][0] = EOL;
    fclose(port);

    /* paste copy buffer to main buffer */
    paste_selection();
    ed_copy_end = 0;
    display_screen();
    restore_cursol();
    modify_flag = true;
}

void load_file()
{
    int i, j;

    for (i = 0; i < ROW_SIZE; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = 0;
	}
    }

    ESCMOVE(ed_footer, 1);
    clear_status();
    CHECK(addstr, "filename:  ");
    strcpy(fname, replace_tilde(getname()));
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    load_data(fname);
    ESCCLS();
    display_header();
    display_screen();
    ESCMOVE(ed_footer, 1);
    ESCREV();
    CHECK(addstr, "loaded ");
    CHECK(addstr, fname);
    ESCRST();
    ed_row = ed_col = ed_col1 = 0;
    restore_cursol();
    modify_flag = false;

}


//--------------searck word-------------------------------------

void search_next()
{
    char str1[SHORT_STR_MAX];
    struct position pos;

    clear_status();
    CHECK(addstr, "search:    ");
    strcpy(str1, getword1());
    ESCRST();
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    pos = find_word(str1);
    if (pos.row == -1) {
	ESCREV();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "can't find ");
	CHECK(addstr, str1);
	ESCRST();
	restore_cursol();
	return;
    }
    ed_row = pos.row;
    ed_col = ed_col1 = pos.col;
    ed_start = ed_row - ed_scroll / 2;
    if (ed_start < 0) {
	ed_start = 0;
    }
    display_screen();
    restore_cursol();
    ESCREV();
    CHECK(addstr, str1);
    ESCRST();
}

void search_prev()
{
    char str1[SHORT_STR_MAX];
    struct position pos;

    clear_status();
    CHECK(addstr, "search:    ");
    strcpy(str1, getword1());
    ESCRST();
    if (cancel_flag) {
	cancel_flag = 0;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    pos = find_word_back(str1);
    if (pos.row == -1) {
	ESCREV();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "can't find ");
	CHECK(addstr, str1);
	ESCRST();
	restore_cursol();
	return;
    }
    ed_row = pos.row;
    ed_col = ed_col1 = pos.col;
    ed_start = ed_row - ed_scroll / 2;
    if (ed_start < 0) {
	ed_start = 0;
    }
    display_screen();
    restore_cursol();
    ESCREV();
    CHECK(addstr, str1);
    ESCRST();
}


void transfer_word()
{
    int c;
    char str1[SHORT_STR_MAX], str2[SHORT_STR_MAX];
    struct position pos;

    clear_status();
    CHECK(addstr, "search: ");
    strcpy(str1, getword1());
    clear_status();
    if (cancel_flag) {
	cancel_flag = false;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    CHECK(addstr, "replace: ");
    strcpy(str2, getword2());
    if (cancel_flag) {
	cancel_flag = false;
	clear_status();
	ESCRST();
	restore_cursol();
	return;
    }
    ESCRST();
    pos = find_word(str1);
    while (pos.row != -1) {
	ed_row = pos.row;
	ed_col = ed_col1 = pos.col;
	ed_start = ed_row - ed_scroll / 2;
	if (ed_start < 0) {
	    ed_start = 0;
	}
	display_screen();
	restore_cursol();
	ESCREV();
	CHECK(addstr, str1);
	clear_status();
	do {
	    CHECK(addstr, "replace? y/n ");
	    ESCRST();
	    CHECK(refresh);
	    c = getch1();
	}
	while (c != 'y' && c != 'n' && c != CTRL('G'));
	if (c == 'y') {
	    ed_row = pos.row;
	    ed_col = ed_col1 = pos.col;
	    replace_word(str1, str2);
	    display_screen();
	    modify_flag = true;
	    ed_col++;
	} else if (c == CTRL('G')) {
	    clear_status();
	    ESCRST();
	    display_screen();
	    restore_cursol();
	    return;
	} else {
	    display_screen();
	    ed_col++;
	}
	pos = find_word(str1);
    }
    clear_status();
    CHECK(addstr, "can't find ");
    CHECK(addstr, str1);
    ESCRST();
    restore_cursol();
}


void completion()
{
    int i, c;
    find_candidate();		// completion
    if (ed_candidate_pt == 0)
	return;
    else if (ed_candidate_pt == 1) {
	replace_fragment(ed_candidate[0]);
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
    } else {
	const int CANDIDATE = 3;
	int k = 0;
	ESCMOVE(ed_footer, 1);
	bool more_candidates_selected;
	do {
	    more_candidates_selected = false;
	    ESCREV();
	    for (i = 0; i < CANDIDATE; i++) {
		if (i + k >= ed_candidate_pt)
		    break;
		CHECK(printw, "%d:%s ", i + 1, ed_candidate[i + k]);
	    }
	    if (ed_candidate_pt > k + CANDIDATE)
		CHECK(addstr, "4:more");
	    ESCRST();
	    bool bad_candidate_selected;
	    do {
		bad_candidate_selected = false;
		CHECK(refresh);
		c = getch();
		if (c == ERR) {
		    errw("getch");
		}
		if (c != CTRL('G')) {
		    i = c - '1';
		    more_candidates_selected =
			ed_candidate_pt > k + CANDIDATE && i == CANDIDATE;
		    if (more_candidates_selected) {
			k = k + CANDIDATE;
			ESCMVLEFT(1);
			ESCCLSL();
			break;
		    }
		    bad_candidate_selected =
			i + k > ed_candidate_pt || i < 0 || c == RET;
		} else {
		    ESCMOVE(ed_footer, 1);
		    ESCREV();
		    clear_status();
		    ESCRST();
		    return;
		}
	    }
	    while (bad_candidate_selected);
	}
	while (more_candidates_selected);
	if (c != ESC)
	    replace_fragment(ed_candidate[i + k]);
	display_screen();
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
    }
    return;
}



void pageup()
{
    ed_start = ed_start - ed_scroll;
    if (ed_start < 0)
	ed_start = 0;
    ed_row = ed_start;
    display_screen();
    restore_cursol();
}

void home()
{
    ed_row = 0;
    ed_start = 0;
    recalculate_col(ed_row, ed_col);
    display_screen();
    ESCMOVE(2, ed_col1 + LEFT_MARGIN);
}

void end()
{
    ed_row = ed_end;
    if (ed_end > ed_scroll)
	ed_start = ed_row - ed_middle;
    recalculate_col(ed_row, ed_col);
    display_screen();
    restore_cursol();
}

void pagedn()
{
    if (ed_end < ed_start + ed_scroll)
	return;
    ed_start = ed_start + ed_scroll;
    if (ed_start > ed_end)
	ed_start = ed_end - ed_scroll;
    ed_row = ed_start;
    recalculate_col(ed_row, ed_col);
    display_screen();
    restore_cursol();
}


char *getname()
{
    int c;
    static int pos;
    static char buf[SHORT_STR_MAX];

    cancel_flag = false;
    ESCMOVE(ed_footer, 12);
    ESCREV();
    CHECK(addstr, "                    ");
    ESCMOVE(ed_footer, 12);
    CHECK(addstr, buf);
    ESCRST();

    while (1) {
	CHECK(refresh);
	c = getch();
	if (c == ERR) {
	    errw("getch");
	}
	switch (c) {
	case RET:
	    if (strcmp(buf, "") == 0)
		break;
	    else
		return (buf);
	case KEY_BACKSPACE:
	case DEL:
	    if (pos > 0)
		pos--;
	    buf[pos] = 0;
	    break;
	case CTRL('G'):
	    cancel_flag = true;
	    return (buf);
	default:
	    if (pos > SHORT_STR_MAX)
		break;
	    else if (c < 20)
		break;
	    buf[pos] = c;
	    pos++;
	    break;
	}
	ESCMOVE(ed_footer, 12);
	ESCREV();
	CHECK(addstr, "                    ");
	ESCMOVE(ed_footer, 12);
	CHECK(addstr, buf);
	ESCRST();
    }

}


char *getword1()
{
    int c;
    static int pos;
    static char buf[SHORT_STR_MAX];

    cancel_flag = false;
    ESCMOVE(ed_footer, 12);
    ESCREV();
    CHECK(addstr, "                    ");
    ESCMOVE(ed_footer, 12);
    CHECK(addstr, buf);
    ESCRST();

    while (1) {
	CHECK(refresh);
	c = getch();
	if (c == ERR) {
	    errw("getch");
	}
	switch (c) {
	case RET:
	    if (strcmp(buf, "") == 0)
		break;
	    else
		return (buf);
	case KEY_BACKSPACE:
	case DEL:
	    if (pos > 0)
		pos--;
	    buf[pos] = 0;
	    break;
	case CTRL('G'):
	    cancel_flag = true;
	    return (buf);
	default:
	    if (pos > SHORT_STR_MAX)
		break;
	    else if (c < 20)
		break;
	    buf[pos] = c;
	    pos++;
	    break;
	}
	ESCMOVE(ed_footer, 12);
	ESCREV();
	CHECK(addstr, "                    ");
	ESCMOVE(ed_footer, 12);
	CHECK(addstr, buf);
	ESCRST();
    }

}

char *getword2()
{
    int c;
    static int pos;
    static char buf[SHORT_STR_MAX];

    cancel_flag = false;
    ESCMOVE(ed_footer, 12);
    ESCREV();
    CHECK(addstr, "                    ");
    ESCMOVE(ed_footer, 12);
    CHECK(addstr, buf);
    ESCRST();

    while (1) {
	CHECK(refresh);
	c = getch();
	if (c == ERR) {
	    errw("getch");
	}
	switch (c) {
	case RET:
	    if (strcmp(buf, "") == 0)
		break;
	    else
		return (buf);
	case KEY_BACKSPACE:
	case DEL:
	    if (pos > 0)
		pos--;
	    buf[pos] = 0;
	    break;
	case CTRL('G'):
	    cancel_flag = true;
	    return (buf);
	default:
	    if (pos > SHORT_STR_MAX)
		break;
	    else if (c < 20)
		break;
	    buf[pos] = c;
	    pos++;
	    break;
	}
	ESCMOVE(ed_footer, 12);
	ESCREV();
	CHECK(addstr, "                    ");
	ESCMOVE(ed_footer, 12);
	CHECK(addstr, buf);
	ESCRST();
    }

}

void edit_screen(void)
{
    restore_cursol();
    bool quit = edit_loop();
    while (!quit) {
	quit = edit_loop();
    }
}

bool edit_loop(void)
{
    int c;

    static int skip = 0;

    CHECK(refresh);
    c = getch1();
    switch (c) {
    case CTRL('H'):
	help();
	break;
    case CTRL('F'):
	right();
	break;
    case CTRL('B'):
	left();
	break;
    case CTRL('P'):
	up();
	break;
    case CTRL('N'):
	down();
	break;
    case CTRL('D'):
	del();
	break;
    case CTRL('A'):
	line_begin();
	break;
    case CTRL('E'):
	line_end();
	break;
    case CTRL('K'):
	cut_line();
	break;
    case CTRL('W'):
	cut_selection();
	break;
    case CTRL('Y'):
	uncut_selection();
	break;
    case CTRL('X'):
	ESCMOVE(ed_footer, 1);
	ESCREV();
	clear_status();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "^X");
	ESCRST();
	while (1) {
	    c = getch1();
	    switch (c) {
	    case CTRL('C'):
		return (quit_with_save());
	    case CTRL('S'):
		save_file();
		return false;
	    case CTRL('F'):
	    case CTRL('V'):
		load_file();
		return false;
	    case CTRL('W'):
		save_file_as();
		return false;
	    case CTRL('I'):
		insert_file();
		return false;
	    case CTRL('P'):
		save_region();
		return false;
	    case CTRL('Z'):
		ESCCLS();
		ESCMOVE(1, 1);
		return true;
	    case CTRL('G'):
		ESCMOVE(ed_footer, 1);
		ESCREV();
		clear_status();
		ESCRST();
		return false;
	    }
	}
	break;
    case CTRL('V'):
	pagedn();
	break;
    case CTRL('S'):
	search_next();
	break;
    case CTRL('R'):
	search_prev();
	break;
    case CTRL('T'):
	transfer_word();
	break;
    case CTRL('L'):
	redisplay_screen();
	break;
    case ESC:
	ESCMOVE(ed_footer, 1);
	ESCREV();
	clear_status();
	ESCMOVE(ed_footer, 1);
	CHECK(addstr, "M");
	ESCRST();
	CHECK(refresh);
	while (1) {
	    c = getch();
	    if (c == ERR) {
		errw("getch");
	    }
	    switch (c) {
	    case 'w':
		save_selection();
		return false;
	    case '<':
		home();
		return false;
	    case '>':
		end();
		return false;
	    case 'v':
		pageup();
		return false;
	    case '^':
		mark_unmark();
		return false;
	    case TAB:
		completion();
		return false;
	    case 'i':
		information();
		return false;
	    case 'f':
		word_next();
		return false;
	    case 'b':
		word_prev();
		return false;
	    case CTRL('F'):
		sexp_next();
		return false;
	    case CTRL('B'):
		sexp_prev();
		return false;
	    case CTRL('N'):
		list_next();
		return false;
	    case CTRL('P'):
		list_prev();
		return false;
	    case CTRL('D'):
		list_down();
		return false;
	    case CTRL('U'):
		list_up();
		return false;
	    case CTRL('G'):
		ESCMOVE(ed_footer, 1);
		ESCREV();
		clear_status();
		ESCRST();
		return false;
	    }
	}
	break;
    case KEY_UP:
	up();
	break;
    case KEY_DOWN:
	down();
	break;
    case KEY_LEFT:
	left();
	break;
    case KEY_RIGHT:
	right();
	break;
    case KEY_HOME:
	home();
	break;
    case KEY_END:
	end();
	break;
    case KEY_IC:
	ed_ins = !ed_ins;
	display_header();
	restore_cursol();
	break;
    case KEY_PPAGE:
	pageup();
	break;
    case KEY_NPAGE:
	pagedn();
	break;
    case KEY_DC:
	del();
	break;
    case KEY_BACKSPACE:
    case DEL:
	backspace_key();
	break;
    case RET:
    case CTRL('O'):
	return_key();
	break;
    case TAB:
	tab_key();
	break;
    default:
	if (ed_col >= COL_SIZE)
	    break;
	ESCCLSLA();
	restore_paren();
	if (ed_ins)
	    insert_col();
	ed_data[ed_row][ed_col] = c;
	ESCMOVE(ed_row + TOP_MARGIN - ed_start, 1);
	display_line(ed_row);
	emphasis_lparen();
	emphasis_rparen();
	ed_col++;
	if (isUni1(c) && skip == 0) {
	    ed_col1++;
	    skip = 0;
	} else if (isUni2(c) && skip == 0) {
	    ed_col1++;
	    skip = 1;
	} else if (isUni4(c) && skip == 0) {
	    ed_col1++;
	    skip = 3;
	} else if (isUni3(c) && skip == 0) {
	    int unicode;
	    unicode = utf8_to_ucs4(ed_row, ed_col);
	    if ((unicode >= 0x0E31 && unicode <= 0x0E3A)
		|| (unicode >= 0x0E47 && unicode <= 0x0E4E))
		skip = 2;
	    else {
		ed_col1++;
		skip = 2;
	    }
	}

	if (skip > 0)
	    skip--;


	restore_cursol();
	modify_flag = true;
    }
    return false;
}

void display_header(void)
{
    int i;
    ESCHOME();
    ESCREV();
    for (i = 0; i < COLS - 1; i++)
	CHECK(addch, ' ');
    ESCHOME();
    CHECK(printw, "Edlis %1.2f        File: %s   ", VERSION, fname);
    ESCMOVE(1, COLS - 9);
    if (ed_ins == true) {
	CHECK(addstr, "   insert");
    } else {
	CHECK(addstr, "overwrite");
    }
    ESCRST();
}

void display_screen()
{
    int line1, line2, i;

    ESCTOP();
    ESCCLS1();
    line1 = ed_start;
    line2 = ed_start + ed_scroll;
    if (line2 > ed_end)
	line2 = ed_end;

    while (line1 <= line2) {
	display_line(line1);
	line1++;
    }
    ESCMOVE(ed_footer, 1);
    ESCREV();
    for (i = 0; i < COLS - 9; i++)
	CHECK(addch, ' ');
    CHECK(addstr, "^H(help)");
    ESCRST();
}

void help(void)
{
    ESCMOVE(2, 1);
    ESCCLS1();
    CHECK(addstr, "--- Edlis help(1) ---\n"
	  "CTRL+F  move to right in character units     → key\n"
	  "CTRL+B  move to left in character units      ← key\n"
	  "CTRL+P  move to up in line                   ↑ key\n"
	  "CTRL+N  move to down in line                 ↓ key\n"
	  "CTRL+J  move to end of line\n"
	  "CTRL+A  move begin of line\n"
	  "CTRL+E  move to end of line\n"
	  "CTRL+D  delete one char                       Back Space key\n"
	  "CTRL+O  return                                Enter key\n"
	  "CTRL+V  display next page                     Page Down key\n"
	  "ESC V   display previous page                 Page Up key\n"
	  "ESC <   goto top page                         Home key\n"
	  "ESC >   goto end page                         End key\n"
	  "ESC f   Move forward in word units\n"
	  "ESC b   Move backward in word units\n"
	  "ESC CTRL+F  Move forward in S-expressdion units\n"
	  "ESC CTRL+B  Move Back in S-expression units\n"
	  "ESC CTRL+N  Move forward in list units\n"
	  "ESC CTRL+P  Move back in list units\n"
	  "ESC CTRL+U  Move up a level in the list structure\n"
	  "ESC STRL+D  Move down a level in the list structure\n"
	  "--- enter any key to go next page ---");
    CHECK(refresh);
    CHECK(getch);
    ESCMOVE(2, 1);
    ESCCLS1();
    CHECK(addstr, "--- Edlis help(2) ---\n"
	  "Insert      Switch insert-mode and overwrite-mode\n"
	  "TAB     insert spaces as lisp indent rule\n"
	  "CTRL+X  CTRL+C quit from editor with save\n"
	  "CTRL+X  CTRL+Z quit from editor without save\n"
	  "CTRL+X  CTRL+F load from file to editor\n"
	  "CTRL+X  CTRL+V load from file to editor\n"
	  "CTRL+X  CTRL+I insert buffer from file\n"
	  "CTRL+X  CTRL+S save file\n"
	  "CTRL+X  CTRL+W save file as\n"
	  "CTRL+X  CTRL+L save region to file as\n"
	  "CTRL+S  search a word forward\n"
	  "CTRL+R  search a word backward\n"
	  "CTRL+T  replace a word\n"
	  "ESC TAB complete builtin function name\n"
	  "ESC I   info of function\n"
	  "ESC ^   mark(or unmark) row for selection\n"
	  "CTRL+K  cut one line \n"
	  "CTRL+W  cut selection\n"
	  "ESC W   save selection\n"
	  "CTRL+Y  uncut selection\n"
	  "CTRL+G  cancel command\n" "--- enter any key to exit help ---");
    CHECK(refresh);
    CHECK(getch);
    display_screen();
    restore_cursol();
}

/*                                     COL_SIZE
 * buffer [0].........................[255]
 * ed_col = position of buffer
 * LEFT_MARGIN area of line numver 7
 * COLS = size of terminal
 *
 * if terminal col size is 80.
 * 1----6|7--------80|
 * line   buffer[ 0]-[72]
 *        buffer[73]-[145]
 *        ommit 146~
 * turnaround point is 73 (80-7)
 * col is display point 0~, 73~ 
*/

/*
 * unicode for Edlis
 * Now many OS adapted UTF8. unicode in ed_data is utf8 
 * e.g.  Japanese あ  0xe3 0x81 0x82
 * curses require wchar_t wide-charactor. so transform from multibyte-utf8 to wide-charactor.
 * and use addwstr thus display unicode
*/
void display_unicode(int line, int col)
{
    char mb[10];
    wchar_t wch[10];
    if (isUni1(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = 0;
    } else if (isUni2(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = ed_data[line][col + 1];
	mb[2] = 0;
    } else if (isUni3(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = ed_data[line][col + 1];
	mb[2] = ed_data[line][col + 2];
	mb[3] = 0;
    } else if (isUni4(ed_data[line][col])) {
	mb[0] = ed_data[line][col];
	mb[1] = ed_data[line][col + 1];
	mb[2] = ed_data[line][col + 2];
	mb[3] = ed_data[line][col + 3];
	mb[4] = 0;
    }

    mbstowcs(wch, mb, 10);
    addwstr(wch);
}


int find_turn_buffer_position(int line)
{
    int col, col1, turn;

    turn = COLS - LEFT_MARGIN;
    col = col1 = 0;
    while (col1 < turn) {
	col1 = col1 + increase_terminal(line, col);
	col = col + increase_buffer(line, col);
    }
    return (col);
}

void display_line(int line)
{
    int col, col1, turn;
    char linestr[10];

    turn = COLS - LEFT_MARGIN;
    sprintf(linestr, "% 5d ", line);
    CHECK(addstr, linestr);


    if (ed_col1 < turn)
	col = col1 = 0;
    else {
	col = find_turn_buffer_position(line);	// need recalculation
	col1 = turn;
    }
    while (((ed_col1 < turn && col1 < turn)
	    || (ed_col1 >= turn && col < COL_SIZE))
	   && ed_data[line][col] != EOL && ed_data[line][col] != NUL) {
	if (line >= ed_clip_start && line <= ed_clip_end)
	    ESCREV();
	else
	    ESCRST();

	if (ed_incomment != -1 && line >= ed_incomment) {	// comment 
	    // 
	    // #|...|#
	    ESCBOLD();
	    set_color(ed_comment_color);
	    while (((ed_col1 < turn && col1 < turn)
		    || (ed_col1 >= turn && col < COL_SIZE))
		   && ed_data[line][col] != EOL
		   && ed_data[line][col] != NUL) {
		if (isUni1(ed_data[line][col])) {
		    CHECK(addch, ed_data[line][col]);
		} else {
		    display_unicode(line, col);
		}
		col1 = col1 + increase_terminal(line, col);
		col = col + increase_buffer(line, col);

		if (ed_data[line][col - 2] == '|' &&
		    ed_data[line][col - 1] == '#') {
		    ed_incomment = -1;
		    ESCRST();
		    ESCFORG();
		    break;
		}
	    }
	    ESCRST();
	    ESCFORG();
	} else if (ed_data[line][col] == ' ' ||
		   ed_data[line][col] == '(' || ed_data[line][col] == ')')
	{
	    CHECK(addch, ed_data[line][col]);
	    col++;
	    col1++;
	} else {
	    switch (check_token(line, col)) {
	    case HIGHLIGHT_SYNTAX:
		ESCBOLD();
		set_color(ed_syntax_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_BUILTIN:
		ESCBOLD();
		set_color(ed_builtin_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_STRING:
		ESCBOLD();
		set_color(ed_string_color);
		CHECK(addch, ed_data[line][col]);
		col++;
		col1++;
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    if (isUni1(ed_data[line][col])) {
			CHECK(addch, ed_data[line][col]);
		    } else {
			display_unicode(line, col);
		    }
		    col1 = col1 + increase_terminal(line, col);
		    col = col + increase_buffer(line, col);


		    if (ed_data[line][col - 1] == '"' &&
			ed_data[line][col - 2] != '\\')
			break;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_COMMENT:
		ESCBOLD();
		set_color(ed_comment_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    if (isUni1(ed_data[line][col])) {
			CHECK(addch, ed_data[line][col]);
		    } else {
			display_unicode(line, col);
		    }
		    col1 = col1 + increase_terminal(line, col);
		    col = col + increase_buffer(line, col);

		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_EXTENDED:
		ESCBOLD();
		set_color(ed_extended_color);
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_MULTILINE_COMMENT:
		ESCBOLD();
		set_color(ed_comment_color);
		ed_incomment = line;
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != EOL
		       && ed_data[line][col] != NUL) {
		    CHECK(addch, ed_data[line][col]);
		    col++;
		    col1++;
		    if (ed_data[line][col - 2] == '|' &&
			ed_data[line][col - 1] == '#') {
			ed_incomment = -1;
			ESCRST();
			ESCFORG();
			break;
		    }
		}
		break;
	    default:
		while (((ed_col1 < turn && col1 < turn)
			|| (ed_col1 >= turn && col < COL_SIZE))
		       && ed_data[line][col] != ' '
		       && ed_data[line][col] != '('
		       && ed_data[line][col] != ')'
		       && ed_data[line][col] != NUL
		       && ed_data[line][col] != EOL) {
		    if (isUni1(ed_data[line][col])) {
			CHECK(addch, ed_data[line][col]);
		    } else {
			display_unicode(line, col);
		    }
		    col1 = col1 + increase_terminal(line, col);
		    col = col + increase_buffer(line, col);

		}
	    }
	}
    }
    CHECK(addch, EOL);
    ESCRST();
}

void set_color(enum Color n)
{
    if (has_colors()) {
	CHECK(color_set, n, NULL);
    }
}

void backspace(void)
{
    int i, size;

    if (ed_data[ed_row][ed_col - 1] == ')') {
	ed_lparen_row = -1;
	ed_rparen_row = -1;
    }
    i = ed_col;
    size = decrease_buffer(ed_row, ed_col - 1);
    ed_col1 = ed_col1 - decrease_terminal(ed_row, ed_col - 1);
    ed_col = ed_col - decrease_buffer(ed_row, ed_col - 1);
    while (i < COL_SIZE) {
	ed_data[ed_row][i - size] = ed_data[ed_row][i];
	i++;
    }
}

void delete_char(void)
{
    int i, size;

    if (ed_data[ed_row][ed_col] == ')') {
	ed_lparen_row = -1;
	ed_rparen_row = -1;
    }
    i = ed_col;
    size = increase_buffer(ed_row, ed_col);
    while (ed_data[ed_row][i + size] != 0) {
	ed_data[ed_row][i] = ed_data[ed_row][i + size];
	i++;
    }
    ed_data[ed_row][i] = 0;
}


void insert_col()
{
    int i;

    i = find_eol(ed_row);
    while (i >= ed_col) {
	ed_data[ed_row][i + 1] = ed_data[ed_row][i];
	i--;
    }
}

void insert_row()
{
    int i, j, k;

    for (i = ed_end; i >= ed_row; i--) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i + 1][j] = ed_data[i][j];
	}
    }
    k = 0;
    for (j = ed_col; j < COL_SIZE; j++) {
	ed_data[ed_row + 1][k] = ed_data[ed_row][j];
	k++;
    }
    ed_data[ed_row][ed_col] = EOL;
}

void delete_row()
{
    int i, j, k, l, l1;

    k = l = find_eol(ed_row - 1);
    l1 = find_eol1(ed_row - 1);
    for (j = 0; j < COL_SIZE; j++) {
	ed_data[ed_row - 1][k] = ed_data[ed_row][j];
	k++;
	if (ed_data[ed_row][j] == EOL)
	    break;
    }

    for (i = ed_row; i < ed_end; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = ed_data[i + 1][j];
	}
    }
    ed_row--;
    ed_end--;
    ed_col = l;
    ed_col1 = l1;
}

/*
 * find_eol find position of eol in buffer
*/
int find_eol(int row)
{
    int i;

    for (i = 0; i < COL_SIZE; i++) {
	if (ed_data[row][i] == EOL || ed_data[row][i] == 0)
	    return (i);
    }
    return (-1);
}

/*
* find_eol1 find position of eol on display terminal
*/
int find_eol1(int row)
{
    int col, col1;		// col1 is position of display terminal
    col = col1 = 0;
    while (col < COL_SIZE) {
	if (ed_data[row][col] == EOL)
	    return (col1);
	else if (isUni1(ed_data[row][col])) {
	    col++;
	    col1++;
	} else {
	    if (isUni3(ed_data[row][col]))
		col1 = col1 + 2;
	    else
		col1++;

	    col = col + increase_buffer(row, col);
	}
    }

    return (-1);
}

/* if end of line has no EOL, add EOL*/
void add_eol(void)
{
    int col;

    if (ed_data[ed_end][0] == 0)
	return;

    for (col = 0; col < COL_SIZE; col++) {
	if (ed_data[ed_end][col] == EOL)
	    return;
	else if (ed_data[ed_end][col] == 0) {
	    ed_data[ed_end][col] = EOL;
	    return;
	}
    }
}


struct position find_lparen(int bias)
{
    int nest, row, col, col1, limit;	//col is position of buffer, col1 is position of display
    struct position pos;

    row = ed_row;
    if (ed_col != 0) {
	col = ed_col - bias;
	col1 = ed_col1 - bias;
    } else {
	row--;
	if (row < 0) {
	    pos.col = 0;
	}
	col = find_eol(row);
	col1 = find_eol1(row);
    }

    nest = 0;
    limit = ed_row - ed_scroll;
    if (limit < 0)
	limit = 0;

    while (row >= limit) {
	if (ed_data[row][col] == '('
	    && !(col > 0 && ed_data[row][col - 1] == '\\') && nest == 0)
	    break;
	else if (ed_data[row][col] == ')'
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest++;
	else if (ed_data[row][col] == '('
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest--;
	else if (ed_data[row][col] == '"') {
	    col--;
	    col1--;
	    while (ed_data[row][col] != '"' && col > 0) {
		col1 = col1 - decrease_terminal(row, col);
		col = col - decrease_buffer(row, col);
	    }
	}


	if (col == 0) {
	    row--;
	    if (row > 0) {
		col = find_eol(row);
		col1 = find_eol1(row);
	    }

	} else {
	    col1 = col1 - decrease_terminal(row, col);
	    col = col - decrease_buffer(row, col);
	}
    }
    if (row >= limit) {
	pos.row = row;
	pos.col = col1;
    } else {
	pos.row = -1;
	pos.col = 0;
    }
    return (pos);
}

struct position find_rparen(int bias)
{
    int nest, row, col, col1, limit;	//col is position of buffer, col1 is position of display
    struct position pos;

    row = ed_row;
    col = ed_col + bias;
    col1 = ed_col1 + bias;
    nest = 0;
    limit = ed_row + ed_scroll;
    if (limit > ed_end)
	limit = ed_end;

    while (row < limit) {
	if (ed_data[row][col] == ')'
	    && !(col > 0 && ed_data[row][col - 1] == '\\') && nest == 0)
	    break;
	else if (ed_data[row][col] == '('
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest++;
	else if (ed_data[row][col] == ')'
		 && !(col > 0 && ed_data[row][col - 1] == '\\'))
	    nest--;
	else if (ed_data[row][col] == '"') {
	    col++;
	    col1++;
	    while (ed_data[row][col] != '"' && ed_data[row][col] != EOL
		   && ed_data[row][col] != 0) {
		col1 = col1 + increase_terminal(row, col);
		col = col + increase_buffer(row, col);
	    }
	}


	if (ed_data[row][col] == EOL) {
	    row++;
	    col = col1 = 0;
	} else {
	    col1 = col1 + increase_terminal(row, col);
	    col = col + increase_buffer(row, col);
	}
    }
    if (row < limit) {
	pos.row = row;
	pos.col = col1;
    } else {
	pos.row = -1;
	pos.col = 0;
    }
    return (pos);
}

void reset_paren()
{
    ed_lparen_row = -1;
    ed_rparen_row = -1;
}

void restore_paren()
{
    if (ed_lparen_row != -1 && ed_lparen_row >= ed_start
	&& ed_lparen_row <= ed_start + ed_scroll) {
	if (ed_lparen_col <= COLS - 1 - LEFT_MARGIN)
	    ESCMOVE(ed_lparen_row + TOP_MARGIN - ed_start,
		    ed_lparen_col + LEFT_MARGIN);
	else
	    ESCMOVE(ed_lparen_row + TOP_MARGIN - ed_start,
		    ed_lparen_col - COLS + LEFT_MARGIN);
	ESCBORG();
	CHECK(addch, '(');
	ed_lparen_row = -1;
    }
    if (ed_rparen_row != -1 && ed_rparen_row >= ed_start
	&& ed_rparen_row <= ed_start + ed_scroll) {
	if (ed_rparen_col <= COLS - 1 - LEFT_MARGIN)
	    ESCMOVE(ed_rparen_row + TOP_MARGIN - ed_start,
		    ed_rparen_col + LEFT_MARGIN);
	else
	    ESCMOVE(ed_rparen_row + TOP_MARGIN - ed_start,
		    ed_rparen_col - COLS + LEFT_MARGIN);
	ESCBORG();
	CHECK(addch, ')');
	ed_rparen_row = -1;
    }
}

void emphasis_lparen()
{
    struct position pos;

    if (ed_data[ed_row][ed_col] != ')')
	return;

    pos = find_lparen(1);
    if (ed_col <= COLS - 1 - LEFT_MARGIN
	&& pos.col <= COLS - 1 - LEFT_MARGIN) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, ')');
	    ESCBORG();
	    if (pos.row >= ed_start) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, '(');
	    }
	    ed_lparen_row = pos.row;
	    ed_lparen_col = pos.col;
	    ed_rparen_row = ed_row;
	    ed_rparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    } else if (ed_col >= COLS && pos.col >= COLS) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		    ed_col1 - COLS + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, ')');
	    ESCBORG();
	    if (pos.row >= ed_start) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col - COLS + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, '(');
	    }
	    ed_lparen_row = pos.row;
	    ed_lparen_col = pos.col;
	    ed_rparen_row = ed_row;
	    ed_rparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    }
}

void emphasis_rparen()
{
    struct position pos;

    if (ed_data[ed_row][ed_col] != '(')
	return;

    pos = find_rparen(1);
    if (ed_col <= COLS - 1 - LEFT_MARGIN
	&& pos.col <= COLS - 1 - LEFT_MARGIN) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, '(');
	    ESCBORG();
	    if (pos.row <= ed_start + ed_scroll) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, ')');
	    }
	    ed_rparen_row = pos.row;
	    ed_rparen_col = pos.col;
	    ed_lparen_row = ed_row;
	    ed_lparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    } else if (ed_col >= COLS && pos.col >= COLS) {
	if (pos.row != -1) {
	    ESCMOVE(ed_row + TOP_MARGIN - ed_start,
		    ed_col1 - COLS + LEFT_MARGIN);
	    ESCBCYAN();
	    CHECK(addch, '(');
	    ESCBORG();
	    if (pos.row <= ed_start + ed_scroll) {
		ESCMOVE(pos.row + TOP_MARGIN - ed_start,
			pos.col - COLS + LEFT_MARGIN);
		ESCBCYAN();
		CHECK(addch, ')');
	    }
	    ed_rparen_row = pos.row;
	    ed_rparen_col = pos.col;
	    ed_lparen_row = ed_row;
	    ed_lparen_col = ed_col1;
	    ESCBORG();
	}
	restore_cursol();
    }
}


void softtabs(int n)
{
    while (n > 0) {
	insert_col();
	ed_data[ed_row][ed_col] = ' ';
	ed_col++;
	ed_col1++;
	n--;
    }
}


void save_data(char *fname)
{
    int row, col;

    /* 
     * If the final line does not end with a newline, 
     * a newline will be inserted before saving.
     */
    col = 0;
    while (ed_data[ed_end][col] != 0) {
	if (ed_data[ed_end][col] == EOL)
	    goto exit;
	col++;
    }
    if (col != 0) {
	ed_data[ed_end][col] = EOL;
	ed_end++;
    }


  exit:
    {
	FILE *port = fopen(fname, "w");
	for (row = 0; row < ed_end; row++)
	    for (col = 0; col < COL_SIZE; col++) {
		fputc(ed_data[row][col], port);
		if (ed_data[row][col] == EOL)
		    break;
	    }
	fclose(port);
    }
}

void save_copy(char *fname)
{
    int row, col;

    FILE *port = fopen(fname, "w");
    for (row = 0; row < ed_copy_end; row++) {
	for (col = 0; col < COL_SIZE; col++) {
	    fputc(ed_copy[row][col], port);
	    if (ed_copy[row][col] == EOL)
		break;
	}
    }
    fputc(EOL, port);
    fclose(port);
}

void load_data(char *fname)
{
    port = fopen(fname, "r");
    ed_row = 0;
    ed_col = 0;
    ed_col1 = 0;
    ed_start = 0;
    ed_end = 0;
    ed_lparen_row = -1;
    ed_rparen_row = -1;
    ed_clip_start = -1;
    ed_clip_end = -1;
    if (port != NULL) {
	int c;

	c = fgetc(port);
	while (c != EOF) {
	    ed_data[ed_row][ed_col] = c;
	    if (c == EOL) {
		ed_row++;
		ed_col = ed_col1 = 0;
		if (ed_row > ROW_SIZE)
		    printf("row %d over max-row", ed_row);
	    } else {
		ed_col++;
		if (ed_col > COL_SIZE)
		    printf("column %d over max-column", ed_col);
	    }
	    c = fgetc(port);
	}
	ed_end = ed_row;
	add_eol();
	fclose(port);
    }
}


bool is_special(int row, int col)
{
    char str[TOKEN_MAX];
    int pos;

    pos = 0;
    while (ed_data[row][col] != ' ' &&
	   ed_data[row][col] != '(' && ed_data[row][col] >= ' ') {
	str[pos] = ed_data[row][col];
	col++;
	pos++;
    }
    str[pos] = NUL;
    if (pos == 0)
	return false;
    return in_special_table(str);
}

int findnext(int row, int col)
{
    if (ed_data[row][col] == '(')
	return (col);
    else {
	while (ed_data[row][col] != ' ' && ed_data[row][col] > ' ')
	    col++;

	while (ed_data[row][col] == ' ')
	    col++;
    }
    return (col);
}


void remove_headspace(int row __unused)
{
    int col, i, j, k;

    col = 0;
    while (ed_data[ed_row][col] == ' ')
	col++;
    k = find_eol(ed_row);
    if (k == -1)		// can't find
	k = 0;
    i = 0;
    for (j = col; j <= k; j++) {
	ed_data[ed_row][i] = ed_data[ed_row][j];
	i++;
    }
}

int calc_tabs()
{
    struct position pos;

    if (ed_row == 0 && ed_col == 0)
	return (0);

    pos = find_lparen(0);


    if (pos.row == -1)
	return (0);		// can't find left paren

    if (is_special(pos.row, pos.col + 1))
	return (pos.col + 4);
    else
	return (findnext(pos.row, pos.col + 1));

    return (0);			// dummy
}

void copy_selection()
{
    int i, j, k;

    if (ed_clip_end - ed_clip_start > COPY_SIZE)
	return;

    j = 0;
    for (i = ed_clip_start; i <= ed_clip_end; i++) {
	for (k = 0; k < COLS; k++)
	    ed_copy[j][k] = ed_data[i][k];
	j++;
    }
    ed_copy_end = j;
}

void paste_selection()
{
    int i, j, k;

    if (ed_copy_end == 0)
	return;
    if (ed_end + ed_copy_end > ROW_SIZE) {
	clear_status();
	ESCMOVE(ed_footer, 1);
	ESCREV();
	CHECK(addstr, "Buffer over flow");
	ESCRST();
	restore_cursol();
	return;
    }

    for (i = ed_end; i >= ed_row; i--) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i + ed_copy_end][j] = ed_data[i][j];
	}
    }
    ed_end = ed_end + ed_copy_end;
    ed_data[ed_end][0] = EOL;

    k = ed_row;
    for (i = 0; i < ed_copy_end; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[k][j] = ed_copy[i][j];
	}
	k++;
    }

}

void delete_selection()
{
    int i, j, k;

    if (ed_clip_start == -1)
	return;
    k = ed_clip_end - ed_clip_start + 1;
    for (i = ed_clip_start; i <= ed_end; i++) {
	for (j = 0; j < COL_SIZE; j++) {
	    ed_data[i][j] = ed_data[i + k][j];
	}
    }
    ed_end = ed_end - k;
    ed_data[ed_end][0] = EOL;
}

enum HighlightToken check_token(int row, int col)
{
    char str[COL_SIZE];
    int pos;

    pos = 0;
    if (ed_data[row][col] == '"')
	return HIGHLIGHT_STRING;
    else if (ed_data[row][col] == ';')
	return HIGHLIGHT_COMMENT;
    while (ed_data[row][col] != ' ' &&
	   ed_data[row][col] != '(' &&
	   ed_data[row][col] != ')' &&
	   ed_data[row][col] != NUL && ed_data[row][col] != EOL) {
	str[pos] = ed_data[row][col];
	col++;
	pos++;
    }
    str[pos] = NUL;
    if (pos == 0)
	return HIGHLIGHT_NONE;
    else if (str[0] == '#' && str[1] == '|')
	return HIGHLIGHT_MULTILINE_COMMENT;	// #|...|#
    return maybe_match(str);
}

char *get_fragment()
{
    static char str[TOKEN_MAX];
    int col, pos;

    col = ed_col - 1;
    while (col >= 0 &&
	   ed_data[ed_row][col] != ' ' &&
	   ed_data[ed_row][col] != '(' && ed_data[ed_row][col] != ')') {
	col--;
    }
    col++;
    pos = 0;
    while (ed_data[ed_row][col] != ' ' &&
	   ed_data[ed_row][col] != '(' && ed_data[ed_row][col] >= ' ') {
	str[pos] = ed_data[ed_row][col];
	col++;
	pos++;
    }
    str[pos] = NUL;
    return (str);
}

void find_candidate()
{
    char *str;

    str = get_fragment();
    ed_candidate_pt = 0;
    if (str[0] != NUL)
	gather_fuzzy_matches(str, ed_candidate, &ed_candidate_pt);
}

void replace_fragment(const char *newstr)
{
    char *oldstr;
    int m, n;

    oldstr = get_fragment();
    m = strlen(oldstr);
    n = strlen(newstr);
    while (m > 0) {
	backspace();
	m--;
    }
    while (n > 0) {
	insert_col();
	ed_data[ed_row][ed_col] = *newstr;
	ed_col++;
	ed_col1++;
	newstr++;
	n--;
    }
}

struct position find_word(const char *word)
{
    int i, j, k, len;
    struct position pos;
    const char *word1;

    i = ed_row;
    j = ed_col;
    word1 = word;
    len = strlen(word);
    while (i <= ed_end + 1) {
	while (j < COL_SIZE && ed_data[i][j] != NUL) {
	    k = j;
	    while (k < j + len && ed_data[i][k] == *word) {
		word++;
		k++;
	    }
	    if (k >= j + len) {
		pos.row = i;
		pos.col = j;
		return (pos);
	    }
	    j++;
	    word = word1;
	}
	i++;
	j = 0;
    }
    // can't find word
    pos.row = -1;
    pos.col = 0;
    return (pos);
}

struct position find_word_back(const char *word)
{
    int i, j, k, len;
    struct position pos;
    const char *word1;

    i = ed_row;
    j = ed_col;
    word1 = word;
    len = strlen(word);
    while (i >= 0) {
	while (j < COL_SIZE && ed_data[i][j] != NUL) {
	    k = j;
	    while (k < j + len && ed_data[i][k] == *word) {
		word++;
		k++;
	    }
	    if (k >= j + len) {
		pos.row = i;
		pos.col = j;
		return (pos);
	    }
	    j++;
	    word = word1;
	}
	i--;
	j = 0;
    }
    // can't find word
    pos.row = -1;
    pos.col = 0;
    return (pos);
}


void replace_word(const char *str1, const char *str2)
{
    int len1, len2, i, j;

    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 == len2) {
	for (i = 0; i < len1; i++) {
	    ed_data[ed_row][ed_col] = *str2;
	    ed_col++;
	    str2++;
	}
    } else if (len1 > len2) {
	i = ed_col + len1;
	j = len1 - len2;
	while (ed_data[ed_row][i] != NUL) {
	    ed_data[ed_row][i - j] = ed_data[ed_row][i];
	    i++;
	}
	ed_data[ed_row][i] = NUL;

	for (i = 0; i < len2; i++) {
	    ed_data[ed_row][ed_col + i] = *str2;
	    str2++;
	}
    } else {			// len1 < len2
	i = find_eol(ed_row);
	j = len2 - len1;
	while (i >= ed_col + len1) {
	    ed_data[ed_row][i + j] = ed_data[ed_row][i];
	    i--;
	}
	ed_data[ed_row][i] = NUL;
	for (i = 0; i < len2; i++) {
	    ed_data[ed_row][ed_col + i] = *str2;
	    str2++;
	}
    }
}

//-------------------help information----------------------------------

void information(void)
{
    int i;

    i = find_function_data(get_fragment());
    ESCMOVE(ed_footer, 1);
    ESCREV();
    clear_status();
    if (i != -1) {
	CHECK(addstr, functions_data[i + 1]);
	CHECK(addstr, "\n");
	ESCRST();
	CHECK(addstr, functions_data[i + 2]);
	CHECK(addstr, " --- enter any key to exit ---");
	CHECK(refresh);
	CHECK(getch);
	display_header();
	display_screen();
    } else {
	CHECK(addstr, "Can't fild");
	ESCRST();
    }
    ESCMOVE(ed_row + TOP_MARGIN - ed_start, ed_col1 + LEFT_MARGIN);
}

static const char *functions_data[] = {
    "basic-array-p",
    "(BASIC-ARRAY-P obj) boolean",
    "Check if obj is an array, string or vector",
    "general-array*p",
    "(GENERAL-ARRAY*-P obj) boolean",
    "Check if obj is a general-array",
    "aref",
    "(AREF basic-array z *) <object>",
    "Return the zth element of the basic-array",
    "garef",
    "(GAREF general-array z *) <object>",
    "Return the zth element of the general-array",
    "set-are",
    "(SET-AREF obj basic-array z *) <object>",
    "Set the zth element of the basic-array to obj",
    "set-gref",
    "(SET-GAREF obj general-array z *) <object>",
    "Set the zth element of the general-array to obj",
    "array-dimensions",
    "(ARRAY-DIMENSIONS basic-array) <list>",
    "Return a list of the dimensions of a basic-array",
    "characterp",
    "(CHARACTERP obj) boolean",
    "Check if obj is a string",
    "char=",
    "(CHAR= char1 char2) boolean",
    "Check if the characters char1 and char2 are equal",
    "char/=",
    "(CHAR/= char1 char2) boolean",
    "Check if the characters char1 and char2 are not equal",
    "char<",
    "(CHAR< char1 char2) boolean",
    "Check if the character code of char1 is less than char2",
    "char>",
    "(CHAR> char1 char2) boolean",
    "Check if the character code of char1 is greater than char2",
    "char<=",
    "(CHAR<= char1 char2) boolean",
    "Check if the character code of char1 is less than or equal to char2",
    "char>=",
    "(CHAR>= char1 char2) boolean",
    "Check if the character code of char1 is greater than or equal to char2",
    "error",
    "(error error-string obj *) <object>",
    "Signal an error",
    "cerror",
    "(cerror continue-string error-string obj *) <object>",
    "Signal a continuable error",
    "signal-condition",
    "(signal-condition condition continuable) <object>",
    "Signal a condition",
    "ignore-errors",
    "(ignore-errors form *) <object>",
    "Ignore errors (special form)",
    "report-condition",
    "(report-condition condition stream) <condition>",
    "Report the condition 'condition' to stream 'stream'",
    "condition-continuable",
    "(condition-continuable condition) <object>",
    "Check if a condition is continuable",
    "continue-condition",
    "(continue-condition condition value +) <object>",
    "Continue from a condition",
    "with-handler",
    "(with-handler handler form *) <object>",
    "Evaluate the handler and execute the form (special form)",
    "arithmetic-error-operation",
    "(arithmetic-error-operation arithmetic-error) <function>",
    "Return the operation of an arithmetic error",
    "arithmetic-error-operands",
    "(arithmetic-error-operands arithmetic-error) <list>",
    "Return the operands of an arithmetic error",
    "domain-error-object",
    "(domain-error-object domain-error) <object>",
    "Return the object supplied when creating the domain error 'domain-error'",
    "domain-error-expected-calss",
    "(domain-error-expected-class domain-error) <class>",
    "Domain error, return the desired domain supplied when creating 'domain-error'",
    "parse-error-string",
    "(parse-error-string parse-error) <string>",
    "Parsing error, return the string supplied when creating 'parse-error",
    "parse-error-expected-class",
    "(parse-error-expected-class parse-error) <class>",
    "Parsing error, return the desired class supplied when creating 'parse-error'",
    "simple-error-format-string",
    "(simple-error-format-string simple-error) <string>",
    "Return the string supplied when creating 'simple-error'",
    "simple-error-format-arguments",
    "(simple-error-format-arguments simple-error) <list>",
    "Return the list of arguments supplied when creating 'simple-error'",
    "stream-error-stream",
    "(stream-error-stream stream-error) <stream>",
    "Stream error, return the stream supplied when creating 'stream-error'",
    "undefined-entity-name",
    "(undefined-entity-name undefined-entity) <symbol>",
    "Return the symbol supplied when createing the undefined entity 'undefined-entity'",
    "undefined-entity-namespace",
    "(undefined-entity-namespace undefined-entity) <symbol>",
    "Return the namespace supplied when createing the undefined entity 'undefined-entity'",
    "quote",
    "(quote obj) <object>",
    "Return a reference to obj (special form)",
    "setq",
    "(setq var form) <object>",
    "Assign the result of evaluating 'form' to the variable 'var' (special form)",
    "set-dynamic",
    "(set-dynamic var form) <object>",
    "Assign the result of evaluating 'form' to the dynamic variable 'var' (special form)",
    "setf",
    "(setf place form) <object>",
    "Assign the result of evaluating 'form' to 'place' (special form)",
    "let",
    "(let ((var form) *) body-form *) <object>",
    "Define local variables and execute 'body-form ...' in that environment (special form)",
    "let*",
    "(let* ((var form) *) body-form *) <object>",
    "Similar to let, except that local variables are bound sequentially (special form)",
    "dynamic",
    "(dynamic var) <object>",
    "Return the binding of a dynamic variable (special form)",
    "setf",
    "(setf (dynamic var) form) <object>",
    "Assign a value to a dynamic variable (special form)",
    "dynamic-let",
    "(dynamic-let ((var form) *) body-form *) <object>",
    "Temporarily bind dynamic variables (special form)",
    "if",
    "(if test-form then-form else-form+) <object>",
    "Branch according to a condition (special form)",
    "cond",
    "(cond (test form *) *) <object>",
    "Branch according to a condition (special form)",
    "case",
    "(case keyform ((key *) form *) * (t form *)+) <object>",
    "Branches in various ways depending on the value of keyform (special form)",
    "case-using",
    "(case-using predform keyform ((key *) form *) * (t form *) +) <object>",
    "Almost the same as the case statement, but using the predicate function 'predform' for comparison (special form)",
    "progn",
    "(progn form*) <object>",
    "Perform sequential execution (special format)",
    "while",
    "(while test-form body-form *) <null>",
    "Execute body-form repeatedly as long as 'test-form' is not nil (special form)",
    "for",
    "(for (iteration-spec *) (end-test result *) form *) <object>",
    "Iterate repeatedly while end-test is not nil, using the initial values and steppers indicated by iteration-spec (special form)",
    "block",
    "(block name form *) <object>",
    "Execute sequentially with block tags (special format)",
    "return-from",
    "(return-from name result-form) transfers-control-and-data",
    "Exit the 'name' block (special form)",
    "catch",
    "(catch tag-form form *) <object>",
    "Catch tag-form and execute 'form ...' (special form)",
    "throw",
    "(throw tag-form result-form) transfers-control-and-data",
    "Throw tag-form (special form)",
    "tagbody",
    "(tagbody tagbody-tag * form *) <object>",
    "Execute sequentially with optional 'tagbody-tag' labels (special form)",
    "go",
    "(go tagbody-tag) transfers-control",
    "Transfer control to 'tagbody-tag' in a tagbody (special format)",
    "unwind-protect",
    "(unwind-protect form cleanup-form *) <object>",
    "Execute 'cleanup-form ...' whenever the evaluation of 'form' finishes (special form)",
    "the",
    "(THE class-name form) <object>",
    "Declare the class of the execution result of 'form' as class-name (special form)",
    "assure",
    "(ASSURE class-name form) <object>",
    "Claim the class of the execution result of 'form' as class-name, if it is different, an error will occur (special form)",
    "convert",
    "(CONVERT obj class-name) <object>",
    "Convert obj to class 'class-name' (special form)",
    "probe-file",
    "(probe-file filename) boolean",
    "Check if a file 'filename' exists",
    "file-position",
    "(file-position stream) <integer>",
    "Return the current file position of a stream",
    "set-file-position",
    "(set-file-position stream z) <integer>",
    "Set the file position of 'stream' to z",
    "file-length",
    "(file-length filename element-class) <integer>",
    "Return the size of the file 'filename' as an 'element-class' file",
    "functionp",
    "(functionp obj) boolean",
    "Check if obj is a function",
    "function",
    "(function function-name) <function>",
    "Returns a function named function-name (special form)",
    "lambda",
    "(lambda lambda-list form *) <function>",
    "Generate a lambda expression (special form)",
    "labels",
    "(labels ((function-name lambda-list form *) *) body-forms *) <object>",
    "Like 'flet', but binds local functions sequentially (recursive definition is possible) (special form)",
    "flet",
    "(flet ((function-name lambda-list form *) *) body-forms *) <object>",
    "Binds local functions (special form)",
    "apply",
    "(apply function obj * list) <object>",
    "Apply function",
    "funcall",
    "(funcall function obj *) <object>",
    "Call function",
    "defconstant",
    "(defconstant name form) <symbol>",
    "Define a constant (special form)",
    "defglobal",
    "(defglobal name form) <symbol>",
    "Define a global variable (special form)",
    "defdynamic",
    "(defdynamic name form) <symbol>",
    "Define a dynamic variable (special form)",
    "defun",
    "(defun function-name lambda-list form *) <symbol>",
    "Define a function (special form)",
    "read",
    "(read input-stream + eos-error-p + eos-value +) <object>",
    "Read an S-expression from 'input-stream'",
    "read-char",
    "(read-char input-stream + eos-error-p + eos-value +) <object>",
    "Read one character from 'input-stream'",
    "preview-char",
    "(preview-char input-stream + eos-error-p + eos-value +) <object>",
    "Returnsthe next character that will be read (one character look-ahead, file position does not change)",
    "read-line",
    "(read-line input-stream + eos-error-p + eos-value +) <object>",
    "Read one line as a string",
    "stream-ready-p",
    "(stream-ready-p input-stream) boolean",
    "Is the stream readable?",
    "format",
    "(format output-stream format-string obj *) <null>",
    "Output obj according to format-string",
    "format-char",
    "(format-char output-stream char) <null>",
    "Output one character",
    "format-float",
    "(format-float output-stream float) <null>",
    "Output as a floating point number",
    "format-fresh-line",
    "(format-fresh-line output-stream) <null>",
    "Begin on a new line",
    "format-integer",
    "(format-integer output-stream integer radix) <null>",
    "Output as an integer",
    "format-object",
    "(format-object output-stream obj escape-p) <null>",
    "Output as an object",
    "format-tab",
    "(format-tab output-stream column) <null>",
    "Output ASCII TAB",
    "read-byte",
    "(read-byte input-stream eos-error-p + eos-value +) <integer>",
    "Read as a byte",
    "write",
    "(write-byte z output-stream) <integer>",
    "Write as a byte",
    "consp",
    "(CONSP obj) boolean",
    "Check if obj is a cons",
    "cons",
    "(CONS obj1 obj2) <cons>",
    "Generate a cons",
    "car",
    "(CAR cons) <object>",
    "Return the Car part of a cons",
    "cdr",
    "(CDR cons) <object>",
    "Return the Cdr part of a cons",
    "set-car",
    "(SET-CAR obj cons) <object>",
    "Set the Car part of a cons",
    "set-cdr",
    "(SET-CDR obj cons) <object>",
    "Set the Cdr part of a cons",
    "null",
    "(NULL obj) boolean",
    "Check if obj is null",
    "listp",
    "(LISTP obj) boolean",
    "Check if obj is a list",
    "create-list",
    "(CREATE-LIST i initial-element +) <list>",
    "Generates a list with length i and initial values 'initial-element'",
    "list",
    "(LIST obj *) <list>",
    "Generate a list with every element set to obj",
    "reverse",
    "(REVERSE list) <list>",
    "Reverse the list (do not destroy the original list)",
    "nreverse",
    "(NREVERSE list) <list>",
    "Reverse the list (the original list is destroyed)",
    "append",
    "(APPEND list *) <list>",
    "Concatenate lists",
    "member",
    "(MEMBER obj list) <list>",
    "If the list list contains obj, it returns a partial list starting with obj",
    "mapcar",
    "(MAPCAR function list +) <list>",
    "Execute the function function on the elements of list 'list' and return a list of results",
    "mapc",
    "(MAPC function list +) <list>",
    "Execute the function function on the elements of list 'list' and return the 'list' argument",
    "mapcan",
    "(MAPCAN function list +) <list>",
    "Like 'mapcar', but the list is destroyed",
    "maplist",
    "(MAPLIST function list +) <list>",
    "Execute 'function' on a part of 'list' and return a list of results",
    "mapl",
    "(MAPL function list +) <list>",
    "Executes the 'function' on a part of 'list' and return the 'list' argument",
    "mapcon",
    "(MAPCON function list +) <list>",
    "Like 'maplist', but the list is destroyed",
    "assoc",
    "(ASSOC obj association-list) <cons>",
    "Return an obj-keyed value from association-list",
    "defmacro",
    "(defmacro macro-name lambda-list form *) <symbol>",
    "Define a macro (special form)",
    "identity",
    "(IDENTITY obj) <object>",
    "Return obj as is",
    "get-universal-time",
    "(GET-UNIVERSAL-TIME) <integer>",
    "Returns universal time (seconds)",
    "get-internal-run-time",
    "(GET-INTERNAL-RUN-TIME) <integer>",
    "Return the execution time",
    "get-internal-real-time",
    "(GET-INTERNAL-REAL-TIME) <integer>",
    "Return elapsed time",
    "internal-time-units-per-second",
    "(internal-time-units-per-second) <integer>",
    "Return internal time units per second",
    "numberp",
    "(NUMBERP obj) boolean",
    "Test if 'obj' is a number",
    "parse-number",
    "(PARSE-NUMBER string) <number>",
    "Parse the string 'string' and convert it into a number",
    "=",
    "(= x1 x2) boolean",
    "Test if two numeric values are equal",
    "/=",
    "(/= x1 x2) boolean",
    "Test if two numeric values are not equal",
    ">=",
    "(>= x1 x2) boolean",
    "Test if numeric value 'x1' is greater than or equal to 'x2'",
    "<=",
    "(<= x1 x2) boolean",
    "Test if numeric value 'x1' is less than or equal to 'x2'",
    ">",
    "(> x1 x2) boolean",
    "Test if numeric value 'x1' is greater than 'x2'",
    "<",
    "(< x1 x2) boolean",
    "Test if numeric value 'x1' is less than 'x2'",
    "+",
    "(+ x *) <number>",
    "Sum of the numbers 'x ...'",
    "*",
    "(* x *) <number>",
    "Product of the numbers 'x ...'",
    "-",
    "(- x y *) <number>",
    "Successive subtraction of 'x y ...'",
    "quotient",
    "(QUOTIENT dividend divisor +) <number>",
    "Successive division of 'dividend' by 'divisor ...'",
    "reciprocal",
    "(RECIPROCAL x) <number>",
    "Return 1/x",
    "max",
    "(MAX x y *) <number>",
    "Return the maximum of 'x y ...'",
    "min",
    "(MIN x y *) <number>",
    "Return the minimum of 'x y ...'",
    "abs",
    "(ABS x) <number>",
    "Return the absolute value of 'x'",
    "exp",
    "(EXP x) <number>",
    "Return e^x",
    "log",
    "(LOG x) <number>",
    "Return the natural logarithm of x",
    "expt",
    "(EXPT x1 x2) <number>",
    "Return x1 to the power of x2",
    "sqrt",
    "(SQRT x) <number>",
    "Return the positive square root of x",
    "sin",
    "(SIN x) <number>",
    "Return the sine of x",
    "cos",
    "(COS x) <number>",
    "Return the cosine of x",
    "tan",
    "(TAN x) <number>",
    "Return the tangent of x",
    "atan",
    "(ATAN x) <number>",
    "Return the arctangent of x",
    "atan2",
    "(ATAN2 x1 x2) <number>",
    "Convert from rectangular coordinates (x1, x2) to the angle part of a polar coordinate",
    "sinh",
    "(SINH x) <number>",
    "Return the hyperbolic sine of x",
    "cosh",
    "(COSH x) <number>",
    "Return the hyperbolic cosine of x",
    "tanh",
    "(TANH x) <number>",
    "Return the hyperbolic tangent of x",
    "atanh",
    "(ATANH x) <number>",
    "Return the hyperbolic tangent of x",
    "floatp",
    "(FLOATP obj) boolean",
    "Test if 'obj' is a floating-point number",
    "float",
    "(FLOAT x) <float>",
    "Convert 'x' to a floating-point number",
    "floor",
    "(FLOOR x) <integer>",
    "Truncation towards negative infinity",
    "ceiling",
    "(CEILING x) <integer>",
    "Truncation towards positive infinity",
    "truncate",
    "(TRUNCATE x) <integer>",
    "Truncation towards 0",
    "round",
    "(ROUND x) <integer>",
    "Round to integer nearest 'x'",
    "integerp",
    "(INTEGERP obj) boolean",
    "Check if 'obj' is an integer",
    "div",
    "(DIV z1 z2) <integer>",
    "Integer division",
    "mod",
    "(MOD z1 z2) <integer>",
    "Modulus",
    "gcd",
    "(GCD z1 z2) <integer>",
    "'Greatest Common Divisor' or 'Highest Common Factor'",
    "lcm",
    "(LCM z1 z2) <integer>",
    "'Lowest Common Multiple'",
    "isqrt",
    "(ISQRT z) <integer>",
    "Integer square root, i.e. greatest integer <= '(sqrt z)'",
    "defclass",
    "(defclass class-name (sc-name *) (slot-spec *) class-opt *) <symbol>",
    "Define a class (special form)",
    "generic-function-p",
    "(generic-function-p obj) boolean",
    "Test of 'obj' is a generic function",
    "defgeneric",
    "(defgeneric func-spec lambda-list option * method-desc *) <symbol>",
    "Define a generic function (special form)",
    "defmethod",
    "(defmethod func-spec method-qualifier * parameter-profile form *) <symbol>",
    "Define a method (special form)",
    "call-next-method",
    "(call-next-method) <object>",
    "Call the next method in a class's precedence order (special form)",
    "next-method-p",
    "(next-method-p) boolean",
    "Test if a next method exists (special form)",
    "create-class",
    "(create class initarg * initval *) <object>",
    "Create an instance of a class (generic function)",
    "initialize-object",
    "(initialize-object instance initialization-list) <object>",
    "Initialize an object",
    "class-of",
    "(class-of obj) <class>",
    "Return the class of an object",
    "instancep",
    "(instancep obj class) boolean",
    "Test whether 'obj' is an instance of 'class'",
    "subclassp",
    "(subclassp class1 class2) boolean",
    "Test for a subclass relation",
    "class",
    "(class class-name) <class>",
    "Return the class named 'class-name' (special form)",
    "eq",
    "(EQ obj1 obj2) boolean",
    "Test whether obj1 and obj2 are 'eq'",
    "eql",
    "(EQL obj1 obj2) boolean",
    "Test whether obj1 and obj2 are 'eql'",
    "equal",
    "(EQUAL obj1 obj2) boolean",
    "Test whether obj1 and obj2 are 'equal'",
    "not",
    "(NOT obj) boolean",
    "Return the logical NOT of 'obj'",
    "and",
    "(AND form *) <object>",
    "Logical AND of the forms 'form ...' (special form)",
    "or",
    "(OR form *) <object>",
    "logical OR of the forms 'form ...' (special form)",
    "length",
    "(LENGTH sequence) <integer>",
    "Return the length of 'sequence'",
    "elt",
    "(ELT sequence z) <object>",
    "Return element no. 'z' of 'sequence'",
    "set-elt",
    "(SET-ELT obj sequence z) <object>",
    "Set item 'z' of 'sequence' to 'obj'",
    "subseq",
    "(SUBSEQ sequence z1 z2) sequence",
    "Get the portion of 'sequence' from indexes z1 to z2",
    "map-into",
    "(MAP-INTO destination function seq *) sequenc",
    "Apply 'function' to the elements of 'sequence' in turn, then store the results in 'destination'",
    "streamp",
    "(streamp obj) boolean",
    "Predicate that is true for streams",
    "open-stream-p",
    "(open-stream-p obj) boolean",
    "Predicate is true for open streams",
    "input-stream-p",
    "(input-stream-p obj) boolean",
    "Predicate that is true for input streams",
    "output-stream-p",
    "(output-stream-p obj) boolean",
    "Predicate that is true for output streams",
    "standard-input",
    "(standard-input) <stream>",
    "Return the standard input stream",
    "standard-output",
    "(standard-output) <stream>",
    "Return the standard output stream",
    "error-output",
    "(error-output) <stream>",
    "Return the standard error stream",
    "with-standard-input",
    "(with-standard-input stream-form form *) <object>",
    "Evaluate the forms form ... with standard-output set to the result of 'steram-form' (special form)",
    "with-standard-output",
    "(with-standard-output stream-form form *) <object>",
    "Evaluate the forms form ... with standard-output set to the result of 'steram-form' (special form)",
    "with-error-output",
    "(with-error-output stream-form form *) <object>",
    "Evaluate the forms form ... with standard-error set to the result of 'stream-form' (special form)",
    "open-input-file",
    "(open-input-file filename element-class +) <stream>",
    "Open the file 'filename' as an input stream",
    "open-output-file",
    "(open-output-file filename element-class +) <stream>",
    "Open the file 'filename' as an output stream",
    "open-io-file",
    "(open-io-file filename element-class +) <stream>",
    "Open the file 'filename' for as an input/output stream",
    "with-open-input-file",
    "(with-open-input-file (name file element-class +) form *) <object>",
    "Evaluate 'form' with standard-input redirected from 'file' and afterwards close it (special form)",
    "with-open-output-file",
    "(with-open-output-file (name file element-class +) form *) <object>",
    "Evaluate 'form' with standard-output redirected to 'file' and afterwards close it (special form)",
    "with-open-io-file",
    "(with-open-io-file (name file element-class +) form *) <object>",
    "Evaluate 'form' with both standard-input and standard-output streams redirected to/from 'file' and afterwards close it (special form)",
    "close",
    "(close stream) implementation-defined",
    "Close a stream",
    "create-string-input-stream",
    "(create-string-input-stream string) <stream>",
    "Create a string input stream",
    "create-string-output-stream",
    "(create-string-output-stream) <stream>",
    "Create a string output stream",
    "get-output-stream-string",
    "(get-output-stream-string stream) <string>",
    "Return a string containing the output that was sent to a string output stream",
    "stringp",
    "(STRINGP obj) boolean",
    "Predicate that is true for strings",
    "create-string",
    "(CREATE-STRING i initial-element+) <string>",
    "Create a string of length 'i' filled with 'initial-element'",
    "string=",
    "(STRING= string1 string2) quasi-boolean",
    "Are two strings equal?",
    "string/=",
    "(STRING/= string1 string2) quasi-boolean",
    "Are two strings not equal?",
    "string<",
    "(STRING< string1 string2) quasi-boolean",
    "Is 'string1' before 'string2' in sort order?",
    "string>",
    "(STRING> string1 string2) quasi-boolean",
    "Is 'string1' after 'string2' in sort order?",
    "string>=",
    "(STRING>= string1 string2) quasi-boolean",
    "Is 'string1' after or equal to 'string2' in sort order?",
    "string<=",
    "(STRING<= string1 string2) quasi-boolean",
    "Is 'string1' before or equal to 'string2' in sort order?",
    "char-index",
    "(CHAR-INDEX character string start-position +) <object>",
    "Return the position where 'character' occurs in 'string'",
    "string-index",
    "(STRING-INDEX substring string start-position +) <object>",
    "Return the position where 'substring' occurs in 'string'",
    "string-append",
    "(STRING-APPEND string *) <string>",
    "Concatenate the strings string ...",
    "symbolp",
    "(SYMBOLP obj) boolean",
    "Predicate that is true for <symbol> objects",
    "property",
    "(PROPERTY symbol property-name obj +) <object>",
    "Return a property of a symbol",
    "set-property",
    "(SET-PROPERTY obj symbol property-name) <object>",
    "Set a property of a symbol",
    "remove-property",
    "(REMOVE-PROPERTY symbol property-name) <object>",
    "Remove a property from a symbol",
    "gensym",
    "(GENSYM) <symbol>",
    "Create an anonymous symbol",
    "basic-vector-p",
    "(BASIC-VECTOR-P obj) boolean",
    "Predicate that is true for <basic-vector> objects",
    "general-vector-p",
    "(GENERAL-VECTOR-P obj) boolean",
    "Predicate that is true for <general-vector> objects",
    "create-vector",
    "(CREATE-VECTOR i initial-element +) <general-vector>",
    "Create a vector of length 'i', with each element initialised to 'initial-element'",
    "vector",
    "(VECTOR obj *) <general-vector>",
    "Create a vector from the elements obj ...",
    "load",
    "(load file) T",
    "Load 'file' (extension)",
    "time",
    "(time form) <object>",
    "Show the time to evaluate 'form' (special form) (extension)",
    "eval",
    "(eval form) <object>",
    "Evaluate 'form' (extension)",
    "compile-file",
    "(compile-file file) boolean",
    "Compile 'file' (extension)",
    "gbc",
    "(gbc) <null>",
    "Force garbage collection (extension)",
    "quit",
    "(quit) transfers-control",
    "Exit the ISLisp interpreter (extension)",
};

#define NELEM(X) (sizeof(X) / sizeof((X)[0]))

int find_function_data(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(functions_data); i = i + 3) {
	if (strcmp(functions_data[i], str) == 0) {
	    return i;
	}
    }
    return -1;
}
