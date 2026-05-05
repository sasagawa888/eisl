static int TEST_LAMBDA_NESTED1(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc(th);
res = ({int arg1,arg2,res;
arg1 = ({Fset_cdr(Fmakesym("dotslashtestsslashbug0"),NIL);Fcar(Fmakesym("dotslashtestsslashbug0"));});
Fpshelterpush(arg1,th);
arg2 = N;
Fpshelterpush(arg2,th);
res = Fpcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(arg1,Flist1(arg2)),th);
arg2=Fpshelterpop(th);
arg1=Fpshelterpop(th);
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int DIFFERENCE(int XS,int YS, int th){
int res;
int temp1,temp2,temp3,temp4;
DIFFERENCEloop:
 if(exit_flag == 1){exit_flag = 0; Fjump_to_repl();}if(CELLRANGE(XS)) Fpshelterpush(XS,th);
if(CELLRANGE(YS)) Fpshelterpush(YS,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(Fpcallsubr(Fcar(Fmakesym("NULL")),Flist1(XS),th)
 != NIL){
res = NIL;}
else if(Fpcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_car(XS),Flist1(YS)),th)
 != NIL){
{
temp1 = fast_cdr(XS);
temp2 = YS;
if(CELLRANGE(XS)) XS=Fpshelterpop(th);
if(CELLRANGE(YS)) YS=Fpshelterpop(th);
XS = temp1;
1;
YS = temp2;
2;
goto DIFFERENCEloop;};}
else{
res = Fcons(fast_car(XS),({int arg1,arg2,res;
arg1 = fast_cdr(XS);
arg2 = YS;
res = DIFFERENCE(arg1,arg2,th);
;res;}));}
;res;});
if(CELLRANGE(YS)) YS=Fpshelterpop(th);
if(CELLRANGE(XS)) XS=Fpshelterpop(th);
return(res);}
