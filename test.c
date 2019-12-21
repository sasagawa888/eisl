#include "fast.h"
#include <stdio.h>
int f_MA(int arglist);int MA(int A,int X,int B);
int f_ASH(int arglist);int ASH(int N,int M);
int f_FOO(int arglist);int FOO(int X);
int f_MA(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(MA(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_ASH(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ASH(fast_convert(arg1),fast_convert(arg2))));
}
int f_FOO(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FOO(fast_convert(arg1))));
}
int MA(int A,int X,int B){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(B)) Fshelterpush(B);
if(Ffreecell() < 900) Fgbc();
res=INT_FLAG | ((INT_MASK & A) * (INT_MASK & X) + (INT_MASK & B));
if(CELLRANGE(B)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int ASH(int N,int M){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_eqgreaterp(fast_convert(M),fast_convert(fast_immediate(0))) != NIL){
res = INT_FLAG | ((INT_MASK & N) << (INT_MASK & M));
;}
else{
res = ({int res;int M1 = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(M)))));res = res = INT_FLAG | ((INT_MASK & N) >> (INT_MASK & M1));
res;})
;}res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int FOO(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;res = fast_mult(fast_convert(X),fast_convert(X));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("MA" , f_MA);
(deftfunc)("ASH" , f_ASH);
(deftfunc)("FOO" , f_FOO);
}void init_declare(void){
Fsetcatchsymbols(NIL);;}