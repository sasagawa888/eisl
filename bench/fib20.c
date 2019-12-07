#include "fast.h"
int f_FIB(int arglist);int FIB(int N);
int f_GFIB(int arglist);int GFIB(int N);
int f_FIB(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIB(fast_convert(arg1))));
}
int f_GFIB(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GFIB(fast_convert(arg1))));
}
int FIB(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(1);}
else if(fast_eq(fast_convert(N),fast_convert(fast_immediate(2))) != NIL){
res = fast_immediate(1);}
else{
res = fast_plus(fast_convert(FIB(fast_minus(fast_convert(N),fast_convert(fast_immediate(1))))),fast_convert(FIB(fast_minus(fast_convert(N),fast_convert(fast_immediate(2))))));}
;res;});
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int GFIB(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
if(Fadaptp(N,Fmakesym("<INTEGER>")))
{res = ({int res=NIL;
if(fast_eq(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(1);}
else if(fast_eq(fast_convert(N),fast_convert(fast_immediate(2))) != NIL){
res = fast_immediate(1);}
else{
res = fast_plus(fast_convert(GFIB(fast_minus(fast_convert(N),fast_convert(fast_immediate(1))))),fast_convert(GFIB(fast_minus(fast_convert(N),fast_convert(fast_immediate(2))))));}
;res;});return(res);}
if(CELLRANGE(N)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("FIB" , f_FIB);
(deftfunc)("GFIB" , f_GFIB);
}void init_declare(void){
Fsetcatchsymbols(NIL);}