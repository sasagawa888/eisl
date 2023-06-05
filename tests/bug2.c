static int SUM(int XS){
int res;
if(CELLRANGE(XS)) Fshelterpush(XS);
Fcheckgbc();
res = ({int res;int A = fast_immediate(0);({int arg1,arg2,res;
arg1 = ({Fset_cdr(Fmakesym("testsslashbug0"),Fcons(A,Fcons(T,NIL)));Fcar(Fmakesym("testsslashbug0"));});
Fshelterpush(arg1);
arg2 = XS;
Fshelterpush(arg2);
res = Fcallsubr(Fcar(Fmakesym("MAPC")),Fcons(arg1,Flist1(arg2)));
arg2=Fshelterpop();
arg1=Fshelterpop();
;res;});
res = A;
res;})
;
if(CELLRANGE(XS)) XS=Fshelterpop();
return(res);}
static int SUM_A(int XS){
int res;
if(CELLRANGE(XS)) Fshelterpush(XS);
Fcheckgbc();
res = ({int res;int A = fast_immediate(0);Fcallsubr(Fcar(Fmakesym("PRINT")),Flist1(({int arg1,arg2,res;
arg1 = ({Fset_cdr(Fmakesym("testsslashbug1"),Fcons(A,Fcons(T,NIL)));Fcar(Fmakesym("testsslashbug1"));});
Fshelterpush(arg1);
arg2 = XS;
Fshelterpush(arg2);
res = Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(arg1,Flist1(arg2)));
arg2=Fshelterpop();
arg1=Fshelterpop();
;res;})))
;
res = A;
res;})
;
if(CELLRANGE(XS)) XS=Fshelterpop();
return(res);}
