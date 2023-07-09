static int FOO(int X,int Y, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
Fcheckgbc();
res = ({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_plus(th);res;});
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
if(CELLRANGE(X)) X=Fpshelterpop(th);
return(res);}
