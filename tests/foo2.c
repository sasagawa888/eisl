static int FOO(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_plus(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO1(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_numeqp(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO2(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_greaterp(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO3(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_eqgreaterp(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO4(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_smallerp(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO5(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_eqsmallerp(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO6(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_mod(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO7(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_minus(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO8(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_mult(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO9(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(X,Flist1(Y)))
;
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO10(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(X,Flist1(Y)))
;
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
