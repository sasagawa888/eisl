static int TEST_BOUNDARY1(int th){
int res;
res = 123;
return(res);}
static int TEST_BOUNDARY2(int X, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
Fcheckgbc(th);
res = ({int res;
if(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(X),th)
 != NIL){
res = Fmakesym("NIL-CASE");}
else{
res = Fmakesym("NON-NIL-CASE");}res;})
;
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
static int FOO(int th){
int res;
Fcheckgbc(th);
res = ({int arg1,arg2,res;
arg1 = TEST_BOUNDARY1(th);
Fpshelterpush(arg1,th);
arg2 = ({int arg1,res;
arg1 = T;
res = TEST_BOUNDARY2(arg1,th);
;res;});
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("LIST")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;});
return(res);}
