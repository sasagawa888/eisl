#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include "eisl.h"
#include "fmt.h"
#include "except.h"
#include "str.h"
#include "mem.h"

#define TOKEN_MAX 80
#define FRAGMENT_MAX 20

#ifndef CTRL
#define CTRL(X) ((X) & 0x1F)
#endif

bool read_line_loop(int c, int *j, int *uni_j, int *pos, int limit,
		    int *rl_line);

int f_edit(int arglist, int th)
{
    int arg1, res;

    arg1 = car(arglist);
    if (length(arglist) != 1)
	error(WRONG_ARGS, "edit", arglist, th);
    char *ed;
    if ((ed = getenv("VISUAL")) == NULL) {
	if ((ed = getenv("EDITOR")) == NULL) {
	    ed = "edlis";
	}
    }
    char *str = Str_catv(ed, 1, 0, " ", 1, 0, GET_NAME(arg1), 1, 0, NULL);
    res = system(str);
    FREE(str);
    if (res == -1)
	error(SYSTEM_ERR, "edit", arg1, th);
    f_load(arglist, 0);
    return (T);
}

void setcolor(short n)
{
    putp(tparm(set_a_foreground, n));
}

int eisl_getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// ------------REPL read-line-----------------
void display_buffer()
{
    int col;

    ESCMVLEFT(3);
    ESCCLSL();
    col = 0;

    while (buffer[col][0] != EOL && buffer[col][0] != NUL) {

	if (ed_incomment != -1 && line >= ed_incomment) {
	    // comment                                       
	    // #|...|#
	    ESCBOLD();
	    setcolor(ed_comment_color);
	    while (buffer[col][0] != EOL && buffer[col][0] != NUL) {
		putchar(buffer[col][0]);
		col++;
		if (buffer[col - 2][0] == '|' && buffer[col - 1][0] == '#') {
		    ed_incomment = -1;
		    ESCRST();
		    ESCFORG();
		    break;
		}
	    }
	    ESCRST();
	    ESCFORG();
	} else if (buffer[col][0] == ' ' ||
		   buffer[col][0] == '(' || buffer[col][0] == ')') {
	    putchar(buffer[col][0]);
	    col++;
	} else {
	    switch (check_token_buffer(col)) {
	    case HIGHLIGHT_SYNTAX:
		ESCBOLD();
		setcolor(ed_syntax_color);
		while (buffer[col][0] != ' ' &&
		       buffer[col][0] != '(' &&
		       buffer[col][0] != ')' &&
		       buffer[col][0] != NUL && buffer[col][0] != EOL) {
		    putchar(buffer[col][0]);
		    col++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_BUILTIN:
		ESCBOLD();
		setcolor(ed_builtin_color);
		while (buffer[col][0] != ' ' &&
		       buffer[col][0] != '(' &&
		       buffer[col][0] != ')' &&
		       buffer[col][0] != NUL && buffer[col][0] != EOL) {
		    putchar(buffer[col][0]);
		    col++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_STRING:
		ESCBOLD();
		setcolor(ed_string_color);
		putchar(buffer[col][0]);
		col++;
		while (buffer[col][0] != NUL && buffer[col][0] != EOL) {
		    putchar(buffer[col][0]);
		    col++;
		    if (buffer[col - 1][0] == '"'
			&& buffer[col - 2][0] != '\\')
			break;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_COMMENT:
		ESCBOLD();
		setcolor(ed_comment_color);
		while (buffer[col][0] != NUL && buffer[col][0] != EOL) {
		    putchar(buffer[col][0]);
		    col++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_EXTENDED:
		ESCBOLD();
		setcolor(ed_extended_color);
		while (buffer[col][0] != ' ' &&
		       buffer[col][0] != '(' &&
		       buffer[col][0] != ')' &&
		       buffer[col][0] != NUL && buffer[col][0] != EOL) {
		    putchar(buffer[col][0]);
		    col++;
		}
		ESCRST();
		ESCFORG();
		break;
	    case HIGHLIGHT_MULTILINE_COMMENT:
		ESCBOLD();
		setcolor(ed_comment_color);
		ed_incomment = line;
		while (buffer[col][0] != EOL && buffer[col][0] != NUL) {
		    putchar(buffer[col][0]);
		    col++;
		    if (buffer[col - 2][0] == '|'
			&& buffer[col - 1][0] == '#') {
			ed_incomment = -1;
			ESCRST();
			ESCFORG();
			break;
		    }
		}
		break;
	    default:
		while (buffer[col][0] != ' ' &&
		       buffer[col][0] != '(' &&
		       buffer[col][0] != ')' &&
		       buffer[col][0] != NUL && buffer[col][0] != EOL) {
		    putchar(buffer[col][0]);
		    col++;
		}
	    }
	}
    }
    ESCRST();
    return;
}


enum HighlightToken check_token_buffer(int col)
{
    char str[TOKEN_MAX + 1];
    int pos;

    pos = 0;
    if (buffer[col][0] == '"')
	return HIGHLIGHT_STRING;
    else if (buffer[col][0] == ';')
	return HIGHLIGHT_COMMENT;
    while (buffer[col][0] != ' ' &&
	   buffer[col][0] != '(' &&
	   buffer[col][0] != ')' &&
	   buffer[col][0] != NUL && buffer[col][0] != EOL
	   && pos < TOKEN_MAX) {
	str[pos] = buffer[col][0];
	col++;
	pos++;
    }
    str[pos] = NUL;
    if (str[0] == '#' && str[1] == '|')
	return HIGHLIGHT_MULTILINE_COMMENT;	// #|...|#
    if (pos == 0)
	return HIGHLIGHT_NONE;
    return maybe_match(str);
}


int find_lparen_buffer(int col)
{
    int nest, uni_col, i;

    REQUIRE(col <= COL_SIZE);
    col--;
    nest = 0;
    while (col >= 0) {
	if (buffer[col][0] == '(' && nest == 0)
	    break;
	else if (buffer[col][0] == ')')
	    nest++;
	else if (buffer[col][0] == '(')
	    nest--;

	col--;
    }
    uni_col = 0;
    for (i = 0; i < col; i++) {
	if (isUni1(buffer[i][0]))
	    uni_col++;
	else if (isUni3(buffer[i][0])) {
	    uni_col++;
	    uni_col++;
	} else if (isUni2(buffer[i][0]) || isUni4(buffer[i][0]) ||
		   isUni5(buffer[i][0]) || isUni6(buffer[i][0])) {
	    uni_col++;
	}
    }
    return (uni_col);
}

int find_rparen_buffer(int col)
{
    int nest, limit, uni_col, i;

    col++;
    nest = 0;
    for (limit = 0; limit <= COL_SIZE; limit++)
	if (buffer[limit][0] == 0)
	    break;

    while (col <= limit) {
	if (buffer[col][0] == ')' && nest == 0)
	    break;
	else if (buffer[col][0] == '(')
	    nest++;
	else if (buffer[col][0] == ')')
	    nest--;

	col++;
    }
    uni_col = 0;
    for (i = 0; i < col; i++) {
	if (isUni1(buffer[i][0]))
	    uni_col++;
	else if (isUni3(buffer[i][0])) {
	    uni_col++;
	    uni_col++;
	} else if (isUni2(buffer[i][0]) || isUni3(buffer[i][0])
		   || isUni4(buffer[i][0]) || isUni5(buffer[i][0])
		   || isUni6(buffer[i][0])) {
	    uni_col++;
	}
    }
    if (col > limit)
	return (-1);
    else
	return (uni_col);
}

void emphasis_rparen_buffer(int col, int uni_col)
{
    int uni_pos;

    if (buffer[col][0] != '(')
	return;
    uni_pos = find_rparen_buffer(col);
    if (uni_pos < 0)
	return;

    ESCMVLEFT(uni_col + 3);
    ESCBCYAN();
    putchar('(');
    ESCBORG();
    ESCMVLEFT(uni_pos + 3);
    ESCBCYAN();
    putchar(')');
    ESCBORG();
    ed_rparen_col = uni_pos;
    ed_lparen_col = uni_col;
    ESCMVLEFT(uni_col + 3);
}


void emphasis_lparen_buffer(int col, int uni_col)
{
    int uni_pos;

    if (buffer[col][0] != ')')
	return;

    uni_pos = find_lparen_buffer(col);
    if (uni_pos < 0)
	return;

    ESCMVLEFT(uni_col + 3);
    ESCBCYAN();
    putchar(')');
    ESCBORG();
    ESCMVLEFT(uni_pos + 3);
    ESCBCYAN();
    putchar('(');
    ESCBORG();
    ed_rparen_col = uni_col;
    ed_lparen_col = uni_pos;
    ESCMVLEFT(uni_col + 3);
}


void reset_paren_buffer()
{
    ed_lparen_col = -1;
    ed_rparen_col = -1;
}

void restore_paren_buffer(int col)
{

    if (ed_lparen_col != -1) {
	ESCMVLEFT(ed_lparen_col + 3);
	ESCBORG();
	putchar('(');
	ed_lparen_col = -1;
    }
    if (ed_rparen_col != -1) {
	ESCMVLEFT(ed_rparen_col + 3);
	ESCBORG();
	putchar(')');
	ed_rparen_col = -1;
    }
    ESCMVLEFT(col + 3);
}


char *get_fragment_buffer(int col)
{
    static char str[FRAGMENT_MAX];
    int pos;

    REQUIRE(col <= COL_SIZE);
    while (col >= 0 &&
	   buffer[col][0] != ' ' &&
	   buffer[col][0] != '(' && buffer[col][0] != ')') {
	col--;
    }
    col++;
    pos = 0;
    while (buffer[col][0] != ' ' &&
	   buffer[col][0] != '(' && buffer[col][0] >= ' ') {
	str[pos] = buffer[col][0];
	col++;
	pos++;
    }
    str[pos] = NUL;
    return (str);
}


void find_candidate_buffer(int col)
{
    char *str;

    str = get_fragment_buffer(col);
    ed_candidate_pt = 0;
    if (str[0] != NUL)
	gather_fuzzy_matches(str, ed_candidate, &ed_candidate_pt);
}

int replace_fragment_buffer(const char *newstr, int col)
{
    char *oldstr;
    int m, n;

    oldstr = get_fragment_buffer(col);
    m = strlen(oldstr);
    n = strlen(newstr);
    col--;
    while (m > 0) {
	backspace_buffer(col);
	m--;
	col--;
    }
    col++;
    while (n > 0) {
	insertcol_buffer(col);
	buffer[col][0] = *newstr;
	col++;
	newstr++;
	n--;
    }

    return (col);
}

void backspace_buffer(int col)
{
    int i;

    for (i = col; i < COL_SIZE; i++)
	buffer[i][0] = buffer[i + 1][0];
    buffer[COL_SIZE][0] = 0;
}

void insertcol_buffer(int col)
{
    int i;

    for (i = COL_SIZE; i > col; i--)
	buffer[i][0] = buffer[i - 1][0];
}

static void right(int *j, int *uni_j)
{
    int c;

    if (buffer[*j][0] == 0 || buffer[*j][0] == EOL) {
	return;
    }

    c = buffer[*j][0];
    if (isUni1(c)) {
	(*j)++;
	(*uni_j)++;
    } else {
	(*j)++;
	c = buffer[*j][0];
	while (isUniRest(c)) {
	    (*j)++;
	    c = buffer[*j][0];
	}
	if (isUni3(c)) {
	    (*uni_j)++;
	    (*uni_j)++;
	} else {
	    (*uni_j)++;
	}
    }
    restore_paren_buffer(*uni_j);
    emphasis_lparen_buffer(*j, *uni_j);
    emphasis_rparen_buffer(*j, *uni_j);
    ESCMVLEFT(*uni_j + 3);
}

static void left(int *j, int *uni_j)
{
    int c;

    if (*j <= 0)
	return;
    (*j)--;
    c = buffer[*j][0];
    if (isUni1(c)) {
	(*uni_j)--;
    } else {
	while (isUniRest(c)) {
	    (*j)--;
	    c = buffer[*j][0];
	}
	if (isUni3(c)) {
	    (*uni_j)--;
	    (*uni_j)--;
	} else {
	    (*uni_j)--;
	}
    }

    restore_paren_buffer(*uni_j);
    emphasis_lparen_buffer(*j, *uni_j);
    emphasis_rparen_buffer(*j, *uni_j);
    ESCMVLEFT(*uni_j + 3);
}

int read_line(int flag)
{
    int j,			// colums position of buffer 
     uni_j,			// column position of display
     rl_line;

    static int pos = 0;

    if (flag == -1) {
	pos--;
	return (-1);
    }

    if (buffer[pos][0] == 0) {
	int c, i;
	static int limit = 0;

	for (i = 9; i > 0; i--)
	    for (j = 0; j <= COL_SIZE; j++)
		buffer[j][i] = buffer[j][i - 1];

	limit++;
	if (limit >= 10)
	    limit = 9;

	for (j = 0; j <= COL_SIZE; j++)
	    buffer[j][0] = 0;

	rl_line = 0;
	ed_lparen_col = -1;
	ed_rparen_col = -1;
	j = 0;
	uni_j = 0;
	c = eisl_getch();
	while (!read_line_loop(c, &j, &uni_j, &pos, limit, &rl_line)) {
	    c = eisl_getch();
	}
    }
    return (buffer[pos++][0]);
}

// for Multi-process 
// input from stdin with pipe
//
int read_stdin(void)
{
    int j;			// colums position of buffer 
    static int pos = 0;

    // when buffer is empty buffering from stdin
    if (buffer2[pos] == 0) {
	int c;

	// clear buffer
	for (j = 0; j <= COL_SIZE; j++)
	    buffer2[j] = 0;

	// add data from stdin until get null(0) code
	j = 0;

	// wait until get not null data
      loop:
	c = getc(stdin);
	if (c == 0)
	    goto loop;
	while (c != 0) {
	    buffer2[j] = c;
	    c = getc(stdin);
	    j++;
	}
	buffer2[j] = 0;
	pos = 0;
    }
    return (buffer2[pos++]);
}

bool check_balance(void)
{
    int col, paren, quote;

    col = paren = quote = 0;

    while (buffer[col][0] != 0) {
	if (buffer[col][0] == '(')
	    paren++;
	else if (buffer[col][0] == ')')
	    paren--;
	else if (col == 0 && buffer[col][0] == '"')
	    quote++;
	else if (col > 0 && buffer[col][0] == '"'
		 && buffer[col - 1][0] != '\\')
	    quote++;

	col++;
    }

    if (paren == 0 && quote % 2 == 0)
	return true;

    return false;
}

void up(int limit, int *rl_line, int *j, int *uni_j, int *pos)
{
    if (limit <= 1)
	return;
    if (*rl_line >= limit - 1)
	*rl_line = limit - 2;
    for (*j = 0; *j <= COL_SIZE; (*j)++) {
	buffer[*j][0] = buffer[*j][*rl_line + 1];
    }
    *uni_j = 0;
    for (*j = 0; *j <= COL_SIZE; (*j)++) {
	if (buffer[*j][0] == EOL)
	    break;
	if (isUni1(buffer[*j][0]))
	    (*uni_j)++;
	else if (isUni3(buffer[*j][0])) {
	    (*uni_j)++;
	    (*uni_j)++;
	} else if (isUni2(buffer[*j][0]) || isUni4(buffer[*j][0]) ||
		   isUni5(buffer[*j][0]) || isUni6(buffer[*j][0])) {
	    (*uni_j)++;
	}
    }

    (*rl_line)++;
    *pos = 0;
    ed_rparen_col = -1;
    ed_lparen_col = -1;
    display_buffer();
}

void down(int *rl_line, int *j, int *uni_j, int *pos)
{
    if (*rl_line <= 1)
	*rl_line = 1;
    for (*j = 0; *j <= COL_SIZE; (*j)++) {
	buffer[*j][0] = buffer[*j][*rl_line - 1];
    }
    *uni_j = 0;
    for (*j = 0; *j <= COL_SIZE; (*j)++) {
	if (buffer[*j][0] == EOL)
	    break;
	if (isUni1(buffer[*j][0]))
	    (*uni_j)++;
	else if (isUni3(buffer[*j][0])) {
	    (*uni_j)++;
	    (*uni_j)++;
	} else if (isUni2(buffer[*j][0]) || isUni4(buffer[*j][0]) ||
		   isUni5(buffer[*j][0]) || isUni6(buffer[*j][0])) {
	    (*uni_j)++;
	}
    }

    (*rl_line)--;
    *pos = 0;
    ed_rparen_col = -1;
    ed_lparen_col = -1;
    display_buffer();
}

static int unipos(const int *j)
{
    int k, uni_pos;

    uni_pos = 0;
    for (k = 0; k < (*j); k++) {
	if (isUni1(buffer[k][0])) {
	    uni_pos++;
	} else if (isUni3(buffer[k][0])) {
	    uni_pos++;
	    uni_pos++;
	} else if (isUni2(buffer[k][0]) || isUni4(buffer[k][0]) ||
		   isUni5(buffer[k][0]) || isUni6(buffer[k][0])) {
	    uni_pos++;
	}
    }
    return (uni_pos);
}

bool
read_line_loop(int c, int *j, int *uni_j, int *pos, int limit,
	       int *rl_line)
{
    int k;

    switch (c) {
    case CTRL('M'):
    case EOL:
	if (!check_balance()) {
	    printf("\n() \"\" unbalance --- enter any key ---");
	    eisl_getch();
	    ESCMVLEFT(1);
	    ESCCLSL();
	    ESCMVU();
	    ESCMVLEFT(3);
	    display_buffer();
	    ESCMVLEFT(*j + 3);
	    restore_paren_buffer(*j);
	    return false;
	}
	for (*j = 0; *j <= COL_SIZE; (*j)++)
	    if (buffer[*j][0] == 0) {
		buffer[*j][0] = c;
		break;
	    }
	restore_paren_buffer(*j);
	putchar(c);
	*pos = 0;
	return true;
    case CTRL('H'):
    case DEL:
	if (*j <= 0)
	    break;
	(*j)--;

	if (isUni1(buffer[(*j)][0])) {
	    (*uni_j)--;
	    for (k = *j; k < COL_SIZE; k++)
		buffer[k][0] = buffer[k + 1][0];
	} else {
	    c = buffer[(*j)][0];
	    while (isUniRest(c)) {
		(*j)--;
		c = buffer[(*j)][0];
	    }
	    if (isUni2(c)) {
		(*uni_j)--;
		for (k = *j; k < COL_SIZE - 2; k++)
		    buffer[k][0] = buffer[k + 2][0];
	    } else if (isUni3(c)) {
		(*uni_j)--;
		(*uni_j)--;
		for (k = *j; k < COL_SIZE - 3; k++)
		    buffer[k][0] = buffer[k + 3][0];
	    } else if (isUni4(c)) {
		(*uni_j)--;
		for (k = *j; k < COL_SIZE - 4; k++)
		    buffer[k][0] = buffer[k + 4][0];
	    } else if (isUni5(c)) {
		(*uni_j)--;
		for (k = *j; k < COL_SIZE - 5; k++)
		    buffer[k][0] = buffer[k + 5][0];
	    } else if (isUni6(c)) {
		(*uni_j)--;
		for (k = *j; k < COL_SIZE - 6; k++)
		    buffer[k][0] = buffer[k + 6][0];
	    }
	}

	display_buffer();
	ESCMVLEFT(*uni_j + 3);
	if (ed_rparen_col > *j)
	    ed_rparen_col--;
	if (ed_lparen_col > *j)
	    ed_lparen_col--;
	break;
    case CTRL('D'):
	if (isUni1(buffer[(*j)][0])) {
	    for (k = *j; k < COL_SIZE; k++)
		buffer[k][0] = buffer[k + 1][0];
	} else if (isUni2(buffer[(*j)][0])) {
	    for (k = *j; k < COL_SIZE - 2; k++)
		buffer[k][0] = buffer[k + 2][0];
	} else if (isUni3(buffer[(*j)][0])) {
	    for (k = *j; k < COL_SIZE - 3; k++)
		buffer[k][0] = buffer[k + 3][0];
	} else if (isUni4(buffer[(*j)][0])) {
	    for (k = *j; k < COL_SIZE - 4; k++)
		buffer[k][0] = buffer[k + 4][0];
	} else if (isUni5(buffer[(*j)][0])) {
	    for (k = *j; k < COL_SIZE - 5; k++)
		buffer[k][0] = buffer[k + 5][0];
	} else if (isUni6(buffer[(*j)][0])) {
	    for (k = *j; k < COL_SIZE - 6; k++)
		buffer[k][0] = buffer[k + 6][0];
	}
	display_buffer();
	ESCMVLEFT(*uni_j + 3);
	if (ed_rparen_col > *j)
	    ed_rparen_col--;
	if (ed_lparen_col > *j)
	    ed_lparen_col--;
	break;
    case CTRL('A'):
	*j = 0;
	*uni_j = 0;
	ESCMVLEFT(*uni_j + 3);
	break;
    case CTRL('E'):
	*uni_j = 0;
	for (k = 0; k < COL_SIZE; k++) {
	    if (buffer[k][0] == NUL) {
		break;
	    }
	    if (isUni1(buffer[k][0])) {
		(*uni_j)++;
	    } else if (isUni3(buffer[k][0])) {
		(*uni_j)++;
		(*uni_j)++;
	    } else if (isUni2(buffer[k][0]) || isUni4(buffer[k][0]) ||
		       isUni5(buffer[k][0]) || isUni6(buffer[k][0])) {
		(*uni_j)++;
	    }
	}

	display_buffer();
	*j = k;
	ESCMVLEFT(*uni_j + 3);
	break;
    case CTRL('F'):
	right(j, uni_j);
	break;
    case CTRL('B'):
	left(j, uni_j);
	break;
    case CTRL('P'):
	up(limit, rl_line, j, uni_j, pos);
	break;
    case CTRL('N'):
	down(rl_line, j, uni_j, pos);
	break;
    case ESC:
	c = eisl_getch();
	switch (c) {
	case TAB:
	    find_candidate_buffer(*j);	// completion
	    if (ed_candidate_pt == 0)
		break;
	    else if (ed_candidate_pt == 1) {
		*j = replace_fragment_buffer(ed_candidate[0], *j);
		*uni_j = unipos(j);
		display_buffer();
		ESCMVLEFT(*uni_j + 3);
	    } else {
		const int CANDIDATE = 3;
		int i;

		k = 0;
		ESCSCR();
		ESCMVLEFT(1);
		bool more_candidates_selected;
		do {
		    more_candidates_selected = false;
		    ESCREV();
		    for (i = 0; i < CANDIDATE; i++) {
			if (i + k >= ed_candidate_pt)
			    break;
			printf("%d:%s ", i + 1, ed_candidate[i + k]);
		    }
		    if (ed_candidate_pt > k + CANDIDATE)
			printf("4:more");
		    ESCRST();
		    bool bad_candidate_selected;
		    do {
			bad_candidate_selected = false;
			c = eisl_getch();
			if (c != ESC) {
			    i = c - '1';
			    more_candidates_selected =
				ed_candidate_pt > k + CANDIDATE
				&& i == CANDIDATE;
			    if (more_candidates_selected) {
				k = k + CANDIDATE;
				ESCMVLEFT(1);
				ESCCLSL();
				break;
			    }
			    bad_candidate_selected =
				i + k >= ed_candidate_pt || i < 0
				|| c == EOL;
			}
		    }
		    while (bad_candidate_selected);
		}
		while (more_candidates_selected);
		if (c != ESC) {
		    *j = replace_fragment_buffer(ed_candidate[i + k], *j);
		    *uni_j = unipos(j);
		}
		ESCMVLEFT(1);
		ESCCLSL();
		ESCMVU();
		ESCMVLEFT(3);
		display_buffer();
		ESCMVLEFT(*uni_j + 3);
	    }
	    return false;
	case 'q':		// Esc+q
	    putchar('\n');
	    RAISE(Exit_Interp);
	    break;
	case ARROW_PREFIX:
	    c = eisl_getch();
	    if (c == ed_key_up) {
		up(limit, rl_line, j, uni_j, pos);
	    } else if (c == ed_key_down) {
		down(rl_line, j, uni_j, pos);
	    } else if (c == ed_key_left) {
		left(j, uni_j);
	    } else if (c == ed_key_right) {
		right(j, uni_j);
	    }
	}
	break;

    default:
	if (c < 32)		// if control char, ignore it.
	    return false;

	for (k = COL_SIZE; k > *j; k--)
	    buffer[k][0] = buffer[k - 1][0];
	buffer[(*j)++][0] = c;
	if (isUni1(c) || isUni2(c) || isUni4(c) || isUni5(c) || isUni6(c)) {
	    (*uni_j)++;
	} else if (isUni3(c)) {
	    (*uni_j)++;
	    (*uni_j)++;
	}
	display_buffer();
	reset_paren_buffer();
	if (c == '(' || c == ')') {
	    emphasis_lparen_buffer((*j - 1), (*uni_j - 1));
	    emphasis_rparen_buffer((*j - 1), (*uni_j - 1));
	} else {
	    if (ed_rparen_col >= *j - 1)
		ed_rparen_col++;
	    if (ed_lparen_col >= *j - 1)
		ed_lparen_col++;
	}
	ESCMVLEFT(*uni_j + 3);

    }
    return false;
}
