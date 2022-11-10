/*
 * Terminal-handling definitions common to the interpreter and edlis.
 * This also includes some presentation-related functions, e.g. syntax highlighting.
 *
 * There are two relevant library layers here:
 * 1. Curses is high-level, but only appropriate for fullscreen programs
 * 2. Terminfo is lower-level (curses is built on it)
 * 
 * I only considered standardized libraries (e.g. X/Open).
 */

#ifndef TERM_H
#define TERM_H

#include "compat/curses_stubs.h"
#ifndef FULLSCREEN
#include "compat/term_stubs.h"
#endif

struct position {
    int             row;
    int             col;
};

// special charactor
#define EOL '\n'
#define RET '\r'
#define TAB '\t'
#define SPACE ' '
#define ESC 27
static const char NUL = '\0';
static const char BEL = '\a';
static const char BS = '\b';
#define DEL 127

#ifndef FULLSCREEN
#define ARROW_PREFIX '['
extern char     ed_key_down;
extern char     ed_key_left;
extern char     ed_key_right;
extern char     ed_key_up;
#endif

#ifdef FULLSCREEN
/*
 * Edlis uses the higher-level curses interface 
 */

__dead void     errw(const char *msg);
#define CHECK(fn, ...) { \
        if ((fn)(__VA_ARGS__) == ERR) { \
                errw(#fn); \
        } \
}

static inline void
ESCHOME(void)
{
    CHECK(move, 0, 0);
}

static inline void
ESCTOP(void)
{
    CHECK(move, 1, 0);
}

static inline void
ESCCLS(void)
{
    CHECK(clear);
}

static inline void
ESCCLS1(void)
{
    CHECK(clrtobot);
}

static inline void
ESCCLSL(void)
{
    CHECK(clrtoeol);
}

static inline void
ESCMVLEFT(int x)
{
    int             dummy,
                    cur_y;

    getyx(stdscr, cur_y, dummy);
    CHECK(move, cur_y, x - 1);
}

static inline void
ESCCLSLA(void)
{
    ESCMVLEFT(1);
    CHECK(clrtoeol);
}

static inline void
ESCMOVE(int y, int x)
{
    CHECK(move, y - 1, x - 1);
}

static inline void
ESCFORG(void)
{
    if (has_colors()) {
	CHECK(color_set, 0, NULL);
    }
}

enum Color { RED_ON_DFL =
	1, YELLOW_ON_DFL, BLUE_ON_DFL, MAGENTA_ON_DFL, CYAN_ON_DFL,
    DFL_ON_CYAN,
};
static inline void
ESCBCYAN(void)
{
    if (has_colors()) {
	CHECK(color_set, DFL_ON_CYAN, NULL);
    }
}

static inline void
ESCBORG(void)
{
    if (has_colors()) {
	CHECK(color_set, 0, NULL);
    }
}

static inline void
ESCREV(void)
{
    CHECK(attron, A_REVERSE);
}

static inline void
ESCRST(void)
{
    CHECK(attrset, A_NORMAL);
}

static inline void
ESCBOLD(void)
{
    CHECK(attron, A_BOLD);
}
#elif defined(WITHOUT_CURSES)
#define ESCCLSL()
#define ESCMVLEFT(x)
#define ESCMVU()
#define ESCSCR()
#define ESCFORG()
#define ESCBCYAN()
#define ESCBORG()
#define ESCREV()
#define ESCRST()
#define ESCBOLD()
#else
/*
 * The REPL uses the lower-level terminfo interface because we don't want
 * to clear the screen 
 */

static inline void
ESCCLSL(void)
{
    putp(clr_eol);
}

static inline void
ESCMVLEFT(int x)
{
    putp(tparm(column_address, x - 1));
}

static inline void
ESCMVU(void)
{
    putp(cursor_up);
}

static inline void
ESCSCR(void)
{
    putp(scroll_forward);
}

static inline void
ESCFORG(void)
{
    putp(exit_attribute_mode);
}

static inline void
ESCBCYAN(void)
{
    putp(tparm(set_a_background, COLOR_CYAN));
}

static inline void
ESCBORG(void)
{
    putp(exit_attribute_mode);
}

static inline void
ESCREV(void)
{
    putp(enter_reverse_mode);
}

static inline void
ESCRST(void)
{
    putp(exit_attribute_mode);
}

static inline void
ESCBOLD(void)
{
    putp(enter_bold_mode);
}
#endif

enum HighlightToken { HIGHLIGHT_NONE, HIGHLIGHT_SYNTAX, HIGHLIGHT_BUILTIN,
    HIGHLIGHT_STRING, HIGHLIGHT_COMMENT, HIGHLIGHT_EXTENDED,
    HIGHLIGHT_MULTILINE_COMMENT,
};
enum HighlightToken maybe_match(const char *str);
bool            in_special_table(const char *str);
void            gather_fuzzy_matches(const char *str,
				     const char *candidates[],
				     int *candidate_pt);
#define COMPLETION_CANDIDATES_MAX 50

#endif
