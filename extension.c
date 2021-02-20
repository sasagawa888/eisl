
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __arm__
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif
#include "eisl.h"

void initexsubr(void){
    defsubr("RANDOM-REAL",f_random_real);
    defsubr("RANDOM",f_random);
    defsubr("NCONC",f_nconc);
    defsubr("FAST-ADDRESS",f_address);
    defsubr("MACROEXPAND-1",f_macroexpand_1);
    defsubr("BACKTRACE",f_backtrace);
    defsubr("BREAK",f_break);
    defsubr("EDIT",f_edit);
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
    defsubr("HEAPDUMP",f_heapdump);
    defsubr("INSTANCE",f_instance);
    defsubr("SUBSTITUTE",f_substitute);
    
    #ifdef __arm__
    defsubr("WIRINGPI-SETUP-GPIO",f_wiringpi_setup_gpio);
    defsubr("WIRINGPI-SPI-SETUP-CH-SPEED",f_wiringpi_spi_setup_ch_speed);
    defsubr("PWM-SET-MODE",f_pwm_set_mode);
    defsubr("PWM-SET-RANGE",f_pwm_set_range);
    defsubr("PWM-SET-CLOCK",f_pwm_set_clock);
    defsubr("PIN-MODE",f_pin_mode);
    defsubr("DIGITAL-WRITE",f_digital_write);
    defsubr("DIGITAL-WRITE-BYTE",f_digital_write_byte);
    defsubr("PULL-UP-DN-CONTROL",f_pull_up_dn_control);
    defsubr("DIGITAL-READ",f_digital_read);
    defsubr("DELAY",f_delay);
    defsubr("DELAY-MICROSECONDS",f_delay_microseconds);
    #endif

    #ifdef __NVCC__
    defsubr("GPU-ACCURACY",f_gpu_accuracy); 
    defsubr("GPU-ACTIVATE",f_gpu_activate); 
    defsubr("GPU-ADAGRAD",f_gpu_adagrad);
    defsubr("GPU-ADAM",f_gpu_adam);
    defsubr("GPU-ADD",f_gpu_add);
    defsubr("GPU-ANALIZER",f_gpu_analizer);
    defsubr("GPU-AVERAGE",f_gpu_average);
    defsubr("GPU-COPY",f_gpu_copy);
    defsubr("GPU-CONVOLUTE",f_gpu_convolute);
    defsubr("GPU-CORRECT",f_gpu_correct);
    defsubr("GPU-DECONVOLUTE",f_gpu_deconvolute);
    defsubr("GPU-DIFF",f_gpu_diff);
    defsubr("GPU-DROPOUT",f_gpu_dropout);
    defsubr("GPU-EMULT",f_gpu_emult);
    defsubr("GPU-FULL",f_gpu_full);
    defsubr("GPU-GRADFILTER",f_gpu_gradfilter);
    defsubr("GPU-IDENT",f_gpu_ident);
    defsubr("GPU-LOSS",f_gpu_loss);
    defsubr("GPU-MULT",f_gpu_mult);
    defsubr("GPU-POOLING",f_gpu_pooling);
    defsubr("GPU-RANDOM-SELECT",f_gpu_random_select);
    defsubr("GPU-SGD",f_gpu_sgd);
    defsubr("GPU-SUB",f_gpu_sub);
    defsubr("GPU-SUM",f_gpu_sum);
    defsubr("GPU-SMULT",f_gpu_smult);
    defsubr("GPU-TRACE",f_gpu_trace);
    defsubr("GPU-TRANSPOSE",f_gpu_transpose);
    defsubr("GPU-UNFULL",f_gpu_unfull);
    defsubr("GPU-UNPOOLING",f_gpu_unpooling);
    #endif
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


int f_self_introduction(int arglist){
#if __APPLE__
    return(makesym("MACOS"));
#elif defined(__OpenBSD__)
    return(makesym("OPENBSD"));
#else
    return(makesym("LINUX"));
#endif
}


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


int f_system(int arglist){
    int arg1;

	arg1 = car(arglist);
	if(system(GET_NAME(arg1)) == -1)
		error(SYSTEM_ERR, "system", arg1);
	return(T);
}



int f_freedll(int arglist){
  
    //dlclose(hmod);
    return(T);
}



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
    return(T);
}

int f_instance(int arglist){
    int arg1,addr;

    arg1 = car(arglist);
    addr = get_int(arg1);
    print(addr);
    return(T);
}

//----------for Raspberry PI
#ifdef __arm__
int f_wiringpi_setup_gpio(int arglist){
    wiringPiSetupGpio();
    return(T);
} 

int f_wiringpi_spi_setup_ch_speed(int arglist){
    int arg1,arg2,x,y;

    if(length(arglist) != 2)
        error(WRONG_ARGS,"wiringpi-spi-setup-ch-speed",arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"wiringpi-spi-setup-ch-speed",arg1);
    if(!integerp(arg2))
        error(NOT_INT,"wiringpi-spi-setup-ch-speed",arg2);
    
    x = GET_INT(arg1);
    y = GET_INT(arg2);
    wiringPiSPISetup(x, y);
    return(T);
}

int f_pwm_set_mode(int arglist){
    int arg1;

    if(length(arglist) != 1)
        error(WRONG_ARGS,"pwm-set-mode",arglist);

    arg1 = car(arglist);

    if(arg1 == makesym("pwm-mode-ms"))
        pwmSetMode(PWM_MODE_MS);
    else if(arg1 == makesym("pwm-mode-bal"))
        pwmSetMode(PWM_MODE_BAL);
    else 
        error(WRONG_ARGS,"pwm-set-mode",arg1);
    
    return(T);
}

int f_pwm_set_range(int arglist){
    int arg1,x;

    if(length(arglist) != 1)
        error(WRONG_ARGS,"pwm-set-range",arglist);

    arg1 = car(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"pwm-set-range",arg1);

    x = GET_INT(arg1);
    pwmSetRange(x);
    return(T);
}

int f_pwm_set_clock(int arglist){
    int arg1,x;

    if(length(arglist) != 1)
        error(WRONG_ARGS,"pwm-set-clock",arglist);
    
    arg1 = car(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"pwm-set-clock",arg1);

    x = GET_INT(arg1);
    pwmSetClock(x);
    return(T);
}

int f_pin_mode(int arglist){
    int arg1,arg2,x;

    if(length(arglist) != 2)
        error(WRONG_ARGS,"pin-mode",arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"pin-,mode",arg1);
    
    x = GET_INT(arg1);
    if(arg2 == makesym("intput"))
        pinMode(x,INPUT);
    else if(arg2 == makesym("output"))
        pinMode(x,OUTPUT);
    else if(arg2 == makesym("pwm-output"))
        pinMode(x,PWM_OUTPUT);
    else
        error(WRONG_ARGS,"pin-mode",arg2);
    
    return(T);
}

int f_digital_write(int arglist){
    int arg1,arg2,x,y;

    if(length(arglist) != 2)
        error(WRONG_ARGS,"digital-write",arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"digital-write",arg1);
    if(!integerp(arg2))
        error(NOT_INT,"digital-write",arg2);    

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    digitalWrite(x,y);
    return(T);
}

int f_digital_write_byte(int arglist){
    int arg1,x;

    if(length(arglist) != 1)
        error(WRONG_ARGS,"digital-write-byte",arglist);

    arg1 = car(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"digital-write-byte",arg1);

    x = GET_INT(arg1);
    digitalWriteByte(x);
    return(T);
} 

int f_pull_up_dn_control(int arglist){
    int arg1,arg2,x,y;

    if(length(arglist) != 2)
        error(WRONG_ARGS,"pull-up-dn-control",arglist);

    arg1 = car(arglist);
    arg2 = cadr(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"pull-up-dn-control",arg1);
    if(!integerp(arg2))
        error(NOT_INT,"pull-up-dn-control",arg2);

    x = GET_INT(arg1);
    y = GET_INT(arg2);
    pullUpDnControl(x,y);
    return(T);
}

int f_digital_read(int arglist){
    int arg1,x,res;

    if(length(arglist) != 1)
        error(WRONG_ARGS,"digital-read",arglist);
    
    arg1 = car(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"digital-read",arg1);

    x = GET_INT(arg1);
    res = digitalRead(x);
    return(makeint(res));
}

int f_delay(int arglist){
    int arg1,x;

    if(length(arglist) != 1)
         error(WRONG_ARGS,"delay",arglist);

    arg1 = car(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"delay",arg1);

    x = GET_INT(arg1);
    delay(x);
    return(T);
}

int f_delay_microseconds(int arglist){
    int arg1,x;

    if(length(arglist) != 1)
        error(WRONG_ARGS,"delay-microseconds",arglist);

    arg1 = car(arglist);
    if(!integerp(arg1))
        error(NOT_INT,"delay-microseconds",arg1);
    
    x = GET_INT(arg1);
    delayMicroseconds(x);
    return(T);
}
#endif

int f_substitute(int arglist){
    int arg1,arg2;

    arg1 = car(arglist);
    arg2 = cadr(arglist);

    return(substitute(arg1,arg2,NIL));
}



