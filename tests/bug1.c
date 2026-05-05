static int f_TEST_LAMBDA_NESTED1(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(TEST_LAMBDA_NESTED1(arg1,th));
}
static int f_dotslashtestsslashbug0(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(dotslashtestsslashbug0(arg1,th));
}
static int f_dotslashtestsslashbug1(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(dotslashtestsslashbug1(arg1,th));
}
static int f_DIFFERENCE(int arglist, int th){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(DIFFERENCE(arg1,arg2,th));
}
