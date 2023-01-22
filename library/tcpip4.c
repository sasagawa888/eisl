void init_declare(void){
Fsetcatchsymbols(NIL);;;;;;;;Fsetdynenv(Fmakesym("*DEFAULT-IP-VERSION*"),Fmakesym("IPV4"));Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(T))
;Feval(Fcons(Fmakesym("DEFCLASS"),Fcons(Fmakesym("SOCKET"),Fcons(NIL,Fcons(Fcons(Fcons(Fmakesym("IP"),Fcons(Fmakesym(":ACCESSOR"),Fcons(Fmakesym("SOCKET-IP"),Fcons(Fmakesym(":INITFORM"),Fcons(NIL,NIL))))),Fcons(Fcons(Fmakesym("N"),Fcons(Fmakesym(":ACCESSOR"),Fcons(Fmakesym("SOCKET-N"),Fcons(Fmakesym(":INITFORM"),Fcons(Fmakeint(5000),NIL))))),Fcons(Fcons(Fmakesym("D"),Fcons(Fmakesym(":ACCESSOR"),Fcons(Fmakesym("SOCKET-D"),Fcons(Fmakesym(":INITFORM"),Fcons(Fmakeint(0),NIL))))),NIL))),NIL)))));Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(NIL))
;
