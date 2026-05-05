static int dotslashtestsslashbug1(int Y, int th){
int res;
if(CELLRANGE(Y)) Fpshelterpush(Y,th);
res = fast_plus(Fnth(0,Fcdr(Fmakesym("dotslashtestsslashbug0"))),Y);
if(CELLRANGE(Y)) Y=Fpshelterpop(th);
return(res);}
