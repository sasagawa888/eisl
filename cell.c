/*
memo
lisp-2  symbol-address car=function-addr, cdr=global-val
closure function-address car=arg+body, cdr=environment
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "eisl.h"
#include "compat/nana.h"
#include "mem.h"
#include "fmt.h"
#include "except.h"
#include "str.h"

void initcell(void){
    int addr,x;

    // initialize heap area
    for(addr=0; addr < HEAPSIZE; addr++){
        heap[addr].flag = FRE;
        heap[addr].val.cdr.intnum = addr+1;
        heap[addr].aux = 0;
        heap[addr].option = 0;
    }
    hp = 0;
    fc = HEAPSIZE;
    
    for(x=0; x<HASHTBSIZE; x++)
        cell_hash_table[x] = NIL;
    
   
    //0th address is for NIL, set initial environment
    makesym("NIL");    //0th address NIL
    SET_AUX(0,28);     //class of nil is null
    SET_OPT(0,CONSTN);
    makesym("T");      //2nd address is T
    SET_AUX(2,29);     //class of t is symbol
    SET_OPT(2,CONSTN);
    makesym("<undef>");  //4th address is UNDEF
    SET_AUX(4,29);     //class of <undef> is symbol
    makesym("<file-end>"); //6the address is FEND
    SET_AUX(6,29);     //class of <end-of-file> is symbol
    ep = 0;
    dp = 0;
    sp = 0;
    ap = 0;
}

void bindclass(const char *name, int cl){
    int sym;

    sym = makesym(name);
    SET_AUX(sym,cl);
    SET_OPT(cl,SYSTEM);     //built-in-class
    SET_OPT(sym,SYSTEM);       //symbol formated by <***>  are built-in-classes
}

//class aux = ((format-string . error-msg)(format-arguments . args))
void initerrargs(int cl){
    int vars,args;

    vars = list11(cons(makesym("a"),UNDEF),  //format-string
                  cons(makesym("b"),UNDEF),  //format-arguments
                  cons(makesym("c"),UNDEF),  //function
                  cons(makesym("d"),UNDEF),  //operation
                  cons(makesym("e"),UNDEF),  //operands
                  cons(makesym("f"),UNDEF),  //object
                  cons(makesym("g"),UNDEF),  //expected-class
                  cons(makesym("h"),UNDEF),  //string
                  cons(makesym("i"),UNDEF),  //stream
                  cons(makesym("j"),UNDEF),  //name
                  cons(makesym("k"),UNDEF));  //namespace

    SET_CDR(cl,vars);
    args = list11(cons(makesym("format-string"),makesym("a")),
                  cons(makesym("format-arguments"),makesym("b")),
                  cons(makesym("function"),makesym("c")),
                  cons(makesym("operation"),makesym("d")),
                  cons(makesym("operands"),makesym("e")),
                  cons(makesym("object"),makesym("f")),
                  cons(makesym("expected-class"),makesym("g")),
                  cons(makesym("string"),makesym("h")),
                  cons(makesym("stream"),makesym("i")),
                  cons(makesym("name"),makesym("j")),
                  cons(makesym("namespace"),makesym("k")));
    SET_AUX(cl,args);

}

void initclass(void){
    cobject = makeclass("object",NIL);
    cbasic_array = makeclass("basic-array",cobject);
    cbasic_array_star = makeclass("basic-array*",cbasic_array);
    cgeneral_array_star = makeclass("general-array*",cbasic_array_star);
    cbasic_vector = makeclass("basic-vector",cbasic_array);
    cgeneral_vector = makeclass("general-vector",cbasic_vector);
    cstring = makeclass("string",cbasic_vector);
    cbuilt_in_class = makeclass("built-in-class",cbuilt_in_class);
    ccharacter = makeclass("character",cobject);
    cfunction = makeclass("function",cobject);
    cgeneric_function = makeclass("generic-function",cfunction);
    cstandard_generic_function = makeclass("standard-generic-function",cgeneric_function);
    clist = makeclass("list",cobject);
    ccons = makeclass("cons",clist);
    cnull= makeclass("null",list2(makesym("<SYMBOL>"),makesym("<LIST>")));
    csymbol = makeclass("symbol",cobject);
    cnumber = makeclass("number",cobject);
    cfloat = makeclass("float",cnumber);
    cinteger = makeclass("integer",cnumber);
    cserious_condition = makeclass("serious-condition",cobject);
    cerror = makeclass("error",cserious_condition);
    carithmetic_error = makeclass("arithmetic-condition",cerror);
    cdivision_by_zero = makeclass("division-by-zero",carithmetic_error);
    cfloating_point_overflow = makeclass("floating-point-overflow",carithmetic_error);
    cfloating_point_underflow = makeclass("floating-point-underflow",carithmetic_error);
    ccontrol_error = makeclass("control-error",cerror);
    cparse_error = makeclass("parse-error",cerror);
    cprogram_error = makeclass("program-error",cerror);
    cdomain_error = makeclass("domain-error",cprogram_error);
    cclass_error = makeclass("class-error",cprogram_error);
    cundefined_entity = makeclass("undefined-entity",cprogram_error);
    cunbound_variable = makeclass("unbound-variable",cundefined_entity);
    cundefined_function = makeclass("undefined-function",cundefined_entity);
    csimple_error = makeclass("simple-error",cerror);
    cstream_error = makeclass("stream-error",cerror);
    cend_of_stream = makeclass("end-of-stream",cstream_error);
    cstorage_exhausted = makeclass("storage-exhausted",cserious_condition);

    cstandard_class = makeclass("standard-class",cobject);
    cstandard_object = makeclass("standard-object",cobject);
    cstream = makeclass("stream",cobject);
    cinvalid = makeclass("invalid",cinvalid);
    cfixnum = makeclass("fixnum",cinteger);
    clongnum = makeclass("longnum",cinteger);
    cbignum = makeclass("bignum",cinteger);
    cfloat_array = makeclass("float-array",cbasic_array);

    bindclass("<OBJECT>",cobject);
    bindclass("<BASIC-ARRAY>",cbasic_array);
    bindclass("<GENERAL-ARRAY*>",cgeneral_array_star);
    bindclass("<BASIC-ARRAY*>",cbasic_array_star);
    bindclass("<BASIC-VECTOR>",cbasic_vector);
    bindclass("<GENERAL-VECTOR>",cgeneral_vector);
    bindclass("<STRING>",cstring);
    bindclass("<BUILT-IN-CLASS>",cbuilt_in_class);
    bindclass("<CHARACTER>",ccharacter);
    bindclass("<FUNCTION>",cfunction);
    bindclass("<GENERIC-FUNCTION>",cgeneric_function);
    bindclass("<STANDARD-GENERIC-FUNCTION>",cstandard_generic_function);
    bindclass("<LIST>",clist);
    bindclass("<CONS>",ccons);
    bindclass("<NULL>",cnull);
    bindclass("<SYMBOL>",csymbol);
    bindclass("<NUMBER>",cnumber);
    bindclass("<FLOAT>",cfloat);
    bindclass("<INTEGER>",cinteger);
    bindclass("<SERIOUS-CONDITION>",cserious_condition);
    bindclass("<ERROR>",cerror);
    bindclass("<ARITHMETIC-ERROR>",carithmetic_error);
    bindclass("<DIVISION-BY-ZERO>",cdivision_by_zero);
    bindclass("<FLOATING-POINT-OVERFLOW>",cfloating_point_overflow);
    bindclass("<FLOATING-POINT-UNDERFLOW>",cfloating_point_underflow);
    bindclass("<CONTROL-ERROR>",ccontrol_error);
    bindclass("<PARSE-ERROR>",cparse_error);
    bindclass("<PROGRAM-ERROR>",cprogram_error);
    bindclass("<DOMAIN-ERROR>",cdomain_error);
    bindclass("<CLASS-ERROR>",cclass_error);
    bindclass("<UNDEFINED-ENTITY>",cundefined_entity);
    bindclass("<UNBOUND-VARIABLE>",cunbound_variable);
    bindclass("<UNDEFINED-FUNCTION>",cundefined_function);
    bindclass("<SIMPLE-ERROR>",csimple_error);
    bindclass("<STREAM-ERROR>",cstream_error);
    bindclass("<END-OF-STREAM>",cend_of_stream);
    bindclass("<STORAGE-EXHAUSTED>",cstorage_exhausted);
    bindclass("<STANDARD-CLASS>",cstandard_class);
    bindclass("<STANDARD-OBJECT>",cstandard_object);
    bindclass("<STREAM>",cstream);
    bindclass("<INVALID>",cinvalid);
    bindclass("<FIXNUM>",cfixnum);
    bindclass("<LONGNUM>",clongnum);
    bindclass("<BIGNUM>",cbignum);
    bindclass("<FLOAT-ARRAY>",cfloat_array);

    initerrargs(cserious_condition);
    initerrargs(cerror);
    initerrargs(carithmetic_error);
    initerrargs(cdivision_by_zero);
    initerrargs(cfloating_point_overflow);
    initerrargs(cfloating_point_underflow);
    initerrargs(ccontrol_error);
    initerrargs(cparse_error);
    initerrargs(cprogram_error);
    initerrargs(cdomain_error);
    initerrargs(cclass_error);
    initerrargs(cundefined_entity);
    initerrargs(cunbound_variable);
    initerrargs(cundefined_function);
    initerrargs(csimple_error);
    initerrargs(cstream_error);
    initerrargs(cend_of_stream);
    initerrargs(cstorage_exhausted);

   
}

void initstream(void){
    standard_input = makestream(stdin,EISL_INPUT);
    standard_output = makestream(stdout,EISL_OUTPUT);
    standard_error = makestream(stderr,EISL_OUTPUT);
}

int freshcell(void){
    int res;

    if(gc_sw == 0){
        res = hp;
        hp = heap[hp].val.cdr.intnum;
        SET_CDR(res,0);
        fc--;
        if(fc <= 50)
            error(RESOURCE_ERR,"M&S fleshcell",NIL);
    
        return(res);
    }
    else{
        res = wp;
        if(IS_VECTOR(res) || IS_ARRAY(res)){
            FREE(heap[res].val.car.dyna_vec);
            heap[res].val.car.dyna_vec = NULL;
        }
        else if(IS_STRING(res)){
            FREE(heap[res].name);
            heap[res].name = NULL;
        }
        SET_TAG(res,EMP);
        SET_CAR(res,0);
        SET_CDR(res,0);
        SET_AUX(res,0);
        SET_PROP(res,0);
        SET_OPT(res,0);
        SET_TR(res,0);
        wp++;
        if(wp < HEAPSIZE && wp > HEAPSIZE - 50)
            error(RESOURCE_ERR,"copying fleshcell",NIL);
        else if(wp > HEAPSIZE && wp > CELLSIZE - 50)
            error(RESOURCE_ERR,"copying fleshcell",NIL);
        
        return(res);
    }
}


int hfreshcell(void){
    int res;

    res = hp;
    hp = heap[hp].val.cdr.intnum;
    SET_CDR(res,0);
    fc--;
    if(fc <= 50)
        error(RESOURCE_ERR,"hfleshcell",NIL);
    return(res);
}

//set value to environment by destructive
//by deep-bind
void setlexenv(int sym, int val){
    int addr;

    addr= assq(sym,ep);
    if(addr == FAILSE)
        addlexenv(sym,val);
    else
        SET_CDR(addr,val);
}

//bind value to dynamic environment
int setdynenv(int sym, int val){
    int i;

    for(i=dp;i>0;i--){
        if(dynamic[i][0] == sym){
            dynamic[i][1] = val;
            return(T);
        }
    }
    dp++;
    if(dp >= DYNSIZE)
        error(DYNAMIC_OVERF, "setdynenv", NIL);
    dynamic[dp][0] = sym;
    dynamic[dp][1] = val;
    return(T);
}


//additinal of lexical variable
void addlexenv(int sym, int val){
    ep = cons(cons(sym,val),ep);
}

//addition of dynamic variable
int adddynenv(int sym, int val){
    dp++;
    if(dp >= DYNSIZE)
        error(DYNAMIC_OVERF, "adddynenv", NIL);
    dynamic[dp][0] = sym;
    dynamic[dp][1] = val;
    return(T);
}


//environment is association list
// env = ((sym1 . val1) (sym2 . val2) ...)
// find value with assq
// when not find return FAILSE
int findenv(int sym){
    int addr;

    addr = assq(sym,ep);

    if(addr == FAILSE)
        return(FAILSE);
    else
        return(cdr(addr));
}

//find in dynamic environment
int finddyn(int sym){
    int i;

    for(i=dp;i>0;i--){
        if(dynamic[i][0] == sym)
            return(dynamic[i][1]);
    }
    return(FAILSE);
}

//bind to association list destructively
void setval(int sym, int val, int ls){
    int addr;

    addr= assq(sym,ls);
    if(addr != FAILSE)
        SET_CDR(addr,val);
}


//for uniqueness of symbol
int getsym(const char *name, int index){
    int addr;

    addr = cell_hash_table[index];

    while(addr != NIL){
        if(strcmp(name,GET_NAME(car(addr))) == 0)
            return(car(addr));
        else
            addr = cdr(addr);
    }
    return(-1);
}

/*
link list is generated in hheap area allways
*/
int addsym(const char *name, int index){
    int addr,res;

    addr = cell_hash_table[index];
    addr = hcons(res=makesym1(name),addr);
    cell_hash_table[index] = addr;
    return(res);
}
/*
symbol
car = function addr
cdr = global value
aux = class symbol
option = CONSTN(constant )
*/
int makesym1(const char *pname){
    int addr;

    addr = hfreshcell();
    SET_TAG(addr,SYM);
    TRY
        heap[addr].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF,"makesym",NIL);
    END_TRY;
    SET_CAR(addr,NIL);
    SET_CDR(addr,NIL);
    SET_AUX(addr,csymbol); //class symbol
    return(addr);
}

//calculate hash number
//modulo sum of each charactor's ASCII code with
//HASHTBSIZE(107)
int hash(const char *name){
    int res;

    res = 0;
    while(*name != NUL){
        res = res + (int)*name;
        name++;
    }
    return(res % HASHTBSIZE);
}

//-------for debug------------------
DEF_GETTER(flag, FLAG, flag, NIL)
void cellprint(int addr){
    switch(GET_FLAG(addr)){
    case FRE:   fputs("FRE ", stdout); break;
    case USE:   fputs("USE ", stdout); break;
    }
    switch(GET_TAG(addr)){
    case EMP:   puts("EMP");
        break;
    case INTN:  Fmt_print("INTN   %d\n" , GET_INT(addr));
        break;
    case FLTN:  Fmt_print("FLTN   %f\n", GET_FLT(addr));
        break;
    case LONGN: Fmt_print("LONGN  %lld\n", GET_LONG(addr));
        break;
    case BIGX:  Fmt_print("BIGX   %d\n", GET_CAR(addr));
        break;
    case SYM:   Fmt_print("SYM    %07d %07d %07d %s\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr), GET_NAME(addr));
        break;
    case STR:   Fmt_print("STR    %07d %07d %07d %s\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr), GET_NAME(addr));
        break;
    case LIS:   Fmt_print("LIS    %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr));
        break;
    case SUBR:  Fmt_print("SUBR   %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr));
        break;
    case FSUBR: Fmt_print("FSUBR  %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr));
        break;
    case FUNC:  Fmt_print("FUNC   %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr));
        break;
    case MACRO: Fmt_print("MACRO  %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr));
        break;
    case CLASS: Fmt_print("CLASS  %07d %07d %07d %s\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr), GET_NAME(addr));
        break;
    case GENERIC:
        Fmt_print("GENE   %07d %07d %07d\n", GET_CAR(addr), GET_CDR(addr), GET_AUX(addr));
        break;
    default:
        Fmt_print("cellprint(%d) tag switch default action\n", addr);
    }
}

//heap dump
void heapdump(int start, int end){
    int i;

    puts("addr    F   TAG    CAR     CDR     AUX     NAME");
    for(i=start; i<= end; i++){
        Fmt_print("%07d ", i);
        cellprint(i);
    }
}


void store_backtrace(int x){
    int i;

    for(i=1;i<BACKSIZE;i++){
      int y;
      
        y = backtrace[i];
        backtrace[i-1] = y;
    }
    backtrace[BACKSIZE-1] = x;
}

//----------------------------------------

int makeint(int intn){
    //int addr;

    //addr = freshcell();
    //SET_TAG(addr,INTN);
    //SET_INT(addr,intn);
    //SET_AUX(addr,cfixnum); //class fixnum
    if(intn >= 0)
        return(INT_FLAG | intn);
    else
        return(intn);
}

int makelong(long long int lngnum){
    int addr;

    addr = freshcell();
    SET_TAG(addr,LONGN);
    SET_LONG(addr,lngnum);
    SET_AUX(addr,clongnum); //class longnum
    return(addr);
}

int makeflt(double floatn){
    int addr;

    addr = freshcell();
    SET_TAG(addr,FLTN);
    SET_FLT(addr,floatn);
    SET_AUX(addr,cfloat); //class float
    return(addr);
}
/*
symbol
car = function
cdr = global value
aux = class
*/
int makesym(const char *pname){
    int index,res;

    index = hash(pname);
    if((res=getsym(pname, index)) != -1)
        return(res);
    else
        return(addsym(pname,index));
}

/*
function
car = args&body
cdr = environment
aux = null
func object is generated in heap area.
*/
int makefunc(const char *pname, int addr){
    int val;

    val = hfreshcell();
    SET_TAG(val,FUNC);
    TRY
        heap[val].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF,"makefunc",NIL);
    END_TRY;
    SET_CAR(val,copy_heap(addr));
    SET_CDR(val,ep);
    SET_AUX(val,cfunction); //class function
    SET_OPT(val,count_args(car(addr))); //amount of argument
    return(val);
}

//amount of argument. if it has :rest or &rest, it is minus number
int count_args(int ls){
    int ls1,n,res;

    ls1 = reverse(ls);
    n = length(ls);
    if(eqp(cadr(ls1),makesym(":REST")))
        res = -1*n;
    else if(eqp(cadr(ls1),makesym("&REST")))
        res = -1*n;
    else
        res = n;

    return(res);
}

int makevec(int n, int obj){
    int res,i, *vec;

    res = freshcell();
    TRY
        vec = (int *)ALLOC(sizeof(int) * n);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF, "make_vector", NIL);
    END_TRY;
    SET_VEC(res,vec);
    for(i=0; i<n; i++)
        SET_VEC_ELT(res,i,copy(obj));
    SET_TAG(res,VEC);
    SET_CDR(res,n);
    SET_AUX(res,cgeneral_vector); // class general-vector
    return(res);
}



int vector(int lis){
    int len,i,res;

    len = length(lis);
    i = 0;
    res = makevec(len,UNDEF);
    while(!nullp(lis)){
        vector_set(res,i,car(lis));
        i++;
        lis = cdr(lis);
    }

    return(res);
}

/*
generic
car = args
cdr = method
aux = class
*/
int makegeneric(char *pname, int lamlist,int body){
    int val;

    val = hfreshcell();
    SET_TAG(val,GENERIC);
    TRY
        heap[val].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF,"makegeneric",NIL);
    END_TRY;
    SET_CAR(val,copy_heap(lamlist));
    SET_OPT(val,count_args(lamlist)); //amount of argument
    SET_CDR(val,NIL);
    SET_AUX(val,cstandard_generic_function);
    while(!nullp(body)){
        if(eqp(caar(body),makesym(":METHOD")))
            insert_method(makemethod(cdar(body)),val);

        body = cdr(body);
    }
    return(val);
}
/*
diffrence is class. th class is  generic-function
use in defgeneric*
*/
int makegeneric_star(int lamlist,int body){
    int val;

    val = hfreshcell();
    SET_TAG(val,GENERIC);
    SET_CAR(val,copy_heap(lamlist));
    SET_OPT(val,count_args(lamlist)); //amount of argument
    SET_CDR(val,NIL);
    SET_AUX(val,cgeneric_function); // difference. only this.
    while(!nullp(body)){
        if(eqp(caar(body),makesym(":METHOD")))
            insert_method(makemethod(cdar(body)),val);

        body = cdr(body);
    }
    return(val);
}



/*
method
car = args&body
cdr = environment
aux = null
opt = priority
*/
int makemethod(int addr){
    int val;

    val = hfreshcell();
    SET_TAG(val,METHOD);
    if(eqp(car(addr),makesym(":AROUND"))){
        SET_CAR(val,copy_heap(cdr(addr)));
        SET_OPT(val,AROUND);
    }
    else if(eqp(car(addr),makesym(":BEFORE"))){
        SET_CAR(val,copy_heap(cdr(addr)));
        SET_OPT(val,BEFORE);
    }
    else if(eqp(car(addr),makesym(":AFTER"))){
        SET_CAR(val,copy_heap(cdr(addr)));
        SET_OPT(val,AFTER);
    }
    else{
        SET_CAR(val,copy_heap(addr));
        SET_OPT(val,PRIORITY);
    }
    SET_CDR(val,copy_heap(ep));
    SET_AUX(val,NIL);
    return(val);
}


int makestream(FILE *port, int type){
    int addr;

    addr = freshcell();
    SET_TAG(addr,STREAM);
    SET_PORT(addr,port);
    SET_CDR(addr,0);       //string-stream-position
    SET_AUX(addr,cstream); //class
    SET_OPT(addr,type); //input/output/inout
    return(addr);
}

//--------array-------
int makearray(int ls, int obj){
    int size,res,i,ls1, *vec;

    ls1 = ls;
    if(!nullp(ls)){
        size = 1;
        while(!nullp(ls)){
          int n;
          
            n = GET_INT(car(ls));
            if(n==0)
                n=1;
            size = n * size;
            ls = cdr(ls);
        }
        size++;
    }
    else
        size = 1;

    res = freshcell();
    TRY
        vec = (int *)ALLOC(sizeof(int) * size);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF, "array",  NIL);
    END_TRY;
    SET_VEC(res,vec);
    for(i=0; i<size; i++)
        SET_VEC_ELT(res,i,copy(obj));
    if(nullp(ls1)){
        SET_TAG(res,ARR);
        SET_CDR(res,ls1);
        SET_AUX(res,cgeneral_array_star); //class
    }
    else if(length(ls1) == 1){
        SET_TAG(res,VEC);
        SET_CDR(res,GET_INT(car(ls1)));
        SET_AUX(res,cbasic_vector);
    }
    else{
        SET_TAG(res,ARR);
        SET_CDR(res,ls1);
        SET_AUX(res,cgeneral_array_star); //class
    }

    return(res);
}

// for Deep-Learning float type array
static inline void SET_FVEC(int addr,float *x) { heap[addr].val.car.dyna_fvec = x; }
int makefarray(int ls, int obj){
    int size,res,i,ls1;
    float *vec;

    ls1 = ls;
    if(!nullp(ls)){
        size = 1;
        while(!nullp(ls)){
          int n;
          
            n = GET_INT(car(ls));
            if(n==0)
                n=1;
            size = n * size;
            ls = cdr(ls);
        }
        size++;
    }
    else
        size = 1;

    res = freshcell();
    TRY
        vec = (float *)ALLOC(sizeof(float) * size);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF, "float array",  NIL);
    END_TRY;
    SET_FVEC(res,vec);
    if(eqp(obj,makesym("RAND"))){
        for(i=0; i<size; i++)
            SET_FVEC_ELT(res,i,(float)rand()/RAND_MAX);
    }
    else{
        for(i=0; i<size; i++)
            SET_FVEC_ELT(res,i,GET_FLT(obj));
    }
    SET_TAG(res,FARR);
    SET_CDR(res,ls1);
    SET_AUX(res,cfloat_array); //class
    SET_OPT(res,size); //for GC 
    ac = ac + size;    //remenber allocate size
    return(res);
}


int makestr(const char *string){
    int addr;

    addr = freshcell();
    SET_TAG(addr,STR);
    TRY
        heap[addr].name = Str_dup(string, 1, 0, 1);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF,"makestr",NIL);
    END_TRY;
    SET_AUX(addr,cstring); //class string
    return(addr);
}

int makechar(const char *pname){
    int addr,pos;
    char low_name[SYMSIZE],char_entity;

    
    pos = 0;
    while(pname[pos] != NUL){
        low_name[pos] = tolower(pname[pos]);
        pos++;
    }
    low_name[pos] = NUL;
    char_entity = pname[0];
    
    if(strcmp(low_name,"alarm") == 0){
        char_entity = BEL;
    }
    else if(strcmp(low_name,"backspace") == 0){
        char_entity = BS;
    }
    else if(strcmp(low_name,"delete") == 0){
        char_entity = DEL;
    }
    else if(strcmp(low_name,"escape") == 0){
        char_entity = ESC;
    }
    else if(strcmp(low_name,"return") == 0){
        char_entity = RET;
    }
    else if(strcmp(low_name,"newline") == 0){
        char_entity = EOL;
    }
    else if(strcmp(low_name,"null") == 0){
        char_entity = NUL;
    }
    else if(strcmp(low_name,"space") == 0){
        char_entity = SPACE;
    }
    else if(strcmp(low_name,"tab") == 0){
        char_entity = TAB;
    }

    addr = freshcell();
    SET_TAG(addr,CHR);
    TRY
        heap[addr].name = (char *)ALLOC(CHARSIZE);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF,"makechar",NIL);
    END_TRY;
    heap[addr].name[0] = char_entity;
    heap[addr].name[1] = NUL;
    SET_AUX(addr,ccharacter);
    return(addr);
}

/*
class obj
car = super class
cdr = class variable
aux = method
name = class name
*/
int makeclass(const char *pname, int superclass){
    int addr;

    addr = freshcell();
    SET_TAG(addr,CLASS);
    TRY
        heap[addr].name = Str_dup(pname, 1, 0, 1);
    EXCEPT(Mem_Failed)
        error(MALLOC_OVERF,"makeclass",NIL);
    END_TRY;
    SET_CAR(addr,superclass);
    SET_CDR(addr,NIL);
    SET_AUX(addr,NIL);
    return(addr);
}

/*
initls ((format-string a)(format-argments b))...(initarg var) )
*/
int makeinstance(int cl ,int initls){
    int addr;

    addr = freshcell();
    SET_TAG(addr,INSTANCE);
    SET_CAR(addr,GET_CAR(cl));  //super class
    SET_CDR(addr,slotvars(cl)); //slot vars with super class
    SET_AUX(addr,cl);           //class of instance
    while(!nullp(initls)){
        setval(cdr(assq(car(initls),GET_AUX(cl))),cadr(initls),GET_CDR(addr));
        initls = cddr(initls);
    }
    return(addr);
}

int slotvars(int x){
    if(nullp(x))
        return(NIL);
    else if(atomp(x) && nullp(GET_CAR(x)))
        return(copy(GET_CDR(x)));
    else if(atomp(x) && atomp(GET_CAR(x)))
        return(append(copy(GET_CDR(x)),copy(GET_CDR(GET_CAR(x)))));
    else if(atomp(x) && listp(GET_CAR(x)))
        return(append(copy(GET_CDR(x)),slotvars(GET_CAR(x))));
    else
        return(append(slotvars(GET_AUX(car(x))),slotvars(cdr(x))));
}



//initialize instance
int initinst(int x, int initls){
    int cl,class_vars,inst_vars,initargs,n;

    cl = GET_AUX(x);
    class_vars = GET_CDR(cl);
    inst_vars = GET_CDR(x);
    initargs = GET_AUX(cl);
    while(!nullp(class_vars)){
        if((n=assq(caar(class_vars),inst_vars)))
            SET_CDR(n,copy(cdar(class_vars)));
        class_vars = cdr(class_vars);
    }
    while(!nullp(initls)){
        n=assq(car(initls),initargs);
        if(n != 0 && n != FAILSE) {
            int n2 = assq(GET_CDR(n),inst_vars);
            if (n2 != 0 && n2 != FAILSE) {
                SET_CDR(n2,cadr(initls));
            }
        }
        initls = cddr(initls);
    }
    SET_CDR(x,initinst1(inst_vars,GET_CAR(cl)));
    return(x);
}

//initialize variables of super class of instance
int initinst1(int inst_vars, int sc){
    int class_vars;

    if(nullp(sc))
        return(inst_vars);
    else if(atomp(sc) && nullp(GET_CAR(sc))){
        class_vars = GET_AUX(sc);
        return(initinst2(inst_vars,class_vars));
    }
    else if(atomp(sc) && atomp(GET_CAR(sc))){
        class_vars = GET_AUX(sc);
        return(initinst1(initinst2(inst_vars,class_vars),GET_AUX(GET_CAR(sc))));
    }
    else{
        return(initinst1(initinst1(inst_vars,car(sc)),cdr(sc)));
    }
}

int initinst2(int inst_vars, int class_vars){
    while(!nullp(class_vars)){
        int n;

        n=assq(caar(class_vars),inst_vars);
        if(n != 0 && n != FAILSE) {
                SET_CDR(n,copy(cdar(class_vars)));
        }
        class_vars = cdr(class_vars);
    }
    return(inst_vars);
}

int makedummy(void){
    int res;

    res = freshcell();
    SET_TAG(res,DUMMY);
    SET_AUX(res,cnull);
    return(res);
}

//-----for FAST compiler------
int get_aux(int x){
	return(GET_AUX(x));
}


int set_car(int x, int y){
    SET_CAR(x,y);
    return(y);
}

int set_cdr(int x, int y){
    SET_CDR(x,y);
    return(y);
}

int set_aux(int x, int y){
    SET_AUX(x,y);
    return(y);
}

int set_opt(int x, int y){
    SET_OPT(x,y);
    return(x);
}

int set_prop(int x, int y){
	SET_PROP(x,y);
    return(y);
}

int set_dynpt(int x){
	dp = x;
    return(x);
}


int get_opt(int x){
	return(GET_OPT(x));
}


int get_prop(int x){
	return(GET_PROP(x));
}

int get_dynpt(void){
	return(dp);
}


int callsubr(int func, int arglist){
    return((GET_SUBR(func))(arglist));
}

int makeintlong(int n){
    int addr;

    addr = freshcell();
    SET_TAG(addr,LONGN);
    SET_LONG(addr,(long long int)n);
    SET_AUX(addr,cinteger); //class integer
    return(addr);
}

int makestrflt(const char *str){
    return(makeflt(atof(str)));
}

int makedoubleflt(double x){
    return(makeflt(x));
}

int makestrlong(const char *str){
    return(makelong(atol(str)));
}

static inline int HexDigitToNybble(char c){
    if (!isdigit(c)){
        static const int codesToSkip = 'A' - '9' - 1;
        c -= codesToSkip;
    }
    return c - '0';
}
int makefaststrlong(const char *str){
    uint64_t u = 0;
    for (int i = 0; i < 8; i++){
        uint8_t hi_nybble = HexDigitToNybble(str[14 - (i << 1)]);
        uint8_t lo_nybble = HexDigitToNybble(str[15 - (i << 1)]);
        uint64_t byte = (hi_nybble << 4) | lo_nybble;
        u |= (byte << (i << 3));
    }
    return makelong(u);
}

int nth_cdr(int n, int x){
	if(n == 0)
		return(x);
    else
        return(nth_cdr(n-1,cdr(x)));
}


int convert(int arg1, int arg2){
    char str[STRSIZE];

    switch(GET_TAG(arg1)){
        case INTN:
            if(GET_AUX(arg2) == ccharacter){
                str[0] = GET_INT(arg1);
                str[1] = NUL;
                return(makechar(str));
            }
            else if(GET_AUX(arg2) == cfloat){
                return(exact_to_inexact(arg1));
            }
            else if(GET_AUX(arg2) == cstring){
                Fmt_sfmt(str, STRSIZE, "%d",GET_INT(arg1));
                return(makestr(str));
            }
            break;
        case CHR:
            if(GET_AUX(arg2) == cinteger){
                return(makeint(STRING_REF(arg1,0)));
            }
            else if(GET_AUX(arg2) == csymbol){
                return(makesym(GET_NAME(arg1)));
            }
            else if(GET_AUX(arg2) == cstring){
                return(makestr(GET_NAME(arg1)));
            }
            else if(GET_AUX(arg2) == ccharacter){
                return(arg1);
            }
            break;
        case FLTN:
            if(GET_AUX(arg2) == cinteger){
                return(makeint((int)GET_FLT(arg1)));
            }
            else if(GET_AUX(arg2) == cstring){
              double x;
              
                x = GET_FLT(arg1);
                if(x - ceil(x) != 0 ||  x >= SMALL_INT_MAX)
                    Fmt_sfmt(str, STRSIZE, "%0.16g", x);
                else
                    Fmt_sfmt(str, STRSIZE, "%0.1f", x);
                return(makestr(str));
            }
            break;
        case SYM:
            if(GET_AUX(arg2) == cstring){
                return(makestr(GET_NAME(arg1)));
            }
            break;
        case STR:
            if(GET_AUX(arg2) == cinteger){
                return(makeint(atoi(GET_NAME(arg1))));
            }
            else if(GET_AUX(arg2) == cfloat){
                return(makeflt(atof(GET_NAME(arg1))));
            }
            else if(GET_AUX(arg2) == csymbol){
                return(makesym(GET_NAME(arg1)));
            }
            else if(GET_AUX(arg2) == cgeneral_vector){
                return(string_to_vector(arg1));
            }
            else if(GET_AUX(arg2) == clist){
                return(string_to_list(arg1));
            }
            break;
        case LIS:
            if(GET_AUX(arg2) == cgeneral_vector){
                return(vector(arg1));
            }
            break;
        case VEC:
            if(GET_AUX(arg2) == clist){
                return(vector_to_list(arg1));
            }
            break;
    default:
        IP(false, "convert tag switch default action");
    }
    error(ILLEGAL_ARGS,"convert",arg1);
    return(UNDEF);
}

int adaptp(int x, int y){

    if(!CELLRANGE(x)){
    	if(32 == GET_AUX(y))  // 32is address of <class integer>
        	return(1);
        else if(subclassp(32,GET_AUX(y)))
        	return(1);
        else
        	return(0);
    }
    if (x >= CELLSIZE) {
      error(ILLEGAL_ARGS, "adaptp", x);
      return(0);
    } else if(GET_AUX(x) == GET_AUX(y))
    	return(1);
    else if(subclassp(GET_AUX(x),GET_AUX(y)))
    	return(1);
    else
    	return(0);
}

int fast_length(int x){
	int res;

    if(!listp(x) && !vectorp(x) && !stringp(x)){
        error(ILLEGAL_ARGS, "length", x);
    }

    if(listp(x))
        res = length(x);
    else if(vectorp(x))
        res = vector_length(x);
    else
        res = string_length(x);

    return(INT_FLAG | res);
}


int fast_car(int x){
	if(!(IS_LIST(x)))
    	error(NOT_LIST, "car", x);
    if(IS_NIL(x))
    	error(NOT_LIST, "car", x);

    return(GET_CAR(x));
}


int fast_cdr(int x){
	if(!(IS_LIST(x)))
    	error(NOT_LIST, "cdr", x);
    if(IS_NIL(x))
    	error(NOT_LIST, "cdr", x);

    return(GET_CDR(x));
}


int set_dynamic(int x, int y){
	if(finddyn(x) != FAILSE)
        setdynenv(x,y);
    else
    	error(UNDEF_VAR, "set-dynamic", x);

    return(y);
}

int set_catch_symbols(int x){
    catch_symbols = x;
    return(x);
}


char* get_name(int x){
    return(GET_NAME(x));
}

double get_flt(int x){
    return(GET_FLT(x));
}
