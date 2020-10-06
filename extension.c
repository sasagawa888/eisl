#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eisl.h"

void initexsubr(void){
    defsubr("RANDOM-REAL",f_random_real);
    defsubr("RANDOM",f_random);
    defsubr("MAPVEC",f_mapvec);
    defsubr("HADAMARD",f_hadamard);
    defsubr("LOGISTIC",f_logistic);
    defsubr("NCONC",f_nconc);
    defsubr("FAST-ADDRESS",f_address);
    defsubr("MACROEXPAND-1",f_macroexpand_1);
    defsubr("BACKTRACE",f_backtrace);
    defsubr("BREAK",f_break);
    #if __linux
    defsubr("EDIT",f_edit);
    #endif
    #if _WIN32
    defsubr("WINEXEC",f_winexec);
    #endif
    defsubr("FREEDLL",f_freedll);
    defsubr("SYSTEM",f_system);
    defsubr("SUBRP",f_subrp);
    defsubr("MACROP",f_macrop);
    defsubr("FIXNUMP",f_fixnump);
    defsubr("LONGNUMP",f_longnump);
    defsubr("BIGNUMP",f_bignump);
    defsubr("READED-ARRAY-LIST",f_readed_array_list);
    defsubr("GET-METHOD",f_get_method);
    defsubr("GET-METHOD-BODY",f_get_method_body);
    defsubr("GET-METHOD-PRIORITY",f_get_method_priority);
    defsubr("IGNORE-TOPLEVEL-CHECK",f_ignore_toplevel_check);
    defsubr("SELF-INTRODUCTION",f_self_introduction);
    defsubr("CLASSP",f_classp);
    defsubr("C-INCLUDE",f_ignore);
    defsubr("C-DEFINE",f_ignore);
    defsubr("C-LANG",f_ignore);
    defsubr("C-OPTION",f_ignore);
}

//Fast Project
int f_classp(int arglist){
	int arg1;
    
    arg1 = car(arglist);
    if(length(arglist) != 1)
    	error(ILLEGAL_ARGS,"classp",arglist);
    
    if(IS_CLASS(arg1))
    	return(T);
    else
    	return(NIL);
}


int f_ignore(int arglist){
    return(T);
}

#if __linux
int f_self_introduction(int arglist){
    return(makesym("LINUX"));
}
#endif

#if _WIN32
int f_self_introduction(int arglist){
    return(makesym("WINDOWS"));
}
#endif


int f_ignore_toplevel_check(int arglist){
	int arg1;
    
    arg1 = car(arglist);
    if(arg1 == T)
        ignore_topchk = 1;
    else
    	ignore_topchk = 0;
    return(T);
}

int f_get_method_priority(int arglist){
	int arg1;
    
    arg1 = car(arglist);
    if(!(IS_METHOD(arg1)))
    	error(ILLEGAL_ARGS,"get-method-priority",arg1);
        
    return(makeint(GET_OPT(arg1)));
}


int f_get_method_body(int arglist){
	int arg1;
    
    arg1 = car(arglist);
    if(!(IS_METHOD(arg1)))
    	error(ILLEGAL_ARGS,"get-method-body",arg1);
        
    return(GET_CAR(arg1));
}

int f_get_method(int arglist){
	int arg1;
    
    arg1 = car(arglist);
    if(!genericp(arg1))
    	error(ILLEGAL_ARGS,"get-method",arg1);
    return(GET_CDR(GET_CAR(arg1)));
}


int f_readed_array_list(int arglist){
    int arg1;
    
    arg1 = car(arglist);
    return(GET_PROP(arg1));
}

#if __linux
int f_system(int arglist){
    int arg1;

	arg1 = car(arglist);
	if(system(GET_NAME(arg1)) == -1)
		error(SYSTEM_ERR, "system", arg1);
	return(T);
}
#endif

#if _WIN32
int f_system(int arglist){
	int arg1;
    
    arg1 = car(arglist);
    system(GET_NAME(arg1));
    return(T);
}

int f_winexec(int arglist){
	int arg1;
    
    arg1 = car(arglist);
    
    WinExec(GET_NAME(arg1), SW_SHOWNORMAL);
    return(T);
}
#endif


#if __linux
int f_freedll(int arglist){
  
    //dlclose(hmod);
    return(T);
}
#endif

#if _WIN32
int f_freedll(int arglist){
    int i;
    for(i=0; i<10; i++)
        FreeLibrary(loadeddll);
    return(T);
}
#endif


int f_macrop(int arglist){
int arg1;

    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "macrop", arglist);
    if(IS_MACRO(GET_CAR(arg1)))
        return(T);
    else
        return(NIL);
}

int f_fixnump(int arglist){
int arg1;
	
    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "fixnump", arglist);
    if(IS_INTEGER(arg1))
    	return(T);
    else
    	return(NIL);
}

int f_longnump(int arglist){
    int arg1;
	
    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "longnump", arglist);
    if(IS_LONGNUM(arg1))
    	return(T);
    else
    	return(NIL);
}

int f_bignump(int arglist){
    int arg1;
	
    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "bignump", arglist);
    if(IS_BIGXNUM(arg1))
    	return(T);
    else
    	return(NIL);
}


int f_subrp(int arglist){
    int arg;
    
    arg = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "subrp", arglist);
    if(IS_SUBR(GET_CAR(arg)))
        return(T);
    else
        return(NIL);
}

int f_random_real(int arglist){
    double d;
    
    if(length(arglist) !=0)
        error(WRONG_ARGS, "random-real", arglist);
    
    d = (double)rand()/RAND_MAX;
    return(makeflt(d));
}

int f_random(int arglist){
    int arg1,n;

    if(length(arglist) !=1)
        error(WRONG_ARGS, "random", arglist);

    arg1 = car(arglist);
    n = GET_INT(arg1);

    return(makeint(rand() % n));
}

int f_mapvec(int arglist){
    int arg1,arg2;
    
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "mapvec", arglist);
    if(!(IS_FUNC(arg1)) && !(IS_SUBR(arg1)))
        error(NOT_FUNC, "mapvec", arg1);
    return(mapvec(arg1,arg2));
}

int f_hadamard(int arglist){
    int x,y,i,j,m,n,m1,n1,res;
    double A[MATSIZE][MATSIZE],B[MATSIZE][MATSIZE],C[MATSIZE][MATSIZE];
    
    x = car(arglist);
    y = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS, "hadamard", arglist);
    if(!(length(array_length(x)) == 2 && length(array_length(y)) == 2))
        error(ILLEGAL_ARGS, "hadamard", list2(x,y));
    if(GET_INT(car(array_length(x))) != GET_INT(car(array_length(y))))
        error(ILLEGAL_ARGS, "hadamard", list2(x,y));
    if(GET_INT(cadr(array_length(x))) != GET_INT(cadr(array_length(y))))
        error(ILLEGAL_ARGS, "hadamard", list2(x,y));
    
    m1 = car(array_length(x));
    n1 = cadr(array_length(x));
    m = GET_INT(m1);
    n = GET_INT(n1);
    if(m>MATSIZE || n>MATSIZE)
        error(OUT_OF_RANGE,"hadamard",NIL);
    if(m*n+FREESIZE > fc){
        shelterpush(x);
        shelterpush(y);
        gbc();
        shelterpop();
        shelterpop();
    }
    res = makearray(list2(m1,n1),UNDEF);
    //#pragma omp parallel for private(i,j)
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            A[i][j] = GET_FLT(matrix_ref(x,n,i,j));
    //#pragma omp parallel for private(i,j)
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            B[i][j] = GET_FLT(matrix_ref(y,n,i,j));
    //#pragma omp parallel for private(i,j)
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            C[i][j] = 0.0;
    //#pragma omp parallel for private(i,j)
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            C[i][j] = A[i][j] * B[i][j];
    
    
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            matrix_set(res,n,i,j,makeflt(C[i][j]));
            
    return(res);
    
}

int f_logistic(int arglist){
    int arg1;
    double u,d;
    
    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS, "logistic", arglist);
    if(!numberp(arg1))
        error(NOT_NUM, "logistic", arg1);
    u = GET_FLT(exact_to_inexact(arg1));
    d = 1/(1+exp(-1*u));
    return(makeflt(d)); 
}   

int f_nconc(int arglist){
    int arg1,arg2;
    
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(length(arglist) != 2)
        error(WRONG_ARGS,"nconc",arglist);
    
    return(nconc(arg1,arg2));
}

int f_address(int arglist){
    int arg1;
    
    arg1 = car(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"address",arglist);
    
    return(makeint(arg1));
}

int f_macroexpand_1(int arglist){
    int arg1,func,args,body,macrofunc,varlist,save,res;
    
    arg1 = caar(arglist);
    args = cdar(arglist);
    if(length(arglist) != 1)
        error(WRONG_ARGS,"macroexpand-1",arglist);
    if(!symbolp(arg1))
        error(NOT_SYM,"macroexpand-1",arg1);
    
    
    func = GET_CAR(arg1);
    save = ep;
    res = NIL;
    macrofunc = GET_CAR(func);
    varlist = car(GET_CAR(macrofunc));
    if(GET_OPT(func) >= 0){
        if(length(args) != GET_OPT(func))
            error(WRONG_ARGS,"macroexpand-1",args);
    }
    else{
        if(length(args) < (-1 * GET_OPT(func) - 2))
            error(WRONG_ARGS,"macroexpand-1",args);
    }    
    body = cdr(GET_CAR(macrofunc));
    bindarg(varlist,args);
    while(!(IS_NIL(body))){
        res = eval(car(body));
        body = cdr(body);
    }
    unbind();
    ep = save;
    return(res);
}

int f_backtrace(int arglist){
    int arg1,i,l;
    
    if((l=length(arglist)) != 0 && l != 1)
        error(WRONG_ARGS,"backtrace",arglist);
    
    arg1 = car(arglist);
    
    if(l == 0){ 
        for(i=0;i<BACKSIZE;i++){
            print(backtrace[i]);
            printf("\n");
        }
    }
    else if(arg1 == T)
        back_flag = 1;
    else if(arg1 == NIL)
        back_flag = 0;
    
    return(T);
}

int f_break(int arglist){
    printf("break\n");
    debugger();
    longjmp(buf,1); 
    return(T);
}

/*
//---------for CUBLAS-------------------

#define IDX2C(i,j,ld) (((j)*(ld))+(i))

int f_set_matmat(int arglist){
    int i,j,k,k1,m,m1,n,n1,arg1,arg2,arg3;
    cublasStatus stat;
    float* devPtrA;
    float* devPtrB;
    float* devPtrC;
    float* a = 0;
    float* b = 0;
    float* c = 0;
  
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    m = GET_INT(car(GET_CDR(arg2)));
    k = GET_INT(cadr(GET_CDR(arg2)));
    k1 = GET_INT(car(GET_CDR(arg3)));
    n = GET_INT(cadr(GET_CDR(arg3)));
    m1 = GET_INT(car(GET_CDR(arg1)));
    n1 = GET_INT(cadr(GET_CDR(arg1)));
    if(m != m1 || k != k1 || n != n1)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    
    // Memory Allocation
    a = (float *)malloc (m * k * sizeof (*a));
    if (!a)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    b = (float *)malloc (m * k * sizeof (*b));
    if (!b)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    c = (float *)malloc (m * k * sizeof (*c));
    if (!c)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
        
    // Initalize
    for(j=0;j<k;j++)
        for(i=0;i<m;i++)
            a[IDX2C(i,j,m)] = GET_FLT(vector_ref(arg2,i*k+j));
    
    for (j=0;j<n;j++)
        for (i=0;i<k;i++)
            b[IDX2C(i,j,k)] = GET_FLT(vector_ref(arg3,i*n+j));
        
    for(j=0;j<n;j++)
        for(i=0;i<m;i++)
            c[IDX2C(i,j,m)] = 0.0;
            
    // Initialize CUBLAS
    cublasInit();

    stat = cublasAlloc (m*k, sizeof(*a), (void**)&devPtrA);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    stat = cublasAlloc (k*n, sizeof(*b), (void**)&devPtrB);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL); 
    stat = cublasAlloc (m*n, sizeof(*c), (void**)&devPtrC);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL); 
  

    stat = cublasSetMatrix (m, k, sizeof(*a), a, m, devPtrA, m);
    if(stat != CUBLAS_STATUS_SUCCESS)
    error(ILLEGAL_ARGS,"set-matmat",NIL);
    stat = cublasSetMatrix (k, n, sizeof(*b), b, k, devPtrB, k);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL);
    stat = cublasSetMatrix (m, n, sizeof(*c), c, m, devPtrC, m);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matmat",NIL); 

  
    //Sgemm
    cublasSgemm('N', 'N', m, n, k, 1.0, devPtrA, m, devPtrB, k, 0.0, devPtrC, m);

    stat = cublasGetMatrix (m, n, sizeof(*c), devPtrC, m, c, m);
    if(stat != CUBLAS_STATUS_SUCCESS){
        cublasFree(devPtrA);
        cublasFree(devPtrB);
        cublasFree(devPtrC);
        cublasShutdown();
        error(ILLEGAL_ARGS,"set-matmat",NIL); 
    }

    // Shutdown CUBLAS
    cublasFree(devPtrA);
    cublasFree(devPtrB);
    cublasFree(devPtrC);
    cublasShutdown();

    // Set matrix After sgemm
    for(j=0;j<n;j++)
        for (i=0;i<m;i++){
            SET_TAG(vector_ref(arg1,i*n+j),FLTN);
            SET_FLT(vector_ref(arg1,i*n+j),c[IDX2C(i,j,m)]);
        }
  
    free(a);
    free(b);
    free(c);
    return(NIL);
}

int f_set_matvec(int arglist){
    int i,j,k,k1,m,m1,n,n1,arg1,arg2,arg3;
    cublasStatus stat;
    float* devPtrA;
    float* devPtrB;
    float* devPtrC;
    float* a = 0;
    float* b = 0;
    float* c = 0;
  
    arg1 = car(arglist);
    arg2 = cadr(arglist);
    arg3 = caddr(arglist);
    m = GET_INT(car(GET_CDR(arg2)));
    n = GET_INT(cadr(GET_CDR(arg2)));
    k = GET_CDR(arg3);
    k1 = GET_CDR(arg1);
    if(n != k || m != k1)
        error(ILLEGAL_ARGS,"set-matvec",NIL);
    
    // Memory Allocation
    a = (float *)malloc (m * n * sizeof (*a));
    if (!a)
        error(ILLEGAL_ARGS,"set-matvec",NIL);
    b = (float *)malloc (k * sizeof (*b));
    if (!b)
        error(ILLEGAL_ARGS,"set-matvec",NIL);
    c = (float *)malloc (k1 * sizeof (*c));
    if (!c)
        error(ILLEGAL_ARGS,"set-matvec",NIL);
        
    // Initalize
    for (j=0;j<n;j++)
        for (i=0;i<m;i++)
            a[IDX2C(i,j,m)] = GET_FLT(vector_ref(arg2,i*n+j));
    
    for(i=0;i<k;i++)
        b[i] = GET_FLT(vector_ref(arg3,i));
        
    for(i=0;i<k1;i++)
        c[i] = 0.0;
           
    // Initialize CUBLAS
    cublasInit();

    stat = cublasAlloc (m*n, sizeof(*a), (void**)&devPtrA);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matvec",NIL);
    stat = cublasAlloc (k, sizeof(*b), (void**)&devPtrB);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matvec",NIL); 
    stat = cublasAlloc (k1, sizeof(*c), (void**)&devPtrC);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matvec",NIL); 
  

    stat = cublasSetMatrix (m, n, sizeof(*a), a, m, devPtrA, m);
    if(stat != CUBLAS_STATUS_SUCCESS) 
        error(ILLEGAL_ARGS,"set-matvec",NIL);
    stat = cublasSetVector (k, sizeof(*b), b, 1, devPtrB, 1);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matvec",NIL);
    stat = cublasSetVector (k1, sizeof(*c), c, 1, devPtrC, 1);
    if(stat != CUBLAS_STATUS_SUCCESS)
        error(ILLEGAL_ARGS,"set-matvec",NIL); 

  
    //Sgemv
    cublasSgemv('N', m, n, 1.0, devPtrA, m, devPtrB, 1, 0.0, devPtrC, 1);

    stat = cublasGetVector(k1, sizeof(*c), devPtrC, 1, c, 1);
    if(stat != CUBLAS_STATUS_SUCCESS){
        cublasFree(devPtrA);
        cublasFree(devPtrB);
        cublasFree(devPtrC);
        cublasShutdown();
        error(ILLEGAL_ARGS,"set-matvec",NIL); 
    }

    // Shutdown CUBLAS
    cublasFree(devPtrA);
    cublasFree(devPtrB);
    cublasFree(devPtrC);
    cublasShutdown();

    // Set vector After sgemv
    for (i=0;i<k1;i++){
        SET_TAG(vector_ref(arg1,i),FLTN);
        SET_FLT(vector_ref(arg1,i),c[i]);
    }
  
    free(a);
    free(b);
    free(c);
    return(NIL);
}


//for deep larning forward process
//W 3 dimension
//U 2 dimension

//U(l+1) = W(l)*U(l) 

int f_forward(int arglist){
    int d1,d2,i,j,k,l,m,n,arg1,arg2,arg3;
    double r;
    cublasStatus stat;
    float* devPtrA;
    float* devPtrB;
    float* devPtrC;
    float* a = 0;
    float* b = 0;
    float* c = 0;
  
    arg1 = car(arglist); //W
    arg2 = cadr(arglist); //U
    arg3 = caddr(arglist); //f
    d1 = GET_CDR(arg1); //dimensions
    d2 = GET_CDR(arg2); //dimensions
    if(length(d1) != 3)
        error(ILLEGAL_ARGS,"forward",d1);
    if(length(d2) != 2)
        error(ILLEGAL_ARGS,"forward",d2);
    if(GET_INT(cadr(d1)) != GET_INT(car(d2))) // W(m,n,l) U(n,l+1) check n
        error(ILLEGAL_ARGS,"forward",list2(d1,d2));
    if(GET_INT(caddr(d1))+1 != GET_INT(cadr(d2)))// W(m,n,l) U(n,l+1) check l
        error(ILLEGAL_ARGS,"forward",list2(d1,d2));
    if(!(IS_SUBR(arg3)))
        error(ILLEGAL_ARGS,"forward",arg3);
    
    m = GET_INT(car(d1));
    n = GET_INT(cadr(d1));
    l = GET_INT(caddr(d1));
    
    // Memory Allocation
    a = (float *)malloc (m * n * sizeof (*a));
    if (!a)
        error(ILLEGAL_ARGS,"forward",NIL);
    b = (float *)malloc (n * sizeof (*b));
    if (!b)
        error(ILLEGAL_ARGS,"forward",NIL);
    c = (float *)malloc (n * sizeof (*c));
    if (!c)
        error(ILLEGAL_ARGS,"forward",NIL);
    
    k = 0;
    while(k<l){ 
        // Initalize
        for (j=0;j<n;j++)
            for (i=0;i<m;i++){
                a[IDX2C(i,j,m)] = GET_FLT(vector_ref(arg1,i*n+j+k*m*n));
            }
    
        for(i=0;i<n;i++){
            b[i] = GET_FLT(vector_ref(arg2,i*(l+1)+k));
        }
        for(i=0;i<n;i++)
            c[i] = 0.0;
          
        // Initialize CUBLAS
        cublasInit();

        stat = cublasAlloc (m*n, sizeof(*a), (void**)&devPtrA);
        if(stat != CUBLAS_STATUS_SUCCESS)
            error(ILLEGAL_ARGS,"forward",NIL);
        stat = cublasAlloc (n, sizeof(*b), (void**)&devPtrB);
        if(stat != CUBLAS_STATUS_SUCCESS)
            error(ILLEGAL_ARGS,"forward",NIL); 
        stat = cublasAlloc (n, sizeof(*c), (void**)&devPtrC);
        if(stat != CUBLAS_STATUS_SUCCESS)
            error(ILLEGAL_ARGS,"forward",NIL); 
  

        stat = cublasSetMatrix (m, n, sizeof(*a), a, m, devPtrA, m);
        if(stat != CUBLAS_STATUS_SUCCESS) 
            error(ILLEGAL_ARGS,"forward",NIL);
        stat = cublasSetVector (n, sizeof(*b), b, 1, devPtrB, 1);
        if(stat != CUBLAS_STATUS_SUCCESS)
            error(ILLEGAL_ARGS,"forward",NIL);
        stat = cublasSetVector (n, sizeof(*c), c, 1, devPtrC, 1);
        if(stat != CUBLAS_STATUS_SUCCESS)
            error(ILLEGAL_ARGS,"forward",NIL); 

  
        //Sgemv
        cublasSgemv('N', m, n, 1.0, devPtrA, m, devPtrB, 1, 0.0, devPtrC, 1);

        stat = cublasGetVector(n, sizeof(*c), devPtrC, 1, c, 1);
        if(stat != CUBLAS_STATUS_SUCCESS){
            cublasFree(devPtrA);
            cublasFree(devPtrB);
            cublasFree(devPtrC);
            cublasShutdown();
            error(ILLEGAL_ARGS,"forward",NIL); 
        }
        // Set vector After sgemv
        for (i=0;i<n;i++){
            r = (GET_SUBR(arg3))(list1(makeflt(c[i])));
            vector_set(arg2,i*(l+1)+k+1,r);
        }
        k++;
    }
    
    // Shutdown CUBLAS
    cublasFree(devPtrA);
    cublasFree(devPtrB);
    cublasFree(devPtrC);
    cublasShutdown();

    free(a);
    free(b);
    free(c);
    return(NIL);
}

*/




