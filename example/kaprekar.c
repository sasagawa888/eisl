#include "fast.h"
int f_KAPREKARP(int arglist);int KAPREKARP(int N);
int f_KAPREKAR(int arglist);int KAPREKAR(int N);
int f_SORT(int arglist);int SORT(int X,int FUN);
int f_SORT1(int arglist);int SORT1(int X,int Y,int FUN);
int f_INSERT(int arglist);int INSERT(int X,int LS,int FUN);
int f_LIST_TO_NUMBER(int arglist);int LIST_TO_NUMBER(int LS);
int f_LIST_TO_NUMBER1(int arglist);int LIST_TO_NUMBER1(int LS,int N);
int f_NUMBER_TO_LIST(int arglist);int NUMBER_TO_LIST(int N);
int f_KAPREKARP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(KAPREKARP(fast_convert(arg1))));
}
int f_KAPREKAR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(KAPREKAR(fast_convert(arg1))));
}
int f_SORT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SORT(fast_convert(arg1),fast_convert(arg2))));
}
int f_SORT1(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(SORT1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_INSERT(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(INSERT(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_LIST_TO_NUMBER(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LIST_TO_NUMBER(fast_convert(arg1))));
}
int f_LIST_TO_NUMBER1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LIST_TO_NUMBER1(fast_convert(arg1),fast_convert(arg2))));
}
int f_NUMBER_TO_LIST(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(NUMBER_TO_LIST(fast_convert(arg1))));
}
int KAPREKARP(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int LS = fast_convert(NUMBER_TO_LIST(N));int A = fast_convert(LIST_TO_NUMBER(SORT(LS,Fcar(Fmakesym(">")))));int B = fast_convert(LIST_TO_NUMBER(SORT(LS,Fcar(Fmakesym("<")))));res = ({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(({int res;Fargpush(fast_convert(A));Fargpush(fast_convert(B));res=fast_minus();res;})));res=fast_numeqp();res;});
res;})
;
if(CELLRANGE(N)) N=Fshelterpop();
return(res);}
int KAPREKAR(int N){
int res;
int temp1;
KAPREKARloop:
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int LS = fast_convert(NUMBER_TO_LIST(N));int A = fast_convert(LIST_TO_NUMBER(SORT(LS,Fcar(Fmakesym(">")))));int B = fast_convert(LIST_TO_NUMBER(SORT(LS,Fcar(Fmakesym("<")))));res = ({int res=NIL;
if(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(({int res;Fargpush(fast_convert(A));Fargpush(fast_convert(B));res=fast_minus();res;})));res=fast_numeqp();res;}) != NIL){
res = T;}
else{
res = ({int arg1,res;
arg1 = fast_inverse(({int res;Fargpush(fast_convert(A));Fargpush(fast_convert(B));res=fast_minus();res;}));
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("PRINT")),Flist1(arg1)));
;res;});
{
temp1 = ({int res;Fargpush(fast_convert(A));Fargpush(fast_convert(B));res=fast_minus();res;});
if(CELLRANGE(N)) N=Fshelterpop();
N = temp1;
goto KAPREKARloop;};}
;res;});
res;})
;
if(CELLRANGE(N)) N=Fshelterpop();
return(res);}
int SORT(int X,int FUN){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(FUN)) Fshelterpush(FUN);
if(Ffreecell() < 900) Fgbc();
res = SORT1(X,NIL,FUN);
if(CELLRANGE(FUN)) FUN=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
int SORT1(int X,int Y,int FUN){
int res;
int temp1,temp2,temp3;
SORT1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(FUN)) Fshelterpush(FUN);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int arg1,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(arg1)));
;res;}) != NIL){
res = Y;}
else{
{
temp1 = fast_convert(fast_cdr(X));
temp2 = INSERT(fast_convert(fast_car(X)),Y,FUN);
temp3 = FUN;
if(CELLRANGE(X)) X=Fshelterpop();
if(CELLRANGE(Y)) Y=Fshelterpop();
if(CELLRANGE(FUN)) FUN=Fshelterpop();
X = temp1;
Y = temp2;
FUN = temp3;
goto SORT1loop;};}res;})
;
if(CELLRANGE(FUN)) FUN=Fshelterpop();
if(CELLRANGE(Y)) Y=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
int INSERT(int X,int LS,int FUN){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(FUN)) Fshelterpush(FUN);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int arg1,res;
arg1 = fast_inverse(LS);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(arg1)));
;res;}) != NIL){
res = Fcons(fast_inverse(X),fast_inverse(LS));}
else if(fast_not(({int arg1,arg2,arg3,res;
arg1 = fast_inverse(FUN);
Fshelterpush(arg1);
arg2 = fast_inverse(X);
Fshelterpush(arg2);
arg3 = fast_inverse(fast_convert(fast_car(LS)));
Fshelterpush(arg3);
arg3=Fshelterpop();
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(arg1,Fcons(arg2,Flist1(arg3)))));
;res;})) != NIL){
res = Fcons(fast_inverse(fast_convert(fast_car(LS))),fast_inverse(INSERT(X,fast_convert(fast_cdr(LS)),FUN)));}
else{
res = Fcons(fast_inverse(X),fast_inverse(LS));}
;res;});
if(CELLRANGE(FUN)) FUN=Fshelterpop();
if(CELLRANGE(LS)) LS=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
int LIST_TO_NUMBER(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = LIST_TO_NUMBER1(LS,fast_immediate(0));
if(CELLRANGE(LS)) LS=Fshelterpop();
return(res);}
int LIST_TO_NUMBER1(int LS,int N){
int res;
int temp1,temp2;
LIST_TO_NUMBER1loop:
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int arg1,res;
arg1 = fast_inverse(LS);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(arg1)));
;res;}) != NIL){
res = N;}
else{
{
temp1 = fast_convert(fast_cdr(LS));
temp2 = ({int res;Fargpush(fast_convert(fast_convert(fast_car(LS))));Fargpush(fast_convert(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(10)));res=fast_mult();res;})));res=fast_plus();res;});
if(CELLRANGE(LS)) LS=Fshelterpop();
if(CELLRANGE(N)) N=Fshelterpop();
LS = temp1;
N = temp2;
goto LIST_TO_NUMBER1loop;};}res;})
;
if(CELLRANGE(N)) N=Fshelterpop();
if(CELLRANGE(LS)) LS=Fshelterpop();
return(res);}
int NUMBER_TO_LIST(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(10)));res=fast_smallerp();res;}) != NIL){
res = ({int arg1,res;
arg1 = fast_inverse(N);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(arg1)));
;res;});}
else{
res = ({int arg1,arg2,res;
arg1 = fast_inverse(NUMBER_TO_LIST(({int arg1,arg2,res;
arg1 = fast_inverse(N);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_immediate(10));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(arg1,Flist1(arg2))));
;res;})));
Fshelterpush(arg1);
arg2 = fast_inverse(({int arg1,res;
arg1 = fast_inverse(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(10)));res=fast_mod();res;}));
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(arg1)));
;res;}));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
;res;});}res;})
;
if(CELLRANGE(N)) N=Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("KAPREKARP" , f_KAPREKARP);
(deftfunc)("KAPREKAR" , f_KAPREKAR);
(deftfunc)("SORT" , f_SORT);
(deftfunc)("SORT1" , f_SORT1);
(deftfunc)("INSERT" , f_INSERT);
(deftfunc)("LIST-TO-NUMBER" , f_LIST_TO_NUMBER);
(deftfunc)("LIST-TO-NUMBER1" , f_LIST_TO_NUMBER1);
(deftfunc)("NUMBER-TO-LIST" , f_NUMBER_TO_LIST);
}void init_declare(void){
Fsetcatchsymbols(NIL);}