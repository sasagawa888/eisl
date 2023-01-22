static int f_REGEXP_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(REGEXP_P(arg1));
}
static int f_REGCOMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(REGCOMP(arg1));
}
