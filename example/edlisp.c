#include "fast.h"
jmp_buf c_EXIT[50];
jmp_buf c_REPL[50];
int f_ISLISP(int arglist);int ISLISP();
int f_REPL(int arglist);int REPL();
int f_INITIALIZE(int arglist);int INITIALIZE();
int f_PROMPT(int arglist);int PROMPT();
int f_EVALstar(int arglist);int EVALstar(int S,int ENV);
int f_APPLYstar(int arglist);int APPLYstar(int F,int ARG,int ENV);
int f_BINDARG(int arglist);int BINDARG(int VAR,int ARG,int ENV);
int f_EVLIS(int arglist);int EVLIS(int ARG,int ENV);
int f_LOOKUP(int arglist);int LOOKUP(int SYM,int ENV);
int f_FUNCTION_LOOKUP(int arglist);int FUNCTION_LOOKUP(int SYM);
int f_DYNAMIC_LOOKUP(int arglist);int DYNAMIC_LOOKUP(int SYM);
int f_BIND(int arglist);int BIND(int SYM,int VAL,int ENV);
int f_ERRORstar(int arglist);int ERRORstar(int MSG,int ARG);
int f_PRIMITIVEP(int arglist);int PRIMITIVEP(int X);
int f_FUNCTIONPstar(int arglist);int FUNCTIONPstar(int X);
int f_SPECIAL_FORM_P(int arglist);int SPECIAL_FORM_P(int X);
int f_SPECIAL_FORM(int arglist);int SPECIAL_FORM(int F,int ARG,int ENV);
int f_EVCON(int arglist);int EVCON(int ARG,int ENV);
int f_EVIF(int arglist);int EVIF(int ARG,int ENV);
int f_EVLET(int arglist);int EVLET(int ARG,int ENV);
int f_EVLETstar(int arglist);int EVLETstar(int ARG,int ENV);
int f_EVPROGN(int arglist);int EVPROGN(int ARG,int ENV);
int f_EVSETQ(int arglist);int EVSETQ(int ARG,int ENV);
int f_EVDEFGLOBAL(int arglist);int EVDEFGLOBAL(int ARG,int ENV);
int f_EVDYNAMIC(int arglist);int EVDYNAMIC(int ARG,int ENV);
int f_EVDEFDYNAMIC(int arglist);int EVDEFDYNAMIC(int ARG,int ENV);
int f_EVDEFUN(int arglist);int EVDEFUN(int ARG,int ENV);
int f_ISLISP(int arglist){
return(fast_inverse(ISLISP() ));
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
int f_EVALstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVALstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_APPLYstar(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(APPLYstar(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_BINDARG(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(BINDARG(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_EVLIS(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVLIS(fast_convert(arg1),fast_convert(arg2))));
}
int f_LOOKUP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LOOKUP(fast_convert(arg1),fast_convert(arg2))));
}
int f_FUNCTION_LOOKUP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FUNCTION_LOOKUP(fast_convert(arg1))));
}
int f_DYNAMIC_LOOKUP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DYNAMIC_LOOKUP(fast_convert(arg1))));
}
int f_BIND(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(BIND(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_ERRORstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ERRORstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_PRIMITIVEP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PRIMITIVEP(fast_convert(arg1))));
}
int f_FUNCTIONPstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FUNCTIONPstar(fast_convert(arg1))));
}
int f_SPECIAL_FORM_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SPECIAL_FORM_P(fast_convert(arg1))));
}
int f_SPECIAL_FORM(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(SPECIAL_FORM(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_EVCON(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVCON(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVIF(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVIF(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVLET(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVLET(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVLETstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVLETstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVPROGN(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVPROGN(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVSETQ(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVSETQ(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVDEFGLOBAL(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVDEFGLOBAL(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVDYNAMIC(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVDYNAMIC(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVDEFDYNAMIC(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVDEFDYNAMIC(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVDEFUN(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVDEFUN(fast_convert(arg1),fast_convert(arg2))));
}
int ISLISP(){
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
int S = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("READ")),NIL)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(S),Flist1(fast_inverse(Fcons(Fmakesym("QUIT"),NIL)))))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("PRINT")),Flist1(fast_inverse(EVALstar(S,NIL)))));
({int res;
 res = Fset_cdr(Fmakesym("*DYNAMIC*"),fast_inverse(NIL));res;});
PROMPT();
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("READ")),NIL));
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
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("Subset ISLisp for education~%"))))));
res = PROMPT();
return(res);}
int PROMPT(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("L> "))))));res;});
return(res);}
int EVALstar(int S,int ENV){
int res;
if(CELLRANGE(S)) Fshelterpush(S);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(S))));res;}) != NIL){
res = S;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(S)))) != NIL){
res = S;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(S)))) != NIL){
res = S;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(S)))) != NIL){
res = S;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-VECTOR-P")),Flist1(fast_inverse(S)))) != NIL){
res = S;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-ARRAY*-P")),Flist1(fast_inverse(S)))) != NIL){
res = S;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(S)))) != NIL){
res = ({int res;
if(fast_eq(fast_convert(S),fast_convert(T)) != NIL){
res = S;}
else{
res = LOOKUP(S,ENV);}res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(S)))) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(fast_convert(fast_car(S))),fast_convert(Fmakesym("FUNCALL"))) != NIL){
res = APPLYstar(EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(S),Flist1(fast_inverse(fast_immediate(1)))))),ENV),fast_convert(fast_cdr(fast_convert(fast_cdr(S)))),ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(S)))))) && fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(S))))),fast_convert(Fmakesym("LAMBDA")))) != NIL){
res = APPLYstar(EVALstar(fast_convert(fast_car(S)),ENV),EVLIS(fast_convert(fast_cdr(S)),ENV),ENV);}
else if(SPECIAL_FORM_P(fast_convert(fast_car(S))) != NIL){
res = APPLYstar(fast_convert(fast_car(S)),fast_convert(fast_cdr(S)),ENV);}
else if(PRIMITIVEP(fast_convert(fast_car(S))) != NIL){
res = APPLYstar(fast_convert(fast_car(S)),EVLIS(fast_convert(fast_cdr(S)),ENV),ENV);}
else if(FUNCTIONPstar(fast_convert(fast_car(S))) != NIL){
res = APPLYstar(fast_convert(fast_car(S)),EVLIS(fast_convert(fast_cdr(S)),ENV),ENV);}
else{
res = APPLYstar(FUNCTION_LOOKUP(fast_convert(fast_car(S))),EVLIS(fast_convert(fast_cdr(S)),ENV),ENV);}
;res;});}
else{
res = ERRORstar(Fmakestr("undefined object"),S);}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(S)) Fshelterpop();
return(res);}
int APPLYstar(int F,int ARG,int ENV){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(SPECIAL_FORM_P(F) != NIL){
res = SPECIAL_FORM(F,ARG,ENV);}
else if(PRIMITIVEP(F) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("APPLY")),Fcons(fast_inverse(Fcar(F)),Flist1(fast_inverse(ARG)))));res;});}
else if(FUNCTIONPstar(F) != NIL){
res = ({int res;int ENV1 = fast_convert(BINDARG(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_immediate(0)))))),ARG,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(2))))))));res = ({int res;
int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(1)))))))));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY)))))) == NIL){
EVALstar(fast_convert(fast_car(BODY)),ENV1);
temp1 = fast_convert(fast_cdr(BODY));
BODY = temp1;
}
res = EVALstar(fast_convert(fast_car(BODY)),ENV1);res;});
res;})
;}
else{
res = ERRORstar(Fmakestr("Illegal function call apply* "),F);}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int BINDARG(int VAR,int ARG,int ENV){
int res;
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int VAR1 = fast_convert(VAR);int ARG1 = fast_convert(ARG);int RES = fast_convert(NIL);int temp1,temp2,temp3;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(VAR1)))) == NIL){
temp1 = fast_convert(fast_cdr(VAR1));
temp2 = fast_convert(fast_cdr(ARG1));
temp3 = Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(fast_car(VAR1))),fast_inverse(fast_convert(fast_car(ARG1))))),fast_inverse(RES));
VAR1 = temp1;
ARG1 = temp2;
RES = temp3;
}
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(fast_inverse(RES),Flist1(fast_inverse(ENV)))));res;});res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
if(CELLRANGE(VAR)) Fshelterpop();
return(res);}
int EVLIS(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(ARG))));res;}) != NIL){
res = NIL;}
else{
res = Fcons(fast_inverse(EVALstar(fast_convert(fast_car(ARG)),ENV)),fast_inverse(EVLIS(fast_convert(fast_cdr(ARG)),ENV)));}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int LOOKUP(int SYM,int ENV){
int res;
if(CELLRANGE(SYM)) Fshelterpush(SYM);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(ENV)))));res;}) != NIL){
res = fast_convert(fast_cdr(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(ENV)))));res;})));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*GLOBAL*")))))))) != NIL){
res = fast_convert(fast_cdr(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*GLOBAL*"))))))));res;})));}
else if(PRIMITIVEP(SYM) != NIL){
res = Fmakesym("PRIMITIVE");}
else{
res = ERRORstar(Fmakestr("Undefined variable "),SYM);}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(SYM)) Fshelterpop();
return(res);}
int FUNCTION_LOOKUP(int SYM){
int res;
if(CELLRANGE(SYM)) Fshelterpush(SYM);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*FUNCTION*"))))))));res;}) != NIL){
res = fast_convert(fast_cdr(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*FUNCTION*"))))))));res;})));}
else{
res = ERRORstar(Fmakestr("Undefined function "),SYM);}
;res;});
if(CELLRANGE(SYM)) Fshelterpop();
return(res);}
int DYNAMIC_LOOKUP(int SYM){
int res;
if(CELLRANGE(SYM)) Fshelterpush(SYM);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*DYNAMIC*"))))))));res;}) != NIL){
res = fast_convert(fast_cdr(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*DYNAMIC*"))))))));res;})));}
else{
res = ERRORstar(Fmakestr("Undefined variable "),SYM);}
;res;});
if(CELLRANGE(SYM)) Fshelterpop();
return(res);}
int BIND(int SYM,int VAL,int ENV){
int res;
if(CELLRANGE(SYM)) Fshelterpush(SYM);
if(CELLRANGE(VAL)) Fshelterpush(VAL);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(ENV)))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(VAL),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(ENV))))))))));res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*GLOBAL*")))))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(VAL),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(SYM),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*GLOBAL*")))))))))))));res;});}
else{
res = ERRORstar(Fmakestr("Undefined variable "),SYM);}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(VAL)) Fshelterpop();
if(CELLRANGE(SYM)) Fshelterpop();
return(res);}
int ERRORstar(int MSG,int ARG){
int res;
if(CELLRANGE(MSG)) Fshelterpush(MSG);
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(MSG)))));
fast_convert(Fcallsubr(Fcar(Fmakesym("PRINT")),Flist1(fast_inverse(ARG))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("~%"))))));
res = ({int res,i;
res = NIL;catch_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;
if(CELLRANGE(ARG)) Fshelterpop();
if(CELLRANGE(MSG)) Fshelterpop();
return(res);}
int PRIMITIVEP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*PRIMITIVE*"))))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FUNCTIONPstar(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X))))) != NIL)
if((res=fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FUNC")))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SPECIAL_FORM_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*SPECIAL-FORM*"))))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SPECIAL_FORM(int F,int ARG,int ENV){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(F),fast_convert(Fmakesym("QUOTE"))) != NIL){
res = fast_convert(fast_car(ARG));}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("LAMBDA"))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("FUNC")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(ENV))))));res;});}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("COND"))) != NIL){
res = EVCON(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("SETQ"))) != NIL){
res = EVSETQ(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("DEFUN"))) != NIL){
res = EVDEFUN(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("IF"))) != NIL){
res = EVIF(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("LET"))) != NIL){
res = EVLET(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("LET*"))) != NIL){
res = EVLETstar(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("PROGN"))) != NIL){
res = EVPROGN(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("DEFGLOBAL"))) != NIL){
res = EVDEFGLOBAL(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("DEFDYNAMIC"))) != NIL){
res = EVDEFDYNAMIC(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("DYNAMIC"))) != NIL){
res = EVDYNAMIC(ARG,ENV);}
else if(fast_eq(fast_convert(F),fast_convert(Fmakesym("FUNCTION"))) != NIL){
res = ({int res;
if(PRIMITIVEP(fast_convert(fast_car(ARG))) != NIL){
res = fast_convert(fast_car(ARG));}
else{
res = FUNCTION_LOOKUP(fast_convert(fast_car(ARG)));}res;})
;}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int EVCON(int ARG,int ENV){
int res;
int temp1,temp2;
EVCONloop:
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_not(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_car(fast_convert(fast_car(ARG))))))));res;})) != NIL){
res = EVPROGN(fast_convert(fast_cdr(fast_convert(fast_car(ARG)))),ENV);}
else{
{
temp1 = fast_convert(fast_cdr(ARG));
temp2 = ENV;
if(CELLRANGE(ARG)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
ARG = temp1;
ENV = temp2;
goto EVCONloop;};}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVIF(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0)))))),ENV)))));res;})) != NIL){
res = EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(1)))))),ENV);}
else{
res = EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(2)))))),ENV);}res;})
;
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVLET(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
({int res;
int VARS = fast_convert(fast_convert(fast_car(ARG)));int ENV1 = fast_convert(ENV);int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(VARS)))) == NIL){
({int res;
 res = ENV1 = Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(VARS))),Flist1(fast_inverse(fast_immediate(0))))))),fast_inverse(EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(VARS))),Flist1(fast_inverse(fast_immediate(1)))))),ENV)))),fast_inverse(ENV1));res;})
;
temp1 = fast_convert(fast_cdr(VARS));
VARS = temp1;
}
res = ({int res;
 res = ENV = ENV1;res;})
;res;});
res = ({int res;
int BODY = fast_convert(fast_convert(fast_cdr(ARG)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY)))))) == NIL){
EVALstar(fast_convert(fast_car(BODY)),ENV);
temp1 = fast_convert(fast_cdr(BODY));
BODY = temp1;
}
res = EVALstar(fast_convert(fast_car(BODY)),ENV);res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVLETstar(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
({int res;
int VARS = fast_convert(fast_convert(fast_car(ARG)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(VARS)))) == NIL){
({int res;
 res = ENV = Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(VARS))),Flist1(fast_inverse(fast_immediate(0))))))),fast_inverse(EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(VARS))),Flist1(fast_inverse(fast_immediate(1)))))),ENV)))),fast_inverse(ENV));res;})
;
temp1 = fast_convert(fast_cdr(VARS));
VARS = temp1;
}
res = T;res;});
res = ({int res;
int BODY = fast_convert(fast_convert(fast_cdr(ARG)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY)))))) == NIL){
EVALstar(fast_convert(fast_car(BODY)),ENV);
temp1 = fast_convert(fast_cdr(BODY));
BODY = temp1;
}
res = EVALstar(fast_convert(fast_car(BODY)),ENV);res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVPROGN(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int BODY = fast_convert(ARG);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY)))))) == NIL){
EVALstar(fast_convert(fast_car(BODY)),ENV);
temp1 = fast_convert(fast_cdr(BODY));
BODY = temp1;
}
res = EVALstar(fast_convert(fast_car(BODY)),ENV);res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVSETQ(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
BIND(fast_convert(fast_car(ARG)),EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(1)))))),ENV),ENV);
res = fast_convert(fast_car(ARG));
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVDEFGLOBAL(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*GLOBAL*"))))))));res;}) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(1)))))),ENV)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*GLOBAL*")))))))))))));
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))));res;});}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("*GLOBAL*"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(Fmakeint(0))))))),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(Fmakeint(1))))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*GLOBAL*")))))));res;});
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))));res;});}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVDYNAMIC(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = DYNAMIC_LOOKUP(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0)))))));
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVDEFDYNAMIC(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*DYNAMIC*"))))))));res;}) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(EVALstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(1)))))),ENV)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*DYNAMIC*")))))))))))));
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))));res;});}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("*DYNAMIC*"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(Fmakeint(0))))))),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(Fmakeint(1))))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*DYNAMIC*")))))));res;});
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))));res;});}
;res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
int EVDEFUN(int ARG,int ENV){
int res;
if(CELLRANGE(ARG)) Fshelterpush(ARG);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*FUNCTION*")))))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("FUNC")),Fcons(fast_inverse(fast_convert(fast_cdr(ARG))),Flist1(fast_inverse(ENV))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*FUNCTION*")))))))))))));res;});}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("*FUNCTION*"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(Fmakeint(0))))))),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("FUNC")),Fcons(fast_inverse(fast_convert(fast_cdr(ARG))),Flist1(fast_inverse(ENV))))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("*FUNCTION*")))))));res;});}
;res;});
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_immediate(0))))));res;});
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARG)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("ISLISP" , f_ISLISP);
(deftfunc)("REPL" , f_REPL);
(deftfunc)("INITIALIZE" , f_INITIALIZE);
(deftfunc)("PROMPT" , f_PROMPT);
(deftfunc)("EVAL*" , f_EVALstar);
(deftfunc)("APPLY*" , f_APPLYstar);
(deftfunc)("BINDARG" , f_BINDARG);
(deftfunc)("EVLIS" , f_EVLIS);
(deftfunc)("LOOKUP" , f_LOOKUP);
(deftfunc)("FUNCTION-LOOKUP" , f_FUNCTION_LOOKUP);
(deftfunc)("DYNAMIC-LOOKUP" , f_DYNAMIC_LOOKUP);
(deftfunc)("BIND" , f_BIND);
(deftfunc)("ERROR*" , f_ERRORstar);
(deftfunc)("PRIMITIVEP" , f_PRIMITIVEP);
(deftfunc)("FUNCTIONP*" , f_FUNCTIONPstar);
(deftfunc)("SPECIAL-FORM-P" , f_SPECIAL_FORM_P);
(deftfunc)("SPECIAL-FORM" , f_SPECIAL_FORM);
(deftfunc)("EVCON" , f_EVCON);
(deftfunc)("EVIF" , f_EVIF);
(deftfunc)("EVLET" , f_EVLET);
(deftfunc)("EVLET*" , f_EVLETstar);
(deftfunc)("EVPROGN" , f_EVPROGN);
(deftfunc)("EVSETQ" , f_EVSETQ);
(deftfunc)("EVDEFGLOBAL" , f_EVDEFGLOBAL);
(deftfunc)("EVDYNAMIC" , f_EVDYNAMIC);
(deftfunc)("EVDEFDYNAMIC" , f_EVDEFDYNAMIC);
(deftfunc)("EVDEFUN" , f_EVDEFUN);
}void init_declare(void){
Fsetcatchsymbols(Fcons(Fmakesym("EXIT"),Fcons(Fmakesym("REPL"),NIL)));Fset_cdr(Fmakesym("*GLOBAL*"),NIL);Fset_opt(Fmakesym("*GLOBAL*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*DYNAMIC*"),NIL);Fset_opt(Fmakesym("*DYNAMIC*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*FUNCTION*"),NIL);Fset_opt(Fmakesym("*FUNCTION*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*PRIMITIVE*"),Fcons(Fmakesym("ATOM"),Fcons(Fmakesym("+"),Fcons(Fmakesym("-"),Fcons(Fmakesym("*"),Fcons(Fmakesym("DIV"),Fcons(Fmakesym("="),Fcons(Fmakesym("EQ"),Fcons(Fmakesym("SIN"),Fcons(Fmakesym("COS"),Fcons(Fmakesym("TAN"),Fcons(Fmakesym("ATAN"),Fcons(Fmakesym("PRINT"),Fcons(Fmakesym("SYMBOLP"),Fcons(Fmakesym("CAR"),NIL)))))))))))))));Fset_opt(Fmakesym("*PRIMITIVE*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*SPECIAL-FORM*"),Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("SETQ"),Fcons(Fmakesym("IF"),Fcons(Fmakesym("PROGN"),Fcons(Fmakesym("DEFUN"),Fcons(Fmakesym("DEFGLOBAL"),Fcons(Fmakesym("DEFDYNAMIC"),Fcons(Fmakesym("COND"),Fcons(Fmakesym("LAMBDA"),Fcons(Fmakesym("FUNCTION"),Fcons(Fmakesym("LET"),Fcons(Fmakesym("LET*"),NIL)))))))))))));Fset_opt(Fmakesym("*SPECIAL-FORM*"),FAST_GLOBAL);
}