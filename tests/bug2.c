static int TEST_BOUNDARY1(int th){
int res;
res = 123;
return(res);}
static int FOO(int th){
int res;
Fcheckgbc(th);
res = ({int arg1,res;
arg1 = TEST_BOUNDARY1(th);
Fpshelterpush(arg1,th);
res = Fpcallsubr(Fcar(Fmakesym("LIST")),Flist1(arg1),th);
arg1=Fpshelterpop(th);
;res;});
return(res);}
