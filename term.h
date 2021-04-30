/* Terminal-handling definitions common to the interpreter and edlis */

#ifndef TERM_H
#define TERM_H

#ifdef FULLSCREEN
#include <curses.h>
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
// This code is only used in edlis

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
static inline void ESCHOME(void) { printf("\33[1;1H"); }
static inline void ESCTOP(void) { printf("\33[2;1H"); }
static inline void ESCCLS(void) { printf("\33[2J"); }
static inline void ESCCLS1(void) { printf("\33[0J"); }
static inline void ESCCLSL(void) { printf("\33[0K"); }
static inline void ESCCLSLA(void) { printf("\33[2K"); }
static inline void ESCMVLEFT(int x) { printf("\33[%dG", x); }
static inline void ESCMVR(void) { printf("\33[C"); }
static inline void ESCMVL(void) { printf("\33[D"); }
static inline void ESCMVU(void) { printf("\33[A"); }
static inline void ESCMVD(void) { printf("\33[B"); }
static inline void ESCSCR(void) { printf("\33[S"); }
static inline void ESCMVLN(int x) { printf("\33[%dD", x); }
static inline void ESCMOVE(int y, int x) { printf("\33[%d;%df", y, x); }
static inline void ESCFBLACK(void) { printf("\33[30m"); }
static inline void ESCFRED(void) { printf("\33[31m"); }
static inline void ESCFGREEN(void) { printf("\33[32m"); }
static inline void ESCFYELLOW(void) { printf("\33[33m"); }
static inline void ESCFBLUE(void) { printf("\33[34m"); }
static inline void ESCFMAGENTA(void) { printf("\33[35m"); }
static inline void ESCFCYAN(void) { printf("\33[36m"); }
static inline void ESCFWHITE(void) { printf("\33[37m"); }
static inline void ESCFORG(void) { printf("\33[39m"); }

static inline void ESCBCYAN(void) { printf("\33[46m"); }
static inline void ESCBORG(void) { printf("\33[49m"); }
static inline void ESCREV(void) { printf("\33[7m"); }
static inline void ESCRST(void) { printf("\33[0m"); }
static inline void ESCBOLD(void) { printf("\33[1m"); }
#endif

#endif
