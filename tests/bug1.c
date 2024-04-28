static int f_TARAIstar(int arglist, int th){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(TARAIstar(arg1,arg2,arg3,th));
}
