static int CREATE_N(int LEN, int th){
int res;
if(CELLRANGE(LEN)) Fpshelterpush(LEN,th);
Fcheckgbc(th);
res = ({int res;
Fcheckgbc(th);
int Nsubst = LEN;int Asubst = NIL;int temp1,temp2,temp3,temp4;
while(fast_numeqp(Nsubst,fast_immediate(0)) == NIL){
temp1 = fast_minus(Nsubst,fast_immediate(1));
temp2 = Fcons(NIL,Asubst);
Nsubst = temp1;
Asubst = temp2;
}
res = 