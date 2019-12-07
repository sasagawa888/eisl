#include "fast.h"
int f_GEN_BROWSE(int arglist);int GEN_BROWSE();
int f_BROWSE_INIT(int arglist);int BROWSE_INIT(int NBS,int M,int NPATS,int IPATS);
int f_BROWSE_RANDOM(int arglist);int BROWSE_RANDOM();
int f_BROWSE_RANDOMIZE(int arglist);int BROWSE_RANDOMIZE(int L);
int f_MATCH(int arglist);int MATCH(int PAT,int DAT,int ALIST);
int f_BROWSE(int arglist);int BROWSE();
int f_INVESTIGATE(int arglist);int INVESTIGATE(int UNITS,int PATTERNS);
int f_GEN_BROWSE(int arglist){
return(fast_inverse(GEN_BROWSE() ));
}
int f_BROWSE_INIT(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(BROWSE_INIT(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_BROWSE_RANDOM(int arglist){
return(fast_inverse(BROWSE_RANDOM() ));
}
int f_BROWSE_RANDOMIZE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(BROWSE_RANDOMIZE(fast_convert(arg1))));
}
int f_MATCH(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(MATCH(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_BROWSE(int arglist){
return(fast_inverse(BROWSE() ));
}
int f_INVESTIGATE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INVESTIGATE(fast_convert(arg1),fast_convert(arg2))));
}
int GEN_BROWSE(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("*BROWSE-COUNTER*"),fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("*BROWSE-COUNTER*")))),fast_convert(Fmakeint(1)))));res;});
res = fast_convert(Fconvert(fast_inverse(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("g")),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcdr(Fmakesym("*BROWSE-COUNTER*")))),Fmakesym("<STRING>"))))))));res;})),Fmakesym("<SYMBOL>")));
return(res);}
int BROWSE_INIT(int NBS,int M,int NPATS,int IPATS){
int res;
if(CELLRANGE(NBS)) Fshelterpush(NBS);
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(NPATS)) Fshelterpush(NPATS);
if(CELLRANGE(IPATS)) Fshelterpush(IPATS);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("BROWSE-RAND"),fast_inverse(Fmakeint(21)));res;});
res = ({int res;int IP = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("IDENTITY"))),Flist1(fast_inverse(IPATS))))));({int res;
int P = fast_convert(IP);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(P)))))) == NIL){
temp1 = fast_convert(fast_cdr(P));
P = temp1;
}
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(IP),Flist1(fast_inverse(P)))));res;});res;});
res = ({int res;
int N = fast_convert(NBS);int I = fast_convert(M);int NAME = fast_convert(GEN_BROWSE());int A = fast_convert(NIL);int temp1,temp2,temp3,temp4;
while(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) == NIL){
({int res;
 res = A = Fcons(fast_inverse(NAME),fast_inverse(A));res;})
;
({int res;
int J = fast_convert(I);int temp1;
while(fast_numeqp(fast_convert(J),fast_convert(fast_immediate(0))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(NIL),Fcons(fast_inverse(NAME),Flist1(fast_inverse(GEN_BROWSE()))))));
temp1 = fast_minus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int res;
int J = fast_convert(NPATS);int P = fast_convert(IP);int X = fast_convert(NIL);int temp1,temp2,temp3;
while(fast_numeqp(fast_convert(J),fast_convert(fast_immediate(0))) == NIL){
({int res;
 res = X = Fcons(fast_inverse(fast_convert(fast_car(P))),fast_inverse(X));res;})
;
temp1 = fast_minus(fast_convert(J),fast_convert(fast_immediate(1)));
temp2 = fast_convert(fast_cdr(P));
J = temp1;
P = temp2;
}
res = X;res;})),Fcons(fast_inverse(NAME),Flist1(fast_inverse(Fmakesym("PATTERN")))))));
({int res;
int J = fast_convert(fast_minus(fast_convert(M),fast_convert(I)));int temp1;
while(fast_numeqp(fast_convert(J),fast_convert(fast_immediate(0))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(NIL),Fcons(fast_inverse(NAME),Flist1(fast_inverse(GEN_BROWSE()))))));
temp1 = fast_minus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
temp1 = fast_minus(fast_convert(N),fast_convert(fast_immediate(1)));
temp2 = ({int res;
if(fast_numeqp(fast_convert(I),fast_convert(fast_immediate(0))) != NIL){
res = M;}
else{
res = fast_minus(fast_convert(I),fast_convert(fast_immediate(1)));}res;})
;
temp3 = GEN_BROWSE();
N = temp1;
I = temp2;
NAME = temp3;
}
res = A;res;});
res;})
;
if(CELLRANGE(IPATS)) Fshelterpop();
if(CELLRANGE(NPATS)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(NBS)) Fshelterpop();
return(res);}
int BROWSE_RANDOM(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("BROWSE-RAND"),fast_inverse(fast_mod(fast_convert(fast_mult(fast_convert(fast_convert(Fcdr(Fmakesym("BROWSE-RAND")))),fast_convert(Fmakeint(17)))),fast_convert(Fmakeint(251)))));res;});
return(res);}
int BROWSE_RANDOMIZE(int L){
int res;
if(CELLRANGE(L)) Fshelterpush(L);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int A = fast_convert(NIL);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(L)))) == NIL){
({int res;int N = fast_convert(fast_mod(fast_convert(BROWSE_RANDOM()),fast_convert(Flength(L))));res = ({int res=NIL;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = ({int res;
 res = A = Fcons(fast_inverse(fast_convert(fast_car(L))),fast_inverse(A));res;})
;
res = ({int res;
 res = L = fast_convert(fast_cdr(L));res;})
;}
else{
res = ({int res;
int I = fast_convert(N);int X = fast_convert(L);int temp1,temp2;
while(fast_eq(fast_convert(I),fast_convert(fast_immediate(1))) == NIL){
temp1 = fast_minus(fast_convert(I),fast_convert(fast_immediate(1)));
temp2 = fast_convert(fast_cdr(X));
I = temp1;
X = temp2;
}
({int res;
 res = X = Fcons(fast_inverse(fast_convert(fast_car(fast_convert(fast_cdr(X))))),fast_inverse(X));res;})
;
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(X))))),Flist1(fast_inverse(X)))));res;});res;});}
;res;});
res;})
;
}
res = A;res;});
if(CELLRANGE(L)) Fshelterpop();
return(res);}
int MATCH(int PAT,int DAT,int ALIST){
int res;
int temp1,temp2,temp3;
MATCHloop:
if(CELLRANGE(PAT)) Fshelterpush(PAT);
if(CELLRANGE(DAT)) Fshelterpush(DAT);
if(CELLRANGE(ALIST)) Fshelterpush(ALIST);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(PAT))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(DAT))));res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(DAT)))) != NIL){
res = DAT;}
else if((fast_eq(fast_convert(fast_convert(fast_car(PAT))),fast_convert(Fmakesym("?"))) || fast_eq(fast_convert(fast_convert(fast_car(PAT))),fast_convert(fast_convert(fast_car(DAT))))) != NIL){
{
temp1 = fast_convert(fast_cdr(PAT));
temp2 = fast_convert(fast_cdr(DAT));
temp3 = ALIST;
if(CELLRANGE(PAT)) Fshelterpop();
if(CELLRANGE(DAT)) Fshelterpop();
if(CELLRANGE(ALIST)) Fshelterpop();
PAT = temp1;
DAT = temp2;
ALIST = temp3;
goto MATCHloop;};}
else if(fast_eq(fast_convert(fast_convert(fast_car(PAT))),fast_convert(Fmakesym("*"))) != NIL){
res = ({int res;
if((res=MATCH(fast_convert(fast_cdr(PAT)),DAT,ALIST)) == NIL)
if((res=MATCH(fast_convert(fast_cdr(PAT)),fast_convert(fast_cdr(DAT)),ALIST)) == NIL)
if((res=MATCH(PAT,fast_convert(fast_cdr(DAT)),ALIST)) !=NIL)
res=res;
else res=NIL;
else res=res;else res=res;res;})
;}
else{
res = ({int res;
if(fast_not(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(PAT))))));res;})) != NIL){
res = ({int res;int VAL = fast_convert(NIL);res = ({int res;
if(Fmember(fast_inverse(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(fast_car(PAT))),Fmakesym("<STRING>")))),Flist1(fast_inverse(fast_immediate(0))))));res;})),Fcons(Fmakechar("?"),NIL)) != NIL){
res = ({int res;
 res = VAL = fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(fast_car(PAT))),Flist1(fast_inverse(ALIST)))));res;})
;
res = ({int res;
if(VAL != NIL){
{
temp1 = Fcons(fast_inverse(fast_convert(fast_cdr(VAL))),fast_inverse(fast_convert(fast_cdr(PAT))));
temp2 = DAT;
temp3 = ALIST;
if(CELLRANGE(PAT)) Fshelterpop();
if(CELLRANGE(DAT)) Fshelterpop();
if(CELLRANGE(ALIST)) Fshelterpop();
PAT = temp1;
DAT = temp2;
ALIST = temp3;
goto MATCHloop;};}
else{
{
temp1 = fast_convert(fast_cdr(PAT));
temp2 = fast_convert(fast_cdr(DAT));
temp3 = Fcons(fast_inverse(Fcons(fast_inverse(PAT),fast_inverse(DAT))),fast_inverse(ALIST));
if(CELLRANGE(PAT)) Fshelterpop();
if(CELLRANGE(DAT)) Fshelterpop();
if(CELLRANGE(ALIST)) Fshelterpop();
PAT = temp1;
DAT = temp2;
ALIST = temp3;
goto MATCHloop;};}res;})
;}
else if(Fmember(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(fast_car(PAT))),Fmakesym("<STRING>")))),Flist1(fast_inverse(fast_immediate(0))))))),Fcons(Fmakechar("*"),NIL)) != NIL){
res = ({int res;
 res = VAL = fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(fast_car(PAT))),Flist1(fast_inverse(ALIST)))));res;})
;
res = ({int res;
if(VAL != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(fast_inverse(fast_convert(fast_cdr(VAL))),Flist1(fast_inverse(fast_convert(fast_cdr(PAT)))))));
temp2 = DAT;
temp3 = ALIST;
if(CELLRANGE(PAT)) Fshelterpop();
if(CELLRANGE(DAT)) Fshelterpop();
if(CELLRANGE(ALIST)) Fshelterpop();
PAT = temp1;
DAT = temp2;
ALIST = temp3;
goto MATCHloop;};}
else{
res = ({int res;
int L = fast_convert(NIL);int E = fast_convert(Fcons(fast_inverse(NIL),fast_inverse(DAT)));int D = fast_convert(DAT);int temp1,temp2,temp3;
while(({int res;
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(E))))) == NIL)
if((res=MATCH(fast_convert(fast_cdr(PAT)),D,Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(fast_car(PAT))),fast_inverse(L))),fast_inverse(ALIST)))) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
 == NIL){
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(fast_inverse(L),Flist1(fast_inverse(Fcons(fast_inverse(({int res;
if((res = D) != NIL)
if((res=fast_convert(fast_car(D))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
),fast_inverse(NIL)))))));
temp2 = ({int res;
if((res = E) != NIL)
if((res=fast_convert(fast_cdr(E))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
temp3 = ({int res;
if((res = D) != NIL)
if((res=fast_convert(fast_cdr(D))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
L = temp1;
E = temp2;
D = temp3;
}
res = E;res;});}res;})
;}
else{
res = NIL;}
;res;});
res;})
;}
else{
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(DAT))))));res;}) != NIL){
res = ({int res;
MATCH(fast_convert(fast_car(PAT)),fast_convert(fast_car(DAT)),ALIST);
{
temp1 = fast_convert(fast_cdr(PAT));
temp2 = fast_convert(fast_cdr(DAT));
temp3 = ALIST;
if(CELLRANGE(PAT)) Fshelterpop();
if(CELLRANGE(DAT)) Fshelterpop();
if(CELLRANGE(ALIST)) Fshelterpop();
PAT = temp1;
DAT = temp2;
ALIST = temp3;
goto MATCHloop;};res;});}
 else res = NIL;res;})
;}res;})
;}
;res;});
if(CELLRANGE(ALIST)) Fshelterpop();
if(CELLRANGE(DAT)) Fshelterpop();
if(CELLRANGE(PAT)) Fshelterpop();
return(res);}
int BROWSE(){
int res;
if(Ffreecell() < 900) Fgbc();
res = INVESTIGATE(BROWSE_RANDOMIZE(BROWSE_INIT(fast_immediate(80),fast_immediate(8),fast_immediate(4),Fcons(Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),NIL))))))))))))))))),Fcons(Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),NIL)),Fcons(Fcons(Fmakesym("B"),Fcons(Fmakesym("B"),NIL)),NIL)))))))))),Fcons(Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),Fcons(Fcons(Fmakesym("B"),Fcons(Fmakesym("A"),NIL)),Fcons(Fmakesym("B"),Fcons(Fmakesym("A"),Fcons(Fmakesym("B"),Fcons(Fmakesym("A"),NIL))))))))),NIL))))),Fcons(Fcons(Fmakesym("*A"),Fcons(Fmakesym("?B"),Fcons(Fmakesym("*B"),Fcons(Fmakesym("?B"),Fcons(Fmakesym("A"),Fcons(Fmakesym("*A"),Fcons(Fmakesym("A"),Fcons(Fmakesym("*B"),Fcons(Fmakesym("*A"),NIL))))))))),Fcons(Fcons(Fmakesym("*A"),Fcons(Fmakesym("*B"),Fcons(Fmakesym("*B"),Fcons(Fmakesym("*A"),Fcons(Fcons(Fmakesym("*A"),NIL),Fcons(Fcons(Fmakesym("*B"),NIL),NIL)))))),Fcons(Fcons(Fmakesym("?"),Fcons(Fmakesym("?"),Fcons(Fmakesym("*"),Fcons(Fcons(Fmakesym("B"),Fcons(Fmakesym("A"),NIL)),Fcons(Fmakesym("*"),Fcons(Fmakesym("?"),Fcons(Fmakesym("?"),NIL))))))),NIL))));
return(res);}
int INVESTIGATE(int UNITS,int PATTERNS){
int res;
if(CELLRANGE(UNITS)) Fshelterpush(UNITS);
if(CELLRANGE(PATTERNS)) Fshelterpush(PATTERNS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int U = fast_convert(UNITS);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(U)))) == NIL){
({int res;
int PATS = fast_convert(PATTERNS);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(PATS)))) == NIL){
({int res;
int P = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(fast_convert(fast_car(U))),Flist1(fast_inverse(Fmakesym("PATTERN")))))));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(P)))) == NIL){
MATCH(fast_convert(fast_car(PATS)),fast_convert(fast_car(P)),NIL);
temp1 = fast_convert(fast_cdr(P));
P = temp1;
}
res=NIL;res;});
temp1 = fast_convert(fast_cdr(PATS));
PATS = temp1;
}
res=NIL;res;});
temp1 = fast_convert(fast_cdr(U));
U = temp1;
}
res=NIL;res;});
if(CELLRANGE(PATTERNS)) Fshelterpop();
if(CELLRANGE(UNITS)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("GEN-BROWSE" , f_GEN_BROWSE);
(deftfunc)("BROWSE-INIT" , f_BROWSE_INIT);
(deftfunc)("BROWSE-RANDOM" , f_BROWSE_RANDOM);
(deftfunc)("BROWSE-RANDOMIZE" , f_BROWSE_RANDOMIZE);
(deftfunc)("MATCH" , f_MATCH);
(deftfunc)("BROWSE" , f_BROWSE);
(deftfunc)("INVESTIGATE" , f_INVESTIGATE);
}void init_declare(void){
Fsetcatchsymbols(NIL);Fset_cdr(Fmakesym("BROWSE-RAND"),Fmakeint(21));Fset_opt(Fmakesym("BROWSE-RAND"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*BROWSE-COUNTER*"),Fmakeint(1));Fset_opt(Fmakesym("*BROWSE-COUNTER*"),FAST_GLOBAL);
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("BROWSE-CHAR1"),Fcons(Fcons(Fmakesym("X"),NIL),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("ELT"),Fcons(Fcons(Fmakesym("CONVERT"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("X"),NIL)),Fcons(Fmakesym("<STRING>"),NIL))),Fcons(Fmakeint(0),NIL))),NIL)),NIL)))));
}