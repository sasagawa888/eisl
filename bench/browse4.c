void init_declare(void){int th=0;
signal(SIGINT, signal_handler_c);
Fsetcatchsymbols(NIL);Fset_cdr(Fmakesym("BROWSE-RAND"),Fbigxtoparmanent(Fmakeint(21)));Fset_opt(Fmakesym("BROWSE-RAND"),GLOBAL);
Fset_cdr(Fmakesym("*BROWSE-COUNTER*"),Fbigxtoparmanent(Fmakeint(1)));Fset_opt(Fmakesym("*BROWSE-COUNTER*"),GLOBAL);
Fpeval(Fcons(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK"),Fcons(T,NIL)),0);
Fpeval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("BROWSE-CHAR1"),Fcons(Fcons(Fmakesym("X"),NIL),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("ELT"),Fcons(Fcons(Fmakesym("CONVERT"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("<STRING>"),NIL))),Fcons(Fmakeint(0),NIL))),NIL)),NIL)))),0);
Fpeval(Fcons(Fmakesym("EISL-IGNORE-TOPLEVEL-CHECK"),Fcons(NIL,NIL)),0);
