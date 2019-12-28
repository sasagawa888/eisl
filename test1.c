#include "fast.h"
int f_FIB(int arglist);int FIB(double N);
int f_FIB(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(Fmakedoubleflt(FIB(Fgetflt(arg1))));
}
int FIB(double N){
int res;
res = ({int res=NIL;
if(N==1.0){
res = 1.0;}
else if(N==2.0){
res = 1.0;}
else{
res = FIB(N-1.0)+FIB(N-2.0);}
;res;});
return(res);}
void init_tfunctions(void){
(deftfunc)("FIB" , f_FIB);
}void init_declare(void){
Fsetcatchsymbols(NIL);}