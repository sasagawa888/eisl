#include "fast.h"
int f_benchslashcpbench0(int arglist);int benchslashcpbench0(int X);
int f_benchslashcpbench0(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(benchslashcpbench0(fast_convert(arg1))));
}
int benchslashcpbench0(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr(";; compiling ~A ..~%")),Flist1(fast_inverse(X))))));
({int res;
 res = X = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("bench/")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakestr(".lsp")))))));res;})
;
Fapply(Fcar(Fmakesym("COMPILE-FILE")),Flist1(fast_inverse(X)));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("GBC")),NIL));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("benchslashcpbench0" , f_benchslashcpbench0);
}void init_declare(void){
Fsetcatchsymbols(NIL);fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr(";; Gabriel's benchmark suite for ISLISP.~%"))))));Fset_cdr(Fmakesym("*GABRIEL-FILES*"),Fcons(Fmakestr("boyer"),Fcons(Fmakestr("browse"),Fcons(Fmakestr("ctak"),Fcons(Fmakestr("dderiv"),Fcons(Fmakestr("deriv"),Fcons(Fmakestr("destru"),Fcons(Fmakestr("div2"),Fcons(Fmakestr("fft"),Fcons(Fmakestr("fib20"),Fcons(Fmakestr("fprint"),Fcons(Fmakestr("fread"),Fcons(Fmakestr("frpoly"),Fcons(Fmakestr("puzzle"),Fcons(Fmakestr("stak"),Fcons(Fmakestr("tak"),Fcons(Fmakestr("takl"),Fcons(Fmakestr("takr"),Fcons(Fmakestr("tprint"),Fcons(Fmakestr("traverse"),Fcons(Fmakestr("triang"),NIL)))))))))))))))))))));Fset_opt(Fmakesym("*GABRIEL-FILES*"),FAST_GLOBAL);
fast_convert(Fcallsubr(Fcar(Fmakesym("MAPC")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("benchslashcpbench0"),Fcons(T,NIL));Fcar(Fmakesym("benchslashcpbench0"));})),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("*GABRIEL-FILES*"))))))));}