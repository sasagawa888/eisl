static int dotslashtestsslashbug4(int Y, int th){
int res;
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
res = Fnth(0,Fcdr(Fmakesym("dotslashtestsslashbug4")));
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
return(res);}
