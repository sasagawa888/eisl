static int FOO(){
int res;
Fcheckgbc();
res = Fapply(Fcar(Fmakesym("WITH-OPEN-IO-FILE")),Fcons(Fapply(Fcar(Fmakesym("IO")),Flist1(Fmakestr("tests/test.txt"))),Fcons(({int res;
while(Fcallsubr(Fcar(Fmakesym("READ-LINE")),Fcons(