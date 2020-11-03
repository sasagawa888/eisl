#include "fast.h"
int f_QSORT(int arglist);int QSORT(int LAMBDA,int LIST);
int f_QSORT2(int arglist);int QSORT2(int LAMBDA,int P,int LIST,int LEFT,int RIGHT);
int f_NQUEEN(int arglist);int NQUEEN(int N);
int f_NQUEEN2(int arglist);int NQUEEN2(int N,int Y,int BOARD);
int f_DIAGONAL(int arglist);int DIAGONAL(int X,int QUEEN,int BOARD);
int f_QSORT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(QSORT(fast_convert(arg1),fast_convert(arg2))));
}
int f_QSORT2(int arglist){
int arg1,arg2,arg3,arg4,arg5;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
return(fast_inverse(QSORT2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5))));
}
int f_NQUEEN(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(NQUEEN(fast_convert(arg1))));
}
int f_NQUEEN2(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(NQUEEN2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_DIAGONAL(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(DIAGONAL(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int QSORT(int LAMBDA,int LIST){
int res;
if(CELLRANGE(LAMBDA)) Fshelterpush(LAMBDA);
if(CELLRANGE(LIST)) Fshelterpush(LIST);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LIST)))) != NIL){
res = LIST;}
else{
res = QSORT2(LAMBDA,fast_convert(fast_car(LIST)),fast_convert(fast_cdr(LIST)),NIL,NIL);}res;})
;
if(CELLRANGE(LIST)) LIST=Fshelterpop();
if(CELLRANGE(LAMBDA)) LAMBDA=Fshelterpop();
return(res);}
int QSORT2(int LAMBDA,int P,int LIST,int LEFT,int RIGHT){
int res;
int temp1,temp2,temp3,temp4,temp5;
QSORT2loop:
if(CELLRANGE(LAMBDA)) Fshelterpush(LAMBDA);
if(CELLRANGE(P)) Fshelterpush(P);
if(CELLRANGE(LIST)) Fshelterpush(LIST);
if(CELLRANGE(LEFT)) Fshelterpush(LEFT);
if(CELLRANGE(RIGHT)) Fshelterpush(RIGHT);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LIST)))) != NIL){
res = ({int arg1,arg2,res;
arg1 = fast_inverse(QSORT(LAMBDA,LEFT));
Fshelterpush(arg1);
arg2 = fast_inverse(Fcons(fast_inverse(P),fast_inverse(QSORT(LAMBDA,RIGHT))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;});}
else{
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("APPLY")),Fcons(fast_inverse(LAMBDA),Fcons(fast_inverse(fast_convert(fast_car(LIST))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(P)))))))))) != NIL){
{
temp1 = LAMBDA;
temp2 = P;
temp3 = fast_convert(fast_cdr(LIST));
temp4 = Fcons(fast_inverse(fast_convert(fast_car(LIST))),fast_inverse(LEFT));
temp5 = RIGHT;
if(CELLRANGE(LAMBDA)) LAMBDA=Fshelterpop();
if(CELLRANGE(P)) P=Fshelterpop();
if(CELLRANGE(LIST)) LIST=Fshelterpop();
if(CELLRANGE(LEFT)) LEFT=Fshelterpop();
if(CELLRANGE(RIGHT)) RIGHT=Fshelterpop();
LAMBDA = temp1;
P = temp2;
LIST = temp3;
LEFT = temp4;
RIGHT = temp5;
goto QSORT2loop;};}
else{
{
temp1 = LAMBDA;
temp2 = P;
temp3 = fast_convert(fast_cdr(LIST));
temp4 = LEFT;
temp5 = Fcons(fast_inverse(fast_convert(fast_car(LIST))),fast_inverse(RIGHT));
if(CELLRANGE(LAMBDA)) LAMBDA=Fshelterpop();
if(CELLRANGE(P)) P=Fshelterpop();
if(CELLRANGE(LIST)) LIST=Fshelterpop();
if(CELLRANGE(LEFT)) LEFT=Fshelterpop();
if(CELLRANGE(RIGHT)) RIGHT=Fshelterpop();
LAMBDA = temp1;
P = temp2;
LIST = temp3;
LEFT = temp4;
RIGHT = temp5;
goto QSORT2loop;};}res;})
;}res;})
;
if(CELLRANGE(RIGHT)) RIGHT=Fshelterpop();
if(CELLRANGE(LEFT)) LEFT=Fshelterpop();
if(CELLRANGE(LIST)) LIST=Fshelterpop();
if(CELLRANGE(P)) P=Fshelterpop();
if(CELLRANGE(LAMBDA)) LAMBDA=Fshelterpop();
return(res);}
int NQUEEN(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = NQUEEN2(N,fast_immediate(1),NIL);
if(CELLRANGE(N)) N=Fshelterpop();
return(res);}
int NQUEEN2(int N,int Y,int BOARD){
int res;
int temp1,temp2,temp3;
NQUEEN2loop:
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(BOARD)) Fshelterpush(BOARD);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;Fargpush(fast_convert(Y));Fargpush(fast_convert(N));res=fast_greaterp();res;}) != NIL){
res = NIL;}
else{
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(Y),Flist1(fast_inverse(BOARD))))) || DIAGONAL(fast_immediate(1),Y,BOARD)) != NIL){
{
temp1 = N;
temp2 = ({int res;Fargpush(fast_convert(Y));Fargpush(fast_convert(fast_immediate(1)));res=fast_plus();res;});
temp3 = BOARD;
if(CELLRANGE(N)) N=Fshelterpop();
if(CELLRANGE(Y)) Y=Fshelterpop();
if(CELLRANGE(BOARD)) BOARD=Fshelterpop();
N = temp1;
Y = temp2;
BOARD = temp3;
goto NQUEEN2loop;};}
else{
res = ({int arg1,arg2,res;
arg1 = fast_inverse(({int res;
if(({int res;Fargpush(fast_convert(Flength(BOARD)));Fargpush(fast_convert(({int res;Fargpush(fast_convert(N));Fargpush(fast_convert(fast_immediate(1)));res=fast_minus();res;})));res=fast_numeqp();res;}) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(Fcons(fast_inverse(Y),fast_inverse(BOARD))))));}
else{
res = NQUEEN2(N,fast_immediate(1),Fcons(fast_inverse(Y),fast_inverse(BOARD)));}res;})
);
Fshelterpush(arg1);
arg2 = fast_inverse(NQUEEN2(N,({int res;Fargpush(fast_convert(Y));Fargpush(fast_convert(fast_immediate(1)));res=fast_plus();res;}),BOARD));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;});}res;})
;}res;})
;
if(CELLRANGE(BOARD)) BOARD=Fshelterpop();
if(CELLRANGE(Y)) Y=Fshelterpop();
if(CELLRANGE(N)) N=Fshelterpop();
return(res);}
int DIAGONAL(int X,int QUEEN,int BOARD){
int res;
int temp1,temp2,temp3;
DIAGONALloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(QUEEN)) Fshelterpush(QUEEN);
if(CELLRANGE(BOARD)) Fshelterpush(BOARD);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(BOARD)))) != NIL){
res = NIL;}
else{
res = ({int res;
if(({int res;Fargpush(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(({int res;Fargpush(fast_convert(fast_convert(fast_car(BOARD))));Fargpush(fast_convert(QUEEN));res=fast_minus();res;})))))));Fargpush(fast_convert(X));res=fast_numeqp();res;}) != NIL){
res = T;}
else{
{
temp1 = ({int res;Fargpush(fast_convert(X));Fargpush(fast_convert(fast_immediate(1)));res=fast_plus();res;});
temp2 = QUEEN;
temp3 = fast_convert(fast_cdr(BOARD));
if(CELLRANGE(X)) X=Fshelterpop();
if(CELLRANGE(QUEEN)) QUEEN=Fshelterpop();
if(CELLRANGE(BOARD)) BOARD=Fshelterpop();
X = temp1;
QUEEN = temp2;
BOARD = temp3;
goto DIAGONALloop;};}res;})
;}res;})
;
if(CELLRANGE(BOARD)) BOARD=Fshelterpop();
if(CELLRANGE(QUEEN)) QUEEN=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("QSORT" , f_QSORT);
(deftfunc)("QSORT2" , f_QSORT2);
(deftfunc)("NQUEEN" , f_NQUEEN);
(deftfunc)("NQUEEN2" , f_NQUEEN2);
(deftfunc)("DIAGONAL" , f_DIAGONAL);
}void init_declare(void){
Fsetcatchsymbols(NIL);}