static int MAKE_NODE(int th){
int res;
Fcheckgbc(th);
res = ({int res;int Xsubst = Fpcallsubr(Fcar(Fmakesym("CREATE-VECTOR")),Fcons(fast_immediate(10),Flist1(NIL)),th)
;({int arg1,arg2,arg3,res;
arg1 = SNB(th);
Fpshelterpush(arg1,th);
arg2 = Xsubst;
Fpshelterpush(arg2,th);
arg3 = fast_immediate(2);
Fpshelterpush(arg3,th);
res = Fpcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(arg1,Fcons(arg2,Flist1(arg3))),th);
arg3=Fpshelterpop(th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;});
res = 