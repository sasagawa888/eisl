void init_declare(void){int th=0;
signal(SIGINT, signal_handler_c);
Fsetcatchsymbols(NIL);({int res=NIL;
if(Fpcallsubr(Fcar(Fmakesym("PROBE-FILE")),Flist1(Fmakestr("/usr/local/share/eisl/library/unistd.o")),th)
 != NIL){
res = Fpcallsubr(Fcar(Fmakesym("LOAD")),Flist1(Fmakestr("/usr/local/share/eisl/library/unistd.o")),th)
;}
else if(Fpcallsubr(Fcar(Fmakesym("PROBE-FILE")),Flist1(Fmakestr("/usr/local/share/eisl/library/unistd.lsp")),th)
 != NIL){
res = Fpcallsubr(Fcar(Fmakesym("LOAD")),Flist1(Fmakestr("/usr/local/share/eisl/library/unistd.lsp")),th)
;}
;res;});}