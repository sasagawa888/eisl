static int PCOEFADD(int E,int C,int X, int th){
int res;
if(CELLRANGE(E)) Fpshelterpush(E,th);
if(CELLRANGE(C)) Fpshelterpush(C,th);
if(CELLRANGE(X)) Fpshelterpush(X,th);
Fcheckgbc(th);
res = ({int res;
if((Fpcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(C),th)
 && fast_numeqp(C,fast_immediate(0))) != NIL){
res = X;}
else{
res = Fcons(E,Fcons(C,X));}res;})
;
if(CELLRANGE(X)) X=Fpshelterpop(th);
if(CELLRANGE(C)) C=Fpshelterpop(th);
if(CELLRANGE(E)) E=Fpshelterpop(th);
return(res);}
static int PCPLUS(int C,int P, int th){
int res;
if(CELLRANGE(C)) Fpshelterpush(C,th);
if(CELLRANGE(P)) Fpshelterpush(P,th);
Fcheckgbc(th);
res = ({int res;
if(fast_not(Fpcallsubr(Fcar(Fmakesym("CONSP")),Flist1(P),th)
) != NIL){
res = fast_plus(P,C);}
else{
res = ({int arg1,arg2,res;
arg1 = fast_car(P);
arg2 = ({int arg1,arg2,res;
arg1 = C;
arg2 = fast_cdr(P);
res = PCPLUS1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}res;})
;
if(CELLRANGE(P)) P=Fpshelterpop(th);
if(CELLRANGE(C)) C=Fpshelterpop(th);
return(res);}
static int PCPLUS1(int C,int X, int th){
int res;
if(CELLRANGE(C)) Fpshelterpush(C,th);
if(CELLRANGE(X)) Fpshelterpush(X,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(X),th)
 != NIL){
res = ({int res;
if((Fpcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(C),th)
 && fast_numeqp(C,fast_immediate(0))) != NIL){
res = NIL;}
else{
res = Fcons(fast_immediate(0),Fcons(C,NIL));}res;})
;}
else if((Fpcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_car(X)),th)
 && fast_numeqp(fast_car(X),fast_immediate(0))) != NIL){
res = ({int arg1,arg2,arg3,res;
arg1 = fast_immediate(0);
arg2 = ({int arg1,arg2,res;
arg1 = C;
arg2 = fast_car(fast_cdr(X));
res = PPLUS(arg1,arg2,th);
;res;});
arg3 = NIL;
res = PCOEFADD(arg1,arg2,arg3,th);
;res;});}
else{
res = Fcons(fast_car(X),Fcons(fast_car(fast_cdr(X)),({int arg1,arg2,res;
arg1 = C;
arg2 = fast_cdr(fast_cdr(X));
res = PCPLUS1(arg1,arg2,th);
;res;})));}
;res;});
if(CELLRANGE(X)) X=Fpshelterpop(th);
if(CELLRANGE(C)) C=Fpshelterpop(th);
return(res);}
static int PCTIMES(int C,int P, int th){
int res;
if(CELLRANGE(C)) Fpshelterpush(C,th);
if(CELLRANGE(P)) Fpshelterpush(P,th);
Fcheckgbc(th);
res = ({int res;
if(fast_not(Fpcallsubr(Fcar(Fmakesym("CONSP")),Flist1(P),th)
) != NIL){
res = fast_mult(C,P);}
else{
res = ({int arg1,arg2,res;
arg1 = fast_car(P);
arg2 = ({int arg1,arg2,res;
arg1 = C;
arg2 = fast_cdr(P);
res = PCTIMES1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}res;})
;
if(CELLRANGE(P)) P=Fpshelterpop(th);
if(CELLRANGE(C)) C=Fpshelterpop(th);
return(res);}
static int PCTIMES1(int C,int X, int th){
int res;
if(CELLRANGE(C)) Fpshelterpush(C,th);
if(CELLRANGE(X)) Fpshelterpush(X,th);
Fcheckgbc(th);
res = ({int res;
if(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(X),th)
 != NIL){
res = NIL;}
else{
res = ({int arg1,arg2,arg3,res;
arg1 = fast_car(X);
arg2 = ({int arg1,arg2,res;
arg1 = C;
arg2 = fast_car(fast_cdr(X));
res = PTIMES(arg1,arg2,th);
;res;});
arg3 = ({int arg1,arg2,res;
arg1 = C;
arg2 = fast_cdr(fast_cdr(X));
res = PCTIMES1(arg1,arg2,th);
;res;});
res = PCOEFADD(arg1,arg2,arg3,th);
;res;});}res;})
;
if(CELLRANGE(X)) X=Fpshelterpop(th);
if(CELLRANGE(C)) C=Fpshelterpop(th);
return(res);}
static int PPLUS(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(fast_not(Fpcallsubr(Fcar(Fmakesym("CONSP")),Flist1(X),th)
) != NIL){
res = ({int arg1,arg2,res;
arg1 = X;
arg2 = Y;
res = PCPLUS(arg1,arg2,th);
;res;});}
else if(fast_not(Fpcallsubr(Fcar(Fmakesym("CONSP")),Flist1(Y),th)
) != NIL){
res = ({int arg1,arg2,res;
arg1 = Y;
arg2 = X;
res = PCPLUS(arg1,arg2,th);
;res;});}
else if(fast_eq(fast_car(X),fast_car(Y)) != NIL){
res = ({int arg1,arg2,res;
arg1 = fast_car(X);
arg2 = ({int arg1,arg2,res;
arg1 = fast_cdr(Y);
arg2 = fast_cdr(X);
res = PPLUS1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}
else if(fast_greaterp(({int arg1,arg2,res;
arg1 = fast_car(X);
Fpshelterpush(arg1,th);
arg2 = Fmakesym("ORDER");
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;}),({int arg1,arg2,res;
arg1 = fast_car(Y);
Fpshelterpush(arg1,th);
arg2 = Fmakesym("ORDER");
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;})) != NIL){
res = ({int arg1,arg2,res;
arg1 = fast_car(X);
arg2 = ({int arg1,arg2,res;
arg1 = Y;
arg2 = fast_cdr(X);
res = PCPLUS1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}
else{
res = ({int arg1,arg2,res;
arg1 = fast_car(Y);
arg2 = ({int arg1,arg2,res;
arg1 = X;
arg2 = fast_cdr(Y);
res = PCPLUS1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}
;res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int PPLUS1(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(X),th)
 != NIL){
res = Y;}
else if(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(Y),th)
 != NIL){
res = X;}
else if(fast_numeqp(fast_car(X),fast_car(Y)) != NIL){
res = ({int arg1,arg2,arg3,res;
arg1 = fast_car(X);
arg2 = ({int arg1,arg2,res;
arg1 = fast_car(fast_cdr(X));
arg2 = fast_car(fast_cdr(Y));
res = PPLUS(arg1,arg2,th);
;res;});
arg3 = ({int arg1,arg2,res;
arg1 = fast_cdr(fast_cdr(X));
arg2 = fast_cdr(fast_cdr(Y));
res = PPLUS1(arg1,arg2,th);
;res;});
res = PCOEFADD(arg1,arg2,arg3,th);
;res;});}
else if(fast_greaterp(fast_car(X),fast_car(Y)) != NIL){
res = Fcons(fast_car(X),Fcons(fast_car(fast_cdr(X)),({int arg1,arg2,res;
arg1 = fast_cdr(fast_cdr(X));
arg2 = Y;
res = PPLUS1(arg1,arg2,th);
;res;})));}
else{
res = Fcons(fast_car(Y),Fcons(fast_car(fast_cdr(Y)),({int arg1,arg2,res;
arg1 = X;
arg2 = fast_cdr(fast_cdr(Y));
res = PPLUS1(arg1,arg2,th);
;res;})));}
;res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int PSIMP(int VAR,int X, int th){
int res;
if(CELLRANGE(VAR)) Fpshelterpush(VAR,th);
if(CELLRANGE(X)) Fpshelterpush(X,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(X),th)
 != NIL){
res = fast_immediate(0);}
else if(fast_not(Fpcallsubr(Fcar(Fmakesym("CONSP")),Flist1(X),th)
) != NIL){
res = X;}
else if((Fpcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_car(X)),th)
 && fast_numeqp(fast_car(X),fast_immediate(0))) != NIL){
res = fast_car(fast_cdr(X));}
else{
res = Fcons(VAR,X);}
;res;});
if(CELLRANGE(X)) X=Fpshelterpop(th);
if(CELLRANGE(VAR)) VAR=Fpshelterpop(th);
return(res);}
static int PTIMES(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(((Fpcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(X),th)
 && fast_numeqp(X,fast_immediate(0))) || (Fpcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(Y),th)
 && fast_numeqp(Y,fast_immediate(0)))) != NIL){
res = fast_immediate(0);}
else if(fast_not(Fpcallsubr(Fcar(Fmakesym("CONSP")),Flist1(X),th)
) != NIL){
res = ({int arg1,arg2,res;
arg1 = X;
arg2 = Y;
res = PCTIMES(arg1,arg2,th);
;res;});}
else if(fast_not(Fpcallsubr(Fcar(Fmakesym("CONSP")),Flist1(Y),th)
) != NIL){
res = ({int arg1,arg2,res;
arg1 = Y;
arg2 = X;
res = PCTIMES(arg1,arg2,th);
;res;});}
else if(fast_eq(fast_car(X),fast_car(Y)) != NIL){
res = ({int arg1,arg2,res;
arg1 = fast_car(X);
arg2 = ({int arg1,arg2,res;
arg1 = fast_cdr(X);
arg2 = fast_cdr(Y);
res = PTIMES1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}
else if(fast_greaterp(({int arg1,arg2,res;
arg1 = fast_car(X);
Fpshelterpush(arg1,th);
arg2 = Fmakesym("ORDER");
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;}),({int arg1,arg2,res;
arg1 = fast_car(Y);
Fpshelterpush(arg1,th);
arg2 = Fmakesym("ORDER");
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;})) != NIL){
res = ({int arg1,arg2,res;
arg1 = fast_car(X);
arg2 = ({int arg1,arg2,res;
arg1 = Y;
arg2 = fast_cdr(X);
res = PCTIMES1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}
else{
res = ({int arg1,arg2,res;
arg1 = fast_car(Y);
arg2 = ({int arg1,arg2,res;
arg1 = X;
arg2 = fast_cdr(Y);
res = PCTIMES1(arg1,arg2,th);
;res;});
res = PSIMP(arg1,arg2,th);
;res;});}
;res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int PTIMES1(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc(th);
res = ({int res,val,save,dynpt;
 save=Fgetdynpt();
dynpt=Fgetdynpt();Fpshelterpush(dynpt,th);Fsetdynpt(save);
val=X;Fsetdynpt(dynpt);Fpshelterpop(th);Fpadddynenv(Fmakesym("*X*"),val,th);res = ({int res,val,save,dynpt;
 save=Fgetdynpt();
dynpt=Fgetdynpt();Fpshelterpush(dynpt,th);Fsetdynpt(save);
val=({int arg1,res;
arg1 = Y;
res = PTIMES2(arg1,th);
;res;});Fsetdynpt(dynpt);Fpshelterpop(th);Fpadddynenv(Fmakesym("U*"),val,th);res = ({int res,val,save,dynpt;
 save=Fgetdynpt();
dynpt=Fgetdynpt();Fpshelterpush(dynpt,th);Fsetdynpt(save);
val=