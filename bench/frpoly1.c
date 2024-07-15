static int f_PCOEFADD(int arglist, int th){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(PCOEFADD(arg1,arg2,arg3,th));
}
static int f_PCPLUS(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PCPLUS(arg1,arg2,th));
}
static int f_PCPLUS1(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PCPLUS1(arg1,arg2,th));
}
static int f_PCTIMES(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PCTIMES(arg1,arg2,th));
}
static int f_PCTIMES1(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PCTIMES1(arg1,arg2,th));
}
static int f_PPLUS(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PPLUS(arg1,arg2,th));
}
static int f_PPLUS1(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PPLUS1(arg1,arg2,th));
}
static int f_PSIMP(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PSIMP(arg1,arg2,th));
}
static int f_PTIMES(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PTIMES(arg1,arg2,th));
}
static int f_PTIMES1(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(PTIMES1(arg1,arg2,th));
}
