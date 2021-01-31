#define VERSION  1.73
#define ROW_SIZE 4000
#define COL_SIZE  160
#define COPY_SIZE 500


#define NIL     0

struct position{
    int row;
    int col;
};

//special charactor
#define EOL     '\n'
#define RET     '\r'
#define TAB     '\t'
#define SPACE   ' '
#define ESC     27
#define NUL     '\0'
#define BEL     '\a'
#define BS      '\b'
#define DEL     127


#define LEFT    'D'
#define UP  'A'
#define RIGHT   'C'
#define DOWN    'B'
#define INSERT  '2'
#define DELETE  '3'
#define PAGEUP  '5'
#define PAGEDN  '6'
#define HOME    'H'
#define END 'F'

#define ESCHOME printf("\33[1;1H")
#define ESCTOP  printf("\33[2;1H")
#define ESCCLS  printf("\33[2J")
#define ESCCLS1 printf("\33[0J")
#define ESCCLSL printf("\33[0K")
#define ESCCLSLA printf("\33[2K")
#define ESCMVLEFT(x) printf("\33[%dG", x)
#define ESCMVR  printf("\33[C")
#define ESCMVL  printf("\33[D")
#define ESCMVU  printf("\33[A")
#define ESCMVD  printf("\33[B")
#define ESCSCR  printf("\33[S")
#define ESCMVLN(x) printf("\33[%dD", x)
#define ESCMOVE(x,y)    printf("\33[%d;%df", x,y)
#define ESCFBLACK printf("\33[30m")
#define ESCFRED  printf("\33[31m")
#define ESCFGREEN printf("\33[32m")
#define ESCFYELLOW printf("\33[33m")
#define ESCFBLUE printf("\33[34m")
#define ESCFMAGENTA printf("\33[35m")
#define ESCFCYAN printf("\33[36m")
#define ESCFWHITE printf("\33[37m")
#define ESCFORG  printf("\33[39m")

#define ESCBCYAN printf("\33[46m")
#define ESCBORG  printf("\33[49m")
#define ESCREV  printf("\33[7m")
#define ESCRST  printf("\33[0m")
#define ESCBOLD printf("\33[1m")


void signal_handler(int signo);
void input(char* str);
void edit_screen(char *fname);
void display_command(char *fname);
void display_screen();
void display_line(int line);
void setcolor(int n);
void backspace();
void insertcol();
void insertrow();
int getch();
void deleterow();
int findeol(int row);
struct position findlparen(int bias);
struct position findrparen(int bias);
void reset_paren();
void restore_paren();
void emphasis_lparen();
void emphasis_rparen();
void softtabs(int n);
void save_data(char *name);
int is_special(int row, int col);
int findnext(int row, int col);
void remove_headspace(int row);
int calc_tabs();
void copy_selection();
void paste_selection();
void delete_selection();
int check_token(int row, int col);
char* get_fragment();
void find_candidate();
void replace_fragment(char* newstr);
struct position find_word(char* word);
void replace_word(char* str1, char* str2);
