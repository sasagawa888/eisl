#ifndef EDLIS_H
#define EDLIS_H

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif	/* 
 */
    
#define FULLSCREEN
#include "term.h"

static const float VERSION = 4.03;

#define ROW_SIZE 5000
#define COL_SIZE 255
#define COPY_SIZE 500
#define TOKEN_MAX   80
#define LEFT_MARGIN 7
#define TOP_MARGIN  2

static const int NIL = 0;

bool is_special(int row, int col);
int calc_tabs(void);
int findnext(int row, int col);
int findeol(int row);
int findeol1(int row);
char *get_fragment(void);
enum HighlightToken check_token(int row, int col);
struct position find_lparen(int bias);
struct position find_rparen(int bias);
struct position find_word(const char *word);
struct position find_word_back(const char *word);
void backspace(void);
void copy_selection(void);
void deleterow(void);
void delete_selection(void);
void display_header(char *fname);
void display_screen(void);
void display_line(int line);
void edit_screen(char *fname);
void emphasis_lparen(void);
void emphasis_rparen(void);
void find_candidate(void);
void help(void);
void init_ncurses(void);
void input(char *str);
void insertcol(void);
void insertrow(void);
void load_data(char *name);
void paste_selection(void);
void replace_fragment(const char *newstr);
void replace_word(const char *str1, const char *str2);
void reset_paren(void);
void restore_paren(void);
void remove_headspace(int row);
void setcolor(enum Color);
void softtabs(int n);
void save_data(char *name);
void signal_handler_c(int signo __unused);
void signal_handler_z(int signo __unused);
 
 
//following are for unicode<=>UTF-8 transform
#define UNI2ADD1    192		//#b11000000
#define UNI3ADD1    224		//#b11100000
#define UNI4ADD1    240		//#b11110000
#define UNIOADDO    128		//#b10000000
#define UNI2MSK1    1984	//#b0000011111000000
#define UNI2MSK2    63		//#b0000000000111111
#define UNI3MSK1    61440	//#b1111000000000000
#define UNI3MSK2    4032	//#b0000111111000000
#define UNI3MSK3    63		//#b0000000000111111
#define UNI4MSK1    1835008	//#b00000000000111000000000000000000
#define UNI4MSK2    258048	//#b00000000000000111111000000000000
#define UNI4MSK3    4032	//#b00000000000000000000111111000000
#define UNI4MSK4    63		//#b00000000000000000000000000111111
#define UTF2MSK1    63		//#b00111111
#define UTF3MSK1    31		//#b00011111
#define UTF4MSK1    15		//#b00001111
#define UTFOMSKO    127		//#b01111111
    
#define isUni1(c)   ((unsigned char)(c) <= 0x7f)
    
#define isUni2(c)   (((unsigned char)(c) >= 0xc2) && \
    ((unsigned char) (c) <= 0xdf)) 
 
#define isUni3(c)   (((unsigned char)(c) >= 0xe0) && \
    ((unsigned char) (c) <= 0xef)) 
 
#define isUni4(c)   (((unsigned char)(c) >= 0xf0) && \
    ((unsigned char) (c) <= 0xf7)) 
 
 
#endif	
