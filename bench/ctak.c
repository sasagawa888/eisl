#include "fast.h"
jmp_buf c_CTAK_AUX[50];
int f_CTAK(int arglist);int CTAK(int X,int Y,int Z);
int f_CTAK_AUX(int arglist);int CTAK_AUX(int X,int Y,int Z);
int f_CTAK(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(CTAK(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_CTAK_AUX(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(CTAK_AUX(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int CTAK(int X,int Y,int Z){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(Z)) Fshelterpush(Z);
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("CTAK-AUX"));
Fsetprop(Fmakesym("CTAK-AUX"),i+1);
ret=setjmp(c_CTAK_AUX[i]);if(ret == 0){
res = CTAK_AUX(X,Y,Z);Fsetprop(Fmakesym("CTAK-AUX"),i);
}
 else{
ret = 0;
res=catch_arg;}
res;});
if(CELLRANGE(Z)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CTAK_AUX(int X,int Y,int Z){
int res;
int temp1,temp2,temp3;
CTAK_AUXloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(Z)) Fshelterpush(Z);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_eqgreaterp(fast_convert(Y),fast_convert(X)) != NIL){
res = ({int res,i;
res = Z;catch_arg=res;
 i = Fgetprop(Fmakesym("CTAK-AUX"));
Fsetprop(Fmakesym("CTAK-AUX"),i-1);
longjmp(c_CTAK_AUX[i-1],1);res;})
;}
else{
{
temp1 = ({int res,ret,i;
 i = Fgetprop(Fmakesym("CTAK-AUX"));
Fsetprop(Fmakesym("CTAK-AUX"),i+1);
ret=setjmp(c_CTAK_AUX[i]);if(ret == 0){
res = CTAK_AUX(fast_minus(fast_convert(X),fast_convert(fast_immediate(1))),Y,Z);Fsetprop(Fmakesym("CTAK-AUX"),i);
}
 else{
ret = 0;
res=catch_arg;}
res;});
temp2 = ({int res,ret,i;
 i = Fgetprop(Fmakesym("CTAK-AUX"));
Fsetprop(Fmakesym("CTAK-AUX"),i+1);
ret=setjmp(c_CTAK_AUX[i]);if(ret == 0){
res = CTAK_AUX(fast_minus(fast_convert(Y),fast_convert(fast_immediate(1))),Z,X);Fsetprop(Fmakesym("CTAK-AUX"),i);
}
 else{
ret = 0;
res=catch_arg;}
res;});
temp3 = ({int res,ret,i;
 i = Fgetprop(Fmakesym("CTAK-AUX"));
Fsetprop(Fmakesym("CTAK-AUX"),i+1);
ret=setjmp(c_CTAK_AUX[i]);if(ret == 0){
res = CTAK_AUX(fast_minus(fast_convert(Z),fast_convert(fast_immediate(1))),X,Y);Fsetprop(Fmakesym("CTAK-AUX"),i);
}
 else{
ret = 0;
res=catch_arg;}
res;});
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(Z)) Fshelterpop();
X = temp1;
Y = temp2;
Z = temp3;
goto CTAK_AUXloop;};}res;})
;
if(CELLRANGE(Z)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("CTAK" , f_CTAK);
(deftfunc)("CTAK-AUX" , f_CTAK_AUX);
}void init_declare(void){
Fsetcatchsymbols(Fcons(Fmakesym("CTAK-AUX"),NIL));}