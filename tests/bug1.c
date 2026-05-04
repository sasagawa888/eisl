static int f_TEST_BOUNDARY1(int arglist, int th){
return(Fmakeint(TEST_BOUNDARY1(th) ));
}
static int f_TEST_BOUNDARY2(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(TEST_BOUNDARY2(arg1,th));
}
static int f_FOO(int arglist, int th){
return(FOO(th) );
}
