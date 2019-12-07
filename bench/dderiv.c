#include "fast.h"
int f_DDERIV_AUX(int arglist);int DDERIV_AUX(int A);
int f_DDERIVplus(int arglist);int DDERIVplus(int A);
int f_DDERIV_(int arglist);int DDERIV_(int A);
int f_DDERIVstar(int arglist);int DDERIVstar(int A);
int f_DDERIVslash(int arglist);int DDERIVslash(int A);
int f_DDERIV(int arglist);int DDERIV(int A);
int f_DDERIV_RUN(int arglist);int DDERIV_RUN();
int f_DDERIV_AUX(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DDERIV_AUX(fast_convert(arg1))));
}
int f_DDERIVplus(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DDERIVplus(fast_convert(arg1))));
}
int f_DDERIV_(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DDERIV_(fast_convert(arg1))));
}
int f_DDERIVstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DDERIVstar(fast_convert(arg1))));
}
int f_DDERIVslash(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DDERIVslash(fast_convert(arg1))));
}
int f_DDERIV(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DDERIV(fast_convert(arg1))));
}
int f_DDERIV_RUN(int arglist){
return(fast_inverse(DDERIV_RUN() ));
}
int DDERIV_AUX(int A){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(DDERIV(A)),Flist1(fast_inverse(A))))));res;});
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int DDERIVplus(int A){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = Fcons(fast_inverse(Fmakesym("+")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("DDERIV"))),Flist1(fast_inverse(A)))))));
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int DDERIV_(int A){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = Fcons(fast_inverse(Fmakesym("-")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("DDERIV"))),Flist1(fast_inverse(A)))))));
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int DDERIVstar(int A){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fcons(fast_inverse(Fmakesym("*")),fast_inverse(A))),Flist1(fast_inverse(Fcons(fast_inverse(Fmakesym("+")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("DDERIV-AUX"))),Flist1(fast_inverse(A)))))))))))));res;});
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int DDERIVslash(int A){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("-")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(DDERIV(fast_convert(fast_car(A)))),Flist1(fast_inverse(Fapply(Fcar(Fmakesym("CADR")),Flist1(fast_inverse(A)))))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_convert(fast_car(A))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fapply(Fcar(Fmakesym("CADR")),Flist1(fast_inverse(A)))),Fcons(fast_inverse(Fapply(Fcar(Fmakesym("CADR")),Flist1(fast_inverse(A)))),Flist1(fast_inverse(DDERIV(Fapply(Fcar(Fmakesym("CADR")),Flist1(fast_inverse(A)))))))))))))))))))))));res;});
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int DDERIV(int A){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(A))));res;}) != NIL){
res = ({int res;int DDERIV_VAR = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(fast_convert(fast_car(A))),Flist1(fast_inverse(Fmakesym("DDERIV")))))));res = ({int res;
if(DDERIV_VAR != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(fast_inverse(DDERIV_VAR),Flist1(fast_inverse(fast_convert(fast_cdr(A)))))));res;});}
else{
res = Fmakesym("ERROR");}res;})
;
res;})
;}
else{
res = ({int res;
if(fast_eq(fast_convert(A),fast_convert(Fmakesym("X"))) != NIL){
res = fast_immediate(1);}
else{
res = fast_immediate(0);}res;})
;}res;})
;
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int DDERIV_RUN(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int I = fast_convert(fast_immediate(0));int temp1;
while(fast_numeqp(fast_convert(I),fast_convert(fast_immediate(1000))) == NIL){
DDERIV(Fcons(Fmakesym("+"),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakeint(3),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("A"),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("B"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakeint(5),NIL))))));
DDERIV(Fcons(Fmakesym("+"),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakeint(3),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("A"),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("B"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakeint(5),NIL))))));
DDERIV(Fcons(Fmakesym("+"),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakeint(3),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("A"),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("B"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakeint(5),NIL))))));
DDERIV(Fcons(Fmakesym("+"),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakeint(3),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("A"),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("B"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakeint(5),NIL))))));
DDERIV(Fcons(Fmakesym("+"),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakeint(3),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("A"),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL)))),Fcons(Fcons(Fmakesym("*"),Fcons(Fmakesym("B"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakeint(5),NIL))))));
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res=NIL;res;});
return(res);}
void init_tfunctions(void){
(deftfunc)("DDERIV-AUX" , f_DDERIV_AUX);
(deftfunc)("DDERIV+" , f_DDERIVplus);
(deftfunc)("DDERIV-" , f_DDERIV_);
(deftfunc)("DDERIV*" , f_DDERIVstar);
(deftfunc)("DDERIV/" , f_DDERIVslash);
(deftfunc)("DDERIV" , f_DDERIV);
(deftfunc)("DDERIV-RUN" , f_DDERIV_RUN);
}void init_declare(void){
Fsetcatchsymbols(NIL);fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fcar(Fmakesym("DDERIV-"))),Fcons(fast_inverse(Fmakesym("-")),Flist1(fast_inverse(Fmakesym("DDERIV")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fcar(Fmakesym("DDERIV*"))),Fcons(fast_inverse(Fmakesym("*")),Flist1(fast_inverse(Fmakesym("DDERIV")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fcar(Fmakesym("DDERIV+"))),Fcons(fast_inverse(Fmakesym("+")),Flist1(fast_inverse(Fmakesym("DDERIV")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fcar(Fmakesym("DDERIV/"))),Fcons(fast_inverse(Fmakesym("/")),Flist1(fast_inverse(Fmakesym("DDERIV")))))));}