static int GEN_BROWSE(int th){
int res;
Fcheckgbc(th);
({int res;
 res = Fset_cdr(Fmakesym("*BROWSE-COUNTER*"),fast_plus(Fcdr(Fmakesym("*BROWSE-COUNTER*")),fast_immediate(1)));res;});
res = Fconvert(({int arg1,arg2,res;
arg1 = Fmakestr("g");
Fpshelterpush(arg1,th);
arg2 = Fconvert(Fcdr(Fmakesym("*BROWSE-COUNTER*")),Fmakesym("<STRING>"));
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;}),Fmakesym("<SYMBOL>"));
return(res);}
static int BROWSE_INIT(int NBS,int M,int NPATS,int IPATS, int th){
int res;
if(CELLRANGE(NBS)) Fpshelterpush(NBS,th);
if(CELLRANGE(M)) Fpshelterpush(M,th);
if(CELLRANGE(NPATS)) Fpshelterpush(NPATS,th);
if(CELLRANGE(IPATS)) Fpshelterpush(IPATS,th);
Fcheckgbc(th);
({int res;
 res = Fset_cdr(Fmakesym("BROWSE-RAND"),fast_immediate(21));res;});
res = ({int res;int IPsubst = ({int arg1,arg2,res;
arg1 = Fcar(Fmakesym("IDENTITY"));
Fpshelterpush(arg1,th);
arg2 = IPATS;
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;});({int res;
Fcheckgbc(th);
int Psubst = IPsubst;int temp1,temp2,temp3;
while(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_cdr(Psubst)),th)
 == NIL){
temp1 = fast_cdr(Psubst);
Psubst = temp1;
}
res = Fpcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(IPsubst,Flist1(Psubst)),th)
;res;});
res = ({int res;
Fcheckgbc(th);
int Nsubst = NBS;int Isubst = M;int NAMEsubst = GEN_BROWSE(th);int Asubst = NIL;int temp1,temp2,temp3,temp4,temp5,temp6;
while(fast_numeqp(Nsubst,fast_immediate(0)) == NIL){
({int res;
 res = Asubst = Fcons(NAMEsubst,Asubst);res;})
;
({int res;
Fcheckgbc(th);
int Jsubst = Isubst;int temp1,temp2,temp3;
while(fast_numeqp(Jsubst,fast_immediate(0)) == NIL){
({int arg1,arg2,arg3,res;
arg1 = NIL;
Fpshelterpush(arg1,th);
arg2 = NAMEsubst;
Fpshelterpush(arg2,th);
arg3 = GEN_BROWSE(th);
Fpshelterpush(arg3,th);
res = Fpcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(arg1,Fcons(arg2,Flist1(arg3))),th);
arg3=Fpshelterpop(th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;});
temp1 = fast_minus(Jsubst,fast_immediate(1));
Jsubst = temp1;
}
res=NIL;res;});
({int arg1,arg2,arg3,res;
arg1 = ({int res;
Fcheckgbc(th);
int Jsubst = NPATS;int Psubst = IPsubst;int Xsubst = NIL;int temp1,temp2,temp3,temp4,temp5;
while(fast_numeqp(Jsubst,fast_immediate(0)) == NIL){
({int res;
 res = Xsubst = Fcons(fast_car(Psubst),Xsubst);res;})
;
temp1 = fast_minus(Jsubst,fast_immediate(1));
temp2 = fast_cdr(Psubst);
Jsubst = temp1;
Psubst = temp2;
}
res = 