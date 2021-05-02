/* Terminal-handling definitions common to the interpreter and edlis */

#ifndef TERM_H
#define TERM_H

#include <curses.h>
#ifndef FULLSCREEN
#include <term.h>
#endif

struct position {
     int row;
     int col;
};

//special charactor
static const char EOL = '\n';
static const char RET = '\r';
static const char TAB = '\t';
static const char SPACE = ' ';
static const char ESC = 27;
static const char NUL = '\0';
static const char BEL = '\a';
static const char BS = '\b';
static const char DEL = 127;

#ifndef FULLSCREEN
static const char LEFT = 'D';
static const char UP = 'A';
static const char RIGHT = 'C';
static const char DOWN = 'B';
static const char INSERT = '2';
static const char DELETE = '3';
static const char PAGEUP = '5';
static const char PAGEDN = '6';
static const char HOME = 'H';
static const char END = 'F';
#endif

#ifdef FULLSCREEN
/* This code is only used in edlis.
 * It uses the higher-level curses interface. */

__dead void errw(const char* msg);
#define CHECK(fn, ...) { \
        if ((fn)(__VA_ARGS__) == ERR) { \
                errw(#fn); \
        } \
}

// ESCMVR, ESCMVL, ESCMVU, ESCMVD, ESCSCR, ESCMVLN, ESCF<color> removed
static inline void ESCHOME(void) { CHECK(move, 0, 0); }
static inline void ESCTOP(void) { CHECK(move, 1, 0); }
static inline void ESCCLS(void) { CHECK(clear); }
static inline void ESCCLS1(void) { CHECK(clrtobot); }
static inline void ESCCLSL(void) { CHECK(clrtoeol); }
static inline void ESCMVLEFT(int x)
{
     int dummy, cur_y;

     getyx(stdscr, cur_y, dummy);
     CHECK(move, cur_y, x - 1);
}
static inline void ESCCLSLA(void)
{
     ESCMVLEFT(1);
     CHECK(clrtoeol);
}
static inline void ESCMOVE(int y, int x) { CHECK(move, y - 1, x - 1); }
static inline void ESCFORG(void)
{
     if (has_colors()) {
          CHECK(color_set, 0, NULL);
     }
}

enum Color { RED_ON_DFL = 1, YELLOW_ON_DFL, BLUE_ON_DFL, MAGENTA_ON_DFL, CYAN_ON_DFL, DFL_ON_CYAN, };
static inline void ESCBCYAN(void)
{
     if (has_colors()) {
          CHECK(color_set, DFL_ON_CYAN, NULL);
     }
}
static inline void ESCBORG(void)
{
     if (has_colors()) {
          CHECK(color_set, 0, NULL);
     }
}
static inline void ESCREV(void) { CHECK(attron, A_REVERSE); }
static inline void ESCRST(void) { CHECK(attrset, A_NORMAL); }
static inline void ESCBOLD(void) { CHECK(attron, A_BOLD); }
#else
/* This uses the lower-level terminfo interface because we don't want to clear the screen */

static inline void ESCCLSL(void) { putp(clr_eol); }
static inline void ESCMVLEFT(int x) { putp(tparm(column_address, x - 1)); }
static inline void ESCMVU(void) { putp(cursor_up); }
static inline void ESCSCR(void) { putp(scroll_forward); }
static inline void ESCFORG(void) { putp(exit_attribute_mode); }

static inline void ESCBCYAN(void) { putp(tparm(set_a_background, COLOR_CYAN)); }
static inline void ESCBORG(void) { putp(exit_attribute_mode); }
static inline void ESCREV(void) { putp(enter_reverse_mode); }
static inline void ESCRST(void) { putp(exit_attribute_mode); }
static inline void ESCBOLD(void) { putp(enter_bold_mode); }
#endif

enum HighlightToken { HIGHLIGHT_NONE, HIGHLIGHT_SYNTAX, HIGHLIGHT_BUILTIN, HIGHLIGHT_STRING, HIGHLIGHT_COMMENT, HIGHLIGHT_EXTENDED, HIGHLIGHT_MULTILINE_COMMENT, };
enum HighlightToken maybe_match(const char *str);
bool in_special_table(const char *str);
void gather_fuzzy_matches(const char *str, const char *candidates[], int *candidate_pt);

#endif
