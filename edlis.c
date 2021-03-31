#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "edlis.h"

//-----editor-----
int ed_hight;
int ed_width;
int ed_scroll;
int ed_footer;
int ed_row;
int ed_col;
int ed_start;
int ed_end;
int ed_ins = 1;
int ed_tab = 0;
int ed_indent = 1;
int ed_name = NIL;
char ed_data[ROW_SIZE][COL_SIZE];
char ed_copy[COPY_SIZE][COL_SIZE];
int ed_lparen_row;
int ed_lparen_col;
int ed_rparen_row;
int ed_rparen_col;
int ed_clip_start;
int ed_clip_end;
int ed_copy_end;
char ed_candidate[50][30];
int ed_candidate_pt;
int ed_syntax_color = 1;   //default red
int ed_builtin_color = 6;  //default cyan
int ed_extended_color = 5; //default magenta
int ed_string_color = 3;   //default yellow
int ed_comment_color = 4;  //default blue
int ed_incomment = -1;     // #|...|# comment
int ctrl = 0;
int modify_flag = 0;

//special form token
char special[40][12] = {
{"defun"},{"defmacro"},{"defglobal"},{"defdynamic"},{"defconstant"},
{"let"},{"let*"},{"case"},{"while"},{"progn"},{"defmodule"},{"defpublic"},
};
//syntax token
char syntax[60][30] = {
{"lambda"},{"labels"},{"flet"},{"let"},{"let*"},{"setq"},{"setf"},{"defconstant"},{"defun"},{"defmacro"},{"defglobal"},{"defdynamic"},
{"dynamic"},{"function"},{"function*"},{"symbol-function"},{"class"},
{"and"},{"or"},{"if"},{"cond"},{"while"},{"for"},{"block"},{"return-from"},
{"case"},{"case-using"},{"progn"},{"defclass"},{"defgeneric"},{"defgeneric*"},
{"defmethod"},{"dynamic-let"},{"ignore-errors"},{"catch"},{"throw"},
{"tagbody"},{"go"},{"unwind-protect"},{"with-standard-input"},
{"with-standard-output"},{"with-error-output"},{"with-handler"},
{"convert"},{"with-open-input-file"},{"with-open-output-file"},
{"with-open-io-file"},{"the"},{"assure"},{"time"},{"trace"},{"untrace"},{"defmodule"},{"defpublic"},
};
//builtin token
char builtin[200][32] ={
{"-"},{"*"},{"/="},{"+"},{"<"},{"<="},{"="},{">"},{">="},
{"abs"},{"append"},{"apply"},{"aref"},{"arithmetic-error-operands"},
{"arithmetic-error-operation"},{"array-dimensions"},{"assoc"},{"atan"},
{"atan2"},{"atanh"},{"atom"},{"basic-array-p"},{"basic-array*-p"},
{"basic-vector-p"},{"call-next-method"},{"car"},{"cdr"},{"ceiling"},
{"cerror"},{"char-index"},{"char/="},{"char<"},{"char<="},{"char="},
{"char>"},{"char>="},{"characterp"},{"class-of"},{"close"},
{"condition-continuable"},{"cons"},{"consp"},{"constinue-condition"},
{"cos"},{"cosh"},{"create-array"},{"create-list"},{"create-string-input-stream"},
{"create-string-output-stream"},{"create-string"},{"create-vector"},{"create*"},
{"div"},{"domain-error-object"},{"domain-error-expected-class"},
{"dummyp"},{"elt"},{"eq"},{"eql"},{"equal"},{"error-output"},{"error"},
{"eval"},{"exp"},{"expt"},{"file-length"},{"file-position"},{"finish-output"},
{"float"},{"floatp"},{"floor"},{"format-char"},{"format-fresh-line"},
{"format-float"},{"format-integer"},{"format-object"},{"format-tab"},{"format"},
{"funcall"},{"functionp"},{"garef"},{"gbc"},{"gcd"},{"general-array*-p"},
{"general-vector-p"},{"generic-function-p"},{"gensym"},{"get-internal-run-time"},
{"get-internal-real-time"},
{"get-output-stream-string"},{"get-universal-time"},{"hdmp"},{"identity"},
{"initialize-object*"},{"input-stream-p"},{"instancep"},{"integerp"},
{"internal-time-units-per-second"},{"isqrt"},{"lcm"},{"length"},{"list"},
{"listp"},{"load"},{"log"},{"map-into"},{"mapc"},{"mapcar"},{"mapcan"},
{"mapcon"},{"mapl"},{"maplist"},{"max"},{"member"},{"min"},{"mod"},
{"next-method-p"},{"not"},{"nreverse"},{"null"},{"numberp"},
{"open-input-file"},{"open-io-file"},{"open-output-file"},{"open-stream-p"},
{"output-stream-p"},{"parse-error-string"},{"parse-error-expected-class"},
{"parse-number"},{"preview-char"},{"prin1"},{"print"},{"probe-file"},
{"property"},{"quit"},{"quotient"},{"read-byte"},{"read-char"},{"read-line"},
{"read"},{"reciprocal"},{"remove-property"},{"reverse"},{"round"},{"set-aref"},
{"set-car"},{"set-cdr"},{"set-elt"},{"set-file-position"},{"set-garef"},
{"set-property"},{"signal-condition"},{"simple-error-format-argument"},
{"simple-error-format-string"},{"sin"},{"sinh"},{"slot-value"},{"sqrt"},
{"standard-input"},{"standard-output"},{"stream-error-stream"},{"streamp"},
{"stream-ready-p"},{"string-append"},{"string-index"},{"string/="},{"string<"},{"string<="},{"string="},{"string>"},{"string>="},{"stringp"},{"subclassp"},
{"subseq"},{"symbolp"},{"tan"},{"tanh"},{"truncate"},{"undefined-entity-name"},
{"undefined-entity-namespace"},{"vector"},{"write-byte"}
};

//extended function
char extended[50][30] = {
{"random-real"},{"random"},{"mapvec"},{"hadamard"},{"logistic"},
{"nconc"},{"fast-address"},{"macroexpand-1"},{"backtrace"},
{"break"},{"edit"},{"set-editor"},{"wiringpi-setup-gpio"},{"delay-microseconds"},
{"wiringpi-spi-setup-ch-speed"},{"pwm-set-mode"},{"pwm-set-range"},
{"pwm-set-clock"},{"pin-mode"},{"digital-write"},{"digital-read"},
{"pwm-write"},{"pull-up-dn-control"},{"delay"},{"compile-file"},
{"c-include"},{"c-define"},{"c-lang"},{"c-option"}
};

int main(int argc, char *argv[]){
    int i,j;
    FILE *port;
    char *fname;

    (void)argc;
    fname = argv[1];
    signal(SIGINT, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGTSTP, signal_handler);
    for(i=0; i<ROW_SIZE; i++)
        for(j=0; j<COL_SIZE; j++)
            ed_data[i][j] = NUL;
    port = fopen(fname,"r");

    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    ed_hight = w.ws_row;
    ed_width = w.ws_col;
    ed_scroll = ed_hight - 4;
    ed_footer = ed_hight - 1;
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
        int c;
        
        c = fgetc(port);
        while(c != EOF){
            ed_data[ed_row][ed_col] = c;
            if(c == EOL){
                ed_row++;
                ed_col = 0;
                if(ed_row >= ROW_SIZE)
                    printf("row %d over max-row", ed_row);
            }
            else{
                ed_col++;
                if(ed_col >= COL_SIZE)
                   printf("row %d over max-column", ed_col);
            }
            c = getc(port);
        }
        ed_end = ed_row;
        ed_data[ed_end][0] = EOL;
        fclose(port);
    }
    ESCCLS;
    display_command(fname);
    display_screen();
    ed_row = ed_col = 0;
    edit_screen(fname);
    return(0);
}

void signal_handler(int signo){
   ctrl = signo;
}

void input(char* str){
    int c,pos;

    pos = 0;
    loop:
    c = getc(stdin);
    if(c == EOL){
        str[pos] = '\0';
        return;
    }
    else {
        str[pos] = c;
        pos++;
        goto loop;
    }
}

void edit_screen(char *fname){
    int c,i,k,type;
    char str1[20],str2[20];
    struct position pos;
    FILE *port;

    ESCMOVE(ed_row+2 - ed_start, ed_col+1);
    i = 0;
    loop:
    c = getch();
    switch(c){
        case 7:     ESCMOVE(2,1);    //ctrl+G help
                    ESCCLS1;
                    printf("Edlis help\n");        
                    printf("CTRL+F  move to right          CTRL+W  search word\n");
                    printf("CTRL+B  move to left           CTRL+R  replace word\n");
                    printf("CTRL+P  move to up             ESC TAB   complete name\n");
                    printf("CTRL+N  move to down           ESC <   goto top page\n");
                    printf("CTRL+J  end of line            ESC >   goto end page\n");
                    printf("CTRL+A  begin of line          ESC A   mark(or unmark) row for selection\n");
                    printf("CTRL+E  end of line            CTRL+D  delete one char\n");
                    printf("CTRL+V  page up\n");
                    printf("ESC V   page down\n");
                    printf("CTRL+O  save file\n");
                    printf("CTRL+T  insert file\n");
                    printf("CTRL+X  quit from editor\n");
                    printf("CTRL+K  cut selection\n");
                    printf("CTRL+U  uncut selection\n");
                    printf("CTRL+_ (or CTRL+L) goto line\n");
                    printf("\n  enter any key to exit help\n");
                    c = getch();
                    display_screen();
                    break;
        case 6:     //ctrl+F
                    goto right;
        case 2:     //ctrl+B
                    goto left;
        case 16:    //ctrl+P
                    goto up;
        case 14:    //ctrl+N
                    goto down;
        case 8:     //ctrl+H
                    goto backspace;
        case 20:     //ctrl+T
                    ESCREV;
                    ESCMOVE(ed_footer,1);
                    printf("                                            ");
                    ESCMOVE(ed_footer,1);
                    printf("filename: ");
                    input(str1);
                    ESCRST;
                    port = fopen(str1,"r");
                    if(port == NULL){
                        ESCREV;
                        ESCMOVE(ed_footer,1);
                        printf("                                            ");
                        ESCMOVE(ed_footer,1);
                        printf("%s not exist", str1);
                        ESCRST;
                        ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                        break;
                    }
                    c = fgetc(port);
                    while(c != EOF){
                        ed_data[ed_row][ed_col] = c;
                        if(c == EOL){
                            ed_row++;
                            ed_col = 0;
                            if(ed_row >= ROW_SIZE)
                                printf("row %d over max-row", ed_row);
                        }
                        else{
                            ed_col++;
                            if(ed_col >= COL_SIZE)
                                printf("row %d over max-column", ed_col);
                        }
                        c = getc(port);
                    }
                    ed_end = ed_row;
                    ed_data[ed_end][0] = EOL;
                    fclose(port);
                    display_screen();
                    modify_flag = 1;
                    break;
        case 4:     //ctrl+D
                    goto del;
        case 1:     //ctrl+A
                    ed_col = 0;
                    ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                    break; 
        case 5:     //ctrl+E
                    for(i=0;i<255;i++){
                       if(ed_data[ed_row][i] == NUL)
                            break; 
                    }
                    ed_col = i - 1;
                    ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                    modify_flag = 1;
                    break; 
        case 15:    save_data(fname); //ctrl+O
                    ESCMOVE(ed_footer,1);
                    ESCREV;
                    printf("saved");
                    ESCRST;
                    ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                    modify_flag = 0;
                    break; 
       case 11:     copy_selection(); //ctrl+K
                    delete_selection();
                    ed_row = ed_clip_start;
                    ed_clip_start = ed_clip_end = -1;
                    restore_paren();
                    display_screen();
                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                    modify_flag = 1;
                    break;
        case 21:    paste_selection(); //ctrl+U
                    restore_paren();
                    display_screen();
                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                    modify_flag = 1;
                    break;
        case 24:    //ctrl+X
                    if(modify_flag == 0){
                        ESCCLS; 
                        ESCMOVE(1,1);
                        return;
                    }
                    else{
                        retryX:
                        ESCREV;
                        ESCMOVE(ed_footer,1);
                        printf("save modified buffer? y/n/c ");
                        c = getch();
                        ESCRST;
                        if(c == 'y'){
                            save_data(fname);
                            ESCCLS; 
                            ESCMOVE(1,1);
                            return;
                        }
                        else if(c == 'n'){
                            ESCCLS; 
                            ESCMOVE(1,1);
                            return;
                        }
                        else if(c == 'c'){
                            ESCREV;
                            ESCMOVE(ed_footer,1);
                            printf("                                             ");
                            ESCRST;
                            ESCMOVE(ed_row+2-ed_start,ed_col+1);
                        }
                        else{
                            goto retryX;
                        }
                    }
                    break;
        case 22:    goto pageup;  //ctrl+V
        case 23:    //CTRL+W
                    ESCREV;
                    ESCMOVE(ed_footer,1);
                    printf("                                            ");
                    ESCMOVE(ed_footer,1);
                    printf("search: ");
                    input(str1);
                    ESCRST;
                    pos = find_word(str1);
                    if(pos.row == -1){
                        ESCREV;
                        ESCMOVE(ed_footer,1);
                        printf("can't find %s", str1);
                        ESCRST;
                        ESCMOVE(ed_row+2-ed_start,ed_col+1);
                        break;
                    }
                    ed_row = pos.row;
                    ed_col = pos.col;
                    ed_start = ed_row - ed_scroll/2;
                    if(ed_start < 0){
                        ed_start = 0;
                    }
	                display_screen();
                    ESCMOVE(ed_row+2-ed_start,ed_col+1);
                    break;

        case 18:    //CTRL+R
                    ESCREV;
                    ESCMOVE(ed_footer,1);
                    printf("                                            ");
                    ESCMOVE(ed_footer,1);
                    printf("search: ");
                    input(str1);
                    ESCMOVE(ed_footer,1);
                    printf("                                            ");
                    ESCMOVE(ed_footer,1);
                    printf("replace: ");
                    input(str2);
                    ESCRST;
                    retry1R:
                    pos = find_word(str1);
                    if(pos.row == -1){
                        ESCREV;
                        ESCMOVE(ed_footer,1);
                        printf("                      ");
                        ESCMOVE(ed_footer,1);
                        printf("can't find %s", str1);
                        ESCRST;
                        ESCMOVE(ed_row+2-ed_start,ed_col+1);
                        break;
                    }
                    else{
                        ed_row = pos.row;
                        ed_col = pos.col;
                        ed_start = ed_row - ed_scroll/2;
                        if(ed_start < 0){
                            ed_start = 0;
                        }
                        display_screen();
                        ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                        ESCREV;
                        printf("%s",str1);
                        ESCMOVE(ed_footer,1);
                        printf("                                            ");
                        ESCMOVE(ed_footer,1);
                        retry2R:
                        printf("replace? y/n ");
                        ESCRST;
                        c = getch();
                        if(c == 'y'){
                            ed_row = pos.row;
                            ed_col = pos.col;
                            replace_word(str1,str2);
                            display_screen();
                            modify_flag = 1;
                            ed_col++;
                            goto retry1R;
                        }
                        else if(c == 'n'){
                            display_screen();
                            ed_col++;
                            goto retry1R;
                        }
                        else{
                            goto retry2R;
                        }
                    }
                    break;
        case 12:             //CTRL+L
        case 31:    reinput: //CTRL+_
                    ESCREV;
                    ESCMOVE(ed_footer,1);
                    printf("          ");
                    ESCMOVE(ed_footer,1);
                    printf("line? ");
                    c = scanf("%d",&i);
                    c = getch();
                    ESCRST;
                    if(i < 0 || i > ed_end)
                        goto reinput;
                    ed_row = i - 1;
                    ed_col = 0;
                    ed_start = ed_row - ed_scroll/2;
                    if(ed_start < 0){
                        ed_start = 0;
                    }
	                display_screen();
                    ESCMOVE(ed_row+2-ed_start,ed_col+1);
                    break;
        case ESC:   c = getch();
                    switch(c){
                        case '<': goto home;
                        case '>': goto end;
                        case 'v': goto pagedn;
                        case 'a': if(ed_clip_start == -1){
                                        ed_clip_start = ed_clip_end = ed_row;
                                        ESCMOVE(ed_footer,1);
                                        ESCREV;
                                        printf("marked");
                                        ESCRST;
                                        goto loop;
                                          }
                                   else{
                                        ed_clip_start = ed_clip_end = -1;
                                        display_screen();
                                        ESCMOVE(ed_footer,1);
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
                                        #define CANDIDATE 3
                                        k = 0;
                                        ESCMOVE(ed_footer,1);
                                        next:
                                        ESCREV;
                                        for(i=0; i<CANDIDATE; i++){
                                            if(i+k >= ed_candidate_pt)
                                                 break;
                                             printf("%d:%s ", i+1, ed_candidate[i+k]);
                                        }
                                        if(ed_candidate_pt > k+CANDIDATE)
                                            printf("4:more");
                                        ESCRST;
                                        ESCRST;
                                        retry:
                                        c = getch();
                                        if(c == ESC)
                                             goto escape;
                                        i = c - '1';
                                        if(ed_candidate_pt > k+CANDIDATE && i == CANDIDATE){
                                            k = k+CANDIDATE;
                                            ESCMVLEFT(1);
                                            ESCCLSL;
                                            goto next;
                                        }
                                        if(i+k > ed_candidate_pt || i < 0)
                                            goto retry;
                                        if(c == EOL)
                                            goto retry;
                                        replace_fragment(ed_candidate[i+k]);
                                        escape:
                                        display_screen();
                                        ESCMOVE(ed_row+2 - ed_start, ed_col+1);
                         }
                         goto loop;
                    }
                    c = getch();
                    switch(c){
                        case UP:    up:
                                    if(ed_row == 0)
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
                                         if(ed_col >= ed_width){
                                            ed_col = ed_width - 1;
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
                                    modify_flag = 1;
                                    break;
                        case DOWN:  down:
                                    if(ed_row == ed_end)
                                        break;
                                    else if(ed_clip_start != -1 &&
                                            ed_row == ed_start+ed_scroll){
                                        if(ed_row == ed_clip_end)
                                            ed_clip_end++;
                                        else
                                            ed_clip_start++;
                                        ed_row++;
                                        ed_start++;
                                        display_screen();
                                        ESCMOVE(ed_row+2-ed_start,1);
                                    }
                                    else if(ed_row == ed_start+ed_scroll){
                                        ed_row = ed_row+10;
                                        ed_start = ed_start+10;
                                        if(ed_row > ed_end)
                                            ed_row = ed_start = ed_end-ed_scroll;
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
                                        if(ed_col >= ed_width){
                                            ed_col = ed_width - 1;
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
                        case LEFT:  left:
                                    if(ed_col == 0)
                                        break;
                                    ed_col--;
                                    if(ed_col <= ed_width - 1){
                                        if(ed_col == ed_width - 1){
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
                                    else if(ed_col >= ed_width){
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
                                    }
                                    break;
                        case RIGHT: right:
                                    if(ed_col == findeol(ed_row) || ed_col >= 159)
                                        break;
                                    ed_col++;
                                    if(ed_col < ed_width - 1){
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    }
                                    else {
                                        if(ed_col == ed_width){
                                             reset_paren();
                                             ESCCLSLA;
                                             ESCMOVE(ed_row+2 - ed_start,0);
                                             display_line(ed_row);
                                        }
                                        restore_paren();
                                        emphasis_lparen();
                                        emphasis_rparen();
                                        ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
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
                                    if(ed_end > ed_scroll)
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
                                    ed_start = ed_start - ed_scroll;
                                    if(ed_start < 0)
                                        ed_start = 0;
                                    ed_row = ed_start;
                                    display_screen();
                                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    break;
                        case PAGEDN:
                                    c = getch();
                                    pagedn:
                                    if(ed_end < ed_start + ed_scroll)
                                        break;
                                    ed_start = ed_start + ed_scroll;
                                    if(ed_start > ed_end)
                                        ed_start = ed_end - ed_scroll;
                                    ed_row = ed_start;
                                    display_screen();
                                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    break;
                        case DELETE:
                                    c = getch();
                                    del:
                                    if(ed_data[ed_row][ed_col] == EOL)
                                        break;
                                    ed_col++;
                                    backspace();
                                    display_screen();
                                    ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                                    modify_flag = 1;
                                    break;
                    }
                    break;
        case DEL:   backspace:
                    if(ed_row == 0 && ed_col == 0)
                        break;
                    else if(ed_col == 0){
                        restore_paren();
                        deleterow();
                        if(ed_row < ed_start)
                            ed_start = ed_row;
                        display_screen();
                        if(ed_row < ed_start+ed_scroll){
                            if(ed_col <= ed_width - 1)
                                ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                            else
                                ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
                        }
                        else{
                            if(ed_col <= ed_width - 1)
                                ESCMOVE(21,ed_col+1);
                            else
                                ESCMOVE(21,ed_col-ed_width+1);
                        }
                    }
                    else if(ed_col >= ed_width){
                        type = check_token(ed_row,ed_col-2);
                        if(type == 6) // #|...
                           ed_incomment = -1;
                        backspace();
                        display_screen();
                        if(ed_row < ed_start+ed_scroll)
                            ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
                        else
                            ESCMOVE(22,ed_col-ed_width+1);
                    }
                    else{
                        type = check_token(ed_row,ed_col-2);
                        if(type == 6) // #|...
                           ed_incomment = -1;
                        backspace();
                        display_screen();
                        if(ed_row < ed_start+ed_scroll)
                            ESCMOVE(ed_row+2 - ed_start,ed_col+1);
                        else
                            ESCMOVE(22,ed_col+1);
                    }
                    modify_flag = 1;
                    break;
        case EOL:   if(ed_indent == 1)
                        i = calc_tabs();
                    if(ed_row == ed_start+ed_scroll){
                        restore_paren();
                        insertrow();
                        ed_start++;
                        ed_row++;
                        ed_end++;
                        ed_col = 0;
                        display_screen();
                        ESCMOVE(22,1);
                    }
                    else if(ed_col >= ed_width){
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
                    modify_flag = 1;
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
                    modify_flag = 1;
                    break;
        default:    if(ed_ins){
                        if(ed_col > 159)
                            break;
                        else if(ed_col >= ed_width){
                            ESCCLSLA;
                            restore_paren();
                            insertcol();
                            ed_data[ed_row][ed_col] = c;
                            ESCMOVE(ed_row+2 - ed_start,1);
                            display_line(ed_row);
                            emphasis_lparen();
                            emphasis_rparen();
                            ed_col++;
                            ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
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
                        else if(ed_col >= ed_width){
                            if(ed_col == ed_width)
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
                    modify_flag = 1;
        }
    goto loop;
}

void display_command(char *fname){
    int i;
    ESCHOME;
    ESCREV;
    printf("Edlis %1.2f        File: %s    ", VERSION, fname);
    for(i=31;i<ed_width;i++)
        printf(" ");
    ESCRST;
    return;
}

void display_screen(){
    int line1,line2,i;

    ESCTOP;
    ESCCLS1;
    line1 = ed_start;
    line2 = ed_start + ed_scroll;
    if(line2 > ed_end)
        line2 = ed_end;

    while(line1 <= line2){
        display_line(line1);
        line1++;
    }
    ESCMOVE(ed_footer,1);
    ESCREV;
    for(i=0;i<ed_width-35;i++)
        printf(" ");
    printf("^G(help) ^X(quit) ^O(save) ^L(goto)");
    ESCRST;
    return;
}

void display_line(int line){
    int col,type;

    if(ed_row != line)
        col = 0;
    else if(ed_row == line && ed_col <= ed_width - 1)
        col = 0;
    else
        col = ed_width;

    while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
          ed_data[line][col] != EOL &&
          ed_data[line][col] != NUL){
          if(line >= ed_clip_start && line <= ed_clip_end)
                ESCREV;
          else
                ESCRST;

          if(ed_incomment != -1 && line >= ed_incomment){ //comment #|...|#
             ESCBOLD;
             setcolor(ed_comment_color);
             while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
                while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
                    while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
                    while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
                   while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
                   while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
                   while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
                    while(((ed_col <= ed_width - 1 && col <= ed_width - 1) || (ed_col >= ed_width && col <= 159)) &&
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
    while(i < COL_SIZE){
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
        for(j=0; j<COL_SIZE; j++){
            ed_data[i+1][j] = ed_data[i][j];
        }
    }
    k = 0;
    for(j=ed_col; j<COL_SIZE; j++){
        ed_data[ed_row+1][k] = ed_data[ed_row][j];
        k++;
    }
    ed_data[ed_row][ed_col] = EOL;
    return;
}

void deleterow(){
    int i,j,k,l;

    k = l = findeol(ed_row-1);
    for(j=0; j<COL_SIZE; j++){
        ed_data[ed_row-1][k] = ed_data[ed_row][j];
        k++;
        if(ed_data[ed_row][j] == EOL)
            break;
    }

    for(i=ed_row; i<ed_end; i++){
        for(j=0; j<COL_SIZE; j++){
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

    for(i=0; i<COL_SIZE; i++){
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
            pos.col = 0;
        }
        col = findeol(row);
    }

    nest = 0;
    limit = ed_row-ed_scroll;
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
    limit = ed_row+ed_scroll;
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

    if(ed_lparen_row != -1 && ed_lparen_row >= ed_start && ed_lparen_row <= ed_start+ed_scroll){
        if(ed_lparen_col <= ed_width - 1)
            ESCMOVE(ed_lparen_row+2 - ed_start,ed_lparen_col+1);
        else
            ESCMOVE(ed_lparen_row+2 - ed_start,ed_lparen_col-ed_width+1);
        ESCBORG;
        printf("(");
        ed_lparen_row = -1;
    }
    if(ed_rparen_row != -1 && ed_rparen_row >= ed_start && ed_rparen_row <= ed_start+ed_scroll){
        if(ed_rparen_col <= ed_width - 1)
            ESCMOVE(ed_rparen_row+2 - ed_start,ed_rparen_col+1);
        else
            ESCMOVE(ed_rparen_row+2 - ed_start,ed_rparen_col-ed_width+1);
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
    if(ed_col <= ed_width - 1 && pos.col <= ed_width - 1){
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
    else if(ed_col >= ed_width && pos.col >= ed_width){
        if(pos.row != -1){
            ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
            ESCBCYAN;
            printf(")");
            ESCBORG;
            if(pos.row >= ed_start){
                ESCMOVE(pos.row+2 - ed_start,pos.col-ed_width+1);
                ESCBCYAN;
                printf("(");
            }
            ed_lparen_row = pos.row;
            ed_lparen_col = pos.col;
            ed_rparen_row = ed_row;
            ed_rparen_col = ed_col;
            ESCBORG;
        }
        ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
    }
}

void emphasis_rparen(){
    struct position pos;

    if(ed_data[ed_row][ed_col] != '(')
        return;

    pos = findrparen(1);
    if(ed_col <= ed_width - 1 && pos.col <= ed_width - 1){
        if(pos.row != -1){
            ESCMOVE(ed_row+2 - ed_start,ed_col+1);
            ESCBCYAN;
            printf("(");
            ESCBORG;
            if(pos.row <= ed_start+ed_scroll){
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
    else if(ed_col >= ed_width && pos.col >= ed_width){
        if(pos.row != -1){
            ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
            ESCBCYAN;
            printf("(");
            ESCBORG;
            if(pos.row <= ed_start+ed_scroll){
                ESCMOVE(pos.row+2 - ed_start,pos.col-ed_width+1);
                ESCBCYAN;
                printf(")");
            }
            ed_rparen_row = pos.row;
            ed_rparen_col = pos.col;
            ed_lparen_row = ed_row;
            ed_lparen_col = ed_col;
            ESCBORG;
        }
    ESCMOVE(ed_row+2 - ed_start,ed_col-ed_width+1);
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


void save_data(char *fname){
    int row,col;
    FILE *port;

    port = fopen(fname,"w");
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
        while(ed_data[row][col] != ' ' && ed_data[row][col] > ' ')
            col++;

        while(ed_data[row][col] == ' ')
            col++;
    }
    return(col);
}


void remove_headspace(int row){
    int col,i,j,k;

    (void)row;
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
        return(pos.col+4);
    else
        return(findnext(pos.row,pos.col+1));

    return(0); //dammy
}

void copy_selection(){
    int i,j,k;

    if(ed_clip_end - ed_clip_start > COPY_SIZE)
        return;

    j = 0;
    for(i=ed_clip_start; i<=ed_clip_end; i++){
        for(k=0; k<ed_width; k++)
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
    char str[ed_width];
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

struct position find_word(char* word){
    int i,j,k,len;
    struct position pos;
    char* word1; 

    i = ed_row;
    j = ed_col;
    word1 = word;
    len = strlen(word);
    while(i<=ed_end+1){
        while(j<COL_SIZE){
            if(ed_data[i][j] == NUL)
                goto next1;
            k = j;
            while(k<j+len){
                if(ed_data[i][k] != *word){
                    goto next2;
                }
                word++;
                k++;
            }
            pos.row = i;
            pos.col = j;
            return(pos);
            
            next2:
            j++;
            word = word1;
        }
        next1:
        i++;
        j = 0;
    }
    //can't find word
    pos.row = -1;
    pos.col = 0;
    return(pos);
}


void replace_word(char* str1, char* str2){
    int len1,len2,i,j;

    len1 = strlen(str1);
    len2 = strlen(str2);

    if(len1 == len2){
        for(i=0;i<len1;i++){
            ed_data[ed_row][ed_col] = *str2;
            ed_col++;
            str2++;
        }
    }
    else if (len1 > len2){
        i = ed_col + len1;
        j = len1 - len2;
        while(ed_data[ed_row][i] != NUL){
            ed_data[ed_row][i-j] = ed_data[ed_row][i];
            i++; 
        }
        ed_data[ed_row][i] = NUL;

        for(i=0;i<len2;i++){
            ed_data[ed_row][ed_col+i] = *str2;
            str2++;
        }
    }
    else { //len1 < len2
        i = findeol(ed_row);
        j = len2 - len1;
        while(i >= ed_col+len1){
            ed_data[ed_row][i+j] = ed_data[ed_row][i];
            i--; 
        }
        ed_data[ed_row][i] = NUL;

        for(i=0;i<len2;i++){
            ed_data[ed_row][ed_col+i] = *str2;
            str2++;
        }
    }
}
