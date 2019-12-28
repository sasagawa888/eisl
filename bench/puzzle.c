#include "fast.h"
int f_FIT_AUX(int arglist);int FIT_AUX(int I,int J,int END);
int f_PLACE_AUX(int arglist);int PLACE_AUX(int I,int J,int END);
int f_PUZZLE_REMOVE_AUX(int arglist);int PUZZLE_REMOVE_AUX(int I,int J,int END);
int f_TRIAL(int arglist);int TRIAL(int J,int K);
int f_DEFINEPIECE(int arglist);int DEFINEPIECE(int ICLASS,int II,int JJ,int KK);
int f_PUZZLE_START(int arglist);int PUZZLE_START();
int f_FIT_AUX(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(FIT_AUX(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_PLACE_AUX(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(PLACE_AUX(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_PUZZLE_REMOVE_AUX(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(PUZZLE_REMOVE_AUX(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_TRIAL(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TRIAL(fast_convert(arg1),fast_convert(arg2))));
}
int f_DEFINEPIECE(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(DEFINEPIECE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_PUZZLE_START(int arglist){
return(fast_inverse(PUZZLE_START() ));
}
int FIT_AUX(int I,int J,int END){
int res;
if(CELLRANGE(I)) Fshelterpush(I);
if(CELLRANGE(J)) Fshelterpush(J);
if(CELLRANGE(END)) Fshelterpush(END);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int K = fast_convert(fast_immediate(0));int temp1;
while(({int res;
if((res=fast_greaterp(fast_convert(K),fast_convert(END))) == NIL)
if((res=({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("AREF")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-P")))),Fcons(fast_inverse(I),Flist1(fast_inverse(K))))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE")))),Flist1(fast_inverse(fast_plus(fast_convert(J),fast_convert(K)))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
 == NIL){
temp1 = fast_plus(fast_convert(K),fast_convert(fast_immediate(1)));
K = temp1;
}
res = fast_greaterp(fast_convert(K),fast_convert(END));res;});
if(CELLRANGE(END)) Fshelterpop();
if(CELLRANGE(J)) Fshelterpop();
if(CELLRANGE(I)) Fshelterpop();
return(res);}
int PLACE_AUX(int I,int J,int END){
int res;
if(CELLRANGE(I)) Fshelterpush(I);
if(CELLRANGE(J)) Fshelterpush(J);
if(CELLRANGE(END)) Fshelterpush(END);
if(Ffreecell() < 900) Fgbc();
({int res;
int K = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(K),fast_convert(END)) == NIL){
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("AREF")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-P")))),Fcons(fast_inverse(I),Flist1(fast_inverse(K)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(T),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE")))),Flist1(fast_inverse(fast_plus(fast_convert(J),fast_convert(K))))))));}
 else res = NIL;res;})
;
temp1 = fast_plus(fast_convert(K),fast_convert(fast_immediate(1)));
K = temp1;
}
res=NIL;res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_minus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-CLASS")))),Flist1(fast_inverse(I))))))))))),fast_convert(fast_immediate(1)))),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-CLASS")))),Flist1(fast_inverse(I)))))))))));
res = ({int res;
int K = fast_convert(J);int temp1;
while(({int res;
if((res=fast_greaterp(fast_convert(K),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-SIZE")))))) == NIL)
if((res=fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE")))),Flist1(fast_inverse(K))))))) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
 == NIL){
temp1 = fast_plus(fast_convert(K),fast_convert(fast_immediate(1)));
K = temp1;
}
res = ({int res;
if(fast_greaterp(fast_convert(K),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-SIZE"))))) != NIL){
res = fast_immediate(0);}
else{
res = K;}res;})
;res;});
if(CELLRANGE(END)) Fshelterpop();
if(CELLRANGE(J)) Fshelterpop();
if(CELLRANGE(I)) Fshelterpop();
return(res);}
int PUZZLE_REMOVE_AUX(int I,int J,int END){
int res;
if(CELLRANGE(I)) Fshelterpush(I);
if(CELLRANGE(J)) Fshelterpush(J);
if(CELLRANGE(END)) Fshelterpush(END);
if(Ffreecell() < 900) Fgbc();
({int res;
int K = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(K),fast_convert(END)) == NIL){
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("AREF")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-P")))),Fcons(fast_inverse(I),Flist1(fast_inverse(K)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(NIL),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE")))),Flist1(fast_inverse(fast_plus(fast_convert(J),fast_convert(K))))))));}
 else res = NIL;res;})
;
temp1 = fast_plus(fast_convert(K),fast_convert(fast_immediate(1)));
K = temp1;
}
res=NIL;res;});
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-CLASS")))),Flist1(fast_inverse(I))))))))))),fast_convert(fast_immediate(1)))),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-CLASS")))),Flist1(fast_inverse(I)))))))))));res;});
if(CELLRANGE(END)) Fshelterpop();
if(CELLRANGE(J)) Fshelterpop();
if(CELLRANGE(I)) Fshelterpop();
return(res);}
int TRIAL(int J,int K){
int res;
if(CELLRANGE(J)) Fshelterpush(J);
if(CELLRANGE(K)) Fshelterpush(K);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int I = fast_convert(fast_immediate(0));int temp1;
while(({int res;
if((res=fast_greaterp(fast_convert(I),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-TYPEMAX")))))) == NIL)
if((res=({int res;
if(fast_not(fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-CLASS")))),Flist1(fast_inverse(I))))))))))),fast_convert(fast_immediate(0)))) != NIL){
res = ({int res=NIL;
if(FIT_AUX(I,J,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECEMAX")))),Flist1(fast_inverse(I)))))) != NIL){
res = ({int res;
 res = K = PLACE_AUX(I,J,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECEMAX")))),Flist1(fast_inverse(I))))));res;})
;
res = ({int res=NIL;
if((TRIAL(K,fast_immediate(0)) || fast_numeqp(fast_convert(K),fast_convert(fast_immediate(0)))) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("KOUNT"),fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("KOUNT")))),fast_convert(Fmakeint(1)))));res;});
res = T;}
else{
res = PUZZLE_REMOVE_AUX(I,J,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECEMAX")))),Flist1(fast_inverse(I))))));
res = NIL;}
;res;});}
;res;});}
 else res = NIL;res;})
) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
 == NIL){
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = ({int res;
if(fast_greaterp(fast_convert(I),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-TYPEMAX"))))) != NIL){
res = ({int res;
({int res;
 res = Fset_cdr(Fmakesym("KOUNT"),fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("KOUNT")))),fast_convert(Fmakeint(1)))));res;});
res = NIL;res;});}
else{
res = T;}res;})
;res;});
if(CELLRANGE(K)) Fshelterpop();
if(CELLRANGE(J)) Fshelterpop();
return(res);}
int DEFINEPIECE(int ICLASS,int II,int JJ,int KK){
int res;
if(CELLRANGE(ICLASS)) Fshelterpush(ICLASS);
if(CELLRANGE(II)) Fshelterpush(II);
if(CELLRANGE(JJ)) Fshelterpush(JJ);
if(CELLRANGE(KK)) Fshelterpush(KK);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int INDEX = fast_convert(fast_immediate(0));({int res;
int I = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(I),fast_convert(II)) == NIL){
({int res;
int J = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(J),fast_convert(JJ)) == NIL){
({int res;
int K = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(K),fast_convert(KK)) == NIL){
({int res;
 res = INDEX = fast_plus(fast_convert(I),fast_convert(fast_mult(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-D")))),fast_convert(fast_plus(fast_convert(J),fast_convert(fast_mult(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-D")))),fast_convert(K))))))));res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-AREF")),Fcons(fast_inverse(T),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-P")))),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("III")))),Flist1(fast_inverse(INDEX)))))));
temp1 = fast_plus(fast_convert(K),fast_convert(fast_immediate(1)));
K = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res=NIL;res;});
({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(ICLASS),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-CLASS")))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("III")))))))));res;});
({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(INDEX),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECEMAX")))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("III")))))))));res;});
res = ({int res;
if(fast_not(fast_eq(fast_convert(fast_convert(Fcdr(Fmakesym("III")))),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-TYPEMAX")))))) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("III"),fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("III")))),fast_convert(Fmakeint(1)))));res;});}
 else res = NIL;res;})
;
res;})
;
if(CELLRANGE(KK)) Fshelterpop();
if(CELLRANGE(JJ)) Fshelterpop();
if(CELLRANGE(II)) Fshelterpop();
if(CELLRANGE(ICLASS)) Fshelterpop();
return(res);}
int PUZZLE_START(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("PIECECOUNT"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-VECTOR")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-CLASSMAX")))),fast_convert(Fmakeint(1)))),Flist1(fast_inverse(Fmakeint(0))))))));res;});
({int res;
 res = Fset_cdr(Fmakesym("PUZZLE-CLASS"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-VECTOR")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-TYPEMAX")))),fast_convert(Fmakeint(1)))),Flist1(fast_inverse(Fmakeint(0))))))));res;});
({int res;
 res = Fset_cdr(Fmakesym("PIECEMAX"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-VECTOR")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-TYPEMAX")))),fast_convert(Fmakeint(1)))),Flist1(fast_inverse(Fmakeint(0))))))));res;});
({int res;
 res = Fset_cdr(Fmakesym("PUZZLE"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-VECTOR")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-SIZE")))),fast_convert(Fmakeint(1)))),Flist1(fast_inverse(Fmakeint(0))))))));res;});
({int res;
 res = Fset_cdr(Fmakesym("PUZZLE-P"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-ARRAY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-TYPEMAX")))),fast_convert(Fmakeint(1)))),Flist1(fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-SIZE")))),fast_convert(Fmakeint(1))))))))),Flist1(fast_inverse(Fmakeint(0))))))));res;});
({int res;
int M = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(M),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-SIZE"))))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(T),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE")))),Flist1(fast_inverse(M))))));
temp1 = fast_plus(fast_convert(M),fast_convert(fast_immediate(1)));
M = temp1;
}
res=NIL;res;});
({int res;
int I = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(I),fast_convert(fast_immediate(5))) == NIL){
({int res;
int J = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(J),fast_convert(fast_immediate(5))) == NIL){
({int res;
int K = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(K),fast_convert(fast_immediate(5))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(NIL),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE")))),Flist1(fast_inverse(fast_plus(fast_convert(I),fast_convert(fast_mult(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-D")))),fast_convert(fast_plus(fast_convert(J),fast_convert(fast_mult(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-D")))),fast_convert(K))))))))))))));
temp1 = fast_plus(fast_convert(K),fast_convert(fast_immediate(1)));
K = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res=NIL;res;});
({int res;
int I = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(I),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-TYPEMAX"))))) == NIL){
({int res;
int M = fast_convert(fast_immediate(0));int temp1;
while(fast_greaterp(fast_convert(M),fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-SIZE"))))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-AREF")),Fcons(fast_inverse(NIL),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PUZZLE-P")))),Fcons(fast_inverse(I),Flist1(fast_inverse(M)))))));
temp1 = fast_plus(fast_convert(M),fast_convert(fast_immediate(1)));
M = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res=NIL;res;});
({int res;
 res = Fset_cdr(Fmakesym("III"),fast_inverse(Fmakeint(0)));res;});
DEFINEPIECE(fast_immediate(0),fast_immediate(3),fast_immediate(1),fast_immediate(0));
DEFINEPIECE(fast_immediate(0),fast_immediate(1),fast_immediate(0),fast_immediate(3));
DEFINEPIECE(fast_immediate(0),fast_immediate(0),fast_immediate(3),fast_immediate(1));
DEFINEPIECE(fast_immediate(0),fast_immediate(1),fast_immediate(3),fast_immediate(0));
DEFINEPIECE(fast_immediate(0),fast_immediate(3),fast_immediate(0),fast_immediate(1));
DEFINEPIECE(fast_immediate(0),fast_immediate(0),fast_immediate(1),fast_immediate(3));
DEFINEPIECE(fast_immediate(1),fast_immediate(2),fast_immediate(0),fast_immediate(0));
DEFINEPIECE(fast_immediate(1),fast_immediate(0),fast_immediate(2),fast_immediate(0));
DEFINEPIECE(fast_immediate(1),fast_immediate(0),fast_immediate(0),fast_immediate(2));
DEFINEPIECE(fast_immediate(2),fast_immediate(1),fast_immediate(1),fast_immediate(0));
DEFINEPIECE(fast_immediate(2),fast_immediate(1),fast_immediate(0),fast_immediate(1));
DEFINEPIECE(fast_immediate(2),fast_immediate(0),fast_immediate(1),fast_immediate(1));
DEFINEPIECE(fast_immediate(3),fast_immediate(1),fast_immediate(1),fast_immediate(1));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_immediate(13)),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_immediate(0)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_immediate(3)),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_immediate(1)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_immediate(1)),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_immediate(2)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(fast_immediate(1)),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECECOUNT")))),Flist1(fast_inverse(fast_immediate(3)))))));
({int res;
 res = Fset_cdr(Fmakesym("KOUNT"),fast_inverse(Fmakeint(0)));res;});
res = ({int res;int M = fast_convert(fast_plus(fast_convert(fast_mult(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-D")))),fast_convert(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("PUZZLE-D")))),fast_convert(fast_immediate(1)))))),fast_convert(fast_immediate(1))));int N = fast_convert(fast_immediate(0));({int res;
if(FIT_AUX(fast_immediate(0),M,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECEMAX")))),Flist1(fast_inverse(fast_immediate(0))))))) != NIL){
res = ({int res;
 res = N = PLACE_AUX(fast_immediate(0),M,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("PIECEMAX")))),Flist1(fast_inverse(fast_immediate(0)))))));res;})
;}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("Error.~%"))))));res;});}res;})
;
res = ({int res;
if(TRIAL(N,fast_immediate(0)) != NIL){
res = fast_convert(Fcdr(Fmakesym("KOUNT")));}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("Failure.~%"))))));res;});}res;})
;
res;})
;
return(res);}
void init_tfunctions(void){
(deftfunc)("FIT-AUX" , f_FIT_AUX);
(deftfunc)("PLACE-AUX" , f_PLACE_AUX);
(deftfunc)("PUZZLE-REMOVE-AUX" , f_PUZZLE_REMOVE_AUX);
(deftfunc)("TRIAL" , f_TRIAL);
(deftfunc)("DEFINEPIECE" , f_DEFINEPIECE);
(deftfunc)("PUZZLE-START" , f_PUZZLE_START);
}void init_declare(void){
Fsetcatchsymbols(NIL);Fset_cdr(Fmakesym("PUZZLE-SIZE"),Fmakeint(511));Fset_opt(Fmakesym("PUZZLE-SIZE"),FAST_CONSTN);
Fset_cdr(Fmakesym("PUZZLE-CLASSMAX"),Fmakeint(3));Fset_opt(Fmakesym("PUZZLE-CLASSMAX"),FAST_CONSTN);
Fset_cdr(Fmakesym("PUZZLE-TYPEMAX"),Fmakeint(12));Fset_opt(Fmakesym("PUZZLE-TYPEMAX"),FAST_CONSTN);
Fset_cdr(Fmakesym("PUZZLE-D"),Fmakeint(8));Fset_opt(Fmakesym("PUZZLE-D"),FAST_CONSTN);
Fset_cdr(Fmakesym("III"),Fmakeint(0));Fset_opt(Fmakesym("III"),FAST_GLOBAL);
Fset_cdr(Fmakesym("KOUNT"),Fmakeint(0));Fset_opt(Fmakesym("KOUNT"),FAST_GLOBAL);
Fset_cdr(Fmakesym("PIECECOUNT"),NIL);Fset_opt(Fmakesym("PIECECOUNT"),FAST_GLOBAL);
Fset_cdr(Fmakesym("PUZZLE-CLASS"),NIL);Fset_opt(Fmakesym("PUZZLE-CLASS"),FAST_GLOBAL);
Fset_cdr(Fmakesym("PIECEMAX"),NIL);Fset_opt(Fmakesym("PIECEMAX"),FAST_GLOBAL);
Fset_cdr(Fmakesym("PUZZLE"),NIL);Fset_opt(Fmakesym("PUZZLE"),FAST_GLOBAL);
Fset_cdr(Fmakesym("PUZZLE-P"),NIL);Fset_opt(Fmakesym("PUZZLE-P"),FAST_GLOBAL);
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("FIT"),Fcons(Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("FIT-AUX"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("ELT"),Fcons(Fmakesym("PIECEMAX"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("X"),NIL)),NIL))),NIL)))),NIL)),NIL)))));
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("PLACE"),Fcons(Fcons(Fmakesym("I"),Fcons(Fmakesym("J"),NIL)),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("PLACE-AUX"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("I"),NIL)),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("J"),NIL)),Fcons(Fcons(Fmakesym("ELT"),Fcons(Fmakesym("PIECEMAX"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("I"),NIL)),NIL))),NIL)))),NIL)),NIL)))));
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("PUZZLE-REMOVE"),Fcons(Fcons(Fmakesym("I"),Fcons(Fmakesym("J"),NIL)),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("PUZZLE-REMOVE-AUX"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("I"),NIL)),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("J"),NIL)),Fcons(Fcons(Fmakesym("ELT"),Fcons(Fmakesym("PIECEMAX"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("I"),NIL)),NIL))),NIL)))),NIL)),NIL)))));
}