static int f_INIT_AUX(int arglist, int th){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(INIT_AUX(arg1,arg2,arg3,th));
}
