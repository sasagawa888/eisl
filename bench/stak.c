#include "fast.h"
int f_STAK(int arglist);int STAK(int ST_X,int ST_Y,int ST_Z);
int f_STAK_AUX(int arglist);int STAK_AUX();
int f_STAK(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(STAK(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_STAK_AUX(int arglist){
return(fast_inverse(STAK_AUX() ));
}
int STAK(int ST_X,int ST_Y,int ST_Z){
int res;
if(CELLRANGE(ST_X)) Fshelterpush(ST_X);
if(CELLRANGE(ST_Y)) Fshelterpush(ST_Y);
if(CELLRANGE(ST_Z)) Fshelterpush(ST_Z);
if(Ffreecell() < 900) Fgbc();
Fsetdynamic(Fmakesym("STAK-X"),fast_inverse(ST_X));
Fsetdynamic(Fmakesym("STAK-Y"),fast_inverse(ST_Y));
Fsetdynamic(Fmakesym("STAK-Z"),fast_inverse(ST_Z));
res = STAK_AUX();
if(CELLRANGE(ST_Z)) Fshelterpop();
if(CELLRANGE(ST_Y)) Fshelterpop();
if(CELLRANGE(ST_X)) Fshelterpop();
return(res);}
int STAK_AUX(){
int res;
STAK_AUXloop:
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_eqgreaterp(fast_convert(fast_convert(Ffinddyn(Fmakesym("STAK-Y")))),fast_convert(fast_convert(Ffinddyn(Fmakesym("STAK-X"))))) != NIL){
res = fast_convert(Ffinddyn(Fmakesym("STAK-Z")));}
else{
res = ({int res,val,save,dynpt;
 save=Fgetdynpt();
dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(({int res,val,save,dynpt;
 save=Fgetdynpt();
dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_minus(fast_convert(fast_convert(Ffinddyn(Fmakesym("STAK-X")))),fast_convert(fast_immediate(1))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-X"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_convert(Ffinddyn(Fmakesym("STAK-Y"))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Y"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_convert(Ffinddyn(Fmakesym("STAK-Z"))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Z"),val);res = STAK_AUX();res;}));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-X"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(({int res,val,save,dynpt;
 save=Fgetdynpt();
dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_minus(fast_convert(fast_convert(Ffinddyn(Fmakesym("STAK-Y")))),fast_convert(fast_immediate(1))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-X"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_convert(Ffinddyn(Fmakesym("STAK-Z"))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Y"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_convert(Ffinddyn(Fmakesym("STAK-X"))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Z"),val);res = STAK_AUX();res;}));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Y"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(({int res,val,save,dynpt;
 save=Fgetdynpt();
dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_minus(fast_convert(fast_convert(Ffinddyn(Fmakesym("STAK-Z")))),fast_convert(fast_immediate(1))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-X"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_convert(Ffinddyn(Fmakesym("STAK-X"))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Y"),val);dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);
val=fast_inverse(fast_convert(Ffinddyn(Fmakesym("STAK-Y"))));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Z"),val);res = STAK_AUX();res;}));Fsetdynpt(dynpt);Fshelterpop();Fadddynenv(Fmakesym("STAK-Z"),val);{
goto STAK_AUXloop;};res;});}res;})
;
return(res);}
void init_tfunctions(void){
(deftfunc)("STAK" , f_STAK);
(deftfunc)("STAK-AUX" , f_STAK_AUX);
}void init_declare(void){
Fsetcatchsymbols(NIL);Fsetdynenv(Fmakesym("STAK-X"),NIL);Fsetdynenv(Fmakesym("STAK-Y"),NIL);Fsetdynenv(Fmakesym("STAK-Z"),NIL);}