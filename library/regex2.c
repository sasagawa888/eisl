static int REGEXP_P(int O){
int res;
if(CELLRANGE(O)) Fshelterpush(O);
Fcheckgbc();
res = ({int arg1,arg2,res;
arg1 = O;
Fshelterpush(arg1);
arg2 = Faux(Fmakesym("<REGEXP>"));
Fshelterpush(arg2);
res = Fcallsubr(Fcar(Fmakesym("INSTANCEP")),Fcons(arg1,Flist1(arg2)));
arg2=Fshelterpop();
arg1=Fshelterpop();
;res;});
if(CELLRANGE(O)) O=Fshelterpop();
return(res);}
static int REGCOMP(int RE){
int res;
if(CELLRANGE(RE)) Fshelterpush(RE);
Fcheckgbc();
;
regex_t *preg;
preg = (regex_t *)malloc(sizeof(regex_t));
res = ({int res;int RES = Fapply(Fcar(Fmakesym("CREATE")),Flist1(Faux(Fmakesym("<REGEXP>"))));int C_RES = regcomp(preg, Fgetname(RE), REG_EXTENDED) | INT_FLAG
;res = ({int res;
if(({int res;Fargpush(C_RES);Fargpush(fast_immediate(0));res=fast_numeqp();res;}) != NIL){
res = ({int res;
char *preg_str;
preg_str = fast_sprint_hex_long(preg);
