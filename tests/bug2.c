static int PFIB(int N, int th){
int res;
;
res = ({int res=NIL;
if(N==0){
res = 0;}
else if(N==1){
res = 1;}
else{
res = ({pthread_t t[PARASIZE]; struct para d[PARASIZE];if(th != 0) return(PFIB(N-1,th)+PFIB(N-2,th));
int TEMP0,TEMP1;d[0].sym = Fmakesym("PFIB");
d[0].arg = Flist1(N-1);
d[0].num = 1;
pthread_create(&t[0], NULL, pcallPFIB, &d[0]);
d[1].sym = Fmakesym("PFIB");
d[1].arg = Flist1(N-2);
d[1].num = 2;
pthread_create(&t[1], NULL, pcallPFIB, &d[1]);
pthread_join(t[0], NULL);
pthread_join(t[1], NULL);
TEMP0 = d[0].out;TEMP1 = d[1].out;
res = TEMP0+TEMP1;
res;});}
;res;});
return(res);}
