void init_declare(void){
Fsetcatchsymbols(NIL);Fset_cdr(Fmakesym("*CALL-TREE*"),NIL);Fset_opt(Fmakesym("*CALL-TREE*"),GLOBAL);
Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(T))
;Feval(Fcons(Fmakesym("DEFCLASS"),Fcons(Fmakesym("C00"),Fcons(NIL,Fcons(NIL,NIL)))));Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(NIL))
;
Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(T))
;Feval(Fcons(Fmakesym("DEFCLASS"),Fcons(Fmakesym("C11"),Fcons(NIL,Fcons(NIL,NIL)))));Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(NIL))
;
Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(T))
;Feval(Fcons(Fmakesym("DEFCLASS"),Fcons(Fmakesym("C22"),Fcons(Fcons(Fmakesym("C11"),NIL),Fcons(NIL,NIL)))));Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(NIL))
;
Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(T))
;Feval(Fcons(Fmakesym("DEFCLASS"),Fcons(Fmakesym("C33"),Fcons(Fcons(Fmakesym("C22"),NIL),Fcons(NIL,NIL)))));Fcallsubr(Fcar(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK")),Flist1(NIL))
;
Fset_cdr(Fmakesym("C00"),Fapply(Fcar(Fmakesym("CREATE")),Flist1(Faux(Fmakesym("C00")))));Fset_opt(Fmakesym("C00"),GLOBAL);
Fset_cdr(Fmakesym("C11"),Fapply(Fcar(Fmakesym("CREATE")),Flist1(Faux(Fmakesym("C11")))));Fset_opt(Fmakesym("C11"),GLOBAL);
Fset_cdr(Fmakesym("C22"),Fapply(Fcar(Fmakesym("CREATE")),Flist1(Faux(Fmakesym("C22")))));Fset_opt(Fmakesym("C22"),GLOBAL);
Fset_cdr(Fmakesym("C33"),Fapply(Fcar(Fmakesym("CREATE")),Flist1(Faux(Fmakesym("C33")))));Fset_opt(Fmakesym("C3