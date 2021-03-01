#include <stdio.h>
#include <setjmp.h>

#define HEAPSIZE    20000000
#define CELLSIZE    20000000
#define WORK1        6000000
#define WORK2       13000000
#define FREESIZE    100
#define STACKSIZE   30000
#define SYMSIZE     32
#define BUFSIZE     256
#define STRSIZE     5120
#define CHARSIZE    2   //ascii char. add \0 to tail
#define MATSIZE     256
#define NIL         0
#define T           2
#define UNDEF       4
#define FEND        6
#define HASHTBSIZE  107
#define BIGNUM_BASE 1000000000
#define SMALL_INT_MAX       1000000000
#define SMALL_INT_MIN       -1000000000
#define INT_FLAG	1073741824 //#b1000000000000000000000000000000
#define INT_MASK	1073741823 //#b0111111111111111111111111111111
#define INT_PSQRT	1073773446 //INT_FLAG+sqrt(999999999)
#define INT_MSQRT	-31622     //- sqrt(999999999)
#define CTRLSTK     100
#define CELLRANGE(x)	(x < INT_FLAG && x > 0)

//option
#define FAST_CONSTN      1
#define FAST_IMMUTABLE   2
#define FAST_SYSTEM      3 //class of provided by system
#define FAST_USER        4 //class of user' definition
#define FAST_GLOBAL      5 //global variable
#define FAST_CONTINUABLE 6 //continuable condition
#define FAST_NOTCONT     7 //no continuable condition


typedef int (*fn0)();
typedef int (*fn1)(int);
typedef int (*fn2)(int , int);
typedef int (*fn3)(char*);
typedef long long int (*fn4)(int);
typedef int (*fn5)(int , int , int);
typedef char* (*fn6)(int);
typedef double (*fn7)(int);
typedef int (*fn8)(double);
typedef void (*tfunc)(char*, int(*func)(int));

tfunc deftfunc;

fn0 f0[100];
fn1 f1[100];
fn2 f2[100];
fn3 f3[100];
fn4 f4[100];
fn5 f5[100];
fn6 f6[100];
fn7 f7[100];
fn8 f8[100];


void init0(int n, tfunc x){
    f0[n] = (fn0)x;
}

void init1(int n, tfunc x){
    f1[n] = (fn1)x;
}

void init2(int n, tfunc x){
    f2[n] = (fn2)x;
}

void init3(int n, char* x){
    f3[n] = (fn3)x;
}

void init4(int n, tfunc x){
	f4[n] = (fn4)x;
}

void init5(int n, tfunc x){
    f5[n] = (fn5)x;
}

void init6(int n, tfunc x){
    f6[n] = (fn6)x;
}

void init7(int n, tfunc x){
    f7[n] = (fn7)x;
}

void init8(int n, tfunc x){
    f8[n] = (fn8)x;
}

void init_deftfunc(tfunc x){
    deftfunc = (tfunc)x;
}

jmp_buf catch_buf[10];
int catch_arg; //receive argument of catch
int block_arg; //receive argument of block

#define Fcheckgbc() (f0[0])()
#define Fgbc()	(f0[1])()
#define Ffreshcell() (f0[2])()
#define Ffreecell() (f0[3])()
#define Fgbcsw() (f0[4])()
#define Fgetwp() (f0[5])()
#define Fargpop() (f0[9])()
#define Fshelterpop() (f0[10])()
#define Fpop() (f0[11])()
#define Fgetdynpt() (f0[12])()

#define Fcar(x) (f1[0])(x)
#define Fcdr(x) (f1[1])(x)
#define Fcadr(x) (f1[2])(x)
#define Fcaddr(x) (f1[3])(x)
#define Fcaar(x) (f1[4])(x)
#define Fcadar(x) (f1[5])(x)
#define Flist1(x) (f1[6])(x)
#define Feval(x) (f1[7])(x)
#define Faux(x) (f1[8])(x)
#define Flength(x) (f1[9])(x)
#define Fsubrp(x) (f1[10])(x)
#define Ffsubrp(x) (f1[11])(x)
#define Ffunctionp(x) (f1[12])(x)
#define Fmacrop(x) (f1[13])(x)
#define Fintegerp(x) (f1[14])(x)
#define Flongnump(x) (f1[15])(x)
#define Fbignump(x) (f1[16])(x)
#define Fgetint(x) (f1[20])(x)
#define Fmakeint(x) (f1[21])(x)
#define Fmakeintlong(x) (f1[22])(x)
#define Fvector(x) (f1[23])(x)
#define fast_car(x) (f1[24])(x)
#define fast_cdr(x) (f1[25])(x)
#define Ffindenv(x) (f1[30])(x)
#define Ffinddyn(x) (f1[31])(x)
#define Fargpush(x) (f1[39])(x)
#define Fshelterpush(x) (f1[40])(x)
#define Fpush(x) (f1[41])(x)
#define Fgetopt(x) (f1[42])(x)
#define Fgetprop(x) (f1[43])(x)
#define Fsetdynpt(x) (f1[44])(x)
#define Fsetcatchsymbols(x) (f1[45])(x)
#define Feval(x) (f1[46])(x)

#define Fcons(x,y) (f2[0])(x,y)
#define Fnth(x,y) (f2[1])(x,y)
#define Fset_car(x,y) (f2[2])(x,y)
#define Fset_cdr(x,y) (f2[3])(x,y)
#define Fset_aux(x,y) (f2[4])(x,y)
#define Fset_opt(x,y) (f2[5])(x,y)
#define Fcallsubr(x,y) (f2[6])(x,y)
#define Flist2(x,y) (f2[7])(x,y)
#define Fnthcdr(x,y) (f2[8])(x,y)
#define Fapply(x,y) (f2[9])(x,y)
#define Fplus(x,y) (f2[10])(x,y)
#define Fminus(x,y) (f2[11])(x,y)
#define Fmult(x,y) (f2[12])(x,y)
#define Fquotient(x,y) (f2[13])(x,y)
#define Fremainder(x,y) (f2[14])(x,y)
#define Fdivide(x,y) (f2[15])(x,y)
#define Feqp(x,y) (f2[16])(x,y)
#define Feqlp(x,y) (f2[17])(x,y)
#define Fnumeqp(x,y) (f2[18])(x,y)
#define Fsmallerp(x,y) (f2[19])(x,y)
#define Feqsmallerp(x,y) (f2[20])(x,y)
#define Fgreaterp(x,y) (f2[21])(x,y)
#define Feqgreaterp(x,y) (f2[22])(x,y)
#define Fmember(x,y) (f2[23])(x,y)
#define Fconvert(x,y) (f2[30])(x,y)
#define Farray(x,y) (f2[31])(x,y)
#define Fsetdynenv(x,y) (f2[32])(x,y)
#define Fadddynenv(x,y) (f2[33])(x,y)
#define Fsetdynamic(x,y) (f2[34])(x,y)
#define Fsetprop(x,y) (f2[35])(x,y)
#define Fadaptp(x,y) (f2[36])(x,y)

#define Fmakestr(x) (f3[0])(x)
#define Fmakesym(x) (f3[1])(x)
#define Fmakechar(x) (f3[2])(x)
#define Fmakestrflt(x) (f3[3])(x)
#define Fmakebig(x) (f3[4])(x)

#define Fgetlong(x) (f4[0])(x)

#define Fstringset(x,y,z) (f5[0])(x,y,z)
#define Farrayset(x,y,z) (f5[1])(x,y,z)
#define Fmember1(x,y,z) (f5[2])(x,y,z)

#define Fgetname(x) (f6[0])(x)

#define Fgetflt(x) (f7[0])(x)

#define Fmakedoubleflt(x) (f8[0])(x)

int fast_immediate(int x){
    if(x >= 0)
        return(x | INT_FLAG);
    else
        return(x);
}

int fast_convert(int x){
	int res,n;

    if(x < 0 || x >= INT_FLAG)
    	return(x);
	else if(Fintegerp(x)){
        n = Fgetint(x);
        if(n >= 0)
            res = n | INT_FLAG;
        else
            res = n;
    }
    else
    	res = x;

    return(res);
}

int fast_inverse(int x){
	int res;

    if(x >= INT_FLAG)
    	res = Fmakeint(x & INT_MASK);
    else if(x < 0)
    	res = Fmakeint(x);
    else
    	res = x;

    return(res);
}


int fast_numeqp(){
    int x,y;

    y = Fargpop();
    x = Fargpop();
    if(x >= INT_FLAG && y >= INT_FLAG)
        if(x == y)
            return(T);
        else
            return(0);
    else if(x < 0 && y < 0)
        if(x == y)
            return(T);
        else
            return(0);
    else if(x >= INT_FLAG && y < 0)
        return(0);
    else if(x < 0 && y >= INT_FLAG)
        return(0);
    else
        return(Fnumeqp(fast_inverse(x),fast_inverse(y)));
}

int fast_smallerp(){
    int x,y;

    y = Fargpop();
    x = Fargpop();
    if(x >= INT_FLAG && y >= INT_FLAG)
        if(x < y)
            return(T);
        else
            return(0);
    else if(x < 0 && y < 0)
        if(x < y)
            return(T);
        else
            return(0);
    else if(x >= INT_FLAG && y < 0)
        return(0);
    else if(x < 0 && y >= INT_FLAG)
        return(T);
    else
        return(Fsmallerp(fast_inverse(x),fast_inverse(y)));
}

int fast_eqsmallerp(){
    int x,y;

    y = Fargpop();
    x = Fargpop();
    if(x >= INT_FLAG && y >= INT_FLAG)
        if(x <= y)
            return(T);
        else
            return(0);
    else if(x < 0 && y < 0)
        if(x <= y)
            return(T);
        else
            return(0);
    else if(x >= INT_FLAG && y < 0)
        return(0);
    else if(x < 0 && y >= INT_FLAG)
        return(T);
    else
        return(Feqsmallerp(fast_inverse(x),fast_inverse(y)));
}


int fast_greaterp(){
    int x,y;

    y = Fargpop();
    x = Fargpop();
    Fargpush(y);
    Fargpush(x);
    return(fast_smallerp());
}

int fast_eqgreaterp(){
    int x,y;

    y = Fargpop();
    x = Fargpop();
    Fargpush(y);
    Fargpush(x);
    return(fast_eqsmallerp());
}

int fast_plus(){
    int x,y,intx,inty,res;

    y = Fargpop();
    x = Fargpop();
    if(x >= INT_FLAG && y >= INT_FLAG){
        intx = (x & INT_MASK);
        inty = (y & INT_MASK);
        res = intx + inty;
        if(res >= SMALL_INT_MAX)
        	return(Fmakeintlong(res));
        else
            return(res | INT_FLAG);
    }
    else if(x >= INT_FLAG && y < 0){
        intx = (x & INT_MASK);
        inty = y;
        res = intx + inty;
        if(res>=0)
            res = res | INT_FLAG;

        return(res);
    }
    else if(x < 0 && y >= INT_FLAG){
        intx = x;
        inty = (y & INT_MASK);
        res = intx + inty;
        if(res>=0)
            res = res | INT_FLAG;

        return(res);
    }
    else
        return(fast_convert(Fplus(fast_inverse(x),fast_inverse(y))));
}

int fast_minus(){
    int x,y,intx,inty,res;

    y = Fargpop();
    x = Fargpop();
    if(x >= INT_FLAG && y >= INT_FLAG){
        intx = (x & INT_MASK);
        inty = (y & INT_MASK);
        res = intx - inty;
        if(res>=0)
            res = res | INT_FLAG;

        return(res);
    }
    else if(x >= INT_FLAG && y < 0){
        intx = (x & INT_MASK);
        inty = y;
        res = intx - inty;
        if(res>=0)
            res = res | INT_FLAG;

        return(res);
    }
    else if(x < 0 && y >= INT_FLAG){
        intx = x;
        inty = (y & INT_MASK);
        res = intx - inty;
        if(res>=0)
            return(res | INT_FLAG);
		else if(res <= SMALL_INT_MAX)
        	return(Fmakeintlong(res));
		else
            return(res);
    }
    else
        return(fast_convert(Fminus(fast_inverse(x),fast_inverse(y))));
}

int fast_mult(){
    int x,y,intx,inty,res;

    y = Fargpop();
    x = Fargpop();
    if(x >= INT_FLAG && x <= INT_PSQRT &&
       y >= INT_FLAG && y <= INT_PSQRT){
        intx = (x & INT_MASK);
        inty = (y & INT_MASK);
        res = intx * inty;
        return(res | INT_FLAG);
    }
    else if(x >= INT_FLAG && x <= INT_PSQRT &&
            y < 0 && y >= INT_MSQRT){
        intx = (x & INT_MASK);
        inty = y;
        res = intx * inty;
        return(res);
    }
    else if(x < 0 && x >= INT_MSQRT &&
            y >= INT_FLAG && y <= INT_PSQRT){
        intx = x;
        inty = (y & INT_MASK);
        res = intx * inty;
        return(res);
    }
    else
        return(fast_convert(Fmult(fast_inverse(x),fast_inverse(y))));
}



int fast_mod(){
    int x,y,intx,inty,res;
    long long int longx,longy;

    y = Fargpop();
    x = Fargpop();
    if(x >= INT_FLAG && y >= INT_FLAG){
        intx = (x & INT_MASK);
        inty = (y & INT_MASK);
        res = intx % inty;
        res = res | INT_FLAG;
        return(res);
    }
    else if(x >= INT_FLAG && y < 0){
        intx = (x & INT_MASK);
        inty = y;
    	res = -1 * (intx % inty);
        if(res >= 0)
        	res = res | INT_FLAG;
        return(res);
    }
    else if(x < 0 && y >= INT_FLAG){
        intx = x;
        inty = (y & INT_MASK);
    	res = -1*(intx % inty);
        if(res>=0)
            res = res | INT_FLAG;
        return(res);
    }
    else if(x < 0 && y < 0){
        res = -1*((-1*x) % (-1*y));
        return(res);
    }
    else if((x >= 0 && x <INT_FLAG && Flongnump(x)) && (y >= INT_FLAG || y < 0)){
        longx = Fgetlong(x);
        if(y >= INT_FLAG)
    	    inty = (y & INT_MASK);
        longy = (long long int)inty;
        res = (int)(longx % longy);
        if(res >= 0)
        	res = res | INT_FLAG;
        return(res);
    }
    else
    	return(fast_convert(
                 Fcallsubr(Fcar(Fmakesym("MOD")),
                           Flist2(fast_inverse(x),fast_inverse(y)))));
}

int fast_not(int x){
	if(x == NIL)
    	return(T);
    else
    	return(NIL);
}

int fast_eq(){
    int x,y;

    y = Fargpop();
    x = Fargpop();
    if(x == y)
        return(T);
    else
        return(NIL);
}

int fast_setnth(int x, int n, int y){
    while(n > 0){
        x = Fcdr(x);
        n--;
    }
    Fset_car(x,y);
    return(y);
}
//---------------OPenGL-----------------
int displayfunc;

void display_callback(void){
    Feval(displayfunc);
}

int keyboardfunc;

void keyboard_callback(unsigned char key, int x, int y){
    Fset_cdr(Fmakesym("gl::key"),Fmakeint((int)key));
    Fset_cdr(Fmakesym("gl::x"),Fmakeint(x));
    Fset_cdr(Fmakesym("gl::y"),Fmakeint(y));
    Feval(keyboardfunc);
}

int mousefunc;

void mouse_callback(int button, int state, int x, int y) {
    Fset_cdr(Fmakesym("gl::button"),Fmakeint(button));
    Fset_cdr(Fmakesym("gl::state"),Fmakeint(state));
    Fset_cdr(Fmakesym("gl::x"),Fmakeint(x));
    Fset_cdr(Fmakesym("gl::y"),Fmakeint(y));
    Feval(mousefunc);
}
