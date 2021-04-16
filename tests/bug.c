#include "fast.h"
#include <stdio.h>
#include <syslog.h>
static int f_FOO(int arglist);static int FOO(int X);
static int f_FOO(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(FOO(arg1));
}
static int FOO(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
Fcheckgbc();
printf("%d",X);
if(CELLRANGE(X)) X=Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("FOO" , f_FOO);
}void init_declare(void){
Fsetcatchsymbols(NIL);;;;;;}