#include "fast.h"
int f_FIBstar(int arglist);int FIBstar(int N);
int f_FIBstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIBstar(fast_convert(arg1))));
}
int FIBstar(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(N),fast_convert(Fmakestrflt("1.0"))) != NIL){
res = Fmakestrflt("1.0");}
else if(fast_numeqp(fast_convert(N),fast_convert(Fmakestrflt("2.0"))) != NIL){
res = Fmakestrflt("1.0");}
else{
res = fast_plus(fast_convert(FIBstar(fast_minus(fast_convert(N),fast_convert(Fmakestrflt("1.0"))))),fast_convert(FIBstar(fast_minus(fast_convert(N),fast_convert(Fmakestrflt("2.0"))))));}
;res;});
if(CELLRANGE(N)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("FIB*" , f_FIBstar);
}void init_declare(void){
Fsetcatchsymbols(NIL);}