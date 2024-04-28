static int TARAIstar(int X,int Y,int Z, int th){
int res;
if(CELLRANGE(X)) Fpshelterpush(X,th);
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
if(CELLRANGE(Z)) Fpshelterpush(Z,th);
Fcheckgbc();
res = ({int res;
if(({int res;Fpargpush(X,th);Fpargpush(Y,th);res=pfast_eqsmallerp(th);res;}) != NIL){
res = Y;}
else{
res = ({int res;Fwrite_to_pipe(Fsexp_to_str(Fcons(Fmake_sym("TARAI"),