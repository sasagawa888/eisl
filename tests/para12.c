static int PFIB(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(fast_numeqp(N,fast_immediate(0)) != NIL){
res = fast_immediate(0);}
else if(fast_numeqp(N,fast_immediate(1)) != NIL){
res = fast_immediate(1);}
else{
res = ({int res; Fclear_parent_buffer(4);Fsend_to_child(0,Fsexp_to_str(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(1)),NIL))));
Fsend_to_child(1,Fsexp_to_str(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(2)),NIL))));
Fwait_all(2);res=Fpapply(Fcar(Fmakesym("+")),Fcons(Fstr_to_sexp(Freceive_from_child(0)),Fcons(Fstr_to_sexp(Freceive_from_child(1)),NIL)),0);res;});}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int FIB(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(fast_numeqp(N,fast_immediate(0)) != NIL){
res = fast_immediate(0);}
else if(fast_numeqp(N,fast_immediate(1)) != NIL){
res = fast_immediate(1);}
else{
res = fast_plus(({int arg1,res;
arg1 = fast_minus(N,fast_immediate(1));
res = FIB(arg1,th);
;res;}),({int arg1,res;
arg1 = fast_minus(N,fast_immediate(2));
res = FIB(arg1,th);
;res;}));}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int PTARAI(int X,int Y,int Z, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
if(CELLRANGE(Z)) Fpshelterpush(Z,th);
Fcheckgbc(th);
res = ({int res;
if(fast_eqsmallerp(X,Y) != NIL){
res = Y;}
else{
res = ({int res; Fclear_parent_buffer(5);Fsend_to_child(0,Fsexp_to_str(Fcons(Fmakesym("TARAI"),Fcons(fast_minus(X,fast_immediate(1)),Fcons(Y,Fcons(Z,NIL))))));
Fsend_to_child(1,Fsexp_to_str(Fcons(Fmakesym("TARAI"),Fcons(fast_minus(Y,fast_immediate(1)),Fcons(Z,Fcons(X,NIL))))));
Fsend_to_child(2,Fsexp_to_str(Fcons(Fmakesym("TARAI"),Fcons(fast_minus(Z,fast_immediate(1)),Fcons(X,Fcons(Y,NIL))))));
Fwait_all(3);res=Fpapply(Fcar(Fmakesym("TARAI")),Fcons(Fstr_to_sexp(Freceive_from_child(0)),Fcons(Fstr_to_sexp(Freceive_from_child(1)),Fcons(Fstr_to_sexp(Freceive_from_child(2)),NIL))),0);res;});}res;})
;
if(CELLRANGE(Z)) Z=Fpshelterpop(th);
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int TARAI(int X,int Y,int Z, int th){
int res;
int temp1,temp2,temp3,temp4,temp5;
TARAIloop:
 if(exit_flag == 1){exit_flag = 0; Fjump_to_repl();}if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
if(CELLRANGE(Z)) Fpshelterpush(Z,th);
Fcheckgbc(th);
res = ({int res;
if(fast_eqsmallerp(X,Y) != NIL){
res = Y;}
else{
{
temp1 = ({int arg1,arg2,arg3,res;
arg1 = fast_minus(X,fast_immediate(1));
arg2 = Y;
arg3 = Z;
res = TARAI(arg1,arg2,arg3,th);
;res;});
temp2 = ({int arg1,arg2,arg3,res;
arg1 = fast_minus(Y,fast_immediate(1));
arg2 = Z;
arg3 = X;
res = TARAI(arg1,arg2,arg3,th);
;res;});
temp3 = ({int arg1,arg2,arg3,res;
arg1 = fast_minus(Z,fast_immediate(1));
arg2 = X;
arg3 = Y;
res = TARAI(arg1,arg2,arg3,th);
;res;});
if(CELLRANGE(X)) X=Fpshelterpop(th);
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(Z)) Z=Fpshelterpop(th);
X = temp1;
1;
Y = temp2;
2;
Z = temp3;
3;
goto TARAIloop;};}res;})
;
if(CELLRANGE(Z)) Z=Fpshelterpop(th);
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int PCOUNT(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int res; Fclear_parent_buffer(3);Fsend_to_child(0,Fsexp_to_str(Fcons(Fmakesym("COUNT1"),Fcons(fast_immediate(1),Fcons(Fpcallsubr(Fcar(Fmakesym("DIV")),Fcons(N,Flist1(fast_immediate(2))),th)
,NIL)))));
Fsend_to_child(1,Fsexp_to_str(Fcons(Fmakesym("COUNT1"),Fcons(fast_plus(Fpcallsubr(Fcar(Fmakesym("DIV")),Fcons(N,Flist1(fast_immediate(2))),th)
,fast_immediate(1)),Fcons(N,NIL)))));
Fwait_all(2);res=Fstr_to_sexp(Freceive_from_child(0));res=Fstr_to_sexp(Freceive_from_child(1));res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int COUNT(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int arg1,arg2,res;
arg1 = fast_immediate(1);
arg2 = N;
res = COUNT1(arg1,arg2,th);
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int COUNT1(int M,int N, int th){
int res;
if(CELLRANGE(M)) Fpshelterpush(M,th);
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int res;
Fcheckgbc(th);
int Isubst = M;int temp1,temp2,temp3;
while(fast_numeqp(Isubst,N) == NIL){
Fpcallsubr(Fcar(Fmakesym("SIN")),Flist1(Fpcallsubr(Fcar(Fmakesym("COS")),Flist1(Fpcallsubr(Fcar(Fmakesym("TAN")),Flist1(Isubst),th)
),th)
),th)
;
temp1 = fast_plus(Isubst,fast_immediate(1));
Isubst = temp1;
}
res = T;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
if(CELLRANGE(M)) M=Fpshelterpop(th);
return(res);}
static int PRIMEPstar(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(fast_numeqp(N,fast_immediate(2)) != NIL){
res = T;}
else if(fast_numeqp(fast_mod(N,fast_immediate(2)),fast_immediate(0)) != NIL){
res = NIL;}
else{
res = ({int res;int LIMIT = Fpcallsubr(Fcar(Fmakesym("ISQRT")),Flist1(N),th)
;int SPAN = Fpcallsubr(Fcar(Fmakesym("DIV")),Fcons(LIMIT,Flist1(fast_immediate(2))),th)
;res = ({int res; Fclear_parent_buffer(2);Fsend_to_child(0,Fsexp_to_str(Fcons(Fmakesym("COPRIMEP"),Fcons(N,Fcons(({int arg1,res;
arg1 = SPAN;
res = NEAR_ODD(arg1,th);
;res;}),Fcons(LIMIT,NIL))))));
res = Fwait_and(2); res;});
res;})
;}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int NEAR_ODD(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int res;
if(fast_numeqp(fast_mod(N,fast_immediate(2)),fast_immediate(0)) != NIL){
res = fast_minus(N,fast_immediate(1));}
else{
res = N;}res;})
;
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int COPRIMEP(int N,int S,int E, int th){
int res;
int temp1,temp2,temp3,temp4,temp5;
COPRIMEPloop:
 if(exit_flag == 1){exit_flag = 0; Fjump_to_repl();}if(CELLRANGE(N)) Fpshelterpush(N,th);
if(CELLRANGE(S)) Fpshelterpush(S,th);
if(CELLRANGE(E)) Fpshelterpush(E,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(fast_greaterp(S,E) != NIL){
res = T;}
else if(fast_numeqp(fast_mod(N,S),fast_immediate(0)) != NIL){
res = NIL;}
else{
{
temp1 = N;
temp2 = fast_plus(S,fast_immediate(2));
temp3 = E;
if(CELLRANGE(N)) N=Fpshelterpop(th);
if(CELLRANGE(S)) S=Fpshelterpop(th);
if(CELLRANGE(E)) E=Fpshelterpop(th);
N = temp1;
1;
S = temp2;
2;
E = temp3;
3;
goto COPRIMEPloop;};}
;res;});
if(CELLRANGE(E)) E=Fpshelterpop(th);
if(CELLRANGE(S)) S=Fpshelterpop(th);
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int PRIMEP(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(fast_numeqp(N,fast_immediate(2)) != NIL){
res = T;}
else if(fast_numeqp(fast_mod(N,fast_immediate(2)),fast_immediate(0)) != NIL){
res = NIL;}
else{
res = ({int arg1,arg2,arg3,res;
arg1 = N;
arg2 = fast_immediate(3);
arg3 = Fpcallsubr(Fcar(Fmakesym("ISQRT")),Flist1(N),th)
;
res = COPRIMEP(arg1,arg2,arg3,th);
;res;});}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
