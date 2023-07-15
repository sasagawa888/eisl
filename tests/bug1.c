static int f_PFIB(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(Fmakeint(PFIB(Fgetint(arg1),0)));
}
void *pcallPFIB(void *arg);
void *pcallPFIB(void *arg){struct para *pd = (struct para *) arg;pd->out = Fpcallsubr(Fcar(pd->sym),pd->arg, pd->num);return NULL;}