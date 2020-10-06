#include "fast.h"
jmp_buf c_CTAK_AUX[50];
int f_TARAI(int arglist);int TARAI(int X,int Y,int Z);
int f_FIB(int arglist);int FIB(int N);
int f_FIBstar(int arglist);int FIBstar(int N);
int f_ACK(int arglist);int ACK(int M,int N);
int f_GFIB(int arglist);int GFIB(int N);
int f_TAK(int arglist);int TAK(int X,int Y,int Z);
int f_LISTN(int arglist);int LISTN(int N);
int f_TAKL(int arglist);int TAKL(int X,int Y,int Z);
int f_CTAK(int arglist);int CTAK(int X,int Y,int Z);
int f_CTAK_AUX(int arglist);int CTAK_AUX(int X,int Y,int Z);
int f_TARAI(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(Fmakeint(TARAI(Fgetint(arg1),Fgetint(arg2),Fgetint(arg3))));
}
int f_FIB(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(Fmakeint(FIB(Fgetint(arg1))));
}
int f_FIBstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIBstar(fast_convert(arg1))));
}
int f_ACK(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(Fmakeint(ACK(Fgetint(arg1),Fgetint(arg2))));
}
int f_GFIB(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GFIB(fast_convert(arg1))));
}
int f_TAK(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(Fmakeint(TAK(Fgetint(arg1),Fgetint(arg2),Fgetint(arg3))));
}
int f_LISTN(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LISTN(fast_convert(arg1))));
}
int f_TAKL(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(TAKL(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
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
int TARAI(int X,int Y,int Z){
int res;
int temp1;int temp2;int temp3;
TARAIloop:
;
;
;
res = ({int res;
if(X<=Y){
res = Y;}
else{
{
temp1 = TARAI(X-1,Y,Z);
temp2 = TARAI(Y-1,Z,X);
temp3 = TARAI(Z-1,X,Y);
X = temp1;
Y = temp2;
Z = temp3;
goto TARAIloop;};}res;})
;
return(res);}
int FIB(int N){
int res;
;
res = ({int res=NIL;
if(N==1){
res = 1;}
else if(N==2){
res = 1;}
else{
res = FIB(N-1)+FIB(N-2);}
;res;});
return(res);}
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
int ACK(int M,int N){
int res;
int temp1;int temp2;
ACKloop:
;
;
res = ({int res=NIL;
if(M==0){
res = N+1;}
else if(N==0){
{
temp1 = M-1;
temp2 = 1;
M = temp1;
N = temp2;
goto ACKloop;};}
else{
{
temp1 = M-1;
temp2 = ACK(M,N-1);
M = temp1;
N = temp2;
goto ACKloop;};}
;res;});
return(res);}
int GFIB(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
if(Fadaptp(N,Fmakesym("<INTEGER>")))
{res = ({int res=NIL;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(1);}
else if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(2))) != NIL){
res = fast_immediate(1);}
else{
res = fast_plus(fast_convert(GFIB(fast_minus(fast_convert(N),fast_convert(fast_immediate(1))))),fast_convert(GFIB(fast_minus(fast_convert(N),fast_convert(fast_immediate(2))))));}
;res;});return(res);}
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int TAK(int X,int Y,int Z){
int res;
int temp1;int temp2;int temp3;
TAKloop:
;
;
;
res = ({int res;
if(Y>=X){
res = Z;}
else{
{
temp1 = TAK(X-1,Y,Z);
temp2 = TAK(Y-1,Z,X);
temp3 = TAK(Z-1,X,Y);
X = temp1;
Y = temp2;
Z = temp3;
goto TAKloop;};}res;})
;
return(res);}
int LISTN(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(fast_immediate(0)),fast_convert(N))) != NIL){
res = Fcons(fast_inverse(N),fast_inverse(LISTN(fast_minus(fast_convert(N),fast_convert(fast_immediate(1))))));}
 else res = NIL;res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int TAKL(int X,int Y,int Z){
int res;
int temp1,temp2,temp3;
TAKLloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(Z)) Fshelterpush(Z);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(fast_smallerp(fast_convert(Flength(Y)),fast_convert(Flength(X)))) != NIL){
res = Z;}
else{
{
temp1 = TAKL(fast_convert(fast_cdr(X)),Y,Z);
temp2 = TAKL(fast_convert(fast_cdr(Y)),Z,X);
temp3 = TAKL(fast_convert(fast_cdr(Z)),X,Y);
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(Z)) Fshelterpop();
X = temp1;
Y = temp2;
Z = temp3;
goto TAKLloop;};}res;})
;
if(CELLRANGE(Z)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
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
(deftfunc)("TARAI" , f_TARAI);
(deftfunc)("FIB" , f_FIB);
(deftfunc)("FIB*" , f_FIBstar);
(deftfunc)("ACK" , f_ACK);
(deftfunc)("GFIB" , f_GFIB);
(deftfunc)("TAK" , f_TAK);
(deftfunc)("LISTN" , f_LISTN);
(deftfunc)("TAKL" , f_TAKL);
(deftfunc)("CTAK" , f_CTAK);
(deftfunc)("CTAK-AUX" , f_CTAK_AUX);
}void init_declare(void){
Fsetcatchsymbols(Fcons(Fmakesym("CTAK-AUX"),NIL));Fset_cdr(Fmakesym("LL-18"),LISTN(Fmakeint(18)));Fset_opt(Fmakesym("LL-18"),FAST_CONSTN);
Fset_cdr(Fmakesym("LL-12"),LISTN(Fmakeint(12)));Fset_opt(Fmakesym("LL-12"),FAST_CONSTN);
Fset_cdr(Fmakesym("LL-6"),LISTN(Fmakeint(6)));Fset_opt(Fmakesym("LL-6"),FAST_CONSTN);
Fset_cdr(Fmakesym("LL-32"),LISTN(Fmakeint(32)));Fset_opt(Fmakesym("LL-32"),FAST_CONSTN);
Fset_cdr(Fmakesym("LL-16"),LISTN(Fmakeint(16)));Fset_opt(Fmakesym("LL-16"),FAST_CONSTN);
Fset_cdr(Fmakesym("LL-8"),LISTN(Fmakeint(8)));Fset_opt(Fmakesym("LL-8"),FAST_CONSTN);
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("SHORTERP"),Fcons(Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("<"),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("Y"),NIL)),NIL)),NIL))),NIL)),NIL)))));
}