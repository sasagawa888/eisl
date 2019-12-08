#include "fast.h"
jmp_buf c_EXIT[50];
jmp_buf c_REPL[50];
int f_GET_WEIGHT(int arglist);int GET_WEIGHT(int X);
int f_GET_TYPE(int arglist);int GET_TYPE(int X);
int f_GET_SEXP(int arglist);int GET_SEXP(int X);
int f_MEXP(int arglist);int MEXP();
int f_REPL(int arglist);int REPL();
int f_INITIALIZE(int arglist);int INITIALIZE();
int f_PROMPT(int arglist);int PROMPT();
int f_ERRORstar(int arglist);int ERRORstar(int MSG,int ARG);
int f_LOADstar(int arglist);int LOADstar(int FILE);
int f_PARSE(int arglist);int PARSE();
int f_MEXP_READ(int arglist);int MEXP_READ();
int f_FORMULA(int arglist);int FORMULA(int OPERAND1,int OPERATOR);
int f_FORMULA1(int arglist);int FORMULA1(int OPERAND1,int OPERAND2,int OPERATOR,int WEIGHT,int TYPE);
int f_FORMULA_READ(int arglist);int FORMULA_READ();
int f_CONVERT_TO_COND(int arglist);int CONVERT_TO_COND(int LS);
int f_CONVERT_TO_COND1(int arglist);int CONVERT_TO_COND1(int LS);
int f_MEXP_READ_LIST(int arglist);int MEXP_READ_LIST();
int f_SEXP_READ(int arglist);int SEXP_READ();
int f_SEXP_READ_LIST(int arglist);int SEXP_READ_LIST();
int f_GET_TOKEN(int arglist);int GET_TOKEN();
int f_CONVERT_TO_ATOM(int arglist);int CONVERT_TO_ATOM(int LS);
int f_CUT_BOTH_SIDE(int arglist);int CUT_BOTH_SIDE(int LS);
int f_CONVERT_TO_SYMBOL(int arglist);int CONVERT_TO_SYMBOL(int LS);
int f_CONVERT_TO_STRING(int arglist);int CONVERT_TO_STRING(int LS);
int f_UPPERCASE(int arglist);int UPPERCASE(int X);
int f_CONVERT_TO_INTEGER(int arglist);int CONVERT_TO_INTEGER(int LS);
int f_CONVERT_TO_FLOAT(int arglist);int CONVERT_TO_FLOAT(int LS);
int f_END_OF_FILE_P(int arglist);int END_OF_FILE_P(int X);
int f_DELIMITERP(int arglist);int DELIMITERP(int C);
int f_TERMINALP(int arglist);int TERMINALP(int C);
int f_OPERATOR_CHAR_P(int arglist);int OPERATOR_CHAR_P(int C);
int f_LEFT_PAREN_P(int arglist);int LEFT_PAREN_P(int C);
int f_RIGHT_PAREN_P(int arglist);int RIGHT_PAREN_P(int C);
int f_OPERATORP(int arglist);int OPERATORP(int X);
int f_SPACE_SKIP(int arglist);int SPACE_SKIP();
int f_GETC(int arglist);int GETC();
int f_UNGETC(int arglist);int UNGETC(int C);
int f_LOOK(int arglist);int LOOK();
int f_LOOK1(int arglist);int LOOK1();
int f_STRING_LIST_P(int arglist);int STRING_LIST_P(int LS);
int f_INTEGER_LIST_P(int arglist);int INTEGER_LIST_P(int LS);
int f_INTEGER_LIST_P1(int arglist);int INTEGER_LIST_P1(int LS);
int f_FLOAT_LIST_P(int arglist);int FLOAT_LIST_P(int LS);
int f_FLOAT_LIST_P1(int arglist);int FLOAT_LIST_P1(int LS);
int f_NUMBER_CHAR_P(int arglist);int NUMBER_CHAR_P(int X);
int f_GET_WEIGHT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GET_WEIGHT(fast_convert(arg1))));
}
int f_GET_TYPE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GET_TYPE(fast_convert(arg1))));
}
int f_GET_SEXP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GET_SEXP(fast_convert(arg1))));
}
int f_MEXP(int arglist){
return(fast_inverse(MEXP() ));
}
int f_REPL(int arglist){
return(fast_inverse(REPL() ));
}
int f_INITIALIZE(int arglist){
return(fast_inverse(INITIALIZE() ));
}
int f_PROMPT(int arglist){
return(fast_inverse(PROMPT() ));
}
int f_ERRORstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ERRORstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_LOADstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LOADstar(fast_convert(arg1))));
}
int f_PARSE(int arglist){
return(fast_inverse(PARSE() ));
}
int f_MEXP_READ(int arglist){
return(fast_inverse(MEXP_READ() ));
}
int f_FORMULA(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FORMULA(fast_convert(arg1),fast_convert(arg2))));
}
int f_FORMULA1(int arglist){
int arg1,arg2,arg3,arg4,arg5;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
return(fast_inverse(FORMULA1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5))));
}
int f_FORMULA_READ(int arglist){
return(fast_inverse(FORMULA_READ() ));
}
int f_CONVERT_TO_COND(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_COND(fast_convert(arg1))));
}
int f_CONVERT_TO_COND1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_COND1(fast_convert(arg1))));
}
int f_MEXP_READ_LIST(int arglist){
return(fast_inverse(MEXP_READ_LIST() ));
}
int f_SEXP_READ(int arglist){
return(fast_inverse(SEXP_READ() ));
}
int f_SEXP_READ_LIST(int arglist){
return(fast_inverse(SEXP_READ_LIST() ));
}
int f_GET_TOKEN(int arglist){
return(fast_inverse(GET_TOKEN() ));
}
int f_CONVERT_TO_ATOM(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_ATOM(fast_convert(arg1))));
}
int f_CUT_BOTH_SIDE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CUT_BOTH_SIDE(fast_convert(arg1))));
}
int f_CONVERT_TO_SYMBOL(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_SYMBOL(fast_convert(arg1))));
}
int f_CONVERT_TO_STRING(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_STRING(fast_convert(arg1))));
}
int f_UPPERCASE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(UPPERCASE(fast_convert(arg1))));
}
int f_CONVERT_TO_INTEGER(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_INTEGER(fast_convert(arg1))));
}
int f_CONVERT_TO_FLOAT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_FLOAT(fast_convert(arg1))));
}
int f_END_OF_FILE_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(END_OF_FILE_P(fast_convert(arg1))));
}
int f_DELIMITERP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DELIMITERP(fast_convert(arg1))));
}
int f_TERMINALP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(TERMINALP(fast_convert(arg1))));
}
int f_OPERATOR_CHAR_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(OPERATOR_CHAR_P(fast_convert(arg1))));
}
int f_LEFT_PAREN_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LEFT_PAREN_P(fast_convert(arg1))));
}
int f_RIGHT_PAREN_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(RIGHT_PAREN_P(fast_convert(arg1))));
}
int f_OPERATORP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(OPERATORP(fast_convert(arg1))));
}
int f_SPACE_SKIP(int arglist){
return(fast_inverse(SPACE_SKIP() ));
}
int f_GETC(int arglist){
return(fast_inverse(GETC() ));
}
int f_UNGETC(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(UNGETC(fast_convert(arg1))));
}
int f_LOOK(int arglist){
return(fast_inverse(LOOK() ));
}
int f_LOOK1(int arglist){
return(fast_inverse(LOOK1() ));
}
int f_STRING_LIST_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(STRING_LIST_P(fast_convert(arg1))));
}
int f_INTEGER_LIST_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INTEGER_LIST_P(fast_convert(arg1))));
}
int f_INTEGER_LIST_P1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INTEGER_LIST_P1(fast_convert(arg1))));
}
int f_FLOAT_LIST_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FLOAT_LIST_P(fast_convert(arg1))));
}
int f_FLOAT_LIST_P1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FLOAT_LIST_P1(fast_convert(arg1))));
}
int f_NUMBER_CHAR_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(NUMBER_CHAR_P(fast_convert(arg1))));
}
int GET_WEIGHT(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("WEIGHT")),Flist1(fast_inverse(X)))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int GET_TYPE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("TYPE")),Flist1(fast_inverse(X)))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int GET_SEXP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("SEXP")),Flist1(fast_inverse(X)))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int MEXP(){
int res;
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("INITIALIZE")),NIL));
res = REPL();
return(res);}
int REPL(){
int res;
REPLloop:
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("REPL"));
Fsetprop(Fmakesym("REPL"),i+1);
ret=setjmp(c_REPL[i]);if(ret == 0){
res = ({int res=NIL;
if(({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;
int S = fast_convert(PARSE());int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(S),Flist1(fast_inverse(Fcons(Fmakesym("QUIT"),NIL)))))) == NIL){
({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(S)))) && fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(S),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("LOAD")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~A~%")),Flist1(fast_inverse(Fapply(Fcar(Fmakesym("IGNORE-ERRORS")),Flist1(fast_inverse(LOADstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(S),Flist1(fast_inverse(fast_immediate(1))))))))))))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~A~%")),Flist1(fast_inverse(Fapply(Fcar(Fmakesym("IGNORE-ERRORS")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(S)))))))))))));}res;})
;
PROMPT();
temp1 = PARSE();
S = temp1;
}
({int res,i;
res = T;block_arg=res;
 i = Fgetprop(Fmakesym("REPL"));
Fsetprop(Fmakesym("REPL"),i-1);
longjmp(c_REPL[i-1],1);res;})
;res;});Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
res=catch_arg;}
res;}) != NIL){
res = T;}
else{
res = PROMPT();
{
goto REPLloop;};}
;res;});Fsetprop(Fmakesym("REPL"),i);
}
 else{
ret = 0;
res=block_arg;}
res;});
return(res);}
int INITIALIZE(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("BUFFER"),fast_inverse(NIL));res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("Meta expression translater~%"))))));
res = PROMPT();
return(res);}
int PROMPT(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("M> "))))));res;});
return(res);}
int ERRORstar(int MSG,int ARG){
int res;
if(CELLRANGE(MSG)) Fshelterpush(MSG);
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(MSG)))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~A")),Flist1(fast_inverse(ARG))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("~%"))))));
({int res;
 res = Fset_cdr(Fmakesym("BUFFER"),fast_inverse(NIL));res;});
({int res;
if(fast_not(fast_eq(fast_convert(fast_convert(Fcdr(Fmakesym("INPUT-STREAM")))),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-INPUT")),NIL))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("INPUT-STREAM")))))));}
 else res = NIL;res;})
;
({int res;
 res = Fset_cdr(Fmakesym("INPUT-STREAM"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-INPUT")),NIL))));res;});
res = ({int res,i;
res = NIL;catch_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;
if(CELLRANGE(ARG)) Fshelterpop();
if(CELLRANGE(MSG)) Fshelterpop();
return(res);}
int LOADstar(int FILE){
int res;
if(CELLRANGE(FILE)) Fshelterpush(FILE);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int EXP = fast_convert(NIL);({int res;
 res = Fset_cdr(Fmakesym("INPUT-STREAM"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("OPEN-INPUT-FILE")),Flist1(fast_inverse(FILE))))));res;});
({int res;
 res = EXP = PARSE();res;})
;
({int res;
while(fast_not((fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(EXP)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("STRING=")),Fcons(fast_inverse(EXP),Flist1(fast_inverse(Fmakestr("the end")))))))) !=NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(EXP))));
res = ({int res;
 res = EXP = PARSE();res;})
;};res;})
;
({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("INPUT-STREAM")))))));res;});
({int res;
 res = Fset_cdr(Fmakesym("INPUT-STREAM"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-INPUT")),NIL))));res;});
res = T;
res;})
;
if(CELLRANGE(FILE)) Fshelterpop();
return(res);}
int PARSE(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int EXP = fast_convert(MEXP_READ());int OPE = fast_convert(GET_TOKEN());int TERMINAL = fast_convert(NIL);res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(EXP)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("STRING=")),Fcons(fast_inverse(EXP),Flist1(fast_inverse(Fmakestr("the end"))))))) != NIL){
res = EXP;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(OPE)))) && fast_eq(fast_convert(OPE),fast_convert(Fmakesym("<=")))) != NIL){
res = ({int res;int RESULT = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("DEFUN")),Fcons(fast_inverse(fast_convert(fast_car(EXP))),Fcons(fast_inverse(fast_convert(fast_cdr(EXP))),Flist1(fast_inverse(MEXP_READ()))))))));({int res;
 res = TERMINAL = GET_TOKEN();res;})
;
({int res;
if(fast_not(TERMINALP(TERMINAL)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error expected period ")),Flist1(fast_inverse(TERMINAL)))));res;});}
 else res = NIL;res;})
;
res = RESULT;
res;})
;}
else if(TERMINALP(OPE) != NIL){
res = EXP;}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error ")),Flist1(fast_inverse(OPE)))));res;});}
;res;});
res;})
;
return(res);}
int MEXP_READ(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(GET_TOKEN());int RESULT = fast_convert(NIL);res = ({int res=NIL;
if(END_OF_FILE_P(TOKEN) != NIL){
res = TOKEN;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("["))))))) != NIL){
res = ({int res;
 res = RESULT = MEXP_READ_LIST();res;})
;
res = ({int res;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(RESULT),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(Fmakesym("->"))) != NIL){
res = CONVERT_TO_COND(RESULT);}
else{
res = RESULT;}res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) && (fast_eq(fast_convert(TOKEN),fast_convert(Fmakesym("LAMBDA"))) || fast_eq(fast_convert(TOKEN),fast_convert(Fmakesym("^"))))) != NIL){
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(GET_TOKEN()),Flist1(fast_inverse(Fmakechar("["))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error expected [")),Flist1(fast_inverse(TOKEN)))));}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(GET_TOKEN()),Flist1(fast_inverse(Fmakechar("["))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error expected ]")),Flist1(fast_inverse(TOKEN)))));}
 else res = NIL;res;})
;
res = ({int res;
 res = RESULT = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LAMBDA")),Fcons(fast_inverse(MEXP_READ_LIST()),Flist1(fast_inverse(MEXP_READ()))))));res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(GET_TOKEN()),Flist1(fast_inverse(Fmakechar("]"))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error expected ]")),Flist1(fast_inverse(TOKEN)))));}
 else res = NIL;res;})
;
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("["))))));res;}) != NIL){
res = GET_TOKEN();
res = Fcons(fast_inverse(RESULT),fast_inverse(MEXP_READ_LIST()));}
;res;});}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("["))))))) != NIL){
res = GET_TOKEN();
res = ({int res;
 res = RESULT = Fcons(fast_inverse(TOKEN),fast_inverse(MEXP_READ_LIST()));res;})
;
res = ({int res;
if(OPERATOR_CHAR_P(LOOK()) != NIL){
res = FORMULA(RESULT,GET_TOKEN());}
else{
res = RESULT;}res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) && OPERATOR_CHAR_P(LOOK())) != NIL){
res = FORMULA(TOKEN,GET_TOKEN());}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) != NIL){
res = TOKEN;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(TOKEN)))) && OPERATOR_CHAR_P(LOOK())) != NIL){
res = FORMULA(TOKEN,GET_TOKEN());}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("("))))))) != NIL){
res = ({int res;
 res = RESULT = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(SEXP_READ_LIST())))));res;})
;
res = ({int res;
if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("."))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar(";"))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("]")))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error expected ; or ] ")),Flist1(fast_inverse(RESULT)))));}
 else res = NIL;res;})
;
res = RESULT;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("\'"))))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(SEXP_READ())))));res;});}
else if(DELIMITERP(TOKEN) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("M-exp illegal object ")),Flist1(fast_inverse(TOKEN)))));res;});}
else{
res = TOKEN;}
;res;});
res;})
;
return(res);}
int FORMULA(int OPERAND1,int OPERATOR){
int res;
if(CELLRANGE(OPERAND1)) Fshelterpush(OPERAND1);
if(CELLRANGE(OPERATOR)) Fshelterpush(OPERATOR);
if(Ffreecell() < 900) Fgbc();
res = FORMULA1(OPERAND1,FORMULA_READ(),OPERATOR,GET_WEIGHT(OPERATOR),GET_TYPE(OPERATOR));
if(CELLRANGE(OPERATOR)) Fshelterpop();
if(CELLRANGE(OPERAND1)) Fshelterpop();
return(res);}
int FORMULA1(int OPERAND1,int OPERAND2,int OPERATOR,int WEIGHT,int TYPE){
int res;
int temp1,temp2,temp3,temp4,temp5;
FORMULA1loop:
if(CELLRANGE(OPERAND1)) Fshelterpush(OPERAND1);
if(CELLRANGE(OPERAND2)) Fshelterpush(OPERAND2);
if(CELLRANGE(OPERATOR)) Fshelterpush(OPERATOR);
if(CELLRANGE(WEIGHT)) Fshelterpush(WEIGHT);
if(CELLRANGE(TYPE)) Fshelterpush(TYPE);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(FORMULA_READ());res = ({int res=NIL;
if(END_OF_FILE_P(TOKEN) != NIL){
res = TOKEN;}
else if(DELIMITERP(TOKEN) != NIL){
res = UNGETC(TOKEN);
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(GET_SEXP(OPERATOR)),Fcons(fast_inverse(OPERAND1),Flist1(fast_inverse(OPERAND2))))));res;});}
else if((OPERATORP(TOKEN) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(OPERATOR))))) && fast_greaterp(fast_convert(WEIGHT),fast_convert(GET_WEIGHT(TOKEN)))) != NIL){
{
temp1 = OPERAND1;
temp2 = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(GET_SEXP(TOKEN)),Fcons(fast_inverse(OPERAND2),Flist1(fast_inverse(FORMULA_READ()))))));
temp3 = OPERATOR;
temp4 = WEIGHT;
temp5 = TYPE;
if(CELLRANGE(OPERAND1)) Fshelterpop();
if(CELLRANGE(OPERAND2)) Fshelterpop();
if(CELLRANGE(OPERATOR)) Fshelterpop();
if(CELLRANGE(WEIGHT)) Fshelterpop();
if(CELLRANGE(TYPE)) Fshelterpop();
OPERAND1 = temp1;
OPERAND2 = temp2;
OPERATOR = temp3;
WEIGHT = temp4;
TYPE = temp5;
goto FORMULA1loop;};}
else if((OPERATORP(TOKEN) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(OPERATOR))))) && fast_smallerp(fast_convert(WEIGHT),fast_convert(GET_WEIGHT(TOKEN)))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(GET_SEXP(OPERATOR)),Fcons(fast_inverse(OPERAND1),Flist1(fast_inverse(OPERAND2))))));
temp2 = FORMULA_READ();
temp3 = TOKEN;
temp4 = WEIGHT;
temp5 = TYPE;
if(CELLRANGE(OPERAND1)) Fshelterpop();
if(CELLRANGE(OPERAND2)) Fshelterpop();
if(CELLRANGE(OPERATOR)) Fshelterpop();
if(CELLRANGE(WEIGHT)) Fshelterpop();
if(CELLRANGE(TYPE)) Fshelterpop();
OPERAND1 = temp1;
OPERAND2 = temp2;
OPERATOR = temp3;
WEIGHT = temp4;
TYPE = temp5;
goto FORMULA1loop;};}
else if((OPERATORP(TOKEN) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(OPERATOR))))) && fast_eq(fast_convert(TYPE),fast_convert(Fmakesym("YFX"))) && fast_numeqp(fast_convert(GET_WEIGHT(TOKEN)),fast_convert(WEIGHT))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(GET_SEXP(OPERATOR)),Fcons(fast_inverse(OPERAND1),Flist1(fast_inverse(OPERAND2))))));
temp2 = FORMULA_READ();
temp3 = TOKEN;
temp4 = WEIGHT;
temp5 = TYPE;
if(CELLRANGE(OPERAND1)) Fshelterpop();
if(CELLRANGE(OPERAND2)) Fshelterpop();
if(CELLRANGE(OPERATOR)) Fshelterpop();
if(CELLRANGE(WEIGHT)) Fshelterpop();
if(CELLRANGE(TYPE)) Fshelterpop();
OPERAND1 = temp1;
OPERAND2 = temp2;
OPERATOR = temp3;
WEIGHT = temp4;
TYPE = temp5;
goto FORMULA1loop;};}
else if((OPERATORP(TOKEN) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(OPERATOR))))) && fast_eq(fast_convert(TYPE),fast_convert(Fmakesym("XFY"))) && fast_numeqp(fast_convert(GET_WEIGHT(TOKEN)),fast_convert(WEIGHT))) != NIL){
{
temp1 = OPERAND1;
temp2 = FORMULA1(OPERAND2,FORMULA_READ(),TOKEN,GET_WEIGHT(TOKEN),GET_TYPE(TOKEN));
temp3 = OPERATOR;
temp4 = WEIGHT;
temp5 = TYPE;
if(CELLRANGE(OPERAND1)) Fshelterpop();
if(CELLRANGE(OPERAND2)) Fshelterpop();
if(CELLRANGE(OPERATOR)) Fshelterpop();
if(CELLRANGE(WEIGHT)) Fshelterpop();
if(CELLRANGE(TYPE)) Fshelterpop();
OPERAND1 = temp1;
OPERAND2 = temp2;
OPERATOR = temp3;
WEIGHT = temp4;
TYPE = temp5;
goto FORMULA1loop;};}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error illegal formula")),Flist1(fast_inverse(TOKEN)))));res;});}
;res;});
res;})
;
if(CELLRANGE(TYPE)) Fshelterpop();
if(CELLRANGE(WEIGHT)) Fshelterpop();
if(CELLRANGE(OPERATOR)) Fshelterpop();
if(CELLRANGE(OPERAND2)) Fshelterpop();
if(CELLRANGE(OPERAND1)) Fshelterpop();
return(res);}
int FORMULA_READ(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(GET_TOKEN());res = ({int res=NIL;
if(END_OF_FILE_P(TOKEN) != NIL){
res = TOKEN;}
else if(DELIMITERP(TOKEN) != NIL){
res = TOKEN;}
else if(OPERATORP(TOKEN) != NIL){
res = TOKEN;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(TOKEN)))) != NIL){
res = TOKEN;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("["))))))) != NIL){
res = GETC();
res = Fcons(fast_inverse(TOKEN),fast_inverse(MEXP_READ_LIST()));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) != NIL){
res = TOKEN;}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error illegal formula element")),Flist1(fast_inverse(TOKEN)))));res;});}
;res;});
res;})
;
return(res);}
int CONVERT_TO_COND(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = LS;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(LS)))) && fast_smallerp(fast_convert(Flength(LS)),fast_convert(fast_immediate(3)))) != NIL){
res = LS;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(LS)))) && fast_eqgreaterp(fast_convert(Flength(LS)),fast_convert(fast_immediate(3))) && fast_not(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(Fmakesym("->"))))) != NIL){
res = LS;}
else{
res = Fcons(fast_inverse(Fmakesym("COND")),fast_inverse(CONVERT_TO_COND1(LS)));}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CONVERT_TO_COND1(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = NIL;}
else if(fast_smallerp(fast_convert(Flength(LS)),fast_convert(fast_immediate(3))) != NIL){
res = LS;}
else{
res = Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(CONVERT_TO_COND(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(2))))))))))))),fast_inverse(CONVERT_TO_COND1(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(LS)))))))));}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int MEXP_READ_LIST(){
int res;
MEXP_READ_LISTloop:
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(GET_TOKEN());int RESULT = fast_convert(NIL);res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("]"))))))) != NIL){
res = NIL;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("["))))))) != NIL){
res = Fcons(fast_inverse(MEXP_READ_LIST()),fast_inverse(MEXP_READ_LIST()));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar(";"))))))) != NIL){
{
goto MEXP_READ_LISTloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) && fast_eq(fast_convert(TOKEN),fast_convert(Fmakesym("->")))) != NIL){
res = Fcons(fast_inverse(TOKEN),fast_inverse(MEXP_READ_LIST()));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("["))))))) != NIL){
res = GET_TOKEN();
res = Fcons(fast_inverse(Fcons(fast_inverse(TOKEN),fast_inverse(MEXP_READ_LIST()))),fast_inverse(MEXP_READ_LIST()));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("("))))))) != NIL){
res = ({int res;
 res = RESULT = SEXP_READ_LIST();res;})
;
res = ({int res;
if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("-"))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar(";"))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("]")))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error expected ; or ] ")),Flist1(fast_inverse(RESULT)))));}
 else res = NIL;res;})
;
res = Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(RESULT)))))),fast_inverse(MEXP_READ_LIST()));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("\'"))))))) != NIL){
res = Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(SEXP_READ())))))),fast_inverse(MEXP_READ_LIST()));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(TOKEN)))) != NIL){
res = ({int res;
if(OPERATOR_CHAR_P(LOOK()) != NIL){
res = Fcons(fast_inverse(FORMULA(TOKEN,GET_TOKEN())),fast_inverse(MEXP_READ_LIST()));}
else{
res = Fcons(fast_inverse(TOKEN),fast_inverse(MEXP_READ_LIST()));}res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(TOKEN)))) != NIL){
res = ({int res;
if((OPERATOR_CHAR_P(LOOK()) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK1()),Flist1(fast_inverse(Fmakechar(">")))))))) != NIL){
res = Fcons(fast_inverse(FORMULA(TOKEN,GET_TOKEN())),fast_inverse(MEXP_READ_LIST()));}
else{
res = Fcons(fast_inverse(TOKEN),fast_inverse(MEXP_READ_LIST()));}res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(TOKEN)))) != NIL){
res = ({int res;
if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("-"))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar(";"))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar("]")))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("Syntax error expected ; or ] ")),Flist1(fast_inverse(TOKEN)))));}
 else res = NIL;res;})
;
res = Fcons(fast_inverse(TOKEN),fast_inverse(MEXP_READ_LIST()));}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR*")),Fcons(fast_inverse(Fmakestr("M-exp illegal object")),Flist1(fast_inverse(TOKEN)))));res;});}
;res;});
res;})
;
return(res);}
int SEXP_READ(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(GET_TOKEN());res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("("))))))) != NIL){
res = SEXP_READ_LIST();}
else{
res = TOKEN;}
;res;});
res;})
;
return(res);}
int SEXP_READ_LIST(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(NIL);int RESULT = fast_convert(NIL);({int res;
 res = TOKEN = GET_TOKEN();res;})
;
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar(")"))))))) != NIL){
res = NIL;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(TOKEN)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(TOKEN),Flist1(fast_inverse(Fmakechar("("))))))) != NIL){
res = Fcons(fast_inverse(SEXP_READ_LIST()),fast_inverse(SEXP_READ_LIST()));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar(".")))))) != NIL){
res = GET_TOKEN();
res = ({int res;
 res = RESULT = Fcons(fast_inverse(TOKEN),fast_inverse(SEXP_READ()));res;})
;
res = GET_TOKEN();
res = RESULT;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(TOKEN)))) != NIL){
res = Fcons(fast_inverse(TOKEN),fast_inverse(SEXP_READ_LIST()));}
;res;});
res;})
;
return(res);}
int GET_TOKEN(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;int TOKEN = fast_convert(NIL);int CHAR = fast_convert(NIL);({int res;
 res = CHAR = SPACE_SKIP();res;})
;
({int res;
if(END_OF_FILE_P(CHAR) != NIL){
({int res,i;
res = CHAR;block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;
({int res;
 res = CHAR = GETC();res;})
;
({int res;
if(END_OF_FILE_P(CHAR) != NIL){
({int res,i;
res = CHAR;block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;
res = ({int res=NIL;
if(DELIMITERP(CHAR) != NIL){
res = CHAR;}
else if(OPERATOR_CHAR_P(CHAR) != NIL){
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar("-")))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(LOOK()),Flist1(fast_inverse(Fmakechar(">"))))))) != NIL){
res = GETC();
res = Fmakesym("->");}
else{
res = CONVERT_TO_ATOM(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(CHAR)))));}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar("\"")))))) != NIL){
res = ({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;
res = ({int res;
while(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar("\""))))))) !=NIL){
({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;};res;})
;
res = ({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = CONVERT_TO_ATOM(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(TOKEN)))));}
else{
res = ({int res;
while((fast_not(DELIMITERP(CHAR)) && fast_not(OPERATOR_CHAR_P(CHAR))) !=NIL){
({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;};res;})
;
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar(".")))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))))))) && NUMBER_CHAR_P(LOOK())) != NIL){
res = ({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;
({int res;
while((fast_not(DELIMITERP(CHAR)) && fast_not(OPERATOR_CHAR_P(CHAR))) !=NIL){
({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;};res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar("+")))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(TOKEN))),Flist1(fast_inverse(Fmakechar("e"))))))) != NIL){
res = ({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;
({int res;
while((fast_not(DELIMITERP(CHAR)) && fast_not(OPERATOR_CHAR_P(CHAR))) !=NIL){
({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;};res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar("-")))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(TOKEN))),Flist1(fast_inverse(Fmakechar("e"))))))) != NIL){
res = ({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;
({int res;
while((fast_not(DELIMITERP(CHAR)) && fast_not(OPERATOR_CHAR_P(CHAR))) !=NIL){
({int res;
 res = TOKEN = Fcons(fast_inverse(CHAR),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = CHAR = GETC();res;})
;};res;})
;}
;res;});
res = UNGETC(CHAR);
res = CONVERT_TO_ATOM(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(TOKEN)))));}
;res;});
res;})
;Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
res=block_arg;}
res;});
return(res);}
int CONVERT_TO_ATOM(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(STRING_LIST_P(LS) != NIL){
res = CONVERT_TO_STRING(CUT_BOTH_SIDE(LS));}
else if(INTEGER_LIST_P(LS) != NIL){
res = CONVERT_TO_INTEGER(LS);}
else if(FLOAT_LIST_P(LS) != NIL){
res = CONVERT_TO_FLOAT(LS);}
else{
res = CONVERT_TO_SYMBOL(LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CUT_BOTH_SIDE(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(fast_convert(fast_cdr(LS))))))))))));res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CONVERT_TO_SYMBOL(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fconvert(fast_inverse(CONVERT_TO_STRING(LS)),Fmakesym("<SYMBOL>")));
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CONVERT_TO_STRING(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = Fmakestr("");}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(UPPERCASE(fast_convert(fast_car(LS)))),Fmakesym("<STRING>")))),Flist1(fast_inverse(CONVERT_TO_STRING(fast_convert(fast_cdr(LS))))))));res;});}res;})
;
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int UPPERCASE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int ASCII = fast_convert(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<INTEGER>"))));res = ({int res;
if((fast_eqgreaterp(fast_convert(ASCII),fast_convert(fast_immediate(97))) && fast_eqsmallerp(fast_convert(ASCII),fast_convert(fast_immediate(122)))) != NIL){
res = fast_convert(Fconvert(fast_inverse(fast_minus(fast_convert(ASCII),fast_convert(fast_immediate(32)))),Fmakesym("<CHARACTER>")));}
else{
res = X;}res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CONVERT_TO_INTEGER(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fconvert(fast_inverse(CONVERT_TO_STRING(LS)),Fmakesym("<INTEGER>")));
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CONVERT_TO_FLOAT(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fconvert(fast_inverse(CONVERT_TO_STRING(LS)),Fmakesym("<FLOAT>")));
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int END_OF_FILE_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("STRING=")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakestr("the end"))))))) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int DELIMITERP(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(C)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(C),Flist1(fast_inverse(Fcons(Fmakechar(" "),Fcons(Fmakechar("["),Fcons(Fmakechar("]"),Fcons(Fmakechar("("),Fcons(Fmakechar(")"),Fcons(Fmakechar(";"),Fcons(Fmakechar(","),Fcons(Fmakechar("\'"),Fcons(Fmakechar("."),NIL))))))))))))))) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int TERMINALP(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(C))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(C),Flist1(fast_inverse(Fmakechar("."))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int OPERATOR_CHAR_P(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(C)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(C),Flist1(fast_inverse(Fcons(Fmakechar("+"),Fcons(Fmakechar("-"),Fcons(Fmakechar("*"),Fcons(Fmakechar("/"),Fcons(Fmakechar("^"),NIL))))))))))) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int LEFT_PAREN_P(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(C)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Flist1(fast_inverse(Fmakechar("(")))))) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int RIGHT_PAREN_P(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(C)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Flist1(fast_inverse(Fmakechar(")")))))) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int OPERATORP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fcons(Fmakesym("+"),Fcons(Fmakesym("-"),Fcons(Fmakesym("*"),Fcons(Fmakesym("/"),Fcons(Fmakesym("^"),NIL))))))))));res;}) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SPACE_SKIP(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;int CHAR = fast_convert(NIL);({int res;
 res = CHAR = GETC();res;})
;
({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(CHAR)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("STRING=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakestr("the end"))))))) != NIL){
({int res,i;
res = CHAR;block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;
({int res;
while((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar(" ")))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakechar("	"))))))) !=NIL){
({int res;
 res = CHAR = GETC();res;})
;
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(CHAR)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("STRING=")),Fcons(fast_inverse(CHAR),Flist1(fast_inverse(Fmakestr("the end"))))))) != NIL){
({int res,i;
res = CHAR;block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;};res;})
;
res = UNGETC(CHAR);
res;})
;Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
res=block_arg;}
res;});
return(res);}
int GETC(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;int INPUT = fast_convert(NIL);int RESULT = fast_convert(NIL);({int res;
while(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))))));res;}) !=NIL){
({int res;
 res = INPUT = fast_convert(Fcallsubr(Fcar(Fmakesym("READ-LINE")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("INPUT-STREAM")))),Fcons(fast_inverse(NIL),Flist1(fast_inverse(Fmakestr("the end")))))));res;})
;
res = ({int res;
if(END_OF_FILE_P(INPUT) != NIL){
({int res,i;
res = Fmakestr("the end");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("BUFFER"),fast_inverse(fast_convert(Fconvert(fast_inverse(INPUT),Fmakesym("<LIST>")))));res;});}res;})
;};res;})
;
({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("BUFFER")))))),Flist1(fast_inverse(Fmakechar("!"))))));res;}) != NIL){
res = ({int res;
 res = INPUT = fast_convert(Fcallsubr(Fcar(Fmakesym("READ-LINE")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("INPUT-STREAM")))),Fcons(fast_inverse(NIL),Flist1(fast_inverse(Fmakestr("the end")))))));res;})
;
res = ({int res;
if(END_OF_FILE_P(INPUT) != NIL){
({int res,i;
res = Fmakestr("the end");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("BUFFER"),fast_inverse(fast_convert(Fconvert(fast_inverse(INPUT),Fmakesym("<LIST>")))));res;});}res;})
;}
;res;});
({int res;
 res = RESULT = fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("BUFFER")))));res;})
;
({int res;
 res = Fset_cdr(Fmakesym("BUFFER"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("BUFFER")))))));res;});
res = RESULT;
res;})
;Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
res=block_arg;}
res;});
return(res);}
int UNGETC(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("BUFFER"),fast_inverse(Fcons(fast_inverse(C),fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))))));res;});
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int LOOK(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;int MAX = fast_convert(Flength(fast_convert(Fcdr(Fmakesym("BUFFER")))));({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))))));res;}) != NIL){
({int res,i;
res = Fmakechar(".");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;
res = ({int res;
int POS = fast_convert(fast_immediate(0));int temp1;
while(fast_eqgreaterp(fast_convert(POS),fast_convert(MAX)) == NIL){
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))),Flist1(fast_inverse(POS)))))),Flist1(fast_inverse(Fmakechar(" "))))))) != NIL){
({int res,i;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))),Flist1(fast_inverse(POS)))));block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;
temp1 = fast_plus(fast_convert(POS),fast_convert(fast_immediate(1)));
POS = temp1;
}
res = NIL;res;});
res;})
;Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
res=block_arg;}
res;});
return(res);}
int LOOK1(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;int MAX = fast_convert(Flength(fast_convert(Fcdr(Fmakesym("BUFFER")))));({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))))));res;}) != NIL){
({int res,i;
res = Fmakechar(".");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;
res = ({int res;
int POS = fast_convert(fast_immediate(0));int temp1;
while(fast_eqgreaterp(fast_convert(POS),fast_convert(MAX)) == NIL){
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))),Flist1(fast_inverse(POS)))))),Flist1(fast_inverse(Fmakechar(" "))))))) != NIL){
({int res,i;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("BUFFER")))),Flist1(fast_inverse(fast_plus(fast_convert(POS),fast_convert(fast_immediate(1))))))));block_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;}
 else res = NIL;res;})
;
temp1 = fast_plus(fast_convert(POS),fast_convert(fast_immediate(1)));
POS = temp1;
}
res = NIL;res;});
res;})
;Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
res=block_arg;}
res;});
return(res);}
int STRING_LIST_P(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("\""))))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(LS))))))),Flist1(fast_inverse(Fmakechar("\""))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int INTEGER_LIST_P(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("+"))))));res;}) != NIL){
res = INTEGER_LIST_P1(fast_convert(fast_cdr(LS)));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("-")))))) != NIL){
res = INTEGER_LIST_P1(fast_convert(fast_cdr(LS)));}
else{
res = INTEGER_LIST_P1(LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int INTEGER_LIST_P1(int LS){
int res;
int temp1;
INTEGER_LIST_P1loop:
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = NIL;}
else if((NUMBER_CHAR_P(fast_convert(fast_car(LS))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(LS))))))) != NIL){
res = T;}
else if(fast_not(NUMBER_CHAR_P(fast_convert(fast_car(LS)))) != NIL){
res = NIL;}
else{
{
temp1 = fast_convert(fast_cdr(LS));
if(CELLRANGE(LS)) Fshelterpop();
LS = temp1;
goto INTEGER_LIST_P1loop;};}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int FLOAT_LIST_P(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_not(NUMBER_CHAR_P(fast_convert(fast_car(LS)))) != NIL){
res = NIL;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("+")))))) != NIL){
res = FLOAT_LIST_P1(fast_convert(fast_cdr(LS)));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("-")))))) != NIL){
res = FLOAT_LIST_P1(fast_convert(fast_cdr(LS)));}
else{
res = FLOAT_LIST_P1(LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int FLOAT_LIST_P1(int LS){
int res;
int temp1;
FLOAT_LIST_P1loop:
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = NIL;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar(".")))))) != NIL){
res = INTEGER_LIST_P(fast_convert(fast_cdr(LS)));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("e")))))) != NIL){
res = INTEGER_LIST_P(fast_convert(fast_cdr(LS)));}
else if(fast_not(NUMBER_CHAR_P(fast_convert(fast_car(LS)))) != NIL){
res = NIL;}
else{
{
temp1 = fast_convert(fast_cdr(LS));
if(CELLRANGE(LS)) Fshelterpop();
LS = temp1;
goto FLOAT_LIST_P1loop;};}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int NUMBER_CHAR_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR>=")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakechar("0"))))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR<=")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakechar("9"))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("GET-WEIGHT" , f_GET_WEIGHT);
(deftfunc)("GET-TYPE" , f_GET_TYPE);
(deftfunc)("GET-SEXP" , f_GET_SEXP);
(deftfunc)("MEXP" , f_MEXP);
(deftfunc)("REPL" , f_REPL);
(deftfunc)("INITIALIZE" , f_INITIALIZE);
(deftfunc)("PROMPT" , f_PROMPT);
(deftfunc)("ERROR*" , f_ERRORstar);
(deftfunc)("LOAD*" , f_LOADstar);
(deftfunc)("PARSE" , f_PARSE);
(deftfunc)("MEXP-READ" , f_MEXP_READ);
(deftfunc)("FORMULA" , f_FORMULA);
(deftfunc)("FORMULA1" , f_FORMULA1);
(deftfunc)("FORMULA-READ" , f_FORMULA_READ);
(deftfunc)("CONVERT-TO-COND" , f_CONVERT_TO_COND);
(deftfunc)("CONVERT-TO-COND1" , f_CONVERT_TO_COND1);
(deftfunc)("MEXP-READ-LIST" , f_MEXP_READ_LIST);
(deftfunc)("SEXP-READ" , f_SEXP_READ);
(deftfunc)("SEXP-READ-LIST" , f_SEXP_READ_LIST);
(deftfunc)("GET-TOKEN" , f_GET_TOKEN);
(deftfunc)("CONVERT-TO-ATOM" , f_CONVERT_TO_ATOM);
(deftfunc)("CUT-BOTH-SIDE" , f_CUT_BOTH_SIDE);
(deftfunc)("CONVERT-TO-SYMBOL" , f_CONVERT_TO_SYMBOL);
(deftfunc)("CONVERT-TO-STRING" , f_CONVERT_TO_STRING);
(deftfunc)("UPPERCASE" , f_UPPERCASE);
(deftfunc)("CONVERT-TO-INTEGER" , f_CONVERT_TO_INTEGER);
(deftfunc)("CONVERT-TO-FLOAT" , f_CONVERT_TO_FLOAT);
(deftfunc)("END-OF-FILE-P" , f_END_OF_FILE_P);
(deftfunc)("DELIMITERP" , f_DELIMITERP);
(deftfunc)("TERMINALP" , f_TERMINALP);
(deftfunc)("OPERATOR-CHAR-P" , f_OPERATOR_CHAR_P);
(deftfunc)("LEFT-PAREN-P" , f_LEFT_PAREN_P);
(deftfunc)("RIGHT-PAREN-P" , f_RIGHT_PAREN_P);
(deftfunc)("OPERATORP" , f_OPERATORP);
(deftfunc)("SPACE-SKIP" , f_SPACE_SKIP);
(deftfunc)("GETC" , f_GETC);
(deftfunc)("UNGETC" , f_UNGETC);
(deftfunc)("LOOK" , f_LOOK);
(deftfunc)("LOOK1" , f_LOOK1);
(deftfunc)("STRING-LIST-P" , f_STRING_LIST_P);
(deftfunc)("INTEGER-LIST-P" , f_INTEGER_LIST_P);
(deftfunc)("INTEGER-LIST-P1" , f_INTEGER_LIST_P1);
(deftfunc)("FLOAT-LIST-P" , f_FLOAT_LIST_P);
(deftfunc)("FLOAT-LIST-P1" , f_FLOAT_LIST_P1);
(deftfunc)("NUMBER-CHAR-P" , f_NUMBER_CHAR_P);
}void init_declare(void){
Fsetcatchsymbols(Fcons(Fmakesym("EXIT"),Fcons(Fmakesym("REPL"),NIL)));Fset_cdr(Fmakesym("BUFFER"),NIL);Fset_opt(Fmakesym("BUFFER"),FAST_GLOBAL);
Fset_cdr(Fmakesym("INPUT-STREAM"),fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-INPUT")),NIL)));Fset_opt(Fmakesym("INPUT-STREAM"),FAST_GLOBAL);
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakeint(500)),Fcons(fast_inverse(Fmakesym("WEIGHT")),Flist1(fast_inverse(Fmakesym("+")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakeint(500)),Fcons(fast_inverse(Fmakesym("WEIGHT")),Flist1(fast_inverse(Fmakesym("-")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakeint(400)),Fcons(fast_inverse(Fmakesym("WEIGHT")),Flist1(fast_inverse(Fmakesym("*")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakeint(400)),Fcons(fast_inverse(Fmakesym("WEIGHT")),Flist1(fast_inverse(Fmakesym("/")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakeint(300)),Fcons(fast_inverse(Fmakesym("WEIGHT")),Flist1(fast_inverse(Fmakesym("^")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("YFX")),Fcons(fast_inverse(Fmakesym("TYPE")),Flist1(fast_inverse(Fmakesym("+")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("YFX")),Fcons(fast_inverse(Fmakesym("TYPE")),Flist1(fast_inverse(Fmakesym("-")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("YFX")),Fcons(fast_inverse(Fmakesym("TYPE")),Flist1(fast_inverse(Fmakesym("*")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("YFX")),Fcons(fast_inverse(Fmakesym("TYPE")),Flist1(fast_inverse(Fmakesym("/")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("XFY")),Fcons(fast_inverse(Fmakesym("TYPE")),Flist1(fast_inverse(Fmakesym("^")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("+")),Fcons(fast_inverse(Fmakesym("SEXP")),Flist1(fast_inverse(Fmakesym("+")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("-")),Fcons(fast_inverse(Fmakesym("SEXP")),Flist1(fast_inverse(Fmakesym("-")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fmakesym("SEXP")),Flist1(fast_inverse(Fmakesym("*")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("QUOTIENT")),Fcons(fast_inverse(Fmakesym("SEXP")),Flist1(fast_inverse(Fmakesym("/")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fmakesym("EXPT")),Fcons(fast_inverse(Fmakesym("SEXP")),Flist1(fast_inverse(Fmakesym("^")))))));}