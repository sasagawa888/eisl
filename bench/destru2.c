static int DESTRUCTIVE(int N,int M, int th){
int res;
if(CELLRANGE(N)) Fpshelterpush(N,th);
if(CELLRANGE(M)) Fpshelterpush(M,th);
Fcheckgbc(th);
res = ({int res;int Lsubst = ({int res;
Fcheckgbc(th);
int Isubst = fast_immediate(10);int Asubst = NIL;int temp1,temp2,temp3,temp4;
while(fast_numeqp(Isubst,fast_immediate(0)) == NIL){
temp1 = fast_minus(Isubst,fast_immediate(1));
temp2 = Fcons(NIL,Asubst);
Isubst = temp1;
Asubst = temp2;
}
res = 