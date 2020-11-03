#include "fast.h"
int f_FIBstar(int arglist);int FIBstar(int N);
int f_FIB(int arglist);int FIB(int N);
int f_FIBstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIBstar(fast_convert(arg1))));
}
int f_FIB(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIB(fast_convert(arg1))));
}
int FIBstar(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(Fmakestrflt("1.0")));res=fast_numeqp();res;}) != NIL){
res = Fmakestrflt("1.0");}
else if(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(Fmakestrflt("2.0")));res=fast_numeqp();res;}) != NIL){
res = Fmakestrflt("1.0");}
else{
res = ({int res;Fargpush(fast_convert(FIBstar(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(Fmakestrflt("1.0")));res=fast_minus();res;}))));Fargpush(fast_convert(FIBstar(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(Fmakestrflt("2.0")));res=fast_minus();res;}))));res=fast_plus();res;});}
;res;});
if(CELLRANGE(N)) N=Fshelterpop();
return(res);}
int FIB(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(1)));res=fast_numeqp();res;}) != NIL){
res = fast_immediate(1);}
else if(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(2)));res=fast_numeqp();res;}) != NIL){
res = fast_immediate(1);}
else{
res = ({int res;Fargpush(fast_convert(FIB(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(1)));res=fast_minus();res;}))));Fargpush(fast_convert(FIB(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(2)));res=fast_minus();res;}))));res=fast_plus();res;});}
;res;});
if(CELLRANGE(N)) N=Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("FIB*" , f_FIBstar);
(deftfunc)("FIB" , f_FIB);
}void init_declare(void){
Fsetcatchsymbols(NIL);}