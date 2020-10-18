#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "eisl.h"


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

void setcolor(int n){
        switch(n){
                case 0: ESCFBLACK; break;
                case 1: ESCFRED; break;
                case 2: ESCFGREEN; break;
                case 3: ESCFYELLOW; break;
                case 4: ESCFBLUE; break;
                case 5: ESCFMAGENTA; break;
                case 6: ESCFCYAN; break;
                case 7: ESCFWHITE; break;
                default: ESCFWHITE; break;
        }
        return;
}

int getch(){
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
    int col,type;

    ESCMVLEFT(3);
    ESCCLSL;
    col = 0;

    while(buffer[col][0] != EOL &&
          buffer[col][0] != NUL){

          if(ed_incomment != -1 && line >= ed_incomment){ //comment #|...|#
             ESCBOLD;
             setcolor(ed_comment_color);
             while(buffer[col][0] != EOL &&
                   buffer[col][0] != NUL){
                       printf("%c", buffer[col][0]);
                       col++;
                       if(buffer[col-2][0] == '|' &&
                          buffer[col-1][0] == '#'){
                             ed_incomment = -1;
                             ESCRST;
                             ESCFORG;
                             break;
                       }
             }
             ESCRST;
             ESCFORG;
         }
         else if(buffer[col][0] == ' ' ||
                 buffer[col][0] == '(' ||
                 buffer[col][0] == ')' ){
            printf("%c", buffer[col][0]);
            col++;
         }
         else{
            type = check_token_buffer(col);
            if(type == 1){
                ESCBOLD;
                setcolor(ed_syntax_color);
                while(buffer[col][0] != ' ' &&
                      buffer[col][0] != '(' &&
                      buffer[col][0] != ')' &&
                      buffer[col][0] != NUL &&
                      buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                }
                ESCRST;
                ESCFORG;
                }
                else if(type == 2){
                        ESCBOLD;
                    setcolor(ed_builtin_color);
                    while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                        }
                        ESCRST;
                        ESCFORG;
                }
                else if(type == 3){
                    ESCBOLD;
                    setcolor(ed_string_color);
                    printf("%c", buffer[col][0]);
                    col++;
                    while(buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                        if(buffer[col-1][0] == '"')
                            break;
                   }
                   ESCRST;
                   ESCFORG;

               }
               else if(type == 4){
                   ESCBOLD;
                   setcolor(ed_comment_color);
                   while(buffer[col][0] != NUL &&
                         buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                   }
                   ESCRST;
                   ESCFORG;
               }
               else if(type == 5){
                   ESCBOLD;
                   setcolor(ed_extended_color);
                   while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                   }
                   ESCRST;
                   ESCFORG;
               }
               else if(type == 6){ //comment #|...|#
                   ESCBOLD;
                   setcolor(ed_comment_color);
                   ed_incomment = line;
                   while(buffer[col][0] != EOL &&
                         buffer[col][0] != NUL){
                             printf("%c", buffer[col][0]);
                             col++;
                             if(buffer[col-2][0] == '|' &&
                                buffer[col-1][0] == '#'){
                                 ed_incomment = -1;
                                 ESCRST;
                                 ESCFORG;
                                 break;
                             }
                   }
               }
               else{
                    while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                       printf("%c", buffer[col][0]);
                       col++;
                    }
               }
                }
        }
    ESCRST;
    return;
}


int check_token_buffer(int col){
    char str[80];
    int pos,i;

    pos = 0;
    if(buffer[col][0] == '"')
        return(3); //string token
    else if(buffer[col][0] == ';')
       return(4); //comment token
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
        return(6); // #|...|#
    if(pos == 0)
        return(0);
    for(i=0; i<60; i++){
        if(strcmp(syntax[i],str) == 0){
            return(1); //syntax token
        }
    }
    for(i=0; i<200; i++){
        if(strcmp(builtin[i],str) == 0){
            return(2); //builtin token
        }
    }
    for(i=0; i<50; i++){
        if(strcmp(extended[i],str) == 0){
            return(5); //extended token
        }
    }
    return(0);
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
    ESCBCYAN;
    printf("(");
    ESCBORG;
    ESCMVLEFT(pos+3);
    ESCBCYAN;
    printf(")");
    ESCBORG;
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
    ESCBCYAN;
    printf(")");
    ESCBORG;
    ESCMVLEFT(pos+3);
    ESCBCYAN;
    printf("(");
    ESCBORG;
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
        ESCBORG;
        printf("(");
        ed_lparen_col = -1;
    }
    if(ed_rparen_col != -1){
        ESCMVLEFT(ed_rparen_col+3);
        ESCBORG;
        printf(")");
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
    int i;

    str = get_fragment_buffer(col);
    ed_candidate_pt = 0;
    if(str[0] == NUL)
        return;
    for(i=0;i<60;i++){
        if(strstr(syntax[i],str) !=NULL && syntax[i][0] == str[0]){
            strcpy(ed_candidate[ed_candidate_pt],syntax[i]);
                        ed_candidate_pt++;
        }
    }
    for(i=0;i<200;i++){
        if(strstr(builtin[i],str) !=NULL && builtin[i][0] == str[0]){
            strcpy(ed_candidate[ed_candidate_pt],builtin[i]);
                        ed_candidate_pt++;
        }
    }
    for(i=0;i<50;i++){
        if(strstr(extended[i],str) !=NULL && extended[i][0] == str[0]){
            strcpy(ed_candidate[ed_candidate_pt],extended[i]);
                        ed_candidate_pt++;
        }
    }
    return;
}

int replace_fragment_buffer(char* newstr, int col){
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

    for(i=col;i<256;i++)
        buffer[i][0] = buffer[i+1][0];
}

void insertcol_buffer(int col){
    int i;

    for(i=255;i>col;i--)
        buffer[i][0] = buffer[i-1][0];
}

int read_line(int flag){
    int c,i,j,k,line;
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

        line = 0;
        ed_lparen_col = -1;
        ed_rparen_col = -1;
        j = 0;
        c = getch();
        loop:
        switch(c){
            case 13:  //ctrl+M
            case EOL: for(j=0;j<256;j++)
                          if(buffer[j][0] == 0)
                              break;
                      buffer[j][0] = c;
                      restore_paren_buffer(j);
                      printf("%c",c);
                      pos = 0;
                      goto exit;
            case 8:   //ctrl+H  
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
            case 4:   //ctrl+D  
                      for(k=j;k<255;k++)
                          buffer[k][0] = buffer[k+1][0];
                      display_buffer();
                      ESCMVLEFT(j+3);
                      if(ed_rparen_col > i)
                          ed_rparen_col--;
                      if(ed_lparen_col > i)
                          ed_lparen_col--;
                      break;
            case 11:   //ctrl+K  
                      memset(buffer1,NUL,255);
                      for(k=j;k<255;k++){
                          buffer1[k-j] = buffer[k][0];
                          buffer[k][0] = NUL;
                      }
                      display_buffer();
                      ESCMVLEFT(j+3);
                      break;
            case 25:   //ctrl+Y  
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
            case 1:   //ctrl+A  
                      j = 0;
                      ESCMVLEFT(j+3);
                      break;
            case 5:   //ctrl+E 
                      for(k=0;k<255;k++){
                          if(buffer[k][0] == NUL) 
                            break;
                      }

                      display_buffer();
                      j = k;
                      ESCMVLEFT(k+3);
                      break;
            case 6:   //ctrl+F
                      goto right;
            case 2:   //ctrl+B
                      goto left;
            case 16:  //ctrl+P
                      up:
                      if(limit <= 1)
                         break;
                      if(line >= limit-1)
                         line = limit-2;
                      for(j=0;j<256;j++)
                          buffer[j][0] = buffer[j][line+1];

                      for(j=0;j<256;j++)
                          if(buffer[j][0] == EOL)
                              break;
                      line++;
                      pos = 0;
                      ed_rparen_col = -1;
                      ed_lparen_col = -1;
                      display_buffer();
                      break;
            case 14:  //ctrl+N
                      down:
                      if(line <= 1)
                         line = 1;
                      for(j=0;j<256;j++)
                          buffer[j][0] = buffer[j][line-1];
                      for(j=0;j<256;j++)
                          if(buffer[j][0] == EOL)
                              break;
                      line--;
                      pos = 0;
                      ed_rparen_col = -1;
                      ed_lparen_col = -1;
                      display_buffer();
                      break;
            case ESC: c = getch();
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
                                        ESCSCR;
                                        ESCMVLEFT(1);
                                        ESCREV;
                                        for(i=0; i<5; i++){
                                            if(i >= ed_candidate_pt)
                                                 break;
                                             printf("%d:%s ", i+1, ed_candidate[i]);
                                        }
                                        ESCRST;
                                        retry:
                                        c = getch();
                                        if(c == ESC)
                                             goto escape;
                                        i = c - '1';
                                        if(i > ed_candidate_pt)
                                            goto retry;
                                        if(c == EOL)
                                            goto retry;
                                        j = replace_fragment_buffer(ed_candidate[i],j);
                                        escape:
                                        ESCMVLEFT(1);
                                        ESCCLSL;
                                        ESCMVU;
                                        ESCMVLEFT(3);
                                        display_buffer();
                                        ESCMVLEFT(j+3);
                                    }
                                    c = getch();
                                    goto loop;
                      }
                      c = getch();
                      switch(c){
                          case UP: goto up;
                          case DOWN: goto down;
                          case LEFT:
                                left:
                                if(j <= 0)
                                     break;
                                 j--;
                                 restore_paren_buffer(j);
                                 emphasis_lparen_buffer(j);
                                 emphasis_rparen_buffer(j);
                                 ESCMVLEFT(j+3);
                                 break;

                          case RIGHT:
                                 right:
                                 if(buffer[j][0] == 0)
                                    break;
                                 j++;
                                 restore_paren_buffer(j);
                                 emphasis_lparen_buffer(j);
                                 emphasis_rparen_buffer(j);
                                 ESCMVLEFT(j+3);
                                 break;

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
        c = getch();
        goto loop;
        pos=0;
    }
   exit:
   return(buffer[pos++][0]);
}
