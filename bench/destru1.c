static int f_DESTRUCTIVE(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(DESTRUCTIVE(arg1,arg2,th));
}
