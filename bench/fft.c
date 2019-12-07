#include "fast.h"
int f_IPOWER(int arglist);int IPOWER(int A,int B);
int f_FFT(int arglist);int FFT(int AR,int AI);
int f_FFT_BENCH(int arglist);int FFT_BENCH();
int f_FFT_TEST(int arglist);int FFT_TEST();
int f_IPOWER(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(IPOWER(fast_convert(arg1),fast_convert(arg2))));
}
int f_FFT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FFT(fast_convert(arg1),fast_convert(arg2))));
}
int f_FFT_BENCH(int arglist){
return(fast_inverse(FFT_BENCH() ));
}
int f_FFT_TEST(int arglist){
return(fast_inverse(FFT_TEST() ));
}
int IPOWER(int A,int B){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(B)) Fshelterpush(B);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(B),fast_convert(fast_immediate(1))) != NIL){
res = A;}
else{
res = fast_mult(fast_convert(IPOWER(A,fast_minus(fast_convert(B),fast_convert(fast_immediate(1))))),fast_convert(A));}res;})
;
if(CELLRANGE(B)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int FFT(int AR,int AI){
int res;
if(CELLRANGE(AR)) Fshelterpush(AR);
if(CELLRANGE(AI)) Fshelterpush(AI);
if(Ffreecell() < 900) Fgbc();
({int res;int N = fast_convert(fast_minus(fast_convert(Flength(AR)),fast_convert(fast_immediate(1))));res = ({int res;int NV2 = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(N),Flist1(fast_inverse(fast_immediate(2)))))));int M = fast_convert(fast_immediate(0));int I = fast_convert(fast_immediate(1));int J = fast_convert(NIL);({int res;
while(fast_smallerp(fast_convert(I),fast_convert(N)) !=NIL){
({int res;
 res = M = fast_plus(fast_convert(M),fast_convert(fast_immediate(1)));res;})
;
res = ({int res;
 res = I = fast_plus(fast_convert(I),fast_convert(I));res;})
;};res;})
;
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(N),fast_convert(IPOWER(fast_immediate(2),M)))) != NIL){
res = ({int res;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("error ... array size not a power of two.~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("READ")),NIL));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-FRESH-LINE")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))))));res;});}
else{
res = ({int res;
({int res;
 res = J = fast_immediate(1);res;})
;
({int res;
 res = I = fast_immediate(1);res;})
;
({int res;
while(fast_smallerp(fast_convert(I),fast_convert(N)) !=NIL){
({int res;
if(fast_smallerp(fast_convert(I),fast_convert(J)) != NIL){
res = ({int res;int TR = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AR),Flist1(fast_inverse(J))))));int TI = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AI),Flist1(fast_inverse(J))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AR),Flist1(fast_inverse(I)))))),Fcons(fast_inverse(AR),Flist1(fast_inverse(J))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AI),Flist1(fast_inverse(I)))))),Fcons(fast_inverse(AI),Flist1(fast_inverse(J))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(TR),Fcons(fast_inverse(AR),Flist1(fast_inverse(I))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(TI),Fcons(fast_inverse(AI),Flist1(fast_inverse(I))))));
res;})
;}
 else res = NIL;res;})
;
res = ({int res;int K = fast_convert(NV2);({int res;
while(fast_smallerp(fast_convert(K),fast_convert(J)) !=NIL){
({int res;
 res = J = fast_minus(fast_convert(J),fast_convert(K));res;})
;
res = ({int res;
 res = K = fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(K),Flist1(fast_inverse(fast_immediate(2))))));res;})
;};res;})
;
({int res;
 res = J = fast_plus(fast_convert(J),fast_convert(K));res;})
;
res = ({int res;
 res = I = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));res;})
;
res;})
;};res;})
;
res = ({int res;int L = fast_convert(fast_immediate(1));res = ({int res;
while(fast_eqsmallerp(fast_convert(L),fast_convert(M)) !=NIL){
({int res;int L2 = fast_convert(IPOWER(fast_immediate(2),L));int UR = fast_convert(Fmakestrflt("1.0"));int UI = fast_convert(Fmakestrflt("0.0"));res = ({int res;int LE1 = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(L2),Flist1(fast_inverse(fast_immediate(2)))))));int WR = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("COS")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PI")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("FLOAT")),Flist1(fast_inverse(LE1))))))))))))));int WI = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("SIN")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PI")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("FLOAT")),Flist1(fast_inverse(LE1))))))))))))));({int res;int K = fast_convert(fast_immediate(1));res = ({int res;
while(fast_eqsmallerp(fast_convert(K),fast_convert(LE1)) !=NIL){
({int res;int P = fast_convert(K);res = ({int res;
while(fast_eqsmallerp(fast_convert(P),fast_convert(N)) !=NIL){
({int res;int IP = fast_convert(fast_plus(fast_convert(P),fast_convert(LE1)));res = ({int res;int TR = fast_convert(fast_minus(fast_convert(fast_mult(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AR),Flist1(fast_inverse(IP)))))),fast_convert(UR))),fast_convert(fast_mult(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AI),Flist1(fast_inverse(IP)))))),fast_convert(UI)))));int TI = fast_convert(fast_plus(fast_convert(fast_mult(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AR),Flist1(fast_inverse(IP)))))),fast_convert(UR))),fast_convert(fast_mult(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AI),Flist1(fast_inverse(IP)))))),fast_convert(UI)))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_minus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AR),Flist1(fast_inverse(P)))))),fast_convert(TR))),Fcons(fast_inverse(AR),Flist1(fast_inverse(IP))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_minus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AI),Flist1(fast_inverse(P)))))),fast_convert(TI))),Fcons(fast_inverse(AI),Flist1(fast_inverse(IP))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AR),Flist1(fast_inverse(P)))))),fast_convert(TR))),Fcons(fast_inverse(AR),Flist1(fast_inverse(P))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(AI),Flist1(fast_inverse(P)))))),fast_convert(TI))),Fcons(fast_inverse(AI),Flist1(fast_inverse(P))))));
res;})
;
res;})
;
res = ({int res;
 res = P = fast_plus(fast_convert(P),fast_convert(L2));res;})
;};res;})
;
res;})
;
res = ({int res;
 res = K = fast_plus(fast_convert(K),fast_convert(fast_immediate(1)));res;})
;};res;})
;
res;})
;
({int res;
 res = Fset_cdr(Fmakesym("NUR"),fast_inverse(fast_minus(fast_convert(fast_mult(fast_convert(UR),fast_convert(WR))),fast_convert(fast_mult(fast_convert(UI),fast_convert(WI))))));res;});
({int res;
 res = Fset_cdr(Fmakesym("NUI"),fast_inverse(fast_plus(fast_convert(fast_mult(fast_convert(UR),fast_convert(WI))),fast_convert(fast_mult(fast_convert(UI),fast_convert(WR))))));res;});
({int res;
 res = UR = fast_convert(Fcdr(Fmakesym("NUR")));res;})
;
({int res;
 res = UI = fast_convert(Fcdr(Fmakesym("NUI")));res;})
;
res = ({int res;
if(fast_convert(Fcdr(Fmakesym("VERIF"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("End of DO: ur=~S, ui=~S~%")),Fcons(fast_inverse(UR),Flist1(fast_inverse(UI)))))));}
 else res = NIL;res;})
;
res;})
;
res;})
;
res = ({int res;
 res = L = fast_plus(fast_convert(L),fast_convert(fast_immediate(1)));res;})
;};res;})
;
res;})
;res;});}res;})
;
res;})
;
res;})
;
res = T;
if(CELLRANGE(AI)) Fshelterpop();
if(CELLRANGE(AR)) Fshelterpop();
return(res);}
int FFT_BENCH(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int I = fast_convert(fast_immediate(0));int temp1;
while(fast_numeqp(fast_convert(I),fast_convert(fast_immediate(10))) == NIL){
FFT(fast_convert(Fcdr(Fmakesym("+RE+"))),fast_convert(Fcdr(Fmakesym("+IM+"))));
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res=NIL;res;});
return(res);}
int FFT_TEST(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("VERIF"),fast_inverse(T));res;});
FFT(fast_convert(Fcdr(Fmakesym("+RE+"))),fast_convert(Fcdr(Fmakesym("+IM+"))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("Compare results with the following references:~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=-1.0, ui=1.509958e-07~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=7.549789e-08, ui=1.0~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.7071068, ui=0.7071067~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.9238795, ui=0.3826834~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.9807853, ui=0.1950903~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.9951847, ui=0.09801713~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.9987954, ui=0.04906767~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.9996988, ui=0.02454123~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.9999247, ui=0.01227154~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("End of DO: ur=0.9999812, ui=0.006135884~%"))))));
res = ({int res;
 res = Fset_cdr(Fmakesym("VERIF"),fast_inverse(NIL));res;});
return(res);}
void init_tfunctions(void){
(deftfunc)("IPOWER" , f_IPOWER);
(deftfunc)("FFT" , f_FFT);
(deftfunc)("FFT-BENCH" , f_FFT_BENCH);
(deftfunc)("FFT-TEST" , f_FFT_TEST);
}void init_declare(void){
Fsetcatchsymbols(NIL);Fset_cdr(Fmakesym("PI"),Fmakestrflt("3.1415926535"));Fset_opt(Fmakesym("PI"),FAST_CONSTN);
Fset_cdr(Fmakesym("+RE+"),fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-VECTOR")),Fcons(fast_inverse(Fmakeint(1025)),Flist1(fast_inverse(Fmakestrflt("0.0")))))));Fset_opt(Fmakesym("+RE+"),FAST_CONSTN);
Fset_cdr(Fmakesym("+IM+"),fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-VECTOR")),Fcons(fast_inverse(Fmakeint(1025)),Flist1(fast_inverse(Fmakestrflt("0.0")))))));Fset_opt(Fmakesym("+IM+"),FAST_CONSTN);
Fset_cdr(Fmakesym("NUR"),NIL);Fset_opt(Fmakesym("NUR"),FAST_GLOBAL);
Fset_cdr(Fmakesym("NUI"),NIL);Fset_opt(Fmakesym("NUI"),FAST_GLOBAL);
Fset_cdr(Fmakesym("VERIF"),NIL);Fset_opt(Fmakesym("VERIF"),FAST_GLOBAL);
}