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
if(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(0),th);res=pfast_numeqp(th);res;}) != NIL){
res = fast_immediate(0);}
else if(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(1),th);res=pfast_numeqp(th);res;}) != NIL){
res = fast_immediate(1);}
else{
res = ({int num[PARASIZE];num[0] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(1),th);res=pfast_minus(th);res;}),NIL)));
num[1] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(2),th);res=pfast_minus(th);res;}),NIL)));
Fwait_para();
int TEMP0 = Fget_para_output(num[0]);int TEMP1 = Fget_para_output(num[1]);
res = ({int res;Fpargpush(TEMP0,th);Fpargpush(TEMP1,th);res=pfast_plus(th);res;});
res;});}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int FIB1(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc();
res = ({int num[PARASIZE];num[0] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(1),th);res=pfast_minus(th);res;}),NIL)));
num[1] = Feval_para(Fcons(Fmakesym("FIB"),Fcons(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(2),th);res=pfast_minus(th);res;}),NIL)));
Fwait_para();
int A = Fget_para_output(num[0]);
int B = Fget_para_output(num[1]);
res = ({int res;Fpargpush(A,th);Fpargpush(B,th);res=pfast_plus(th);res;});res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
static int FIB(int N, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
Fcheckgbc();
res = ({int res=NIL;
if(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(0),th);res=pfast_numeqp(th);res;}) != NIL){
res = fast_immediate(0);}
else if(({int res;Fpargpush(N,th);Fpargpush(fast_immediate(1),th);res=pfast_numeqp(th);res;}) != NIL){
res = fast_immediate(1);}
else{
res = ({int res;Fpargpush(({int arg1,res;
arg1 = ({int res;Fpargpush(N,th);Fpargpush(fast_immediate(1),th);res=pfast_minus(th);res;});
Fpshelterpush(arg1,th);
res = FIB(arg1,th);
arg1=Fpshelterpop(th);
;res;}),th);Fpargpush(({int arg1,res;
arg1 = ({int res;Fpargpush(N,th);Fpargpush(fast_immediate(2),th);res=pfast_minus(th);res;});
Fpshelterpush(arg1,th);
res = FIB(arg1,th);
arg1=Fpshelterpop(th);
;res;}),th);res=pfast_plus(th);res;});}
;res;});
if(CELLRANGE(N)) N=Fpshelterpop(th);
return(res);}
