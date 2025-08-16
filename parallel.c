

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include "eisl.h"
#include "mem.h"
#include "fmt.h"
#include "except.h"
#include "str.h"
#include "text.h"


/* multi thread parallel functions */
void mt_enqueue(int n)
{
    mt_queue[mt_queue_pt] = n;
    mt_queue_pt++;
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&mt_cond_queue);
    pthread_mutex_unlock(&mutex);
}

int mt_dequeue(int arg)
{
    int num, i;

    if (mt_queue_pt == 0) {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_queue, &mutex);
	pthread_mutex_unlock(&mutex);
    }

    num = mt_queue[0];
    mt_queue_pt--;
    for (i = 0; i < mt_queue_pt; i++) {
	mt_queue[i] = mt_queue[i + 1];
    }
    pthread_mutex_lock(&mutex);
    para_input[num] = arg;
    para_output[num] = NIL;
    pthread_cond_signal(&mt_cond_para[num]);
    pthread_mutex_unlock(&mutex);

    return (num);
}

int eval_para(int arg)
{
    int num;

    num = mt_dequeue(arg);
    return (num);
}

void *parallel(void *arg)
{
    int num = *(int *) arg;

    while (1) {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&mt_cond_para[num], &mutex);
	pthread_mutex_unlock(&mutex);
	if (parallel_exit_flag)
	    goto exit;

	ep[num] = ep[0];
	TRY para_output[num] = eval(para_input[num], num);
	EXCEPT(Exit_Thread);
	END_TRY;
	mt_enqueue(num);
	if (mt_queue_pt == mt_queue_num) {
	    pthread_mutex_lock(&mutex);
	    pthread_cond_signal(&mt_cond_main);
	    pthread_mutex_unlock(&mutex);
	}
    }
  exit:
    pthread_exit(NULL);
}

void init_para(void)
{
    int i;

    /* mt_queue[1,2,3,4,...] worker thread number 
     * mt_para_thread[1] has worker-number 1
     * mt_para_thread[2] has worker-number 2 ... 
     */
    for (i = 0; i < mt_queue_num; i++) {
	mt_queue[i] = i + 1;
    }

    for (i = 0; i < mt_queue_num; i++) {
	pthread_create(&mt_para_thread[i + 1], NULL, parallel,
		       &mt_queue[i]);
    }

    mt_queue_pt = mt_queue_num;
}


void exit_para(void)
{
    int i;

    parallel_exit_flag = true;
    for (i = 1; i <= mt_queue_num; i++) {
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&mt_cond_para[i]);
	pthread_mutex_unlock(&mutex);
    }

}

int get_para_output(int n)
{
    return (para_output[n]);
}

int wait_para(void)
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&mt_cond_main, &mutex);
    pthread_mutex_unlock(&mutex);
    return (0);
}

int f_mt_create(int arglist, int th)
{
    int arg1;

    arg1 = car(arglist);

    if (!integerp(arg1))
	error(NOT_INT, "mt-create", arg1, th);
    if (GET_INT(arg1) > PARASIZE)
	error(WRONG_ARGS, "mt-create", arg1, th);
    if (thread_flag)
	error(WRONG_ARGS, "mt-create", arg1, th);

    mt_queue_num = GET_INT(arg1);
    thread_num = mt_queue_num;
    thread_flag = true;
    init_para();
    gbc();
    return (T);
}

int f_mt_close(int arglist, int th)
{
    if (!nullp(arglist))
	error(ILLEGAL_ARGS, "mt-close", arglist, th);

    exit_para();
    thread_flag = false;
    mt_queue_num = 0;
    thread_num = 1;
    gbc();
    return (T);
}


int f_mt_let(int arglist, int th)
{
    int arg1, arg2, temp, i, res, num[PARASIZE];

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "mt-let", arglist, th);
    if (length(arg1) > mt_queue_num)
	error(WRONG_ARGS, "mt-let", arg1, th);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "mt-let", arg1, th);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(car(temp));
	if (improper_list_p(car(temp)))
	    error(IMPROPER_ARGS, "mt-let", car(temp), th);
	if (length(car(temp)) != 2)
	    error(IMPROPER_ARGS, "mt-let", car(temp), th);
	if (!symbolp(temparg1))
	    error(NOT_SYM, "mt-let", temparg1, th);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "mt-let", arg1, th);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "mt-let", arg1, th);
	if (!listp(cadr(temp)))
	    error(WRONG_ARGS, "mt-let", arg1, th);
	temp = cdr(temp);
    }

    check_gbc(th);

    temp = arg1;
    i = 0;
    parallel_flag = 1;
    while (!nullp(temp)) {
	num[i] = eval_para(cadr(car(temp)));
	temp = cdr(temp);
	i++;
    }

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&mt_cond_main, &mutex);
    pthread_mutex_unlock(&mutex);
    parallel_flag = 0;
    if (error_flag) {
	error_flag = false;
	signal_condition(signal_condition_x, signal_condition_y, th);
    }

    temp = arg1;
    i = 0;
    while (!nullp(temp)) {
	add_lex_env(car(car(temp)), para_output[num[i]], 0);
	temp = cdr(temp);
	i++;
    }

    res = NIL;
    while (arg2 != NIL) {
	shelter_push(arg2, 0);
	res = eval(car(arg2), 0);
	shelter_pop(0);
	arg2 = cdr(arg2);
    }
    return (res);
}


int f_mt_call(int arglist, int th)
{
    int arg1, arg2, temp, i, num[PARASIZE];

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "mt-call", arglist, th);
    if (length(arg2) > mt_queue_num)
	error(WRONG_ARGS, "mt-call", arg1, th);

    temp = arg2;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "mt-call", arg2, th);
	temp = cdr(temp);
    }

    check_gbc(th);

    temp = arg2;
    i = 0;
    parallel_flag = 1;
    while (!nullp(temp)) {
	num[i] = eval_para(car(temp));
	temp = cdr(temp);
	i++;
    }

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&mt_cond_main, &mutex);
    pthread_mutex_unlock(&mutex);
    parallel_flag = 0;
    if (error_flag) {
	error_flag = false;
	signal_condition(signal_condition_x, signal_condition_y, th);
    }

    temp = NIL;
    i--;
    while (i >= 0) {
	temp = tcons(para_output[num[i]], temp, th);
	i--;
    }
    return (apply(eval(arg1, th), temp, th));
}


int f_mt_exec(int arglist, int th)
{
    int temp, i, num[PARASIZE];

    if (length(arglist) == 0)
	error(WRONG_ARGS, "mt-exec", arglist, th);
    if (length(arglist) > mt_queue_num)
	error(WRONG_ARGS, "mt-exec", arglist, th);

    temp = arglist;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "mt-exec", arglist, th);
	temp = cdr(temp);
    }


    check_gbc(th);

    temp = arglist;
    i = 0;
    parallel_flag = 1;
    while (!nullp(temp)) {
	num[i] = eval_para(car(temp));
	temp = cdr(temp);
	i++;
    }

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&mt_cond_main, &mutex);
    pthread_mutex_unlock(&mutex);
    parallel_flag = 0;
    if (error_flag) {
	error_flag = false;
	signal_condition(signal_condition_x, signal_condition_y, th);
    }

    i--;
    return (para_output[num[i]]);
}



int f_mt_lock(int arglist, int th)
{

    int res;

    pthread_mutex_lock(&mutex1);
    res = f_progn(arglist, th);
    pthread_mutex_unlock(&mutex1);
    return (res);
}


//-----------multi process-----------

#define R (0)
#define W (1)


// 1st arg is count of process
int f_mp_create(int arglist, int th)
{
    int arg1, n, i;
    char str[10];

    arg1 = car(arglist);

    if (!integerp(arg1))
	error(NOT_INT, "mp-create", arg1, th);
    if (length(arglist) != 1)
	error(ILLEGAL_ARGS, "mp-create", arglist, th);
    n = GET_INT(arg1);
    if (n > PROCSIZE)
	error(CANT_CREATE, "mp-create", n, th);

    for (i = 0; i < n; i++) {
	if (pipe(pipe_p2c[i]) == -1) {
	    error(CANT_CREATE, "mp-create pipe_p2c", NIL, th);
	}
	if (pipe(pipe_c2p[i]) == -1) {
	    error(CANT_CREATE, "mp-create pipe_c2p", NIL, th);
	}

	pid[i] = fork();
	if (pid[i] == -1) {
	    error(CANT_CREATE, "mp-create fork", NIL, th);
	}
	if (pid[i] == 0) {	// child 
	    close(pipe_p2c[i][W]);
	    close(pipe_c2p[i][R]);
	    if (dup2(pipe_p2c[i][R], STDIN_FILENO) == -1)
		error(CANT_CREATE, "mp-create dup2 stdin", NIL, th);
	    if (dup2(pipe_c2p[i][W], STDOUT_FILENO) == -1)
		error(CANT_CREATE, "mp-create dup2 stdout", NIL, th);
	    close(pipe_p2c[i][R]);
	    close(pipe_c2p[i][W]);
	    sprintf(str, "%d", i);
	    execl("/usr/local/bin/eisl", "eisl", "-r", "-p", str, NULL);
	    exit(1);

	}
	close(pipe_p2c[i][R]);
	close(pipe_c2p[i][W]);

	process_pt++;
    }

    return (T);
}


int sexp_to_str(int x)
{
    int save, res;
    char *str;

    res = make_stm(stdout, EISL_OUTSTR, NULL);
    TRY str = (char *) ALLOC(STRSIZE);
    EXCEPT(Mem_Failed)
	error(MALLOC_OVERF, "create-string-output-stream", NIL, 0);
    END_TRY;
    heap[res].name = str;
    heap[res].name[0] = '\0';

    save = output_stream;
    output_stream = res;
    print(x);
    res = output_stream;
    output_stream = save;
    return (res);
}

int write_to_pipe(int n, int x)
{
    int i, j, pos, c, m;
    char buffer1[10], buffer2[STRSIZE];

    strcpy(buffer2, GET_NAME(x));

    i = 0;
    pos = 0;
    for (j = 0; j < 10; j++)
	buffer1[j] = 0;
    c = buffer2[pos];
    while (1) {
	while (i < 7 && c != 0) {
	    buffer1[i] = c;
	    i++;
	    pos++;
	    c = buffer2[pos];

	}
	// write to pipe
	m = write(pipe_p2c[n][W], buffer1, sizeof(buffer1));
	if (m < 0)
	    error(SYSTEM_ERR, "write_to_pipe", NIL, 0);

	if (c == 0)
	    break;

	i = 0;
	for (j = 0; j < 10; j++)
	    buffer1[j] = 0;
    }
    return (NIL);
}

/*  Protocol
*   Message: 0x02, message, 0x03
*   Error: 0x15
*   Computation results: non
*/
int read_from_pipe(int n)
{
    char sub_buffer[256];
    int i, j;

    // set nonblock mode
    int flags = fcntl(pipe_c2p[n][R], F_GETFL, 0);
    fcntl(pipe_c2p[n][R], F_SETFL, flags | O_NONBLOCK);

    int bytes_read;

  reread:
    // wait until get result
    memset(buffer3, 0, sizeof(buffer3));
    while ((bytes_read =
	    read(pipe_c2p[n][R], buffer3, sizeof(buffer3))) == -1
	   && errno == EAGAIN);

  retry:
    if (buffer3[0] == '\x02') {
	i = 0;
	while (buffer3[i + 1] != '\x03') {
	    sub_buffer[i] = buffer3[i + 1];
	    i++;
	}
	sub_buffer[i] = 0;
	printf("%s", sub_buffer);
	j = 0;
	i = i + 2;
	while (buffer3[j + i] != 0) {
	    buffer3[j] = buffer3[j + i];
	    j++;
	}
	buffer3[j] = 0;
	if (buffer3[0] == 0)
	    goto reread;
	else
	    goto retry;
    } else if (buffer3[0] == '\x15') {
	error(SYSTEM_ERR, "in child", make_int(n), 0);
    } else {
	return (make_str(buffer3));
    }

    return (0);
}

int read_from_pipe_part(int n)
{
    char sub_buffer[256];
    int i, j;


    while (1) {
	for (i = 0; i < n; i++) {
	    if (child_signal[i] == 1) {
		child_signal[i] = -1;
		goto exit;
	    }
	}
	usleep(1000);
    }

  exit:
    memset(buffer3, 0, sizeof(buffer3));
    int m;
    m = read(pipe_c2p[i][R], buffer3, sizeof(buffer3));
    if (m < 0)
	error(SYSTEM_ERR, "read_from_pipe_part", NIL, 0);

  retry:
    if (buffer3[0] == '\x02') {
	i = 0;
	while (buffer3[i + 1] != '\x03') {
	    sub_buffer[i] = buffer3[i + 1];
	    i++;
	}
	sub_buffer[i] = 0;
	printf("%s", sub_buffer);
	j = 0;
	i = i + 2;
	while (buffer3[j + i] != 0) {
	    buffer3[j] = buffer3[j + i];
	    j++;
	}
	buffer3[j] = 0;
	if (buffer3[0] == 0)
	    goto exit;
	else
	    goto retry;
    } else if (buffer3[0] == '\x15') {
	error(SYSTEM_ERR, "in child", make_int(n), 0);
    } else {
	return (make_str(buffer3));
    }

    return (0);
}


int clear_child_signal(void)
{
    int i;

    for (i = 0; i < PROCSIZE; i++) {
	child_signal[i] = 0;
    }

    return (0);
}

int kill_rest_process(int n)
{
    int i;

    for (i = 0; i < n; i++) {
	child_signal1[i] = child_signal[i];
	if (child_signal[i] == 0) {
	    kill(pid[i], SIGINT);
	}
    }

    /*
       if child_signal1[i] is 0 ,ignore the pipe output.
       Because ctrl+c does not output to buffer.
     */
    for (i = 0; i < n; i++) {
	if (child_signal1[i] == 1) {
	    read_from_pipe(i);
	}
    }
    return (0);
}


int str_to_sexp(int x)
{
    int stm, save, res;

    stm = make_stm(stdin, EISL_INSTR, NULL);
    TRY heap[stm].name = Str_dup(GET_NAME(x), 1, 0, 1);
    EXCEPT(Mem_Failed) error(MALLOC_OVERF, "create-string-input-stream",
			     NIL, 0);
    END_TRY;

    save = input_stream;
    input_stream = stm;
    res = sread();
    input_stream = save;
    return (res);
}

int eval_args1(int x);
int eval_args1(int x)
{
    if (nullp(x))
	return (NIL);
    else
	return (cons(eval(car(x), 0), eval_args1(cdr(x))));
}

int eval_args(int x)
{
    return (cons(car(x), eval_args1(cdr(x))));
}



// fsubr (mp-call fun arg1 arg2 ... argn)
int f_mp_call(int arglist, int th)
{
    int arg1, arg2, temp, res, n, i, args, exp;

    arg1 = car(arglist);	//fun
    arg2 = cdr(arglist);	//args
    n = length(arg2);
    if (n > process_pt)
	error(ILLEGAL_ARGS, "mp-call", arg2, th);
    temp = arglist;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "mp-call", arglist, th);
	temp = cdr(temp);
    }

    i = 0;
    while (!nullp(arg2)) {
	exp = eval_args(car(arg2));
	write_to_pipe(i, sexp_to_str(exp));
	arg2 = cdr(arg2);
	i++;
    }

    args = NIL;
    for (i = 0; i < n; i++) {
	args = cons(str_to_sexp(read_from_pipe(i)), args);
    }
    args = reverse(args);

    res = apply(eval(arg1, th), args, th);
    return (res);
}


int f_mp_exec(int arglist, int th)
{
    int temp, res, n, i, exp;

    n = length(arglist);
    if (n > process_pt)
	error(ILLEGAL_ARGS, "mp-exec", arglist, th);
    temp = arglist;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "mp-exec", arglist, th);
	temp = cdr(temp);
    }

    i = 0;
    temp = arglist;
    while (!nullp(temp)) {
	exp = eval_args(car(temp));
	write_to_pipe(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }

    for (i = 0; i < n; i++) {
	res = str_to_sexp(read_from_pipe(i));
    }

    return (res);

}

int f_mp_part(int arglist, int th)
{
    int temp, res, n, i, exp, opt;

    opt = car(arglist);
    n = length(cdr(arglist));
    if (opt != T && opt != NIL)
	error(ILLEGAL_ARGS, "mp-part", opt, th);
    if (n > process_pt)
	error(ILLEGAL_ARGS, "mp-part", cdr(arglist), th);
    temp = cdr(arglist);
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "mp-part", arglist, th);
	temp = cdr(temp);
    }

    clear_child_signal();
    i = 0;
    temp = cdr(arglist);
    while (!nullp(temp)) {
	exp = eval_args(car(temp));
	write_to_pipe(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }
    if (opt == NIL) {
	for (i = 0; i < n; i++) {
	    res = str_to_sexp(read_from_pipe_part(n));
	    if (res == NIL)
		break;
	}
    } else if (opt == T) {
	for (i = 0; i < n; i++) {
	    res = str_to_sexp(read_from_pipe_part(n));
	    if (res != NIL)
		break;
	}
    }


    kill_rest_process(n);
    return (res);

}

int f_mp_let(int arglist, int th)
{
    int arg1, arg2, temp, exp, i, res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "mp-let", arglist, th);
    if (length(arg1) > process_pt)
	error(WRONG_ARGS, "mp-let", arg1, th);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "mp-let", arg1, th);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(car(temp));
	if (improper_list_p(car(temp)))
	    error(IMPROPER_ARGS, "mp-let", car(temp), th);
	if (length(car(temp)) != 2)
	    error(IMPROPER_ARGS, "mp-let", car(temp), th);
	if (!symbolp(temparg1))
	    error(NOT_SYM, "mp-let", temparg1, th);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "mt-let", arg1, th);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "mp-let", arg1, th);
	if (!listp(cadr(car(temp))))
	    error(WRONG_ARGS, "mp-let", arg1, th);
	temp = cdr(temp);
    }

    temp = arg1;
    i = 0;
    while (!nullp(temp)) {
	exp = eval_args(cadr(car(temp)));
	write_to_pipe(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }

    temp = arg1;
    i = 0;
    while (!nullp(temp)) {
	add_lex_env(car(car(temp)), str_to_sexp(read_from_pipe(i)), th);
	temp = cdr(temp);
	i++;
    }

    res = NIL;
    while (arg2 != NIL) {
	shelter_push(arg2, 0);
	res = eval(car(arg2), 0);
	shelter_pop(0);
	arg2 = cdr(arg2);
    }

    return (res);
}



// close all process 
int f_mp_close(int arglist, int th)
{
    int i, m;

    if (!nullp(arglist))
	error(ILLEGAL_ARGS, "mp-close", arglist, th);

    for (i = 0; i < process_pt; i++) {
	char data[] = "(quit)";
	m = write(pipe_p2c[i][W], data, sizeof(data));
	if (m < 0)
	    error(SYSTEM_ERR, "mp-close", NIL, th);
    }

    process_pt = 0;
    return (T);
}

int f_mp_report(int arglist, int th __unused)
{
    int arg1;

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "mp-report", arg1, 0);

    Fmt_print("\x02");
    printf("%s", GET_NAME(arg1));
    Fmt_print("\x03");
    fflush(stdout);
    return (T);
}

int f_mp_eval(int arglist, int th)
{
    int arg1, arg2, i, res;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (!integerp(arg1))
	error(NOT_INT, "mp-eval", arg1, th);
    if (GET_INT(arg1) > process_pt || GET_INT(arg1) < 0)
	error(WRONG_ARGS, "mp-eval", arg1, th);

    i = GET_INT(arg1);
    write_to_pipe(i, sexp_to_str(arg2));
    res = str_to_sexp(read_from_pipe(i));
    return (res);
}



//------------Distributed procces--------------------------
// code for distributed parallel machine

int f_dp_create(int arglist, int th)
{

    parent_flag = true;
    child_num = 0;
    while (!nullp(arglist)) {
	if (!stringp(car(arglist)))
	    error(NOT_STR, "dp-create", car(arglist), th);

	init_child(child_num, car(arglist));
	arglist = cdr(arglist);
	child_num++;
    }
    init_preceiver(child_num);
    return (T);
}

// close all distributed child 
int f_dp_close(int arglist, int th)
{
    int i, exp;

    if (!nullp(arglist))
	error(ILLEGAL_ARGS, "dp-close", arglist, th);

    if (parent_flag) {
	exp = list1(make_sym("dp-close"));
	for (i = 0; i < child_num; i++) {
	    send_to_child(i, sexp_to_str(exp));
	}
    }
    if (child_flag) {
	printf("Easy-ISLisp exit network mode.\n");
	RAISE(Exit_Interp);
    }
    receiver_exit_flag = 0;
    //close_socket();
    child_num = 0;
    return (T);
}

// close all distributed child  and shutdown
int f_dp_halt(int arglist, int th)
{
    int i, exp;

    if (!nullp(arglist))
	error(ILLEGAL_ARGS, "dp-halt", arglist, th);

    if (parent_flag) {
	exp = list1(make_sym("dp-halt"));
	for (i = 0; i < child_num; i++) {
	    send_to_child(i, sexp_to_str(exp));
	}
    }
    if (child_flag) {
	printf("Easy-ISLisp exit network mode.\n");
	RAISE(Exit_Interp);
	int i;
	printf("Shutting down the system...\n");
	i = system("sudo shutdown now");
	if (i == -1)
	error(SYSTEM_ERR, "dp-halt shatdown", NIL, 0);
	}
    
    child_num = 0;
    parent_flag = false;
    return (T);
}


int f_dp_let(int arglist, int th)
{
    int arg1, arg2, temp, exp, i, res;

    arg1 = car(arglist);
    arg2 = cdr(arglist);
    if (length(arglist) == 0)
	error(WRONG_ARGS, "dp-let", arglist, th);
    if (length(arg1) > child_num)
	error(WRONG_ARGS, "dp-let", arg1, th);
    if (!listp(arg1))
	error(IMPROPER_ARGS, "dp-let", arg1, th);
    temp = arg1;
    while (!nullp(temp)) {
	int temparg1;

	temparg1 = car(car(temp));
	if (improper_list_p(car(temp)))
	    error(IMPROPER_ARGS, "dp-let", car(temp), th);
	if (length(car(temp)) != 2)
	    error(IMPROPER_ARGS, "dp-let", car(temp), th);
	if (!symbolp(temparg1))
	    error(NOT_SYM, "dp-let", temparg1, th);
	if (temparg1 == T || temparg1 == NIL
	    || temparg1 == make_sym("*PI*")
	    || temparg1 == make_sym("*MOST-POSITIVE-FLOAT*")
	    || temparg1 == make_sym("*MOST-NEGATIVE-FLOAT*"))
	    error(WRONG_ARGS, "dt-let", arg1, th);
	if (STRING_REF(temparg1, 0) == ':'
	    || STRING_REF(temparg1, 0) == '&')
	    error(WRONG_ARGS, "dp-let", arg1, th);
	if (!listp(cadr(temp)))
	    error(WRONG_ARGS, "dp-let", arg1, th);
	temp = cdr(temp);
    }

    temp = arg1;
    i = 0;
    while (!nullp(temp)) {
	exp = eval_args(cadr(car(temp)));
	send_to_child(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }

    temp = arg1;
    i = 0;
    while (!nullp(temp)) {
	add_lex_env(car(car(temp)), str_to_sexp(receive_from_child(i)),
		    th);
	temp = cdr(temp);
	i++;
    }

    res = NIL;
    while (arg2 != NIL) {
	shelter_push(arg2, 0);
	res = eval(car(arg2), 0);
	shelter_pop(0);
	arg2 = cdr(arg2);
    }

    return (res);
}


void init_parent(void)
{

    // create socket
    parent_sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (parent_sockfd[0] < 0) {
	error(SYSTEM_ERR, "init parent", NIL, 0);
    }
    // initialize parent_addr
    memset((char *) &parent_addr, 0, sizeof(parent_addr));
    parent_addr.sin_family = AF_INET;
    parent_addr.sin_addr.s_addr = INADDR_ANY;
    parent_addr.sin_port = htons(PORT);

    // bind socket
    if (bind
	(parent_sockfd[0], (struct sockaddr *) &parent_addr,
	 sizeof(parent_addr)) < 0) {
	error(SYSTEM_ERR, "init parent", NIL, 0);
    }

}

void init_child(int n, int x)
{
    // create socket
    child_sockfd[n] = socket(AF_INET, SOCK_STREAM, 0);
    if (child_sockfd[n] < 0) {
	error(SYSTEM_ERR, "dp-create", make_int(n), 0);
    }
    // initialize child_addr
    memset((char *) &child_addr[n], 0, sizeof(child_addr[n]));
    child_addr[n].sin_family = AF_INET;
    child_addr[n].sin_port = htons(PORT);

    if (inet_pton(AF_INET, GET_NAME(x), &child_addr[n].sin_addr) < 0)
	error(SYSTEM_ERR, "dp-create", x, 0);


    if (connect
	(child_sockfd[n], (struct sockaddr *) &child_addr[n],
	 sizeof(child_addr[n])) < 0) {
	error(SYSTEM_ERR, "dp-create", make_int(n), 0);
    }

}

void close_socket(void)
{
    int i;

    if (parent_flag && child_num > 0) {
	for (i = 0; i < child_num; i++)
	    close(child_sockfd[i]);
    } else if (child_flag) {
	puts("EISL exit network mode.\n");
	close(parent_sockfd[0]);
	close(parent_sockfd[1]);
    }

    receiver_exit_flag = true;
}


void send_to_parent(int x)
{
    int n, i;

    // send message to parent
    memset(output_buffer, 0, sizeof(output_buffer));
    strcpy(output_buffer, GET_NAME(x));
    strcat(output_buffer, "\n");
    i = strlen(output_buffer);
    output_buffer[i] = 0x16;
    n = write(parent_sockfd[1], output_buffer, strlen(output_buffer));
    if (n < 0) {
	error(SYSTEM_ERR, "send to parent", x, 0);
    }

}

int send_to_child(int n, int x)
{
    int m, i;

    // send message to child
    memset(output_buffer, 0, sizeof(output_buffer));
    strcpy(output_buffer, GET_NAME(x));
    strcat(output_buffer, "\n");
    i = strlen(output_buffer);
    output_buffer[i] = 0x16;
    m = write(child_sockfd[n], output_buffer, strlen(output_buffer));
    if (m < 0) {
	error(SYSTEM_ERR, "send to child", NIL, 0);
    }
    return (0);
}

int receive_from_child(int n)
{
    return (make_str(parent_buffer[n]));
}



int f_dp_eval(int arglist, int th __unused)
{
    int arg1, arg2, res, i;

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if (GET_INT(arg1) >= child_num || GET_INT(arg1) < 0)
	error(WRONG_ARGS, "dp-eval", arg1, 0);

    memset(parent_buffer[i], 0, sizeof(parent_buffer[i]));
    send_to_child(GET_INT(arg1), sexp_to_str(arg2));
    while (parent_buffer[i][0] == 0) {
	usleep(1000);
    }
    res = str_to_sexp(receive_from_child(GET_INT(arg1)));
    return (res);
}

/* parent lisp */
int f_dp_transfer(int arglist, int th)
{
    int arg1, exp, i, m;
    FILE *file;

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-transfer", arg1, th);

    file = fopen(GET_NAME(arg1), "r");
    if (!file) {
	error(CANT_OPEN, "dp-transfer", arg1, th);
    }

    exp = list2(make_sym("dp-receive"), arg1);

    for (i = 0; i < child_num; i++) {
	send_to_child(i, sexp_to_str(exp));

	int bytes_read;
	while ((bytes_read =
		fread(output_buffer, sizeof(char), sizeof(output_buffer),
		      file)) > 0) {
	    m = write(child_sockfd[i], output_buffer, bytes_read);
	    if (m < 0) {
		error(SYSTEM_ERR, "dp-transfer", NIL, 0);
	    }
	}
	memset(output_buffer, 0, sizeof(output_buffer));
	output_buffer[0] = 0x16;
	m = write(child_sockfd[i], output_buffer, 1);
	if (m < 0) {
	    error(SYSTEM_ERR, "dp-transfer", NIL, 0);
	}
	receive_from_child(i);
	fseek(file, 0, SEEK_SET);
    }

    fclose(file);

    return (T);
}

/* child lisp */
int f_dp_receive(int arglist, int th)
{
    int arg1;
    FILE *file;

    child_busy_flag = false;
    arg1 = car(arglist);

    file = fopen(GET_NAME(arg1), "w");
    if (!file) {
	error(CANT_OPEN, "dp-receive", arg1, th);
    }

    int bytes_received;
    while ((bytes_received =
	    read(parent_sockfd[1], input_buffer,
		 sizeof(input_buffer))) > 0) {
	if (input_buffer[bytes_received - 1] == 0x16) {
	    input_buffer[bytes_received - 1] = 0;
	    fwrite(input_buffer, sizeof(char), bytes_received - 1, file);
	    break;
	}
	fwrite(input_buffer, sizeof(char), bytes_received, file);
    }
    fclose(file);

    return (T);
}


int f_dp_load(int arglist, int th)
{
    int arg1, exp, i;

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-load", arg1, th);

    exp = list2(make_sym("LOAD"), arg1);

    for (i = 0; i < child_num; i++) {
	send_to_child(i, sexp_to_str(exp));
	receive_from_child(i);
    }

    eval(exp, 0);

    return (T);
}


int f_dp_compile(int arglist, int th)
{
    int arg1, exp, i;

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-compile", arg1, th);

    exp = list2(make_sym("COMPILE-FILE"), arg1);

    for (i = 0; i < child_num; i++) {
	send_to_child(i, sexp_to_str(exp));
	receive_from_child(i);
    }

    eval(exp, 0);

    return (T);
}

// fsubr (dp-call fun arg1 arg2 ... argn)
int f_dp_call(int arglist, int th)
{
    int arg1, arg2, temp, res, n, i, args, exp;

    arg1 = car(arglist);	//fun
    arg2 = cdr(arglist);	//args
    n = length(arg2);
    if (n > child_num)
	error(ILLEGAL_ARGS, "dp-call", arg2, th);
    temp = arglist;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "dp-call", arglist, th);
	temp = cdr(temp);
    }

    i = 0;
    while (!nullp(arg2)) {
	exp = eval_args(car(arg2));
	send_to_child(i, sexp_to_str(exp));
	arg2 = cdr(arg2);
	i++;
    }

    args = NIL;
    for (i = 0; i < n; i++) {
	args = cons(str_to_sexp(receive_from_child(i)), args);
    }
    args = reverse(args);

    res = apply(eval(arg1, th), args, th);
    return (res);
}


int f_dp_exec(int arglist, int th)
{
    int temp, res, n, i, exp;

    n = length(arglist);
    if (n > child_num)
	error(ILLEGAL_ARGS, "dp-exec", arglist, th);
    temp = arglist;
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "dp-exec", arglist, th);
	temp = cdr(temp);
    }

    i = 0;
    temp = arglist;
    while (!nullp(temp)) {
	exp = eval_args(car(temp));
	send_to_child(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }

    for (i = 0; i < n; i++) {
	res = str_to_sexp(receive_from_child(i));
    }

    return (res);

}

int f_dp_report(int arglist, int th __unused)
{
    int arg1;
    char sub_buffer[STRSIZE];

    arg1 = car(arglist);
    if (!stringp(arg1))
	error(NOT_STR, "dp-report", arg1, 0);

    memset(sub_buffer, 0, sizeof(sub_buffer));
    sprintf(sub_buffer, "\x02%s\x03", GET_NAME(arg1));
    send_to_parent(make_str(sub_buffer));
    return (T);
}


int f_dp_part(int arglist, int th)
{
    int temp, res, n, i, exp, opt;

    opt = car(arglist);
    n = length(cdr(arglist));
    if (opt != T && opt != NIL)
	error(ILLEGAL_ARGS, "dp-part", opt, th);
    if (n > child_num)
	error(ILLEGAL_ARGS, "dp-part", cdr(arglist), th);
    temp = cdr(arglist);
    while (!nullp(temp)) {
	if (!listp(car(temp)))
	    error(WRONG_ARGS, "dp-part", arglist, th);
	temp = cdr(temp);
    }
    i = 0;
    temp = cdr(arglist);
    while (!nullp(temp)) {
	exp = eval_args(car(temp));
	send_to_child(i, sexp_to_str(exp));
	temp = cdr(temp);
	i++;
    }
    if (opt == NIL) {
	//res = str_to_sexp(receive_from_child_part(n, 0));
    } else if (opt == T) {
	//res = str_to_sexp(receive_from_child_part(n, 1));
    }
    return (res);

}



int receive_from_parent(void)
{
    return (make_str(child_buffer));
}


void print_ascii(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++) {
	printf("0x%02X ", (unsigned char) str[i]);
    }
    printf("\n");
}


// Thread for parent receiver
void *preceiver(void *arg)
{
    int n, m, i;
    char buffer[BUFSIZE], sub_buffer[BUFSIZE];

    n = *(int *) arg;

    while (1) {

	if (receiver_exit_flag)
	    break;

	// read message from parent
	memset(buffer, 0, sizeof(buffer));
      reread:
	memset(sub_buffer, 0, sizeof(sub_buffer));
	m = read(child_sockfd[n], sub_buffer, sizeof(sub_buffer));
	if (m < 0) {
	    error(SYSTEM_ERR, "receive from child", make_int(n), 0);
	}
	//print_ascii(sub_buffer);printf("m=%d",m);fflush(stdout);
	strcat(buffer, sub_buffer);

	// normal message  0x16 is at m-1
	if (sub_buffer[m - 1] != 0x16)
	    goto reread;

	//print_ascii(buffer); 

	i = strlen(buffer);
	buffer[i] = 0;
	strcpy(parent_buffer[n], buffer);
    }

    pthread_exit(NULL);
}

// Thread for child receiver
void *creceiver(void *arg)
{
    int n, m, i, j;
    char buffer[BUFSIZE], sub_buffer[BUFSIZE];

    if (!connect_flag) {
	//wait conneting
	listen(parent_sockfd[0], 5);
	parent_len = sizeof(parent_addr);
	connect_flag = 1;

	// connection from parent
	parent_sockfd[1] =
	    accept(parent_sockfd[0], (struct sockaddr *) &parent_addr,
		   &parent_len);
	if (parent_sockfd[1] < 0) {
	    error(SYSTEM_ERR, "*creceiver", NIL, 0);
	}
    }


    while (1) {

	if (receiver_exit_flag)
	    break;


	// read message from parent
	memset(buffer, 0, sizeof(buffer));
      reread:
	memset(sub_buffer, 0, sizeof(sub_buffer));
	n = read(parent_sockfd[1], sub_buffer, sizeof(sub_buffer));
	if (n < 0) {
	    error(SYSTEM_ERR, "*creceiver", NIL, 0);
	}

	strcat(buffer, sub_buffer);
	if (sub_buffer[n - 1] != 0x16)
	    goto reread;

	pthread_mutex_lock(&mutex2);


	j = 0;


	m = strlen(buffer);

	for (i = 0; i < m - 1; i++) {
	    if (buffer[i] == 0x11) {
		memset(child_buffer, 0, sizeof(child_buffer));
		strcpy(child_buffer, "nil");
		ctrl_c_flag = 1;
		goto exit;
	    } else {
		child_buffer[j] = buffer[i];
		j++;
	    }
	}


      exit:

	child_buffer_ready = 1;
	pthread_cond_signal(&md_cond);
	pthread_mutex_unlock(&mutex2);


    }

    pthread_exit(NULL);
}


void init_preceiver(int n)
{
    int i;
    // create parent receiver thread 
    for (i = 0; i < n; i++) {
	int *arg = malloc(sizeof(int));
	*arg = i;
	pthread_create(&preceiver_thread[i], NULL, preceiver, arg);
    }

}

void init_creceiver(void)
{
    // create child receiver thread 
    pthread_create(&creceiver_thread, NULL, creceiver, NULL);

}
