#include "../fast.h"
int f_ADD_LEMMA(int arglist);int ADD_LEMMA(int TERM);
int f_ADD_LEMMA_LST(int arglist);int ADD_LEMMA_LST(int LST);
int f_APPLY_SUBST(int arglist);int APPLY_SUBST(int ALIST,int TERM);
int f_APPLY_SUBST_LST(int arglist);int APPLY_SUBST_LST(int ALIST,int LST);
int f_FALSEP(int arglist);int FALSEP(int X,int LST);
int f_TRUEP(int arglist);int TRUEP(int X,int LST);
int f_ONE_WAY_UNIFY(int arglist);int ONE_WAY_UNIFY(int TERM1,int TERM2);
int f_ONE_WAY_UNIFY1(int arglist);int ONE_WAY_UNIFY1(int TERM1,int TERM2);
int f_ONE_WAY_UNIFY1_LST(int arglist);int ONE_WAY_UNIFY1_LST(int LST1,int LST2);
int f_REWRITE(int arglist);int REWRITE(int TERM);
int f_REWRITE_ARGS(int arglist);int REWRITE_ARGS(int LST);
int f_REWRITE_WITH_LEMMAS(int arglist);int REWRITE_WITH_LEMMAS(int TERM,int LST);
int f_BOYER_SETUP(int arglist);int BOYER_SETUP();
int f_TAUTOLOGYP(int arglist);int TAUTOLOGYP(int X,int TRUE_LST,int FALSE_LST);
int f_TAUTP(int arglist);int TAUTP(int X);
int f_BOYER(int arglist);int BOYER();
int f_ADD_LEMMA(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ADD_LEMMA(fast_convert(arg1))));
}
int f_ADD_LEMMA_LST(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ADD_LEMMA_LST(fast_convert(arg1))));
}
int f_APPLY_SUBST(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(APPLY_SUBST(fast_convert(arg1),fast_convert(arg2))));
}
int f_APPLY_SUBST_LST(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(APPLY_SUBST_LST(fast_convert(arg1),fast_convert(arg2))));
}
int f_FALSEP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FALSEP(fast_convert(arg1),fast_convert(arg2))));
}
int f_TRUEP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TRUEP(fast_convert(arg1),fast_convert(arg2))));
}
int f_ONE_WAY_UNIFY(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ONE_WAY_UNIFY(fast_convert(arg1),fast_convert(arg2))));
}
int f_ONE_WAY_UNIFY1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ONE_WAY_UNIFY1(fast_convert(arg1),fast_convert(arg2))));
}
int f_ONE_WAY_UNIFY1_LST(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ONE_WAY_UNIFY1_LST(fast_convert(arg1),fast_convert(arg2))));
}
int f_REWRITE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(REWRITE(fast_convert(arg1))));
}
int f_REWRITE_ARGS(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(REWRITE_ARGS(fast_convert(arg1))));
}
int f_REWRITE_WITH_LEMMAS(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(REWRITE_WITH_LEMMAS(fast_convert(arg1),fast_convert(arg2))));
}
int f_BOYER_SETUP(int arglist){
return(fast_inverse(BOYER_SETUP() ));
}
int f_TAUTOLOGYP(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(TAUTOLOGYP(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_TAUTP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(TAUTP(fast_convert(arg1))));
}
int f_BOYER(int arglist){
return(fast_inverse(BOYER() ));
}
int ADD_LEMMA(int TERM){
int res;
if(CELLRANGE(TERM)) Fshelterpush(TERM);
Fcheckgbc();
res = ({int res=NIL;
if((({int arg1,res;
arg1 = fast_inverse(TERM);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(arg1)));
;res;}) && ({int res;Fargpush(fast_convert(fast_convert(fast_car(TERM))));Fargpush(fast_convert(Fmakesym("EQUAL")));res=fast_eq();res;}) && ({int arg1,res;
arg1 = fast_inverse(fast_convert(fast_car(fast_convert(fast_cdr(TERM)))));
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(arg1)));
;res;})) != NIL){
res = ({int arg1,arg2,arg3,res;
arg1 = fast_inverse(Fcons(fast_inverse(TERM),fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(fast_car(fast_convert(fast_car(fast_convert(fast_cdr(TERM)))))));
Fshelterpush(arg1);
arg2 = fast_inverse(Fmakesym("LEMMAS"));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(arg1,Flist1(arg2))));
;res;}))));
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(fast_car(fast_convert(fast_car(fast_convert(fast_cdr(TERM)))))));
Fshelterpush(arg2);
arg3 = fast_inverse(Fmakesym("LEMMAS"));
Fshelterpush(arg3);
arg3=Fshelterpop();
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(arg1,Fcons(arg2,Flist1(arg3)))));
;res;});}
else{
res = ({int arg1,arg2,res;
arg1 = fast_inverse(Fmakestr("%ADD-LEMMA did not like the term: ~a~%"));
Fshelterpush(arg1);
arg2 = fast_inverse(TERM);
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(arg1,Flist1(arg2))));
;res;});}
;res;});
if(CELLRANGE(TERM)) TERM=Fshelterpop();
return(res);}
int ADD_LEMMA_LST(int LST){
int res;
int temp1;
ADD_LEMMA_LSTloop:
if(CELLRANGE(LST)) Fshelterpush(LST);
Fcheckgbc();
res = ({int res=NIL;
if(({int arg1,res;
arg1 = fast_inverse(LST);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(arg1)));
;res;}) != NIL){
res = T;}
else{
res = ADD_LEMMA(fast_convert(fast_car(LST)));
{
temp1 = fast_convert(fast_cdr(LST));
if(CELLRANGE(LST)) LST=Fshelterpop();
LST = temp1;
goto ADD_LEMMA_LSTloop;};}
;res;});
if(CELLRANGE(LST)) LST=Fshelterpop();
return(res);}
int APPLY_SUBST(int ALIST,int TERM){
int res;
if(CELLRANGE(ALIST)) Fshelterpush(ALIST);
if(CELLRANGE(TERM)) Fshelterpush(TERM);
Fcheckgbc();
res = ({int res=NIL;
if(fast_not(({int arg1,res;
arg1 = fast_inverse(TERM);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(arg1)));
;res;})) != NIL){
res = ({int res=NIL;
if(({int res;
 res = Fset_cdr(Fmakesym("TEMP-TEMP"),fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(TERM);
Fshelterpush(arg1);
arg2 = fast_inverse(ALIST);
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(arg1,Flist1(arg2))));
;res;})));res;}) != NIL){
res = fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("TEMP-TEMP")))));}
else{
res = TERM;}
;res;});}
else{
res = Fcons(fast_inverse(fast_convert(fast_car(TERM))),fast_inverse(APPLY_SUBST_LST(ALIST,fast_convert(fast_cdr(TERM)))));}
;res;});
if(CELLRANGE(TERM)) TERM=Fshelterpop();
if(CELLRANGE(ALIST)) ALIST=Fshelterpop();
return(res);}
int APPLY_SUBST_LST(int ALIST,int LST){
int res;
if(CELLRANGE(ALIST)) Fshelterpush(ALIST);
if(CELLRANGE(LST)) Fshelterpush(LST);
Fcheckgbc();
res = ({int res=NIL;
if(({int arg1,res;
arg1 = fast_inverse(LST);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(arg1)));
;res;}) != NIL){
res = NIL;}
else{
res = Fcons(fast_inverse(APPLY_SUBST(ALIST,fast_convert(fast_car(LST)))),fast_inverse(APPLY_SUBST_LST(ALIST,fast_convert(fast_cdr(LST)))));}
;res;});
if(CELLRANGE(LST)) LST=Fshelterpop();
if(CELLRANGE(ALIST)) ALIST=Fshelterpop();
return(res);}
int FALSEP(int X,int LST){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(LST)) Fshelterpush(LST);
Fcheckgbc();
res = ({int res;
if((res=({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(Fcons(Fmakesym("F"),NIL));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(arg1,Flist1(arg2))));
;res;})) == NIL)
if((res=({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(LST);
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(arg1,Flist1(arg2))));
;res;})) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
;
if(CELLRANGE(LST)) LST=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
int TRUEP(int X,int LST){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(LST)) Fshelterpush(LST);
Fcheckgbc();
res = ({int res;
if((res=({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(Fcons(T,NIL));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(arg1,Flist1(arg2))));
;res;})) == NIL)
if((res=({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(LST);
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(arg1,Flist1(arg2))));
;res;})) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
;
if(CELLRANGE(LST)) LST=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
int ONE_WAY_UNIFY(int TERM1,int TERM2){
int res;
if(CELLRANGE(TERM1)) Fshelterpush(TERM1);
if(CELLRANGE(TERM2)) Fshelterpush(TERM2);
Fcheckgbc();
({int res;
 res = Fset_cdr(Fmakesym("UNIFY-SUBST"),fast_inverse(NIL));res;});
res = ONE_WAY_UNIFY1(TERM1,TERM2);
if(CELLRANGE(TERM2)) TERM2=Fshelterpop();
if(CELLRANGE(TERM1)) TERM1=Fshelterpop();
return(res);}
int ONE_WAY_UNIFY1(int TERM1,int TERM2){
int res;
if(CELLRANGE(TERM1)) Fshelterpush(TERM1);
if(CELLRANGE(TERM2)) Fshelterpush(TERM2);
Fcheckgbc();
res = ({int res=NIL;
if(fast_not(({int arg1,res;
arg1 = fast_inverse(TERM2);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(arg1)));
;res;})) != NIL){
res = ({int res=NIL;
if(({int res;
 res = Fset_cdr(Fmakesym("TEMP-TEMP"),fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(TERM2);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcdr(Fmakesym("UNIFY-SUBST"))));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(arg1,Flist1(arg2))));
;res;})));res;}) != NIL){
res = ({int arg1,arg2,res;
arg1 = fast_inverse(TERM1);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(fast_cdr(fast_convert(Fcdr(Fmakesym("TEMP-TEMP"))))));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(arg1,Flist1(arg2))));
;res;});}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("UNIFY-SUBST"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(TERM2),fast_inverse(TERM1))),fast_inverse(fast_convert(Fcdr(Fmakesym("UNIFY-SUBST")))))));res;});
res = T;}
;res;});}
else if(fast_not(({int arg1,res;
arg1 = fast_inverse(TERM1);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(arg1)));
;res;})) != NIL){
res = NIL;}
else if(({int res;Fargpush(fast_convert(fast_convert(fast_car(TERM1))));Fargpush(fast_convert(fast_convert(fast_car(TERM2))));res=fast_eq();res;}) != NIL){
res = ONE_WAY_UNIFY1_LST(fast_convert(fast_cdr(TERM1)),fast_convert(fast_cdr(TERM2)));}
else{
res = NIL;}
;res;});
if(CELLRANGE(TERM2)) TERM2=Fshelterpop();
if(CELLRANGE(TERM1)) TERM1=Fshelterpop();
return(res);}
int ONE_WAY_UNIFY1_LST(int LST1,int LST2){
int res;
int temp1,temp2;
ONE_WAY_UNIFY1_LSTloop:
if(CELLRANGE(LST1)) Fshelterpush(LST1);
if(CELLRANGE(LST2)) Fshelterpush(LST2);
Fcheckgbc();
res = ({int res=NIL;
if(({int arg1,res;
arg1 = fast_inverse(LST1);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(arg1)));
;res;}) != NIL){
res = T;}
else if(ONE_WAY_UNIFY1(fast_convert(fast_car(LST1)),fast_convert(fast_car(LST2))) != NIL){
{
temp1 = fast_convert(fast_cdr(LST1));
temp2 = fast_convert(fast_cdr(LST2));
if(CELLRANGE(LST1)) LST1=Fshelterpop();
if(CELLRANGE(LST2)) LST2=Fshelterpop();
LST1 = temp1;
LST2 = temp2;
goto ONE_WAY_UNIFY1_LSTloop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(LST2)) LST2=Fshelterpop();
if(CELLRANGE(LST1)) LST1=Fshelterpop();
return(res);}
int REWRITE(int TERM){
int res;
if(CELLRANGE(TERM)) Fshelterpush(TERM);
Fcheckgbc();
res = ({int res;
if(({int arg1,res;
arg1 = fast_inverse(TERM);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(arg1)));
;res;}) != NIL){
res = REWRITE_WITH_LEMMAS(Fcons(fast_inverse(fast_convert(fast_car(TERM))),fast_inverse(REWRITE_ARGS(fast_convert(fast_cdr(TERM))))),({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(fast_car(TERM)));
Fshelterpush(arg1);
arg2 = fast_inverse(Fmakesym("LEMMAS"));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(arg1,Flist1(arg2))));
;res;}));}
else{
res = TERM;}res;})
;
if(CELLRANGE(TERM)) TERM=Fshelterpop();
return(res);}
int REWRITE_ARGS(int LST){
int res;
if(CELLRANGE(LST)) Fshelterpush(LST);
Fcheckgbc();
res = ({int res;
if((res = LST) != NIL)
if((res=Fcons(fast_inverse(REWRITE(fast_convert(fast_car(LST)))),fast_inverse(REWRITE_ARGS(fast_convert(fast_cdr(LST)))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(LST)) LST=Fshelterpop();
return(res);}
int REWRITE_WITH_LEMMAS(int TERM,int LST){
int res;
int temp1,temp2;
REWRITE_WITH_LEMMASloop:
if(CELLRANGE(TERM)) Fshelterpush(TERM);
if(CELLRANGE(LST)) Fshelterpush(LST);
Fcheckgbc();
res = ({int res=NIL;
if(({int arg1,res;
arg1 = fast_inverse(LST);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(arg1)));
;res;}) != NIL){
res = TERM;}
else if(ONE_WAY_UNIFY(TERM,fast_convert(fast_car(fast_convert(fast_cdr(fast_convert(fast_car(LST))))))) != NIL){
res = REWRITE(APPLY_SUBST(fast_convert(Fcdr(Fmakesym("UNIFY-SUBST"))),({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(fast_car(LST)));
Fshelterpush(arg1);
arg2 = fast_inverse(fast_immediate(2));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(arg1,Flist1(arg2))));
;res;})));}
else{
{
temp1 = TERM;
temp2 = fast_convert(fast_cdr(LST));
if(CELLRANGE(TERM)) TERM=Fshelterpop();
if(CELLRANGE(LST)) LST=Fshelterpop();
TERM = temp1;
LST = temp2;
goto REWRITE_WITH_LEMMASloop;};}
;res;});
if(CELLRANGE(LST)) LST=Fshelterpop();
if(CELLRANGE(TERM)) TERM=Fshelterpop();
return(res);}
int BOYER_SETUP(){
int res;
Fcheckgbc();
res = ADD_LEMMA_LST(Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("COMPILE"),Fcons(Fmakesym("FORM"),NIL)),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fcons(Fmakesym("CODEGEN"),Fcons(Fcons(Fmakesym("OPTIMIZE"),Fcons(Fmakesym("FORM"),NIL)),Fcons(Fcons(NIL,NIL),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("Y"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("GREATERP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSEQP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("GREATEREQP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("BOOLEAN"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(T,NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("F"),NIL),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("IFF"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EVEN1"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(T,NIL),Fcons(Fcons(Fmakesym("ODD"),Fcons(Fcons(Fmakesym("1-"),Fcons(Fmakesym("X"),NIL)),NIL)),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("COUNTPS-"),Fcons(Fmakesym("L"),Fcons(Fmakesym("PRED"),NIL))),Fcons(Fcons(Fmakesym("COUNTPS-LOOP"),Fcons(Fmakesym("L"),Fcons(Fmakesym("PRED"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("FACT-"),Fcons(Fmakesym("I"),NIL)),Fcons(Fcons(Fmakesym("FACT-LOOP"),Fcons(Fmakesym("I"),Fcons(Fmakeint(1),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("REVERSE-"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("REVERSE-LOOP"),Fcons(Fmakesym("X"),Fcons(Fcons(NIL,NIL),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIVIDES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fcons(Fmakesym("REMAINDER"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("ASSUME-TRUE"),Fcons(Fmakesym("VAR"),Fcons(Fmakesym("ALIST"),NIL))),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("VAR"),Fcons(Fcons(T,NIL),NIL))),Fcons(Fmakesym("ALIST"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("ASSUME-FALSE"),Fcons(Fmakesym("VAR"),Fcons(Fmakesym("ALIST"),NIL))),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("VAR"),Fcons(Fcons(Fmakesym("F"),NIL),NIL))),Fcons(Fmakesym("ALIST"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TAUTOLOGY-CHECKER"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("TAUTOLOGYP"),Fcons(Fcons(Fmakesym("NORMALIZE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(NIL,NIL),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("FALSIFY"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("FALSIFY1"),Fcons(Fcons(Fmakesym("NORMALIZE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(NIL,NIL),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PRIME"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("1+"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL)),NIL))),NIL)),Fcons(Fcons(Fmakesym("PRIME1"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("1-"),Fcons(Fmakesym("X"),NIL)),NIL))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("AND"),Fcons(Fmakesym("P"),Fcons(Fmakesym("Q"),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("P"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("Q"),Fcons(Fcons(T,NIL),Fcons(Fcons(Fmakesym("F"),NIL),NIL)))),Fcons(Fcons(Fmakesym("F"),NIL),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("OR"),Fcons(Fmakesym("P"),Fcons(Fmakesym("Q"),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("P"),Fcons(Fcons(T,NIL),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("Q"),Fcons(Fcons(T,NIL),Fcons(Fcons(Fmakesym("F"),NIL),NIL)))),Fcons(Fcons(Fmakesym("F"),NIL),NIL))))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fmakesym("P"),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("P"),Fcons(Fcons(Fmakesym("F"),NIL),Fcons(Fcons(T,NIL),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("P"),Fcons(Fmakesym("Q"),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("P"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("Q"),Fcons(Fcons(T,NIL),Fcons(Fcons(Fmakesym("F"),NIL),NIL)))),Fcons(Fcons(T,NIL),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),Fcons(Fmakesym("C"),NIL)))),Fcons(Fmakesym("D"),Fcons(Fmakesym("E"),NIL)))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("A"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("B"),Fcons(Fmakesym("D"),Fcons(Fmakesym("E"),NIL)))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fmakesym("C"),Fcons(Fmakesym("D"),Fcons(Fmakesym("E"),NIL)))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("X"),NIL)),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("A"),NIL)),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("B"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("X"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("A"),Fcons(Fmakesym("C"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("B"),NIL)),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("C"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("ZERO"),NIL),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("Y"),NIL)),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fcons(Fmakesym("PLUS-TREE"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fcons(Fmakesym("PLUS-TREE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fcons(Fmakesym("PLUS-TREE"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fmakesym("A"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fcons(Fmakesym("PLUS-TREE"),Fcons(Fcons(Fmakesym("PLUS-FRINGE"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fmakesym("X"),Fcons(Fmakesym("A"),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),NIL)),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fmakesym("B"),NIL)),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fmakesym("A"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Z"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("Y"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EXEC"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakesym("PDS"),Fcons(Fmakesym("ENVRN"),NIL)))),Fcons(Fcons(Fmakesym("EXEC"),Fcons(Fmakesym("Y"),Fcons(Fcons(Fmakesym("EXEC"),Fcons(Fmakesym("X"),Fcons(Fmakesym("PDS"),Fcons(Fmakesym("ENVRN"),NIL)))),Fcons(Fmakesym("ENVRN"),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("MC-FLATTEN"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fcons(Fmakesym("FLATTEN"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),NIL))),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("X"),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("X"),Fcons(Fmakesym("B"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fmakesym("Y"),NIL)),NIL))),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fmakesym("X"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("Z"),Fcons(Fcons(Fmakesym("INTERSECT"),Fcons(Fmakesym("B"),Fcons(Fmakesym("C"),NIL))),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("A"),Fcons(Fmakesym("C"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("NTH"),Fcons(Fcons(Fmakesym("ZERO"),NIL),Fcons(Fmakesym("I"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EXP"),Fcons(Fmakesym("I"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("J"),Fcons(Fmakesym("K"),NIL))),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fcons(Fmakesym("EXP"),Fcons(Fmakesym("I"),Fcons(Fmakesym("H"),NIL))),Fcons(Fcons(Fmakesym("EXP"),Fcons(Fmakesym("I"),Fcons(Fmakesym("K"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EXP"),Fcons(Fmakesym("I"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("J"),Fcons(Fmakesym("K"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EXP"),Fcons(Fcons(Fmakesym("EXP"),Fcons(Fmakesym("I"),Fcons(Fmakesym("J"),NIL))),Fcons(Fmakesym("K"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("REVERSE-LOOP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("COUNT-LIST"),Fcons(Fmakesym("Z"),Fcons(Fcons(Fmakesym("SORT-LP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("COUNT-LIST"),Fcons(Fmakesym("Z"),Fcons(Fmakesym("X"),NIL))),Fcons(Fcons(Fmakesym("COUNT-LIST"),Fcons(Fmakesym("Z"),Fcons(Fmakesym("Y"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("C"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("B"),Fcons(Fmakesym("C"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("REMAINDER"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("Y"),Fcons(Fcons(Fmakesym("QUOTIENT"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("X"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("POWER-EVAL"),Fcons(Fcons(Fmakesym("BIG-PLUS1"),Fcons(Fmakesym("L"),Fcons(Fmakesym("I"),Fcons(Fmakesym("BASE"),NIL)))),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("POWER-EVAL"),Fcons(Fmakesym("L"),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fmakesym("I"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("POWER-EVAL"),Fcons(Fcons(Fmakesym("BIG-PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("I"),Fcons(Fmakesym("BASE"),NIL))))),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("I"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("POWER-EVAL"),Fcons(Fmakesym("X"),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fcons(Fmakesym("POWER-EVAL"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("BASE"),NIL))),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("REMAINDER"),Fcons(Fmakesym("Y"),Fcons(Fmakeint(1),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fcons(Fmakesym("QUOTIENT"),Fcons(Fmakesym("I"),Fcons(Fmakesym("J"),NIL))),Fcons(Fmakesym("I"),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("I"),NIL)),NIL)),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("J"),NIL)),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("J"),Fcons(Fmakeint(1),NIL))),NIL)),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fcons(Fmakesym("REMAINDER"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakesym("X"),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("Y"),NIL)),NIL)),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("POWER-EVAL"),Fcons(Fcons(Fmakesym("POWER-REP"),Fcons(Fmakesym("I"),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("I"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("POWER-EVAL"),Fcons(Fcons(Fmakesym("BIG-PLUS"),Fcons(Fcons(Fmakesym("POWER-REP"),Fcons(Fmakesym("I"),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fcons(Fmakesym("POWER-REP"),Fcons(Fmakesym("J"),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),Fcons(Fmakesym("BASE"),NIL))))),Fcons(Fmakesym("BASE"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("I"),Fcons(Fmakesym("J"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("GCD"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("GCD"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("NTH"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fmakesym("I"),NIL))),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fcons(Fmakesym("NTH"),Fcons(Fmakesym("A"),Fcons(Fmakesym("I"),NIL))),Fcons(Fcons(Fmakesym("NTH"),Fcons(Fmakesym("B"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("I"),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fmakesym("A"),NIL)),NIL))),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakesym("X"),NIL))),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("Y"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakesym("X"),NIL))),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("Y"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("C"),Fcons(Fmakesym("W"),NIL))),NIL))),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("C"),Fcons(Fmakesym("X"),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("W"),Fcons(Fmakesym("X"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("REMAINDER"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Z"),NIL))),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fcons(Fmakesym("1+"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL)),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("1+"),Fcons(Fmakesym("Y"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("Z"),NIL)),NIL)),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Y"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("X"),NIL)),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("GCD"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("Z"),Fcons(Fcons(Fmakesym("GCD"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("VALUE"),Fcons(Fcons(Fmakesym("NORMALIZE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("VALUE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("A"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("FLATTEN"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("Y"),Fcons(Fcons(NIL,NIL),NIL))),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NLISTP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LISTP"),Fcons(Fcons(Fmakesym("GOPHER"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("LISTP"),Fcons(Fmakesym("X"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("SAMEFRINGE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("FLATTEN"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("FLATTEN"),Fcons(Fmakesym("Y"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("GREATEST-FACTOR"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("Y"),Fcons(Fmakeint(1),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("GREATEST-FACTOR"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakeint(1),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fmakeint(1),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fcons(Fmakesym("GREATEST-FACTOR"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("Y"),Fcons(Fmakeint(1),NIL))),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("X"),NIL)),NIL)),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TIMES-LIST"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fcons(Fmakesym("TIMES-LIST"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("TIMES-LIST"),Fcons(Fmakesym("Y"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PRIME-LIST"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("PRIME-LIST"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("PRIME-LIST"),Fcons(Fmakesym("Y"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("Z"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("W"),Fcons(Fmakesym("Z"),NIL))),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("Z"),NIL)),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("Z"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("W"),Fcons(Fmakeint(1),NIL))),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("GREATEREQPR"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("OR"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("Y"),Fcons(Fmakeint(1),NIL))),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("REMAINDER"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fmakeint(1),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("A"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),NIL)),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("B"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),NIL)),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("A"),NIL)),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("B"),NIL)),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("1-"),Fcons(Fmakesym("A"),NIL)),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("1-"),Fcons(Fmakesym("B"),NIL)),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),NIL))))))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fcons(Fmakesym("DELETE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("L"),NIL))),NIL)),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fmakesym("L"),NIL)),NIL))),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("X"),Fcons(Fmakesym("L"),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("SORT2"),Fcons(Fcons(Fmakesym("DELETE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("L"),NIL))),NIL)),Fcons(Fcons(Fmakesym("DELETE"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("SORT2"),Fcons(Fmakesym("L"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DSORT"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("SORT2"),Fcons(Fmakesym("X"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("X1"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("X2"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("X3"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("X4"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("X5"),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fmakesym("X6"),Fcons(Fmakesym("X7"),NIL))),NIL))),NIL))),NIL))),NIL))),NIL))),NIL)),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakeint(6),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fmakesym("X7"),NIL)),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fcons(Fmakesym("1+"),Fcons(Fcons(Fmakesym("1+"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fmakeint(2),NIL))),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("X"),NIL)),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("QUOTIENT"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fmakeint(2),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("QUOTIENT"),Fcons(Fmakesym("Y"),Fcons(Fmakeint(2),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("SIGMA"),Fcons(Fcons(Fmakesym("ZERO"),NIL),Fcons(Fmakesym("I"),NIL))),Fcons(Fcons(Fmakesym("QUOTIENT"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("I"),Fcons(Fcons(Fmakesym("1+"),Fcons(Fmakesym("I"),NIL)),NIL))),Fcons(Fmakeint(2),NIL))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("1+"),Fcons(Fmakesym("Y"),NIL)),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("1+"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),Fcons(Fcons(Fmakesym("1+"),Fcons(Fmakesym("X"),NIL)),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("Z"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Z"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),NIL)),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("Z"),NIL)),NIL))),NIL)))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fcons(Fmakesym("PLUS-TREE"),Fcons(Fcons(Fmakesym("DELETE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fcons(Fmakesym("PLUS-TREE"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fmakesym("X"),Fcons(Fmakesym("A"),NIL))),NIL))),Fcons(Fcons(Fmakesym("MEANING"),Fcons(Fcons(Fmakesym("PLUS-TREE"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fmakesym("A"),NIL))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("1+"),Fcons(Fmakesym("Y"),NIL)),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("NUMBERP"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL))),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("X"),NIL)),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("NTH"),Fcons(Fcons(NIL,NIL),Fcons(Fmakesym("I"),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("I"),NIL)),Fcons(Fcons(NIL,NIL),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LAST"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("LISTP"),Fcons(Fmakesym("B"),NIL)),Fcons(Fcons(Fmakesym("LAST"),Fcons(Fmakesym("B"),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("LISTP"),Fcons(Fmakesym("A"),NIL)),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fcons(Fmakesym("CAR"),Fcons(Fcons(Fmakesym("LAST"),Fcons(Fmakesym("A"),NIL)),NIL)),Fcons(Fmakesym("B"),NIL))),Fcons(Fmakesym("B"),NIL)))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("LESSP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(T,Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fmakesym("F"),Fcons(Fmakesym("Z"),NIL))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("ASSIGNMENT"),Fcons(Fmakesym("X"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("ASSIGNEDP"),Fcons(Fmakesym("X"),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("ASSIGNMENT"),Fcons(Fmakesym("X"),Fcons(Fmakesym("A"),NIL))),Fcons(Fcons(Fmakesym("ASSIGNMENT"),Fcons(Fmakesym("X"),Fcons(Fmakesym("B"),NIL))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("CAR"),Fcons(Fcons(Fmakesym("GOPHER"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("LISTP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("CAR"),Fcons(Fcons(Fmakesym("FLATTEN"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("FLATTEN"),Fcons(Fcons(Fmakesym("CDR"),Fcons(Fcons(Fmakesym("GOPHER"),Fcons(Fmakesym("X"),NIL)),NIL)),NIL)),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("LISTP"),Fcons(Fmakesym("X"),NIL)),Fcons(Fcons(Fmakesym("CDR"),Fcons(Fcons(Fmakesym("FLATTEN"),Fcons(Fmakesym("X"),NIL)),NIL)),Fcons(Fcons(Fmakesym("CONS"),Fcons(Fcons(Fmakesym("ZERO"),NIL),Fcons(Fcons(NIL,NIL),NIL))),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("QUOTIENT"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("X"),NIL))),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("ZEROP"),Fcons(Fmakesym("Y"),NIL)),Fcons(Fcons(Fmakesym("ZERO"),NIL),Fcons(Fcons(Fmakesym("TRUNCATE"),Fcons(Fmakesym("X"),NIL)),NIL)))),NIL))),Fcons(Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PROPERTY"),Fcons(Fmakesym("J"),Fcons(Fcons(Fmakesym("SET"),Fcons(Fmakesym("I"),Fcons(Fmakesym("VAL"),Fcons(Fmakesym("MEM"),NIL)))),NIL))),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("EQP"),Fcons(Fmakesym("J"),Fcons(Fmakesym("I"),NIL))),Fcons(Fmakesym("VAL"),Fcons(Fcons(Fmakesym("PROPERTY"),Fcons(Fmakesym("J"),Fcons(Fmakesym("MEM"),NIL))),NIL)))),NIL))),NIL)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
return(res);}
int TAUTOLOGYP(int X,int TRUE_LST,int FALSE_LST){
int res;
int temp1,temp2,temp3;
TAUTOLOGYPloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TRUE_LST)) Fshelterpush(TRUE_LST);
if(CELLRANGE(FALSE_LST)) Fshelterpush(FALSE_LST);
Fcheckgbc();
res = ({int res=NIL;
if(TRUEP(X,TRUE_LST) != NIL){
res = T;}
else if(FALSEP(X,FALSE_LST) != NIL){
res = NIL;}
else if(fast_not(({int arg1,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(arg1)));
;res;})) != NIL){
res = NIL;}
else if(({int res;Fargpush(fast_convert(fast_convert(fast_car(X))));Fargpush(fast_convert(Fmakesym("IF")));res=fast_eq();res;}) != NIL){
res = ({int res=NIL;
if(TRUEP(fast_convert(fast_car(fast_convert(fast_cdr(X)))),TRUE_LST) != NIL){
{
temp1 = ({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_immediate(2));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(arg1,Flist1(arg2))));
;res;});
temp2 = TRUE_LST;
temp3 = FALSE_LST;
if(CELLRANGE(X)) X=Fshelterpop();
if(CELLRANGE(TRUE_LST)) TRUE_LST=Fshelterpop();
if(CELLRANGE(FALSE_LST)) FALSE_LST=Fshelterpop();
X = temp1;
TRUE_LST = temp2;
FALSE_LST = temp3;
goto TAUTOLOGYPloop;};}
else if(FALSEP(fast_convert(fast_car(fast_convert(fast_cdr(X)))),FALSE_LST) != NIL){
{
temp1 = ({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_immediate(3));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(arg1,Flist1(arg2))));
;res;});
temp2 = TRUE_LST;
temp3 = FALSE_LST;
if(CELLRANGE(X)) X=Fshelterpop();
if(CELLRANGE(TRUE_LST)) TRUE_LST=Fshelterpop();
if(CELLRANGE(FALSE_LST)) FALSE_LST=Fshelterpop();
X = temp1;
TRUE_LST = temp2;
FALSE_LST = temp3;
goto TAUTOLOGYPloop;};}
else{
res = ({int res;
if((res = TAUTOLOGYP(({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_immediate(2));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(arg1,Flist1(arg2))));
;res;}),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(fast_cdr(X))))),fast_inverse(TRUE_LST)),FALSE_LST)) != NIL)
if((res=TAUTOLOGYP(({int arg1,arg2,res;
arg1 = fast_inverse(X);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_immediate(3));
Fshelterpush(arg2);
arg2=Fshelterpop();
arg1=Fshelterpop();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(arg1,Flist1(arg2))));
;res;}),TRUE_LST,Fcons(fast_inverse(fast_convert(fast_car(fast_convert(fast_cdr(X))))),fast_inverse(FALSE_LST)))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;}
;res;});}
else{
res = NIL;}
;res;});
if(CELLRANGE(FALSE_LST)) FALSE_LST=Fshelterpop();
if(CELLRANGE(TRUE_LST)) TRUE_LST=Fshelterpop();
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
int TAUTP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
Fcheckgbc();
res = TAUTOLOGYP(REWRITE(X),NIL,NIL);
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
int BOYER(){
int res;
Fcheckgbc();
res = TAUTP(APPLY_SUBST(Fcons(Fcons(Fmakesym("X"),Fcons(Fmakesym("F"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("C"),Fcons(Fcons(Fmakesym("ZERO"),NIL),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("Y"),Fcons(Fmakesym("F"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fcons(Fmakesym("TIMES"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("C"),Fcons(Fmakesym("D"),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("Z"),Fcons(Fmakesym("F"),Fcons(Fcons(Fmakesym("REVERSE"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(NIL,NIL),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("U"),Fcons(Fmakesym("EQUAL"),Fcons(Fcons(Fmakesym("PLUS"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("DIFFERENCE"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),NIL)))),Fcons(Fcons(Fmakesym("W"),Fcons(Fmakesym("LESSP"),Fcons(Fcons(Fmakesym("REMAINDER"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),NIL))),Fcons(Fcons(Fmakesym("MEMBER"),Fcons(Fmakesym("A"),Fcons(Fcons(Fmakesym("LENGTH"),Fcons(Fmakesym("B"),NIL)),NIL))),NIL)))),NIL))))),Fcons(Fmakesym("IMPLIES"),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("Y"),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("Y"),Fcons(Fmakesym("Z"),NIL))),Fcons(Fcons(Fmakesym("AND"),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("Z"),Fcons(Fmakesym("U"),NIL))),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("U"),Fcons(Fmakesym("W"),NIL))),NIL))),NIL))),NIL))),Fcons(Fcons(Fmakesym("IMPLIES"),Fcons(Fmakesym("X"),Fcons(Fmakesym("W"),NIL))),NIL)))));
return(res);}
void init_tfunctions(void){
(deftfunc)("ADD-LEMMA" , f_ADD_LEMMA);
(deftfunc)("ADD-LEMMA-LST" , f_ADD_LEMMA_LST);
(deftfunc)("APPLY-SUBST" , f_APPLY_SUBST);
(deftfunc)("APPLY-SUBST-LST" , f_APPLY_SUBST_LST);
(deftfunc)("FALSEP" , f_FALSEP);
(deftfunc)("TRUEP" , f_TRUEP);
(deftfunc)("ONE-WAY-UNIFY" , f_ONE_WAY_UNIFY);
(deftfunc)("ONE-WAY-UNIFY1" , f_ONE_WAY_UNIFY1);
(deftfunc)("ONE-WAY-UNIFY1-LST" , f_ONE_WAY_UNIFY1_LST);
(deftfunc)("REWRITE" , f_REWRITE);
(deftfunc)("REWRITE-ARGS" , f_REWRITE_ARGS);
(deftfunc)("REWRITE-WITH-LEMMAS" , f_REWRITE_WITH_LEMMAS);
(deftfunc)("BOYER-SETUP" , f_BOYER_SETUP);
(deftfunc)("TAUTOLOGYP" , f_TAUTOLOGYP);
(deftfunc)("TAUTP" , f_TAUTP);
(deftfunc)("BOYER" , f_BOYER);
}void init_declare(void){
Fsetcatchsymbols(NIL);Fset_cdr(Fmakesym("UNIFY-SUBST"),NIL);Fset_opt(Fmakesym("UNIFY-SUBST"),FAST_GLOBAL);
Fset_cdr(Fmakesym("TEMP-TEMP"),NIL);Fset_opt(Fmakesym("TEMP-TEMP"),FAST_GLOBAL);
BOYER_SETUP();}