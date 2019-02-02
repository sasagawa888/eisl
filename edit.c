#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "eisl.h"

//----editor----

int f_set_editor(int arglist){
        int arg1,arg2;

        if(length(arglist) != 2)
                error(ILLEGAL_ARGS,"EDIT-SET",arglist);
        arg1 = car(arglist);
        arg2 = cadr(arglist);
        if(arg1 == makesym("REPL")){
            if(arg2 == makesym("ON"))
                repl_flag = 1;
            else if(arg2 == makesym("OFF"))
                repl_flag = 0;
        }
        else if(arg1 == makesym("INDENT") && arg2 == makesym("AUTO"))
                ed_indent = 1;
        else if(arg1 == makesym("INDENT") && arg2 == makesym("MANUAL"))
                ed_indent = 0;
        else if(arg1 == makesym("TAB")){
                if(arg2 == makesym("LISP"))
                        ed_tab = 0;
                else if(integerp(arg2) && GET_INT(arg2) == 2)
                        ed_tab = 2;
                else if(integerp(arg2) && GET_INT(arg2) == 4)
                        ed_tab = 4;
                else if(integerp(arg2) && GET_INT(arg2) == 8)
                        ed_tab = 8;
        }
                else if(arg1 == makesym("SYNTAX-COLOR"))
                        ed_syntax_color = GET_INT(arg2);
                else if(arg1 == makesym("BUILTIN-COLOR"))
                        ed_builtin_color = GET_INT(arg2);
                else if(arg1 == makesym("EXTENDED-COLOR"))
                        ed_extended_color = GET_INT(arg2);
                else if(arg1 == makesym("STRING-COLOR"))
                        ed_string_color = GET_INT(arg2);
                else if(arg1 == makesym("COMMENT-COLOR"))
                        ed_comment_color = GET_INT(arg2);
        else
                return(NIL);
        
        return(T);
}

int f_edit(int arglist){
    int arg1,c,i,j;
    FILE *port;
    
    if(length(arglist) != 1)
        error(ILLEGAL_ARGS,"EDIT",arglist);
    arg1 = car(arglist);
    if(nullp(arg1)){
        if(ed_name != NIL){
             arg1 = ed_name;
             ed_row = 0;
             ed_col = 0;
             ed_start = 0;
             ed_lparen_row = -1;
             ed_rparen_row = -1;
             ed_clip_start = -1;
             ed_clip_end = -1;        
             goto skip;
        }
        else
             return(NIL);
    }
    ed_name = arg1;
    for(i=0; i<1000; i++)
        for(j=0; j<100; j++)
            ed_data[i][j] = NUL;
    port = fopen(GET_NAME(arg1),"r");
    ed_row = 0;
    ed_col = 0;
    ed_start = 0;
    ed_end = 0;
    ed_lparen_row = -1;
    ed_rparen_row = -1;
    ed_clip_start = -1;
    ed_clip_end = -1;
    ed_data[0][0] = EOL;
    if(port != NULL){
        c = fgetc(port);
        while(c != EOF){
            ed_data[ed_row][ed_col] = c;
            if(c == EOL){
                ed_row++;
                ed_col = 0;
                if(ed_row >= 1000)
                    error(OUT_OF_RANGE,"EDIT over max-row", makeint(ed_row));
            }
            else{
                ed_col++;
                if(ed_col >= 160)
                   error(OUT_OF_RANGE,"EDIT over max-column", makeint(ed_col)); 
            }
            c = getc(port);
        }
        ed_end = ed_row;
        ed_data[ed_end][0] = EOL;
        fclose(port);
    }
    skip:
    ESCCLS;
    display_command(arg1);
    display_screen();
    ed_row = ed_col = 0;
    edit_screen(arg1); 
    return(T);
}

void edit_screen(int name){
    int c,i,type;
    
    ESCMOVE(ed_row+2 - ed_start, ed_col+1);
    i = 0;
    loop:
    c = getch();
    switch(c){
        case 8:     break;           //ctrl+H discard
        case 7:     ESCMOVE(2,1);    //ctrl+g help
                    ESCCLS1;
                    printf("This editor is referring to the nano editor.\n");
                    printf("(edit filename)  invoke editor\n");
                    printf("(edit nil)       invoke editor again\n");
                    printf("CTRL+Y  page up\n");
                    printf("CTRL+V  page down\n");
                    printf("CTRL+O  save file\n");
                    printf("CTRL+X  quit from editor and load program\n");
                    printf("CTRL+K  cut selection\n");
                    printf("CTRL+U  uncut selection\n");
                    printf("CTRL+_ (or CTRL+L) goto line\n");
                    printf("ESC TAB   complete name\n");
                    printf("ESC |   goto top page\n");
                    printf("ESC /   goto end page\n");
                    printf("ESC A   mark(or unmark) row for selection\n");
                    printf("\n  enter any key to exit help\n");
                    c = getch();
                    display_screen();
                    break;
        case 15:    save_data(name); //ctrl+O
                    ESCMOVE(23,1);
                    ESCREV;
                    printf("saved");
                    ESCRST;
                    ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                    break;
       case 11:     copy_selection(); //ctrl+K   
                    delete_selection();
                    ed_row = ed_clip_start;
                    ed_clip_start = ed_clip_end = -1;
                    restore_paren();
                    display_screen();
                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                    break;
        case 21:    paste_selection(); //ctrl+U
                    restore_paren();
                    display_screen();
                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                    break;
        case 25:    goto pageup;  //ctrl+Y
        case 22:    goto pagedn;  //ctrl+V
        case 24:    ESCCLS;       //ctrl+x
                    ESCMOVE(1,1);
                    f_load(list1(name)); 
                    return; 
        case 12:             //CTRL+L
        case 31:    reinput: //CTRL+_
                    ESCREV;
                    ESCMOVE(23,1);
                    printf("          ");
                    ESCMOVE(23,1);
                    printf("line? ");
                    c = scanf("%d",&i);
                    c = getch();
                    if(i < 0 || i > ed_end)
                        goto reinput;
                    ed_row = i;
                    ed_col = 0;
                    ed_start = ed_row -10;
                    if(ed_start < 0)
                        ed_start = 0;
	            display_screen();
                    ESCMOVE(ed_row+2-ed_start,ed_col+1);
                    break;
        case ESC:   c = getch();
                    switch(c){
                        case '|': goto home;
                        case '/': goto end;
                        case 'a': if(ed_clip_start == -1){
                                        ed_clip_start = ed_clip_end = ed_row;
                                        ESCMOVE(23,1);
                                        ESCREV;
                                        printf("marked");
                                        ESCRST;
                                        goto loop;
                                          }
                                   else{
                                        ed_clip_start = ed_clip_end = -1;
                                        display_screen();
                                        ESCMOVE(23,1);
                                        ESCREV;
                                        printf("unmark");
                                        ESCRST;
                                        goto loop;
                                   }
                        case TAB:   find_candidate(); //completion
                                    if(ed_candidate_pt == 0)
                                        break;                                  
                                    else if(ed_candidate_pt == 1){
                                        replace_fragment(ed_candidate[0]);
                                        ESCMOVE(ed_row+2 - ed_start, 0);
                                        display_line(ed_row);
                                        ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                                    }
                                    else{
                                        ESCMOVE(23,1);
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
                                        replace_fragment(ed_candidate[i]);
                                        escape:
                                        display_screen();
                                        ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                         }
                         goto loop;     
                    }
                    c = getch();
                    switch(c){
                        case UP:    if(ed_row == 0)
                                        break;
                                    else if(ed_clip_start != -1 &&
                                            ed_row == ed_start){
                                        if(ed_row == ed_clip_start)
                                             ed_clip_start--;
                                        else 
                                             ed_clip_end--;
                                        ed_row--;
                                        ed_start--;
                                        display_screen();
                                        ESCMOVE(ed_row+2-ed_start,1);
                                    }
                                    else if(ed_row == ed_start){
                                        ed_row = ed_row-10;
                                        ed_start = ed_start-10;
                                        if(ed_row < 0)
                                            ed_row = ed_start = 0;
                                        i = findeol(ed_row);
                                        if(ed_col >= i)
                                            ed_col = i;
                                        display_screen();
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(2,ed_col+1);
                                    }
                                    else if(ed_clip_start != -1){
                                        if(ed_row == ed_clip_start)
                                            ed_clip_start--;
                                        else 
                                            ed_clip_end--;
                                        ed_row--;
                                        i = findeol(ed_row);
                                        if(ed_col >= i)
                                            ed_col = i;
                                        display_screen();
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2-ed_start,ed_col+1);
                                    }
                                    else{
                                         if(ed_col >= 80){
                                            ed_col = 79;
                                            ESCCLSLA;
                                            ESCMOVE(ed_row+2 - ed_start,0);
                                            display_line(ed_row);
                                        }
                                        ed_row--;
                                        i = findeol(ed_row);
                                        if(ed_col >= i)
                                            ed_col = i;
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2-ed_start,ed_col+1);
                                    }
                                    break;
                        case EOL:   ed_row++;
                                    printf("%c", c);
                                    break;
                        case DOWN:  if(ed_row == ed_end)
                                        break;
                                    else if(ed_clip_start != -1 &&
                                            ed_row == ed_start+20){
                                        if(ed_row == ed_clip_end)
                                            ed_clip_end++;
                                        else 
                                            ed_clip_start++;
                                        ed_row++;
                                        ed_start++;
                                        display_screen();
                                        ESCMOVE(ed_row+2-ed_start,1);
                                    }
                                    else if(ed_row == ed_start+20){  
                                        ed_row = ed_row+10;
                                        ed_start = ed_start+10;
                                        if(ed_row > ed_end)
                                            ed_row = ed_start = ed_end-20;
                                        display_screen();
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        i = findeol(ed_row);
                                        if(ed_col >= i)
                                            ed_col = i;
                                        ESCMOVE(22,ed_col+1);
                                    }
                                    else if(ed_clip_start != -1){
                                        if(ed_row == ed_clip_end)
                                             ed_clip_end++;
                                        else 
                                             ed_clip_start++;
                                        ed_row++;
                                        i = findeol(ed_row);
                                        if(ed_col >= i)
                                            ed_col = i;
                                        display_screen();
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    }
                                    else{
                                        if(ed_col >= 80){
                                            ed_col = 79;
                                            ESCCLSLA;
                                            ESCMOVE(ed_row+2 - ed_start,0);
                                            display_line(ed_row);
                                        }
                                        ed_row++;
                                        i = findeol(ed_row);
                                        if(ed_col >= i)
                                            ed_col = i;
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    }
                                    break;
                        case LEFT:  if(ed_col == 0)
                                        break;
                                    ed_col--;
                                    if(ed_col <= 79){
                                        if(ed_col == 79){
                                             reset_paren();
                                             ESCCLSLA;
                                             ESCMOVE(ed_row+2 - ed_start,0);
                                             display_line(ed_row);
                                        }
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    }
                                    else if(ed_col >= 80){
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
                                    }
                                    break;
                        case RIGHT: if(ed_col == findeol(ed_row) || ed_col >= 159)
                                        break;
                                    ed_col++;
                                    if(ed_col < 79){            
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    }
                                    else if(ed_col >= 79){
                                        if(ed_col == 80){
                                             reset_paren();
                                             ESCCLSLA;
                                             ESCMOVE(ed_row+2 - ed_start,0);
                                             display_line(ed_row);
                                        }
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
                                    }
                                    break;
                        case HOME:  home: 
                                    ed_row = 0;
                                    ed_start = 0;
                                    display_screen();
                                    ESCMOVE(2,ed_col+1);
                                    break;
                        case END:   end:  
                                    ed_row = ed_end;
                                    if(ed_end > 20)
                                        ed_start = ed_row - 10;
                                    display_screen();
                                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    break;
                        case INSERT:
                                    c = getch(); 
                                    if(ed_ins == 1)
                                        ed_ins = 0;
                                    else
                                        ed_ins = 1;
                                    break;
                        case PAGEUP:                                    
                                    c = getch();
                                    pageup:
                                    ed_start = ed_start - 20;
                                    if(ed_start < 0)
                                        ed_start = 0;
                                    ed_row = ed_start;
                                    display_screen();
                                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    break;
                        case PAGEDN:                                    
                                    c = getch();
                                    pagedn:
                                    if(ed_end < ed_start + 20)
                                        break;
                                    ed_start = ed_start + 20;
                                    if(ed_start > ed_end)
                                        ed_start = ed_end - 20;
                                    ed_row = ed_start;
                                    display_screen();
                                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    break;
                        case DELETE:
                                    c = getch();
                                    if(ed_data[ed_row][ed_col] == EOL)
                                        break;
                                    ed_col++;
                                    backspace();
                                    display_screen();
                                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    break;
                    }
                    break;
        case DEL:   if(ed_row == 0 && ed_col == 0)
                        break;  
                    else if(ed_col == 0){
                        restore_paren();
                        deleterow();
                        if(ed_row < ed_start)
                            ed_start = ed_row;
                        display_screen();
                        if(ed_row < ed_start+20){
                            if(ed_col <= 79)
                                ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                            else
                                ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
                        }
                        else{
                            if(ed_col <= 79)
                                ESCMOVE(21,ed_col+1);
                            else
                                ESCMOVE(21,ed_col-80+1);
                        }
                    }
                    else if(ed_col >= 80){
                        type = check_token(ed_row,ed_col-2);
                        if(type == 6) // #|...
                           ed_incomment = -1;   
                        backspace();
                        display_screen();
                        if(ed_row < ed_start+20)
                            ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
                        else
                            ESCMOVE(22,ed_col-80+1);
                    }
                    else{
                        type = check_token(ed_row,ed_col-2);
                        if(type == 6) // #|...
                           ed_incomment = -1;   
                        backspace();
                        display_screen();
                        if(ed_row < ed_start+20)
                            ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                        else
                            ESCMOVE(22,ed_col+1);
                    }
                    break;
        case EOL:   if(ed_indent == 1)
                        i = calc_tabs();
                    if(ed_row == ed_start+20){
                        restore_paren();    
                        insertrow();
                        ed_start++;
                        ed_row++;
                        ed_end++;
                        ed_col = 0;
                        display_screen();
                        ESCMOVE(22,1);
                    }
                    else if(ed_col >= 80){
                        restore_paren();    
                        insertrow();
                        ed_start++;
                        ed_row++;
                        ed_end++;
                        ed_col = 0;
                        display_screen();
                        ESCMOVE(ed_row+2 - ed_start,1);
                    }
                    else{   
                        restore_paren();    
                        insertrow();
                        ed_row++;
                        ed_end++;
                        ed_col = 0;
                        display_screen();
                        ESCMOVE(ed_row+2 - ed_start,1);
                    }
                    if(ed_indent == 1){ 
                         ed_col = 0;
                         remove_headspace(ed_row);
                         softtabs(i);
                         display_screen();
                         ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                    }
                    break;
        case TAB:   if(ed_tab == 0){
                        ed_col = 0;
                        i = calc_tabs();
                        remove_headspace(ed_row);
                        softtabs(i);
                    }
                    else{
                        softtabs(ed_tab);
                    }
                    display_screen();
                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                    break;
        default:    if(ed_ins){
                        if(ed_col > 159)
                            break;
                        else if(ed_col >= 80){
                            ESCCLSLA;
                            restore_paren();
                            insertcol();
                            ed_data[ed_row][ed_col] = c;
                            ESCMOVE(ed_row+2 - ed_start,1);
                            display_line(ed_row);
                            emphasis_lparen();
                            emphasis_rparen();
                            ed_col++;
                            ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
                        }
                        else{
                            restore_paren();
                            insertcol();
                            ed_data[ed_row][ed_col] = c;
                            ESCMOVE(ed_row+2 - ed_start,1);
                            display_line(ed_row);
                            emphasis_lparen();
                            emphasis_rparen();
                            ed_col++;
                            ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                        }
                    }
                    else{
                        if(ed_col > 159)
                            break;
                        else if(ed_col >= 80){
                            if(ed_col == 80)
                                ESCCLSLA;
                            ed_data[ed_row][ed_col] = c;
                            printf("%c", c);
                            emphasis_lparen();
                            ed_col++;
                        }
                        else{
                            ed_data[ed_row][ed_col] = c;
                            printf("%c", c);
                            emphasis_lparen();
                            ed_col++;
                        }
                    }
        }
    goto loop;
}

void display_command(int name){
    ESCHOME;
    ESCREV;
    printf("EISL editor         File: %s                                                     ", GET_NAME(name));
    ESCRST;
    return;
}

void display_screen(){
    int line1,line2;
    
    ESCTOP;
    ESCCLS1;
    line1 = ed_start;
    line2 = ed_start + 20;
    if(line2 > ed_end)
        line2 = ed_end;
    
    while(line1 <= line2){
        display_line(line1);
        line1++;
    }
    ESCMOVE(23,1);
    ESCREV;
    printf("                                             ^G(help) ^X(quit) ^O(save) ^L(goto)");
    ESCRST;
    return;
}

void display_line(int line){
    int col,type;

    if(ed_row != line)
        col = 0;
    else if(ed_row == line && ed_col <= 79)
        col = 0;
    else
        col = 80;
   
    while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
          ed_data[line][col] != EOL &&
          ed_data[line][col] != NUL){
          if(line >= ed_clip_start && line <= ed_clip_end)
                ESCREV;
          else
                ESCRST;

          if(ed_incomment != -1 && line >= ed_incomment){ //comment #|...|#
             ESCBOLD;
             setcolor(ed_comment_color);
             while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                   ed_data[line][col] != EOL &&
                   ed_data[line][col] != NUL){
                       printf("%c", ed_data[line][col]);
                       col++;
                       if(ed_data[line][col-2] == '|' &&
                          ed_data[line][col-1] == '#'){
                             ed_incomment = -1;
                             ESCRST;
                             ESCFORG;
                             break;
                       }  
             }
             ESCRST;
             ESCFORG;
         }         
         else if(ed_data[line][col] == ' ' ||
                ed_data[line][col] == '(' ||
                ed_data[line][col] == ')' ){
            printf("%c", ed_data[line][col]);
            col++; 
         }
         else{
            type = check_token(line,col);
            if(type == 1){
                ESCBOLD;
                setcolor(ed_syntax_color);
                while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                      ed_data[line][col] != ' ' &&
                      ed_data[line][col] != '(' &&
                      ed_data[line][col] != ')' &&
                      ed_data[line][col] != NUL &&
                      ed_data[line][col] != EOL){
                        printf("%c", ed_data[line][col]);
                        col++;
                }
                ESCRST;
                ESCFORG;
                }
                else if(type == 2){
                        ESCBOLD;
                    setcolor(ed_builtin_color);
                    while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                          ed_data[line][col] != ' ' &&
                          ed_data[line][col] != '(' &&
                          ed_data[line][col] != ')' &&
                          ed_data[line][col] != NUL &&
                          ed_data[line][col] != EOL){
                        printf("%c", ed_data[line][col]);
                        col++;
                        }
                        ESCRST;
                        ESCFORG;
                }
                else if(type == 3){
                    ESCBOLD;
                    setcolor(ed_string_color);
                    printf("%c", ed_data[line][col]);
                    col++;
                    while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                          ed_data[line][col] != NUL &&
                          ed_data[line][col] != EOL){
                        printf("%c", ed_data[line][col]);
                        col++;
                        if(ed_data[line][col-1] == '"')
                            break;
                   }
                   ESCRST;
                   ESCFORG;

               }
               else if(type == 4){
                   ESCBOLD;
                   setcolor(ed_comment_color);
                   while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                         ed_data[line][col] != NUL &&
                         ed_data[line][col] != EOL){
                        printf("%c", ed_data[line][col]);
                        col++;
                   }
                   ESCRST;
                   ESCFORG;
               }
               else if(type == 5){
                   ESCBOLD;
                   setcolor(ed_extended_color);
                   while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                          ed_data[line][col] != ' ' &&
                          ed_data[line][col] != '(' &&
                          ed_data[line][col] != ')' &&
                          ed_data[line][col] != NUL &&
                          ed_data[line][col] != EOL){
                        printf("%c", ed_data[line][col]);
                        col++;
                   }
                   ESCRST;
                   ESCFORG;
               }
               else if(type == 6){ //comment #|...|#
                   ESCBOLD;
                   setcolor(ed_comment_color);
                   ed_incomment = line;
                   while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                         ed_data[line][col] != EOL &&
                         ed_data[line][col] != NUL){
                             printf("%c", ed_data[line][col]);
                             col++;
                             if(ed_data[line][col-2] == '|' &&
                                ed_data[line][col-1] == '#'){
                                 ed_incomment = -1;
                                 ESCRST;
                                 ESCFORG;
                                 break;
                             }  
                   }
               }
               else{
                    while(((ed_col <= 79 && col <= 79) || (ed_col >= 80 && col <= 159)) && 
                          ed_data[line][col] != ' ' &&
                          ed_data[line][col] != '(' &&
                          ed_data[line][col] != ')' &&
                          ed_data[line][col] != NUL &&
                          ed_data[line][col] != EOL){
                       printf("%c", ed_data[line][col]);
                       col++;
                    }
               }
                }
        }
    printf("%c",EOL);
    ESCRST;
    return;
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

void backspace(){
    int i;
    
    if(ed_data[ed_row][ed_col-1] == ')' ){
        ed_lparen_row = -1;     
        ed_rparen_row = -1;
    }
    i = ed_col;
    while(i <= 160){
        ed_data[ed_row][i-1] = ed_data[ed_row][i]; 
        i++;
    }
    ed_col--;
    return;
}

void insertcol(){
    int i;
    
    i = findeol(ed_row);
    while(i >= ed_col ){
        ed_data[ed_row][i+1] = ed_data[ed_row][i]; 
        i--;
    }
    return;
}

void insertrow(){
    int i,j,k;

    for(i=ed_end; i>=ed_row; i--){
        for(j=0; j<160; j++){
            ed_data[i+1][j] = ed_data[i][j];
        }
    } 
    k = 0;
    for(j=ed_col; j<160; j++){
        ed_data[ed_row+1][k] = ed_data[ed_row][j];
        k++;
    }
    ed_data[ed_row][ed_col] = EOL;
    return;
}

void deleterow(){
    int i,j,k,l;

    k = l = findeol(ed_row-1);
    for(j=0; j<160; j++){
        ed_data[ed_row-1][k] = ed_data[ed_row][j];
        k++;
        if(ed_data[ed_row][j] == EOL)
            break;
    }
    
    for(i=ed_row; i<ed_end; i++){
        for(j=0; j<160; j++){
            ed_data[i][j] = ed_data[i+1][j];
        } 
    }
    ed_row--;
    ed_end--;
    ed_col = l;
    return; 
}



int findeol(int row){
    int i;

    for(i=0; i<160; i++){
        if(ed_data[row][i] == EOL)
            return(i);  
    }
    return(-1);
}

struct position findlparen(int bias){
    int nest,row,col,limit;
    struct position pos;
    
    row = ed_row;
    if(ed_col != 0)
        col = ed_col - bias;
    else{
        row--;
        if(row < 0){
            pos.row = -1; //not found
            pos.col = 0;
        }
        col = findeol(row);
    }
        
    nest = 0;
    limit = ed_row-20;
    if(limit < 0)
        limit = 0;
    
    while(row >= limit){
        if(ed_data[row][col] == '(' && nest == 0)
            break;
        else if(ed_data[row][col] == ')')
            nest++;
        else if(ed_data[row][col] == '(')
            nest--;
        

        if(col == 0){
            row--;
            col = findeol(row);
        }
        else{
            col--;
        }   
    }
    if(row >= limit){
        pos.row = row;
        pos.col = col;
    }
    else{
        pos.row = -1;
        pos.col = 0;
    }
    return(pos);    
}

struct position findrparen(int bias){
    int nest,row,col,limit;
    struct position pos;
    
    row = ed_row;
    col = ed_col + bias;
    nest = 0;
    limit = ed_row+20;
    if(limit > ed_end)
        limit = ed_end;
    
    while(row < limit){
        if(ed_data[row][col] == ')' && nest == 0)
            break;
        else if(ed_data[row][col] == '(')
            nest++;
        else if(ed_data[row][col] == ')')
            nest--;
        

        if(col == findeol(row)){
            row++;
            col = 0;
        }
        else{
            col++;
        }   
    }
    if(row < limit){
        pos.row = row;
        pos.col = col;
    }
    else{
        pos.row = -1;
        pos.col = 0;
    }
    return(pos);    
}

void reset_paren(){
    ed_lparen_row = -1;
    ed_rparen_row = -1;
}

void restore_paren(){
    
    if(ed_lparen_row != -1 && ed_lparen_row >= ed_start && ed_lparen_row <= ed_start+20){
        if(ed_lparen_col <= 79)
            ESCMOVE(ed_lparen_row+2 - ed_start,ed_lparen_col+1);
        else
            ESCMOVE(ed_lparen_row+2 - ed_start,ed_lparen_col-80+1);
        ESCBORG;
        printf("(");
        ed_lparen_row = -1;
    }
    if(ed_rparen_row != -1 && ed_rparen_row >= ed_start && ed_rparen_row <= ed_start+20){
        if(ed_rparen_col <= 79)
            ESCMOVE(ed_rparen_row+2 - ed_start,ed_rparen_col+1);
        else
            ESCMOVE(ed_rparen_row+2 - ed_start,ed_rparen_col-80+1);
        ESCBORG;
        printf(")");
        ed_rparen_row = -1;
    }
}

void emphasis_lparen(){
    struct position pos;

    if(ed_data[ed_row][ed_col] != ')')
        return;
    
    pos = findlparen(1);
    if(ed_col <= 79 && pos.col <= 79){
        if(pos.row != -1){
            ESCMOVE(ed_row+2 - ed_start,ed_col+1);
            ESCBCYAN;
            printf(")");
            ESCBORG;
            if(pos.row >= ed_start){
                ESCMOVE(pos.row+2 - ed_start,pos.col+1);
                ESCBCYAN;
                printf("(");
            }
            ed_lparen_row = pos.row;
            ed_lparen_col = pos.col;
            ed_rparen_row = ed_row;
            ed_rparen_col = ed_col;
            ESCBORG;
        }
        ESCMOVE(ed_row+2 - ed_start,ed_col+1);
    }
    else if(ed_col >= 80 && pos.col >= 80){
        if(pos.row != -1){
            ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
            ESCBCYAN;
            printf(")");
            ESCBORG;
            if(pos.row >= ed_start){
                ESCMOVE(pos.row+2 - ed_start,pos.col-80+1);
                ESCBCYAN;
                printf("(");
            }
            ed_lparen_row = pos.row;
            ed_lparen_col = pos.col;
            ed_rparen_row = ed_row;
            ed_rparen_col = ed_col;
            ESCBORG;
        }
        ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
    }
}

void emphasis_rparen(){
    struct position pos;

    if(ed_data[ed_row][ed_col] != '(')
        return;
    
    pos = findrparen(1);
    if(ed_col <= 79 && pos.col <= 79){
        if(pos.row != -1){
            ESCMOVE(ed_row+2 - ed_start,ed_col+1);
            ESCBCYAN;
            printf("(");
            ESCBORG;
            if(pos.row <= ed_start+20){ 
                ESCMOVE(pos.row+2 - ed_start,pos.col+1);
                ESCBCYAN;
                printf(")");
            }
            ed_rparen_row = pos.row;
            ed_rparen_col = pos.col;
            ed_lparen_row = ed_row;
            ed_lparen_col = ed_col;
            ESCBORG;
        }
    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
    }
    else if(ed_col >= 80 && pos.col >= 80){
        if(pos.row != -1){
            ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
            ESCBCYAN;
            printf("(");
            ESCBORG;
            if(pos.row <= ed_start+20){ 
                ESCMOVE(pos.row+2 - ed_start,pos.col-80+1);
                ESCBCYAN;
                printf(")");
            }
            ed_rparen_row = pos.row;
            ed_rparen_col = pos.col;
            ed_lparen_row = ed_row;
            ed_lparen_col = ed_col;
            ESCBORG;
        }
    ESCMOVE(ed_row+2 - ed_start,ed_col-80+1);
    }
}


void softtabs(int n){
    while(n > 0){
        insertcol();
        ed_data[ed_row][ed_col] = ' ';
        ed_col++;
        n--;
    }
}


void save_data(int arg1){
    int row,col;
    FILE *port;

    port = fopen(GET_NAME(arg1),"w");
    for(row=0; row<=ed_end; row++)
        for(col=0; col<100; col++){
            fputc(ed_data[row][col],port);
            if(ed_data[row][col] == EOL)
                break;
        }
    fclose(port);
}

int is_special(int row, int col){
    char str[80];
    int pos,i;

    pos = 0;
    while(ed_data[row][col] != ' ' &&
          ed_data[row][col] != '(' && 
          ed_data[row][col] >= ' '){
        str[pos] = ed_data[row][col];
        col++;
        pos++; 
    }
    str[pos] = NUL;
    if(pos == 0)
        return(0);
    for(i=0;i<40;i++){ 
        if(strcmp(special[i],str) == 0){
            return(1);
        }
    }
    return(0);
}

int findnext(int row, int col){ 
   if(ed_data[row][col] == '(')
      return(col);
   else{
        while(ed_data[row][col] != ' ' && ed_data[row][col] >= ' ')     
            col++;
                
        while(ed_data[row][col] == ' ' && ed_data[row][col] >= ' ')
            col++;
    }    
    return(col);
}


void remove_headspace(int row){
    int col,i,j,k;

    col = 0;
    while(ed_data[ed_row][col] == ' ')
        col++;
    k = findeol(ed_row);
    if(k == -1)// can't find
                k = 0;
    i = 0;
    for(j=col; j<=k; j++){
        ed_data[ed_row][i] = ed_data[ed_row][j];
        i++;
    }
    return;
}

int calc_tabs(){
    struct position pos;
    
    pos = findlparen(0);

        if(ed_data[ed_row][ed_col] == '(')
                return(0);

    if(pos.row == -1)
        return(0); //can't find left paren

    if(is_special(pos.row, pos.col+1))
        return(pos.col+2);
    else
        return(findnext(pos.row,pos.col+1));

    return(0); //dammy
}

void copy_selection(){
    int i,j,k;
    
    if(ed_clip_end - ed_clip_start > 500)
        return;

    j = 0;
    for(i=ed_clip_start; i<=ed_clip_end; i++){
        for(k=0; k<80; k++)
            ed_copy[j][k] = ed_data[i][k];
            j++;
    }
    ed_copy_end = j;
    return;
}

void paste_selection(){
    int i,j,k;
    
    if(ed_copy_end == 0)
        return;
    if(ed_end + ed_copy_end > 1000)
        return;
    
    for(i=ed_end; i>=ed_row; i--){
        for(j=0; j<100; j++){
            ed_data[i+ed_copy_end][j] = ed_data[i][j];
        }
    }
    ed_end = ed_end + ed_copy_end;
    ed_data[ed_end][0] = EOL;

    k = ed_row;
    for(i=0; i<ed_copy_end; i++){
        for(j=0; j<100; j++){
            ed_data[k][j] = ed_copy[i][j];
        }
        k++;
    }
    return;
}

void delete_selection(){
    int i,j,k;

    if(ed_clip_start == -1)
        return;
    k= ed_clip_end - ed_clip_start + 1;
    for(i=ed_clip_start; i<=ed_end; i++){
        for(j=0; j<100; j++){
            ed_data[i][j] = ed_data[i+k][j];
        }
    }
    ed_end = ed_end - k;
    ed_data[ed_end][0] = EOL;
    return;
}

int check_token(int row, int col){
    char str[80];
    int pos,i;

    pos = 0;
    if(ed_data[row][col] == '"')
        return(3); //string token
    else if(ed_data[row][col] == ';')
       return(4); //comment token
    while(ed_data[row][col] != ' ' &&
          ed_data[row][col] != '(' &&
          ed_data[row][col] != ')' &&
          ed_data[row][col] != NUL &&
          ed_data[row][col] != EOL){
        str[pos] = ed_data[row][col];
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

char *get_fragment(){
    static char str[80];
    int col,pos;

    col = ed_col-1;
        while(col >= 0 &&
                  ed_data[ed_row][col] != ' ' &&
                  ed_data[ed_row][col] != '(' &&
          ed_data[ed_row][col] != ')'){
                col--;
        }
        col++;
        pos = 0;
    while(ed_data[ed_row][col] != ' ' &&
          ed_data[ed_row][col] != '(' && 
          ed_data[ed_row][col] >= ' '){
        str[pos] = ed_data[ed_row][col];
        col++;
        pos++; 
    }
    str[pos] = NUL;
    return(str);
}

void find_candidate(){
    char* str;
    int i;
        
    str = get_fragment();
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

void replace_fragment(char* newstr){
        char* oldstr;
        int m,n;

        oldstr = get_fragment();
        m = strlen(oldstr);
        n = strlen(newstr);
        while(m>0){
                backspace();
                m--;
        }
        while(n>0){
                insertcol();
                ed_data[ed_row][ed_col] = *newstr;
                ed_col++;
                newstr++;
                n--;
        }
        return;
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
            case EOL: for(j=0;j<256;j++)
                          if(buffer[j][0] == 0)
                              break;
                      buffer[j][0] = c;
                      restore_paren_buffer(j);
                      printf("%c",c);
                      pos = 0;
                      goto exit;
            case DEL:  if(j <= 0)
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
            case 25:  //ctrl+Y
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
            case 22:  //ctrl+V
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
                                if(j <= 0)
                                     break;
                                 j--;
                                 restore_paren_buffer(j);
                                 emphasis_lparen_buffer(j);
                                 emphasis_rparen_buffer(j);
                                 ESCMVLEFT(j+3);
                                 break;
                          
                          case RIGHT: 
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


