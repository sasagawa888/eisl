static int testsslashbug0(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
({int res;
 res = fast_setnth(Fcdr(Fmakesym("testsslashbug0")),0,({int res;Fargpush(Fnth(0,Fcdr(Fmakesym("testsslashbug0"))));Fargpush(X);res=fast_plus();res;}));res;});
res = Fcallsubr(Fcar(Fmakesym("PRINT")),Flist1(Fnth(0,Fcdr(Fmakesym("testsslashbug0")))))
;
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
static int testsslashbug1(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
({int res;
 res = fast_setnth(Fcdr(Fmakesym("testsslashbug1")),0,({int res;Fargpush(Fnth(0,Fcdr(Fmakesym("testsslashbug1"))));Fargpush(X);res=fast_plus();res;}));res;});
res = Fnth(0,Fcdr(Fmakesym("testsslashbug1")));
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
