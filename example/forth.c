#include "fast.h"
jmp_buf c_DO_QUESTION[50];
jmp_buf c_EXIT[50];
jmp_buf c_REPL[50];
int f_POP(int arglist);int POP();
int f_FORTH(int arglist);int FORTH();
int f_REPL(int arglist);int REPL();
int f_INITIALIZE(int arglist);int INITIALIZE();
int f_INTERPRET_ALL(int arglist);int INTERPRET_ALL(int X);
int f_INTERPRET(int arglist);int INTERPRET(int X);
int f_ERRORstar(int arglist);int ERRORstar(int MSG,int X);
int f_WORDP(int arglist);int WORDP(int X);
int f_ENTITY(int arglist);int ENTITY(int X);
int f_DOT(int arglist);int DOT();
int f_DOT_S(int arglist);int DOT_S();
int f_SEE(int arglist);int SEE(int X);
int f_DROP(int arglist);int DROP();
int f_SWAP(int arglist);int SWAP();
int f_DUP(int arglist);int DUP();
int f_ROT(int arglist);int ROT();
int f_OVER(int arglist);int OVER();
int f_CR(int arglist);int CR();
int f_SPACE(int arglist);int SPACE();
int f_SPACES(int arglist);int SPACES();
int f_EMIT(int arglist);int EMIT();
int f_DO(int arglist);int DO(int X);
int f_questionDO(int arglist);int questionDO(int X);
int f_IFstar(int arglist);int IFstar(int X,int Y);
int f_PLUS(int arglist);int PLUS();
int f_MINUS(int arglist);int MINUS();
int f_MULT(int arglist);int MULT();
int f_DEVIDE(int arglist);int DEVIDE();
int f_MODstar(int arglist);int MODstar();
int f_slashMOD(int arglist);int slashMOD();
int f_ABSstar(int arglist);int ABSstar();
int f_NEGATE(int arglist);int NEGATE();
int f_MAXstar(int arglist);int MAXstar();
int f_MINstar(int arglist);int MINstar();
int f_SQRTstar(int arglist);int SQRTstar();
int f_DEFINE_WORD(int arglist);int DEFINE_WORD(int X);
int f_READ_CODE(int arglist);int READ_CODE();
int f_SLICE_CODE(int arglist);int SLICE_CODE(int X,int DELIMITER);
int f_SLICE_CODE1(int arglist);int SLICE_CODE1(int X,int DELIMITER,int Y);
int f_GETTOKEN(int arglist);int GETTOKEN();
int f_GETTOKEN1(int arglist);int GETTOKEN1();
int f_GETTOKEN2(int arglist);int GETTOKEN2(int LS);
int f_GETTOKEN3(int arglist);int GETTOKEN3();
int f_SKIP_SPACE(int arglist);int SKIP_SPACE();
int f_SKIP_PAREN(int arglist);int SKIP_PAREN();
int f_INTEGER_LIST_P(int arglist);int INTEGER_LIST_P(int LS);
int f_INTEGER_LIST_P1(int arglist);int INTEGER_LIST_P1(int LS);
int f_FLOAT_LIST_P(int arglist);int FLOAT_LIST_P(int LS);
int f_FLOAT_LIST_P1(int arglist);int FLOAT_LIST_P1(int LS);
int f_NUMBER_CHAR_P(int arglist);int NUMBER_CHAR_P(int X);
int f_CONVERT_TO_STRING_UPPER(int arglist);int CONVERT_TO_STRING_UPPER(int LS);
int f_CONVERT_TO_STRING(int arglist);int CONVERT_TO_STRING(int LS);
int f_UPPERCASE(int arglist);int UPPERCASE(int X);
int f_POP(int arglist){
return(fast_inverse(POP() ));
}
int f_FORTH(int arglist){
return(fast_inverse(FORTH() ));
}
int f_REPL(int arglist){
return(fast_inverse(REPL() ));
}
int f_INITIALIZE(int arglist){
return(fast_inverse(INITIALIZE() ));
}
int f_INTERPRET_ALL(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INTERPRET_ALL(fast_convert(arg1))));
}
int f_INTERPRET(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INTERPRET(fast_convert(arg1))));
}
int f_ERRORstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ERRORstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_WORDP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(WORDP(fast_convert(arg1))));
}
int f_ENTITY(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ENTITY(fast_convert(arg1))));
}
int f_DOT(int arglist){
return(fast_inverse(DOT() ));
}
int f_DOT_S(int arglist){
return(fast_inverse(DOT_S() ));
}
int f_SEE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SEE(fast_convert(arg1))));
}
int f_DROP(int arglist){
return(fast_inverse(DROP() ));
}
int f_SWAP(int arglist){
return(fast_inverse(SWAP() ));
}
int f_DUP(int arglist){
return(fast_inverse(DUP() ));
}
int f_ROT(int arglist){
return(fast_inverse(ROT() ));
}
int f_OVER(int arglist){
return(fast_inverse(OVER() ));
}
int f_CR(int arglist){
return(fast_inverse(CR() ));
}
int f_SPACE(int arglist){
return(fast_inverse(SPACE() ));
}
int f_SPACES(int arglist){
return(fast_inverse(SPACES() ));
}
int f_EMIT(int arglist){
return(fast_inverse(EMIT() ));
}
int f_DO(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DO(fast_convert(arg1))));
}
int f_questionDO(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(questionDO(fast_convert(arg1))));
}
int f_IFstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(IFstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_PLUS(int arglist){
return(fast_inverse(PLUS() ));
}
int f_MINUS(int arglist){
return(fast_inverse(MINUS() ));
}
int f_MULT(int arglist){
return(fast_inverse(MULT() ));
}
int f_DEVIDE(int arglist){
return(fast_inverse(DEVIDE() ));
}
int f_MODstar(int arglist){
return(fast_inverse(MODstar() ));
}
int f_slashMOD(int arglist){
return(fast_inverse(slashMOD() ));
}
int f_ABSstar(int arglist){
return(fast_inverse(ABSstar() ));
}
int f_NEGATE(int arglist){
return(fast_inverse(NEGATE() ));
}
int f_MAXstar(int arglist){
return(fast_inverse(MAXstar() ));
}
int f_MINstar(int arglist){
return(fast_inverse(MINstar() ));
}
int f_SQRTstar(int arglist){
return(fast_inverse(SQRTstar() ));
}
int f_DEFINE_WORD(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DEFINE_WORD(fast_convert(arg1))));
}
int f_READ_CODE(int arglist){
return(fast_inverse(READ_CODE() ));
}
int f_SLICE_CODE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SLICE_CODE(fast_convert(arg1),fast_convert(arg2))));
}
int f_SLICE_CODE1(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(SLICE_CODE1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_GETTOKEN(int arglist){
return(fast_inverse(GETTOKEN() ));
}
int f_GETTOKEN1(int arglist){
return(fast_inverse(GETTOKEN1() ));
}
int f_GETTOKEN2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GETTOKEN2(fast_convert(arg1))));
}
int f_GETTOKEN3(int arglist){
return(fast_inverse(GETTOKEN3() ));
}
int f_SKIP_SPACE(int arglist){
return(fast_inverse(SKIP_SPACE() ));
}
int f_SKIP_PAREN(int arglist){
return(fast_inverse(SKIP_PAREN() ));
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
int f_CONVERT_TO_STRING_UPPER(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONVERT_TO_STRING_UPPER(fast_convert(arg1))));
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
int POP(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*"))))))) != NIL){
res = ERRORstar(Fmakestr("not enough data in stack"),NIL);}
 else res = NIL;res;})
;
res = ({int res;int X = fast_convert(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*DATA-STACK*"))))));({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res = X;
res;})
;
return(res);}
int FORTH(){
int res;
if(Ffreecell() < 900) Fgbc();
INITIALIZE();
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
int S = fast_convert(READ_CODE());int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(S),Flist1(fast_inverse(Fcons(Fmakesym("BYE"),NIL)))))) == NIL){
INTERPRET_ALL(S);
temp1 = READ_CODE();
S = temp1;
}
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("May the Force be with you~%"))))));
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
{
goto REPLloop;};}
else{
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
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(NIL));res;});
({int res;
 res = Fset_cdr(Fmakesym("*RETURN-STACK*"),fast_inverse(NIL));res;});
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("Forth in ISLisp~%"))))));res;});
return(res);}
int INTERPRET_ALL(int X){
int res;
int temp1;
INTERPRET_ALLloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X))));res;}) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fmakesym(":")))))) != NIL){
res = ({int res;int Y = fast_convert(SLICE_CODE(fast_convert(fast_cdr(X)),Fmakesym("SEMICOLON")));DEFINE_WORD(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(0)))))));
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(1))))));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto INTERPRET_ALLloop;};
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fmakesym("SEE")))))) != NIL){
res = SEE(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));
{
temp1 = fast_convert(fast_cdr(fast_convert(fast_cdr(X))));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto INTERPRET_ALLloop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fmakesym("DO")))))) != NIL){
res = ({int res;int Y = fast_convert(SLICE_CODE(fast_convert(fast_cdr(X)),Fmakesym("LOOP")));DO(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(0)))))));
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(1))))));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto INTERPRET_ALLloop;};
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fmakesym("?DO")))))) != NIL){
res = ({int res;int Y = fast_convert(SLICE_CODE(fast_convert(fast_cdr(X)),Fmakesym("LOOP")));questionDO(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(0)))))));
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(1))))));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto INTERPRET_ALLloop;};
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fmakesym("IF")))))) != NIL){
res = ({int res;int Y = fast_convert(SLICE_CODE(fast_convert(fast_cdr(X)),Fmakesym("ELSE")));int Z = fast_convert(SLICE_CODE(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(1)))))),Fmakesym("ENDIF")));IFstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(0)))))),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Z),Flist1(fast_inverse(fast_immediate(0)))))));
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Z),Flist1(fast_inverse(fast_immediate(1))))));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto INTERPRET_ALLloop;};
res;})
;}
else{
res = INTERPRET(fast_convert(fast_car(X)));
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto INTERPRET_ALLloop;};}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INTERPRET(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && WORDP(X)) != NIL){
res = ({int res;int Y = fast_convert(ENTITY(X));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(Y))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Flist1(fast_inverse(Fcar(Y)))));res;});}
else{
res = INTERPRET_ALL(Y);}res;})
;
res;})
;}
else{
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(X))));res;}) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(X),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~A")),Flist1(fast_inverse(X))))));res;});}
else{
res = ERRORstar(Fmakestr("undefined word"),X);}
;res;});}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int ERRORstar(int MSG,int X){
int res;
if(CELLRANGE(MSG)) Fshelterpush(MSG);
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("Error ~A ~A~%")),Fcons(fast_inverse(MSG),Flist1(fast_inverse(X)))))));
res = ({int res,i;
res = T;catch_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(MSG)) Fshelterpop();
return(res);}
int WORDP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*WORD*"))))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int ENTITY(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*WORD*"))))))))),Flist1(fast_inverse(fast_immediate(1))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int DOT(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~A~%")),Flist1(fast_inverse(POP()))))));res;});
return(res);}
int DOT_S(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("<~A> ~A~%")),Fcons(fast_inverse(Flength(fast_convert(Fcdr(Fmakesym("*DATA-STACK*"))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*"))))))))))))));res;});
return(res);}
int SEE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int DEFINE = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*WORD*")))))))));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(DEFINE))));res;}) != NIL){
res = ERRORstar(Fmakestr("undefined word"),X);}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~A ~A~%")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(DEFINE),Flist1(fast_inverse(fast_immediate(1)))))))))))));res;});}res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int DROP(){
int res;
if(Ffreecell() < 900) Fgbc();
res = POP();
return(res);}
int SWAP(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int FIRST = fast_convert(POP());int SECOND = fast_convert(POP());({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(FIRST),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(SECOND),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int DUP(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(POP());({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(X),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(X),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int ROT(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int FIRST = fast_convert(POP());int SECOND = fast_convert(POP());int THIRD = fast_convert(POP());({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(SECOND),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(FIRST),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(THIRD),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int OVER(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_smallerp(fast_convert(Flength(fast_convert(Fcdr(Fmakesym("*DATA-STACK*"))))),fast_convert(fast_immediate(2))) != NIL){
res = ERRORstar(Fmakestr("not enough data"),Fmakesym("ROT"));}
 else res = NIL;res;})
;
res = ({int res;int SECOND = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))),Flist1(fast_inverse(fast_immediate(1)))))));res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(SECOND),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int CR(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("~%"))))));res;});
return(res);}
int SPACE(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr(" "))))));res;});
return(res);}
int SPACES(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int COUNT = fast_convert(POP());({int res;
if(fast_smallerp(fast_convert(COUNT),fast_convert(fast_immediate(0))) != NIL){
res = ERRORstar(Fmakestr("illegal number"),COUNT);}
 else res = NIL;res;})
;
res = ({int res;
int I = fast_convert(fast_immediate(0));int temp1;
while(fast_numeqp(fast_convert(I),fast_convert(COUNT)) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr(" "))))));
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = T;res;});
res;})
;
return(res);}
int EMIT(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int DATA = fast_convert(POP());({int res;
if(fast_not(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("INTEGERP")),Flist1(fast_inverse(DATA))));res;})) != NIL){
res = ERRORstar(Fmakestr("not integer"),DATA);}
 else res = NIL;res;})
;
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~C")),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(DATA),Fmakesym("<CHARACTER>")))))))));res;});
res;})
;
return(res);}
int DO(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int START = fast_convert(POP());int END = fast_convert(POP());res = ({int res;
int I = fast_convert(START);int temp1;
while(fast_eqgreaterp(fast_convert(I),fast_convert(END)) == NIL){
INTERPRET_ALL(X);
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = T;res;});
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int questionDO(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("DO-QUESTION"));
Fsetprop(Fmakesym("DO-QUESTION"),i+1);
ret=setjmp(c_DO_QUESTION[i]);if(ret == 0){
res = ({int res;int START = fast_convert(POP());int END = fast_convert(POP());({int res;
if(fast_smallerp(fast_convert(END),fast_convert(START)) != NIL){
({int res,i;
res = T;block_arg=res;
 i = Fgetprop(Fmakesym("DO-QUESTION"));
Fsetprop(Fmakesym("DO-QUESTION"),i-1);
longjmp(c_DO_QUESTION[i-1],1);res;})
;}
 else res = NIL;res;})
;
res = ({int res;
int I = fast_convert(START);int temp1;
while(fast_eqgreaterp(fast_convert(I),fast_convert(END)) == NIL){
INTERPRET_ALL(X);
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = T;res;});
res;})
;Fsetprop(Fmakesym("DO-QUESTION"),i);
}
 else{
ret = 0;
res=block_arg;}
res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int IFstar(int X,int Y){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TEST = fast_convert(POP());res = ({int res;
if(fast_not(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(TEST),Flist1(fast_inverse(fast_immediate(0))))));res;})) != NIL){
res = INTERPRET_ALL(X);}
else{
res = INTERPRET_ALL(Y);}res;})
;
res;})
;
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int PLUS(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_plus(fast_convert(POP()),fast_convert(POP()))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
return(res);}
int MINUS(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_minus(fast_convert(POP()),fast_convert(POP()))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
return(res);}
int MULT(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_mult(fast_convert(POP()),fast_convert(POP()))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
return(res);}
int DEVIDE(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(POP()),Flist1(fast_inverse(POP())))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
return(res);}
int MODstar(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int FIRST = fast_convert(POP());int SECOND = fast_convert(POP());res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_mod(fast_convert(SECOND),fast_convert(FIRST))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int slashMOD(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int FIRST = fast_convert(POP());int SECOND = fast_convert(POP());({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(SECOND),Flist1(fast_inverse(FIRST)))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_mod(fast_convert(SECOND),fast_convert(FIRST))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int ABSstar(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(POP());res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(X))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int NEGATE(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(POP());res = ({int res;
if(fast_greaterp(fast_convert(X),fast_convert(fast_immediate(0))) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(X))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(X))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});}res;})
;
res;})
;
return(res);}
int MAXstar(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(POP());int Y = fast_convert(POP());res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAX")),Fcons(fast_inverse(X),Flist1(fast_inverse(Y)))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int MINstar(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(POP());int Y = fast_convert(POP());res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MIN")),Fcons(fast_inverse(X),Flist1(fast_inverse(Y)))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int SQRTstar(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(POP());res = ({int res;
 res = Fset_cdr(Fmakesym("*DATA-STACK*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("SQRT")),Flist1(fast_inverse(POP()))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DATA-STACK*")))))));res;});
res;})
;
return(res);}
int DEFINE_WORD(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(fast_car(X)));int BODY = fast_convert(fast_convert(fast_cdr(X)));res = ({int res;
 res = Fset_cdr(Fmakesym("*WORD*"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(NAME),Flist1(fast_inverse(BODY)))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*WORD*")))))));res;});
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int READ_CODE(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(Fcons(Fmakechar("\\"),NIL)));res;});
({int res;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),Flist1(fast_inverse(Fmakechar("\\")))))) !=NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("? "))))));
res = ({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("READ-LINE")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-INPUT")),NIL))))))),Fmakesym("<LIST>")))));res;});};res;})
;
res = ({int res;int CODE = fast_convert(NIL);int TOKEN = fast_convert(NIL);({int res;
 res = TOKEN = GETTOKEN();res;})
;
({int res;
while(fast_not(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TOKEN))));res;})) !=NIL){
({int res;
 res = CODE = Fcons(fast_inverse(TOKEN),fast_inverse(CODE));res;})
;
res = ({int res;
 res = TOKEN = GETTOKEN();res;})
;};res;})
;
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(CODE))));res;});
res;})
;
return(res);}
int SLICE_CODE(int X,int DELIMITER){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(DELIMITER)) Fshelterpush(DELIMITER);
if(Ffreecell() < 900) Fgbc();
res = SLICE_CODE1(X,DELIMITER,NIL);
if(CELLRANGE(DELIMITER)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SLICE_CODE1(int X,int DELIMITER,int Y){
int res;
int temp1,temp2,temp3;
SLICE_CODE1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(DELIMITER)) Fshelterpush(DELIMITER);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(DELIMITER)))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(Y))))),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))));res;});}
else{
{
temp1 = fast_convert(fast_cdr(X));
temp2 = DELIMITER;
temp3 = Fcons(fast_inverse(fast_convert(fast_car(X))),fast_inverse(Y));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(DELIMITER)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
X = temp1;
DELIMITER = temp2;
Y = temp3;
goto SLICE_CODE1loop;};}
;res;});
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(DELIMITER)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int GETTOKEN(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))));res;}) != NIL){
res = NIL;}
else{
res = GETTOKEN1();}res;})
;
return(res);}
int GETTOKEN1(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(NIL);SKIP_SPACE();
SKIP_PAREN();
({int res;
while((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),Flist1(fast_inverse(Fmakechar(" ")))))))) !=NIL){
({int res;
 res = TOKEN = Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))));res;});};res;})
;
res = GETTOKEN2(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(TOKEN)))));
res;})
;
return(res);}
int GETTOKEN2(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_numeqp(fast_convert(Flength(LS)),fast_convert(fast_immediate(1))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar(";"))))))) != NIL){
res = Fmakesym("SEMICOLON");}
else if((fast_numeqp(fast_convert(Flength(LS)),fast_convert(fast_immediate(1))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("."))))))) != NIL){
res = Fmakesym("DOT");}
else if((fast_numeqp(fast_convert(Flength(LS)),fast_convert(fast_immediate(2))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar(".")))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(Fmakechar("s"))))))) != NIL){
res = Fmakesym("DOT-S");}
else if((fast_numeqp(fast_convert(Flength(LS)),fast_convert(fast_immediate(2))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar(".")))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(Fmakechar("\""))))))) != NIL){
res = GETTOKEN3();}
else if(INTEGER_LIST_P(LS) != NIL){
res = fast_convert(Fconvert(fast_inverse(CONVERT_TO_STRING(LS)),Fmakesym("<INTEGER>")));}
else if(FLOAT_LIST_P(LS) != NIL){
res = fast_convert(Fconvert(fast_inverse(CONVERT_TO_STRING(LS)),Fmakesym("<FLOAT>")));}
else{
res = fast_convert(Fconvert(fast_inverse(CONVERT_TO_STRING_UPPER(LS)),Fmakesym("<SYMBOL>")));}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int GETTOKEN3(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TOKEN = fast_convert(NIL);SKIP_SPACE();
({int res;
while((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),Flist1(fast_inverse(Fmakechar("\"")))))))) !=NIL){
({int res;
 res = TOKEN = Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),fast_inverse(TOKEN));res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))));res;});};res;})
;
({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))));res;});
res = CONVERT_TO_STRING(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(TOKEN)))));
res;})
;
return(res);}
int SKIP_SPACE(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
while((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),Flist1(fast_inverse(Fmakechar(" "))))))) !=NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))));res;});};res;})
;
return(res);}
int SKIP_PAREN(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),Flist1(fast_inverse(Fmakechar("("))))))) != NIL){
res = ({int res;
while((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))),Flist1(fast_inverse(Fmakechar(")")))))))) !=NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))));res;});};res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("*BUFFER*"),fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("*BUFFER*")))))));res;});
res = SKIP_SPACE();}
;res;});
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
int CONVERT_TO_STRING_UPPER(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = Fmakestr("");}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(UPPERCASE(fast_convert(fast_car(LS)))),Fmakesym("<STRING>")))),Flist1(fast_inverse(CONVERT_TO_STRING_UPPER(fast_convert(fast_cdr(LS))))))));res;});}res;})
;
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
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(fast_car(LS))),Fmakesym("<STRING>")))),Flist1(fast_inverse(CONVERT_TO_STRING(fast_convert(fast_cdr(LS))))))));res;});}res;})
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
void init_tfunctions(void){
(deftfunc)("POP" , f_POP);
(deftfunc)("FORTH" , f_FORTH);
(deftfunc)("REPL" , f_REPL);
(deftfunc)("INITIALIZE" , f_INITIALIZE);
(deftfunc)("INTERPRET-ALL" , f_INTERPRET_ALL);
(deftfunc)("INTERPRET" , f_INTERPRET);
(deftfunc)("ERROR*" , f_ERRORstar);
(deftfunc)("WORDP" , f_WORDP);
(deftfunc)("ENTITY" , f_ENTITY);
(deftfunc)("DOT" , f_DOT);
(deftfunc)("DOT-S" , f_DOT_S);
(deftfunc)("SEE" , f_SEE);
(deftfunc)("DROP" , f_DROP);
(deftfunc)("SWAP" , f_SWAP);
(deftfunc)("DUP" , f_DUP);
(deftfunc)("ROT" , f_ROT);
(deftfunc)("OVER" , f_OVER);
(deftfunc)("CR" , f_CR);
(deftfunc)("SPACE" , f_SPACE);
(deftfunc)("SPACES" , f_SPACES);
(deftfunc)("EMIT" , f_EMIT);
(deftfunc)("DO" , f_DO);
(deftfunc)("?DO" , f_questionDO);
(deftfunc)("IF*" , f_IFstar);
(deftfunc)("PLUS" , f_PLUS);
(deftfunc)("MINUS" , f_MINUS);
(deftfunc)("MULT" , f_MULT);
(deftfunc)("DEVIDE" , f_DEVIDE);
(deftfunc)("MOD*" , f_MODstar);
(deftfunc)("/MOD" , f_slashMOD);
(deftfunc)("ABS*" , f_ABSstar);
(deftfunc)("NEGATE" , f_NEGATE);
(deftfunc)("MAX*" , f_MAXstar);
(deftfunc)("MIN*" , f_MINstar);
(deftfunc)("SQRT*" , f_SQRTstar);
(deftfunc)("DEFINE-WORD" , f_DEFINE_WORD);
(deftfunc)("READ-CODE" , f_READ_CODE);
(deftfunc)("SLICE-CODE" , f_SLICE_CODE);
(deftfunc)("SLICE-CODE1" , f_SLICE_CODE1);
(deftfunc)("GETTOKEN" , f_GETTOKEN);
(deftfunc)("GETTOKEN1" , f_GETTOKEN1);
(deftfunc)("GETTOKEN2" , f_GETTOKEN2);
(deftfunc)("GETTOKEN3" , f_GETTOKEN3);
(deftfunc)("SKIP-SPACE" , f_SKIP_SPACE);
(deftfunc)("SKIP-PAREN" , f_SKIP_PAREN);
(deftfunc)("INTEGER-LIST-P" , f_INTEGER_LIST_P);
(deftfunc)("INTEGER-LIST-P1" , f_INTEGER_LIST_P1);
(deftfunc)("FLOAT-LIST-P" , f_FLOAT_LIST_P);
(deftfunc)("FLOAT-LIST-P1" , f_FLOAT_LIST_P1);
(deftfunc)("NUMBER-CHAR-P" , f_NUMBER_CHAR_P);
(deftfunc)("CONVERT-TO-STRING-UPPER" , f_CONVERT_TO_STRING_UPPER);
(deftfunc)("CONVERT-TO-STRING" , f_CONVERT_TO_STRING);
(deftfunc)("UPPERCASE" , f_UPPERCASE);
}void init_declare(void){
Fsetcatchsymbols(Fcons(Fmakesym("DO-QUESTION"),Fcons(Fmakesym("EXIT"),Fcons(Fmakesym("REPL"),NIL))));Fset_cdr(Fmakesym("*DATA-STACK*"),NIL);Fset_opt(Fmakesym("*DATA-STACK*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*RETURN-STACK*"),NIL);Fset_opt(Fmakesym("*RETURN-STACK*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*WORD*"),Fcons(Fcons(Fmakesym("DOT"),Fcons(Fmakesym("DOT"),NIL)),Fcons(Fcons(Fmakesym("BYE"),Fcons(T,NIL)),Fcons(Fcons(Fmakesym(":"),Fcons(Fmakesym("DEFINE-WORD"),NIL)),Fcons(Fcons(Fmakesym("DOT-S"),Fcons(Fmakesym("DOT-S"),NIL)),Fcons(Fcons(Fmakesym("SEE"),Fcons(Fmakesym("SEE"),NIL)),Fcons(Fcons(Fmakesym("DROP"),Fcons(Fmakesym("DROP"),NIL)),Fcons(Fcons(Fmakesym("SWAP"),Fcons(Fmakesym("SWAP"),NIL)),Fcons(Fcons(Fmakesym("DUP"),Fcons(Fmakesym("DUP"),NIL)),Fcons(Fcons(Fmakesym("ROT"),Fcons(Fmakesym("ROT"),NIL)),Fcons(Fcons(Fmakesym("CR"),Fcons(Fmakesym("CR"),NIL)),Fcons(Fcons(Fmakesym("OVER"),Fcons(Fmakesym("OVER"),NIL)),Fcons(Fcons(Fmakesym("SPACE"),Fcons(Fmakesym("SPACE"),NIL)),Fcons(Fcons(Fmakesym("SPACES"),Fcons(Fmakesym("SPACES"),NIL)),Fcons(Fcons(Fmakesym("EMIT"),Fcons(Fmakesym("EMIT"),NIL)),Fcons(Fcons(Fmakesym("MOD"),Fcons(Fmakesym("MOD*"),NIL)),Fcons(Fcons(Fmakesym("/MOD"),Fcons(Fmakesym("/MOD"),NIL)),Fcons(Fcons(Fmakesym("DO"),Fcons(Fmakesym("DO"),NIL)),Fcons(Fcons(Fmakesym("LOOP"),Fcons(T,NIL)),Fcons(Fcons(Fmakesym("?DO"),Fcons(Fmakesym("?DO"),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("IF*"),NIL)),Fcons(Fcons(Fmakesym("THEN"),Fcons(T,NIL)),Fcons(Fcons(Fmakesym("+"),Fcons(Fmakesym("PLUS"),NIL)),Fcons(Fcons(Fmakesym("-"),Fcons(Fmakesym("MINUS"),NIL)),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("MULT"),NIL)),Fcons(Fcons(Fmakesym("/"),Fcons(Fmakesym("DEVIDE"),NIL)),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakesym("SQRT*"),NIL)),Fcons(Fcons(Fmakesym("ABS"),Fcons(Fmakesym("ABS*"),NIL)),Fcons(Fcons(Fmakesym("NEGATE"),Fcons(Fmakesym("NEGATE"),NIL)),Fcons(Fcons(Fmakesym("MAX"),Fcons(Fmakesym("MAX*"),NIL)),Fcons(Fcons(Fmakesym("MIN"),Fcons(Fmakesym("MNIN*"),NIL)),NIL)))))))))))))))))))))))))))))));Fset_opt(Fmakesym("*WORD*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*BUFFER*"),NIL);Fset_opt(Fmakesym("*BUFFER*"),FAST_GLOBAL);
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("PUSH"),Fcons(Fcons(Fmakesym("X"),NIL),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("SETQ"),Fcons(Fmakesym("*DATA-STACK*"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("*DATA-STACK*"),NIL))),NIL))),NIL)),NIL)))));
}