#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include "eisl.h"

#ifndef CTRL
#define CTRL(X) ((X) & 0x1F)
#endif

static const int COL_SIZE = 255;

int f_edit(int arglist){
    int arg1;
    char str[STRSIZE];

	arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "edit", arglist);
    strcpy(str,"./edlis ");
    strcat(str,GET_NAME(arg1));
	if(system(str) == -1)
		error(SYSTEM_ERR, "edit", arg1);
    f_load(arglist);
	return(T);
}

void setcolor(short n){
    putp(tparm(set_a_foreground, n));
}

int eisl_getch(){
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

//------------REPL read-line-----------------
void display_buffer(){
    int col;

    ESCMVLEFT(3);
    ESCCLSL();
    col = 0;

    while(buffer[col][0] != EOL &&
          buffer[col][0] != NUL){

          if(ed_incomment != -1 && line >= ed_incomment){ //comment #|...|#
              ESCBOLD();
             setcolor(ed_comment_color);
             while(buffer[col][0] != EOL &&
                   buffer[col][0] != NUL){
                       putchar(buffer[col][0]);
                       col++;
                       if(buffer[col-2][0] == '|' &&
                          buffer[col-1][0] == '#'){
                             ed_incomment = -1;
                             ESCRST();
                             ESCFORG();
                             break;
                       }
             }
             ESCRST();
             ESCFORG();
         }
         else if(buffer[col][0] == ' ' ||
                 buffer[col][0] == '(' ||
                 buffer[col][0] == ')' ){
            putchar(buffer[col][0]);
            col++;
         }
         else{
             switch (check_token_buffer(col)) {
             case HIGHLIGHT_SYNTAX:
                ESCBOLD();
                setcolor(ed_syntax_color);
                while(buffer[col][0] != ' ' &&
                      buffer[col][0] != '(' &&
                      buffer[col][0] != ')' &&
                      buffer[col][0] != NUL &&
                      buffer[col][0] != EOL){
                        putchar(buffer[col][0]);
                        col++;
                }
                ESCRST();
                ESCFORG();
                break;
             case HIGHLIGHT_BUILTIN:
                    ESCBOLD();
                    setcolor(ed_builtin_color);
                    while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
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
                    while(buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                        putchar(buffer[col][0]);
                        col++;
                        if(buffer[col-1][0] == '"')
                            break;
                   }
                    ESCRST();
                    ESCFORG();
                    break;
             case HIGHLIGHT_COMMENT:
                   ESCBOLD();
                   setcolor(ed_comment_color);
                   while(buffer[col][0] != NUL &&
                         buffer[col][0] != EOL){
                        putchar(buffer[col][0]);
                        col++;
                   }
                   ESCRST();
                   ESCFORG();
                   break;
             case HIGHLIGHT_EXTENDED:
                   ESCBOLD();
                   setcolor(ed_extended_color);
                   while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
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
                   while(buffer[col][0] != EOL &&
                         buffer[col][0] != NUL){
                             putchar(buffer[col][0]);
                             col++;
                             if(buffer[col-2][0] == '|' &&
                                buffer[col-1][0] == '#'){
                                 ed_incomment = -1;
                                 ESCRST();
                                 ESCFORG();
                                 break;
                             }
                   }
                   break;
             default:
                    while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                       putchar(buffer[col][0]);
                       col++;
                    }
             }
         }
    }
    ESCRST();
    return;
}


enum HighlightToken check_token_buffer(int col){
    char str[80];
    int pos;

    pos = 0;
    if(buffer[col][0] == '"')
        return HIGHLIGHT_STRING;
    else if(buffer[col][0] == ';')
       return HIGHLIGHT_COMMENT;
    while(buffer[col][0] != ' ' &&
          buffer[col][0] != '(' &&
          buffer[col][0] != ')' &&
          buffer[col][0] != NUL &&
          buffer[col][0] != EOL){
        str[pos] = buffer[col][0];
        col++;
        pos++;
        }
    str[pos] = NUL;
    if(str[0] == '#' && str[1] == '|')
        return HIGHLIGHT_MULTILINE_COMMENT; // #|...|#
    if(pos == 0)
        return HIGHLIGHT_NONE;
    return maybe_match(str);
}


int findlparen_buffer(int col){
    int nest;

    col--;
    nest = 0;
    while(col >= 0){
        if(buffer[col][0] == '(' && nest == 0)
            break;
        else if(buffer[col][0] == ')')
            nest++;
        else if(buffer[col][0] == '(')
            nest--;

        col--;
    }
    return(col);
}

int findrparen_buffer(int col){
    int nest,limit;

    col++;
    nest = 0;
    for(limit=0;limit<256;limit++)
        if(buffer[limit][0] == 0)
            break;

    while(col <= limit){
        if(buffer[col][0] == ')' && nest == 0)
            break;
        else if(buffer[col][0] == '(')
            nest++;
        else if(buffer[col][0] == ')')
            nest--;

        col++;
    }
    if(col > limit)
       return(-1);
    else
       return(col);
}

void emphasis_rparen_buffer(int col){
    int pos;

    if(buffer[col][0] != '(')
        return;
    pos = findrparen_buffer(col);
    if(pos < 0)
        return;

    ESCMVLEFT(col+3);
    ESCBCYAN();
    putchar('(');
    ESCBORG();
    ESCMVLEFT(pos+3);
    ESCBCYAN();
    putchar(')');
    ESCBORG();
    ed_rparen_col = pos;
    ed_lparen_col = col;
    ESCMVLEFT(col+3);
}


void emphasis_lparen_buffer(int col){
    int pos;

    if(buffer[col][0] != ')')
        return;

    pos = findlparen_buffer(col);
    if(pos < 0)
        return;

    ESCMVLEFT(col+3);
    ESCBCYAN();
    putchar(')');
    ESCBORG();
    ESCMVLEFT(pos+3);
    ESCBCYAN();
    putchar('(');
    ESCBORG();
    ed_rparen_col = col;
    ed_lparen_col = pos;
    ESCMVLEFT(col+3);
}


void reset_paren_buffer(){
    ed_lparen_col = -1;
    ed_rparen_col = -1;
}

void restore_paren_buffer(int col){

    if(ed_lparen_col != -1){
        ESCMVLEFT(ed_lparen_col+3);
        ESCBORG();
        putchar('(');
        ed_lparen_col = -1;
    }
    if(ed_rparen_col != -1){
        ESCMVLEFT(ed_rparen_col+3);
        ESCBORG();
        putchar(')');
        ed_rparen_col = -1;
    }
    ESCMVLEFT(col+3);
}


char *get_fragment_buffer(int col){
    static char str[80];
    int pos;

    while(col >= 0 &&
          buffer[col][0] != ' ' &&
          buffer[col][0] != '(' &&
          buffer[col][0] != ')'){
                col--;
        }
        col++;
        pos = 0;
    while(buffer[col][0] != ' ' &&
          buffer[col][0] != '(' &&
          buffer[col][0] >= ' '){
        str[pos] = buffer[col][0];
        col++;
        pos++;
    }
    str[pos] = NUL;
    return(str);
}


void find_candidate_buffer(int col){
    char* str;

    str = get_fragment_buffer(col);
    ed_candidate_pt = 0;
    if(str[0] != NUL)
        gather_fuzzy_matches(str, ed_candidate, &ed_candidate_pt);
}

int replace_fragment_buffer(const char* newstr, int col){
    char* oldstr;
    int m,n;

    oldstr = get_fragment_buffer(col);
    m = strlen(oldstr);
    n = strlen(newstr);
    col--;
    while(m>0){
        backspace_buffer(col);
        m--;
        col--;
    }
    col++;
    while(n>0){
        insertcol_buffer(col);
        buffer[col][0] = *newstr;
        col++;
        newstr++;
        n--;
    }

    return(col);
}

void backspace_buffer(int col){
    int i;

    for(i=col;i<255;i++)
        buffer[i][0] = buffer[i+1][0];
    buffer[255][0] = 0;
}

void insertcol_buffer(int col){
    int i;

    for(i=255;i>col;i--)
        buffer[i][0] = buffer[i-1][0];
}

static void right(int *j)
{
    if(buffer[*j][0] == 0)
        return;
    (*j) = (*j) + 1;
    restore_paren_buffer(*j);
    emphasis_lparen_buffer(*j);
    emphasis_rparen_buffer(*j);
    ESCMVLEFT((*j)+3);
}

static void left(int *j)
{
    if((*j) <= 0)
        return;
    (*j) = (*j) - 1;
    restore_paren_buffer(*j);
    emphasis_lparen_buffer(*j);
    emphasis_rparen_buffer(*j);
    ESCMVLEFT((*j)+3);
}

int read_line(int flag){
    int c,i,j,k,rl_line;
    static int pos=0,limit=0;

    if(flag == -1){
       pos--;
       return(-1);
    }

    if(buffer[pos][0] == 0){
        for(i=9;i>0;i--)
            for(j=0;j<256;j++)
                buffer[j][i] = buffer[j][i-1];

        limit++;
        if(limit >= 10)
            limit = 9;

       for(j=0;j<256;j++)
            buffer[j][0] = 0;

        rl_line = 0;
        ed_lparen_col = -1;
        ed_rparen_col = -1;
        j = 0;
        c = eisl_getch();
        loop:
        switch(c){
        case CTRL('M'):
            case EOL: for(j=0;j<256;j++)
                          if(buffer[j][0] == 0) {
                              buffer[j][0] = c;
                              break;
                          }
                      restore_paren_buffer(j);
                      putchar(c);
                      pos = 0;
                      goto exit;
        case CTRL('H'):
            case DEL: if(j <= 0)
                          break;
                      j--;
                      for(k=j;k<255;k++)
                          buffer[k][0] = buffer[k+1][0];
                      display_buffer();
                      ESCMVLEFT(j+3);
                      if(ed_rparen_col > i)
                          ed_rparen_col--;
                      if(ed_lparen_col > i)
                          ed_lparen_col--;
                      break;
        case CTRL('D'):
                      for(k=j;k<255;k++)
                          buffer[k][0] = buffer[k+1][0];
                      display_buffer();
                      ESCMVLEFT(j+3);
                      if(ed_rparen_col > i)
                          ed_rparen_col--;
                      if(ed_lparen_col > i)
                          ed_lparen_col--;
                      break;
        case CTRL('K'):
                      memset(buffer1,NUL,255);
                      for(k=j;k<255;k++){
                          buffer1[k-j] = buffer[k][0];
                          buffer[k][0] = NUL;
                      }
                      display_buffer();
                      ESCMVLEFT(j+3);
                      break;
        case CTRL('Y'):
                      for(k=0;k<255;k++)
                          buffer[k][0] = buffer1[k];
                      
                      for(k=0;k<255;k++){
                          if(buffer[k][0] == NUL) 
                            break;
                      }

                      display_buffer();
                      j = k;
                      ESCMVLEFT(k+3);
                      break;
        case CTRL('A'):
                      j = 0;
                      ESCMVLEFT(j+3);
                      break;
        case CTRL('E'):
                      for(k=0;k<255;k++){
                          if(buffer[k][0] == NUL) 
                            break;
                      }

                      display_buffer();
                      j = k;
                      ESCMVLEFT(k+3);
                      break;
        case CTRL('F'):
            right(&j);
            break;
        case CTRL('B'):
            left(&j);
            break;
        case CTRL('P'):
                      up:
                      if(limit <= 1)
                         break;
                      if(rl_line >= limit-1)
                         rl_line = limit-2;
                      for(j=0;j<256;j++)
                          buffer[j][0] = buffer[j][rl_line+1];

                      for(j=0;j<256;j++)
                          if(buffer[j][0] == EOL)
                              break;
                      rl_line++;
                      pos = 0;
                      ed_rparen_col = -1;
                      ed_lparen_col = -1;
                      display_buffer();
                      break;
        case CTRL('N'):
                      down:
                      if(rl_line <= 1)
                         rl_line = 1;
                      for(j=0;j<256;j++)
                          buffer[j][0] = buffer[j][rl_line-1];
                      for(j=0;j<256;j++)
                          if(buffer[j][0] == EOL)
                              break;
                      rl_line--;
                      pos = 0;
                      ed_rparen_col = -1;
                      ed_lparen_col = -1;
                      display_buffer();
                      break;
            case ESC: c = eisl_getch();
                    switch(c){
                        case TAB: find_candidate_buffer(j); //completion
                                    if(ed_candidate_pt == 0)
                                        break;
                                    else if(ed_candidate_pt == 1){
                                        j = replace_fragment_buffer(ed_candidate[0],j);
                                        display_buffer();
                                        ESCMVLEFT(j+3);
                                    }
                                    else{
                                        #define CANDIDATE 3
                                        k = 0;
                                        ESCSCR();
                                        ESCMVLEFT(1);
                                        next:
                                        ESCREV();
                                        for(i=0; i<CANDIDATE; i++){
                                            if(i+k >= ed_candidate_pt)
                                                 break;
                                             printf("%d:%s ", i+1, ed_candidate[i+k]);
                                        }
                                        if(ed_candidate_pt > k+CANDIDATE)
                                            printf("4:more");
                                        ESCRST();
                                        retry:
                                        c = eisl_getch();
                                        if(c == ESC)
                                             goto escape;
                                        i = c - '1';
                                        if(ed_candidate_pt > k+CANDIDATE && i == CANDIDATE){
                                            k = k+CANDIDATE;
                                            ESCMVLEFT(1);
                                            ESCCLSL();
                                            goto next;
                                        }
                                        if(i+k >= ed_candidate_pt || i < 0)
                                            goto retry;
                                        if(c == EOL)
                                            goto retry;
                                        j = replace_fragment_buffer(ed_candidate[i+k],j);
                                        escape:
                                        ESCMVLEFT(1);
                                        ESCCLSL();
                                        ESCMVU();
                                        ESCMVLEFT(3);
                                        display_buffer();
                                        ESCMVLEFT(j+3);
                                    }
                                    c = eisl_getch();
                                     goto loop;
                        case 'q':   //Esc+q
                                    putchar('\n');
                                    greeting_flag = false;
                                    longjmp(buf,2);
                    case ARROW_PREFIX:
                            c = eisl_getch();
                            if (c == ed_key_up) {
                                goto up;
                            } else if (c == ed_key_down) {
                                goto down;
                            } else if (c == ed_key_left) {
                                left(&j);
                            } else if (c == ed_key_right) {
                                right(&j);
                            }
                    }
                      break;

            default:  for(k=255;k>j;k--)
                          buffer[k][0] = buffer[k-1][0];
                      buffer[j++][0] = c;
                      display_buffer();
                      reset_paren_buffer();
                      if(c == '(' || c == ')'){
                          emphasis_lparen_buffer(j-1);
                          emphasis_rparen_buffer(j-1);
                      }
                      else{
                          if(ed_rparen_col >= j-1)
                              ed_rparen_col++;
                          if(ed_lparen_col >= j-1)
                              ed_lparen_col++;
                      }
                      ESCMVLEFT(j+3);

        }
        c = eisl_getch();
        goto loop;
    }
   exit:
   return(buffer[pos++][0]);
}
