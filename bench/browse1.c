static int f_GEN_BROWSE(int arglist, int th){
return(GEN_BROWSE(th) );
}
static int f_BROWSE_INIT(int arglist, int th){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(BROWSE_INIT(arg1,arg2,arg3,arg4,th));
}
