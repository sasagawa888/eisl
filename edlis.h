#ifndef EDLIS_H
#define EDLIS_H

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif	/* 
 */
    
#define FULLSCREEN
#include "term.h"

static const float VERSION = 5.22;

#define ROW_SIZE 5000
#define COL_SIZE 256
#define COPY_SIZE 1000
#define TOKEN_MAX   80
#define LEFT_MARGIN 7
#define TOP_MARGIN  2

static const int NIL = 0;
static const char *functions_data[];

bool edit_loop(void);
bool is_special(int row, int col);
bool is_word_char(char x);
bool quit_with_save(void);
int calc_tabs(void);
int findnext(int row, int col);
int findeol(int row);
int findeol1(int row);
int find_function_data(const char *str);
int getch1(void);
char *get_fragment(void);
char *getname(void);
enum HighlightToken check_token(int row, int col);
struct position find_lparen(int bias);
struct position find_rparen(int bias);
struct position find_word(const char *word);
struct position find_word_back(const char *word);
void backspace(void);
void backspace_key(void);
void copy_selection(void);
void cut_line(void);
void del(void);
void delete_char(void);
void deleterow(void);
void delete_selection(void);
void display_header(void);
void display_screen(void);
void display_line(int line);
void down(void);
void edit_screen(void);
void end(void);
void emphasis_lparen(void);
void emphasis_rparen(void);
void find_candidate(void);
void help(void);
void home(void);
void information(void);
void init_ncurses(void);
void input(char *str);
void insertcol(void);
void insertrow(void);
void left(void);
void load_data(char *name);
void mark_unmark(void);
void pageup(void);
void pagedown(void);
void paste_selection(void);
void redisplay_screen(void);
void replace_fragment(const char *newstr);
void replace_word(const char *str1, const char *str2);
void reset_paren(void);
void restore_paren(void);
void restore_cursol(void);
void return_key(void);
void remove_headspace(int row);
void right(void);
void save_region(void);
void save_file_as(void);
void setcolor(enum Color);
void softtabs(int n);
void save_data(char *name);
void save_copy(char *name);
void signal_handler_c(int signo __unused);
void signal_handler_z(int signo __unused);
void tab_key(void);
void up(void);
void word_next(void);
void word_prev(void);
 
 
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
