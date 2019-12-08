#include "fast.h"
#include <stdio.h>
int f_ASH(int arglist);int ASH(int N,int M);
int f_ASH(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ASH(fast_convert(arg1),fast_convert(arg2))));
}
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
void init_tfunctions(void){
(deftfunc)("ASH" , f_ASH);
}void init_declare(void){
Fsetcatchsymbols(NIL);;}