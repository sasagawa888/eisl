static int INIT_AUX(int M,int N,int ATOMS, int th){
int res;
if(CELLRANGE(M)) Fpshelterpush(M,th);
if(CELLRANGE(N)) Fpshelterpush(N,th);
if(CELLRANGE(ATOMS)) Fpshelterpush(ATOMS,th);
Fcheckgbc(th);
res = ({int res=NIL;
if(fast_numeqp(M,fast_immediate(0)) != NIL){
res = fast_car(ATOMS);}
else{
res = ({int res;
Fcheckgbc(th);
int Isubst = N;int Asubst = NIL;int temp1,temp2,temp3,temp4;
while(fast_smallerp(Isubst,fast_immediate(1)) == NIL){
({int res;
 res = Asubst = Fcons(fast_car(ATOMS),Asubst);res;})
;
({int res;
 res = ATOMS = fast_cdr(ATOMS);res;})
;
({int res;
 res = Asubst = Fcons(({int arg1,arg2,arg3,res;
arg1 = fast_minus(M,fast_immediate(1));
arg2 = N;
arg3 = ATOMS;
res = INIT_AUX(arg1,arg2,arg3,th);
;res;}),Asubst);res;})
;
temp1 = fast_minus(Isubst,fast_immediate(2));
Isubst = temp1;
}
res = 