#include "fast.h"
int f_DISPLAY(int arglist);int DISPLAY(int X);
int f_NEWLINE(int arglist);int NEWLINE();
int f_CDRstar(int arglist);int CDRstar(int X);
int f_CAAR(int arglist);int CAAR(int X);
int f_CADR(int arglist);int CADR(int X);
int f_CDDR(int arglist);int CDDR(int X);
int f_CDDAR(int arglist);int CDDAR(int X);
int f_PROLOG(int arglist);int PROLOG();
int f_READ_WITH_PROMPT(int arglist);int READ_WITH_PROMPT();
int f_DEFINE_CLAUSE(int arglist);int DEFINE_CLAUSE(int CLAUSE);
int f_REFUTES(int arglist);int REFUTES(int CLAUSE,int OLD_SUBST,int NEW_SUBST,int CUE);
int f_REFUTE(int arglist);int REFUTE(int CLAUSE,int DEFINITIONS,int OLD_SUBST,int NEW_SUBST,int CUE);
int f_RESOLVE(int arglist);int RESOLVE(int CLAUSE,int DEFINITIONS,int NEW_SUBST,int OLD_SUBST,int CUE);
int f_UNDO(int arglist);int UNDO(int U);
int f_LINK(int arglist);int LINK(int X,int X_SUBST,int Y,int Y_SUBST);
int f_UNIFY(int arglist);int UNIFY(int X,int X_SUBST,int Y,int Y_SUBST);
int f_FETCH(int arglist);int FETCH(int X,int SUBST);
int f_SET_UP(int arglist);int SET_UP();
int f_dotslashexampleslashppisl0(int arglist);int dotslashexampleslashppisl0(int FORM,int SUBST);
int f_dotslashexampleslashppisl1(int arglist);int dotslashexampleslashppisl1(int FORM,int SUBST);
int f_dotslashexampleslashppisl2(int arglist);int dotslashexampleslashppisl2(int X);
int f_dotslashexampleslashppisl3(int arglist);int dotslashexampleslashppisl3(int FORM,int SUBST);
int f_dotslashexampleslashppisl4(int arglist);int dotslashexampleslashppisl4(int FORM,int SUBST);
int f_dotslashexampleslashppisl5(int arglist);int dotslashexampleslashppisl5(int X);
int f_TRY_SYS(int arglist);int TRY_SYS(int FORM,int SUBST);
int f_VARP(int arglist);int VARP(int X);
int f_ASSIGNEDP(int arglist);int ASSIGNEDP(int X,int SUBST);
int f_FETCH_VALUE(int arglist);int FETCH_VALUE(int X,int SUBST);
int f_FIRST(int arglist);int FIRST(int X);
int f_SECOND(int arglist);int SECOND(int X);
int f_THIRD(int arglist);int THIRD(int X);
int f_DISPLAY(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DISPLAY(fast_convert(arg1))));
}
int f_NEWLINE(int arglist){
return(fast_inverse(NEWLINE() ));
}
int f_CDRstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CDRstar(fast_convert(arg1))));
}
int f_CAAR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CAAR(fast_convert(arg1))));
}
int f_CADR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CADR(fast_convert(arg1))));
}
int f_CDDR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CDDR(fast_convert(arg1))));
}
int f_CDDAR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CDDAR(fast_convert(arg1))));
}
int f_PROLOG(int arglist){
return(fast_inverse(PROLOG() ));
}
int f_READ_WITH_PROMPT(int arglist){
return(fast_inverse(READ_WITH_PROMPT() ));
}
int f_DEFINE_CLAUSE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DEFINE_CLAUSE(fast_convert(arg1))));
}
int f_REFUTES(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(REFUTES(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_REFUTE(int arglist){
int arg1,arg2,arg3,arg4,arg5;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
return(fast_inverse(REFUTE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5))));
}
int f_RESOLVE(int arglist){
int arg1,arg2,arg3,arg4,arg5;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
return(fast_inverse(RESOLVE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5))));
}
int f_UNDO(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(UNDO(fast_convert(arg1))));
}
int f_LINK(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(LINK(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_UNIFY(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(UNIFY(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_FETCH(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FETCH(fast_convert(arg1),fast_convert(arg2))));
}
int f_SET_UP(int arglist){
return(fast_inverse(SET_UP() ));
}
int f_dotslashexampleslashppisl0(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(dotslashexampleslashppisl0(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashppisl1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(dotslashexampleslashppisl1(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashppisl2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashppisl2(fast_convert(arg1))));
}
int f_dotslashexampleslashppisl3(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(dotslashexampleslashppisl3(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashppisl4(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(dotslashexampleslashppisl4(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashppisl5(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashppisl5(fast_convert(arg1))));
}
int f_TRY_SYS(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TRY_SYS(fast_convert(arg1),fast_convert(arg2))));
}
int f_VARP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(VARP(fast_convert(arg1))));
}
int f_ASSIGNEDP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ASSIGNEDP(fast_convert(arg1),fast_convert(arg2))));
}
int f_FETCH_VALUE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FETCH_VALUE(fast_convert(arg1),fast_convert(arg2))));
}
int f_FIRST(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIRST(fast_convert(arg1))));
}
int f_SECOND(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SECOND(fast_convert(arg1))));
}
int f_THIRD(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(THIRD(fast_convert(arg1))));
}
int dotslashexampleslashppisl0(int FORM,int SUBST){
int res;
if(CELLRANGE(FORM)) Fshelterpush(FORM);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
res = DEFINE_CLAUSE(FETCH_VALUE(FORM,SUBST));
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(FORM)) Fshelterpop();
return(res);}
int dotslashexampleslashppisl1(int FORM,int SUBST){
int res;
if(CELLRANGE(FORM)) Fshelterpush(FORM);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
res = ({int res;int F = fast_convert(FETCH_VALUE(FIRST(FORM),SUBST));res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPLY")),Fcons(fast_inverse(Fcar(F)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashppisl2"),Fcons(SUBST,Fcons(T,NIL)));Fcar(Fmakesym("dotslashexampleslashppisl2"));})),Flist1(fast_inverse(CDRstar(FORM)))))))))));
res;})
;
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(FORM)) Fshelterpop();
return(res);}
int dotslashexampleslashppisl3(int FORM,int SUBST){
int res;
if(CELLRANGE(FORM)) Fshelterpush(FORM);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
res = ({int res;
 res = Fset_cdr(Fmakesym("EPILOG"),fast_inverse(T));res;});
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(FORM)) Fshelterpop();
return(res);}
int dotslashexampleslashppisl4(int FORM,int SUBST){
int res;
if(CELLRANGE(FORM)) Fshelterpush(FORM);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
res = ({int res;int F = fast_convert(FETCH_VALUE(fast_convert(fast_car(FIRST(FORM))),SUBST));res = ({int res=NIL;
if(UNIFY(fast_convert(Fcallsubr(Fcar(Fmakesym("APPLY")),Fcons(fast_inverse(Fcar(F)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashppisl5"),Fcons(SUBST,Fcons(T,NIL)));Fcar(Fmakesym("dotslashexampleslashppisl5"));})),Flist1(fast_inverse(CDRstar(FIRST(FORM)))))))))))),SUBST,SECOND(FORM),SUBST) != NIL){
res = T;}
else{
res = NIL;}
;res;});
res;})
;
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(FORM)) Fshelterpop();
return(res);}
int dotslashexampleslashppisl2(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = FETCH_VALUE(X,Fnth(0,Fcdr(Fmakesym("dotslashexampleslashppisl2"))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int dotslashexampleslashppisl5(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = FETCH_VALUE(X,Fnth(0,Fcdr(Fmakesym("dotslashexampleslashppisl5"))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int DISPLAY(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("~A")),Flist1(fast_inverse(X))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int NEWLINE(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("~%"))))));res;});
return(res);}
int CDRstar(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X))));res;}) != NIL){
res = NIL;}
else{
res = fast_convert(fast_cdr(X));}res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CAAR(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(fast_car(fast_convert(fast_car(X))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CADR(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(fast_car(CDRstar(X)));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CDDR(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = CDRstar(CDRstar(X));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CDDAR(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = CDRstar(CDRstar(fast_convert(fast_car(X))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int PROLOG(){
int res;
if(Ffreecell() < 900) Fgbc();
DISPLAY(Fmakestr("Portable Prolog (in ISLisp)"));
SET_UP();
({int res;
while(fast_convert(Fcdr(Fmakesym("EPILOG"))) == NIL){
({int res;
 res = Fset_cdr(Fmakesym("FETCHED-SUBST"),fast_inverse(Fmakesym("NIL")));res;});
({int res;
 res = Fset_cdr(Fmakesym("UNDO-LIST"),fast_inverse(Fmakesym("NIL")));res;});
DISPLAY(REFUTES(Fcons(fast_inverse(READ_WITH_PROMPT()),fast_inverse(Fmakesym("NIL"))),Fcons(fast_inverse(Fmakesym("NIL")),fast_inverse(Fmakesym("NIL"))),Fcons(fast_inverse(Fmakesym("NIL")),fast_inverse(Fmakesym("NIL"))),Fmakesym("NIL")));
}
res=NIL;res;});
res = ({int res;
 res = Fset_cdr(Fmakesym("EPILOG"),fast_inverse(NIL));res;});
return(res);}
int READ_WITH_PROMPT(){
int res;
if(Ffreecell() < 900) Fgbc();
NEWLINE();
DISPLAY(Fmakestr(": "));
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("READ")),NIL));res;});
return(res);}
int DEFINE_CLAUSE(int CLAUSE){
int res;
if(CELLRANGE(CLAUSE)) Fshelterpush(CLAUSE);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int DEFINITION = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(CAAR(CLAUSE)),Flist1(fast_inverse(Fmakesym("PROLOG")))))));({int res;
if(fast_not(DEFINITION) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(Fcons(fast_inverse(CLAUSE),fast_inverse(Fmakesym("NIL")))),Fcons(fast_inverse(CAAR(CLAUSE)),Flist1(fast_inverse(Fmakesym("PROLOG")))))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(fast_inverse(DEFINITION),Flist1(fast_inverse(Fcons(fast_inverse(CLAUSE),fast_inverse(Fmakesym("NIL"))))))))),Fcons(fast_inverse(CAAR(CLAUSE)),Flist1(fast_inverse(Fmakesym("PROLOG")))))));res;});}res;})
;
DISPLAY(Fmakestr("defined"));
NEWLINE();
res = T;
res;})
;
if(CELLRANGE(CLAUSE)) Fshelterpop();
return(res);}
int REFUTES(int CLAUSE,int OLD_SUBST,int NEW_SUBST,int CUE){
int res;
int temp1,temp2,temp3,temp4;
REFUTESloop:
if(CELLRANGE(CLAUSE)) Fshelterpush(CLAUSE);
if(CELLRANGE(OLD_SUBST)) Fshelterpush(OLD_SUBST);
if(CELLRANGE(NEW_SUBST)) Fshelterpush(NEW_SUBST);
if(CELLRANGE(CUE)) Fshelterpush(CUE);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(CLAUSE))));res;}) != NIL){
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(CUE))));res;}) != NIL){
res = Fmakesym("*S*");}
else{
{
temp1 = fast_convert(fast_car(FIRST(CUE)));
temp2 = CDRstar(FIRST(CUE));
temp3 = Fcons(fast_inverse(Fmakesym("NIL")),fast_inverse(Fmakesym("NIL")));
temp4 = CDRstar(CUE);
if(CELLRANGE(CLAUSE)) Fshelterpop();
if(CELLRANGE(OLD_SUBST)) Fshelterpop();
if(CELLRANGE(NEW_SUBST)) Fshelterpop();
if(CELLRANGE(CUE)) Fshelterpop();
CLAUSE = temp1;
OLD_SUBST = temp2;
NEW_SUBST = temp3;
CUE = temp4;
goto REFUTESloop;};}
;res;});}
else if((VARP(CLAUSE) && ASSIGNEDP(CLAUSE,OLD_SUBST)) != NIL){
{
temp1 = FETCH_VALUE(CLAUSE,OLD_SUBST);
temp2 = fast_convert(Fcdr(Fmakesym("FETCHED-SUBST")));
temp3 = NEW_SUBST;
temp4 = CUE;
if(CELLRANGE(CLAUSE)) Fshelterpop();
if(CELLRANGE(OLD_SUBST)) Fshelterpop();
if(CELLRANGE(NEW_SUBST)) Fshelterpop();
if(CELLRANGE(CUE)) Fshelterpop();
CLAUSE = temp1;
OLD_SUBST = temp2;
NEW_SUBST = temp3;
CUE = temp4;
goto REFUTESloop;};}
else if((VARP(FIRST(CLAUSE)) && ASSIGNEDP(FIRST(CLAUSE),OLD_SUBST)) != NIL){
{
temp1 = Fcons(fast_inverse(FETCH_VALUE(FIRST(CLAUSE),OLD_SUBST)),fast_inverse(Fmakesym("NIL")));
temp2 = fast_convert(Fcdr(Fmakesym("FETCHED-SUBST")));
temp3 = NEW_SUBST;
temp4 = Fcons(fast_inverse(Fcons(fast_inverse(CDRstar(CLAUSE)),fast_inverse(OLD_SUBST))),fast_inverse(CUE));
if(CELLRANGE(CLAUSE)) Fshelterpop();
if(CELLRANGE(OLD_SUBST)) Fshelterpop();
if(CELLRANGE(NEW_SUBST)) Fshelterpop();
if(CELLRANGE(CUE)) Fshelterpop();
CLAUSE = temp1;
OLD_SUBST = temp2;
NEW_SUBST = temp3;
CUE = temp4;
goto REFUTESloop;};}
else{
res = REFUTE(CLAUSE,fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(CAAR(CLAUSE)),Flist1(fast_inverse(Fmakesym("PROLOG")))))),OLD_SUBST,NEW_SUBST,CUE);}
;res;});
if(CELLRANGE(CUE)) Fshelterpop();
if(CELLRANGE(NEW_SUBST)) Fshelterpop();
if(CELLRANGE(OLD_SUBST)) Fshelterpop();
if(CELLRANGE(CLAUSE)) Fshelterpop();
return(res);}
int REFUTE(int CLAUSE,int DEFINITIONS,int OLD_SUBST,int NEW_SUBST,int CUE){
int res;
if(CELLRANGE(CLAUSE)) Fshelterpush(CLAUSE);
if(CELLRANGE(DEFINITIONS)) Fshelterpush(DEFINITIONS);
if(CELLRANGE(OLD_SUBST)) Fshelterpush(OLD_SUBST);
if(CELLRANGE(NEW_SUBST)) Fshelterpush(NEW_SUBST);
if(CELLRANGE(CUE)) Fshelterpush(CUE);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_not(DEFINITIONS) != NIL){
res = ({int res=NIL;
if((TRY_SYS(fast_convert(fast_car(CLAUSE)),OLD_SUBST) && REFUTES(CDRstar(CLAUSE),OLD_SUBST,Fcons(fast_inverse(Fmakesym("NIL")),fast_inverse(Fmakesym("NIL"))),CUE)) != NIL){
res = T;}
else{
res = UNDO(fast_convert(Fcdr(Fmakesym("UNDO-LIST"))));}
;res;});}
else{
res = RESOLVE(CLAUSE,DEFINITIONS,NEW_SUBST,OLD_SUBST,CUE);}
;res;});
if(CELLRANGE(CUE)) Fshelterpop();
if(CELLRANGE(NEW_SUBST)) Fshelterpop();
if(CELLRANGE(OLD_SUBST)) Fshelterpop();
if(CELLRANGE(DEFINITIONS)) Fshelterpop();
if(CELLRANGE(CLAUSE)) Fshelterpop();
return(res);}
int RESOLVE(int CLAUSE,int DEFINITIONS,int NEW_SUBST,int OLD_SUBST,int CUE){
int res;
int temp1,temp2,temp3,temp4,temp5;
RESOLVEloop:
if(CELLRANGE(CLAUSE)) Fshelterpush(CLAUSE);
if(CELLRANGE(DEFINITIONS)) Fshelterpush(DEFINITIONS);
if(CELLRANGE(NEW_SUBST)) Fshelterpush(NEW_SUBST);
if(CELLRANGE(OLD_SUBST)) Fshelterpush(OLD_SUBST);
if(CELLRANGE(CUE)) Fshelterpush(CUE);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(DEFINITIONS))));res;}) != NIL){
res = NIL;}
else if((UNIFY(fast_convert(fast_car(CLAUSE)),OLD_SUBST,CAAR(DEFINITIONS),NEW_SUBST) && REFUTES(CDRstar(FIRST(DEFINITIONS)),NEW_SUBST,Fcons(fast_inverse(Fmakesym("NIL")),fast_inverse(Fmakesym("NIL"))),Fcons(fast_inverse(Fcons(fast_inverse(CDRstar(CLAUSE)),fast_inverse(OLD_SUBST))),fast_inverse(CUE)))) != NIL){
res = T;}
else{
res = UNDO(fast_convert(Fcdr(Fmakesym("UNDO-LIST"))));
{
temp1 = CLAUSE;
temp2 = CDRstar(DEFINITIONS);
temp3 = NEW_SUBST;
temp4 = OLD_SUBST;
temp5 = CUE;
if(CELLRANGE(CLAUSE)) Fshelterpop();
if(CELLRANGE(DEFINITIONS)) Fshelterpop();
if(CELLRANGE(NEW_SUBST)) Fshelterpop();
if(CELLRANGE(OLD_SUBST)) Fshelterpop();
if(CELLRANGE(CUE)) Fshelterpop();
CLAUSE = temp1;
DEFINITIONS = temp2;
NEW_SUBST = temp3;
OLD_SUBST = temp4;
CUE = temp5;
goto RESOLVEloop;};}
;res;});
if(CELLRANGE(CUE)) Fshelterpop();
if(CELLRANGE(OLD_SUBST)) Fshelterpop();
if(CELLRANGE(NEW_SUBST)) Fshelterpop();
if(CELLRANGE(DEFINITIONS)) Fshelterpop();
if(CELLRANGE(CLAUSE)) Fshelterpop();
return(res);}
int UNDO(int U){
int res;
int temp1;
UNDOloop:
if(CELLRANGE(U)) Fshelterpush(U);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(U))));res;}) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("UNDO-LIST"),fast_inverse(Fmakesym("NIL")));res;});
res = NIL;}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(CDDAR(U)),Flist1(fast_inverse(fast_convert(fast_car(U)))))));
{
temp1 = CDRstar(U);
if(CELLRANGE(U)) Fshelterpop();
U = temp1;
goto UNDOloop;};}
;res;});
if(CELLRANGE(U)) Fshelterpop();
return(res);}
int LINK(int X,int X_SUBST,int Y,int Y_SUBST){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(X_SUBST)) Fshelterpush(X_SUBST);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(Y_SUBST)) Fshelterpush(Y_SUBST);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_eq(fast_convert(X),fast_convert(Y)) && fast_eq(fast_convert(X_SUBST),fast_convert(Y_SUBST))) != NIL){
res = T;}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("UNDO-LIST"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(X),fast_inverse(Fcons(fast_inverse(FETCH(Y,Y_SUBST)),fast_inverse(fast_convert(Fcdr(Fmakesym("FETCHED-SUBST")))))))),fast_inverse(CDRstar(X_SUBST)))),Flist1(fast_inverse(X_SUBST)))))),fast_inverse(fast_convert(Fcdr(Fmakesym("UNDO-LIST")))))));res;});}
;res;});
if(CELLRANGE(Y_SUBST)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X_SUBST)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int UNIFY(int X,int X_SUBST,int Y,int Y_SUBST){
int res;
int temp1,temp2,temp3,temp4;
UNIFYloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(X_SUBST)) Fshelterpush(X_SUBST);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(Y_SUBST)) Fshelterpush(Y_SUBST);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(VARP(X) != NIL){
res = ({int res=NIL;
if(ASSIGNEDP(X,X_SUBST) != NIL){
{
temp1 = FETCH(X,X_SUBST);
temp2 = fast_convert(Fcdr(Fmakesym("FETCHED-SUBST")));
temp3 = Y;
temp4 = Y_SUBST;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(X_SUBST)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(Y_SUBST)) Fshelterpop();
X = temp1;
X_SUBST = temp2;
Y = temp3;
Y_SUBST = temp4;
goto UNIFYloop;};}
else{
res = LINK(X,X_SUBST,Y,Y_SUBST);}
;res;});}
else if(VARP(Y) != NIL){
{
temp1 = Y;
temp2 = Y_SUBST;
temp3 = X;
temp4 = X_SUBST;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(X_SUBST)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(Y_SUBST)) Fshelterpop();
X = temp1;
X_SUBST = temp2;
Y = temp3;
Y_SUBST = temp4;
goto UNIFYloop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(X),Flist1(fast_inverse(Y)))));res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(Y)))) != NIL){
res = NIL;}
else if(UNIFY(fast_convert(fast_car(X)),X_SUBST,fast_convert(fast_car(Y)),Y_SUBST) != NIL){
{
temp1 = CDRstar(X);
temp2 = X_SUBST;
temp3 = CDRstar(Y);
temp4 = Y_SUBST;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(X_SUBST)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(Y_SUBST)) Fshelterpop();
X = temp1;
X_SUBST = temp2;
Y = temp3;
Y_SUBST = temp4;
goto UNIFYloop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(Y_SUBST)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X_SUBST)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FETCH(int X,int SUBST){
int res;
int temp1,temp2;
FETCHloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("FETCHED-SUBST"),fast_inverse(SUBST));res;});
res = ({int res=NIL;
if(VARP(X) != NIL){
res = ({int res;int V = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(CDRstar(SUBST)))))));res = ({int res=NIL;
if(fast_not(V) != NIL){
res = X;}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("FETCHED-SUBST"),fast_inverse(CDDR(V)));res;});
{
temp1 = SECOND(V);
temp2 = CDDR(V);
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(SUBST)) Fshelterpop();
X = temp1;
SUBST = temp2;
goto FETCHloop;};}
;res;});
res;})
;}
else{
res = X;}
;res;});
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SET_UP(){
int res;
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashppisl0"),Fcons(T,NIL));Fcar(Fmakesym("dotslashexampleslashppisl0"));})),Fcons(fast_inverse(Fmakesym("ASSERT")),Flist1(fast_inverse(Fmakesym("PRIMITIVE")))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashppisl1"),Fcons(T,NIL));Fcar(Fmakesym("dotslashexampleslashppisl1"));})),Fcons(fast_inverse(Fmakesym("CALL")),Flist1(fast_inverse(Fmakesym("PRIMITIVE")))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashppisl3"),Fcons(T,NIL));Fcar(Fmakesym("dotslashexampleslashppisl3"));})),Fcons(fast_inverse(Fmakesym("HALT")),Flist1(fast_inverse(Fmakesym("PRIMITIVE")))))));
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashppisl4"),Fcons(T,NIL));Fcar(Fmakesym("dotslashexampleslashppisl4"));})),Fcons(fast_inverse(Fmakesym("EVAL")),Flist1(fast_inverse(Fmakesym("PRIMITIVE")))))));res;});
return(res);}
int TRY_SYS(int FORM,int SUBST){
int res;
if(CELLRANGE(FORM)) Fshelterpush(FORM);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(fast_convert(fast_car(FORM))),Flist1(fast_inverse(Fmakesym("PRIMITIVE"))))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("APPLY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(fast_convert(fast_car(FORM))),Flist1(fast_inverse(Fmakesym("PRIMITIVE"))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(CDRstar(FORM)),Flist1(fast_inverse(SUBST))))))))));res;});}
else{
res = NIL;}res;})
;
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(FORM)) Fshelterpop();
return(res);}
int VARP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("AREF")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>")))),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(Fmakechar("*"))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int ASSIGNEDP(int X,int SUBST){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(CDRstar(SUBST))))));res;});
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FETCH_VALUE(int X,int SUBST){
int res;
int temp1,temp2;
FETCH_VALUEloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(VARP(X) != NIL){
res = ({int res;int V = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(CDRstar(SUBST)))))));res = ({int res;
if(fast_not(V) != NIL){
res = X;}
else{
{
temp1 = SECOND(V);
temp2 = CDDR(V);
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(SUBST)) Fshelterpop();
X = temp1;
SUBST = temp2;
goto FETCH_VALUEloop;};}res;})
;
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = X;}
else{
res = Fcons(fast_inverse(FETCH_VALUE(fast_convert(fast_car(X)),SUBST)),fast_inverse(FETCH_VALUE(CDRstar(X),SUBST)));}
;res;});
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIRST(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(fast_car(X));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SECOND(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = CADR(X);
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int THIRD(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = Fapply(Fcar(Fmakesym("CADDR")),Flist1(fast_inverse(X)));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("DISPLAY" , f_DISPLAY);
(deftfunc)("NEWLINE" , f_NEWLINE);
(deftfunc)("CDR*" , f_CDRstar);
(deftfunc)("CAAR" , f_CAAR);
(deftfunc)("CADR" , f_CADR);
(deftfunc)("CDDR" , f_CDDR);
(deftfunc)("CDDAR" , f_CDDAR);
(deftfunc)("PROLOG" , f_PROLOG);
(deftfunc)("READ-WITH-PROMPT" , f_READ_WITH_PROMPT);
(deftfunc)("DEFINE-CLAUSE" , f_DEFINE_CLAUSE);
(deftfunc)("REFUTES" , f_REFUTES);
(deftfunc)("REFUTE" , f_REFUTE);
(deftfunc)("RESOLVE" , f_RESOLVE);
(deftfunc)("UNDO" , f_UNDO);
(deftfunc)("LINK" , f_LINK);
(deftfunc)("UNIFY" , f_UNIFY);
(deftfunc)("FETCH" , f_FETCH);
(deftfunc)("dotslashexampleslashppisl0" , f_dotslashexampleslashppisl0);
(deftfunc)("dotslashexampleslashppisl2" , f_dotslashexampleslashppisl2);
(deftfunc)("dotslashexampleslashppisl1" , f_dotslashexampleslashppisl1);
(deftfunc)("dotslashexampleslashppisl3" , f_dotslashexampleslashppisl3);
(deftfunc)("dotslashexampleslashppisl5" , f_dotslashexampleslashppisl5);
(deftfunc)("dotslashexampleslashppisl4" , f_dotslashexampleslashppisl4);
(deftfunc)("SET-UP" , f_SET_UP);
(deftfunc)("TRY-SYS" , f_TRY_SYS);
(deftfunc)("VARP" , f_VARP);
(deftfunc)("ASSIGNEDP" , f_ASSIGNEDP);
(deftfunc)("FETCH-VALUE" , f_FETCH_VALUE);
(deftfunc)("FIRST" , f_FIRST);
(deftfunc)("SECOND" , f_SECOND);
(deftfunc)("THIRD" , f_THIRD);
}void init_declare(void){
Fsetcatchsymbols(NIL);Fset_cdr(Fmakesym("FETCHED-SUBST"),Fmakesym("NIL"));Fset_opt(Fmakesym("FETCHED-SUBST"),FAST_GLOBAL);
Fset_cdr(Fmakesym("UNDO-LIST"),Fmakesym("NIL"));Fset_opt(Fmakesym("UNDO-LIST"),FAST_GLOBAL);
Fset_cdr(Fmakesym("EPILOG"),NIL);Fset_opt(Fmakesym("EPILOG"),FAST_GLOBAL);
}