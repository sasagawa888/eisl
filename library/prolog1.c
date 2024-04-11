static int f_PROLOG(int arglist, int th){
return(PROLOG(th) );
}
static int f_libraryslashprolog0(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(libraryslashprolog0(arg1,th));
}
