# Spec

- (plet form body)  

```
form   ((var1 sexp1)(var2 sexp2)...)
```
- (pcall fun arg ...)

# Summary
 I am attempting to introduce parallel computing to Easy-ISLisp. First, I added parallel syntax to the interpreter and achieved some results by running it with multiple threads. I am documenting these findings for future reference.

# Thread Safety
I used the C programming language library, Pthread. I need to make key parts like eval and apply thread-safe. Each thread should have its own stack and local environment. Additionally, access to cells must be protected to prevent conflicts.

# Parallel Syntax
I adopted a syntax called "plet." I borrowed the idea from a parallel library in Common Lisp. The following example is code that uses plet to calculate Fibonacci numbers.

```
;;; test paralell

(defun fib (n)
    (plet ((a (fib1 (- n 1)))
           (b (fib1 (- n 2)))) (+ a b)))

(defun fib1 (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib1 (- n 1)) (fib1 (- n 2))))))

```


# Data Structures
The local environment is implemented as an association list. Previously, it was stored in a variable called ep, holding the head address. To manage ep for each thread, it has been changed to an array.

ep[0] for the main thread
ep[1] for sub-thread 1
ep[2] for sub-thread 2
ep[3] for sub-thread 3

Similarly, the stack pointer sp is also an array. The stack itself is a multidimensional array.

stack[STCKSIZE][PARASIZE]

The push and pop operations are defined as follows:

```
/* for stack to store ep(environment) */
int push(int pt, int th)
{
    if (sp[th] >= STACKSIZE)
	error(STACK_OVERF, "push", NIL);

    stack[sp[th]++][th] = pt;
    return (T);
}

int pop(int th)
{
    if (sp[th] <= 0)
	error(STACK_UNDERF, "pop", NIL);
    return (stack[--sp[th]][th]);
}

```


I have added a thread number parameter to major functions such as eval and apply. By providing the thread number (1-4) when starting a thread, I achieve thread safety.

# Concurrency Control
here is a potential for contention among threads when retrieving cells from the free list. To avoid this, I use mutex for concurrency control. The function freshcell is responsible for supplying cells. It switches its behavior based on the situation to accommodate concurrent garbage collection (GC).

```
int freshcell(void)
{
    int res;


    if (concurrent_stop_flag) {
	/* while remarking stop the world */
	pthread_mutex_lock(&mutex);
	while (concurrent_stop_flag) {
	    pthread_mutex_unlock(&mutex);
	    pthread_mutex_lock(&mutex);
	}
	pthread_mutex_unlock(&mutex);
	res = hp;
	hp = GET_CDR(hp);
	SET_CDR(res, 0);
	fc--;

    } else if (concurrent_sweep_flag) {
	pthread_mutex_lock(&mutex);
	while (fc < 50) {
	    pthread_mutex_unlock(&mutex);
	    pthread_mutex_lock(&mutex);
	}
	res = hp;
	hp = GET_CDR(hp);
	SET_CDR(res, 0);
	fc--;
	pthread_mutex_unlock(&mutex);
    } else if (concurrent_flag && fc > 50) {
	pthread_mutex_lock(&mutex);
	res = hp;
	hp = GET_CDR(hp);
	SET_CDR(res, 0);
	fc--;
	remark[remark_pt++] = res;
	pthread_mutex_unlock(&mutex);
    } else if (!concurrent_flag) {
	pthread_mutex_lock(&mutex);
	res = hp;
	hp = GET_CDR(hp);
	SET_CDR(res, 0);
	fc--;
	pthread_mutex_unlock(&mutex);
	if (fc <= 50 && !handling_resource_err) {
	    handling_resource_err = true;
	    error(RESOURCE_ERR, "M&S freshcell", NIL);
	}
    }

    else {
	pthread_mutex_lock(&mutex);
	res = hp;
	hp = GET_CDR(hp);
	SET_CDR(res, 0);
	fc--;
	pthread_mutex_unlock(&mutex);
    }

    return (res);
}


```
Ensuring thread safety in cases where destructive assignment, such as setq, is used is currently unsupported.

# Implementation
Achieving thread safety proved to be quite challenging. It was necessary to carefully divide functions under eval at the thread level. With the help of ChatGPT, I managed to make it thread-safe and functional with plet. 

We further introduced thread pooling, which allows us to eliminate the overhead of thread creation and disposal.

- worker_thread has it's number (1 ~ core)
- exec_para(int arg)  eval S-exp in thread-pooling. It return thread-number.
- para_output[N] result of eval in thread N

The code for plet is as follows:

```

int f_plet(int arglist)
{
    int arg1, arg2, temp, i, res, num[PARASIZE];

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "plet", arglist);
    if (length(arg1) > worker_count)
	error(WRONG_ARGS, "plet", arg1);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "plet", arg1);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(car(temp));
	if (improper_list_p(car(temp)))
	    error(IMPROPER_ARGS, "plet", car(temp));
	if (length(car(temp)) != 2)
	    error(IMPROPER_ARGS, "plet", car(temp));
	if (!symbolp(temparg1))
	    error(NOT_SYM, "plet", temparg1);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "plet", arg1);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "plet", arg1);

	temp = cdr(temp);
    }

	
    temp = arg1;
    i = 0;
    while (!nullp(temp)) {
	num[i] = exec_para(cadr(car(temp)));
	temp = cdr(temp);
	i++;
    }

	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond_main,&mutex);
	pthread_mutex_unlock(&mutex);

	
    temp = arg1;
    i = 0;
    while (!nullp(temp)) {
	add_lex_env(car(car(temp)), para_output[num[i]], 0);
	temp = cdr(temp);
	i++;
    }
	
    while (arg2 != NIL) {
	shelter_push(arg2, 0);
	res = eval(car(arg2), 0);
	shelter_pop(0);
	arg2 = cdr(arg2);
    }
    return (res);
}


```

# Measurement
We have achieved parallel computation in the interpreter for Fibonacci numbers up to around 30. By utilizing parallel processing, the execution time has been significantly reduced. The following measurements were taken on Windows WSL Ubuntu:

```
Easy-ISLisp Ver3.14
> (load "./tests/para.lsp")
T
> (time (fib 25))
Elapsed Time(second)=1.017071
<undef>
> (time (fib1 25))
Elapsed Time(second)=1.492650
<undef>
> 
On Linux MINT
Easy-ISLisp Ver3.26
> (load "./tests/para.lsp")
T
> (time (fib 30))
Elapsed Time(second)=2.301220
<undef>
> (time (pfib 30))
Elapsed Time(second)=4.423270
<undef>
> 

```

Parallel processing shows a reduction in execution time to approximately two-thirds compared to sequential execution. The effectiveness of parallel processing is evident. Similar results were observed on a Raspberry Pi 400 as well. However, when executed on a desktop Linux Mint system, the parallel execution took twice as long. It seems that the overhead of dividing the workload into threads is significant in this case.

# Future Outlook
For version 4, we plan to enhance the parallel processing component. Specifically, we have the following plans:

- Generating parallel execution code in the compiler: We aim to incorporate parallel processing capabilities directly into the generated code by the compiler.
- Coexistence with concurrent garbage collection (GC): We will work on ensuring smooth coexistence between parallel processing and concurrent garbage collection, optimizing memory management.
- Parallelization of map-type functions like pmapcar: We intend to extend the parallelization capabilities to functions that operate on sequences, such as pmapcar, enabling efficient parallel processing of data.

By addressing these areas, we aim to further improve the parallel processing capabilities of the system, enhance performance, and provide more flexibility for parallel execution in future versions.


# Thread safety in compiled code

## from REPL
   e.g. takeuchi function
   ```
   f_tarai(int arglist, int th){
	  x = nth(arglist,0);
	  y = nth(arglist,1);
	  z = nth(arglist,2);
	  tarai(x,y,z,th)
   }

   int tarai(int x, int y, int z, int th){
	 -- compiled code --
   }
	```
## inner code
	```
	int tarai(int x, int y, int z, int th)
	```

	All function has th argument. Th argument have thread number

## compiled code
e.g. parallel fibonacci

```
```
;;; test paralell

(defun fib (n)
    (plet ((a (fib1 (- n 1)))
           (b (fib1 (- n 2)))) (+ a b)))

(defun fib1 (n)
    (cond ((= n 0) 0)
          ((= n 1) 1)
          (t (+ (fib1 (- n 1)) (fib1 (- n 2))))))

```

```
{
	int num[PARASIZE];

	num[0] = Feval_para(Fcons(Fmakesym("FIB1"),Flist1(Fminus(N,makeint(1)))));
	num[1] = Feval_para_fcons(Fmakesym("FIB1"),Flist1(Fminus(N,makeint(2))))); 

	Fwait_para();
	
	int a = Fget_para_output(num[0]);
	int b = Fget_para_output(num[1]);
}
```

## execution

```
eisl -c
Easy-ISLisp Ver3.26
> (compile-file "./tests/para.lsp")
type inference
initialize
pass1
pass2
compiling FIB 
compiling FIB1 
finalize
invoke CC
T
> (load "./tests/para.o")
T
> (fib 30)
832040
> (fib1 30)
832040
> 

```