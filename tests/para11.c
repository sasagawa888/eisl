static int f_PFIB(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(PFIB(arg1,th));
}
static int f_FIB(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(FIB(arg1,th));
}
static int f_PTARAI(int arglist, int th){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(PTARAI(arg1,arg2,arg3,th));
}
static int f_TARAI(int arglist, int th){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(TARAI(arg1,arg2,arg3,th));
}
static int f_PCOUNT(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(PCOUNT(arg1,th));
}
static int f_COUNT(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(COUNT(arg1,th));
}
static int f_COUNT1(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(COUNT1(arg1,arg2,th));
}
static int f_PRIMEPstar(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(PRIMEPstar(arg1,th));
}
static int f_NEAR_ODD(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(NEAR_ODD(arg1,th));
}
static int f_COPRIMEP(int arglist, int th){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(COPRIMEP(arg1,arg2,arg3,th));
}
static int f_PRIMEP(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(PRIMEP(arg1,th));
}
