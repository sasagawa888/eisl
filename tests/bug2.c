static int FOO(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc();
res = ({int num[PARASIZE];num[0] = Feval_para(Fcons(Fmakesym("SLEEP"),Fcons(N,NIL)));
num[1] = Feval_para(Fcons(Fmakesym("SLEEP"),Fcons(N,NIL)));
Fwait_para();
int A = Fget_para_output(num[0]);
int B = Fget_para_output(num[1]);
res = ({int arg1,res;
arg1 = Fmakesym("END");
Fpshelterpush(arg1,th);
res = Fpcallsubr(Fcar(Fmakesym("PRINT")),Flist1(arg1),th);
arg1=Fpshelterpop(th);
;res;});res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int PFIB(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc();
res = ({int res=NIL;
if(fast_numeqp(N,fast_immediate(0)) != NIL){
res = fast_immediate(0);}
else if(fast_numeqp(N,fast_immediate(1)) != NIL){
res = fast_immediate(1);}
else{
res = ({int num[PARASIZE];num[0] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(1)),NIL)));
num[1] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(2)),NIL)));
Fwait_para();
int TEMP0 = Fget_para_output(num[0]);int TEMP1 = Fget_para_output(num[1]);
res = fast_plus(TEMP0,TEMP1);
res;});}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int FIB1(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc();
res = ({int num[PARASIZE];num[0] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(1)),NIL)));
num[1] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(fast_minus(N,fast_immediate(2)),NIL)));
Fwait_para();
int A = Fget_para_output(num[0]);
int B = Fget_para_output(num[1]);
res = fast_plus(A,B);res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int FIB(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc();
res = ({int res=NIL;
if(fast_numeqp(N,fast_immediate(0)) != NIL){
res = fast_immediate(0);}
else if(fast_numeqp(N,fast_immediate(1)) != NIL){
res = fast_immediate(1);}
else{
res = fast_plus(({int arg1,res;
arg1 = fast_minus(N,fast_immediate(1));
//Fpshelterpush(arg1,th);
res = FIB(arg1,th);
//arg1=Fpshelterpop(th);
;res;}),({int arg1,res;
arg1 = fast_minus(N,fast_immediate(2));
//Fpshelterpush(arg1,th);
res = FIB(arg1,th);
//arg1=Fpshelterpop(th);
;res;}));}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
