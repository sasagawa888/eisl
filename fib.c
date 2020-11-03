#include "fast.h"
int f_FOO(int arglist);int FOO(int X,int Y);
int f_FIBstar(int arglist);int FIBstar(int N);
int f_FIB(int arglist);int FIB(int N);
int f_FOO(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FOO(fast_convert(arg1),fast_convert(arg2))));
}
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
int FOO(int X,int Y){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(Y);
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
;res;});
if(CELLRANGE(Y)) Y=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
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
(deftfunc)("FOO" , f_FOO);
(deftfunc)("FIB*" , f_FIBstar);
(deftfunc)("FIB" , f_FIB);
}void init_declare(void){
Fsetcatchsymbols(NIL);}