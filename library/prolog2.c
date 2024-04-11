static int PROLOG(int th){
int res;
Fcheckgbc();
res = ({int res;
Fcheckgbc();
while(Fcdr(Fmakesym("PEISL::EPILOG")) == NIL){
Fpcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(Fpcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL,th)
,Flist1(Fmakestr("-? "))),th)
;
({int res;int PEISLcoloncolonGOAL = Fpcallsubr(Fcar(Fmakesym("READ")),NIL,th)
;({int res;
 res = Fset_cdr(Fmakesym("PEISL::VARIABLE"),({int arg1,res;
arg1 = PEISLcoloncolonGOAL;
Fpshelterpush(arg1,th);
res = PEISLcoloncolonFINDVAR(arg1,th);
arg1=Fpshelterpop(th);
;res;}));res;});
res = ({int res;int PEISLcoloncolonRES = ({int res,ret,i;
 Fset_error_flag(1);
i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;int handler = 