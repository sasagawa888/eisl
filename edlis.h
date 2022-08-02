#ifndef EDLIS_H
#define EDLIS_H

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif

#define FULLSCREEN
#include "term.h"

static const float VERSION = 2.57;
#define ROW_SIZE 4000
#define COL_SIZE 255
#define COPY_SIZE 500
#define TOKEN_MAX   80
#define LEFT_MARGIN 7
#define TOP_MARGIN  2
#define BOTTOM      22
#define MIDDLE      10



static const int NIL = 0;


void input(char* str);
void edit_screen(char* fname);
void display_command(char* fname);
void display_screen(void);
void display_line(int line);
void setcolor(enum Color);
void backspace(void);
void insertcol(void);
void insertrow(void);
void deleterow(void);
int findeol(int row);
struct position findlparen(int bias);
struct position findrparen(int bias);
void reset_paren(void);
void restore_paren(void);
void emphasis_lparen(void);
void emphasis_rparen(void);
void softtabs(int n);
void save_data(char* name);
bool is_special(int row, int col);
int findnext(int row, int col);
void remove_headspace(int row);
int calc_tabs(void);
void copy_selection(void);
void paste_selection(void);
void delete_selection(void);
enum HighlightToken check_token(int row, int col);
char *get_fragment(void);
void find_candidate(void);
void replace_fragment(const char *newstr);
struct position find_word(const char *word);
struct position find_word_back(const char *word);
void replace_word(const char *str1, const char *str2);


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



#endif
