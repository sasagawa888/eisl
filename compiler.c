#include "fast.h"
jmp_buf c_EXIT_ARG[50];
jmp_buf c_EXIT_FOR[50];
jmp_buf c_EXIT_LET[50];
jmp_buf c_EXIT_ALL[50];
jmp_buf c_EXIT_INFERENCE[50];
jmp_buf c_EXIT[50];
int f_ANY(int arglist);int ANY(int F,int LS);
int f_EVERY(int arglist);int EVERY(int F,int LS);
int f_TAKE(int arglist);int TAKE(int N,int LS);
int f_DROP(int arglist);int DROP(int N,int LS);
int f_LAST(int arglist);int LAST(int LS);
int f_SECOND_LAST(int arglist);int SECOND_LAST(int LS);
int f_REMOVE(int arglist);int REMOVE(int X,int LS);
int f_APPENDexclamation(int arglist);int APPENDexclamation(int X,int Y);
int f_POSITION(int arglist);int POSITION(int X,int LS);
int f_FILENAME(int arglist);int FILENAME(int STR);
int f_FILENAME1(int arglist);int FILENAME1(int STR);
int f_FILENAME2(int arglist);int FILENAME2(int STR);
int f_DROPSTRING(int arglist);int DROPSTRING(int STR,int N);
int f_SUBSTRING(int arglist);int SUBSTRING(int STR,int M,int N);
int f_SUBST(int arglist);int SUBST(int VARS);
int f_ALPHA_CONV(int arglist);int ALPHA_CONV(int X,int VARS,int SUBST);
int f_NTH(int arglist);int NTH(int X,int N);
int f_ERRORstar(int arglist);int ERRORstar(int STR,int X);
int f_COMPILE_FILE(int arglist);int COMPILE_FILE(int X);
int f_compiler0(int arglist);int compiler0();
int f_COMPILE_FILE1(int arglist);int COMPILE_FILE1(int X);
int f_COMPILE_FILEstar(int arglist);int COMPILE_FILEstar(int X);
int f_COMPILE_CUDA(int arglist);int COMPILE_CUDA(int X);
int f_compiler1(int arglist);int compiler1();
int f_COMPILE_CUDA1(int arglist);int COMPILE_CUDA1(int X);
int f_PASS1(int arglist);int PASS1(int X);
int f_CHECK_ARGS_COUNT(int arglist);int CHECK_ARGS_COUNT(int X);
int f_FIND_CATCH_BLOCK_TAG(int arglist);int FIND_CATCH_BLOCK_TAG(int X);
int f_PASS2(int arglist);int PASS2(int X);
int f_COUNT_ARGS(int arglist);int COUNT_ARGS(int LS);
int f_COMPILE(int arglist);int COMPILE(int X);
int f_COMP(int arglist);int COMP(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_INITIALIZE(int arglist);int INITIALIZE();
int f_DECLARE_CATCH_BLOCK_BUFFER(int arglist);int DECLARE_CATCH_BLOCK_BUFFER();
int f_FINALIZE(int arglist);int FINALIZE(int X,int EXT);
int f_COMP_DEFUN(int arglist);int COMP_DEFUN(int X);
int f_COMP_LAMBDA(int arglist);int COMP_LAMBDA(int X,int ENV,int GLOBAL);
int f_LAMBDA_NAME(int arglist);int LAMBDA_NAME();
int f_COMP_DEFGENERIC(int arglist);int COMP_DEFGENERIC(int X);
int f_COMP_DEFUN0(int arglist);int COMP_DEFUN0(int X);
int f_COMP_LAMBDA0(int arglist);int COMP_LAMBDA0(int X,int NAME);
int f_COMP_DEFGENERIC0(int arglist);int COMP_DEFGENERIC0(int X);
int f_COMP_DEFUN1(int arglist);int COMP_DEFUN1(int X);
int f_COMP_LAMBDA1(int arglist);int COMP_LAMBDA1(int X,int NAME);
int f_COMP_DEFGENERIC1(int arglist);int COMP_DEFGENERIC1(int X);
int f_COMP_DEFUN2(int arglist);int COMP_DEFUN2(int X);
int f_COMP_LAMBDA2(int arglist);int COMP_LAMBDA2(int BODY,int ENV,int ARGS,int NAME,int CLOS);
int f_LAMBDA_STREAM_CALLEE(int arglist);int LAMBDA_STREAM_CALLEE();
int f_LAMBDA_STREAM_CALLER(int arglist);int LAMBDA_STREAM_CALLER(int GLOBAL);
int f_FIND_FREE_VARIABLE(int arglist);int FIND_FREE_VARIABLE(int X,int ENV,int ARGS);
int f_FIND_FREE_VARIABLE1(int arglist);int FIND_FREE_VARIABLE1(int X,int ENV,int ARGS);
int f_FREE_VARIABLE_LIST(int arglist);int FREE_VARIABLE_LIST(int STREAM,int X);
int f_COMP_DEFGENERIC2(int arglist);int COMP_DEFGENERIC2(int X);
int f_VARLIS_TO_LAMBDA_ARGS(int arglist);int VARLIS_TO_LAMBDA_ARGS(int X);
int f_COMP_DEFGENERIC_BODY(int arglist);int COMP_DEFGENERIC_BODY(int X,int AFTER);
int f_METHOD_NEED_RETURN_P(int arglist);int METHOD_NEED_RETURN_P(int X);
int f_METHOD_NEED_RETURN_P1(int arglist);int METHOD_NEED_RETURN_P1(int X);
int f_COMP_DEFGENERIC_COND(int arglist);int COMP_DEFGENERIC_COND(int X);
int f_COMP_DEFGENERIC_COND1(int arglist);int COMP_DEFGENERIC_COND1(int X);
int f_COMP_DEFUN3(int arglist);int COMP_DEFUN3(int X);
int f_COMP_LAMBDA3(int arglist);int COMP_LAMBDA3(int NAME);
int f_COMP_DEFGENERIC3(int arglist);int COMP_DEFGENERIC3(int X);
int f_GEN_ARG1(int arglist);int GEN_ARG1(int N);
int f_GEN_ARG2(int arglist);int GEN_ARG2(int STREAM,int LS);
int f_GEN_ARG3(int arglist);int GEN_ARG3(int N);
int f_GEN_ASSIGN(int arglist);int GEN_ASSIGN(int N);
int f_GEN_CALL(int arglist);int GEN_CALL(int NAME,int N);
int f_GEN_SHELTERPUSH(int arglist);int GEN_SHELTERPUSH(int STREAM,int LS);
int f_GEN_SHELTERPOP(int arglist);int GEN_SHELTERPOP(int STREAM,int LS);
int f_GEN_CHECKGC(int arglist);int GEN_CHECKGC();
int f_COMP_IF(int arglist);int COMP_IF(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_NUMERIC(int arglist);int COMP_NUMERIC(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FUNCALL(int arglist);int COMP_FUNCALL(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FUNCALL_CLANG(int arglist);int COMP_FUNCALL_CLANG(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FUNCALL_CLANG1(int arglist);int COMP_FUNCALL_CLANG1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FUNCALL1(int arglist);int COMP_FUNCALL1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FUNCALL2(int arglist);int COMP_FUNCALL2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_SUBRCALL(int arglist);int COMP_SUBRCALL(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_SUBRCALL1(int arglist);int COMP_SUBRCALL1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_SUBRCALL2(int arglist);int COMP_SUBRCALL2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_SUBRCALL3(int arglist);int COMP_SUBRCALL3(int STREAM,int M,int N);
int f_COMP_LABELS(int arglist);int COMP_LABELS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_LABELS1(int arglist);int COMP_LABELS1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_LABELS2(int arglist);int COMP_LABELS2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_LET(int arglist);int COMP_LET(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_LETstar(int arglist);int COMP_LETstar(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_NOT_NEED_RES_P(int arglist);int NOT_NEED_RES_P(int X);
int f_NOT_NEED_COLON_P(int arglist);int NOT_NEED_COLON_P(int X);
int f_TAILCALLP(int arglist);int TAILCALLP(int X,int TAIL,int NAME);
int f_COMP_LET1(int arglist);int COMP_LET1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_LET2(int arglist);int COMP_LET2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_COND(int arglist);int COMP_COND(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_COND1(int arglist);int COMP_COND1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_COND2(int arglist);int COMP_COND2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CASE(int arglist);int COMP_CASE(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CASE1(int arglist);int COMP_CASE1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS,int KEY);
int f_COMP_CASE_USING(int arglist);int COMP_CASE_USING(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CASE_USING1(int arglist);int COMP_CASE_USING1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS,int KEY,int PRED);
int f_HAS_TAIL_RECUR_P(int arglist);int HAS_TAIL_RECUR_P(int X,int NAME);
int f_HAS_TAIL_RECUR_P1(int arglist);int HAS_TAIL_RECUR_P1(int X,int NAME);
int f_compiler2(int arglist);int compiler2(int Y);
int f_COMP_FOR(int arglist);int COMP_FOR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_compiler3(int arglist);int compiler3(int X);
int f_compiler4(int arglist);int compiler4(int X);
int f_COMP_FOR1(int arglist);int COMP_FOR1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FOR2(int arglist);int COMP_FOR2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FOR3(int arglist);int COMP_FOR3(int VARS,int VAR,int SUBST);
int f_compiler5(int arglist);int compiler5(int X);
int f_COMP_PROGN(int arglist);int COMP_PROGN(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_PROGN1(int arglist);int COMP_PROGN1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_AND(int arglist);int COMP_AND(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_AND1(int arglist);int COMP_AND1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_OR(int arglist);int COMP_OR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_OR1(int arglist);int COMP_OR1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_TEST_AND(int arglist);int COMP_TEST_AND(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_TEST_AND1(int arglist);int COMP_TEST_AND1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_TEST_OR(int arglist);int COMP_TEST_OR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_TEST_OR1(int arglist);int COMP_TEST_OR1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_WHILE(int arglist);int COMP_WHILE(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_SETQ(int arglist);int COMP_SETQ(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_TAGBODY(int arglist);int COMP_TAGBODY(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_TAGBODY1(int arglist);int COMP_TAGBODY1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_GO(int arglist);int COMP_GO(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CONVERT(int arglist);int COMP_CONVERT(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_FUNCTION(int arglist);int COMP_FUNCTION(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_SYMBOL_FUNCTION(int arglist);int COMP_SYMBOL_FUNCTION(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CLASS(int arglist);int COMP_CLASS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_SYMBOL_CLASS(int arglist);int COMP_SYMBOL_CLASS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CATCH(int arglist);int COMP_CATCH(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_THROW(int arglist);int COMP_THROW(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_BLOCK(int arglist);int COMP_BLOCK(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_RETURN_FROM(int arglist);int COMP_RETURN_FROM(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_UNWIND_PROTECT(int arglist);int COMP_UNWIND_PROTECT(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_UNWIND_PROTECT1(int arglist);int COMP_UNWIND_PROTECT1(int BODY,int ENV);
int f_COMP_SETF(int arglist);int COMP_SETF(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_DYNAMIC(int arglist);int COMP_DYNAMIC(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_DYNAMIC_LET(int arglist);int COMP_DYNAMIC_LET(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_DYNAMIC_LET1(int arglist);int COMP_DYNAMIC_LET1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_DYNAMIC_LET2(int arglist);int COMP_DYNAMIC_LET2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_NOT(int arglist);int COMP_NOT(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CAR(int arglist);int COMP_CAR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CDR(int arglist);int COMP_CDR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_CONS(int arglist);int COMP_CONS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_LENGTH(int arglist);int COMP_LENGTH(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_C_INCLUDE(int arglist);int COMP_C_INCLUDE(int X);
int f_COMP_C_DEFINE(int arglist);int COMP_C_DEFINE(int X);
int f_COMP_C_LANG(int arglist);int COMP_C_LANG(int X);
int f_COMP_C_OPTION(int arglist);int COMP_C_OPTION(int X);
int f_COMP_DEFGLOBAL(int arglist);int COMP_DEFGLOBAL(int X);
int f_COMP_DEFCONSTANT(int arglist);int COMP_DEFCONSTANT(int X);
int f_COMP_DEFDYNAMIC(int arglist);int COMP_DEFDYNAMIC(int X);
int f_COMP_SET_DYNAMIC(int arglist);int COMP_SET_DYNAMIC(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS);
int f_COMP_DEFMACRO(int arglist);int COMP_DEFMACRO(int X);
int f_COMP_DEFCLASS(int arglist);int COMP_DEFCLASS(int X);
int f_COMP_DEFMETHOD(int arglist);int COMP_DEFMETHOD(int X);
int f_HAS_SAME_VARLIS_P(int arglist);int HAS_SAME_VARLIS_P(int X,int Y);
int f_CONV_NAME(int arglist);int CONV_NAME(int SYM);
int f_CONV_NAME1(int arglist);int CONV_NAME1(int LS);
int f_CONV_NAME2(int arglist);int CONV_NAME2(int LS);
int f_LIST_TO_C(int arglist);int LIST_TO_C(int STREAM,int X);
int f_LIST_TO_C1(int arglist);int LIST_TO_C1(int STREAM,int X);
int f_QUASI_TRANSFER(int arglist);int QUASI_TRANSFER(int X,int N);
int f_OPTIMIZE_P(int arglist);int OPTIMIZE_P(int X);
int f_OPTIMIZE_P1(int arglist);int OPTIMIZE_P1(int X);
int f_RETURN_TYPE(int arglist);int RETURN_TYPE(int X);
int f_ARGUMENT_TYPE(int arglist);int ARGUMENT_TYPE(int X);
int f_LOCAL_RETURN_TYPE(int arglist);int LOCAL_RETURN_TYPE(int X,int Y);
int f_LOCAL_ARGUMENT_TYPE(int arglist);int LOCAL_ARGUMENT_TYPE(int X,int Y);
int f_TYPE_GEN_ARG2(int arglist);int TYPE_GEN_ARG2(int STREAM,int LS,int TYPE);
int f_TYPE_GEN_ARG3(int arglist);int TYPE_GEN_ARG3(int N,int LS);
int f_TYPE_GEN_CALL(int arglist);int TYPE_GEN_CALL(int NAME,int N);
int f_SUBSETP(int arglist);int SUBSETP(int X,int Y);
int f_CLASS_DYNAMIC(int arglist);int CLASS_DYNAMIC(int C);
int f_WARNING(int arglist);int WARNING(int STR,int X);
int f_INFERENCE_FILE(int arglist);int INFERENCE_FILE(int X);
int f_INFERENCE_DEFUN(int arglist);int INFERENCE_DEFUN(int X);
int f_INFERENCE_LABELS(int arglist);int INFERENCE_LABELS(int X,int TYPE_ENV);
int f_FIND_ARGUMENT_CLASS(int arglist);int FIND_ARGUMENT_CLASS(int LS,int TYPE_ENV);
int f_CREATE_INIT_ENV(int arglist);int CREATE_INIT_ENV(int LS);
int f_INFERENCE(int arglist);int INFERENCE(int X,int TYPE_ENV);
int f_INFERENCE_ALL(int arglist);int INFERENCE_ALL(int X,int TYPE_ENV,int FN,int LOCAL);
int f_INFERENCE_ALL1(int arglist);int INFERENCE_ALL1(int X,int TYPE_ENV,int FN);
int f_INFERENCE_COND(int arglist);int INFERENCE_COND(int X,int TYPE_ENV);
int f_INFERENCE_COND1(int arglist);int INFERENCE_COND1(int X,int TYPE_ENV);
int f_INFERENCE_COND2(int arglist);int INFERENCE_COND2(int X,int TYPE_ENV);
int f_INFERENCE_CASE(int arglist);int INFERENCE_CASE(int X,int TYPE_ENV);
int f_INFERENCE_CASE1(int arglist);int INFERENCE_CASE1(int X,int TYPE_ENV);
int f_INFERENCE_CASE2(int arglist);int INFERENCE_CASE2(int X,int TYPE_ENV);
int f_INFERENCE_IF(int arglist);int INFERENCE_IF(int X,int TYPE_ENV);
int f_INFERENCE_IF1(int arglist);int INFERENCE_IF1(int X,int TYPE_ENV);
int f_INFERENCE_IF2(int arglist);int INFERENCE_IF2(int X,int TYPE_ENV);
int f_INFERENCE_NUMERIC(int arglist);int INFERENCE_NUMERIC(int X,int TYPE_ENV);
int f_compiler6(int arglist);int compiler6(int X);
int f_compiler7(int arglist);int compiler7(int X);
int f_compiler8(int arglist);int compiler8(int X);
int f_compiler9(int arglist);int compiler9(int X);
int f_compiler10(int arglist);int compiler10(int X);
int f_INFERENCE_LET(int arglist);int INFERENCE_LET(int X,int TYPE_ENV);
int f_INFERENCE_FOR(int arglist);int INFERENCE_FOR(int X,int TYPE_ENV);
int f_INFERENCE_WHILE(int arglist);int INFERENCE_WHILE(int X,int TYPE_ENV);
int f_INFERENCE_WHILE1(int arglist);int INFERENCE_WHILE1(int X,int TYPE_ENV);
int f_INFERENCE_FUNCTION(int arglist);int INFERENCE_FUNCTION(int X,int TYPE_ENV);
int f_FIND_FUNCTION_TYPE(int arglist);int FIND_FUNCTION_TYPE(int X);
int f_INFERENCE_ARG(int arglist);int INFERENCE_ARG(int X,int Y,int TYPE_ENV);
int f_FUNCTION_TYPE_OBJECT_P(int arglist);int FUNCTION_TYPE_OBJECT_P(int X);
int f_FIND_CLASS(int arglist);int FIND_CLASS(int X,int TYPE_ENV);
int f_FIND_CLASS_IF(int arglist);int FIND_CLASS_IF(int X,int TYPE_ENV);
int f_FIND_CLASS_COND(int arglist);int FIND_CLASS_COND(int X,int TYPE_ENV);
int f_FIND_CLASS_NUMERIC(int arglist);int FIND_CLASS_NUMERIC(int X,int TYPE_ENV);
int f_compiler11(int arglist);int compiler11(int X);
int f_compiler12(int arglist);int compiler12(int X);
int f_compiler13(int arglist);int compiler13(int X);
int f_compiler14(int arglist);int compiler14(int X);
int f_compiler15(int arglist);int compiler15(int X);
int f_REFER(int arglist);int REFER(int X,int TYPE_ENV);
int f_SET_TYPE_FUNCTION_OUTPUT(int arglist);int SET_TYPE_FUNCTION_OUTPUT(int FN,int Y);
int f_SET_TYPE_FUNCTION_INPUT(int arglist);int SET_TYPE_FUNCTION_INPUT(int FN,int Y);
int f_ADD_TYPE_FUNCTION_LOCAL(int arglist);int ADD_TYPE_FUNCTION_LOCAL(int FN);
int f_SET_LOCAL_TYPE_FUNCTION_OUTPUT(int arglist);int SET_LOCAL_TYPE_FUNCTION_OUTPUT(int FN,int Y);
int f_SET_LOCAL_TYPE_FUNCTION_INPUT(int arglist);int SET_LOCAL_TYPE_FUNCTION_INPUT(int FN,int Y);
int f_TYPE_FUNCTION_P(int arglist);int TYPE_FUNCTION_P(int X);
int f_UNIFY(int arglist);int UNIFY(int X,int Y,int TYPE_ENV);
int f_VARIABLEP(int arglist);int VARIABLEP(int X);
int f_SUBCLASSPstar(int arglist);int SUBCLASSPstar(int X,int Y);
int f_ESTIMATE(int arglist);int ESTIMATE(int LS,int CLASS,int TYPE_ENV);
int f_CLASSstar(int arglist);int CLASSstar(int X);
int f_ANY(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ANY(fast_convert(arg1),fast_convert(arg2))));
}
int f_EVERY(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(EVERY(fast_convert(arg1),fast_convert(arg2))));
}
int f_TAKE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TAKE(fast_convert(arg1),fast_convert(arg2))));
}
int f_DROP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DROP(fast_convert(arg1),fast_convert(arg2))));
}
int f_LAST(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LAST(fast_convert(arg1))));
}
int f_SECOND_LAST(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SECOND_LAST(fast_convert(arg1))));
}
int f_REMOVE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(REMOVE(fast_convert(arg1),fast_convert(arg2))));
}
int f_APPENDexclamation(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(APPENDexclamation(fast_convert(arg1),fast_convert(arg2))));
}
int f_POSITION(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(POSITION(fast_convert(arg1),fast_convert(arg2))));
}
int f_FILENAME(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FILENAME(fast_convert(arg1))));
}
int f_FILENAME1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FILENAME1(fast_convert(arg1))));
}
int f_FILENAME2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FILENAME2(fast_convert(arg1))));
}
int f_DROPSTRING(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DROPSTRING(fast_convert(arg1),fast_convert(arg2))));
}
int f_SUBSTRING(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(SUBSTRING(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_SUBST(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SUBST(fast_convert(arg1))));
}
int f_ALPHA_CONV(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(ALPHA_CONV(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_NTH(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(NTH(fast_convert(arg1),fast_convert(arg2))));
}
int f_ERRORstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ERRORstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_COMPILE_FILE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMPILE_FILE(fast_convert(arg1))));
}
int f_compiler0(int arglist){
return(fast_inverse(compiler0() ));
}
int f_COMPILE_FILE1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMPILE_FILE1(fast_convert(arg1))));
}
int f_COMPILE_FILEstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMPILE_FILEstar(fast_convert(arg1))));
}
int f_COMPILE_CUDA(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMPILE_CUDA(fast_convert(arg1))));
}
int f_compiler1(int arglist){
return(fast_inverse(compiler1() ));
}
int f_COMPILE_CUDA1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMPILE_CUDA1(fast_convert(arg1))));
}
int f_PASS1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PASS1(fast_convert(arg1))));
}
int f_CHECK_ARGS_COUNT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CHECK_ARGS_COUNT(fast_convert(arg1))));
}
int f_FIND_CATCH_BLOCK_TAG(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIND_CATCH_BLOCK_TAG(fast_convert(arg1))));
}
int f_PASS2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PASS2(fast_convert(arg1))));
}
int f_COUNT_ARGS(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COUNT_ARGS(fast_convert(arg1))));
}
int f_COMPILE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMPILE(fast_convert(arg1))));
}
int f_COMP(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_INITIALIZE(int arglist){
return(fast_inverse(INITIALIZE() ));
}
int f_DECLARE_CATCH_BLOCK_BUFFER(int arglist){
return(fast_inverse(DECLARE_CATCH_BLOCK_BUFFER() ));
}
int f_FINALIZE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FINALIZE(fast_convert(arg1),fast_convert(arg2))));
}
int f_COMP_DEFUN(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFUN(fast_convert(arg1))));
}
int f_COMP_LAMBDA(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(COMP_LAMBDA(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_LAMBDA_NAME(int arglist){
return(fast_inverse(LAMBDA_NAME() ));
}
int f_COMP_DEFGENERIC(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGENERIC(fast_convert(arg1))));
}
int f_COMP_DEFUN0(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFUN0(fast_convert(arg1))));
}
int f_COMP_LAMBDA0(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(COMP_LAMBDA0(fast_convert(arg1),fast_convert(arg2))));
}
int f_COMP_DEFGENERIC0(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGENERIC0(fast_convert(arg1))));
}
int f_COMP_DEFUN1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFUN1(fast_convert(arg1))));
}
int f_COMP_LAMBDA1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(COMP_LAMBDA1(fast_convert(arg1),fast_convert(arg2))));
}
int f_COMP_DEFGENERIC1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGENERIC1(fast_convert(arg1))));
}
int f_COMP_DEFUN2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFUN2(fast_convert(arg1))));
}
int f_COMP_LAMBDA2(int arglist){
int arg1,arg2,arg3,arg4,arg5;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
return(fast_inverse(COMP_LAMBDA2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5))));
}
int f_LAMBDA_STREAM_CALLEE(int arglist){
return(fast_inverse(LAMBDA_STREAM_CALLEE() ));
}
int f_LAMBDA_STREAM_CALLER(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LAMBDA_STREAM_CALLER(fast_convert(arg1))));
}
int f_FIND_FREE_VARIABLE(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(FIND_FREE_VARIABLE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_FIND_FREE_VARIABLE1(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(FIND_FREE_VARIABLE1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_FREE_VARIABLE_LIST(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FREE_VARIABLE_LIST(fast_convert(arg1),fast_convert(arg2))));
}
int f_COMP_DEFGENERIC2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGENERIC2(fast_convert(arg1))));
}
int f_VARLIS_TO_LAMBDA_ARGS(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(VARLIS_TO_LAMBDA_ARGS(fast_convert(arg1))));
}
int f_COMP_DEFGENERIC_BODY(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(COMP_DEFGENERIC_BODY(fast_convert(arg1),fast_convert(arg2))));
}
int f_METHOD_NEED_RETURN_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(METHOD_NEED_RETURN_P(fast_convert(arg1))));
}
int f_METHOD_NEED_RETURN_P1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(METHOD_NEED_RETURN_P1(fast_convert(arg1))));
}
int f_COMP_DEFGENERIC_COND(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGENERIC_COND(fast_convert(arg1))));
}
int f_COMP_DEFGENERIC_COND1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGENERIC_COND1(fast_convert(arg1))));
}
int f_COMP_DEFUN3(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFUN3(fast_convert(arg1))));
}
int f_COMP_LAMBDA3(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_LAMBDA3(fast_convert(arg1))));
}
int f_COMP_DEFGENERIC3(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGENERIC3(fast_convert(arg1))));
}
int f_GEN_ARG1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GEN_ARG1(fast_convert(arg1))));
}
int f_GEN_ARG2(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(GEN_ARG2(fast_convert(arg1),fast_convert(arg2))));
}
int f_GEN_ARG3(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GEN_ARG3(fast_convert(arg1))));
}
int f_GEN_ASSIGN(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GEN_ASSIGN(fast_convert(arg1))));
}
int f_GEN_CALL(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(GEN_CALL(fast_convert(arg1),fast_convert(arg2))));
}
int f_GEN_SHELTERPUSH(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(GEN_SHELTERPUSH(fast_convert(arg1),fast_convert(arg2))));
}
int f_GEN_SHELTERPOP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(GEN_SHELTERPOP(fast_convert(arg1),fast_convert(arg2))));
}
int f_GEN_CHECKGC(int arglist){
return(fast_inverse(GEN_CHECKGC() ));
}
int f_COMP_IF(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_IF(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_NUMERIC(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_NUMERIC(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FUNCALL(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FUNCALL(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FUNCALL_CLANG(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FUNCALL_CLANG(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FUNCALL_CLANG1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FUNCALL_CLANG1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FUNCALL1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FUNCALL1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FUNCALL2(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FUNCALL2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_SUBRCALL(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SUBRCALL(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_SUBRCALL1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SUBRCALL1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_SUBRCALL2(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SUBRCALL2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_SUBRCALL3(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(COMP_SUBRCALL3(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_COMP_LABELS(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LABELS(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_LABELS1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LABELS1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_LABELS2(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LABELS2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_LET(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LET(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_LETstar(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LETstar(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_NOT_NEED_RES_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(NOT_NEED_RES_P(fast_convert(arg1))));
}
int f_NOT_NEED_COLON_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(NOT_NEED_COLON_P(fast_convert(arg1))));
}
int f_TAILCALLP(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(TAILCALLP(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_COMP_LET1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LET1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_LET2(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LET2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_COND(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_COND(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_COND1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_COND1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_COND2(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_COND2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CASE(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CASE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CASE1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
arg10 = Fnth(9,arglist);
return(fast_inverse(COMP_CASE1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9),fast_convert(arg10))));
}
int f_COMP_CASE_USING(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CASE_USING(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CASE_USING1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
arg10 = Fnth(9,arglist);
arg11 = Fnth(10,arglist);
return(fast_inverse(COMP_CASE_USING1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9),fast_convert(arg10),fast_convert(arg11))));
}
int f_HAS_TAIL_RECUR_P(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(HAS_TAIL_RECUR_P(fast_convert(arg1),fast_convert(arg2))));
}
int f_HAS_TAIL_RECUR_P1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(HAS_TAIL_RECUR_P1(fast_convert(arg1),fast_convert(arg2))));
}
int f_compiler2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler2(fast_convert(arg1))));
}
int f_COMP_FOR(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FOR(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_compiler3(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler3(fast_convert(arg1))));
}
int f_compiler4(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler4(fast_convert(arg1))));
}
int f_COMP_FOR1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FOR1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FOR2(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FOR2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FOR3(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(COMP_FOR3(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_compiler5(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler5(fast_convert(arg1))));
}
int f_COMP_PROGN(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_PROGN(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_PROGN1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_PROGN1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_AND(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_AND(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_AND1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_AND1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_OR(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_OR(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_OR1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_OR1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_TEST_AND(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_TEST_AND(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_TEST_AND1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_TEST_AND1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_TEST_OR(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_TEST_OR(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_TEST_OR1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_TEST_OR1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_WHILE(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_WHILE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_SETQ(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SETQ(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_TAGBODY(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_TAGBODY(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_TAGBODY1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_TAGBODY1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_GO(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_GO(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CONVERT(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CONVERT(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_FUNCTION(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_FUNCTION(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_SYMBOL_FUNCTION(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SYMBOL_FUNCTION(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CLASS(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CLASS(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_SYMBOL_CLASS(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SYMBOL_CLASS(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CATCH(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CATCH(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_THROW(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_THROW(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_BLOCK(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_BLOCK(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_RETURN_FROM(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_RETURN_FROM(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_UNWIND_PROTECT(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_UNWIND_PROTECT(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_UNWIND_PROTECT1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(COMP_UNWIND_PROTECT1(fast_convert(arg1),fast_convert(arg2))));
}
int f_COMP_SETF(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SETF(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_DYNAMIC(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_DYNAMIC(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_DYNAMIC_LET(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_DYNAMIC_LET(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_DYNAMIC_LET1(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_DYNAMIC_LET1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_DYNAMIC_LET2(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_DYNAMIC_LET2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_NOT(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_NOT(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CAR(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CAR(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CDR(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CDR(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_CONS(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_CONS(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_LENGTH(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_LENGTH(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_C_INCLUDE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_C_INCLUDE(fast_convert(arg1))));
}
int f_COMP_C_DEFINE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_C_DEFINE(fast_convert(arg1))));
}
int f_COMP_C_LANG(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_C_LANG(fast_convert(arg1))));
}
int f_COMP_C_OPTION(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_C_OPTION(fast_convert(arg1))));
}
int f_COMP_DEFGLOBAL(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFGLOBAL(fast_convert(arg1))));
}
int f_COMP_DEFCONSTANT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFCONSTANT(fast_convert(arg1))));
}
int f_COMP_DEFDYNAMIC(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFDYNAMIC(fast_convert(arg1))));
}
int f_COMP_SET_DYNAMIC(int arglist){
int arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
arg5 = Fnth(4,arglist);
arg6 = Fnth(5,arglist);
arg7 = Fnth(6,arglist);
arg8 = Fnth(7,arglist);
arg9 = Fnth(8,arglist);
return(fast_inverse(COMP_SET_DYNAMIC(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4),fast_convert(arg5),fast_convert(arg6),fast_convert(arg7),fast_convert(arg8),fast_convert(arg9))));
}
int f_COMP_DEFMACRO(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFMACRO(fast_convert(arg1))));
}
int f_COMP_DEFCLASS(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFCLASS(fast_convert(arg1))));
}
int f_COMP_DEFMETHOD(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMP_DEFMETHOD(fast_convert(arg1))));
}
int f_HAS_SAME_VARLIS_P(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(HAS_SAME_VARLIS_P(fast_convert(arg1),fast_convert(arg2))));
}
int f_CONV_NAME(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONV_NAME(fast_convert(arg1))));
}
int f_CONV_NAME1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONV_NAME1(fast_convert(arg1))));
}
int f_CONV_NAME2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CONV_NAME2(fast_convert(arg1))));
}
int f_LIST_TO_C(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LIST_TO_C(fast_convert(arg1),fast_convert(arg2))));
}
int f_LIST_TO_C1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LIST_TO_C1(fast_convert(arg1),fast_convert(arg2))));
}
int f_QUASI_TRANSFER(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(QUASI_TRANSFER(fast_convert(arg1),fast_convert(arg2))));
}
int f_OPTIMIZE_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(OPTIMIZE_P(fast_convert(arg1))));
}
int f_OPTIMIZE_P1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(OPTIMIZE_P1(fast_convert(arg1))));
}
int f_RETURN_TYPE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(RETURN_TYPE(fast_convert(arg1))));
}
int f_ARGUMENT_TYPE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ARGUMENT_TYPE(fast_convert(arg1))));
}
int f_LOCAL_RETURN_TYPE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LOCAL_RETURN_TYPE(fast_convert(arg1),fast_convert(arg2))));
}
int f_LOCAL_ARGUMENT_TYPE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LOCAL_ARGUMENT_TYPE(fast_convert(arg1),fast_convert(arg2))));
}
int f_TYPE_GEN_ARG2(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(TYPE_GEN_ARG2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_TYPE_GEN_ARG3(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TYPE_GEN_ARG3(fast_convert(arg1),fast_convert(arg2))));
}
int f_TYPE_GEN_CALL(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TYPE_GEN_CALL(fast_convert(arg1),fast_convert(arg2))));
}
int f_SUBSETP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SUBSETP(fast_convert(arg1),fast_convert(arg2))));
}
int f_CLASS_DYNAMIC(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CLASS_DYNAMIC(fast_convert(arg1))));
}
int f_WARNING(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(WARNING(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_FILE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INFERENCE_FILE(fast_convert(arg1))));
}
int f_INFERENCE_DEFUN(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INFERENCE_DEFUN(fast_convert(arg1))));
}
int f_INFERENCE_LABELS(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_LABELS(fast_convert(arg1),fast_convert(arg2))));
}
int f_FIND_ARGUMENT_CLASS(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FIND_ARGUMENT_CLASS(fast_convert(arg1),fast_convert(arg2))));
}
int f_CREATE_INIT_ENV(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CREATE_INIT_ENV(fast_convert(arg1))));
}
int f_INFERENCE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_ALL(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(INFERENCE_ALL(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_INFERENCE_ALL1(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(INFERENCE_ALL1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_INFERENCE_COND(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_COND(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_COND1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_COND1(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_COND2(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_COND2(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_CASE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_CASE(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_CASE1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_CASE1(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_CASE2(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_CASE2(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_IF(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_IF(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_IF1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_IF1(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_IF2(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_IF2(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_NUMERIC(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_NUMERIC(fast_convert(arg1),fast_convert(arg2))));
}
int f_compiler6(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler6(fast_convert(arg1))));
}
int f_compiler7(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler7(fast_convert(arg1))));
}
int f_compiler8(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler8(fast_convert(arg1))));
}
int f_compiler9(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler9(fast_convert(arg1))));
}
int f_compiler10(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler10(fast_convert(arg1))));
}
int f_INFERENCE_LET(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_LET(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_FOR(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_FOR(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_WHILE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_WHILE(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_WHILE1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_WHILE1(fast_convert(arg1),fast_convert(arg2))));
}
int f_INFERENCE_FUNCTION(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INFERENCE_FUNCTION(fast_convert(arg1),fast_convert(arg2))));
}
int f_FIND_FUNCTION_TYPE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIND_FUNCTION_TYPE(fast_convert(arg1))));
}
int f_INFERENCE_ARG(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(INFERENCE_ARG(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_FUNCTION_TYPE_OBJECT_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FUNCTION_TYPE_OBJECT_P(fast_convert(arg1))));
}
int f_FIND_CLASS(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FIND_CLASS(fast_convert(arg1),fast_convert(arg2))));
}
int f_FIND_CLASS_IF(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FIND_CLASS_IF(fast_convert(arg1),fast_convert(arg2))));
}
int f_FIND_CLASS_COND(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FIND_CLASS_COND(fast_convert(arg1),fast_convert(arg2))));
}
int f_FIND_CLASS_NUMERIC(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FIND_CLASS_NUMERIC(fast_convert(arg1),fast_convert(arg2))));
}
int f_compiler11(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler11(fast_convert(arg1))));
}
int f_compiler12(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler12(fast_convert(arg1))));
}
int f_compiler13(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler13(fast_convert(arg1))));
}
int f_compiler14(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler14(fast_convert(arg1))));
}
int f_compiler15(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(compiler15(fast_convert(arg1))));
}
int f_REFER(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(REFER(fast_convert(arg1),fast_convert(arg2))));
}
int f_SET_TYPE_FUNCTION_OUTPUT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SET_TYPE_FUNCTION_OUTPUT(fast_convert(arg1),fast_convert(arg2))));
}
int f_SET_TYPE_FUNCTION_INPUT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SET_TYPE_FUNCTION_INPUT(fast_convert(arg1),fast_convert(arg2))));
}
int f_ADD_TYPE_FUNCTION_LOCAL(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ADD_TYPE_FUNCTION_LOCAL(fast_convert(arg1))));
}
int f_SET_LOCAL_TYPE_FUNCTION_OUTPUT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SET_LOCAL_TYPE_FUNCTION_OUTPUT(fast_convert(arg1),fast_convert(arg2))));
}
int f_SET_LOCAL_TYPE_FUNCTION_INPUT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SET_LOCAL_TYPE_FUNCTION_INPUT(fast_convert(arg1),fast_convert(arg2))));
}
int f_TYPE_FUNCTION_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(TYPE_FUNCTION_P(fast_convert(arg1))));
}
int f_UNIFY(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(UNIFY(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_VARIABLEP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(VARIABLEP(fast_convert(arg1))));
}
int f_SUBCLASSPstar(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SUBCLASSPstar(fast_convert(arg1),fast_convert(arg2))));
}
int f_ESTIMATE(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(ESTIMATE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_CLASSstar(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CLASSstar(fast_convert(arg1))));
}
int compiler0(){
int res;
({int res;
if(fast_convert(Fcdr(Fmakesym("INSTREAM"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("IGNORE-TOPLEVEL-CHECK")),Flist1(fast_inverse(NIL))));
return(res);}
int compiler1(){
int res;
({int res;
if(fast_convert(Fcdr(Fmakesym("INSTREAM"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("IGNORE-TOPLEVEL-CHECK")),Flist1(fast_inverse(NIL))));
return(res);}
int compiler2(int Y){
int res;
if(CELLRANGE(Y)) Fshelterpush(Y);
res = HAS_TAIL_RECUR_P(fast_convert(fast_cdr(Y)),Fnth(0,Fcdr(Fmakesym("compiler2"))));
if(CELLRANGE(Y)) Fshelterpop();
return(res);}
int compiler3(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler4(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler5(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = ({int res;
if(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(ALPHA_CONV(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0)))))),Fnth(0,Fcdr(Fmakesym("compiler5"))),Fnth(1,Fcdr(Fmakesym("compiler5"))))),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(ALPHA_CONV(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),Fnth(0,Fcdr(Fmakesym("compiler5"))),Fnth(1,Fcdr(Fmakesym("compiler5"))))))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(ALPHA_CONV(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0)))))),Fnth(0,Fcdr(Fmakesym("compiler5"))),Fnth(1,Fcdr(Fmakesym("compiler5"))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))));}res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler6(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = ({int res;int TYPE = fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler6")))));res = ({int res;
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TYPE))))) == NIL)
if((res=fast_eq(fast_convert(TYPE),fast_convert(Faux(Fmakesym("<OBJECT>"))))) == NIL)
if((res=fast_eq(fast_convert(TYPE),fast_convert(Faux(Fmakesym("<NUMBER>"))))) == NIL)
if((res=fast_eq(fast_convert(TYPE),fast_convert(Faux(Fmakesym("<LONGNUM>"))))) == NIL)
if((res=fast_eq(fast_convert(TYPE),fast_convert(Faux(Fmakesym("<BIGNUM>"))))) !=NIL)
res=res;
else res=NIL;
else res=res;else res=res;else res=res;else res=res;res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler7(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<FIXNUM>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler7"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler8(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<FLOAT>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler8"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler9(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<INTEGER>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler9"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler10(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<FIXNUM>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler10"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler11(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = ({int res;int TYPE = fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler11")))));res = ({int res;
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TYPE))))) == NIL)
if((res=fast_eq(fast_convert(TYPE),fast_convert(Faux(Fmakesym("<OBJECT>"))))) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler12(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<FIXNUM>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler12"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler13(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<FLOAT>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler13"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler14(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<INTEGER>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler14"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int compiler15(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_eq(fast_convert(Faux(Fmakesym("<FIXNUM>"))),fast_convert(FIND_CLASS(X,Fnth(0,Fcdr(Fmakesym("compiler15"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int ANY(int F,int LS){
int res;
int temp1,temp2;
ANYloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS)))) != NIL){
res = NIL;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_convert(fast_car(LS))))))) != NIL){
res = T;}
else{
{
temp1 = F;
temp2 = fast_convert(fast_cdr(LS));
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
F = temp1;
LS = temp2;
goto ANYloop;};}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int EVERY(int F,int LS){
int res;
int temp1,temp2;
EVERYloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS)))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_convert(fast_car(LS))))))) != NIL){
{
temp1 = F;
temp2 = fast_convert(fast_cdr(LS));
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
F = temp1;
LS = temp2;
goto EVERYloop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int TAKE(int N,int LS){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = NIL;}
else{
res = Fcons(fast_inverse(fast_convert(fast_car(LS))),fast_inverse(TAKE(fast_minus(fast_convert(N),fast_convert(fast_immediate(1))),fast_convert(fast_cdr(LS)))));}res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int DROP(int N,int LS){
int res;
int temp1,temp2;
DROPloop:
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = LS;}
else{
{
temp1 = fast_minus(fast_convert(N),fast_convert(fast_immediate(1)));
temp2 = fast_convert(fast_cdr(LS));
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
N = temp1;
LS = temp2;
goto DROPloop;};}res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int LAST(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(fast_car(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(LS))))));
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int SECOND_LAST(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(LS))))),Flist1(fast_inverse(fast_immediate(1))))));
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int REMOVE(int X,int LS){
int res;
int temp1,temp2;
REMOVEloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS)))) != NIL){
res = NIL;}
else if(fast_eq(fast_convert(X),fast_convert(fast_convert(fast_car(LS)))) != NIL){
{
temp1 = X;
temp2 = fast_convert(fast_cdr(LS));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
X = temp1;
LS = temp2;
goto REMOVEloop;};}
else{
res = Fcons(fast_inverse(fast_convert(fast_car(LS))),fast_inverse(REMOVE(X,fast_convert(fast_cdr(LS)))));}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int APPENDexclamation(int X,int Y){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
({int res;
while(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X))))))) !=NIL){
res = ({int res;
 res = X = fast_convert(fast_cdr(X));res;})
;};res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-CDR")),Fcons(fast_inverse(Y),Flist1(fast_inverse(X)))));
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int POSITION(int X,int LS){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(X),fast_convert(fast_convert(fast_car(LS)))) != NIL){
res = fast_immediate(0);}
else{
res = fast_plus(fast_convert(fast_immediate(1)),fast_convert(POSITION(X,fast_convert(fast_cdr(LS)))));}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FILENAME(int STR){
int res;
if(CELLRANGE(STR)) Fshelterpush(STR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQL")),Fcons(fast_inverse(SUBSTRING(STR,fast_immediate(0),fast_immediate(0))),Flist1(fast_inverse(Fmakestr(".")))))) != NIL){
res = FILENAME2(STR);}
else{
res = FILENAME1(STR);}res;})
;
if(CELLRANGE(STR)) Fshelterpop();
return(res);}
int FILENAME1(int STR){
int res;
if(CELLRANGE(STR)) Fshelterpush(STR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int N = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR-INDEX")),Fcons(fast_inverse(Fmakechar(".")),Flist1(fast_inverse(STR))))));({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(N)))) != NIL){
res = ERRORstar(Fmakestr("lack of filename ext"),STR);}
 else res = NIL;res;})
;
res = SUBSTRING(STR,fast_immediate(0),fast_minus(fast_convert(N),fast_convert(fast_immediate(1))));
res;})
;
if(CELLRANGE(STR)) Fshelterpop();
return(res);}
int FILENAME2(int STR){
int res;
if(CELLRANGE(STR)) Fshelterpush(STR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int N = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR-INDEX")),Fcons(fast_inverse(Fmakechar(".")),Flist1(fast_inverse(DROPSTRING(STR,fast_immediate(1))))))));({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(N)))) != NIL){
res = ERRORstar(Fmakestr("lack of filename ext"),STR);}
 else res = NIL;res;})
;
res = SUBSTRING(STR,fast_immediate(0),N);
res;})
;
if(CELLRANGE(STR)) Fshelterpop();
return(res);}
int DROPSTRING(int STR,int N){
int res;
if(CELLRANGE(STR)) Fshelterpush(STR);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = SUBSTRING(STR,N,fast_minus(fast_convert(Flength(STR)),fast_convert(fast_immediate(1))));
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(STR)) Fshelterpop();
return(res);}
int SUBSTRING(int STR,int M,int N){
int res;
if(CELLRANGE(STR)) Fshelterpush(STR);
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int Isubst = fast_convert(M);int STR1subst = fast_convert(Fmakestr(""));int temp1,temp2;
while(fast_greaterp(fast_convert(Isubst),fast_convert(N)) == NIL){
({int res;
 res = STR1subst = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(STR1subst),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(STR),Flist1(fast_inverse(Isubst)))))),Fmakesym("<STRING>"))))))));res;})
;
temp1 = fast_plus(fast_convert(Isubst),fast_convert(fast_immediate(1)));
Isubst = temp1;
}
res = STR1subst;res;});
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(STR)) Fshelterpop();
return(res);}
int SUBST(int VARS){
int res;
if(CELLRANGE(VARS)) Fshelterpush(VARS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(VARS)))) != NIL){
res = Fmakesym("NIL");}
else{
res = Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(fast_car(VARS))),Fmakesym("<STRING>")))),Flist1(fast_inverse(Fmakestr("subst"))))))),Fmakesym("<SYMBOL>")))),fast_inverse(SUBST(fast_convert(fast_cdr(VARS)))));}res;})
;
if(CELLRANGE(VARS)) Fshelterpop();
return(res);}
int ALPHA_CONV(int X,int VARS,int SUBST){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(VARS)) Fshelterpush(VARS);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(VARS)))))) != NIL){
res = NTH(SUBST,fast_minus(fast_convert(Flength(VARS)),fast_convert(Flength(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(VARS)))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = X;}
else{
res = Fcons(fast_inverse(ALPHA_CONV(fast_convert(fast_car(X)),VARS,SUBST)),fast_inverse(ALPHA_CONV(fast_convert(fast_cdr(X)),VARS,SUBST)));}
;res;});
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(VARS)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int NTH(int X,int N){
int res;
int temp1,temp2;
NTHloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = fast_convert(fast_car(X));}
else{
{
temp1 = fast_convert(fast_cdr(X));
temp2 = fast_minus(fast_convert(N),fast_convert(fast_immediate(1)));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
X = temp1;
N = temp2;
goto NTHloop;};}res;})
;
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int ERRORstar(int STR,int X){
int res;
if(CELLRANGE(STR)) Fshelterpush(STR);
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("compile error ~A ~A ~%")),Fcons(fast_inverse(STR),Flist1(fast_inverse(X)))))));
res = ({int res,i;
res = T;catch_arg=res;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i-1);
longjmp(c_EXIT[i-1],1);res;})
;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STR)) Fshelterpop();
return(res);}
int COMPILE_FILE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("FILE-NAME-AND-EXT"),fast_inverse(X));res;});
({int res;
 res = Fset_cdr(Fmakesym("TYPE-FUNCTION"),fast_inverse(NIL));res;});
INFERENCE_FILE(X);
({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;
res=COMPILE_FILE1(X);res;});Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
compiler0();res=catch_arg;}
res;});
res = T;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMPILE_FILE1(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int OPTION = fast_convert(({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("SELF-INTRODUCTION")),NIL))),fast_convert(Fmakesym("WINDOWS"))) != NIL){
res = Fmakestr("gcc -O3 -shared -o ");}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("SELF-INTRODUCTION")),NIL))),fast_convert(Fmakesym("LINUX"))) != NIL){
res = Fmakestr("gcc -O3 -w -shared -fPIC -o ");}
;res;}));int FNAME = fast_convert(FILENAME(X));fast_convert(Fcallsubr(Fcar(Fmakesym("IGNORE-TOPLEVEL-CHECK")),Flist1(fast_inverse(T))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("initialize~%"))))));
INITIALIZE();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("pass1~%"))))));
PASS1(X);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("pass2~%"))))));
PASS2(X);
fast_convert(Fcallsubr(Fcar(Fmakesym("IGNORE-TOPLEVEL-CHECK")),Flist1(fast_inverse(NIL))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("finalize~%"))))));
FINALIZE(X,Fmakestr(".c"));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("invoke GCC~%"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SYSTEM")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(OPTION),Fcons(fast_inverse(FNAME),Fcons(fast_inverse(Fmakestr(".o ")),Fcons(fast_inverse(FNAME),Fcons(fast_inverse(Fmakestr(".c ")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("C-LANG-OPTION"))))))))))))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMPILE_FILEstar(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int COMP = fast_convert(({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("SELF-INTRODUCTION")),NIL))),fast_convert(Fmakesym("WINDOWS"))) != NIL){
res = Fmakestr("gcc -O3 -shared -o ");}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("SELF-INTRODUCTION")),NIL))),fast_convert(Fmakesym("LINUX"))) != NIL){
res = Fmakestr("gcc -O3 -w -shared -fPIC -o ");}
;res;}));int FNAME = fast_convert(FILENAME(X));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("invoke GCC~%"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SYSTEM")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(COMP),Fcons(fast_inverse(FNAME),Fcons(fast_inverse(Fmakestr(".o ")),Fcons(fast_inverse(FNAME),Flist1(fast_inverse(Fmakestr(".c")))))))))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMPILE_CUDA(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("FILE-NAME-AND-EXT"),fast_inverse(X));res;});
({int res;
 res = Fset_cdr(Fmakesym("TYPE-FUNCTION"),fast_inverse(NIL));res;});
INFERENCE_FILE(X);
({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT"));
Fsetprop(Fmakesym("EXIT"),i+1);
ret=setjmp(c_EXIT[i]);if(ret == 0){
res = ({int res;
res=COMPILE_CUDA1(X);res;});Fsetprop(Fmakesym("EXIT"),i);
}
 else{
ret = 0;
compiler1();res=catch_arg;}
res;});
res = T;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMPILE_CUDA1(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int OPTION = fast_convert(({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("SELF-INTRODUCTION")),NIL))),fast_convert(Fmakesym("WINDOWS"))) != NIL){
res = Fmakestr("gcc -O3 -shared -o ");}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("SELF-INTRODUCTION")),NIL))),fast_convert(Fmakesym("LINUX"))) != NIL){
res = Fmakestr("nvcc -O3 -w -shared --compiler-options '-fPIC' -lcublas -o ");}
;res;}));int FNAME = fast_convert(FILENAME(X));fast_convert(Fcallsubr(Fcar(Fmakesym("IGNORE-TOPLEVEL-CHECK")),Flist1(fast_inverse(T))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("initialize~%"))))));
INITIALIZE();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("pass1~%"))))));
PASS1(X);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("pass2~%"))))));
PASS2(X);
fast_convert(Fcallsubr(Fcar(Fmakesym("IGNORE-TOPLEVEL-CHECK")),Flist1(fast_inverse(NIL))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("finalize~%"))))));
FINALIZE(X,Fmakestr(".cu"));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("invoke NVCC~%"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SYSTEM")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(OPTION),Fcons(fast_inverse(FNAME),Fcons(fast_inverse(Fmakestr(".o ")),Fcons(fast_inverse(FNAME),Fcons(fast_inverse(Fmakestr(".c ")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("C-LANG-OPTION"))))))))))))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int PASS1(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("INSTREAM"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("OPEN-INPUT-FILE")),Flist1(fast_inverse(X))))));res;});
res = ({int res;int SEXP = fast_convert(NIL);({int res;
while(({int res;
 res = SEXP = fast_convert(Fcallsubr(Fcar(Fmakesym("READ")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))),Fcons(fast_inverse(NIL),Flist1(fast_inverse(NIL))))));res;})
 !=NIL){
CHECK_ARGS_COUNT(SEXP);
res = FIND_CATCH_BLOCK_TAG(SEXP);};res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))))));
res = ({int res;
 res = Fset_cdr(Fmakesym("INSTREAM"),fast_inverse(NIL));res;});
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CHECK_ARGS_COUNT(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFUN"))) != NIL){
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("duplicate definition"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("FUNCTION-ARG"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(COUNT_ARGS(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(2)))))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))));res;});}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFMACRO"))) != NIL){
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defmacro: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defmacro: not list"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defmacro: not exist body"),X);res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("duplicate definition"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("FUNCTION-ARG"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(COUNT_ARGS(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(2)))))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))));res;});
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(X))));}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFGLOBAL"))) != NIL){
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defglobal: illegal form"),X);res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = Fapply(Fcar(Fmakesym("ERROR:")),Fcons(fast_inverse(Fmakestr("defglobal: not symbol")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("GLOBAL-VARIABLE"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("GLOBAL-VARIABLE")))))));res;});
res = ({int res;
if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("COMP-GLOBAL-VAR"))))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(X))));}
 else res = NIL;res;})
;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFCONSTANT"))) != NIL){
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defconstant: illegal form"),X);res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = Fapply(Fcar(Fmakesym("ERROR:")),Fcons(fast_inverse(Fmakestr("defconstant: not symbol")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("GLOBAL-VARIABLE"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("GLOBAL-VARIABLE")))))));res;});
res = ({int res;
if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("COMP-GLOBAL-VAR"))))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(X))));}
 else res = NIL;res;})
;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFCLASS"))) != NIL){
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defclass: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defclass: not list"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));res;});}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(X))));}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFGENERIC"))) != NIL){
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defgeneric: not symbol "),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defgeneric: not list "),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("duplicate definition"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
 res = Fset_cdr(Fmakesym("FUNCTION-ARG"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(COUNT_ARGS(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(2)))))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))));res;});
res = ({int res;
 res = Fset_cdr(Fmakesym("GENERIC-NAME-ARG"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(2))))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("GENERIC-NAME-ARG")))))));res;});
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(X))));}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFMETHOD"))) != NIL){
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defmethod: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not((fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defmethod: not list"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defmethod: not exist body"),X);res;});}
 else res = NIL;res;})
;
res = ({int res;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X))))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defmethod: not exist body"),X);res;});}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(X))));}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_CATCH_BLOCK_TAG(int X){
int res;
int temp1;
FIND_CATCH_BLOCK_TAGloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if((fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CATCH"))) && fast_eqgreaterp(fast_convert(Flength(X)),fast_convert(fast_immediate(3))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))) && fast_numeqp(fast_convert(Flength(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CATCH-BLOCK-TAG"))))))))) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("CATCH-BLOCK-TAG"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("CATCH-BLOCK-TAG")))))));res;});}
 else res = NIL;res;})
;}
else if((fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("BLOCK"))) && fast_eqgreaterp(fast_convert(Flength(X)),fast_convert(fast_immediate(3))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CATCH-BLOCK-TAG"))))))))) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("CATCH-BLOCK-TAG"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("CATCH-BLOCK-TAG")))))));res;});}
 else res = NIL;res;})
;
{
temp1 = fast_convert(fast_cdr(fast_convert(fast_cdr(X))));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto FIND_CATCH_BLOCK_TAGloop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
res = FIND_CATCH_BLOCK_TAG(fast_convert(fast_car(X)));
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto FIND_CATCH_BLOCK_TAGloop;};}
else{
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto FIND_CATCH_BLOCK_TAGloop;};}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int PASS2(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("INSTREAM"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("OPEN-INPUT-FILE")),Flist1(fast_inverse(X))))));res;});
DECLARE_CATCH_BLOCK_BUFFER();
res = ({int res;int SEXP = fast_convert(NIL);({int res;
while(({int res;
 res = SEXP = fast_convert(Fcallsubr(Fcar(Fmakesym("READ")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))),Fcons(fast_inverse(NIL),Flist1(fast_inverse(NIL))))));res;})
 !=NIL){
({int res;
if(OPTIMIZE_P(SEXP) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("OPTIMIZE-ENABLE"),fast_inverse(T));res;});}
else{
res = ({int res;
 res = Fset_cdr(Fmakesym("OPTIMIZE-ENABLE"),fast_inverse(NIL));res;});}res;})
;
res = COMPILE(SEXP);};res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))))));
res = ({int res;
 res = Fset_cdr(Fmakesym("INSTREAM"),fast_inverse(NIL));res;});
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COUNT_ARGS(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS)))) != NIL){
res = fast_immediate(0);}
else if(fast_numeqp(fast_convert(Flength(LS)),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(1);}
else if(fast_eq(fast_convert(SECOND_LAST(LS)),fast_convert(Fmakesym(":REST"))) != NIL){
res = fast_mult(fast_convert(fast_immediate(-1)),fast_convert(fast_minus(fast_convert(Flength(LS)),fast_convert(fast_immediate(1)))));}
else if(fast_eq(fast_convert(SECOND_LAST(LS)),fast_convert(Fmakesym("&REST"))) != NIL){
res = fast_mult(fast_convert(fast_immediate(-1)),fast_convert(fast_minus(fast_convert(Flength(LS)),fast_convert(fast_immediate(1)))));}
else{
res = Flength(LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int COMPILE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFUN"))) != NIL){
res = COMP_DEFUN(X);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFGLOBAL"))) != NIL){
res = COMP_DEFGLOBAL(X);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFDYNAMIC"))) != NIL){
res = COMP_DEFDYNAMIC(X);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFCONSTANT"))) != NIL){
res = COMP_DEFCONSTANT(X);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFMACRO"))) != NIL){
res = COMP_DEFMACRO(X);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFCLASS"))) != NIL){
res = COMP_DEFCLASS(X);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFGENERIC"))) != NIL){
res = COMP_DEFGENERIC(X);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DEFMETHOD"))) != NIL){
res = COMP_DEFMETHOD(X);}
else{
res = COMP(fast_convert(Fcdr(Fmakesym("CODE4"))),X,NIL,NIL,NIL,NIL,T,NIL,NIL);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(";"))))));}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMPloop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("FIXNUMP")),Flist1(fast_inverse(X)))) && fast_not(GLOBAL)) != NIL){
res = ({int res=NIL;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_immediate("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(10)))))));}
;res;});}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("FIXNUMP")),Flist1(fast_inverse(X)))) && GLOBAL) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakeint("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("FLOATP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res=NIL;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestrflt(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-FLOAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-FLOAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));}
;res;});}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("BIGNUMP")),Flist1(fast_inverse(X)))) || fast_convert(Fcallsubr(Fcar(Fmakesym("LONGNUMP")),Flist1(fast_inverse(X))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakebig(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestr("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakechar("\\")))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(34)),Fmakesym("<CHARACTER>")))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakechar("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakechar("\\"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakechar("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-VECTOR-P")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fvector("))))));
res = LIST_TO_C1(STREAM,fast_convert(Fconvert(fast_inverse(X),Fmakesym("<LIST>"))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-ARRAY*-P")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Farray("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Flength(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X)))))),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = LIST_TO_C1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("READED-ARRAY-LIST")),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && CLOS) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(X),fast_convert(NIL)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else if(fast_eq(fast_convert(X),fast_convert(T)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("T"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(CLOS))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fnth("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(POSITION(X,CLOS)),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(",Fcdr(Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(CONV_NAME(NAME)),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")))"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(ENV))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>"))))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert(Fcdr(Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")))"))))));}
;res;});}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && fast_not(CLOS)) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(X),fast_convert(NIL)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else if(fast_eq(fast_convert(X),fast_convert(T)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("T"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(ENV))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(CONV_NAME(X)),Fmakesym("<STRING>"))))))));}
else{
res = ({int res;
if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("GLOBAL-VARIABLE"))))))))) && fast_not(fast_eq(fast_convert(X),fast_convert(Fmakesym("*PI*")))) && fast_not(fast_eq(fast_convert(X),fast_convert(Fmakesym("*MOST-NEGATIVE-FLOAT*")))) && fast_not(fast_eq(fast_convert(X),fast_convert(Fmakesym("*MOST-POSITIVE-FLOAT*"))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("undefined global variable"),X);res;});}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert(Fcdr(Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")))"))))));}
;res;});}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LAMBDA")))) != NIL){
res = COMP_LAMBDA(X,ENV,GLOBAL);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MACROP")),Flist1(fast_inverse(fast_convert(fast_car(X))))))) != NIL){
{
temp1 = STREAM;
temp2 = fast_convert(Fcallsubr(Fcar(Fmakesym("MACROEXPAND-1")),Flist1(fast_inverse(X))));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMPloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("QUOTE")))) != NIL){
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))) != NIL){
res = LIST_TO_C1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));}
else{
{
temp1 = STREAM;
temp2 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMPloop;};}
;res;});}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("QUASI-QUOTE")))) != NIL){
{
temp1 = STREAM;
temp2 = QUASI_TRANSFER(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),fast_immediate(0));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMPloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("IF")))) != NIL){
res = COMP_IF(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("COND")))) != NIL){
res = COMP_COND(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CASE")))) != NIL){
res = COMP_CASE(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CASE-USING")))) != NIL){
res = COMP_CASE_USING(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && (fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LABELS"))) || fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FLET"))))) != NIL){
res = COMP_LABELS(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET")))) != NIL){
res = COMP_LET(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET*")))) != NIL){
res = COMP_LETstar(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("AND")))) != NIL){
res = ({int res;
if(TEST != NIL){
res = COMP_TEST_AND(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else{
res = COMP_AND(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("OR")))) != NIL){
res = ({int res;
if(TEST != NIL){
res = COMP_TEST_OR(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else{
res = COMP_OR(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("PROGN")))) != NIL){
res = COMP_PROGN(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FOR")))) != NIL){
res = COMP_FOR(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("WHILE")))) != NIL){
res = COMP_WHILE(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("SETQ")))) != NIL){
res = COMP_SETQ(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("TAGBODY")))) != NIL){
res = COMP_TAGBODY(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("GO")))) != NIL){
res = COMP_GO(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("BLOCK")))) != NIL){
res = COMP_BLOCK(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("RETURN-FROM")))) != NIL){
res = COMP_RETURN_FROM(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CONVERT")))) != NIL){
res = COMP_CONVERT(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FUNCTION")))) != NIL){
res = COMP_FUNCTION(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("SYMBOL-FUNCTION")))) != NIL){
res = COMP_SYMBOL_FUNCTION(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CLASS")))) != NIL){
res = COMP_CLASS(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("SYMBOL-CLASS")))) != NIL){
res = COMP_SYMBOL_CLASS(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CATCH")))) != NIL){
res = COMP_CATCH(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("THROW")))) != NIL){
res = COMP_THROW(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("UNWIND-PROTECT")))) != NIL){
res = COMP_UNWIND_PROTECT(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("SETF")))) != NIL){
res = COMP_SETF(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DYNAMIC")))) != NIL){
res = COMP_DYNAMIC(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("SET-DYNAMIC")))) != NIL){
res = COMP_SET_DYNAMIC(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DYNAMIC-LET")))) != NIL){
res = COMP_DYNAMIC_LET(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CALL-NEXT-METHOD")))) != NIL){
res = T;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("THE")))) != NIL){
res = T;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("NOT")))) != NIL){
res = COMP_NOT(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CAR")))) != NIL){
res = COMP_CAR(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CDR")))) != NIL){
res = COMP_CDR(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CONS")))) != NIL){
res = COMP_CONS(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LENGTH")))) != NIL){
res = COMP_LENGTH(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("C-INCLUDE")))) != NIL){
res = COMP_C_INCLUDE(X);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("C-DEFINE")))) != NIL){
res = COMP_C_DEFINE(X);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("C-LANG")))) != NIL){
res = COMP_C_LANG(X);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("C-OPTION")))) != NIL){
res = COMP_C_OPTION(X);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fcons(Fmakesym("="),Fcons(Fmakesym("<"),Fcons(Fmakesym("<="),Fcons(Fmakesym(">"),Fcons(Fmakesym(">="),Fcons(Fmakesym("+"),Fcons(Fmakesym("-"),Fcons(Fmakesym("*"),Fcons(Fmakesym("MOD"),Fcons(Fmakesym("EQ"),NIL)))))))))))))))) != NIL){
res = COMP_NUMERIC(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SUBRP")),Flist1(fast_inverse(fast_convert(fast_car(X))))))) != NIL){
res = COMP_SUBRCALL(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(X)))) != NIL){
res = COMP_FUNCALL(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int INITIALIZE(){
int res;
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("GLOBAL-VARIABLE"),fast_inverse(NIL));res;});
({int res;
 res = Fset_cdr(Fmakesym("FUNCTION-ARG"),fast_inverse(NIL));res;});
({int res;
 res = Fset_cdr(Fmakesym("GENERIC-NAME-ARG"),fast_inverse(NIL));res;});
({int res;
 res = Fset_cdr(Fmakesym("CATCH-BLOCK-TAG"),fast_inverse(NIL));res;});
({int res;
 res = Fset_cdr(Fmakesym("C-LANG-OPTION"),fast_inverse(Fmakestr("")));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE0"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE1"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE2"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE3"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE4"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE5"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE6"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
({int res;
 res = Fset_cdr(Fmakesym("CODE7"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),NIL))));res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("void init_tfunctions(void){~%"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("void init_declare(void){~%"))))));
return(res);}
int DECLARE_CATCH_BLOCK_BUFFER(){
int res;
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Fsetcatchsymbols("))))));
LIST_TO_C1(fast_convert(Fcdr(Fmakesym("CODE4"))),fast_convert(Fcdr(Fmakesym("CATCH-BLOCK-TAG"))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(");"))))));
res = ({int res;
int TAGsubst = fast_convert(fast_convert(Fcdr(Fmakesym("CATCH-BLOCK-TAG"))));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TAGsubst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("jmp_buf c_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(TAGsubst)))),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("[50];~%"))))));
temp1 = fast_convert(fast_cdr(TAGsubst));
TAGsubst = temp1;
}
res = T;res;});
return(res);}
int FINALIZE(int X,int EXT){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(EXT)) Fshelterpush(EXT);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("}"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("}"))))));
res = ({int res;int OUTSTREAM = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("OPEN-OUTPUT-FILE")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(FILENAME(X)),Flist1(fast_inverse(EXT))))))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(Fmakestr("#include \"fast.h\"~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0"))))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1"))))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE5"))))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE6"))))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE7"))))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2"))))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3"))))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(OUTSTREAM),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4"))))))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(OUTSTREAM))));
res;})
;
if(CELLRANGE(EXT)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFUN(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("compiling ~A ~%")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))));
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defun: not symbol "),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defun: not list "),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));res;});}
 else res = NIL;res;})
;
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defun: not exist body"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
COMP_DEFUN0(X);
COMP_DEFUN1(X);
COMP_DEFUN2(X);
res = COMP_DEFUN3(X);
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_LAMBDA(int X,int ENV,int GLOBAL){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("lambda: not list"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("lambda: not exist body"),X);res;});}
 else res = NIL;res;})
;
({int res;
 res = Fset_cdr(Fmakesym("LAMBDA-NEST"),fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(Fmakeint(1)))));res;});
res = ({int res;int NAME = fast_convert(LAMBDA_NAME());int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));int FREE = fast_convert(FIND_FREE_VARIABLE(BODY,ARGS,ENV));int STREAM = fast_convert(LAMBDA_STREAM_CALLER(GLOBAL));COMP_LAMBDA0(X,NAME);
COMP_LAMBDA1(X,NAME);
COMP_LAMBDA2(BODY,ENV,ARGS,NAME,FREE);
COMP_LAMBDA3(NAME);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({Fset_cdr(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(NAME),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),"))))));
FREE_VARIABLE_LIST(STREAM,FREE);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(");"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcar(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(NAME),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"));})"))))));
res = ({int res;
 res = Fset_cdr(Fmakesym("LAMBDA-NEST"),fast_inverse(fast_minus(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(Fmakeint(1)))));res;});
res;})
;
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int LAMBDA_NAME(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(CONV_NAME(fast_convert(Fconvert(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(FILENAME(fast_convert(Fcdr(Fmakesym("FILE-NAME-AND-EXT"))))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcdr(Fmakesym("LAMBDA-COUNT")))),Fmakesym("<STRING>"))))))))),Fmakesym("<SYMBOL>")))));({int res;
 res = Fset_cdr(Fmakesym("LAMBDA-COUNT"),fast_inverse(fast_plus(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-COUNT")))),fast_convert(Fmakeint(1)))));res;});
res = NAME;
res;})
;
return(res);}
int COMP_DEFGENERIC(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("compiling ~A ~%")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))));
COMP_DEFGENERIC0(X);
COMP_DEFGENERIC1(X);
COMP_DEFGENERIC2(X);
res = COMP_DEFGENERIC3(X);
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFUN0(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));int N = fast_convert(Flength(ARGS));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("int f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("(int arglist);"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE0"))),ARGS);}
else{
res = TYPE_GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE0"))),ARGS,ARGUMENT_TYPE(NAME));}res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr(";~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_LAMBDA0(int X,int NAME){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int N = fast_convert(Flength(ARGS));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("int f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("(int arglist);"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE0"))),ARGS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr(";~%"))))));
res;})
;
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFGENERIC0(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));int N = fast_convert(Flength(ARGS));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("int f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("(int arglist);"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE0"))),ARGS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr(";~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFUN1(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));int N = fast_convert(COUNT_ARGS(ARGS));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("int f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("(int arglist){~%"))))));
GEN_ARG1(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));
GEN_ASSIGN(N);
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_CALL(CONV_NAME(NAME),fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));}
else{
res = TYPE_GEN_CALL(NAME,fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));}res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("}~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_LAMBDA1(int X,int NAME){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int N = fast_convert(COUNT_ARGS(ARGS));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("int f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("(int arglist){~%"))))));
GEN_ARG1(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));
GEN_ASSIGN(N);
GEN_CALL(CONV_NAME(NAME),fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("}~%"))))));
res;})
;
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFGENERIC1(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));int N = fast_convert(COUNT_ARGS(ARGS));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("int f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("(int arglist){~%"))))));
GEN_ARG1(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));
GEN_ASSIGN(N);
GEN_CALL(CONV_NAME(NAME),fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("}~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFUN2(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS);}
else{
res = TYPE_GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS,ARGUMENT_TYPE(NAME));}res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("{~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int res;~%"))))));
({int res=NIL;
if((fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) && HAS_TAIL_RECUR_P(BODY,NAME)) != NIL){
res = GEN_ARG3(Flength(ARGS));}
else if((fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE"))) && HAS_TAIL_RECUR_P(BODY,NAME)) != NIL){
res = TYPE_GEN_ARG3(Flength(ARGS),ARGUMENT_TYPE(NAME));}
;res;});
({int res=NIL;
if(HAS_TAIL_RECUR_P(BODY,NAME) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("loop:~%"))))));}
;res;});
({int res=NIL;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_SHELTERPUSH(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS);
res = GEN_CHECKGC();}
;res;});
res = ({int res;
int BODY1subst = fast_convert(BODY);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY1subst)))))) == NIL){
COMP(fast_convert(Fcdr(Fmakesym("CODE2"))),fast_convert(fast_car(BODY1subst)),ARGS,ARGS,NIL,NAME,NIL,NIL,NIL);
({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(BODY1subst));
BODY1subst = temp1;
}
({int res;
if((fast_not(NOT_NEED_RES_P(fast_convert(fast_car(BODY1subst)))) && fast_not(TAILCALLP(fast_convert(fast_car(BODY1subst)),T,NAME))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
COMP(fast_convert(Fcdr(Fmakesym("CODE2"))),fast_convert(fast_car(BODY1subst)),ARGS,ARGS,T,NAME,NIL,NIL,NIL);
({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_SHELTERPOP(fast_convert(Fcdr(Fmakesym("CODE2"))),fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(ARGS)))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("return(res);}~%"))))));res;});
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_LAMBDA2(int BODY,int ENV,int ARGS,int NAME,int CLOS){
int res;
if(CELLRANGE(BODY)) Fshelterpush(BODY);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int STREAM = fast_convert(LAMBDA_STREAM_CALLEE());fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
GEN_ARG2(STREAM,ARGS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("{~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("int res;~%"))))));
({int res=NIL;
if(HAS_TAIL_RECUR_P(BODY,NAME) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("loop:~%"))))));}
;res;});
GEN_SHELTERPUSH(STREAM,ARGS);
res = ({int res;
int BODY1subst = fast_convert(BODY);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY1subst)))))) == NIL){
COMP(STREAM,fast_convert(fast_car(BODY1subst)),ARGS,ARGS,NIL,NAME,NIL,NIL,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
temp1 = fast_convert(fast_cdr(BODY1subst));
BODY1subst = temp1;
}
({int res;
if(fast_not(NOT_NEED_RES_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
COMP(STREAM,fast_convert(fast_car(BODY1subst)),ARGS,ARGS,NIL,NAME,NIL,NIL,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
GEN_SHELTERPOP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(ARGS)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("return(res);}~%"))))));res;});
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(BODY)) Fshelterpop();
return(res);}
int LAMBDA_STREAM_CALLEE(){
int res;
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(fast_immediate(0))) != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE5")));}
else if(fast_numeqp(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(fast_immediate(1))) != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE5")));}
else if(fast_numeqp(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(fast_immediate(2))) != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE6")));}
else if(fast_numeqp(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(fast_immediate(3))) != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE7")));}
else{
res = ERRORstar(Fmakestr("lambda: over nesting"),fast_convert(Fcdr(Fmakesym("LAMBDA-NEST"))));}
;res;});
return(res);}
int LAMBDA_STREAM_CALLER(int GLOBAL){
int res;
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(GLOBAL != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE4")));}
else if(fast_numeqp(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(fast_immediate(1))) != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE2")));}
else if(fast_numeqp(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(fast_immediate(2))) != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE5")));}
else if(fast_numeqp(fast_convert(fast_convert(Fcdr(Fmakesym("LAMBDA-NEST")))),fast_convert(fast_immediate(3))) != NIL){
res = fast_convert(Fcdr(Fmakesym("CODE6")));}
else{
res = ERRORstar(Fmakestr("lambda: over nesting"),fast_convert(Fcdr(Fmakesym("LAMBDA-NEST"))));}
;res;});
if(CELLRANGE(GLOBAL)) Fshelterpop();
return(res);}
int FIND_FREE_VARIABLE(int X,int ENV,int ARGS){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(Ffreecell() < 900) Fgbc();
res = ({int arg1,arg2,res;
arg1 = fast_inverse(FIND_FREE_VARIABLE1(X,ENV,ARGS));
Fshelterpush(arg1);
arg2 = fast_inverse(Fcons(T,NIL));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;});
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_FREE_VARIABLE1(int X,int ENV,int ARGS){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(ENV)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(X),Flist1(fast_inverse(ARGS)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(X))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else{
res = ({int arg1,arg2,res;
arg1 = fast_inverse(FIND_FREE_VARIABLE1(fast_convert(fast_car(X)),ENV,ARGS));
Fshelterpush(arg1);
arg2 = fast_inverse(FIND_FREE_VARIABLE1(fast_convert(fast_cdr(X)),ENV,ARGS));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;});}
;res;});
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FREE_VARIABLE_LIST(int STREAM,int X){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcons("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(X)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = FREE_VARIABLE_LIST(STREAM,fast_convert(fast_cdr(X)));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_DEFGENERIC2(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARGS = fast_convert(VARLIS_TO_LAMBDA_ARGS(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))));int METHOD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD")),Flist1(fast_inverse(NAME)))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(CONV_NAME(NAME)),Fmakesym("<STRING>"))))))));
GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("{~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int res;~%"))))));
GEN_SHELTERPUSH(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS);
GEN_CHECKGC();
COMP_DEFGENERIC_BODY(METHOD,NIL);
GEN_SHELTERPOP(fast_convert(Fcdr(Fmakesym("CODE2"))),fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(ARGS)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("return(res);}~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int VARLIS_TO_LAMBDA_ARGS(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym(":REST"))) != NIL){
res = fast_convert(fast_cdr(X));}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym(":REST"))) != NIL){
res = fast_convert(fast_cdr(X));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
res = Fcons(fast_inverse(fast_convert(fast_car(X))),fast_inverse(VARLIS_TO_LAMBDA_ARGS(fast_convert(fast_cdr(X)))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
res = Fcons(fast_inverse(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_inverse(VARLIS_TO_LAMBDA_ARGS(fast_convert(fast_cdr(X)))));}
else{
res = ERRORstar(Fmakestr("defgeneric"),X);}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFGENERIC_BODY(int X,int AFTER){
int res;
int temp1,temp2;
COMP_DEFGENERIC_BODYloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(AFTER)) Fshelterpush(AFTER);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = ({int res;int VARBODY = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-BODY")),Flist1(fast_inverse(fast_convert(fast_car(X)))))));int VARLIS = fast_convert(fast_convert(fast_car(VARBODY)));int BODY = fast_convert(fast_convert(fast_cdr(VARBODY)));int PRIORITY = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X)))))));({int res;
if((fast_numeqp(fast_convert(PRIORITY),fast_convert(fast_immediate(14))) && fast_not(PRIORITY)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("after:~%"))))));}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("if("))))));
COMP_DEFGENERIC_COND(VARLIS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(")~%{"))))));
COMP_PROGN1(fast_convert(Fcdr(Fmakesym("CODE2"))),BODY,VARLIS_TO_LAMBDA_ARGS(VARLIS),NIL,NIL,NIL,NIL,NIL,NIL);
({int res;
if((METHOD_NEED_RETURN_P(X) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(LAST(BODY)),Flist1(fast_inverse(Fcons(Fmakesym("CALL-NEXT-METHOD"),NIL)))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("return(res);"))))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("}~%"))))));
res;})
;}
else{
res = ({int res;int VARBODY = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-BODY")),Flist1(fast_inverse(fast_convert(fast_car(X)))))));int VARLIS = fast_convert(fast_convert(fast_car(VARBODY)));int BODY = fast_convert(fast_convert(fast_cdr(VARBODY)));int PRIORITY = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X)))))));({int res;
if((fast_numeqp(fast_convert(PRIORITY),fast_convert(fast_immediate(14))) && fast_not(AFTER)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("after:~%"))))));}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("if("))))));
COMP_DEFGENERIC_COND(VARLIS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(")~%{"))))));
COMP_PROGN1(fast_convert(Fcdr(Fmakesym("CODE2"))),BODY,VARLIS_TO_LAMBDA_ARGS(VARLIS),NIL,NIL,NIL,NIL,NIL,NIL);
({int res;
if((METHOD_NEED_RETURN_P(X) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(LAST(BODY)),Flist1(fast_inverse(Fcons(Fmakesym("CALL-NEXT-METHOD"),NIL)))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("return(res);"))))));}
 else res = NIL;res;})
;
({int res;
if((fast_numeqp(fast_convert(PRIORITY),fast_convert(fast_immediate(13))) && METHOD_NEED_RETURN_P1(fast_convert(fast_cdr(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("goto after;"))))));}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("}~%"))))));
{
temp1 = fast_convert(fast_cdr(X));
temp2 = ({int res;
if(fast_numeqp(fast_convert(PRIORITY),fast_convert(fast_immediate(14))) != NIL){
res = T;}
else{
res = AFTER;}res;})
;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(AFTER)) Fshelterpop();
X = temp1;
AFTER = temp2;
goto COMP_DEFGENERIC_BODYloop;};
res;})
;}
;res;});
if(CELLRANGE(AFTER)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int METHOD_NEED_RETURN_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = T;}
else if(fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(11))) != NIL){
res = T;}
else if(fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(12))) != NIL){
res = NIL;}
else if((fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(13))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X))))))) != NIL){
res = NIL;}
else if((fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(13))) && METHOD_NEED_RETURN_P1(fast_convert(fast_cdr(X)))) != NIL){
res = NIL;}
else if((fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(14))) && fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))),fast_convert(fast_immediate(14)))) != NIL){
res = NIL;}
else{
res = T;}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int METHOD_NEED_RETURN_P1(int X){
int res;
int temp1;
METHOD_NEED_RETURN_P1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(11))) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(12))) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(fast_convert(fast_car(X))))))),fast_convert(fast_immediate(14))) != NIL){
res = T;}
else{
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto METHOD_NEED_RETURN_P1loop;};}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFGENERIC_COND(int X){
int res;
int temp1;
COMP_DEFGENERIC_CONDloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym(":REST"))) != NIL){
res = T;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("%REST"))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto COMP_DEFGENERIC_CONDloop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("Fadaptp("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(",Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("\"))"))))));
res = COMP_DEFGENERIC_COND1(fast_convert(fast_cdr(X)));}
else{
res = ERRORstar(Fmakestr("defgeneric"),X);}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFGENERIC_COND1(int X){
int res;
int temp1;
COMP_DEFGENERIC_COND1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym(":REST"))) != NIL){
res = T;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("%REST"))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto COMP_DEFGENERIC_COND1loop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(" && Fadaptp("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(",Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("\"))"))))));
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto COMP_DEFGENERIC_COND1loop;};}
else{
res = ERRORstar(Fmakestr("defgeneric"),X);}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFUN3(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("(deftfunc)(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Fcons(fast_inverse(NAME),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("\" , f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr(");~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_LAMBDA3(int NAME){
int res;
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("(deftfunc)(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Fcons(fast_inverse(NAME),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("\" , f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr(");~%"))))));
if(CELLRANGE(NAME)) Fshelterpop();
return(res);}
int COMP_DEFGENERIC3(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("(deftfunc)(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Fcons(fast_inverse(NAME),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr("\" , f_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE3")))),Flist1(fast_inverse(Fmakestr(");~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int GEN_ARG1(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)))) != NIL){
res = ({int res;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("int "))))));
res = ({int res;
int Msubst = fast_convert(fast_immediate(1));int temp1;
while(fast_numeqp(fast_convert(Msubst),fast_convert(N)) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Fcons(fast_inverse(Msubst),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(","))))));
temp1 = fast_plus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
Msubst = temp1;
}
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Fcons(fast_inverse(Msubst),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(";~%"))))));res;});res;});}
 else res = NIL;res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int GEN_ARG2(int STREAM,int LS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("("))))));
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else{
res = ({int res;
int LS1subst = fast_convert(REMOVE(Fmakesym("&REST"),REMOVE(Fmakesym(":REST"),LS)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(LS1subst)))))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
temp1 = fast_convert(fast_cdr(LS1subst));
LS1subst = temp1;
}
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));res;});}res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int GEN_ARG3(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)))) != NIL){
res = ({int res;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int "))))));
res = ({int res;
int Msubst = fast_convert(fast_immediate(1));int temp1;
while(fast_numeqp(fast_convert(Msubst),fast_convert(N)) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("temp"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(","))))));
temp1 = fast_plus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
Msubst = temp1;
}
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("temp"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(";~%"))))));res;});res;});}
 else res = NIL;res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int GEN_ASSIGN(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = T;}
else if(fast_smallerp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = ({int res;
int Msubst = fast_convert(fast_immediate(1));int temp1;
while(fast_numeqp(fast_convert(Msubst),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(" = Fnth("))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1)))),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(",arglist);~%"))))));
temp1 = fast_plus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
Msubst = temp1;
}
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(" = Fnthcdr("))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1)))),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(",arglist);~%"))))));res;});}
else{
res = ({int res;
int Msubst = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(Msubst),fast_convert(N)) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(" = Fnth("))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1)))),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr(",arglist);~%"))))));
temp1 = fast_plus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
Msubst = temp1;
}
res = T;res;});}
;res;});
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int GEN_CALL(int NAME,int N){
int res;
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("return(fast_inverse("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(NAME),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("() ));~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("return(fast_inverse("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(NAME),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("("))))));
res = ({int res;
int Msubst = fast_convert(fast_immediate(1));int temp1;
while(fast_numeqp(fast_convert(Msubst),fast_convert(N)) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("fast_convert(arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("),"))))));
temp1 = fast_plus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
Msubst = temp1;
}
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("fast_convert(arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("))));~%"))))));res;});}
;res;});
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
return(res);}
int GEN_SHELTERPUSH(int STREAM,int LS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))))) != NIL){
res = ({int res;
res = ({int res;
int LS1subst = fast_convert(REMOVE(Fmakesym(":REST"),REMOVE(Fmakesym("&REST"),LS)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS1subst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("if(CELLRANGE("))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")) Fshelterpush("))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(");~%"))))));
temp1 = fast_convert(fast_cdr(LS1subst));
LS1subst = temp1;
}
res = T;res;});res;});}
 else res = NIL;res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int GEN_SHELTERPOP(int STREAM,int LS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))))) != NIL){
res = ({int res;
res = ({int res;
int LS1subst = fast_convert(REMOVE(Fmakesym(":REST"),REMOVE(Fmakesym("&REST"),LS)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS1subst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("if(CELLRANGE("))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")) Fshelterpop();~%"))))));
temp1 = fast_convert(fast_cdr(LS1subst));
LS1subst = temp1;
}
res = T;res;});res;});}
 else res = NIL;res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int GEN_CHECKGC(){
int res;
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("if(Ffreecell() < 900) Fgbc();~%"))))));
return(res);}
int COMP_IF(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not((fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3))) || fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(4))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("if: illegal form"),X);res;});}
 else res = NIL;res;})
;
res = ({int res=NIL;
if(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%if("))))));
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,T,CLOS);
res = ({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" != NIL){~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("){~%"))))));}res;})
;
res = ({int res;
if((fast_not(NOT_NEED_RES_P(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))) && fast_not(TAILCALLP(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),TAIL,NAME))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";}~% else res = NIL;res;})~%"))))));}
else if(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(4))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%if("))))));
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,T,CLOS);
res = ({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" != NIL){~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("){~%"))))));}res;})
;
res = ({int res;
if((fast_not(NOT_NEED_RES_P(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))) && fast_not(TAILCALLP(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),TAIL,NAME))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";}~%"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else{~%"))))));
res = ({int res;
if((fast_not(NOT_NEED_RES_P(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3)))))))) && fast_not(TAILCALLP(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3)))))),TAIL,NAME))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";}res;})~%"))))));}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_NUMERIC(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("EQ"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_eq("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("="))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_numeqp("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("<"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_smallerp("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("<="))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_eqsmallerp("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym(">"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_greaterp("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym(">="))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_eqgreaterp("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("+"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_plus("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("-"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_minus("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("*"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_mult("))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("MOD"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_mod("))))));}
;res;});
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert("))))));
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),fast_convert("))))));
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));}
else{
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = ({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("EQ"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("=="))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("="))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("=="))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("<"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("<"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("<="))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("<="))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym(">"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(">"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym(">="))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(">="))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("+"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("+"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("-"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("-"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("*"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("*"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("MOD"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("%"))))));}
;res;});
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FUNCALL(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((TAIL && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(NAME))) != NIL){
res = COMP_FUNCALL1(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG"))))))))) != NIL){
res = COMP_FUNCALL2(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(fast_convert(fast_cdr(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG"))))))))))),fast_convert(fast_immediate(0)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("call: illegal argument count"),X);res;});}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(X)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("()"))))));}
else{
res = COMP_FUNCALL_CLANG(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FUNCALL_CLANG(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int N = fast_convert(fast_convert(fast_cdr(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))))))));({int res;
if((fast_greaterp(fast_convert(N),fast_convert(fast_immediate(0))) && fast_convert(Fcallsubr(Fcar(Fmakesym("/=")),Fcons(fast_inverse(Flength(fast_convert(fast_cdr(X)))),Flist1(fast_inverse(N)))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("call: illegal arument count"),X);res;});}
 else res = NIL;res;})
;
res = ({int res=NIL;
if(fast_greaterp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(X)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("("))))));
res = ({int res;
int LSsubst = fast_convert(fast_convert(fast_cdr(X)));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(LSsubst)))))) == NIL){
COMP(STREAM,fast_convert(fast_car(LSsubst)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
temp1 = fast_convert(fast_cdr(LSsubst));
LSsubst = temp1;
}
COMP(STREAM,fast_convert(fast_car(LSsubst)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));res;});}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(X)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("("))))));
res = ({int res;
int LSsubst = fast_convert(fast_convert(fast_cdr(X)));int Msubst = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(N)))));int temp1,temp2;
while(fast_numeqp(fast_convert(Msubst),fast_convert(fast_immediate(1))) == NIL){
COMP(STREAM,fast_convert(fast_car(LSsubst)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
temp1 = fast_convert(fast_cdr(LSsubst));
temp2 = fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
LSsubst = temp1;
Msubst = temp2;
}
COMP_FUNCALL_CLANG1(STREAM,LSsubst,ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));res;});}
;res;});
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FUNCALL_CLANG1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcons(fast_inverse("))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),"))))));
res = COMP_FUNCALL_CLANG1(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FUNCALL1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("{~%"))))));
({int res;
int LSsubst = fast_convert(fast_convert(fast_cdr(X)));int Nsubst = fast_convert(fast_immediate(1));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LSsubst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("temp"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Nsubst),Flist1(fast_inverse(fast_immediate(10)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" = "))))));
COMP(STREAM,fast_convert(fast_car(LSsubst)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
temp1 = fast_convert(fast_cdr(LSsubst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
LSsubst = temp1;
Nsubst = temp2;
}
res = T;res;});
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_SHELTERPOP(STREAM,ARGS);}
 else res = NIL;res;})
;
({int res;
int LSsubst = fast_convert(ARGS);int Nsubst = fast_convert(fast_immediate(1));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LSsubst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LSsubst)))),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" = temp"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Nsubst),Flist1(fast_inverse(fast_immediate(10)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
temp1 = fast_convert(fast_cdr(LSsubst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
LSsubst = temp1;
Nsubst = temp2;
}
res = T;res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("goto "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(NAME)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("loop;}"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FUNCALL2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fapply(Fcar(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")),"))))));
COMP_SUBRCALL2(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_SUBRCALL(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_not(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("APPEND")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert(Fcallsubr(Fcar(Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")),"))))));
res = COMP_SUBRCALL1(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int "))))));
res = ({int res;
int LSsubst = fast_convert(fast_convert(fast_cdr(X)));int Nsubst = fast_convert(fast_immediate(1));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LSsubst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Nsubst),Flist1(fast_inverse(fast_immediate(10)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
temp1 = fast_convert(fast_cdr(LSsubst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
LSsubst = temp1;
Nsubst = temp2;
}
res = T;res;});
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;~%"))))));
res = ({int res;
int LSsubst = fast_convert(fast_convert(fast_cdr(X)));int Nsubst = fast_convert(fast_immediate(1));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LSsubst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Nsubst),Flist1(fast_inverse(fast_immediate(10)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" = fast_inverse("))))));
COMP(STREAM,fast_convert(fast_car(LSsubst)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(");~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fshelterpush(arg"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Nsubst),Flist1(fast_inverse(fast_immediate(10)))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(");~%"))))));
temp1 = fast_convert(fast_cdr(LSsubst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
LSsubst = temp1;
Nsubst = temp2;
}
res = T;res;});
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = fast_convert(Fcallsubr(Fcar(Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")),"))))));
res = COMP_SUBRCALL3(STREAM,fast_immediate(1),Flength(fast_convert(fast_cdr(X))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("));~%"))))));
res = ({int res;
int LSsubst = fast_convert(fast_convert(fast_cdr(X)));int Nsubst = fast_convert(fast_immediate(1));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LSsubst)))) == NIL){
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fshelterpop();~%"))))));
temp1 = fast_convert(fast_cdr(LSsubst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
LSsubst = temp1;
Nsubst = temp2;
}
res = T;res;});
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_SUBRCALL1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Flist1(fast_inverse("))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));}
else{
res = COMP_SUBRCALL2(STREAM,X,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_SUBRCALL2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Flist1(fast_inverse("))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcons(fast_inverse("))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),"))))));
res = COMP_SUBRCALL2(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_SUBRCALL3(int STREAM,int M,int N){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(M),fast_convert(N)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Flist1(arg"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(M),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcons(arg"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(M),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = COMP_SUBRCALL3(STREAM,fast_plus(fast_convert(M),fast_convert(fast_immediate(1))),N);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_LABELS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
COMP_LABELS1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = ({int res;
int BODY1subst = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(BODY1subst)))) == NIL){
({int res;
if(fast_not(NOT_NEED_RES_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
COMP(STREAM,fast_convert(fast_car(BODY1subst)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
temp1 = fast_convert(fast_cdr(BODY1subst));
BODY1subst = temp1;
}
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("~%"))))));
res = ({int res;
 res = Fset_cdr(Fmakesym("FUNCTION-ARG"),fast_inverse(DROP(Flength(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))),fast_convert(Fcdr(Fmakesym("FUNCTION-ARG"))))));res;});res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_LABELS1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_LABELS1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else{
res = COMP_LABELS2(STREAM,fast_convert(fast_car(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_LABELS1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_LABELS2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_smallerp(fast_convert(Flength(X)),fast_convert(fast_immediate(3))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("labels: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("labels: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0)))))));res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("labels: not list"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("labels: not exist body"),X);res;});}
 else res = NIL;res;})
;
res = ({int res;int LOCAL_NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0)))))));int ARGS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));({int res;
 res = Fset_cdr(Fmakesym("FUNCTION-ARG"),fast_inverse(Fcons(fast_inverse(Fcons(fast_inverse(LOCAL_NAME),fast_inverse(COUNT_ARGS(ARGS)))),fast_inverse(fast_convert(Fcdr(Fmakesym("FUNCTION-ARG")))))));res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(CONV_NAME(LOCAL_NAME)),Flist1(fast_inverse(NIL))))));
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS);}
else{
res = TYPE_GEN_ARG2(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS,LOCAL_ARGUMENT_TYPE(NAME,LOCAL_NAME));}res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("{~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int res;~%"))))));
({int res=NIL;
if((fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) && HAS_TAIL_RECUR_P(BODY,LOCAL_NAME)) != NIL){
res = GEN_ARG3(Flength(ARGS));}
else if((fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE"))) && HAS_TAIL_RECUR_P(BODY,LOCAL_NAME)) != NIL){
res = TYPE_GEN_ARG3(Flength(ARGS),LOCAL_ARGUMENT_TYPE(NAME,LOCAL_NAME));}
;res;});
({int res=NIL;
if(HAS_TAIL_RECUR_P(BODY,LOCAL_NAME) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(CONV_NAME(LOCAL_NAME)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("loop:~%"))))));}
;res;});
({int res=NIL;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_SHELTERPUSH(fast_convert(Fcdr(Fmakesym("CODE2"))),ARGS);
res = GEN_CHECKGC();}
;res;});
res = ({int res;
int BODY1subst = fast_convert(BODY);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(BODY1subst)))) == NIL){
({int res;
if(fast_not(NOT_NEED_RES_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
COMP(fast_convert(Fcdr(Fmakesym("CODE2"))),fast_convert(fast_car(BODY1subst)),({int arg1,arg2,res;
arg1 = fast_inverse(ARGS);
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(";~%"))))));
temp1 = fast_convert(fast_cdr(BODY1subst));
BODY1subst = temp1;
}
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = GEN_SHELTERPOP(fast_convert(Fcdr(Fmakesym("CODE2"))),fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(ARGS)))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("return(res);}~%"))))));res;});
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_LET(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("let: not list"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;"))))));
COMP_LET1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = ({int res;
int BODY1subst = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY1subst)))))) == NIL){
COMP(STREAM,fast_convert(fast_car(BODY1subst)),({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("CAR"))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))));
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(BODY1subst));
BODY1subst = temp1;
}
({int res;
if(fast_not(TAILCALLP(fast_convert(fast_car(BODY1subst)),TAIL,NAME)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
COMP(STREAM,fast_convert(fast_car(BODY1subst)),({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("CAR"))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))));
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})~%"))))));res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_LETstar(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("let*: not list"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;"))))));
COMP_LET1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("CAR"))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))));
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = ({int res;
int BODY1subst = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(BODY1subst)))))) == NIL){
COMP(STREAM,fast_convert(fast_car(BODY1subst)),({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("CAR"))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))));
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(BODY1subst));
BODY1subst = temp1;
}
({int res;
if(fast_not(TAILCALLP(fast_convert(fast_car(BODY1subst)),TAIL,NAME)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
COMP(STREAM,fast_convert(fast_car(BODY1subst)),({int arg1,arg2,res;
arg1 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("CAR"))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))));
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(BODY1subst)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})~%"))))));res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int NOT_NEED_RES_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("NOT-NEED-RES"))))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int NOT_NEED_COLON_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("NOT-NEED-COLON"))))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int TAILCALLP(int X,int TAIL,int NAME){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = TAIL) != NIL)
if((res=({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X))))) != NIL)
if((res=fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(NAME))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_LET1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_LET1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else{
res = COMP_LET2(STREAM,fast_convert(fast_car(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_LET1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_LET2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("let: illegal let form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("int "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(CONV_NAME(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0)))))))),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" = fast_convert("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(");"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_COND(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res=NIL;~%if("))))));
COMP(STREAM,fast_convert(fast_car(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))),ENV,ARGS,TAIL,NAME,GLOBAL,T,CLOS);
({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" != NIL){~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("){~%"))))));}res;})
;
COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = COMP_COND1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_COND1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_COND1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));}
else if(fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_convert(T)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else{~%"))))));
res = COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(fast_car(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else if("))))));
res = COMP(STREAM,fast_convert(fast_car(fast_convert(fast_car(X)))),ENV,ARGS,NIL,NAME,GLOBAL,T,CLOS);
res = ({int res;
if(fast_not(fast_convert(Fcdr(Fmakesym("OPTIMIZE-ENABLE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" != NIL){~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("){~%"))))));}res;})
;
res = COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(fast_car(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_COND1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_COND2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_COND2loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("cond: illegal form"),X);res;});}
 else res = NIL;res;})
;
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = ({int res;
if((fast_not(TAILCALLP(fast_convert(fast_car(X)),T,NAME)) && fast_not(NOT_NEED_RES_P(fast_convert(fast_car(X))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,T,NAME,GLOBAL,TEST,CLOS);
res = ({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";"))))));}
 else res = NIL;res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("}~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = ({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_COND2loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CASE(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("case: illegal form"),fast_convert(fast_car(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))));res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%if(Fmember(fast_inverse("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),"))))));
LIST_TO_C1(STREAM,fast_convert(fast_car(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") != NIL){~%"))))));
COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = COMP_CASE1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CASE1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS,int KEY){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10;
COMP_CASE1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(CELLRANGE(KEY)) Fshelterpush(KEY);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));}
else if(fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_convert(T)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else{~%"))))));
res = COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(fast_car(X)))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else if(Fmember(fast_inverse("))))));
res = COMP(STREAM,KEY,ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),"))))));
res = LIST_TO_C1(STREAM,fast_convert(fast_car(fast_convert(fast_car(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") != NIL){~%"))))));
res = COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(fast_car(X)))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
temp10 = KEY;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(KEY)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
KEY = temp10;
goto COMP_CASE1loop;};}
;res;});
if(CELLRANGE(KEY)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CASE_USING(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%if(Fmember1(fast_inverse("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),"))))));
LIST_TO_C1(STREAM,fast_convert(fast_car(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3)))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") != NIL){~%"))))));
COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3)))))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = COMP_CASE_USING1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CASE_USING1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS,int KEY,int PRED){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10,temp11;
COMP_CASE_USING1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(CELLRANGE(KEY)) Fshelterpush(KEY);
if(CELLRANGE(PRED)) Fshelterpush(PRED);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));}
else if(fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_convert(T)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else{~%"))))));
res = COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(fast_car(X)))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else if(Fmember1(fast_inverse("))))));
res = COMP(STREAM,KEY,ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),"))))));
res = LIST_TO_C1(STREAM,fast_convert(fast_car(fast_convert(fast_car(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = COMP(STREAM,PRED,ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") != NIL){~%"))))));
res = COMP_COND2(STREAM,fast_convert(fast_cdr(fast_convert(fast_car(X)))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
temp10 = KEY;
temp11 = PRED;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(KEY)) Fshelterpop();
if(CELLRANGE(PRED)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
KEY = temp10;
PRED = temp11;
goto COMP_CASE_USING1loop;};}
;res;});
if(CELLRANGE(PRED)) Fshelterpop();
if(CELLRANGE(KEY)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int HAS_TAIL_RECUR_P(int X,int NAME){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else{
res = HAS_TAIL_RECUR_P1(LAST(X),NAME);}
;res;});
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int HAS_TAIL_RECUR_P1(int X,int NAME){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X))))) != NIL){
res = NIL;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(NAME)) != NIL){
res = T;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("COND"))) != NIL){
res = ANY(({Fset_cdr(Fmakesym("compiler2"),Fcons(NAME,Fcons(T,NIL)));Fcar(Fmakesym("compiler2"));}),fast_convert(fast_cdr(X)));}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("IF"))) != NIL){
res = ({int res;
if((res=HAS_TAIL_RECUR_P1(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),NAME)) == NIL)
if((res=({int res;
if((res = fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(4)))) != NIL)
if((res=HAS_TAIL_RECUR_P1(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3)))))),NAME)) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
;}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET"))) != NIL){
res = HAS_TAIL_RECUR_P(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),NAME);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET*"))) != NIL){
res = HAS_TAIL_RECUR_P(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),NAME);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("DYNAMIC-LET"))) != NIL){
res = HAS_TAIL_RECUR_P(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),NAME);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("PROGN"))) != NIL){
res = HAS_TAIL_RECUR_P(fast_convert(fast_cdr(X)),NAME);}
else if(fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("BLOCK"))) != NIL){
res = HAS_TAIL_RECUR_P(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),NAME);}
else{
res = NIL;}
;res;});
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_FOR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int VARS1 = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int VAR2 = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("CAR"))),Flist1(fast_inverse(VARS1))))));int VAR1 = fast_convert(SUBST(VAR2));int VARS = fast_convert(COMP_FOR3(VARS1,VAR2,VAR1));int END = fast_convert(ALPHA_CONV(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),VAR2,VAR1));int BODY = fast_convert(ALPHA_CONV(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))),VAR2,VAR1));({int res;
if(ANY(({Fset_cdr(Fmakesym("compiler3"),Fcons(T,NIL));Fcar(Fmakesym("compiler3"));}),VARS) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("for: illegal variable"),VARS);res;});}
 else res = NIL;res;})
;
({int res;
if(ANY(({Fset_cdr(Fmakesym("compiler4"),Fcons(T,NIL));Fcar(Fmakesym("compiler4"));}),VAR1) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("for: illegal variable"),VARS);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%"))))));
COMP_LET1(STREAM,VARS,ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
GEN_ARG3(Flength(VARS));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("while("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(END),Flist1(fast_inverse(fast_immediate(0)))))),({int arg1,arg2,res;
arg1 = fast_inverse(VAR1);
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" == NIL){~%"))))));
COMP_FOR1(STREAM,BODY,({int arg1,arg2,res;
arg1 = fast_inverse(VAR1);
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
COMP_FOR2(STREAM,VARS,({int arg1,arg2,res;
arg1 = fast_inverse(VAR1);
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(END))))))) != NIL){
res = COMP_PROGN1(STREAM,fast_convert(fast_cdr(END)),({int arg1,arg2,res;
arg1 = fast_inverse(VAR1);
Fshelterpush(arg1);
arg2 = fast_inverse(ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res=NIL;"))))));}res;})
;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})"))))));
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FOR1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_FOR1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else{
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_FOR1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FOR2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
int UPDATEsubst = fast_convert(X);int Nsubst = fast_convert(fast_immediate(1));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(UPDATEsubst)))) == NIL){
({int res;
if(fast_numeqp(fast_convert(Flength(fast_convert(fast_car(UPDATEsubst)))),fast_convert(fast_immediate(3))) != NIL){
res = ({int res;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("temp"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Nsubst),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" = "))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(UPDATEsubst))),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));res;});}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(UPDATEsubst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
UPDATEsubst = temp1;
Nsubst = temp2;
}
res = T;res;});
({int res;
int UPDATEsubst = fast_convert(X);int Nsubst = fast_convert(fast_immediate(1));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(UPDATEsubst)))) == NIL){
({int res;
if(fast_numeqp(fast_convert(Flength(fast_convert(fast_car(UPDATEsubst)))),fast_convert(fast_immediate(3))) != NIL){
res = ({int res;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(UPDATEsubst))),Flist1(fast_inverse(fast_immediate(0))))))),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" = temp"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Nsubst),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));res;});}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(UPDATEsubst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
UPDATEsubst = temp1;
Nsubst = temp2;
}
res = T;res;});
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("}~%"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FOR3(int VARS,int VAR,int SUBST){
int res;
if(CELLRANGE(VARS)) Fshelterpush(VARS);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(CELLRANGE(SUBST)) Fshelterpush(SUBST);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("compiler5"),Fcons(VAR,Fcons(SUBST,Fcons(VAR,Fcons(SUBST,Fcons(VAR,Fcons(SUBST,Fcons(T,NIL))))))));Fcar(Fmakesym("compiler5"));})),Flist1(fast_inverse(VARS)))));
if(CELLRANGE(SUBST)) Fshelterpop();
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(VARS)) Fshelterpop();
return(res);}
int COMP_PROGN(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%"))))));
COMP_PROGN1(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_PROGN1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_PROGN1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = ({int res;
if((fast_not(NOT_NEED_RES_P(fast_convert(fast_car(X)))) && fast_not(TAILCALLP(fast_convert(fast_car(X)),TAIL,NAME))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = ({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";"))))));}
 else res = NIL;res;})
;}
else{
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = ({int res;
if(fast_not(NOT_NEED_COLON_P(fast_convert(fast_car(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));}
 else res = NIL;res;})
;
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_PROGN1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_AND(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%if((res = "))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") != NIL)~%"))))));
COMP_AND1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else res=NIL;res;})~%"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_AND1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res=res;"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Fmakestr("if((res=")),Fcons(fast_inverse(ENV),Fcons(fast_inverse(ARGS),Fcons(fast_inverse(TAIL),Fcons(fast_inverse(NAME),Flist1(fast_inverse(GLOBAL))))))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") !=NIL)~%res=res;~%else res=NIL;~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("if((res="))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") != NIL)~%"))))));
res = COMP_AND1(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else res=NIL;"))))));}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_OR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%if((res="))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") == NIL)~%"))))));
COMP_OR1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else res=res;res;})~%"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_OR1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = res;"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Fmakestr("if((res=")),Fcons(fast_inverse(ENV),Fcons(fast_inverse(ARGS),Fcons(fast_inverse(TAIL),Fcons(fast_inverse(NAME),Flist1(fast_inverse(GLOBAL))))))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") !=NIL)~%res=res;~%else res=NIL;~%"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("if((res="))))));
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(") == NIL)~%"))))));
res = COMP_OR1(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("else res=res;"))))));}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_TEST_AND(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("("))))));
COMP_TEST_AND1(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_TEST_AND1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_TEST_AND1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);}
else{
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" && "))))));
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_TEST_AND1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_TEST_OR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("("))))));
COMP_TEST_OR1(STREAM,fast_convert(fast_cdr(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_TEST_OR1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_TEST_OR1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);}
else{
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" || "))))));
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_TEST_OR1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_WHILE(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("while: not exist body"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%while("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,T,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" !=NIL){~%"))))));
COMP_PROGN1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("};res;})~%"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_SETQ(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("setq: not symbol"),X);res;});}
 else res = NIL;res;})
;
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(ENV))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~% res = "))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(" = "))))));
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})~%"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(CLOS))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~% res = "))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_setnth(Fcdr(Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(NAME),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")),"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(POSITION(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),CLOS)),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(");res;})"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~% res = "))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fset_cdr(Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),fast_inverse("))))));
res = COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,NIL,NAME,T,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("));res;})"))))));}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_TAGBODY(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("tagbody: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(CONV_NAME(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(":~%"))))));
COMP_TAGBODY1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})~%"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_TAGBODY1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_TAGBODY1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(CONV_NAME(fast_convert(fast_car(X)))),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(":~%"))))));
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_TAGBODY1loop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(X)))))) != NIL){
res = ({int res;
if((fast_not(NOT_NEED_RES_P(fast_convert(fast_car(X)))) && fast_not(TAILCALLP(fast_convert(fast_car(X)),TAIL,NAME))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res = "))))));}
 else res = NIL;res;})
;
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";"))))));}
else{
res = COMP(STREAM,fast_convert(fast_car(X)),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_TAGBODY1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_GO(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("go: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("goto "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(CONV_NAME(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";~%"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CONVERT(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("convert: not symbol"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("convert: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert(Fconvert(fast_inverse("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")))"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_FUNCTION(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("function: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("function: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcar(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"))"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_SYMBOL_FUNCTION(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("symbol-function: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("symbol-function: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcar("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CLASS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("class: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("class: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Faux(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"))"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_SYMBOL_CLASS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("class: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("class: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Faux("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CATCH(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TAG = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_immediate(1)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res,ret,i;~% "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("i = Fgetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"));~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fsetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),i+1);~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("ret=setjmp(c_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(TAG)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("[i]);"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("if(ret == 0){~%"))))));
COMP_PROGN1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fsetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),i);~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("}~% else{~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("ret = 0;~%"))))));
({int res=NIL;
if(fast_convert(Fcdr(Fmakesym("UNWIND-THUNK"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("UNWIND-THUNK")))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("();"))))));}
;res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res=catch_arg;}~%"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})"))))));
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_THROW(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TAG = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_immediate(1)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res,i;~%"))))));
COMP_PROGN1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("catch_arg=res;~% "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("i = Fgetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"));~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fsetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),i-1);~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("longjmp(c_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(TAG)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("[i-1],1);res;})~%"))))));
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_BLOCK(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("block: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;int TAG = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res,ret,i;~% "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("i = Fgetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"));~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fsetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),i+1);~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("ret=setjmp(c_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(TAG)),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("[i]);"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("if(ret == 0){~%"))))));
COMP_PROGN1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fsetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),i);~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("}~% else{~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("ret = 0;~%"))))));
({int res=NIL;
if(fast_convert(Fcdr(Fmakesym("UNWIND-THUNK"))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("UNWIND-THUNK")))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("();"))))));}
;res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res=block_arg;}~%"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})"))))));
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_RETURN_FROM(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("return-from: not symbol"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));res;});}
 else res = NIL;res;})
;
res = ({int res;int TAG = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res,i;~%"))))));
COMP_PROGN1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("block_arg=res;~% "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("i = Fgetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"));~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fsetprop(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(TAG),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),i-1);~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("longjmp(c_"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(TAG)),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("[i-1],1);res;})~%"))))));
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_UNWIND_PROTECT(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res;~%"))))));
({int res;
 res = Fset_cdr(Fmakesym("UNWIND-THUNK"),fast_inverse(COMP_UNWIND_PROTECT1(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV)));res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res="))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(";res;})"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_UNWIND_PROTECT1(int BODY,int ENV){
int res;
if(CELLRANGE(BODY)) Fshelterpush(BODY);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(({int arg1,arg2,res;
arg1 = fast_inverse(Fcons(Fmakesym("LAMBDA"),Fcons(NIL,NIL)));
Fshelterpush(arg1);
arg2 = fast_inverse(BODY);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}));int NAME = fast_convert(LAMBDA_NAME());int ARGS = fast_convert(Fmakesym("NIL"));int FREE = fast_convert(FIND_FREE_VARIABLE(BODY,ARGS,ENV));COMP_LAMBDA0(X,NAME);
COMP_LAMBDA1(X,NAME);
COMP_LAMBDA2(BODY,ENV,ARGS,NAME,FREE);
COMP_LAMBDA3(NAME);
res = NAME;
res;})
;
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(BODY)) Fshelterpop();
return(res);}
int COMP_SETF(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("setf: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if((fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(T)) || fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(NIL))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("setf: can't modify"),X);res;});}
 else res = NIL;res;})
;
res = ({int res;int FORM = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int VAL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_eq(fast_convert(fast_convert(fast_car(FORM))),fast_convert(Fmakesym("AREF")))) != NIL){
res = ({int res;int NEWFORM = fast_convert(Fcons(fast_inverse(Fmakesym("SET-AREF")),fast_inverse(Fcons(fast_inverse(VAL),fast_inverse(fast_convert(fast_cdr(FORM)))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_eq(fast_convert(fast_convert(fast_car(FORM))),fast_convert(Fmakesym("GAREF")))) != NIL){
res = ({int res;int NEWFORM = fast_convert(Fcons(fast_inverse(Fmakesym("SET-GAREF")),fast_inverse(Fcons(fast_inverse(VAL),fast_inverse(fast_convert(fast_cdr(FORM)))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_eq(fast_convert(fast_convert(fast_car(FORM))),fast_convert(Fmakesym("ELT")))) != NIL){
res = ({int res;int NEWFORM = fast_convert(Fcons(fast_inverse(Fmakesym("SET-ELT")),fast_inverse(Fcons(fast_inverse(VAL),fast_inverse(fast_convert(fast_cdr(FORM)))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_eq(fast_convert(fast_convert(fast_car(FORM))),fast_convert(Fmakesym("PROPERTY")))) != NIL){
res = ({int res;int NEWFORM = fast_convert(Fcons(fast_inverse(Fmakesym("SET-PROPERTY")),fast_inverse(Fcons(fast_inverse(VAL),fast_inverse(fast_convert(fast_cdr(FORM)))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_numeqp(fast_convert(Flength(FORM)),fast_convert(fast_immediate(2))) && fast_eq(fast_convert(fast_convert(fast_car(FORM))),fast_convert(Fmakesym("CAR")))) != NIL){
res = ({int res;int NEWFORM = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SET-CAR")),Fcons(fast_inverse(VAL),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(fast_immediate(1)))))))))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_numeqp(fast_convert(Flength(FORM)),fast_convert(fast_immediate(2))) && fast_eq(fast_convert(fast_convert(fast_car(FORM))),fast_convert(Fmakesym("CDR")))) != NIL){
res = ({int res;int NEWFORM = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SET-CDR")),Fcons(fast_inverse(VAL),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(fast_immediate(1)))))))))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_eq(fast_convert(fast_convert(fast_car(FORM))),fast_convert(Fmakesym("DYNAMIC")))) != NIL){
res = ({int res;int NEWFORM = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SET-DYNAMIC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(VAL)))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(FORM)))) && fast_numeqp(fast_convert(Flength(FORM)),fast_convert(fast_immediate(2))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(fast_immediate(0)))))))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;int NEWFORM = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SET-SLOT-VALUE")),Fcons(fast_inverse(VAL),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(NIL))))))))))))))))))))));res = COMP(STREAM,NEWFORM,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(FORM)))) != NIL){
res = COMP_SETQ(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SETQ")),Fcons(fast_inverse(FORM),Flist1(fast_inverse(VAL)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);}
else{
res = ERRORstar(Fmakestr("setf: illegal form"),X);}
;res;});
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_DYNAMIC(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("dynamic: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("dynamic: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert(Ffinddyn(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")))"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_DYNAMIC_LET(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("({int res,val,save,dynpt;~% save=Fgetdynpt();~%"))))));
COMP_DYNAMIC_LET1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
COMP_PROGN1(STREAM,fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("res;})"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_DYNAMIC_LET1(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
int temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
COMP_DYNAMIC_LET1loop:
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else{
res = COMP_DYNAMIC_LET2(STREAM,fast_convert(fast_car(X)),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
{
temp1 = STREAM;
temp2 = fast_convert(fast_cdr(X));
temp3 = ENV;
temp4 = ARGS;
temp5 = TAIL;
temp6 = NAME;
temp7 = GLOBAL;
temp8 = TEST;
temp9 = CLOS;
if(CELLRANGE(STREAM)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(CLOS)) Fshelterpop();
STREAM = temp1;
X = temp2;
ENV = temp3;
ARGS = temp4;
TAIL = temp5;
NAME = temp6;
GLOBAL = temp7;
TEST = temp8;
CLOS = temp9;
goto COMP_DYNAMIC_LET1loop;};}
;res;});
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_DYNAMIC_LET2(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("dynamic-let: illegal let form"),X);res;});}
 else res = NIL;res;})
;
res = ({int res;int SYMBOL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0)))))));int VALUE = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("dynpt=Fgetdynpt();Fshelterpush(dynpt);Fsetdynpt(save);~%"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("val=fast_inverse("))))));
COMP(STREAM,VALUE,ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(");Fsetdynpt(dynpt);Fshelterpop();"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fadddynenv(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(SYMBOL),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),val);"))))));
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_NOT(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("not: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_not("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CAR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("car: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("car: illegal argument"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert(fast_car("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CDR(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("cdr: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("cdr: illegal argument"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_convert(fast_cdr("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_CONS(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("cons: illegal form"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcons(fast_inverse("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("),fast_inverse("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ENV,ARGS,NIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_LENGTH(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("length: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-VECTOR-P")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("length: illegal argument"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Flength("))))));
COMP(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_C_INCLUDE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("c-include: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("c-include: argument must be string"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("#include "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("~%"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_C_DEFINE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("c-define: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("c-define: argument must be string"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("#define "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr(" "))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE0")))),Flist1(fast_inverse(Fmakestr("~%"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_C_LANG(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("c-lang: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("c-lang: argument must be string"),X);res;});}
 else res = NIL;res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("~%"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_C_OPTION(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res = Fset_cdr(Fmakesym("C-LANG-OPTION"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakeint(1))))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFGLOBAL(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int SYMBOL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int VALUE = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Fset_cdr(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Fcons(fast_inverse(SYMBOL),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("\"),"))))));
COMP(fast_convert(Fcdr(Fmakesym("CODE4"))),VALUE,NIL,NIL,NIL,NIL,T,NIL,NIL);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(");"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Fset_opt(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Fcons(fast_inverse(SYMBOL),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("\"),FAST_GLOBAL);~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFCONSTANT(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int SYMBOL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int VALUE = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Fset_cdr(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Fcons(fast_inverse(SYMBOL),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("\"),"))))));
COMP(fast_convert(Fcdr(Fmakesym("CODE4"))),VALUE,NIL,NIL,NIL,NIL,T,NIL,NIL);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(");"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Fset_opt(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Fcons(fast_inverse(SYMBOL),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("\"),FAST_CONSTN);~%"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFDYNAMIC(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("defdynamic: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = Fapply(Fcar(Fmakesym("ERROR:")),Fcons(fast_inverse(Fmakestr("defdynamic: not symbol")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))));res;});}
 else res = NIL;res;})
;
res = ({int res;int SYMBOL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int VALUE = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Fsetdynenv(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Fcons(fast_inverse(SYMBOL),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("\"),"))))));
COMP(fast_convert(Fcdr(Fmakesym("CODE4"))),VALUE,NIL,NIL,NIL,NIL,T,NIL,NIL);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(");"))))));
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_SET_DYNAMIC(int STREAM,int X,int ENV,int ARGS,int TAIL,int NAME,int GLOBAL,int TEST,int CLOS){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(ENV)) Fshelterpush(ENV);
if(CELLRANGE(ARGS)) Fshelterpush(ARGS);
if(CELLRANGE(TAIL)) Fshelterpush(TAIL);
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(GLOBAL)) Fshelterpush(GLOBAL);
if(CELLRANGE(TEST)) Fshelterpush(TEST);
if(CELLRANGE(CLOS)) Fshelterpush(CLOS);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(3)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("set-dynamic: illegal form"),X);res;});}
 else res = NIL;res;})
;
({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = ({int res;
res = Fapply(Fcar(Fmakesym("ERROR:")),Fcons(fast_inverse(Fmakestr("set-dynamic: not symbol")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))));res;});}
 else res = NIL;res;})
;
res = ({int res;int SYMBOL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int VALUE = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fsetdynamic(Fmakesym(\""))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(SYMBOL),Flist1(fast_inverse(NIL))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\"),fast_inverse("))))));
COMP(STREAM,VALUE,ENV,ARGS,TAIL,NAME,GLOBAL,TEST,CLOS);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("))"))))));
res;})
;
if(CELLRANGE(CLOS)) Fshelterpop();
if(CELLRANGE(TEST)) Fshelterpop();
if(CELLRANGE(GLOBAL)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
if(CELLRANGE(TAIL)) Fshelterpop();
if(CELLRANGE(ARGS)) Fshelterpop();
if(CELLRANGE(ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int COMP_DEFMACRO(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Feval("))))));
LIST_TO_C1(fast_convert(Fcdr(Fmakesym("CODE4"))),X);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(");~%"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFCLASS(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
COMP(fast_convert(Fcdr(Fmakesym("CODE4"))),Fcons(Fmakesym("IGNORE-TOPLEVEL-CHECK"),Fcons(T,NIL)),NIL,NIL,NIL,NIL,NIL,NIL,NIL);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(";Feval("))))));
LIST_TO_C1(fast_convert(Fcdr(Fmakesym("CODE4"))),X);
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(");"))))));
COMP(fast_convert(Fcdr(Fmakesym("CODE4"))),Fcons(Fmakesym("IGNORE-TOPLEVEL-CHECK"),Fcons(NIL,NIL)),NIL,NIL,NIL,NIL,NIL,NIL,NIL);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(";~%"))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COMP_DEFMETHOD(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(Fmakesym("CREATE"))) || fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(Fmakesym("INITIALIZE-OBJECT")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr("Feval("))))));
res = LIST_TO_C1(fast_convert(Fcdr(Fmakesym("CODE4"))),X);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE4")))),Flist1(fast_inverse(Fmakestr(");~%"))))));}
else{
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARG = fast_convert(({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3))))));}res;})
);int RES = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(NAME),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("GENERIC-NAME-ARG")))))))));({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(RES)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("not exist defgeneric "),NAME);res;});}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(HAS_SAME_VARLIS_P(ARG,fast_convert(fast_cdr(RES)))) != NIL){
res = ({int res;
res = ERRORstar(Fmakestr("args variable name must be same"),fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(fast_convert(fast_cdr(RES))))))));res;});}
 else res = NIL;res;})
;
res;})
;}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int HAS_SAME_VARLIS_P(int X,int Y){
int res;
int temp1,temp2;
HAS_SAME_VARLIS_Ploop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(Y))))) != NIL){
res = T;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(Y)))))) != NIL){
res = NIL;}
else if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(Y))))) != NIL){
res = NIL;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(Y)))))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(fast_convert(fast_car(Y))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = fast_convert(fast_cdr(Y));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
X = temp1;
Y = temp2;
goto HAS_SAME_VARLIS_Ploop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(Y)))))) && fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(Y))),Flist1(fast_inverse(fast_immediate(0))))))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = fast_convert(fast_cdr(Y));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
X = temp1;
Y = temp2;
goto HAS_SAME_VARLIS_Ploop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(Y)))))) && fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(fast_convert(fast_car(Y))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = fast_convert(fast_cdr(Y));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
X = temp1;
Y = temp2;
goto HAS_SAME_VARLIS_Ploop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(Y)))))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(Y))),Flist1(fast_inverse(fast_immediate(0))))))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = fast_convert(fast_cdr(Y));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
X = temp1;
Y = temp2;
goto HAS_SAME_VARLIS_Ploop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CONV_NAME(int SYM){
int res;
if(CELLRANGE(SYM)) Fshelterpush(SYM);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fconvert(fast_inverse(CONV_NAME1(fast_convert(Fconvert(fast_inverse(fast_convert(Fconvert(fast_inverse(SYM),Fmakesym("<STRING>")))),Fmakesym("<LIST>"))))),Fmakesym("<SYMBOL>")));
if(CELLRANGE(SYM)) Fshelterpop();
return(res);}
int CONV_NAME1(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("0")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("zero")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("1")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("one")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("2")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("two")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("3")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("three")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("4")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("four")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("5")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("five")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("6")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("six")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("7")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("seven")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("8")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("eight")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("9")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("nine")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else{
res = CONV_NAME2(LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CONV_NAME2(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS)))) != NIL){
res = Fmakestr("");}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("-")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("_")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("+")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("plus")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("*")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("star")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("/")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("slash")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("!")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("exclamation")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("%")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("percent")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("$")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("dollar")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("&")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("and")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("=")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("equal")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("^")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("hat")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("~")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("tilde")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("\\")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("yen")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("|")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("vertical")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("@")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("atmark")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("#")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("sharp")),Flist1(fast_inverse(CONV_NAME1(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar(":")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("colon")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar(">")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("greater")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("<")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("smaller")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("[")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("lbracket")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("]")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("rbracket")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("{")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("lcurl")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("}")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("rcurl")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar("?")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("question")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(fast_convert(fast_car(LS))),Flist1(fast_inverse(Fmakechar(".")))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(Fmakestr("dot")),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("STRING-APPEND")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_convert(fast_car(LS))),Fmakesym("<STRING>")))),Flist1(fast_inverse(CONV_NAME2(fast_convert(fast_cdr(LS))))))));}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int LIST_TO_C(int STREAM,int X){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("FIXNUMP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("fast_immediate("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("FLOATP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestrflt(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-FLOAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("BIGNUMP")),Flist1(fast_inverse(X)))) || fast_convert(Fcallsubr(Fcar(Fmakesym("LONGNUMP")),Flist1(fast_inverse(X))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakebig(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestr("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakechar("\\")))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(34)),Fmakesym("<CHARACTER>")))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakechar("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakechar("\\"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakechar("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-VECTOR-P")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fvector("))))));
res = LIST_TO_C1(STREAM,fast_convert(Fconvert(fast_inverse(X),Fmakesym("<LIST>"))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-ARRAY*-P")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Farray("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Flength(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X)))))),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = LIST_TO_C1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("READED-ARRAY-LIST")),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(X),fast_convert(T)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("T"))))));}
else if(fast_eq(fast_convert(X),fast_convert(NIL)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestr(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcons("))))));
res = LIST_TO_C(STREAM,fast_convert(fast_car(X)));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = LIST_TO_C(STREAM,fast_convert(fast_cdr(X)));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int LIST_TO_C1(int STREAM,int X){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("FIXNUMP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakeint("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("FLOATP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestrflt(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-FLOAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("BIGNUMP")),Flist1(fast_inverse(X)))) || fast_convert(Fcallsubr(Fcar(Fmakesym("LONGNUMP")),Flist1(fast_inverse(X))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakebig(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestr("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CHARACTERP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(Fmakechar("\\")))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(34)),Fmakesym("<CHARACTER>")))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakechar("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakechar("\\"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakechar("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-CHAR")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(fast_immediate(39)),Fmakesym("<CHARACTER>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-VECTOR-P")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fvector("))))));
res = LIST_TO_C1(STREAM,fast_convert(Fconvert(fast_inverse(X),Fmakesym("<LIST>"))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("GENERAL-ARRAY*-P")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Farray("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-INTEGER")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(Flength(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X)))))),Flist1(fast_inverse(fast_immediate(10)))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = LIST_TO_C1(STREAM,fast_convert(Fcallsubr(Fcar(Fmakesym("READED-ARRAY-LIST")),Flist1(fast_inverse(X)))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(X),fast_convert(T)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("T"))))));}
else if(fast_eq(fast_convert(X),fast_convert(NIL)) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("NIL"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakesym(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("STRINGP")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fmakestr(\""))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(X),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("\")"))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("Fcons("))))));
res = LIST_TO_C1(STREAM,fast_convert(fast_car(X)));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));
res = LIST_TO_C1(STREAM,fast_convert(fast_cdr(X)));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int QUASI_TRANSFER(int X,int N){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = NIL;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(X)))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("UNQUOTE"))) && fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("UNQUOTE-SPLICING"))) && fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("QUASI-QUOTE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LIST")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(Fmakesym("QUASI-QUOTE"))))))),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),fast_plus(fast_convert(N),fast_convert(fast_immediate(1))))))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_convert(Fmakesym("UNQUOTE"))) && fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("CONS")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(fast_cdr(X)),N)))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_convert(Fmakesym("UNQUOTE-SPLICING"))) && fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("APPEND")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(fast_cdr(X)),N)))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_convert(Fmakesym("UNQUOTE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("CONS")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LIST")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(Fmakesym("UNQUOTE"))))))),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(1)))))),fast_minus(fast_convert(N),fast_convert(fast_immediate(1))))))))))),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(fast_cdr(X)),N)))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_eq(fast_convert(fast_convert(fast_car(fast_convert(fast_car(X))))),fast_convert(Fmakesym("UNQUOTE-SPLICING")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("CONS")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LIST")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("QUOTE")),Flist1(fast_inverse(Fmakesym("UNQUOTE-SPLICING"))))))),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(1)))))),fast_minus(fast_convert(N),fast_convert(fast_immediate(1))))))))))),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(fast_cdr(X)),N)))))));}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("CONS")),Fcons(fast_inverse(QUASI_TRANSFER(fast_convert(fast_car(X)),N)),Flist1(fast_inverse(QUASI_TRANSFER(fast_convert(fast_cdr(X)),N)))))));}
;res;});
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int OPTIMIZE_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_greaterp(fast_convert(Flength(X)),fast_convert(fast_immediate(1))) != NIL){
res = ({int res;int FN = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int DT = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(FN),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION")))))))));res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(DT)))) != NIL){
res = NIL;}
else if((fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Fmakesym("DEFUN"))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(DT),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Faux(Fmakesym("<FIXNUM>"))),Flist1(fast_inverse(Faux(Fmakesym("<FLOAT>")))))))))))) && SUBSETP(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(DT),Flist1(fast_inverse(fast_immediate(2)))))),fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Faux(Fmakesym("<FIXNUM>"))),Flist1(fast_inverse(Faux(Fmakesym("<FLOAT>")))))))) && OPTIMIZE_P1(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(DT)))))))) != NIL){
res = T;}
else{
res = NIL;}
;res;});
res;})
;}
else{
res = NIL;}res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int OPTIMIZE_P1(int X){
int res;
int temp1;
OPTIMIZE_P1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Faux(Fmakesym("<FIXNUM>"))),Flist1(fast_inverse(Faux(Fmakesym("<FLOAT>")))))))))))) && SUBSETP(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(fast_immediate(2)))))),fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Faux(Fmakesym("<FIXNUM>"))),Flist1(fast_inverse(Faux(Fmakesym("<FLOAT>"))))))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
if(CELLRANGE(X)) Fshelterpop();
X = temp1;
goto OPTIMIZE_P1loop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int RETURN_TYPE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION"))))))))),Flist1(fast_inverse(fast_immediate(1))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int ARGUMENT_TYPE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION"))))))))),Flist1(fast_inverse(fast_immediate(2))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int LOCAL_RETURN_TYPE(int X,int Y){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int LOCAL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION"))))))))),Flist1(fast_inverse(fast_immediate(3)))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(Y),Flist1(fast_inverse(LOCAL)))))),Flist1(fast_inverse(fast_immediate(1))))));
res;})
;
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int LOCAL_ARGUMENT_TYPE(int X,int Y){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int LOCAL = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION"))))))))),Flist1(fast_inverse(fast_immediate(3)))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(Y),Flist1(fast_inverse(LOCAL)))))),Flist1(fast_inverse(fast_immediate(2))))));
res;})
;
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int TYPE_GEN_ARG2(int STREAM,int LS,int TYPE){
int res;
if(CELLRANGE(STREAM)) Fshelterpush(STREAM);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(TYPE)) Fshelterpush(TYPE);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("("))))));
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else{
res = ({int res;
int LS1subst = fast_convert(LS);int Nsubst = fast_convert(fast_immediate(0));int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(LS1subst)))))) == NIL){
({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(TYPE),Flist1(fast_inverse(Nsubst)))))),fast_convert(Faux(Fmakesym("<FIXNUM>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("int "))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(TYPE),Flist1(fast_inverse(Nsubst)))))),fast_convert(Faux(Fmakesym("<FLOAT>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("double "))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(","))))));}
;res;});
temp1 = fast_convert(fast_cdr(LS1subst));
temp2 = fast_plus(fast_convert(Nsubst),fast_convert(fast_immediate(1)));
LS1subst = temp1;
Nsubst = temp2;
}
res = ({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(TYPE),Flist1(fast_inverse(Nsubst)))))),fast_convert(Faux(Fmakesym("<FIXNUM>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("int "))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(TYPE),Flist1(fast_inverse(Nsubst)))))),fast_convert(Faux(Fmakesym("<FLOAT>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr("double "))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT-OBJECT")),Fcons(fast_inverse(STREAM),Fcons(fast_inverse(CONV_NAME(fast_convert(fast_car(LS1subst)))),Flist1(fast_inverse(NIL))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(STREAM),Flist1(fast_inverse(Fmakestr(")"))))));}
;res;});res;});}res;})
;
if(CELLRANGE(TYPE)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(STREAM)) Fshelterpop();
return(res);}
int TYPE_GEN_ARG3(int N,int LS){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_not(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)))) != NIL){
res = ({int res;
res = ({int res;
int Msubst = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(Msubst),fast_convert(N)) == NIL){
({int res=NIL;
if(fast_eq(fast_convert(fast_convert(fast_car(LS))),fast_convert(Faux(Fmakesym("<FIXNUM>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("int "))))));}
else if(fast_eq(fast_convert(fast_convert(fast_car(LS))),fast_convert(Faux(Fmakesym("<FLOAT>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("double "))))));}
;res;});
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("temp"))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr(";"))))));
temp1 = fast_plus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
Msubst = temp1;
}
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE2")))),Flist1(fast_inverse(Fmakestr("~%"))))));res;});res;});}
 else res = NIL;res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int TYPE_GEN_CALL(int NAME,int N){
int res;
if(CELLRANGE(NAME)) Fshelterpush(NAME);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME1 = fast_convert(CONV_NAME(NAME));int RETURN = fast_convert(RETURN_TYPE(NAME));int ARGUMENT = fast_convert(ARGUMENT_TYPE(NAME));res = ({int res=NIL;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(RETURN),fast_convert(Faux(Fmakesym("<FIXNUM>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("return(Fmakeint("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(NAME1),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("() ));~%"))))));}
else if(fast_eq(fast_convert(RETURN),fast_convert(Faux(Fmakesym("<FLOAT>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("return(Fmakedoubleflt("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(NAME1),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("() ));~%"))))));}
;res;});}
else{
res = ({int res=NIL;
if(fast_eq(fast_convert(RETURN),fast_convert(Faux(Fmakesym("<FIXNUM>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("return(Fmakeint("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(NAME1),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("("))))));}
else if(fast_eq(fast_convert(RETURN),fast_convert(Faux(Fmakesym("<FLOAT>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("return(Fmakedoubleflt("))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(NAME1),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("("))))));}
;res;});
res = ({int res;
int Msubst = fast_convert(fast_immediate(1));int temp1;
while(fast_numeqp(fast_convert(Msubst),fast_convert(N)) == NIL){
({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARGUMENT),Flist1(fast_inverse(fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1))))))))),fast_convert(Faux(Fmakesym("<FIXNUM>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("Fgetint(arg"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("),"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARGUMENT),Flist1(fast_inverse(fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1))))))))),fast_convert(Faux(Fmakesym("<FLOAT>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("Fgetflt(arg"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("),"))))));}
;res;});
temp1 = fast_plus(fast_convert(Msubst),fast_convert(fast_immediate(1)));
Msubst = temp1;
}
res = ({int res=NIL;
if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARGUMENT),Flist1(fast_inverse(fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1))))))))),fast_convert(Faux(Fmakesym("<FIXNUM>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("Fgetint(arg"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("))));~%"))))));}
else if(fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(ARGUMENT),Flist1(fast_inverse(fast_minus(fast_convert(Msubst),fast_convert(fast_immediate(1))))))))),fast_convert(Faux(Fmakesym("<FLOAT>")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("Fgetflt(arg"))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(fast_convert(Fconvert(fast_inverse(Msubst),Fmakesym("<STRING>"))))))));
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("CODE1")))),Flist1(fast_inverse(Fmakestr("))));~%"))))));}
;res;});res;});}
;res;});
res;})
;
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(NAME)) Fshelterpop();
return(res);}
int SUBSETP(int X,int Y){
int res;
int temp1,temp2;
SUBSETPloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Y))))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = Y;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
X = temp1;
Y = temp2;
goto SUBSETPloop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CLASS_DYNAMIC(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(C),fast_convert(Fmakesym("<STRING>"))) != NIL){
res = Faux(Fmakesym("<STRING>"));}
else if(fast_eq(fast_convert(C),fast_convert(Fmakesym("<LIST>"))) != NIL){
res = Faux(Fmakesym("<LIST>"));}
else if(fast_eq(fast_convert(C),fast_convert(Fmakesym("<NUMBER>"))) != NIL){
res = Faux(Fmakesym("<NUMBER>"));}
else if(fast_eq(fast_convert(C),fast_convert(Fmakesym("<VECTOR>"))) != NIL){
res = Faux(Fmakesym("<VECTOR>"));}
else if(fast_eq(fast_convert(C),fast_convert(Fmakesym("<FLOAT>"))) != NIL){
res = Faux(Fmakesym("<FLOAT>"));}
else{
res = Faux(Fmakesym("<OBJECT>"));}
;res;});
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int WARNING(int STR,int X){
int res;
if(CELLRANGE(STR)) Fshelterpush(STR);
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Fcons(fast_inverse(Fmakestr("warning ~A ~A ~A~%")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("INFERENCE-NAME")))),Fcons(fast_inverse(STR),Flist1(fast_inverse(X))))))));
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(STR)) Fshelterpop();
return(res);}
int INFERENCE_FILE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
fast_convert(Fcallsubr(Fcar(Fmakesym("FORMAT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("STANDARD-OUTPUT")),NIL))),Flist1(fast_inverse(Fmakestr("type inference~%"))))));
({int res;
 res = Fset_cdr(Fmakesym("FILE-NAME-AND-EXT"),fast_inverse(X));res;});
({int res;
 res = Fset_cdr(Fmakesym("TYPE-FUNCTION"),fast_inverse(NIL));res;});
({int res;
 res = Fset_cdr(Fmakesym("INSTREAM"),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("OPEN-INPUT-FILE")),Flist1(fast_inverse(X))))));res;});
({int res;int SEXP = fast_convert(NIL);({int res;
while(({int res;
 res = SEXP = fast_convert(Fcallsubr(Fcar(Fmakesym("READ")),Fcons(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))),Fcons(fast_inverse(NIL),Flist1(fast_inverse(NIL))))));res;})
 !=NIL){
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(SEXP)))) && fast_eq(fast_convert(fast_convert(fast_car(SEXP))),fast_convert(Fmakesym("DEFUN")))) != NIL){
res = INFERENCE_DEFUN(SEXP);}
;res;});};res;})
;
fast_convert(Fcallsubr(Fcar(Fmakesym("CLOSE")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("INSTREAM")))))));
res = ({int res;
 res = Fset_cdr(Fmakesym("INSTREAM"),fast_inverse(NIL));res;});
res;})
;
res = T;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_DEFUN(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int ARG = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))));int INIT_TYPE_INPUT = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-LIST")),Fcons(fast_inverse(Flength(ARG)),Flist1(fast_inverse(Faux(Fmakesym("<OBJECT>"))))))));int INIT_ENV = fast_convert(CREATE_INIT_ENV(ARG));({int res;
 res = Fset_cdr(Fmakesym("INFERENCE-NAME"),fast_inverse(NAME));res;});
({int res;
 res = Fset_cdr(Fmakesym("TYPE-FUNCTION"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(NAME),Fcons(fast_inverse(Faux(Fmakesym("<OBJECT>"))),Flist1(fast_inverse(INIT_TYPE_INPUT))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION")))))));res;});
res = ({int res;int TYPE_ENV = fast_convert(INFERENCE_ALL(BODY,INIT_ENV,NAME,NIL));({int res;
if(fast_not(fast_eq(fast_convert(TYPE_ENV),fast_convert(Fmakesym("NO")))) != NIL){
res = SET_TYPE_FUNCTION_INPUT(NAME,FIND_ARGUMENT_CLASS(ARG,TYPE_ENV));}
 else res = NIL;res;})
;
res = ({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("LOCAL-TYPE-FUNCTION")))))))) != NIL){
res = ADD_TYPE_FUNCTION_LOCAL(NAME);}
 else res = NIL;res;})
;
res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_LABELS(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("LOCAL-TYPE-FUNCTION"),fast_inverse(NIL));res;});
res = ({int res;int LABELS_FUNC = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int LABELS_BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));int LOCAL_TYPE_ENV = fast_convert(NIL);({int res;
while(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LABELS_FUNC))))) !=NIL){
res = ({int res;int FUNC = fast_convert(fast_convert(fast_car(LABELS_FUNC)));int NAME = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FUNC),Flist1(fast_inverse(fast_immediate(0)))))));int ARG = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FUNC),Flist1(fast_inverse(fast_immediate(1)))))));int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(FUNC)))));int INIT_TYPE_INPUT = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-LIST")),Fcons(fast_inverse(Flength(ARG)),Flist1(fast_inverse(Faux(Fmakesym("<OBJECT>"))))))));int INIT_ENV = fast_convert(CREATE_INIT_ENV(ARG));({int res;
 res = Fset_cdr(Fmakesym("LOCAL-TYPE-FUNCTION"),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(NAME),Fcons(fast_inverse(Faux(Fmakesym("<OBJECT>"))),Flist1(fast_inverse(INIT_TYPE_INPUT))))))),fast_inverse(fast_convert(Fcdr(Fmakesym("LOCAL-TYPE-FUNCTION")))))));res;});
({int res;
 res = LOCAL_TYPE_ENV = INFERENCE_ALL(({int arg1,arg2,res;
arg1 = fast_inverse(LABELS_BODY);
Fshelterpush(arg1);
arg2 = fast_inverse(BODY);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),({int arg1,arg2,res;
arg1 = fast_inverse(INIT_ENV);
Fshelterpush(arg1);
arg2 = fast_inverse(TYPE_ENV);
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;}),NAME,T);res;})
;
({int res;
if(fast_not(fast_eq(fast_convert(LOCAL_TYPE_ENV),fast_convert(Fmakesym("NO")))) != NIL){
res = SET_LOCAL_TYPE_FUNCTION_INPUT(NAME,FIND_ARGUMENT_CLASS(ARG,LOCAL_TYPE_ENV));}
 else res = NIL;res;})
;
res = ({int res;
 res = LABELS_FUNC = fast_convert(fast_cdr(LABELS_FUNC));res;})
;
res;})
;};res;})
;
res = LOCAL_TYPE_ENV;
res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_ARGUMENT_CLASS(int LS,int TYPE_ENV){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int ARGsubst = fast_convert(LS);int RESULTsubst = fast_convert(NIL);int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(ARGsubst)))) == NIL){
({int res;
 res = RESULTsubst = Fcons(fast_inverse(FIND_CLASS(fast_convert(fast_car(ARGsubst)),TYPE_ENV)),fast_inverse(RESULTsubst));res;})
;
temp1 = fast_convert(fast_cdr(ARGsubst));
ARGsubst = temp1;
}
res = fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(RESULTsubst))));res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CREATE_INIT_ENV(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int ARGsubst = fast_convert(LS);int RESULTsubst = fast_convert(NIL);int temp1,temp2;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(ARGsubst)))) == NIL){
({int res;
 res = RESULTsubst = Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(fast_car(ARGsubst))),fast_inverse(Faux(Fmakesym("<OBJECT>"))))),fast_inverse(RESULTsubst));res;})
;
temp1 = fast_convert(fast_cdr(ARGsubst));
ARGsubst = temp1;
}
res = fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(RESULTsubst))));res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int INFERENCE(int X,int TYPE_ENV){
int res;
int temp1,temp2;
INFERENCEloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(X),fast_convert(T))) != NIL){
res = TYPE_ENV;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(X),fast_convert(NIL))) != NIL){
res = TYPE_ENV;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res;int Y = fast_convert(REFER(X,TYPE_ENV));res = ({int res;
if(Y != NIL){
res = TYPE_ENV;}
else{
res = UNIFY(X,Faux(Fmakesym("<OBJECT>")),TYPE_ENV);}res;})
;
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = TYPE_ENV;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("THE")))) != NIL){
res = UNIFY(CLASSstar(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("NOT")))) != NIL){
res = TYPE_ENV;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("SETQ")))) != NIL){
res = ({int res=NIL;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))))) != NIL){
res = WARNING(Fmakestr("setq type mismatch"),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));
res = TYPE_ENV;}
else{
res = Fcons(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),fast_inverse(FIND_CLASS(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),TYPE_ENV)))),fast_inverse(TYPE_ENV));}
;res;});}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CONVERT")))) != NIL){
res = TYPE_ENV;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CATCH")))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCEloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("THROW")))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCEloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("QUOTE")))) != NIL){
res = TYPE_ENV;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("COND")))) != NIL){
res = INFERENCE_COND(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CASE")))) != NIL){
res = INFERENCE_CASE(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("IF")))) != NIL){
res = INFERENCE_IF(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET")))) != NIL){
res = INFERENCE_LET(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET*")))) != NIL){
res = INFERENCE_LET(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FOR")))) != NIL){
res = INFERENCE_FOR(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("WHILE")))) != NIL){
res = INFERENCE_WHILE(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LABELS")))) != NIL){
res = INFERENCE_LABELS(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FLET")))) != NIL){
res = INFERENCE_LABELS(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FUNCTION")))) != NIL){
res = INFERENCE_FUNCTION(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MACROP")),Flist1(fast_inverse(X))))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("MACROEXPAND-1")),Flist1(fast_inverse(X))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCEloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fcons(Fmakesym("+"),Fcons(Fmakesym("-"),Fcons(Fmakesym("*"),Fcons(Fmakesym("="),Fcons(Fmakesym(">"),Fcons(Fmakesym("<"),Fcons(Fmakesym(">="),Fcons(Fmakesym("<="),Fcons(Fmakesym("/="),NIL))))))))))))))) != NIL){
res = INFERENCE_NUMERIC(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SUBRP")),Flist1(fast_inverse(fast_convert(fast_car(X))))))) != NIL){
res = ({int res;int TYPE_SUBR = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT-INFERENCE"));
Fsetprop(Fmakesym("EXIT-INFERENCE"),i+1);
ret=setjmp(c_EXIT_INFERENCE[i]);if(ret == 0){
res = ({int res;
int TYPEsubst = fast_convert(TYPE_SUBR);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TYPEsubst)))) == NIL){
({int res;int NEW_ENV = fast_convert(INFERENCE_ARG(fast_convert(fast_cdr(X)),fast_convert(fast_cdr(fast_convert(fast_car(TYPEsubst)))),TYPE_ENV));res = ({int res;
if(fast_not(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO")))) != NIL){
({int res,i;
res = NEW_ENV;block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-INFERENCE"));
Fsetprop(Fmakesym("EXIT-INFERENCE"),i-1);
longjmp(c_EXIT_INFERENCE[i-1],1);res;})
;}
 else res = NIL;res;})
;
res;})
;
temp1 = fast_convert(fast_cdr(TYPEsubst));
TYPEsubst = temp1;
}
WARNING(Fmakestr("subr type mismatch"),X);
res = Fmakesym("NO");res;});Fsetprop(Fmakesym("EXIT-INFERENCE"),i);
}
 else{
ret = 0;
compiler1();res=block_arg;}
res;});
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) != NIL){
res = ({int res;int TYPE = fast_convert(FIND_FUNCTION_TYPE(fast_convert(fast_car(X))));res = ({int res;
if(TYPE != NIL){
res = INFERENCE_ARG(fast_convert(fast_cdr(X)),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(TYPE),Flist1(fast_inverse(fast_immediate(1)))))),TYPE_ENV);}
 else res = NIL;res;})
;
res;})
;}
else{
res = WARNING(Fmakestr("can't inference "),X);
res = Fmakesym("NO");}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_ALL(int X,int TYPE_ENV,int FN,int LOCAL){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(CELLRANGE(FN)) Fshelterpush(FN);
if(CELLRANGE(LOCAL)) Fshelterpush(LOCAL);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int RESULT = fast_convert(INFERENCE_ALL1(X,TYPE_ENV,FN));({int res=NIL;
if((fast_not(fast_eq(fast_convert(RESULT),fast_convert(Fmakesym("NO")))) && fast_not(LOCAL)) != NIL){
res = SET_TYPE_FUNCTION_OUTPUT(FN,FIND_CLASS(LAST(X),RESULT));}
else if((fast_not(fast_eq(fast_convert(RESULT),fast_convert(Fmakesym("NO")))) && LOCAL) != NIL){
res = SET_LOCAL_TYPE_FUNCTION_OUTPUT(FN,FIND_CLASS(LAST(X),RESULT));}
;res;});
res = RESULT;
res;})
;
if(CELLRANGE(LOCAL)) Fshelterpop();
if(CELLRANGE(FN)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_ALL1(int X,int TYPE_ENV,int FN){
int res;
int temp1,temp2,temp3;
INFERENCE_ALL1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(CELLRANGE(FN)) Fshelterpush(FN);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = TYPE_ENV;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(fast_car(X))))),Flist1(fast_inverse(Fcons(Fmakesym("+"),Fcons(Fmakesym("-"),Fcons(Fmakesym("*"),Fcons(Fmakesym("="),Fcons(Fmakesym(">"),Fcons(Fmakesym("<"),Fcons(Fmakesym(">="),Fcons(Fmakesym("<="),Fcons(Fmakesym("/="),NIL))))))))))))))) != NIL){
res = ({int res;int NEW_ENV = fast_convert(INFERENCE(fast_convert(fast_car(X)),TYPE_ENV));res = ({int res=NIL;
if(NEW_ENV != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = NEW_ENV;
temp3 = FN;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(FN)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
FN = temp3;
goto INFERENCE_ALL1loop;};}
else{
res = WARNING(Fmakestr("numeric type mismatch"),X);
res = Fmakesym("NO");}
;res;});
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(fast_convert(fast_car(X)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SUBRP")),Flist1(fast_inverse(fast_convert(fast_car(fast_convert(fast_car(X))))))))) != NIL){
res = ({int res;int TYPE_SUBR = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(fast_convert(fast_car(fast_convert(fast_car(X))))),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT-ALL"));
Fsetprop(Fmakesym("EXIT-ALL"),i+1);
ret=setjmp(c_EXIT_ALL[i]);if(ret == 0){
res = ({int res;
int TYPEsubst = fast_convert(TYPE_SUBR);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TYPEsubst)))) == NIL){
({int res;int NEW_ENV = fast_convert(INFERENCE_ARG(fast_convert(fast_cdr(fast_convert(fast_car(X)))),fast_convert(fast_cdr(fast_convert(fast_car(TYPEsubst)))),TYPE_ENV));res = ({int res;
if(fast_not(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO")))) != NIL){
res = ({int res;int RESULT = fast_convert(INFERENCE_ALL1(fast_convert(fast_cdr(X)),NEW_ENV,FN));res = ({int res;
if(fast_not(fast_eq(fast_convert(RESULT),fast_convert(Fmakesym("NO")))) != NIL){
({int res,i;
res = RESULT;block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-ALL"));
Fsetprop(Fmakesym("EXIT-ALL"),i-1);
longjmp(c_EXIT_ALL[i-1],1);res;})
;}
 else res = NIL;res;})
;
res;})
;}
 else res = NIL;res;})
;
res;})
;
temp1 = fast_convert(fast_cdr(TYPEsubst));
TYPEsubst = temp1;
}
WARNING(Fmakestr("subr type mismatch"),fast_convert(fast_car(X)));
res = Fmakesym("NO");res;});Fsetprop(Fmakesym("EXIT-ALL"),i);
}
 else{
ret = 0;
compiler1();res=block_arg;}
res;});
res;})
;}
else{
res = ({int res;int NEW_ENV = fast_convert(INFERENCE(fast_convert(fast_car(X)),TYPE_ENV));res = ({int res=NIL;
if(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO"))) != NIL){
res = WARNING(Fmakestr("type mismatch"),fast_convert(fast_car(X)));
res = Fmakesym("NO");}
else{
{
temp1 = fast_convert(fast_cdr(X));
temp2 = NEW_ENV;
temp3 = FN;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(FN)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
FN = temp3;
goto INFERENCE_ALL1loop;};}
;res;});
res;})
;}
;res;});
if(CELLRANGE(FN)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_COND(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = INFERENCE_COND1(fast_convert(fast_cdr(X)),TYPE_ENV);
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_COND1(int X,int TYPE_ENV){
int res;
int temp1,temp2;
INFERENCE_COND1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = TYPE_ENV;}
else{
res = ({int res;int NEW_ENV = fast_convert(INFERENCE_COND2(fast_convert(fast_car(X)),TYPE_ENV));res = ({int res=NIL;
if(fast_not(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO")))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCE_COND1loop;};}
else{
res = WARNING(Fmakestr("cond mismatch"),fast_convert(fast_car(X)));
{
temp1 = fast_convert(fast_cdr(X));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCE_COND1loop;};}
;res;});
res;})
;}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_COND2(int X,int TYPE_ENV){
int res;
int temp1,temp2;
INFERENCE_COND2loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = TYPE_ENV;}
else{
res = ({int res;int NEW_ENV = fast_convert(INFERENCE(fast_convert(fast_car(X)),TYPE_ENV));res = ({int res=NIL;
if(fast_not(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO")))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = NEW_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCE_COND2loop;};}
else{
res = WARNING(Fmakestr("cond mismatch"),X);
{
temp1 = fast_convert(fast_cdr(X));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCE_COND2loop;};}
;res;});
res;})
;}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_CASE(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = INFERENCE_CASE1(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))),TYPE_ENV);
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_CASE1(int X,int TYPE_ENV){
int res;
int temp1,temp2;
INFERENCE_CASE1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = TYPE_ENV;}
else{
res = ({int res;int NEW_ENV = fast_convert(INFERENCE_CASE2(fast_convert(fast_cdr(fast_convert(fast_car(X)))),TYPE_ENV));res = ({int res;
if(fast_not(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO")))) != NIL){
{
temp1 = fast_convert(fast_cdr(X));
temp2 = NEW_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCE_CASE1loop;};}
else{
res = WARNING(Fmakestr("case mismatch"),X);}res;})
;
res;})
;}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_CASE2(int X,int TYPE_ENV){
int res;
int temp1,temp2;
INFERENCE_CASE2loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = TYPE_ENV;}
else{
{
temp1 = fast_convert(fast_cdr(X));
temp2 = INFERENCE(fast_convert(fast_car(X)),TYPE_ENV);
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCE_CASE2loop;};}res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_IF(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(Flength(X)),fast_convert(fast_immediate(4))) != NIL){
res = INFERENCE_IF1(X,TYPE_ENV);}
else{
res = INFERENCE_IF2(X,TYPE_ENV);}res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_IF1(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TEST = fast_convert(INFERENCE(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),TYPE_ENV));res = ({int res;
if(fast_not(fast_eq(fast_convert(TEST),fast_convert(Fmakesym("NO")))) != NIL){
res = ({int res;int ELSE = fast_convert(INFERENCE(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(3)))))),TEST));res = ({int res;
if(fast_not(fast_eq(fast_convert(ELSE),fast_convert(Fmakesym("NO")))) != NIL){
res = ({int res;int TRUE = fast_convert(INFERENCE(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),ELSE));res = ({int res;
if(fast_not(fast_eq(fast_convert(TRUE),fast_convert(Fmakesym("NO")))) != NIL){
res = TRUE;}
else{
res = ({int res;
WARNING(Fmakestr("if mismatch"),X);
res = Fmakesym("NO");res;});}res;})
;
res;})
;}
else{
res = Fmakesym("NO");}res;})
;
res;})
;}
else{
res = Fmakesym("NO");}res;})
;
res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_IF2(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int TEST = fast_convert(INFERENCE(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))),TYPE_ENV));res = ({int res;
if(fast_not(fast_eq(fast_convert(TEST),fast_convert(Fmakesym("NO")))) != NIL){
res = ({int res;int TRUE = fast_convert(INFERENCE(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),TEST));res = ({int res;
if(fast_not(fast_eq(fast_convert(TRUE),fast_convert(Fmakesym("NO")))) != NIL){
res = TRUE;}
else{
res = ({int res;
WARNING(Fmakestr("if mismatch"),X);
res = Fmakesym("NO");res;});}res;})
;
res;})
;}
else{
res = Fmakesym("NO");}res;})
;
res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_NUMERIC(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(EVERY(({Fset_cdr(Fmakesym("compiler6"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler6"));}),fast_convert(fast_cdr(X))) != NIL){
res = ESTIMATE(fast_convert(fast_cdr(X)),Faux(Fmakesym("<NUMBER>")),TYPE_ENV);}
else if(EVERY(({Fset_cdr(Fmakesym("compiler7"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler7"));}),fast_convert(fast_cdr(X))) != NIL){
res = TYPE_ENV;}
else if(ANY(({Fset_cdr(Fmakesym("compiler8"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler8"));}),fast_convert(fast_cdr(X))) != NIL){
res = ESTIMATE(fast_convert(fast_cdr(X)),Faux(Fmakesym("<FLOAT>")),TYPE_ENV);}
else if(ANY(({Fset_cdr(Fmakesym("compiler9"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler9"));}),fast_convert(fast_cdr(X))) != NIL){
res = ESTIMATE(fast_convert(fast_cdr(X)),Faux(Fmakesym("<INTEGER>")),TYPE_ENV);}
else if(ANY(({Fset_cdr(Fmakesym("compiler10"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler10"));}),fast_convert(fast_cdr(X))) != NIL){
res = ESTIMATE(fast_convert(fast_cdr(X)),Faux(Fmakesym("<INTEGER>")),TYPE_ENV);}
else{
res = WARNING(Fmakestr("numerical argument type mismatch"),X);
res = Fmakesym("NO");}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_LET(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int VARS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(VARS)))) != NIL){
res = INFERENCE_ALL1(BODY,TYPE_ENV,NIL);}
else{
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT-LET"));
Fsetprop(Fmakesym("EXIT-LET"),i+1);
ret=setjmp(c_EXIT_LET[i]);if(ret == 0){
({int res;
int VARS1subst = fast_convert(VARS);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(VARS1subst)))) == NIL){
({int res;
 res = TYPE_ENV = UNIFY(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(VARS1subst))),Flist1(fast_inverse(fast_immediate(0)))))),fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(fast_car(VARS1subst))),Flist1(fast_inverse(fast_immediate(1)))))),TYPE_ENV);res;})
;
({int res;
if(fast_eq(fast_convert(TYPE_ENV),fast_convert(Fmakesym("NO"))) != NIL){
({int res,i;
res = Fmakesym("NO");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-LET"));
Fsetprop(Fmakesym("EXIT-LET"),i-1);
longjmp(c_EXIT_LET[i-1],1);res;})
;}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(VARS1subst));
VARS1subst = temp1;
}
res=NIL;res;});
res = INFERENCE_ALL1(BODY,TYPE_ENV,NIL);Fsetprop(Fmakesym("EXIT-LET"),i);
}
 else{
ret = 0;
compiler1();res=block_arg;}
res;});}res;})
;
res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_FOR(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int VARS = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1)))))));int END = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));int BODY = fast_convert(fast_convert(fast_cdr(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))))));res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT-FOR"));
Fsetprop(Fmakesym("EXIT-FOR"),i+1);
ret=setjmp(c_EXIT_FOR[i]);if(ret == 0){
({int res;
int VARS1subst = fast_convert(VARS);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(VARS1subst)))) == NIL){
({int res;
 res = TYPE_ENV = INFERENCE(fast_convert(fast_car(VARS1subst)),TYPE_ENV);res;})
;
({int res;
if(fast_eq(fast_convert(TYPE_ENV),fast_convert(Fmakesym("NO"))) != NIL){
({int res,i;
res = Fmakesym("NO");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-FOR"));
Fsetprop(Fmakesym("EXIT-FOR"),i-1);
longjmp(c_EXIT_FOR[i-1],1);res;})
;}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(VARS1subst));
VARS1subst = temp1;
}
res=NIL;res;});
({int res;
int END1subst = fast_convert(END);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(END1subst)))) == NIL){
({int res;
 res = TYPE_ENV = INFERENCE(fast_convert(fast_car(END1subst)),TYPE_ENV);res;})
;
({int res;
if(fast_eq(fast_convert(TYPE_ENV),fast_convert(Fmakesym("NO"))) != NIL){
({int res,i;
res = Fmakesym("NO");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-FOR"));
Fsetprop(Fmakesym("EXIT-FOR"),i-1);
longjmp(c_EXIT_FOR[i-1],1);res;})
;}
 else res = NIL;res;})
;
temp1 = fast_convert(fast_cdr(END1subst));
END1subst = temp1;
}
res=NIL;res;});
res = INFERENCE_ALL1(BODY,TYPE_ENV,NIL);Fsetprop(Fmakesym("EXIT-FOR"),i);
}
 else{
ret = 0;
compiler1();res=block_arg;}
res;});
res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_WHILE(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = INFERENCE_WHILE1(fast_convert(fast_cdr(X)),TYPE_ENV);
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_WHILE1(int X,int TYPE_ENV){
int res;
int temp1,temp2;
INFERENCE_WHILE1loop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = TYPE_ENV;}
else{
{
temp1 = fast_convert(fast_cdr(X));
temp2 = INFERENCE(fast_convert(fast_car(X)),TYPE_ENV);
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto INFERENCE_WHILE1loop;};}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_FUNCTION(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int NEW_ENV = fast_convert(UNIFY(fast_convert(fast_car(fast_convert(fast_cdr(X)))),Faux(Fmakesym("<SYMBOL>")),TYPE_ENV));res = ({int res=NIL;
if(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO"))) != NIL){
res = WARNING(Fmakestr("function mismatch"),X);
res = TYPE_ENV;}
else{
res = NEW_ENV;}
;res;});
res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_FUNCTION_TYPE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Y = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION")))))))));res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(Y)))) != NIL){
res = ({int res;int Z = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("LOCAL-TYPE-FUNCTION")))))))));res = ({int res;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(Z)))) != NIL){
res = NIL;}
else{
res = fast_convert(fast_cdr(Z));}res;})
;
res;})
;}
else{
res = fast_convert(fast_cdr(Y));}res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INFERENCE_ARG(int X,int Y,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res,ret,i;
 i = Fgetprop(Fmakesym("EXIT-ARG"));
Fsetprop(Fmakesym("EXIT-ARG"),i+1);
ret=setjmp(c_EXIT_ARG[i]);if(ret == 0){
res = ({int res;
int ARGsubst = fast_convert(X);int TYPEsubst = fast_convert(Y);int temp1,temp2;
while(({int res;
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(ARGsubst))))) == NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TYPEsubst))))) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
 == NIL){
({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(fast_convert(fast_car(ARGsubst)))))) != NIL){
res = ({int res;int NEW_ENV = fast_convert(UNIFY(fast_convert(fast_car(ARGsubst)),fast_convert(fast_car(TYPEsubst)),TYPE_ENV));res = ({int res;
if(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO"))) != NIL){
({int res,i;
res = Fmakesym("NO");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-ARG"));
Fsetprop(Fmakesym("EXIT-ARG"),i-1);
longjmp(c_EXIT_ARG[i-1],1);res;})
;}
else{
res = ({int res;
 res = TYPE_ENV = NEW_ENV;res;})
;}res;})
;
res;})
;}
else{
res = ({int res;int NEW_ENV = fast_convert(INFERENCE(fast_convert(fast_car(ARGsubst)),TYPE_ENV));({int res=NIL;
if(fast_eq(fast_convert(NEW_ENV),fast_convert(Fmakesym("NO"))) != NIL){
({int res,i;
res = Fmakesym("NO");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-ARG"));
Fsetprop(Fmakesym("EXIT-ARG"),i-1);
longjmp(c_EXIT_ARG[i-1],1);res;})
;}
else{
res = ({int res;int OUTPUT_CLASS = fast_convert(FIND_CLASS(fast_convert(fast_car(ARGsubst)),TYPE_ENV));res = ({int res;
if(fast_not((fast_eq(fast_convert(OUTPUT_CLASS),fast_convert(fast_convert(fast_car(TYPEsubst)))) || fast_convert(Fcallsubr(Fcar(Fmakesym("SUBCLASSP")),Fcons(fast_inverse(OUTPUT_CLASS),Flist1(fast_inverse(fast_convert(fast_car(TYPEsubst))))))) || fast_convert(Fcallsubr(Fcar(Fmakesym("SUBCLASSP")),Fcons(fast_inverse(fast_convert(fast_car(TYPEsubst))),Flist1(fast_inverse(OUTPUT_CLASS))))))) != NIL){
({int res,i;
res = Fmakesym("NO");block_arg=res;
 i = Fgetprop(Fmakesym("EXIT-ARG"));
Fsetprop(Fmakesym("EXIT-ARG"),i-1);
longjmp(c_EXIT_ARG[i-1],1);res;})
;}
 else res = NIL;res;})
;
res;})
;}
;res;});
res = ({int res;
 res = TYPE_ENV = NEW_ENV;res;})
;
res;})
;}
;res;});
temp1 = fast_convert(fast_cdr(ARGsubst));
temp2 = ({int res;
if((fast_eqgreaterp(fast_convert(Flength(TYPEsubst)),fast_convert(fast_immediate(2))) && fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(TYPEsubst),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(Fmakesym("REPEAT")))) != NIL){
res = TYPEsubst;}
else{
res = fast_convert(fast_cdr(TYPEsubst));}res;})
;
ARGsubst = temp1;
TYPEsubst = temp2;
}
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(ARGsubst)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(TYPEsubst))))) != NIL){
res = TYPE_ENV;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(ARGsubst)))) && (fast_eqgreaterp(fast_convert(Flength(TYPEsubst)),fast_convert(fast_immediate(2))) && fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(TYPEsubst),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(Fmakesym("REPEAT"))))) != NIL){
res = TYPE_ENV;}
else{
res = Fmakesym("NO");}
;res;});res;});Fsetprop(Fmakesym("EXIT-ARG"),i);
}
 else{
ret = 0;
compiler1();res=block_arg;}
res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FUNCTION_TYPE_OBJECT_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Y = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION")))))))));res = ({int res;
if(fast_not(Y) != NIL){
res = NIL;}
else{
res = fast_eq(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(Y),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(Faux(Fmakesym("<OBJECT>"))));}res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_CLASS(int X,int TYPE_ENV){
int res;
int temp1,temp2;
FIND_CLASSloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = Faux(Fmakesym("<NULL>"));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(X),fast_convert(Fmakesym("T")))) != NIL){
res = Faux(Fmakesym("<SYMBOL>"));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X)))) != NIL){
res = REFER(X,TYPE_ENV);}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CLASS-OF")),Flist1(fast_inverse(X))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fcons(Fmakesym("+"),Fcons(Fmakesym("-"),Fcons(Fmakesym("*"),Fcons(Fmakesym("="),Fcons(Fmakesym(">"),Fcons(Fmakesym("<"),Fcons(Fmakesym(">="),Fcons(Fmakesym("<="),Fcons(Fmakesym("/="),NIL))))))))))))))) != NIL){
res = FIND_CLASS_NUMERIC(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SUBRP")),Flist1(fast_inverse(fast_convert(fast_car(X))))))) != NIL){
res = ({int res;int TYPE_SUBR = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(fast_convert(fast_car(X))),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(fast_car(fast_convert(fast_car(TYPE_SUBR))));
res;})
;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && TYPE_FUNCTION_P(fast_convert(fast_car(X)))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(FIND_FUNCTION_TYPE(fast_convert(fast_car(X)))),Flist1(fast_inverse(fast_immediate(0))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LABELS")))) != NIL){
{
temp1 = LAST(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("FLET")))) != NIL){
{
temp1 = LAST(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("COND")))) != NIL){
res = FIND_CLASS_COND(fast_convert(fast_cdr(X)),TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("IF")))) != NIL){
res = FIND_CLASS_IF(X,TYPE_ENV);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("QUOTE")))) != NIL){
res = fast_convert(Fcallsubr(Fcar(Fmakesym("CLASS-OF")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("THE")))) != NIL){
res = NIL;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("SETQ")))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CONVERT")))) != NIL){
res = CLASS_DYNAMIC(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("CATCH")))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("THROW")))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2))))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET")))) != NIL){
{
temp1 = LAST(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LET*")))) != NIL){
{
temp1 = LAST(fast_convert(fast_cdr(fast_convert(fast_cdr(X)))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("WHILE")))) != NIL){
res = Faux(Fmakesym("<NULL>"));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_eq(fast_convert(fast_convert(fast_car(X))),fast_convert(Fmakesym("LAMBDA")))) != NIL){
res = Faux(Fmakesym("<FUNCTION>"));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("MACROP")),Flist1(fast_inverse(X))))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("MACROEXPAND-1")),Flist1(fast_inverse(X))));
temp2 = TYPE_ENV;
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
X = temp1;
TYPE_ENV = temp2;
goto FIND_CLASSloop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(X)))) != NIL){
res = Faux(Fmakesym("<OBJECT>"));}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_CLASS_IF(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = FIND_CLASS(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(2)))))),TYPE_ENV);
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_CLASS_COND(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))) != NIL){
res = Faux(Fmakesym("<OBJECT>"));}
else{
res = FIND_CLASS(LAST(fast_convert(fast_car(X))),TYPE_ENV);}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int FIND_CLASS_NUMERIC(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(EVERY(({Fset_cdr(Fmakesym("compiler11"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler11"));}),fast_convert(fast_cdr(X))) != NIL){
res = Faux(Fmakesym("<NUMBER>"));}
else if(EVERY(({Fset_cdr(Fmakesym("compiler12"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler12"));}),fast_convert(fast_cdr(X))) != NIL){
res = Faux(Fmakesym("<FIXNUM>"));}
else if(ANY(({Fset_cdr(Fmakesym("compiler13"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler13"));}),fast_convert(fast_cdr(X))) != NIL){
res = Faux(Fmakesym("<FLOAT>"));}
else if(ANY(({Fset_cdr(Fmakesym("compiler14"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler14"));}),fast_convert(fast_cdr(X))) != NIL){
res = Faux(Fmakesym("<INTEGER>"));}
else if(ANY(({Fset_cdr(Fmakesym("compiler15"),Fcons(TYPE_ENV,Fcons(T,NIL)));Fcar(Fmakesym("compiler15"));}),fast_convert(fast_cdr(X))) != NIL){
res = Faux(Fmakesym("<INTEGER>"));}
else{
res = Faux(Fmakesym("<NUMBER>"));}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int REFER(int X,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Y = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(TYPE_ENV))))));res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(Y)))) != NIL){
res = Faux(Fmakesym("<OBJECT>"));}
else{
res = fast_convert(fast_cdr(Y));}
;res;});
res;})
;
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SET_TYPE_FUNCTION_OUTPUT(int FN,int Y){
int res;
if(CELLRANGE(FN)) Fshelterpush(FN);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Z = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(FN),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION")))))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(Y),Fcons(fast_inverse(Z),Flist1(fast_inverse(fast_immediate(1)))))));
res;})
;
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(FN)) Fshelterpop();
return(res);}
int SET_TYPE_FUNCTION_INPUT(int FN,int Y){
int res;
if(CELLRANGE(FN)) Fshelterpush(FN);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Z = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(FN),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION")))))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(Y),Fcons(fast_inverse(Z),Flist1(fast_inverse(fast_immediate(2)))))));
res;})
;
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(FN)) Fshelterpop();
return(res);}
int ADD_TYPE_FUNCTION_LOCAL(int FN){
int res;
if(CELLRANGE(FN)) Fshelterpush(FN);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Z = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(FN),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION")))))))));res = APPENDexclamation(Z,fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("LOCAL-TYPE-FUNCTION"))))))));
res;})
;
if(CELLRANGE(FN)) Fshelterpop();
return(res);}
int SET_LOCAL_TYPE_FUNCTION_OUTPUT(int FN,int Y){
int res;
if(CELLRANGE(FN)) Fshelterpush(FN);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Z = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(FN),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("LOCAL-TYPE-FUNCTION")))))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(Y),Fcons(fast_inverse(Z),Flist1(fast_inverse(fast_immediate(1)))))));
res;})
;
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(FN)) Fshelterpop();
return(res);}
int SET_LOCAL_TYPE_FUNCTION_INPUT(int FN,int Y){
int res;
if(CELLRANGE(FN)) Fshelterpush(FN);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Z = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(FN),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("LOCAL-TYPE-FUNCTION")))))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-ELT")),Fcons(fast_inverse(Y),Fcons(fast_inverse(Z),Flist1(fast_inverse(fast_immediate(2)))))));
res;})
;
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(FN)) Fshelterpop();
return(res);}
int TYPE_FUNCTION_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ASSOC")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("TYPE-FUNCTION"))))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int UNIFY(int X,int Y,int TYPE_ENV){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_not(VARIABLEP(X)) && fast_not(VARIABLEP(Y))) != NIL){
res = ({int res;int X1 = fast_convert(({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CLASSP")),Flist1(fast_inverse(X))))) != NIL){
res = FIND_CLASS(X,TYPE_ENV);}
else{
res = X;}res;})
);int Y1 = fast_convert(({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CLASSP")),Flist1(fast_inverse(Y))))) != NIL){
res = FIND_CLASS(Y,TYPE_ENV);}
else{
res = Y;}res;})
);res = ({int res;
if((fast_eq(fast_convert(X1),fast_convert(Y1)) || SUBCLASSPstar(X1,Y1) || SUBCLASSPstar(Y1,X1)) != NIL){
res = TYPE_ENV;}
else{
res = Fmakesym("NO");}res;})
;
res;})
;}
else if((VARIABLEP(X) && fast_not(VARIABLEP(Y))) != NIL){
res = ({int res;int X1 = fast_convert(REFER(X,TYPE_ENV));int Y1 = fast_convert(({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CLASSP")),Flist1(fast_inverse(Y))))) != NIL){
res = FIND_CLASS(Y,TYPE_ENV);}
else{
res = Y;}res;})
);res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X1)))) != NIL){
res = ({int res;
 res = TYPE_ENV = Fcons(fast_inverse(Fcons(fast_inverse(X),fast_inverse(Y1))),fast_inverse(TYPE_ENV));res;})
;
res = TYPE_ENV;}
else if(fast_eq(fast_convert(X1),fast_convert(Y1)) != NIL){
res = TYPE_ENV;}
else if(SUBCLASSPstar(X1,Y1) != NIL){
res = TYPE_ENV;}
else if(SUBCLASSPstar(Y1,X1) != NIL){
res = Fcons(fast_inverse(Fcons(fast_inverse(X),fast_inverse(Y1))),fast_inverse(TYPE_ENV));}
else{
res = Fmakesym("NO");}
;res;});
res;})
;}
else if((fast_not(VARIABLEP(X)) && VARIABLEP(Y)) != NIL){
res = ({int res;int X1 = fast_convert(({int res;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("CLASSP")),Flist1(fast_inverse(X))))) != NIL){
res = FIND_CLASS(X,TYPE_ENV);}
else{
res = X;}res;})
);int Y1 = fast_convert(REFER(Y,TYPE_ENV));res = ({int res=NIL;
if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(Y1)))) != NIL){
res = ({int res;
 res = TYPE_ENV = Fcons(fast_inverse(Fcons(fast_inverse(Y),fast_inverse(X1))),fast_inverse(TYPE_ENV));res;})
;
res = TYPE_ENV;}
else if(fast_eq(fast_convert(X1),fast_convert(Y1)) != NIL){
res = TYPE_ENV;}
else if(SUBCLASSPstar(X1,Y1) != NIL){
res = Fcons(fast_inverse(Fcons(fast_inverse(Y),fast_inverse(X1))),fast_inverse(TYPE_ENV));}
else if(SUBCLASSPstar(Y1,X1) != NIL){
res = TYPE_ENV;}
else{
res = Fmakesym("NO");}
;res;});
res;})
;}
else{
res = ({int res;
 res = TYPE_ENV = Fcons(fast_inverse(Fcons(fast_inverse(X),fast_inverse(Y))),fast_inverse(TYPE_ENV));res;})
;
res = TYPE_ENV;}
;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int VARIABLEP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X))))) != NIL)
if((res=fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(X)))))) != NIL)
if((res=fast_not(fast_eq(fast_convert(X),fast_convert(T)))) !=NIL)
res=res;
else res=NIL;
else res=NIL;else res=NIL;res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SUBCLASSPstar(int X,int Y){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_eq(fast_convert(X),fast_convert(NIL)) || fast_eq(fast_convert(X),fast_convert(T)) || fast_eq(fast_convert(Y),fast_convert(NIL)) || fast_eq(fast_convert(Y),fast_convert(T))) != NIL){
res = NIL;}
else{
res = fast_convert(Fcallsubr(Fcar(Fmakesym("SUBCLASSP")),Fcons(fast_inverse(X),Flist1(fast_inverse(Y)))));}
;res;});
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int ESTIMATE(int LS,int CLASS,int TYPE_ENV){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(CLASS)) Fshelterpush(CLASS);
if(CELLRANGE(TYPE_ENV)) Fshelterpush(TYPE_ENV);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
int LS1subst = fast_convert(LS);int temp1;
while(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS1subst)))) == NIL){
({int res=NIL;
if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(fast_convert(fast_car(LS1subst))))))) != NIL){
res = T;}
else{
res = ({int res;
 res = TYPE_ENV = UNIFY(fast_convert(fast_car(LS1subst)),CLASS,TYPE_ENV);res;})
;}
;res;});
temp1 = fast_convert(fast_cdr(LS1subst));
LS1subst = temp1;
}
res = TYPE_ENV;res;});
if(CELLRANGE(TYPE_ENV)) Fshelterpop();
if(CELLRANGE(CLASS)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CLASSstar(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = Faux(X);
if(CELLRANGE(X)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("ANY" , f_ANY);
(deftfunc)("EVERY" , f_EVERY);
(deftfunc)("TAKE" , f_TAKE);
(deftfunc)("DROP" , f_DROP);
(deftfunc)("LAST" , f_LAST);
(deftfunc)("SECOND-LAST" , f_SECOND_LAST);
(deftfunc)("REMOVE" , f_REMOVE);
(deftfunc)("APPEND!" , f_APPENDexclamation);
(deftfunc)("POSITION" , f_POSITION);
(deftfunc)("FILENAME" , f_FILENAME);
(deftfunc)("FILENAME1" , f_FILENAME1);
(deftfunc)("FILENAME2" , f_FILENAME2);
(deftfunc)("DROPSTRING" , f_DROPSTRING);
(deftfunc)("SUBSTRING" , f_SUBSTRING);
(deftfunc)("SUBST" , f_SUBST);
(deftfunc)("ALPHA-CONV" , f_ALPHA_CONV);
(deftfunc)("NTH" , f_NTH);
(deftfunc)("ERROR*" , f_ERRORstar);
(deftfunc)("compiler0" , f_compiler0);
(deftfunc)("COMPILE-FILE" , f_COMPILE_FILE);
(deftfunc)("COMPILE-FILE1" , f_COMPILE_FILE1);
(deftfunc)("COMPILE-FILE*" , f_COMPILE_FILEstar);
(deftfunc)("compiler1" , f_compiler1);
(deftfunc)("COMPILE-CUDA" , f_COMPILE_CUDA);
(deftfunc)("COMPILE-CUDA1" , f_COMPILE_CUDA1);
(deftfunc)("PASS1" , f_PASS1);
(deftfunc)("CHECK-ARGS-COUNT" , f_CHECK_ARGS_COUNT);
(deftfunc)("FIND-CATCH-BLOCK-TAG" , f_FIND_CATCH_BLOCK_TAG);
(deftfunc)("PASS2" , f_PASS2);
(deftfunc)("COUNT-ARGS" , f_COUNT_ARGS);
(deftfunc)("COMPILE" , f_COMPILE);
(deftfunc)("COMP" , f_COMP);
(deftfunc)("INITIALIZE" , f_INITIALIZE);
(deftfunc)("DECLARE-CATCH-BLOCK-BUFFER" , f_DECLARE_CATCH_BLOCK_BUFFER);
(deftfunc)("FINALIZE" , f_FINALIZE);
(deftfunc)("COMP-DEFUN" , f_COMP_DEFUN);
(deftfunc)("COMP-LAMBDA" , f_COMP_LAMBDA);
(deftfunc)("LAMBDA-NAME" , f_LAMBDA_NAME);
(deftfunc)("COMP-DEFGENERIC" , f_COMP_DEFGENERIC);
(deftfunc)("COMP-DEFUN0" , f_COMP_DEFUN0);
(deftfunc)("COMP-LAMBDA0" , f_COMP_LAMBDA0);
(deftfunc)("COMP-DEFGENERIC0" , f_COMP_DEFGENERIC0);
(deftfunc)("COMP-DEFUN1" , f_COMP_DEFUN1);
(deftfunc)("COMP-LAMBDA1" , f_COMP_LAMBDA1);
(deftfunc)("COMP-DEFGENERIC1" , f_COMP_DEFGENERIC1);
(deftfunc)("COMP-DEFUN2" , f_COMP_DEFUN2);
(deftfunc)("COMP-LAMBDA2" , f_COMP_LAMBDA2);
(deftfunc)("LAMBDA-STREAM-CALLEE" , f_LAMBDA_STREAM_CALLEE);
(deftfunc)("LAMBDA-STREAM-CALLER" , f_LAMBDA_STREAM_CALLER);
(deftfunc)("FIND-FREE-VARIABLE" , f_FIND_FREE_VARIABLE);
(deftfunc)("FIND-FREE-VARIABLE1" , f_FIND_FREE_VARIABLE1);
(deftfunc)("FREE-VARIABLE-LIST" , f_FREE_VARIABLE_LIST);
(deftfunc)("COMP-DEFGENERIC2" , f_COMP_DEFGENERIC2);
(deftfunc)("VARLIS-TO-LAMBDA-ARGS" , f_VARLIS_TO_LAMBDA_ARGS);
(deftfunc)("COMP-DEFGENERIC-BODY" , f_COMP_DEFGENERIC_BODY);
(deftfunc)("METHOD-NEED-RETURN-P" , f_METHOD_NEED_RETURN_P);
(deftfunc)("METHOD-NEED-RETURN-P1" , f_METHOD_NEED_RETURN_P1);
(deftfunc)("COMP-DEFGENERIC-COND" , f_COMP_DEFGENERIC_COND);
(deftfunc)("COMP-DEFGENERIC-COND1" , f_COMP_DEFGENERIC_COND1);
(deftfunc)("COMP-DEFUN3" , f_COMP_DEFUN3);
(deftfunc)("COMP-LAMBDA3" , f_COMP_LAMBDA3);
(deftfunc)("COMP-DEFGENERIC3" , f_COMP_DEFGENERIC3);
(deftfunc)("GEN-ARG1" , f_GEN_ARG1);
(deftfunc)("GEN-ARG2" , f_GEN_ARG2);
(deftfunc)("GEN-ARG3" , f_GEN_ARG3);
(deftfunc)("GEN-ASSIGN" , f_GEN_ASSIGN);
(deftfunc)("GEN-CALL" , f_GEN_CALL);
(deftfunc)("GEN-SHELTERPUSH" , f_GEN_SHELTERPUSH);
(deftfunc)("GEN-SHELTERPOP" , f_GEN_SHELTERPOP);
(deftfunc)("GEN-CHECKGC" , f_GEN_CHECKGC);
(deftfunc)("COMP-IF" , f_COMP_IF);
(deftfunc)("COMP-NUMERIC" , f_COMP_NUMERIC);
(deftfunc)("COMP-FUNCALL" , f_COMP_FUNCALL);
(deftfunc)("COMP-FUNCALL-CLANG" , f_COMP_FUNCALL_CLANG);
(deftfunc)("COMP-FUNCALL-CLANG1" , f_COMP_FUNCALL_CLANG1);
(deftfunc)("COMP-FUNCALL1" , f_COMP_FUNCALL1);
(deftfunc)("COMP-FUNCALL2" , f_COMP_FUNCALL2);
(deftfunc)("COMP-SUBRCALL" , f_COMP_SUBRCALL);
(deftfunc)("COMP-SUBRCALL1" , f_COMP_SUBRCALL1);
(deftfunc)("COMP-SUBRCALL2" , f_COMP_SUBRCALL2);
(deftfunc)("COMP-SUBRCALL3" , f_COMP_SUBRCALL3);
(deftfunc)("COMP-LABELS" , f_COMP_LABELS);
(deftfunc)("COMP-LABELS1" , f_COMP_LABELS1);
(deftfunc)("COMP-LABELS2" , f_COMP_LABELS2);
(deftfunc)("COMP-LET" , f_COMP_LET);
(deftfunc)("COMP-LET*" , f_COMP_LETstar);
(deftfunc)("NOT-NEED-RES-P" , f_NOT_NEED_RES_P);
(deftfunc)("NOT-NEED-COLON-P" , f_NOT_NEED_COLON_P);
(deftfunc)("TAILCALLP" , f_TAILCALLP);
(deftfunc)("COMP-LET1" , f_COMP_LET1);
(deftfunc)("COMP-LET2" , f_COMP_LET2);
(deftfunc)("COMP-COND" , f_COMP_COND);
(deftfunc)("COMP-COND1" , f_COMP_COND1);
(deftfunc)("COMP-COND2" , f_COMP_COND2);
(deftfunc)("COMP-CASE" , f_COMP_CASE);
(deftfunc)("COMP-CASE1" , f_COMP_CASE1);
(deftfunc)("COMP-CASE-USING" , f_COMP_CASE_USING);
(deftfunc)("COMP-CASE-USING1" , f_COMP_CASE_USING1);
(deftfunc)("HAS-TAIL-RECUR-P" , f_HAS_TAIL_RECUR_P);
(deftfunc)("compiler2" , f_compiler2);
(deftfunc)("HAS-TAIL-RECUR-P1" , f_HAS_TAIL_RECUR_P1);
(deftfunc)("compiler3" , f_compiler3);
(deftfunc)("compiler4" , f_compiler4);
(deftfunc)("COMP-FOR" , f_COMP_FOR);
(deftfunc)("COMP-FOR1" , f_COMP_FOR1);
(deftfunc)("COMP-FOR2" , f_COMP_FOR2);
(deftfunc)("compiler5" , f_compiler5);
(deftfunc)("COMP-FOR3" , f_COMP_FOR3);
(deftfunc)("COMP-PROGN" , f_COMP_PROGN);
(deftfunc)("COMP-PROGN1" , f_COMP_PROGN1);
(deftfunc)("COMP-AND" , f_COMP_AND);
(deftfunc)("COMP-AND1" , f_COMP_AND1);
(deftfunc)("COMP-OR" , f_COMP_OR);
(deftfunc)("COMP-OR1" , f_COMP_OR1);
(deftfunc)("COMP-TEST-AND" , f_COMP_TEST_AND);
(deftfunc)("COMP-TEST-AND1" , f_COMP_TEST_AND1);
(deftfunc)("COMP-TEST-OR" , f_COMP_TEST_OR);
(deftfunc)("COMP-TEST-OR1" , f_COMP_TEST_OR1);
(deftfunc)("COMP-WHILE" , f_COMP_WHILE);
(deftfunc)("COMP-SETQ" , f_COMP_SETQ);
(deftfunc)("COMP-TAGBODY" , f_COMP_TAGBODY);
(deftfunc)("COMP-TAGBODY1" , f_COMP_TAGBODY1);
(deftfunc)("COMP-GO" , f_COMP_GO);
(deftfunc)("COMP-CONVERT" , f_COMP_CONVERT);
(deftfunc)("COMP-FUNCTION" , f_COMP_FUNCTION);
(deftfunc)("COMP-SYMBOL-FUNCTION" , f_COMP_SYMBOL_FUNCTION);
(deftfunc)("COMP-CLASS" , f_COMP_CLASS);
(deftfunc)("COMP-SYMBOL-CLASS" , f_COMP_SYMBOL_CLASS);
(deftfunc)("COMP-CATCH" , f_COMP_CATCH);
(deftfunc)("COMP-THROW" , f_COMP_THROW);
(deftfunc)("COMP-BLOCK" , f_COMP_BLOCK);
(deftfunc)("COMP-RETURN-FROM" , f_COMP_RETURN_FROM);
(deftfunc)("COMP-UNWIND-PROTECT" , f_COMP_UNWIND_PROTECT);
(deftfunc)("COMP-UNWIND-PROTECT1" , f_COMP_UNWIND_PROTECT1);
(deftfunc)("COMP-SETF" , f_COMP_SETF);
(deftfunc)("COMP-DYNAMIC" , f_COMP_DYNAMIC);
(deftfunc)("COMP-DYNAMIC-LET" , f_COMP_DYNAMIC_LET);
(deftfunc)("COMP-DYNAMIC-LET1" , f_COMP_DYNAMIC_LET1);
(deftfunc)("COMP-DYNAMIC-LET2" , f_COMP_DYNAMIC_LET2);
(deftfunc)("COMP-NOT" , f_COMP_NOT);
(deftfunc)("COMP-CAR" , f_COMP_CAR);
(deftfunc)("COMP-CDR" , f_COMP_CDR);
(deftfunc)("COMP-CONS" , f_COMP_CONS);
(deftfunc)("COMP-LENGTH" , f_COMP_LENGTH);
(deftfunc)("COMP-C-INCLUDE" , f_COMP_C_INCLUDE);
(deftfunc)("COMP-C-DEFINE" , f_COMP_C_DEFINE);
(deftfunc)("COMP-C-LANG" , f_COMP_C_LANG);
(deftfunc)("COMP-C-OPTION" , f_COMP_C_OPTION);
(deftfunc)("COMP-DEFGLOBAL" , f_COMP_DEFGLOBAL);
(deftfunc)("COMP-DEFCONSTANT" , f_COMP_DEFCONSTANT);
(deftfunc)("COMP-DEFDYNAMIC" , f_COMP_DEFDYNAMIC);
(deftfunc)("COMP-SET-DYNAMIC" , f_COMP_SET_DYNAMIC);
(deftfunc)("COMP-DEFMACRO" , f_COMP_DEFMACRO);
(deftfunc)("COMP-DEFCLASS" , f_COMP_DEFCLASS);
(deftfunc)("COMP-DEFMETHOD" , f_COMP_DEFMETHOD);
(deftfunc)("HAS-SAME-VARLIS-P" , f_HAS_SAME_VARLIS_P);
(deftfunc)("CONV-NAME" , f_CONV_NAME);
(deftfunc)("CONV-NAME1" , f_CONV_NAME1);
(deftfunc)("CONV-NAME2" , f_CONV_NAME2);
(deftfunc)("LIST-TO-C" , f_LIST_TO_C);
(deftfunc)("LIST-TO-C1" , f_LIST_TO_C1);
(deftfunc)("QUASI-TRANSFER" , f_QUASI_TRANSFER);
(deftfunc)("OPTIMIZE-P" , f_OPTIMIZE_P);
(deftfunc)("OPTIMIZE-P1" , f_OPTIMIZE_P1);
(deftfunc)("RETURN-TYPE" , f_RETURN_TYPE);
(deftfunc)("ARGUMENT-TYPE" , f_ARGUMENT_TYPE);
(deftfunc)("LOCAL-RETURN-TYPE" , f_LOCAL_RETURN_TYPE);
(deftfunc)("LOCAL-ARGUMENT-TYPE" , f_LOCAL_ARGUMENT_TYPE);
(deftfunc)("TYPE-GEN-ARG2" , f_TYPE_GEN_ARG2);
(deftfunc)("TYPE-GEN-ARG3" , f_TYPE_GEN_ARG3);
(deftfunc)("TYPE-GEN-CALL" , f_TYPE_GEN_CALL);
(deftfunc)("SUBSETP" , f_SUBSETP);
(deftfunc)("CLASS-DYNAMIC" , f_CLASS_DYNAMIC);
(deftfunc)("WARNING" , f_WARNING);
(deftfunc)("INFERENCE-FILE" , f_INFERENCE_FILE);
(deftfunc)("INFERENCE-DEFUN" , f_INFERENCE_DEFUN);
(deftfunc)("INFERENCE-LABELS" , f_INFERENCE_LABELS);
(deftfunc)("FIND-ARGUMENT-CLASS" , f_FIND_ARGUMENT_CLASS);
(deftfunc)("CREATE-INIT-ENV" , f_CREATE_INIT_ENV);
(deftfunc)("INFERENCE" , f_INFERENCE);
(deftfunc)("INFERENCE-ALL" , f_INFERENCE_ALL);
(deftfunc)("INFERENCE-ALL1" , f_INFERENCE_ALL1);
(deftfunc)("INFERENCE-COND" , f_INFERENCE_COND);
(deftfunc)("INFERENCE-COND1" , f_INFERENCE_COND1);
(deftfunc)("INFERENCE-COND2" , f_INFERENCE_COND2);
(deftfunc)("INFERENCE-CASE" , f_INFERENCE_CASE);
(deftfunc)("INFERENCE-CASE1" , f_INFERENCE_CASE1);
(deftfunc)("INFERENCE-CASE2" , f_INFERENCE_CASE2);
(deftfunc)("INFERENCE-IF" , f_INFERENCE_IF);
(deftfunc)("INFERENCE-IF1" , f_INFERENCE_IF1);
(deftfunc)("INFERENCE-IF2" , f_INFERENCE_IF2);
(deftfunc)("compiler6" , f_compiler6);
(deftfunc)("compiler7" , f_compiler7);
(deftfunc)("compiler8" , f_compiler8);
(deftfunc)("compiler9" , f_compiler9);
(deftfunc)("compiler10" , f_compiler10);
(deftfunc)("INFERENCE-NUMERIC" , f_INFERENCE_NUMERIC);
(deftfunc)("INFERENCE-LET" , f_INFERENCE_LET);
(deftfunc)("INFERENCE-FOR" , f_INFERENCE_FOR);
(deftfunc)("INFERENCE-WHILE" , f_INFERENCE_WHILE);
(deftfunc)("INFERENCE-WHILE1" , f_INFERENCE_WHILE1);
(deftfunc)("INFERENCE-FUNCTION" , f_INFERENCE_FUNCTION);
(deftfunc)("FIND-FUNCTION-TYPE" , f_FIND_FUNCTION_TYPE);
(deftfunc)("INFERENCE-ARG" , f_INFERENCE_ARG);
(deftfunc)("FUNCTION-TYPE-OBJECT-P" , f_FUNCTION_TYPE_OBJECT_P);
(deftfunc)("FIND-CLASS" , f_FIND_CLASS);
(deftfunc)("FIND-CLASS-IF" , f_FIND_CLASS_IF);
(deftfunc)("FIND-CLASS-COND" , f_FIND_CLASS_COND);
(deftfunc)("compiler11" , f_compiler11);
(deftfunc)("compiler12" , f_compiler12);
(deftfunc)("compiler13" , f_compiler13);
(deftfunc)("compiler14" , f_compiler14);
(deftfunc)("compiler15" , f_compiler15);
(deftfunc)("FIND-CLASS-NUMERIC" , f_FIND_CLASS_NUMERIC);
(deftfunc)("REFER" , f_REFER);
(deftfunc)("SET-TYPE-FUNCTION-OUTPUT" , f_SET_TYPE_FUNCTION_OUTPUT);
(deftfunc)("SET-TYPE-FUNCTION-INPUT" , f_SET_TYPE_FUNCTION_INPUT);
(deftfunc)("ADD-TYPE-FUNCTION-LOCAL" , f_ADD_TYPE_FUNCTION_LOCAL);
(deftfunc)("SET-LOCAL-TYPE-FUNCTION-OUTPUT" , f_SET_LOCAL_TYPE_FUNCTION_OUTPUT);
(deftfunc)("SET-LOCAL-TYPE-FUNCTION-INPUT" , f_SET_LOCAL_TYPE_FUNCTION_INPUT);
(deftfunc)("TYPE-FUNCTION-P" , f_TYPE_FUNCTION_P);
(deftfunc)("UNIFY" , f_UNIFY);
(deftfunc)("VARIABLEP" , f_VARIABLEP);
(deftfunc)("SUBCLASSP*" , f_SUBCLASSPstar);
(deftfunc)("ESTIMATE" , f_ESTIMATE);
(deftfunc)("CLASS*" , f_CLASSstar);
}void init_declare(void){
Fsetcatchsymbols(Fcons(Fmakesym("EXIT-ARG"),Fcons(Fmakesym("EXIT-FOR"),Fcons(Fmakesym("EXIT-LET"),Fcons(Fmakesym("EXIT-ALL"),Fcons(Fmakesym("EXIT-INFERENCE"),Fcons(Fmakesym("EXIT"),NIL)))))));Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("WHEN"),Fcons(Fcons(Fmakesym("TEST"),Fcons(Fmakesym(":REST"),Fcons(Fmakesym("BODY"),NIL))),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("TEST"),NIL)),Fcons(Fcons(Fmakesym("PROGN"),Fcons(Fcons(Fmakesym("UNQUOTE-SPLICING"),Fcons(Fmakesym("BODY"),NIL)),NIL)),NIL))),NIL)),NIL)))));
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("UNLESS"),Fcons(Fcons(Fmakesym("TEST"),Fcons(Fmakesym(":REST"),Fcons(Fmakesym("BODY"),NIL))),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("TEST"),NIL)),NIL)),Fcons(Fcons(Fmakesym("PROGN"),Fcons(Fcons(Fmakesym("UNQUOTE-SPLICING"),Fcons(Fmakesym("BODY"),NIL)),NIL)),NIL))),NIL)),NIL)))));
Fset_cdr(Fmakesym("COMP-GLOBAL-VAR"),Fcons(Fmakesym("INSTREAM"),Fcons(Fmakesym("NOT-NEED-RES"),Fcons(Fmakesym("NOT-NEED-COLON"),Fcons(Fmakesym("GLOBAL-VARIABLE"),Fcons(Fmakesym("FUNCTION-ARG"),Fcons(Fmakesym("GENERIC-NAME-ARG"),Fcons(Fmakesym("CATCH-BLOCK-TAG"),Fcons(Fmakesym("UNWIND-THUNK"),Fcons(Fmakesym("FILE-NAME-AND-EXT"),Fcons(Fmakesym("LAMBDA-COUNT"),Fcons(Fmakesym("LAMBDA-NEST"),Fcons(Fmakesym("C-LANG-OPTION"),Fcons(Fmakesym("CODE0"),Fcons(Fmakesym("CODE1"),Fcons(Fmakesym("CODE2"),Fcons(Fmakesym("CODE3"),Fcons(Fmakesym("CODE4"),Fcons(Fmakesym("CODE5"),Fcons(Fmakesym("CODE6"),Fcons(Fmakesym("CODE7"),NIL)))))))))))))))))))));Fset_opt(Fmakesym("COMP-GLOBAL-VAR"),FAST_GLOBAL);
Fset_cdr(Fmakesym("INSTREAM"),NIL);Fset_opt(Fmakesym("INSTREAM"),FAST_GLOBAL);
Fset_cdr(Fmakesym("NOT-NEED-RES"),Fcons(Fmakesym("LABELS"),Fcons(Fmakesym("FLET"),Fcons(Fmakesym("RETURN-FROM"),Fcons(Fmakesym("GO"),Fcons(Fmakesym("TAGBODY"),Fcons(Fmakesym("WHILE"),Fcons(Fmakesym("CALL-NEXT-METHOD"),Fcons(Fmakesym("THE"),Fcons(Fmakesym("C-LANG"),Fcons(Fmakesym("C-DEFINE"),Fcons(Fmakesym("C-INCLUDE"),Fcons(Fmakesym("C-OPTION"),NIL)))))))))))));Fset_opt(Fmakesym("NOT-NEED-RES"),FAST_GLOBAL);
Fset_cdr(Fmakesym("NOT-NEED-COLON"),Fcons(Fmakesym("C-LANG"),Fcons(Fmakesym("C-DEFINE"),Fcons(Fmakesym("C-INCLUDE"),Fcons(Fmakesym("C-OPTION"),NIL)))));Fset_opt(Fmakesym("NOT-NEED-COLON"),FAST_GLOBAL);
Fset_cdr(Fmakesym("GLOBAL-VARIABLE"),NIL);Fset_opt(Fmakesym("GLOBAL-VARIABLE"),FAST_GLOBAL);
Fset_cdr(Fmakesym("FUNCTION-ARG"),NIL);Fset_opt(Fmakesym("FUNCTION-ARG"),FAST_GLOBAL);
Fset_cdr(Fmakesym("GENERIC-NAME-ARG"),NIL);Fset_opt(Fmakesym("GENERIC-NAME-ARG"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CATCH-BLOCK-TAG"),NIL);Fset_opt(Fmakesym("CATCH-BLOCK-TAG"),FAST_GLOBAL);
Fset_cdr(Fmakesym("UNWIND-THUNK"),NIL);Fset_opt(Fmakesym("UNWIND-THUNK"),FAST_GLOBAL);
Fset_cdr(Fmakesym("FILE-NAME-AND-EXT"),NIL);Fset_opt(Fmakesym("FILE-NAME-AND-EXT"),FAST_GLOBAL);
Fset_cdr(Fmakesym("LAMBDA-COUNT"),Fmakeint(0));Fset_opt(Fmakesym("LAMBDA-COUNT"),FAST_GLOBAL);
Fset_cdr(Fmakesym("LAMBDA-NEST"),Fmakeint(0));Fset_opt(Fmakesym("LAMBDA-NEST"),FAST_GLOBAL);
Fset_cdr(Fmakesym("C-LANG-OPTION"),NIL);Fset_opt(Fmakesym("C-LANG-OPTION"),FAST_GLOBAL);
Fset_cdr(Fmakesym("OPTIMIZE-ENABLE"),NIL);Fset_opt(Fmakesym("OPTIMIZE-ENABLE"),FAST_GLOBAL);
Fset_cdr(Fmakesym("INFERENCE-NAME"),NIL);Fset_opt(Fmakesym("INFERENCE-NAME"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE0"),NIL);Fset_opt(Fmakesym("CODE0"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE1"),NIL);Fset_opt(Fmakesym("CODE1"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE2"),NIL);Fset_opt(Fmakesym("CODE2"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE3"),NIL);Fset_opt(Fmakesym("CODE3"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE4"),NIL);Fset_opt(Fmakesym("CODE4"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE5"),NIL);Fset_opt(Fmakesym("CODE5"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE6"),NIL);Fset_opt(Fmakesym("CODE6"),FAST_GLOBAL);
Fset_cdr(Fmakesym("CODE7"),NIL);Fset_opt(Fmakesym("CODE7"),FAST_GLOBAL);
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("ASSERT"),Fcons(Fcons(Fmakesym("SYM"),Fcons(Fmakesym(":REST"),Fcons(Fmakesym("CLASS"),NIL))),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("SET-PROPERTY"),Fcons(Fcons(Fmakesym("LIST"),Fcons(Fcons(Fmakesym("MAPCAR"),Fcons(Fcons(Fmakesym("FUNCTION"),Fcons(Fmakesym("EVAL"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("CLASS"),NIL)),NIL)),NIL))),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("SYM"),NIL)),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("INFERENCE"),NIL)),NIL)))),NIL)),NIL)))));
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("ASSERTZ"),Fcons(Fcons(Fmakesym("SYM"),Fcons(Fmakesym(":REST"),Fcons(Fmakesym("CLASS"),NIL))),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("LET"),Fcons(Fcons(Fcons(Fmakesym("OLD"),Fcons(Fcons(Fmakesym("PROPERTY"),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("SYM"),NIL)),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("INFERENCE"),NIL)),NIL))),NIL)),NIL),Fcons(Fcons(Fmakesym("SET-PROPERTY"),Fcons(Fcons(Fmakesym("APPEND"),Fcons(Fmakesym("OLD"),Fcons(Fcons(Fmakesym("LIST"),Fcons(Fcons(Fmakesym("MAPCAR"),Fcons(Fcons(Fmakesym("FUNCTION"),Fcons(Fmakesym("EVAL"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("CLASS"),NIL)),NIL)),NIL))),NIL)),NIL))),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("SYM"),NIL)),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("INFERENCE"),NIL)),NIL)))),NIL))),NIL)),NIL)))));
Fset_cdr(Fmakesym("FILE-NAME-AND-EXT"),NIL);Fset_opt(Fmakesym("FILE-NAME-AND-EXT"),FAST_GLOBAL);
Fset_cdr(Fmakesym("INSTREAM"),NIL);Fset_opt(Fmakesym("INSTREAM"),FAST_GLOBAL);
Fset_cdr(Fmakesym("TYPE-FUNCTION"),NIL);Fset_opt(Fmakesym("TYPE-FUNCTION"),FAST_GLOBAL);
Fset_cdr(Fmakesym("LOCAL-TYPE-FUNCTION"),NIL);Fset_opt(Fmakesym("LOCAL-TYPE-FUNCTION"),FAST_GLOBAL);
fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("PARSE-NUMBER")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("TAN")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ATAN")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("ATAN2")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SINH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("COSH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("TANH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("FLOOR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CEILING")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("TRUNCATE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ROUND")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("MOD")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("DIV")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("GCD")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("LCM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ISQRT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("CHAR=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("CHAR/=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("CHAR<")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("CHAR>")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("CHAR<=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("CHAR>=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("QUOTIENT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("RECIPROCAL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("MAX")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("MIN")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ABS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("EXP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("LOG")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("EXPT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SQRT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("CONS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CAR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CDR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("SET-CAR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("SET-CDR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("CREATE-LIST")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("CREATE-LIST")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("CREATE-LIST")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("LIST")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("REVERSE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("NREVERSE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("ASSOC")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("MEMBER")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("MAPCAR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("MAPC")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("MAPCAN")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("MAPLIST")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("MAPCL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("MAPCON")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<BASIC-ARRAY>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("CREATE-ARRAY")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<BASIC-ARRAY>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-VECTOR>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CREATE-VECTOR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-VECTOR>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("VECTOR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("CREATE-STRING")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING/=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING<")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING>")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING>=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING<=")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("FUNCALL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CHAR-INDEX")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("CHAR-INDEX")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL)))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("CHAR-INDEX")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING-INDEX")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("STRING-INDEX")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("STRING-INDEX")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("LENGTH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("LENGTH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-VECTOR>"),NIL)),NIL))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("LENGTH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("LENGTH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("LENGTH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("ELT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("ELT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-VECTOR>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL)))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("ELT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("ELT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL)))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("ELT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<SYMBOL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("NULL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<SYMBOL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("EQ")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("NOT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("FORMAT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("FORMAT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("FORMAT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("FORMAT-INTEGER")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("FORMAT-FLOAT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<CHARACTER>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("FORMAT-CHAR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("FORMAT-OBJECT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("FORMAT-TAB")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("FORMAT-FRESH-LINE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("STANDARD-INPUT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("STANDARD-OUTPUT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("SYSTEM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("OPEN-INPUT-FILE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("OPEN-OUTPUT-FILE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("OPEN-IO-FILE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("EVAL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ATOM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CONSP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SYMBOLP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("LISTP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CONSP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("NUMBERP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("INTEGERP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("FLOATP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("FIXNUMP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("LONGNUMP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("BIGNUMP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("STRINGP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CHARACTERP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("FUNCTIONP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("GENERAL-VECTOR-P")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("GENERAL-ARRAY*-P")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<SYMBOL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<SYMBOL>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("PROPERTY")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<SYMBOL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<SYMBOL>"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("SET-PROPERTY")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("READ")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("READ")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("READ")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("EVAL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("APPEND")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ERROR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("ERROR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("ERROR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("STRING-APPEND")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<SYMBOL>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SYMBOL-FUNCTION")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("APPLY")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("PRINT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-ARRAY*>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("AREF")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));({int res;int OLD = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("PROPERTY")),Fcons(fast_inverse(Fmakesym("AREF")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));res = fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(({int arg1,arg2,res;
arg1 = fast_inverse(OLD);
Fshelterpush(arg1);
arg2 = fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-VECTOR>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL)))))))))))));
Fshelterpush(arg2);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(arg1,Flist1(arg2))));
Fshelterpop();
Fshelterpop();
;res;})),Fcons(fast_inverse(Fmakesym("AREF")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));
res;})
;fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-ARRAY*>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("QUOTE"),Fcons(Fmakesym("REPEAT"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("GAREF")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-ARRAY*>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))))),Fcons(fast_inverse(Fmakesym("SET-AREF")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-ARRAY*>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<GENERAL-ARRAY*>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CREATE-ARRAY")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("EQUAL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("OPEN")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CLOSE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("STANDARD-INPUT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("STANDARD-OUTPUT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("CREATE-STRING-INPUT-STREAM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("CREATE-STRING-OUTPUT-STREAM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("GET-OUTPUT-STREAM-STRING")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("OPEN-INPUT-FILE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("OPEN-OUTPUT-FILE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("OPEN-IO-FILE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("FINISH-OUTPUT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("IGNORE-TOPLEVEL-CHECK")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SYSTEM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("MACROEXPAND-1")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("GET-METHOD")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("GET-METHOD-BODY")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("GET-METHOD-PRIORITY")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("READED-ARRAY-LIST")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CLASS-OF")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("SUBCLASSP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("READ-BYTE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("WRITE-BYTE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("PROBE-FILE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("FILE-POSITION")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("SET-FILE-POSITION")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("FILE-LENGTH")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))))),Fcons(fast_inverse(Fmakesym("CERROR")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("SIGNAL-CONDITION")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CONDITION-CONTINUABLE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("CONTINUE-CONDITION")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FUNCTION>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ARITHMETIC-ERROR-OPERATION")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("ARITHMETIC-ERROR-OPERANDS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("DOMAIN-ERROR-OBJECT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("DOMAIN-ERROR-EXPECTED-CLASS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("PARSE-ERROR-STRING")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("PARSE-ERROR-EXPECTED-CLASS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SIMPLE-ERROR-FORMAT-STRING")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<LIST>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SIMPLE-ERROR-FORMAT-ARGUMENTS")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("STREAM-ERROR-STREAM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STREAM>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("READ-LINE")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<INTEGER>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("RANDOM")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),NIL))))))))))),Fcons(fast_inverse(Fmakesym("RANDOM-REAL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("EQL")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<FLOAT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NUMBER>"),NIL)),NIL))))))))))))),Fcons(fast_inverse(Fmakesym("QUOTIENT")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<OBJECT>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("SUBRP")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));fast_convert(Fcallsubr(Fcar(Fmakesym("SET-PROPERTY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("EVAL"))),Flist1(fast_inverse(Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<NULL>"),NIL)),Fcons(Fcons(Fmakesym("CLASS"),Fcons(Fmakesym("<STRING>"),NIL)),NIL)))))))))))),Fcons(fast_inverse(Fmakesym("C-LANG")),Flist1(fast_inverse(Fmakesym("INFERENCE")))))));}