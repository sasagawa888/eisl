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
res = ({int res;Fsend_to_child(0,Fsexp_to_str(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(1)),NIL))));
Fsend_to_child(1,Fsexp_to_str(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(2)),NIL))));
Fwait_all(2);res=Fpapply(Fcar(Fmakesym("+")),Fcons(Fstr_to_sexp(Freceive_from_child(0)),Fcons(Fstr_to_sexp(Freceive_from_child(1)),NIL)),0);res;});}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
