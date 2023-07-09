static int f_FIB(int arglist, int th){
int arg1;
arg1 = Fnth(0,arglist);
return(FIB(arg1,th));
}
void *pletFIB(void *arg);
void *pletFIB(void *arg){struct para *pd = (struct para *) arg;pd->out = Fpcallsubr(Fcar(pd->sym), pd->arg, pd->num);return NULL;}