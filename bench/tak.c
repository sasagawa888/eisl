#include "fast.h"
int f_TAK(int arglist);int TAK(int X,int Y,int Z);
int f_TAK(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(TAK(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int TAK(int X,int Y,int Z){
int res;
int temp1,temp2,temp3;
TAKloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(Z)) Fshelterpush(Z);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_eqgreaterp(fast_convert(Y),fast_convert(X)) != NIL){
res = Z;}
else{
{
temp1 = TAK(fast_minus(fast_convert(X),fast_convert(fast_immediate(1))),Y,Z);
temp2 = TAK(fast_minus(fast_convert(Y),fast_convert(fast_immediate(1))),Z,X);
temp3 = TAK(fast_minus(fast_convert(Z),fast_convert(fast_immediate(1))),X,Y);
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(Z)) Fshelterpop();
X = temp1;
Y = temp2;
Z = temp3;
goto TAKloop;};}res;})
;
if(CELLRANGE(Z)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("TAK" , f_TAK);
}void init_declare(void){
Fsetcatchsymbols(NIL);}