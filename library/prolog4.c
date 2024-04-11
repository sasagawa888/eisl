void init_declare(void){int th=0;
Fsetcatchsymbols(Fcons(Fmakesym("PEISL::EXIT"),Fcons(Fmakesym("PEISL::PROVE"),Fcons(Fmakesym("EXIT"),NIL))));Fset_cdr(Fmakesym("PEISL::EPILOG"),Fbigxtoparmanent(NIL));Fset_opt(Fmakesym("PEISL::EPILOG"),GLOBAL);
Fset_cdr(Fmakesym("PEISL::USER"),Fbigxtoparmanent(NIL));Fset_opt(Fmakesym("PEISL::USER"),GLOBAL);
Fset_cdr(Fmakesym("PEISL::VARIABLE"),Fbigxtoparmanent(NIL));Fset_opt(Fmakesym("PEISL::VARIABLE"),GLOBAL);
Fset_cdr(Fmakesym("TRACE"),Fbigxtoparmanent(NIL));Fset_opt(Fmakesym("TRACE"),GLOBAL);
Fset_cdr(Fmakesym("PEISL::FIND"),Fbigxtoparmanent(NIL));Fset_opt(Fmakesym("PEISL::FIND"),GLOBAL);
