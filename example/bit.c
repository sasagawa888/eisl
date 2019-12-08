#include "fast.h"
#include <stdio.h>
int f_ASH(int arglist);int ASH(int N,int M);
int f_ASH(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ASH(fast_convert(arg1),fast_convert(arg2))));
}
