static int dotslashtestsslashbug0(int X, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
Fset_aux(Fmakesym("dotslashtestsslashbug0"),Fcons(X,NIL));res = ({int arg1,arg2,res;
arg1 = ({Fcar(Fmakesym("dotslashtestsslashbug1"));});
Fpshelterpush(arg1,th);
arg2 = fast_immediate(10);
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;});
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
