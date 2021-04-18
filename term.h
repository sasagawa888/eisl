/* Terminal-handling definitions common to the interpreter and edlis */

#ifndef TERM_H
#define TERM_H

struct position{
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

#if __linux || __APPLE__ || defined(__OpenBSD__)
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
static inline void ESCMOVE(int x,int y) { printf("\33[%d;%df", x,y); }
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
