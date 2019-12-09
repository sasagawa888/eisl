#include "fast.h"
int f_ODDP(int arglist);int ODDP(int N);
int f_EVENP(int arglist);int EVENP(int N);
int f_ZEROP(int arglist);int ZEROP(int N);
int f_SQUARE(int arglist);int SQUARE(int N);
int f_SET_AREF1(int arglist);int SET_AREF1(int VAL,int MAT,int I,int J);
int f_AREF1(int arglist);int AREF1(int MAT,int I,int J);
int f_MULT_SCALAR_MAT(int arglist);int MULT_SCALAR_MAT(int S,int MAT);
int f_MATRIX_IDENT(int arglist);int MATRIX_IDENT(int N);
int f_SQUARE_MATRIX_P(int arglist);int SQUARE_MATRIX_P(int X);
int f_TR(int arglist);int TR(int X);
int f_SUB_MATRIX(int arglist);int SUB_MATRIX(int X,int R,int S);
int f_DET(int arglist);int DET(int X);
int f_DET1(int arglist);int DET1(int X,int M);
int f_SIGN(int arglist);int SIGN(int X);
int f_TRANSPOSE(int arglist);int TRANSPOSE(int X);
int f_INV(int arglist);int INV(int X);
int f_INV0(int arglist);int INV0(int X,int M);
int f_INV1(int arglist);int INV1(int X,int M);
int f_INV2(int arglist);int INV2(int X,int M);
int f_SUM(int arglist);int SUM(int F,int LS);
int f_PRODUCT(int arglist);int PRODUCT(int F,int LS);
int f_FOR_ALL(int arglist);int FOR_ALL(int F,int LS);
int f_AT_LEAST(int arglist);int AT_LEAST(int F,int LS);
int f_GAUSS_PRIMES(int arglist);int GAUSS_PRIMES(int X);
int f_COPRIMEP(int arglist);int COPRIMEP(int M,int N);
int f_DIVISIBLEP(int arglist);int DIVISIBLEP(int M,int N);
int f_EQMODP(int arglist);int EQMODP(int M,int N,int A);
int f_PRIMEP(int arglist);int PRIMEP(int N);
int f_DETERMINISTIC_PRIME_P(int arglist);int DETERMINISTIC_PRIME_P(int N);
int f_PRIMEPI(int arglist);int PRIMEPI(int N);
int f_TAU(int arglist);int TAU(int N);
int f_EXPT_1(int arglist);int EXPT_1(int N);
int f_LIOUVILLE_LAMBDA(int arglist);int LIOUVILLE_LAMBDA(int N);
int f_OMEGA(int arglist);int OMEGA(int N);
int f_dotslashexampleslashmath0(int arglist);int dotslashexampleslashmath0(int X);
int f_G(int arglist);int G(int N);
int f_SIGMA2(int arglist);int SIGMA2(int LS);
int f_SIGMA(int arglist);int SIGMA(int N);
int f_PERFECTP(int arglist);int PERFECTP(int N);
int f_MERSENNE(int arglist);int MERSENNE(int P);
int f_DOUBLE_PERFECT_NUMBER_P(int arglist);int DOUBLE_PERFECT_NUMBER_P(int N);
int f_FIND_DOUBLE_PERFECT(int arglist);int FIND_DOUBLE_PERFECT(int N);
int f_FERMATP(int arglist);int FERMATP(int N);
int f_LUCASP(int arglist);int LUCASP(int P);
int f_FERMAT_NUMBER(int arglist);int FERMAT_NUMBER(int N);
int f_RM1(int arglist);int RM1(int N);
int f_RM2(int arglist);int RM2(int A,int Q,int N);
int f_RM3(int arglist);int RM3(int A,int K,int Q,int N);
int f_RM4(int arglist);int RM4(int N,int A);
int f_RABIN_MILLER_P(int arglist);int RABIN_MILLER_P(int N);
int f_GAUSSMOD(int arglist);int GAUSSMOD(int A,int K,int M);
int f_TWIN_PRIMES(int arglist);int TWIN_PRIMES(int N,int M);
int f_DIVISORS(int arglist);int DIVISORS(int N);
int f_PRIME_FACTORS(int arglist);int PRIME_FACTORS(int N);
int f_FACTORIZE(int arglist);int FACTORIZE(int N);
int f_PHI(int arglist);int PHI(int N);
int f_dotslashexampleslashmath1(int arglist);int dotslashexampleslashmath1(int LS);
int f_PRIMITIVE_ROOT_P(int arglist);int PRIMITIVE_ROOT_P(int N,int P);
int f_EXPMOD(int arglist);int EXPMOD(int A,int N,int M);
int f_PRIMITIVE_ROOT(int arglist);int PRIMITIVE_ROOT(int P);
int f_IND(int arglist);int IND(int R,int A,int P);
int f_HIGHLY_COMPOSITE_NUMBER_P(int arglist);int HIGHLY_COMPOSITE_NUMBER_P(int N);
int f_MAX_TAU(int arglist);int MAX_TAU(int N,int M);
int f_CADR(int arglist);int CADR(int LS);
int f_CDDR(int arglist);int CDDR(int LS);
int f_ARG1(int arglist);int ARG1(int F);
int f_ARG2(int arglist);int ARG2(int F);
int f_ARG3(int arglist);int ARG3(int F);
int f_OP(int arglist);int OP(int F);
int f_SUBST(int arglist);int SUBST(int OLD,int NEW,int F);
int f_REMOVE(int arglist);int REMOVE(int X,int F);
int f_OPCODE(int arglist);int OPCODE(int OP);
int f_WEIGHT(int arglist);int WEIGHT(int OP);
int f_INFIX_greaterPREFIX(int arglist);int INFIX_greaterPREFIX(int FMLA);
int f_INFIP(int arglist);int INFIP(int FMLA);
int f_INF1(int arglist);int INF1(int FMLA,int OPTR,int OPLN);
int f_INF2(int arglist);int INF2(int FMLA,int OPTR,int OPLN);
int f_INF3(int arglist);int INF3(int FMLA,int OPTR,int OPLN);
int f_PREFIX_greaterINFIX(int arglist);int PREFIX_greaterINFIX(int FMLA);
int f_PRETF(int arglist);int PRETF(int F);
int f_PRET1(int arglist);int PRET1(int F,int WIN);
int f_PRET2(int arglist);int PRET2(int F,int WF);
int f_slashNESTP(int arglist);int slashNESTP(int F);
int f_plusNESTP(int arglist);int plusNESTP(int F);
int f_starSIMP1(int arglist);int starSIMP1(int F);
int f_starSIMP(int arglist);int starSIMP(int F);
int f_dotslashexampleslashmath2(int arglist);int dotslashexampleslashmath2(int C);
int f_LAT(int arglist);int LAT(int LS);
int f_plusSIMP(int arglist);int plusSIMP(int F);
int f__SIMP(int arglist);int _SIMP(int F);
int f_slashSIMP(int arglist);int slashSIMP(int F);
int f_hatSIMP(int arglist);int hatSIMP(int F);
int f_SIN_SIMP(int arglist);int SIN_SIMP(int F);
int f_COS_SIMP(int arglist);int COS_SIMP(int F);
int f_ATAN_SIMP(int arglist);int ATAN_SIMP(int F);
int f_SINH_SIMP(int arglist);int SINH_SIMP(int F);
int f_exclamationSIMP(int arglist);int exclamationSIMP(int F);
int f_FACTORIAL(int arglist);int FACTORIAL(int N);
int f_SIMPS(int arglist);int SIMPS(int F);
int f_SIMPF(int arglist);int SIMPF(int FF);
int f_starCOMNUM(int arglist);int starCOMNUM(int F,int NUMB,int SYMB,int IMAG);
int f_starNUMB(int arglist);int starNUMB(int S);
int f_starIMAG(int arglist);int starIMAG(int S);
int f_plusCOMNUM(int arglist);int plusCOMNUM(int F,int NUMB,int SYMB);
int f_COMNUM(int arglist);int COMNUM(int F);
int f_SIMPC(int arglist);int SIMPC(int FF);
int f_SIMPL(int arglist);int SIMPL(int FF);
int f_starAUX(int arglist);int starAUX(int F,int VAR);
int f_dotslashexampleslashmath3(int arglist);int dotslashexampleslashmath3(int C);
int f_starDERIV(int arglist);int starDERIV(int FMLA,int VAR);
int f_dotslashexampleslashmath4(int arglist);int dotslashexampleslashmath4(int C);
int f_slashDERIV(int arglist);int slashDERIV(int FMLA,int VAR);
int f_plusDERIV(int arglist);int plusDERIV(int FMLA,int VAR);
int f_dotslashexampleslashmath5(int arglist);int dotslashexampleslashmath5(int C);
int f__DERIV(int arglist);int _DERIV(int FMLA,int VAR);
int f_dotslashexampleslashmath6(int arglist);int dotslashexampleslashmath6(int C);
int f_DERIVE(int arglist);int DERIVE(int FMLA,int VAR);
int f_SDERIV(int arglist);int SDERIV(int F,int VAR);
int f_CDERIV(int arglist);int CDERIV(int F,int VAR);
int f_TDERIV(int arglist);int TDERIV(int F,int VAR);
int f_ASDERIV(int arglist);int ASDERIV(int F,int VAR);
int f_ACDERIV(int arglist);int ACDERIV(int F,int VAR);
int f_ATDERIV(int arglist);int ATDERIV(int F,int VAR);
int f_LOGDERIV(int arglist);int LOGDERIV(int F,int VAR);
int f_SHDERIV(int arglist);int SHDERIV(int F,int VAR);
int f_CHDERIV(int arglist);int CHDERIV(int F,int VAR);
int f_hatDERIV(int arglist);int hatDERIV(int FMLA,int VAR);
int f_DEPEND(int arglist);int DEPEND(int FMLA,int VAR);
int f_FREE(int arglist);int FREE(int FMLA,int VAR);
int f_NDERIVE(int arglist);int NDERIVE(int N,int FMLA,int VAR);
int f_DIF2(int arglist);int DIF2(int FMLA,int VAR);
int f_DIFF(int arglist);int DIFF(int FMLA,int VAR);
int f_DIF(int arglist);int DIF(int FMLA,int VAR);
int f_SINT(int arglist);int SINT(int F,int VAR);
int f_CINT(int arglist);int CINT(int F,int VAR);
int f_TINT(int arglist);int TINT(int F,int VAR);
int f_CTINT(int arglist);int CTINT(int F,int VAR);
int f_LINT(int arglist);int LINT(int F,int VAR);
int f_hatINT(int arglist);int hatINT(int F,int VAR);
int f_MLIN(int arglist);int MLIN(int FF,int VAR);
int f_INTF(int arglist);int INTF(int F,int VAR);
int f_INTL(int arglist);int INTL(int F,int VAR);
int f_VARP(int arglist);int VARP(int X);
int f_CHARACTER(int arglist);int CHARACTER(int X);
int f_MEMBERP(int arglist);int MEMBERP(int A,int B);
int f_MATCHF1(int arglist);int MATCHF1(int P,int F,int VAR);
int f_MATCHF2(int arglist);int MATCHF2(int P,int F,int VAR);
int f_MATCHF(int arglist);int MATCHF(int P,int F,int VAR);
int f_ODDP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ODDP(fast_convert(arg1))));
}
int f_EVENP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(EVENP(fast_convert(arg1))));
}
int f_ZEROP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ZEROP(fast_convert(arg1))));
}
int f_SQUARE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SQUARE(fast_convert(arg1))));
}
int f_SET_AREF1(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(SET_AREF1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_AREF1(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(AREF1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_MULT_SCALAR_MAT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(MULT_SCALAR_MAT(fast_convert(arg1),fast_convert(arg2))));
}
int f_MATRIX_IDENT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(MATRIX_IDENT(fast_convert(arg1))));
}
int f_SQUARE_MATRIX_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SQUARE_MATRIX_P(fast_convert(arg1))));
}
int f_TR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(TR(fast_convert(arg1))));
}
int f_SUB_MATRIX(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(SUB_MATRIX(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_DET(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DET(fast_convert(arg1))));
}
int f_DET1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DET1(fast_convert(arg1),fast_convert(arg2))));
}
int f_SIGN(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIGN(fast_convert(arg1))));
}
int f_TRANSPOSE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(TRANSPOSE(fast_convert(arg1))));
}
int f_INV(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INV(fast_convert(arg1))));
}
int f_INV0(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INV0(fast_convert(arg1),fast_convert(arg2))));
}
int f_INV1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INV1(fast_convert(arg1),fast_convert(arg2))));
}
int f_INV2(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INV2(fast_convert(arg1),fast_convert(arg2))));
}
int f_SUM(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SUM(fast_convert(arg1),fast_convert(arg2))));
}
int f_PRODUCT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(PRODUCT(fast_convert(arg1),fast_convert(arg2))));
}
int f_FOR_ALL(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FOR_ALL(fast_convert(arg1),fast_convert(arg2))));
}
int f_AT_LEAST(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(AT_LEAST(fast_convert(arg1),fast_convert(arg2))));
}
int f_GAUSS_PRIMES(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(GAUSS_PRIMES(fast_convert(arg1))));
}
int f_COPRIMEP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(COPRIMEP(fast_convert(arg1),fast_convert(arg2))));
}
int f_DIVISIBLEP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DIVISIBLEP(fast_convert(arg1),fast_convert(arg2))));
}
int f_EQMODP(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(EQMODP(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_PRIMEP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PRIMEP(fast_convert(arg1))));
}
int f_DETERMINISTIC_PRIME_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DETERMINISTIC_PRIME_P(fast_convert(arg1))));
}
int f_PRIMEPI(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PRIMEPI(fast_convert(arg1))));
}
int f_TAU(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(TAU(fast_convert(arg1))));
}
int f_EXPT_1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(EXPT_1(fast_convert(arg1))));
}
int f_LIOUVILLE_LAMBDA(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LIOUVILLE_LAMBDA(fast_convert(arg1))));
}
int f_OMEGA(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(OMEGA(fast_convert(arg1))));
}
int f_dotslashexampleslashmath0(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashmath0(fast_convert(arg1))));
}
int f_G(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(G(fast_convert(arg1))));
}
int f_SIGMA2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIGMA2(fast_convert(arg1))));
}
int f_SIGMA(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIGMA(fast_convert(arg1))));
}
int f_PERFECTP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PERFECTP(fast_convert(arg1))));
}
int f_MERSENNE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(MERSENNE(fast_convert(arg1))));
}
int f_DOUBLE_PERFECT_NUMBER_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DOUBLE_PERFECT_NUMBER_P(fast_convert(arg1))));
}
int f_FIND_DOUBLE_PERFECT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FIND_DOUBLE_PERFECT(fast_convert(arg1))));
}
int f_FERMATP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FERMATP(fast_convert(arg1))));
}
int f_LUCASP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LUCASP(fast_convert(arg1))));
}
int f_FERMAT_NUMBER(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FERMAT_NUMBER(fast_convert(arg1))));
}
int f_RM1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(RM1(fast_convert(arg1))));
}
int f_RM2(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(RM2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_RM3(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(RM3(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_RM4(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(RM4(fast_convert(arg1),fast_convert(arg2))));
}
int f_RABIN_MILLER_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(RABIN_MILLER_P(fast_convert(arg1))));
}
int f_GAUSSMOD(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(GAUSSMOD(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_TWIN_PRIMES(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TWIN_PRIMES(fast_convert(arg1),fast_convert(arg2))));
}
int f_DIVISORS(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(DIVISORS(fast_convert(arg1))));
}
int f_PRIME_FACTORS(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PRIME_FACTORS(fast_convert(arg1))));
}
int f_FACTORIZE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FACTORIZE(fast_convert(arg1))));
}
int f_PHI(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PHI(fast_convert(arg1))));
}
int f_dotslashexampleslashmath1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashmath1(fast_convert(arg1))));
}
int f_PRIMITIVE_ROOT_P(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(PRIMITIVE_ROOT_P(fast_convert(arg1),fast_convert(arg2))));
}
int f_EXPMOD(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(EXPMOD(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_PRIMITIVE_ROOT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PRIMITIVE_ROOT(fast_convert(arg1))));
}
int f_IND(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(IND(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_HIGHLY_COMPOSITE_NUMBER_P(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(HIGHLY_COMPOSITE_NUMBER_P(fast_convert(arg1))));
}
int f_MAX_TAU(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(MAX_TAU(fast_convert(arg1),fast_convert(arg2))));
}
int f_CADR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CADR(fast_convert(arg1))));
}
int f_CDDR(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CDDR(fast_convert(arg1))));
}
int f_ARG1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ARG1(fast_convert(arg1))));
}
int f_ARG2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ARG2(fast_convert(arg1))));
}
int f_ARG3(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ARG3(fast_convert(arg1))));
}
int f_OP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(OP(fast_convert(arg1))));
}
int f_SUBST(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(SUBST(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_REMOVE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(REMOVE(fast_convert(arg1),fast_convert(arg2))));
}
int f_OPCODE(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(OPCODE(fast_convert(arg1))));
}
int f_WEIGHT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(WEIGHT(fast_convert(arg1))));
}
int f_INFIX_greaterPREFIX(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INFIX_greaterPREFIX(fast_convert(arg1))));
}
int f_INFIP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(INFIP(fast_convert(arg1))));
}
int f_INF1(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(INF1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_INF2(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(INF2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_INF3(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(INF3(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_PREFIX_greaterINFIX(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PREFIX_greaterINFIX(fast_convert(arg1))));
}
int f_PRETF(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(PRETF(fast_convert(arg1))));
}
int f_PRET1(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(PRET1(fast_convert(arg1),fast_convert(arg2))));
}
int f_PRET2(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(PRET2(fast_convert(arg1),fast_convert(arg2))));
}
int f_slashNESTP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(slashNESTP(fast_convert(arg1))));
}
int f_plusNESTP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(plusNESTP(fast_convert(arg1))));
}
int f_starSIMP1(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(starSIMP1(fast_convert(arg1))));
}
int f_starSIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(starSIMP(fast_convert(arg1))));
}
int f_dotslashexampleslashmath2(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashmath2(fast_convert(arg1))));
}
int f_LAT(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(LAT(fast_convert(arg1))));
}
int f_plusSIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(plusSIMP(fast_convert(arg1))));
}
int f__SIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(_SIMP(fast_convert(arg1))));
}
int f_slashSIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(slashSIMP(fast_convert(arg1))));
}
int f_hatSIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(hatSIMP(fast_convert(arg1))));
}
int f_SIN_SIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIN_SIMP(fast_convert(arg1))));
}
int f_COS_SIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COS_SIMP(fast_convert(arg1))));
}
int f_ATAN_SIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(ATAN_SIMP(fast_convert(arg1))));
}
int f_SINH_SIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SINH_SIMP(fast_convert(arg1))));
}
int f_exclamationSIMP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(exclamationSIMP(fast_convert(arg1))));
}
int f_FACTORIAL(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(FACTORIAL(fast_convert(arg1))));
}
int f_SIMPS(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIMPS(fast_convert(arg1))));
}
int f_SIMPF(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIMPF(fast_convert(arg1))));
}
int f_starCOMNUM(int arglist){
int arg1,arg2,arg3,arg4;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
arg4 = Fnth(3,arglist);
return(fast_inverse(starCOMNUM(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3),fast_convert(arg4))));
}
int f_starNUMB(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(starNUMB(fast_convert(arg1))));
}
int f_starIMAG(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(starIMAG(fast_convert(arg1))));
}
int f_plusCOMNUM(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(plusCOMNUM(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_COMNUM(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(COMNUM(fast_convert(arg1))));
}
int f_SIMPC(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIMPC(fast_convert(arg1))));
}
int f_SIMPL(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(SIMPL(fast_convert(arg1))));
}
int f_starAUX(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(starAUX(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashmath3(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashmath3(fast_convert(arg1))));
}
int f_starDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(starDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashmath4(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashmath4(fast_convert(arg1))));
}
int f_slashDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(slashDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_plusDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(plusDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashmath5(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashmath5(fast_convert(arg1))));
}
int f__DERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(_DERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_dotslashexampleslashmath6(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(dotslashexampleslashmath6(fast_convert(arg1))));
}
int f_DERIVE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DERIVE(fast_convert(arg1),fast_convert(arg2))));
}
int f_SDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_CDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(CDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_TDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_ASDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ASDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_ACDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ACDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_ATDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(ATDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_LOGDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LOGDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_SHDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SHDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_CHDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(CHDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_hatDERIV(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(hatDERIV(fast_convert(arg1),fast_convert(arg2))));
}
int f_DEPEND(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DEPEND(fast_convert(arg1),fast_convert(arg2))));
}
int f_FREE(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(FREE(fast_convert(arg1),fast_convert(arg2))));
}
int f_NDERIVE(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(NDERIVE(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_DIF2(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DIF2(fast_convert(arg1),fast_convert(arg2))));
}
int f_DIFF(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DIFF(fast_convert(arg1),fast_convert(arg2))));
}
int f_DIF(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(DIF(fast_convert(arg1),fast_convert(arg2))));
}
int f_SINT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(SINT(fast_convert(arg1),fast_convert(arg2))));
}
int f_CINT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(CINT(fast_convert(arg1),fast_convert(arg2))));
}
int f_TINT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(TINT(fast_convert(arg1),fast_convert(arg2))));
}
int f_CTINT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(CTINT(fast_convert(arg1),fast_convert(arg2))));
}
int f_LINT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(LINT(fast_convert(arg1),fast_convert(arg2))));
}
int f_hatINT(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(hatINT(fast_convert(arg1),fast_convert(arg2))));
}
int f_MLIN(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(MLIN(fast_convert(arg1),fast_convert(arg2))));
}
int f_INTF(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INTF(fast_convert(arg1),fast_convert(arg2))));
}
int f_INTL(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(INTL(fast_convert(arg1),fast_convert(arg2))));
}
int f_VARP(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(VARP(fast_convert(arg1))));
}
int f_CHARACTER(int arglist){
int arg1;
arg1 = Fnth(0,arglist);
return(fast_inverse(CHARACTER(fast_convert(arg1))));
}
int f_MEMBERP(int arglist){
int arg1,arg2;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
return(fast_inverse(MEMBERP(fast_convert(arg1),fast_convert(arg2))));
}
int f_MATCHF1(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(MATCHF1(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_MATCHF2(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(MATCHF2(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int f_MATCHF(int arglist){
int arg1,arg2,arg3;
arg1 = Fnth(0,arglist);
arg2 = Fnth(1,arglist);
arg3 = Fnth(2,arglist);
return(fast_inverse(MATCHF(fast_convert(arg1),fast_convert(arg2),fast_convert(arg3))));
}
int dotslashexampleslashmath0(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_immediate(1))))));
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int dotslashexampleslashmath1(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
res = fast_minus(fast_convert(fast_immediate(1)),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(0)))))))))))));
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int dotslashexampleslashmath2(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
res = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(ARG1(Fnth(0,Fcdr(Fmakesym("dotslashexampleslashmath2"))))),Flist1(fast_inverse(C))))));
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int dotslashexampleslashmath3(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
res = Fcons(fast_inverse(fast_convert(fast_car(Fnth(0,Fcdr(Fmakesym("dotslashexampleslashmath3")))))),fast_inverse(C));
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int dotslashexampleslashmath4(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
res = Fcons(fast_inverse(Fmakesym("*")),fast_inverse(C));
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int dotslashexampleslashmath5(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
res = DERIVE(C,Fnth(0,Fcdr(Fmakesym("dotslashexampleslashmath5"))));
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int dotslashexampleslashmath6(int C){
int res;
if(CELLRANGE(C)) Fshelterpush(C);
res = DERIVE(C,Fnth(0,Fcdr(Fmakesym("dotslashexampleslashmath6"))));
if(CELLRANGE(C)) Fshelterpop();
return(res);}
int ODDP(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("INTEGERP")),Flist1(fast_inverse(N))))) != NIL)
if((res=fast_numeqp(fast_convert(fast_mod(fast_convert(N),fast_convert(fast_immediate(2)))),fast_convert(fast_immediate(1)))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int EVENP(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("INTEGERP")),Flist1(fast_inverse(N))))) != NIL)
if((res=fast_numeqp(fast_convert(fast_mod(fast_convert(N),fast_convert(fast_immediate(2)))),fast_convert(fast_immediate(0)))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int ZEROP(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0)));
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int SQUARE(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = fast_mult(fast_convert(N),fast_convert(N));
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int SET_AREF1(int VAL,int MAT,int I,int J){
int res;
if(CELLRANGE(VAL)) Fshelterpush(VAL);
if(CELLRANGE(MAT)) Fshelterpush(MAT);
if(CELLRANGE(I)) Fshelterpush(I);
if(CELLRANGE(J)) Fshelterpush(J);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SET-AREF")),Fcons(fast_inverse(VAL),Fcons(fast_inverse(MAT),Fcons(fast_inverse(fast_minus(fast_convert(I),fast_convert(fast_immediate(1)))),Flist1(fast_inverse(fast_minus(fast_convert(J),fast_convert(fast_immediate(1))))))))));res;});
if(CELLRANGE(J)) Fshelterpop();
if(CELLRANGE(I)) Fshelterpop();
if(CELLRANGE(MAT)) Fshelterpop();
if(CELLRANGE(VAL)) Fshelterpop();
return(res);}
int AREF1(int MAT,int I,int J){
int res;
if(CELLRANGE(MAT)) Fshelterpush(MAT);
if(CELLRANGE(I)) Fshelterpush(I);
if(CELLRANGE(J)) Fshelterpush(J);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("AREF")),Fcons(fast_inverse(MAT),Fcons(fast_inverse(fast_minus(fast_convert(I),fast_convert(fast_immediate(1)))),Flist1(fast_inverse(fast_minus(fast_convert(J),fast_convert(fast_immediate(1)))))))));res;});
if(CELLRANGE(J)) Fshelterpop();
if(CELLRANGE(I)) Fshelterpop();
if(CELLRANGE(MAT)) Fshelterpop();
return(res);}
int MULT_SCALAR_MAT(int S,int MAT){
int res;
if(CELLRANGE(S)) Fshelterpush(S);
if(CELLRANGE(MAT)) Fshelterpush(MAT);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int M = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(MAT))))),Flist1(fast_inverse(fast_immediate(0)))))));int N = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(MAT))))),Flist1(fast_inverse(fast_immediate(1)))))));res = ({int res;
int I = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(I),fast_convert(M)) == NIL){
({int res;
int J = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(J),fast_convert(N)) == NIL){
SET_AREF1(fast_mult(fast_convert(S),fast_convert(AREF1(MAT,I,J))),MAT,I,J);
temp1 = fast_plus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = MAT;res;});
res;})
;
if(CELLRANGE(MAT)) Fshelterpop();
if(CELLRANGE(S)) Fshelterpop();
return(res);}
int MATRIX_IDENT(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int M = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-ARRAY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(N),Flist1(fast_inverse(N)))))),Flist1(fast_inverse(fast_immediate(0)))))));res = ({int res;
int I = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(I),fast_convert(N)) == NIL){
SET_AREF1(fast_immediate(1),M,I,I);
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = M;res;});
res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int SQUARE_MATRIX_P(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int DIM = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X)))));res = ({int res;
if((res = fast_numeqp(fast_convert(Flength(DIM)),fast_convert(fast_immediate(2)))) != NIL)
if((res=fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(DIM),Flist1(fast_inverse(fast_immediate(0))))))),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(DIM),Flist1(fast_inverse(fast_immediate(1))))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int TR(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(SQUARE_MATRIX_P(X)) != NIL){
res = ({int res;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("tr require square matrix")),Flist1(fast_inverse(X)))));res;});}
 else res = NIL;res;})
;
res = ({int res;int L = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(0)))))));res = ({int res;
int I = fast_convert(fast_immediate(1));int Y = fast_convert(fast_immediate(0));int temp1,temp2;
while(fast_greaterp(fast_convert(I),fast_convert(L)) == NIL){
({int res;
 res = Y = fast_plus(fast_convert(AREF1(X,I,I)),fast_convert(Y));res;})
;
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = Y;res;});
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SUB_MATRIX(int X,int R,int S){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(R)) Fshelterpush(R);
if(CELLRANGE(S)) Fshelterpush(S);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int M = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(0)))))));int N = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(1)))))));int Y = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-ARRAY")),Fcons(fast_inverse(fast_minus(fast_convert(M),fast_convert(fast_immediate(1)))),Fcons(fast_inverse(fast_minus(fast_convert(N),fast_convert(fast_immediate(1)))),Flist1(fast_inverse(fast_immediate(0))))))));res = ({int res;
int I = fast_convert(fast_immediate(0));int temp1;
while(fast_eqgreaterp(fast_convert(I),fast_convert(M)) == NIL){
({int res;
int J = fast_convert(fast_immediate(0));int temp1;
while(fast_eqgreaterp(fast_convert(J),fast_convert(N)) == NIL){
({int res=NIL;
if((fast_smallerp(fast_convert(I),fast_convert(R)) && fast_smallerp(fast_convert(J),fast_convert(S))) != NIL){
res = SET_AREF1(AREF1(X,I,J),Y,I,J);}
else if((fast_greaterp(fast_convert(I),fast_convert(R)) && fast_smallerp(fast_convert(J),fast_convert(S))) != NIL){
res = SET_AREF1(AREF1(X,I,J),Y,fast_minus(fast_convert(I),fast_convert(fast_immediate(1))),J);}
else if((fast_smallerp(fast_convert(I),fast_convert(R)) && fast_greaterp(fast_convert(J),fast_convert(S))) != NIL){
res = SET_AREF1(AREF1(X,I,J),Y,I,fast_minus(fast_convert(J),fast_convert(fast_immediate(1))));}
else if((fast_greaterp(fast_convert(I),fast_convert(R)) && fast_greaterp(fast_convert(J),fast_convert(S))) != NIL){
res = SET_AREF1(AREF1(X,I,J),Y,fast_minus(fast_convert(I),fast_convert(fast_immediate(1))),fast_minus(fast_convert(J),fast_convert(fast_immediate(1))));}
else if((fast_numeqp(fast_convert(I),fast_convert(R)) && fast_numeqp(fast_convert(J),fast_convert(S))) != NIL){
res = NIL;}
;res;});
temp1 = fast_plus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = Y;res;});
res;})
;
if(CELLRANGE(S)) Fshelterpop();
if(CELLRANGE(R)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int DET(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(SQUARE_MATRIX_P(X)) != NIL){
res = ({int res;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("det require square matrix")),Flist1(fast_inverse(X)))));res;});}
 else res = NIL;res;})
;
res = ({int res;int M = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(0)))))));res = DET1(X,M);
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int DET1(int X,int M){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(M),fast_convert(fast_immediate(2))) != NIL){
res = fast_minus(fast_convert(fast_mult(fast_convert(AREF1(X,fast_immediate(1),fast_immediate(1))),fast_convert(AREF1(X,fast_immediate(2),fast_immediate(2))))),fast_convert(fast_mult(fast_convert(AREF1(X,fast_immediate(1),fast_immediate(2))),fast_convert(AREF1(X,fast_immediate(2),fast_immediate(1))))));}
else{
res = ({int res;
int I = fast_convert(fast_immediate(1));int Y = fast_convert(fast_immediate(0));int temp1,temp2;
while(fast_greaterp(fast_convert(I),fast_convert(M)) == NIL){
({int res;
 res = Y = fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("*")),Fcons(fast_inverse(SIGN(fast_plus(fast_convert(I),fast_convert(fast_immediate(1))))),Fcons(fast_inverse(AREF1(X,I,fast_immediate(1))),Flist1(fast_inverse(DET1(SUB_MATRIX(X,I,fast_immediate(1)),fast_minus(fast_convert(M),fast_convert(fast_immediate(1))))))))))),fast_convert(Y));res;})
;
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = Y;res;});}res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SIGN(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(X)))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int TRANSPOSE(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int M = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(0)))))));int N = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(1)))))));int Y = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-ARRAY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(N),Flist1(fast_inverse(M)))))),Flist1(fast_inverse(fast_immediate(0)))))));res = ({int res;
int I = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(I),fast_convert(M)) == NIL){
({int res;
int J = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(J),fast_convert(N)) == NIL){
SET_AREF1(AREF1(X,I,J),Y,J,I);
temp1 = fast_plus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = Y;res;});
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INV(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
({int res;
if(fast_not(SQUARE_MATRIX_P(X)) != NIL){
res = ({int res;
res = fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("inv require square matrix")),Flist1(fast_inverse(X)))));res;});}
 else res = NIL;res;})
;
res = ({int res;int M = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(0)))))));int N = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ARRAY-DIMENSIONS")),Flist1(fast_inverse(X))))),Flist1(fast_inverse(fast_immediate(1)))))));res = ({int res;
if(fast_greaterp(fast_convert(M),fast_convert(fast_immediate(2))) != NIL){
res = INV1(X,M);}
else{
res = INV0(X,M);}res;})
;
res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INV0(int X,int M){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int MAT = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-ARRAY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(M),Flist1(fast_inverse(M)))))),Flist1(fast_inverse(fast_immediate(0)))))));int D = fast_convert(DET(X));({int res;
if(fast_numeqp(fast_convert(D),fast_convert(fast_immediate(0))) != NIL){
res = ({int res;
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("inv determinant is zero")),Flist1(fast_inverse(X)))));res;});res;});}
 else res = NIL;res;})
;
res = ({int res=NIL;
if(fast_numeqp(fast_convert(M),fast_convert(fast_immediate(1))) != NIL){
res = SET_AREF1(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(D))))),MAT,fast_immediate(1),fast_immediate(1));
res = MAT;}
else{
res = SET_AREF1(AREF1(X,fast_immediate(2),fast_immediate(2)),MAT,fast_immediate(1),fast_immediate(1));
res = SET_AREF1(AREF1(X,fast_immediate(1),fast_immediate(1)),MAT,fast_immediate(2),fast_immediate(2));
res = SET_AREF1(fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(AREF1(X,fast_immediate(1),fast_immediate(2)))))),MAT,fast_immediate(1),fast_immediate(2));
res = SET_AREF1(fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(AREF1(X,fast_immediate(2),fast_immediate(1)))))),MAT,fast_immediate(2),fast_immediate(1));
res = MULT_SCALAR_MAT(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(D))))),MAT);}
;res;});
res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INV1(int X,int M){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int D = fast_convert(DET(X));({int res;
if(fast_numeqp(fast_convert(D),fast_convert(fast_immediate(0))) != NIL){
res = ({int res;
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("inv determinant is zero")),Flist1(fast_inverse(X)))));res;});res;});}
 else res = NIL;res;})
;
res = fast_mult(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(D)))))),fast_convert(TRANSPOSE(INV2(X,M))));
res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int INV2(int X,int M){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int Y = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("CREATE-ARRAY")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(M),Flist1(fast_inverse(M)))))),Flist1(fast_inverse(fast_immediate(0)))))));res = ({int res;
int I = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(I),fast_convert(M)) == NIL){
({int res;
int J = fast_convert(fast_immediate(1));int temp1;
while(fast_greaterp(fast_convert(J),fast_convert(M)) == NIL){
SET_AREF1(Y,I,J,fast_mult(fast_convert(SIGN(fast_plus(fast_convert(I),fast_convert(J)))),fast_convert(DET(SUB_MATRIX(X,I,J)))));
temp1 = fast_plus(fast_convert(J),fast_convert(fast_immediate(1)));
J = temp1;
}
res=NIL;res;});
temp1 = fast_plus(fast_convert(I),fast_convert(fast_immediate(1)));
I = temp1;
}
res = Y;res;});
res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int SUM(int F,int LS){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = fast_immediate(0);}
else{
res = fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_convert(fast_car(LS)))))))),fast_convert(SUM(F,fast_convert(fast_cdr(LS)))));}res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int PRODUCT(int F,int LS){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = fast_immediate(1);}
else{
res = fast_mult(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_convert(fast_car(LS)))))))),fast_convert(PRODUCT(F,fast_convert(fast_cdr(LS)))));}res;})
;
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int FOR_ALL(int F,int LS){
int res;
int temp1,temp2;
FOR_ALLloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = T;}
else if(fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("FUNCALL")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_convert(fast_car(LS)))))))) != NIL){
res = NIL;}
else{
{
temp1 = F;
temp2 = fast_convert(fast_cdr(LS));
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
F = temp1;
LS = temp2;
goto FOR_ALLloop;};}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int AT_LEAST(int F,int LS){
int res;
int temp1,temp2;
AT_LEASTloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
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
goto AT_LEASTloop;};}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int GAUSS_PRIMES(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LOG")),Flist1(fast_inverse(X)))))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int COPRIMEP(int M,int N){
int res;
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = fast_numeqp(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("GCD")),Fcons(fast_inverse(M),Flist1(fast_inverse(N)))))),fast_convert(fast_immediate(1)));
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
return(res);}
int DIVISIBLEP(int M,int N){
int res;
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("INTEGERP")),Flist1(fast_inverse(M))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("INTEGERP")),Flist1(fast_inverse(N))))) != NIL)
if((res=fast_numeqp(fast_convert(fast_mod(fast_convert(M),fast_convert(N))),fast_convert(fast_immediate(0)))) !=NIL)
res=res;
else res=NIL;
else res=NIL;else res=NIL;res;})
;
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
return(res);}
int EQMODP(int M,int N,int A){
int res;
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = fast_numeqp(fast_convert(fast_mod(fast_convert(M),fast_convert(A))),fast_convert(fast_mod(fast_convert(N),fast_convert(A))));
if(CELLRANGE(A)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
return(res);}
int PRIMEP(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_smallerp(fast_convert(N),fast_convert(Fmakebig("1000000000000000000"))) != NIL){
res = DETERMINISTIC_PRIME_P(N);}
else{
res = RABIN_MILLER_P(N);}res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int DETERMINISTIC_PRIME_P(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int X,int Y){
int res;
int temp1,temp2;
ITERloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(X),fast_convert(Y)) != NIL){
res = T;}
else if(DIVISIBLEP(N,X) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(X),fast_convert(fast_immediate(2))) != NIL){
res = ITER(fast_immediate(3),Y);}
else{
res = ITER(fast_plus(fast_convert(X),fast_convert(fast_immediate(2))),Y);}
;res;});
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
res = ({int res;
if(fast_smallerp(fast_convert(N),fast_convert(fast_immediate(2))) != NIL){
res = NIL;}
else{
res = ITER(fast_immediate(2),fast_convert(Fcallsubr(Fcar(Fmakesym("SQRT")),Flist1(fast_inverse(N)))));}res;})
;

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int PRIMEPI(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int X,int Y){
int res;
int temp1,temp2;
ITERloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(Y)) Fshelterpush(Y);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(X),fast_convert(N)) != NIL){
res = Y;}
else if(PRIMEP(X) != NIL){
res = ITER(fast_plus(fast_convert(X),fast_convert(fast_immediate(1))),fast_plus(fast_convert(Y),fast_convert(fast_immediate(1))));}
else{
res = ITER(fast_plus(fast_convert(X),fast_convert(fast_immediate(1))),Y);}
;res;});
if(CELLRANGE(Y)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
res = ITER(fast_immediate(2),fast_immediate(0));

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int TAU(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int LS,int M){
int res;
int temp1,temp2;
ITERloop:
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = M;}
else{
res = ITER(fast_convert(fast_cdr(LS)),fast_mult(fast_convert(fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(0))))))),Flist1(fast_inverse(fast_immediate(1))))))),fast_convert(fast_immediate(1)))),fast_convert(M)));}res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(1);}
else{
res = ITER(FACTORIZE(N),fast_immediate(1));}res;})
;

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int EXPT_1(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(ODDP(N) != NIL){
res = fast_immediate(-1);}
else{
res = fast_immediate(1);}res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int LIOUVILLE_LAMBDA(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = EXPT_1(OMEGA(N));
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int OMEGA(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(0);}
else{
res = SUM(({Fset_cdr(Fmakesym("dotslashexampleslashmath0"),Fcons(T,NIL));Fcar(Fmakesym("dotslashexampleslashmath0"));}),FACTORIZE(N));}res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int G(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = SUM(Fcar(Fmakesym("LIOUVILLE-LAMBDA")),DIVISORS(N));
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int SIGMA2(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int P = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(0)))))));int K = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(1)))))));res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(fast_minus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(P),Flist1(fast_inverse(fast_plus(fast_convert(K),fast_convert(fast_immediate(1))))))))),fast_convert(fast_immediate(1)))),Flist1(fast_inverse(fast_minus(fast_convert(P),fast_convert(fast_immediate(1))))))));res;});
res;})
;
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int SIGMA(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_smallerp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(1);}
else{
res = PRODUCT(Fcar(Fmakesym("SIGMA2")),FACTORIZE(N));}
;res;});
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int PERFECTP(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = fast_numeqp(fast_convert(SIGMA(N)),fast_convert(fast_mult(fast_convert(fast_immediate(2)),fast_convert(N))));
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int MERSENNE(int P){
int res;
if(CELLRANGE(P)) Fshelterpush(P);
if(Ffreecell() < 900) Fgbc();
res = fast_minus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(fast_immediate(2)),Flist1(fast_inverse(P)))))),fast_convert(fast_immediate(1)));
if(CELLRANGE(P)) Fshelterpop();
return(res);}
int DOUBLE_PERFECT_NUMBER_P(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = fast_numeqp(fast_convert(SIGMA(N)),fast_convert(fast_mult(fast_convert(fast_immediate(3)),fast_convert(N))));
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int FIND_DOUBLE_PERFECT(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int M,int LS){
int res;
int temp1,temp2;
ITERloop:
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(M),fast_convert(N)) != NIL){
res = LS;}
else if(DOUBLE_PERFECT_NUMBER_P(M) != NIL){
res = ITER(fast_plus(fast_convert(M),fast_convert(fast_immediate(1))),Fcons(fast_inverse(M),fast_inverse(LS)));}
else{
res = ITER(fast_plus(fast_convert(M),fast_convert(fast_immediate(1))),LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
return(res);}
res = ITER(fast_immediate(1),Fmakesym("NIL"));

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int FERMATP(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int M){
int res;
int temp1;
ITERloop:
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_smallerp(fast_convert(M),fast_convert(fast_immediate(1))) != NIL){
res = T;}
else if(fast_not(fast_numeqp(fast_convert(fast_immediate(1)),fast_convert(GAUSSMOD(fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("RANDOM")),Flist1(fast_inverse(fast_minus(fast_convert(N),fast_convert(fast_immediate(2)))))))),fast_convert(fast_immediate(1))),fast_minus(fast_convert(N),fast_convert(fast_immediate(1))),N)))) != NIL){
res = NIL;}
else{
res = ITER(fast_minus(fast_convert(M),fast_convert(fast_immediate(1))));}
;res;});
if(CELLRANGE(M)) Fshelterpop();
return(res);}
res = ITER(fast_immediate(10));

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int LUCASP(int P){
int res;
if(CELLRANGE(P)) Fshelterpush(P);
if(Ffreecell() < 900) Fgbc();
int ITER(int N,int I,int M){
int res;
int temp1,temp2,temp3;
ITERloop:
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(I)) Fshelterpush(I);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_numeqp(fast_convert(I),fast_convert(fast_minus(fast_convert(P),fast_convert(fast_immediate(1))))) && ZEROP(fast_mod(fast_convert(N),fast_convert(M)))) != NIL){
res = T;}
else if((fast_numeqp(fast_convert(I),fast_convert(fast_minus(fast_convert(P),fast_convert(fast_immediate(1))))) && fast_not(ZEROP(fast_mod(fast_convert(N),fast_convert(M))))) != NIL){
res = NIL;}
else{
res = ITER(fast_mod(fast_convert(fast_minus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(N),Flist1(fast_inverse(fast_immediate(2))))))),fast_convert(fast_immediate(2)))),fast_convert(M)),fast_plus(fast_convert(I),fast_convert(fast_immediate(1))),M);}
;res;});
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(I)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
res = ({int res=NIL;
if(fast_smallerp(fast_convert(P),fast_convert(fast_immediate(2))) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(P),fast_convert(fast_immediate(2))) != NIL){
res = T;}
else{
res = ITER(fast_immediate(4),fast_immediate(1),MERSENNE(P));}
;res;});

;
if(CELLRANGE(P)) Fshelterpop();
return(res);}
int FERMAT_NUMBER(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(fast_immediate(2)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(fast_immediate(2)),Flist1(fast_inverse(N))))))))))),fast_convert(fast_immediate(1)));
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int RM1(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int K,int Q){
int res;
int temp1,temp2;
ITERloop:
if(CELLRANGE(K)) Fshelterpush(K);
if(CELLRANGE(Q)) Fshelterpush(Q);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(ODDP(Q) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(K),Flist1(fast_inverse(Q)))));res;});}
else{
res = ITER(fast_plus(fast_convert(K),fast_convert(fast_immediate(1))),fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(Q),Flist1(fast_inverse(fast_immediate(2)))))));}res;})
;
if(CELLRANGE(Q)) Fshelterpop();
if(CELLRANGE(K)) Fshelterpop();
return(res);}
res = ITER(fast_immediate(0),fast_minus(fast_convert(N),fast_convert(fast_immediate(1))));

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int RM2(int A,int Q,int N){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(Q)) Fshelterpush(Q);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = fast_not(fast_numeqp(fast_convert(GAUSSMOD(A,Q,N)),fast_convert(fast_immediate(1))));
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(Q)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int RM3(int A,int K,int Q,int N){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(K)) Fshelterpush(K);
if(CELLRANGE(Q)) Fshelterpush(Q);
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int I){
int res;
int temp1;
ITERloop:
if(CELLRANGE(I)) Fshelterpush(I);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eqgreaterp(fast_convert(I),fast_convert(K)) != NIL){
res = T;}
else if(fast_numeqp(fast_convert(GAUSSMOD(A,fast_mult(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(fast_immediate(2)),Flist1(fast_inverse(I)))))),fast_convert(Q)),N)),fast_convert(fast_immediate(-1))) != NIL){
res = NIL;}
else{
res = ITER(fast_plus(fast_convert(I),fast_convert(fast_immediate(1))));}
;res;});
if(CELLRANGE(I)) Fshelterpop();
return(res);}
res = ITER(fast_immediate(0));

;
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(Q)) Fshelterpop();
if(CELLRANGE(K)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int RM4(int N,int A){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(A)) Fshelterpush(A);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int LS = fast_convert(RM1(N));int K = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(0)))))));int Q = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(LS),Flist1(fast_inverse(fast_immediate(1)))))));res = ({int res;
if((res = RM2(A,Q,N)) != NIL)
if((res=RM3(A,K,Q,N)) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
res;})
;
if(CELLRANGE(A)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int RABIN_MILLER_P(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int M){
int res;
int temp1;
ITERloop:
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_smallerp(fast_convert(M),fast_convert(fast_immediate(1))) != NIL){
res = NIL;}
else if(RM4(N,fast_plus(fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("RANDOM")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MIN")),Fcons(fast_inverse(fast_minus(fast_convert(N),fast_convert(fast_immediate(2)))),Flist1(fast_inverse(fast_immediate(32767))))))))))),fast_convert(fast_immediate(1)))) != NIL){
res = T;}
else{
res = ITER(fast_minus(fast_convert(M),fast_convert(fast_immediate(1))));}
;res;});
if(CELLRANGE(M)) Fshelterpop();
return(res);}
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(2))) != NIL){
res = T;}
else{
res = fast_not(ITER(fast_immediate(10)));}res;})
;

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int GAUSSMOD(int A,int K,int M){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(K)) Fshelterpush(K);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int K1 = fast_convert(EXPMOD(A,K,M));res = ({int res=NIL;
if((fast_greaterp(fast_convert(K1),fast_convert(fast_immediate(0))) && fast_greaterp(fast_convert(K1),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(M),Flist1(fast_inverse(fast_immediate(2)))))))) && fast_smallerp(fast_convert(K1),fast_convert(M))) != NIL){
res = fast_minus(fast_convert(K1),fast_convert(M));}
else if((fast_smallerp(fast_convert(K1),fast_convert(fast_immediate(0))) && fast_smallerp(fast_convert(K1),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(M),Flist1(fast_inverse(fast_immediate(2)))))))))))) && fast_greaterp(fast_convert(K1),fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(M))))))) != NIL){
res = fast_plus(fast_convert(K1),fast_convert(M));}
else{
res = K1;}
;res;});
res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(K)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int TWIN_PRIMES(int N,int M){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
int ITER(int I,int J,int LS){
int res;
int temp1,temp2,temp3;
ITERloop:
if(CELLRANGE(I)) Fshelterpush(I);
if(CELLRANGE(J)) Fshelterpush(J);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(I),fast_convert(J)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(LS))));res;});}
else if((PRIMEP(I) && PRIMEP(fast_plus(fast_convert(I),fast_convert(fast_immediate(2))))) != NIL){
res = ITER(fast_plus(fast_convert(I),fast_convert(fast_immediate(2))),J,Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(I),Flist1(fast_inverse(fast_plus(fast_convert(I),fast_convert(fast_immediate(2))))))))),fast_inverse(LS)));}
else{
res = ITER(fast_plus(fast_convert(I),fast_convert(fast_immediate(2))),J,LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(J)) Fshelterpop();
if(CELLRANGE(I)) Fshelterpop();
return(res);}
res = ({int res=NIL;
if(fast_eqsmallerp(fast_convert(N),fast_convert(fast_immediate(2))) != NIL){
res = ITER(fast_immediate(3),fast_plus(fast_convert(N),fast_convert(M)),Fmakesym("NIL"));}
else if(EVENP(N) != NIL){
res = ITER(fast_plus(fast_convert(N),fast_convert(fast_immediate(1))),fast_plus(fast_convert(N),fast_convert(M)),Fmakesym("NIL"));}
else{
res = ITER(N,fast_plus(fast_convert(N),fast_convert(M)),Fmakesym("NIL"));}
;res;});

;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int DIVISORS(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int M,int O,int LS){
int res;
int temp1,temp2,temp3;
ITERloop:
if(CELLRANGE(M)) Fshelterpush(M);
if(CELLRANGE(O)) Fshelterpush(O);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(M),fast_convert(O)) != NIL){
res = LS;}
else if(DIVISIBLEP(N,M) != NIL){
res = ITER(fast_plus(fast_convert(M),fast_convert(fast_immediate(1))),O,Fcons(fast_inverse(M),fast_inverse(LS)));}
else{
res = ITER(fast_plus(fast_convert(M),fast_convert(fast_immediate(1))),O,LS);}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(O)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
return(res);}
res = ({int res=NIL;
if(fast_not(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("INTEGERP")),Flist1(fast_inverse(N))));res;})) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("divisors require natural number")),Flist1(fast_inverse(N)))));res;});}
else if(fast_smallerp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("divisors require natural number")),Flist1(fast_inverse(N)))));res;});}
else if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = Fcons(Fmakeint(1),NIL);}
else{
res = Fcons(fast_inverse(N),fast_inverse(ITER(fast_immediate(1),fast_convert(Fcallsubr(Fcar(Fmakesym("CEILING")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("QUOTIENT")),Fcons(fast_inverse(N),Flist1(fast_inverse(fast_immediate(2)))))))))),Fmakesym("NIL"))));}
;res;});

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int PRIME_FACTORS(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int P,int X,int LS,int Z){
int res;
int temp1,temp2,temp3,temp4;
ITERloop:
if(CELLRANGE(P)) Fshelterpush(P);
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(Z)) Fshelterpush(Z);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(P),fast_convert(Z)) != NIL){
res = Fcons(fast_inverse(X),fast_inverse(LS));}
else if(fast_numeqp(fast_convert(fast_mod(fast_convert(X),fast_convert(P))),fast_convert(fast_immediate(0))) != NIL){
res = ({int res;int N1 = fast_convert(fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(X),Flist1(fast_inverse(P))))));res = ITER(fast_immediate(2),N1,Fcons(fast_inverse(P),fast_inverse(LS)),fast_convert(Fcallsubr(Fcar(Fmakesym("ISQRT")),Flist1(fast_inverse(N1)))));
res;})
;}
else if(fast_numeqp(fast_convert(P),fast_convert(fast_immediate(2))) != NIL){
res = ITER(fast_immediate(3),X,LS,Z);}
else{
res = ITER(fast_plus(fast_convert(P),fast_convert(fast_immediate(2))),X,LS,Z);}
;res;});
if(CELLRANGE(Z)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
if(CELLRANGE(P)) Fshelterpop();
return(res);}
res = ({int res=NIL;
if(fast_smallerp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = NIL;}
else if(fast_smallerp(fast_convert(N),fast_convert(fast_immediate(2))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(N))));res;});}
else{
res = ITER(fast_immediate(2),N,Fmakesym("NIL"),fast_convert(Fcallsubr(Fcar(Fmakesym("ISQRT")),Flist1(fast_inverse(N)))));}
;res;});

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int FACTORIZE(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
int ITER(int LS,int P,int N,int MULT){
int res;
int temp1,temp2,temp3,temp4;
ITERloop:
if(CELLRANGE(LS)) Fshelterpush(LS);
if(CELLRANGE(P)) Fshelterpush(P);
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(MULT)) Fshelterpush(MULT);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(P),Flist1(fast_inverse(N)))))),fast_inverse(MULT));}
else if(fast_numeqp(fast_convert(fast_convert(fast_car(LS))),fast_convert(P)) != NIL){
res = ITER(fast_convert(fast_cdr(LS)),P,fast_plus(fast_convert(N),fast_convert(fast_immediate(1))),MULT);}
else{
res = ITER(fast_convert(fast_cdr(LS)),fast_convert(fast_car(LS)),fast_immediate(1),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(P),Flist1(fast_inverse(N)))))),fast_inverse(MULT)));}
;res;});
if(CELLRANGE(MULT)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(P)) Fshelterpop();
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
res = ({int res;int LS = fast_convert(PRIME_FACTORS(N));res = ITER(fast_convert(fast_cdr(LS)),fast_convert(fast_car(LS)),fast_immediate(1),Fmakesym("NIL"));
res;})
;

;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int PHI(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = fast_immediate(1);}
else{
res = fast_convert(Fconvert(fast_inverse(fast_mult(fast_convert(N),fast_convert(PRODUCT(({Fset_cdr(Fmakesym("dotslashexampleslashmath1"),Fcons(T,NIL));Fcar(Fmakesym("dotslashexampleslashmath1"));}),FACTORIZE(N))))),Fmakesym("<INTEGER>")));}res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int PRIMITIVE_ROOT_P(int N,int P){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(P)) Fshelterpush(P);
if(Ffreecell() < 900) Fgbc();
int ITER(int I){
int res;
int temp1;
ITERloop:
if(CELLRANGE(I)) Fshelterpush(I);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eqgreaterp(fast_convert(I),fast_convert(fast_minus(fast_convert(P),fast_convert(fast_immediate(1))))) != NIL){
res = T;}
else if(fast_numeqp(fast_convert(EXPMOD(N,I,P)),fast_convert(fast_immediate(1))) != NIL){
res = NIL;}
else{
res = ITER(fast_plus(fast_convert(I),fast_convert(fast_immediate(1))));}
;res;});
if(CELLRANGE(I)) Fshelterpop();
return(res);}
res = ({int res;
if((res = ITER(fast_immediate(1))) != NIL)
if((res=fast_numeqp(fast_convert(EXPMOD(N,fast_minus(fast_convert(P),fast_convert(fast_immediate(1))),P)),fast_convert(fast_immediate(1)))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;

;
if(CELLRANGE(P)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int EXPMOD(int A,int N,int M){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(fast_immediate(0)),fast_convert(N)) != NIL){
res = fast_immediate(1);}
else if(EVENP(N) != NIL){
res = fast_mod(fast_convert(SQUARE(EXPMOD(A,fast_convert(Fcallsubr(Fcar(Fmakesym("DIV")),Fcons(fast_inverse(N),Flist1(fast_inverse(fast_immediate(2)))))),M))),fast_convert(M));}
else{
res = fast_mod(fast_convert(fast_mult(fast_convert(A),fast_convert(EXPMOD(A,fast_minus(fast_convert(N),fast_convert(fast_immediate(1))),M)))),fast_convert(M));}
;res;});
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int PRIMITIVE_ROOT(int P){
int res;
if(CELLRANGE(P)) Fshelterpush(P);
if(Ffreecell() < 900) Fgbc();
int ITER(int N){
int res;
int temp1;
ITERloop:
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(N),fast_convert(P)) != NIL){
res = NIL;}
else if(PRIMITIVE_ROOT_P(N,P) != NIL){
res = N;}
else{
res = ITER(fast_plus(fast_convert(N),fast_convert(fast_immediate(1))));}
;res;});
if(CELLRANGE(N)) Fshelterpop();
return(res);}
res = ITER(fast_immediate(2));

;
if(CELLRANGE(P)) Fshelterpop();
return(res);}
int IND(int R,int A,int P){
int res;
if(CELLRANGE(R)) Fshelterpush(R);
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(P)) Fshelterpush(P);
if(Ffreecell() < 900) Fgbc();
int ITER(int I){
int res;
int temp1;
ITERloop:
if(CELLRANGE(I)) Fshelterpush(I);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_greaterp(fast_convert(I),fast_convert(P)) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(EXPMOD(R,I,P)),fast_convert(A)) != NIL){
res = I;}
else{
res = ITER(fast_plus(fast_convert(I),fast_convert(fast_immediate(1))));}
;res;});
if(CELLRANGE(I)) Fshelterpop();
return(res);}
res = ITER(fast_immediate(0));

;
if(CELLRANGE(P)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
if(CELLRANGE(R)) Fshelterpop();
return(res);}
int HIGHLY_COMPOSITE_NUMBER_P(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eqsmallerp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = NIL;}
else if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = T;}
else{
res = fast_greaterp(fast_convert(TAU(N)),fast_convert(MAX_TAU(fast_minus(fast_convert(N),fast_convert(fast_immediate(1))),fast_immediate(0))));}
;res;});
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int MAX_TAU(int N,int M){
int res;
int temp1,temp2;
MAX_TAUloop:
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(M)) Fshelterpush(M);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int X = fast_convert(TAU(N));res = ({int res=NIL;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(1))) != NIL){
res = M;}
else if(fast_greaterp(fast_convert(X),fast_convert(M)) != NIL){
{
temp1 = fast_minus(fast_convert(N),fast_convert(fast_immediate(1)));
temp2 = X;
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
N = temp1;
M = temp2;
goto MAX_TAUloop;};}
else{
{
temp1 = fast_minus(fast_convert(N),fast_convert(fast_immediate(1)));
temp2 = M;
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(M)) Fshelterpop();
N = temp1;
M = temp2;
goto MAX_TAUloop;};}
;res;});
res;})
;
if(CELLRANGE(M)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int CADR(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = fast_convert(fast_car(fast_convert(fast_cdr(LS))));
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int CDDR(int LS){
int res;
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = NIL;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(fast_convert(fast_cdr(LS)))))) != NIL){
res = NIL;}
else{
res = fast_convert(fast_cdr(fast_convert(fast_cdr(LS))));}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int ARG1(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(1))))));res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int ARG2(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(2))))));res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int ARG3(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(3))))));res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int OP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(0))))));res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int SUBST(int OLD,int NEW,int F){
int res;
if(CELLRANGE(OLD)) Fshelterpush(OLD);
if(CELLRANGE(NEW)) Fshelterpush(NEW);
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))));res;}) != NIL){
res = Fmakesym("NIL");}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(fast_convert(fast_car(F))),Flist1(fast_inverse(OLD))))) != NIL){
res = Fcons(fast_inverse(NEW),fast_inverse(SUBST(OLD,NEW,fast_convert(fast_cdr(F)))));}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(fast_convert(fast_car(F)))))) != NIL){
res = Fcons(fast_inverse(fast_convert(fast_car(F))),fast_inverse(SUBST(OLD,NEW,fast_convert(fast_cdr(F)))));}
else{
res = Fcons(fast_inverse(SUBST(OLD,NEW,fast_convert(fast_car(F)))),fast_inverse(SUBST(OLD,NEW,fast_convert(fast_cdr(F)))));}
;res;});
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(NEW)) Fshelterpop();
if(CELLRANGE(OLD)) Fshelterpop();
return(res);}
int REMOVE(int X,int F){
int res;
int temp1,temp2;
REMOVEloop:
if(CELLRANGE(X)) Fshelterpush(X);
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))));res;}) != NIL){
res = Fmakesym("NIL");}
else if(fast_eq(fast_convert(fast_convert(fast_car(F))),fast_convert(X)) != NIL){
({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("REMOVE")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(fast_cdr(F)))))));res;});}
else{
res = Fcons(fast_inverse(fast_convert(fast_car(F))),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REMOVE")),Fcons(fast_inverse(X),Flist1(fast_inverse(fast_convert(fast_cdr(F)))))))));}
;res;});
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int OPCODE(int OP){
int res;
if(CELLRANGE(OP)) Fshelterpush(OP);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(Fmember(fast_inverse(OP),Fcons(Fmakesym("+"),NIL)) != NIL){
res = Fmakesym("+");}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("-"),NIL)) != NIL){
res = Fmakesym("-");}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("/"),NIL)) != NIL){
res = Fmakesym("/");}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("*"),NIL)) != NIL){
res = Fmakesym("*");}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("^"),NIL)) != NIL){
res = Fmakesym("^");}
else{
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SUBRP")),Flist1(fast_inverse(OP))));res;}) != NIL){
res = OP;}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ERROR")),Fcons(fast_inverse(Fmakestr("opecode else: ")),Flist1(fast_inverse(OP)))));res;});}res;})
;}
;res;});
if(CELLRANGE(OP)) Fshelterpop();
return(res);}
int WEIGHT(int OP){
int res;
if(CELLRANGE(OP)) Fshelterpush(OP);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(Fmember(fast_inverse(OP),Fcons(Fmakesym("+"),NIL)) != NIL){
res = fast_immediate(1);}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("-"),NIL)) != NIL){
res = fast_immediate(1);}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("/"),NIL)) != NIL){
res = fast_immediate(2);}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("*"),NIL)) != NIL){
res = fast_immediate(3);}
else if(Fmember(fast_inverse(OP),Fcons(Fmakesym("^"),NIL)) != NIL){
res = fast_immediate(4);}
else{
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("SUBRP")),Flist1(fast_inverse(OP))));res;}) != NIL){
res = fast_immediate(6);}
else{
res = fast_immediate(9);}res;})
;}
;res;});
if(CELLRANGE(OP)) Fshelterpop();
return(res);}
int INFIX_greaterPREFIX(int FMLA){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(Ffreecell() < 900) Fgbc();
res = INFIP(FMLA);
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int INFIP(int FMLA){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(FMLA))));res;}) != NIL){
res = FMLA;}
else{
res = INF1(FMLA,Fmakesym("NIL"),Fmakesym("NIL"));}res;})
;
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int INF1(int FMLA,int OPTR,int OPLN){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(OPTR)) Fshelterpush(OPTR);
if(CELLRANGE(OPLN)) Fshelterpush(OPLN);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((fast_smallerp(fast_convert(WEIGHT(OP(FMLA))),fast_convert(fast_immediate(5))) || fast_greaterp(fast_convert(WEIGHT(OP(FMLA))),fast_convert(fast_immediate(7)))) != NIL){
res = INF2(fast_convert(fast_cdr(FMLA)),OPTR,Fcons(fast_inverse(INFIP(fast_convert(fast_car(FMLA)))),fast_inverse(OPLN)));}
else{
res = INF3(CDDR(FMLA),OPTR,Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(OP(FMLA)),Flist1(fast_inverse(INFIP(ARG1(FMLA)))))))),fast_inverse(OPLN)));}res;})
;
if(CELLRANGE(OPLN)) Fshelterpop();
if(CELLRANGE(OPTR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int INF2(int FMLA,int OPTR,int OPLN){
int res;
int temp1,temp2,temp3;
INF2loop:
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(OPTR)) Fshelterpush(OPTR);
if(CELLRANGE(OPLN)) Fshelterpush(OPLN);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(FMLA)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(OPTR))))) != NIL){
res = fast_convert(fast_car(OPLN));}
else if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(FMLA))))) && (fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(OPTR)))) || fast_greaterp(fast_convert(WEIGHT(fast_convert(fast_car(FMLA)))),fast_convert(WEIGHT(fast_convert(fast_car(OPTR))))))) != NIL){
res = INF1(fast_convert(fast_cdr(FMLA)),Fcons(fast_inverse(fast_convert(fast_car(FMLA))),fast_inverse(OPTR)),OPLN);}
else{
{
temp1 = FMLA;
temp2 = fast_convert(fast_cdr(OPTR));
temp3 = Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(OPCODE(fast_convert(fast_car(OPTR)))),Fcons(fast_inverse(CADR(OPLN)),Flist1(fast_inverse(fast_convert(fast_car(OPLN))))))))),fast_inverse(CDDR(OPLN)));
if(CELLRANGE(FMLA)) Fshelterpop();
if(CELLRANGE(OPTR)) Fshelterpop();
if(CELLRANGE(OPLN)) Fshelterpop();
FMLA = temp1;
OPTR = temp2;
OPLN = temp3;
goto INF2loop;};}
;res;});
if(CELLRANGE(OPLN)) Fshelterpop();
if(CELLRANGE(OPTR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int INF3(int FMLA,int OPTR,int OPLN){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(OPTR)) Fshelterpush(OPTR);
if(CELLRANGE(OPLN)) Fshelterpush(OPLN);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(FMLA)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(OPLN))))) != NIL){
res = fast_convert(fast_car(OPLN));}
else if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(FMLA))))) && (Fapply(Fcar(Fmakesym("NULL?")),Flist1(fast_inverse(OPTR))) || fast_greaterp(fast_convert(WEIGHT(fast_convert(fast_car(FMLA)))),fast_convert(WEIGHT(CADR(FMLA)))))) != NIL){
res = INF1(fast_convert(fast_cdr(FMLA)),Fcons(fast_inverse(fast_convert(fast_car(FMLA))),fast_inverse(OPTR)),OPLN);}
else{
res = INF2(FMLA,OPTR,OPLN);}
;res;});
if(CELLRANGE(OPLN)) Fshelterpop();
if(CELLRANGE(OPTR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int PREFIX_greaterINFIX(int FMLA){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(FMLA))));res;}) != NIL){
res = FMLA;}
else{
res = PRETF(FMLA);}res;})
;
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int PRETF(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(WEIGHT(OP(F))),fast_convert(fast_immediate(6))) != NIL){
res = ({int res;int ARG = fast_convert(PRET1(ARG1(F),fast_immediate(-1)));res = ({int res;
if(Fapply(Fcar(Fmakesym("ATOM?")),Flist1(fast_inverse(ARG))) != NIL){
res = Fcons(fast_inverse(OP(F)),fast_inverse(ARG));}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(OP(F)),Flist1(fast_inverse(PRET1(ARG1(F),fast_immediate(-1)))))));res;});}res;})
;
res;})
;}
else{
res = PRET1(F,fast_immediate(-1));}res;})
;
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int PRET1(int F,int WIN){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(WIN)) Fshelterpush(WIN);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))));res;}) != NIL){
res = F;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(F)))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(F))));res;});}
else if((Fapply(Fcar(Fmakesym("EQ?")),Fcons(fast_inverse(OP(F)),Flist1(fast_inverse(Fmakesym("-"))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(ARG2(F)))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(fast_inverse(Fcons(Fmakesym("-"),NIL)),Flist1(fast_inverse(PRET2(ARG1(F),fast_immediate(1)))))));res;});}
else{
res = ({int res;int WF = fast_convert(WEIGHT(OP(F)));res = ({int res;
if(fast_smallerp(fast_convert(WF),fast_convert(WIN)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(PRET2(F,WF)))));res;});}
else{
res = PRET2(F,WF);}res;})
;
res;})
;}
;res;});
if(CELLRANGE(WIN)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int PRET2(int F,int WF){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(WF)) Fshelterpush(WF);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(fast_inverse(PRET1(ARG1(F),WF)),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(OP(F)))))),Flist1(fast_inverse(PRET1(ARG2(F),WF)))))));res;});
if(CELLRANGE(WF)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int slashNESTP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(F))))) != NIL)
if((res=fast_eq(fast_convert(OP(F)),fast_convert(Fmakesym("/")))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int plusNESTP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(F))))) != NIL)
if((res=fast_eq(fast_convert(OP(F)),fast_convert(Fmakesym("+")))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int starSIMP1(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(F))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(F))));res;});}
else if(fast_eq(fast_convert(OP(F)),fast_convert(Fmakesym("*"))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAN")),Fcons(fast_inverse(Fcar(Fmakesym("*SIMP1"))),Flist1(fast_inverse(fast_convert(fast_cdr(F)))))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(SIMPS(F)))));res;});}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int starSIMP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(Flength(F)),fast_convert(fast_immediate(3))) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(ARG1(F)),fast_convert(fast_immediate(0))) != NIL){
res = fast_immediate(0);}
else if(Fapply(Fcar(Fmakesym("EQ?")),Fcons(fast_inverse(ARG2(F)),Flist1(fast_inverse(fast_immediate(0))))) != NIL){
res = fast_immediate(0);}
else if(fast_eq(fast_convert(ARG1(F)),fast_convert(fast_immediate(1))) != NIL){
res = SIMPS(ARG2(F));}
else if(fast_eq(fast_convert(ARG2(F)),fast_convert(fast_immediate(1))) != NIL){
res = SIMPS(ARG1(F));}
else if(slashNESTP(ARG2(F)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(SIMPS(ARG1(F))),Flist1(fast_inverse(SIMPS(ARG1(ARG2(F)))))))))),Flist1(fast_inverse(SIMPS(ARG2(ARG2(F)))))))));res;});}
else if(fast_not(LAT(fast_convert(fast_cdr(F)))) != NIL){
res = Fcons(fast_inverse(Fmakesym("*")),fast_inverse(starSIMP1(F)));}
else if(fast_eq(fast_convert(ARG1(F)),fast_convert(ARG2(F))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(fast_immediate(2)))))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(SIMPS(ARG1(F))),Flist1(fast_inverse(SIMPS(ARG2(F))))))));res;});}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(fast_immediate(0)),Flist1(fast_inverse(fast_convert(fast_cdr(F))))))) != NIL){
res = fast_immediate(0);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(ARG2(F))))) && fast_eq(fast_convert(OP(ARG2(F))),fast_convert(Fmakesym("+")))) != NIL){
res = SIMPS(Fcons(fast_inverse(Fmakesym("+")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashmath2"),Fcons(F,Fcons(T,NIL)));Fcar(Fmakesym("dotslashexampleslashmath2"));})),Flist1(fast_inverse(fast_convert(fast_cdr(ARG2(F)))))))))));}
else if(fast_not(LAT(fast_convert(fast_cdr(F)))) != NIL){
res = Fcons(fast_inverse(Fmakesym("*")),fast_inverse(starSIMP1(F)));}
else{
res = Fcons(fast_inverse(Fmakesym("*")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("SIMPS"))),Flist1(fast_inverse(fast_convert(fast_cdr(F)))))))));}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int LAT(int LS){
int res;
int temp1;
LATloop:
if(CELLRANGE(LS)) Fshelterpush(LS);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(LS))));res;}) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(fast_convert(fast_car(LS)))))) != NIL){
{
temp1 = fast_convert(fast_cdr(LS));
if(CELLRANGE(LS)) Fshelterpop();
LS = temp1;
goto LATloop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(LS)) Fshelterpop();
return(res);}
int plusSIMP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(ARG1(F)),fast_convert(fast_immediate(0))) != NIL){
res = ({int res;
if(fast_numeqp(fast_convert(Flength(F)),fast_convert(fast_immediate(3))) != NIL){
res = ARG2(F);}
else{
res = SIMPS(Fcons(fast_inverse(Fmakesym("+")),fast_inverse(CDDR(F))));}res;})
;}
else if((fast_eq(fast_convert(ARG2(F)),fast_convert(fast_immediate(0))) && fast_numeqp(fast_convert(Flength(F)),fast_convert(fast_immediate(3)))) != NIL){
res = SIMPS(ARG1(F));}
else if(fast_eq(fast_convert(ARG1(F)),fast_convert(ARG2(F))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_immediate(2)),Flist1(fast_inverse(SIMPS(ARG1(F))))))));res;});}
else{
res = Fcons(fast_inverse(Fmakesym("+")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("SIMPS"))),Flist1(fast_inverse(fast_convert(fast_cdr(F)))))))));}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int _SIMP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_numeqp(fast_convert(Flength(F)),fast_convert(fast_immediate(2))) != NIL){
res = ({int res=NIL;
if(plusNESTP(ARG1(F)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("+")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(SIMPS(ARG1(ARG1(F)))))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(SIMPS(ARG2(ARG1(F)))))))))))))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(SIMPS(ARG1(F))))))));res;});}
;res;});}
else if(fast_numeqp(fast_convert(Flength(F)),fast_convert(fast_immediate(3))) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(ARG1(F)),fast_convert(ARG2(F))) != NIL){
res = fast_immediate(0);}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("+")),Fcons(fast_inverse(SIMPS(ARG1(F))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(SIMPS(ARG2(F))))))))))))));res;});}
;res;});}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int slashSIMP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(ARG1(F)),fast_convert(ARG2(F))) != NIL){
res = fast_immediate(1);}
else if(fast_eq(fast_convert(ARG1(F)),fast_convert(fast_immediate(0))) != NIL){
res = fast_immediate(0);}
else if(fast_eq(fast_convert(ARG2(F)),fast_convert(Fmakesym("NIL"))) != NIL){
res = fast_immediate(0);}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG2(F))))) != NIL){
res = SIMPS(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fapply(Fcar(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(ARG2(F)))))),Flist1(fast_inverse(ARG1(F))))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("LISTP")),Flist1(fast_inverse(ARG2(F))))) && fast_numeqp(fast_convert(Flength(ARG2(F))),fast_convert(fast_immediate(3))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG1(ARG2(F)))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(ARG2(ARG2(F))))))) != NIL){
res = ({int res;int CDF = fast_convert(ARG2(F));res = ({int res;
if(fast_numeqp(fast_convert(Flength(CDDR(CDF))),fast_convert(fast_immediate(1))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(SIMPS(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fapply(Fcar(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(ARG1(CDF)))))),Flist1(fast_inverse(ARG1(F))))))))),Flist1(fast_inverse(ARG2(CDF)))))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(SIMPS(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fapply(Fcar(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(ARG1(CDF)))))),Flist1(fast_inverse(ARG1(F))))))))),Flist1(fast_inverse(SIMPS(Fcons(fast_inverse(fast_convert(fast_car(CDF))),fast_inverse(CDDR(CDF))))))))));res;});}res;})
;
res;})
;}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(SIMPS(ARG1(F))),Flist1(fast_inverse(SIMPS(ARG2(F))))))));res;});}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int hatSIMP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(fast_eq(fast_convert(ARG2(F)),fast_convert(fast_immediate(0))) != NIL){
res = fast_immediate(1);}
else if(fast_eq(fast_convert(ARG2(F)),fast_convert(fast_immediate(1))) != NIL){
res = ARG1(F);}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(OP(F)),Fcons(fast_inverse(SIMPS(ARG1(F))),Flist1(fast_inverse(SIMPS(ARG2(F))))))));res;});}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int SIN_SIMP(int F){
int res;
int temp1;
SIN_SIMPloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && Fapply(Fcar(Fmakesym("EQ?")),Fcons(fast_inverse(OP(ARG1(F))),Flist1(fast_inverse(Fmakesym("*"))))) && fast_eq(fast_convert(ARG1(ARG1(F))),fast_convert(Fmakesym("I")))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fmakesym("I")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SINH")),Flist1(fast_inverse(ARG2(ARG1(F)))))))))))));res;});}
else if((Fapply(Fcar(Fmakesym("NUMBER?")),Flist1(fast_inverse(ARG1(F)))) && fast_numeqp(fast_convert(ARG1(F)),fast_convert(fast_immediate(0)))) != NIL){
res = fast_immediate(0);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("0.5");}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/2"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = fast_immediate(1);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("2/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("3/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("5/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("0.5");}
else if(fast_eq(fast_convert(ARG1(F)),fast_convert(Fmakesym("PI"))) != NIL){
res = fast_immediate(0);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("7/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("-0.5");}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("5/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("4/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("3/2"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = fast_immediate(-1);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("4/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("7/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("11/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("-0.5");}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakeint(2),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = fast_immediate(0);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_eq(fast_convert(OP(ARG1(F))),fast_convert(Fmakesym("*"))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG1(ARG1(F)))))) && fast_greaterp(fast_convert(ARG1(ARG1(F))),fast_convert(fast_immediate(2))) && fast_eq(fast_convert(ARG2(ARG1(F))),fast_convert(Fmakesym("PI")))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_minus(fast_convert(ARG1(ARG1(F))),fast_convert(fast_immediate(2)))),Flist1(fast_inverse(Fmakesym("PI"))))))))))));
if(CELLRANGE(F)) Fshelterpop();
F = temp1;
goto SIN_SIMPloop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(ARG1(F))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(ARG1(F))))));res;});}
else{
res = ({int res;int ARG = fast_convert(SIMPS(ARG1(F)));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(ARG1(F))))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(ARG)))));res;});}
else{
res = COS_SIMP(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(SIMPS(ARG1(F))))))));}res;})
;
res;})
;}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int COS_SIMP(int F){
int res;
int temp1;
COS_SIMPloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((Fapply(Fcar(Fmakesym("NUMBER?")),Flist1(fast_inverse(ARG1(F)))) && fast_numeqp(fast_convert(ARG1(F)),fast_convert(fast_immediate(0)))) != NIL){
res = fast_immediate(1);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("0.5");}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("1/2"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = fast_immediate(0);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("2/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("-0.5");}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("3/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("5/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if(fast_eq(fast_convert(ARG1(F)),fast_convert(Fmakesym("PI"))) != NIL){
res = fast_immediate(-1);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("7/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("5/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("4/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("-0.5");}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("3/2"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = fast_immediate(0);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("4/3"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fmakestrflt("0.5");}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("7/4"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(2),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakesym("11/6"),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),Fcons(Fmakeint(2),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakeint(2),Fcons(Fmakesym("PI"),NIL))))))))) != NIL){
res = fast_immediate(1);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && Fapply(Fcar(Fmakesym("EQ?")),Fcons(fast_inverse(OP(ARG1(F))),Flist1(fast_inverse(Fmakesym("*"))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG1(ARG1(F)))))) && fast_greaterp(fast_convert(ARG1(ARG1(F))),fast_convert(fast_immediate(2))) && Fapply(Fcar(Fmakesym("EQ?")),Fcons(fast_inverse(ARG2(ARG1(F))),Flist1(fast_inverse(Fmakesym("PI")))))) != NIL){
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_minus(fast_convert(ARG1(ARG1(F))),fast_convert(fast_immediate(2)))),Flist1(fast_inverse(Fmakesym("PI"))))))))))));
if(CELLRANGE(F)) Fshelterpop();
F = temp1;
goto COS_SIMPloop;};}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(ARG1(F))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(ARG1(F))))));res;});}
else{
res = ({int res;int ARG = fast_convert(SIMPS(ARG1(F)));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(ARG1(F))))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(ARG)))));res;});}
else{
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(SIMPS(ARG1(F)))))));
if(CELLRANGE(F)) Fshelterpop();
F = temp1;
goto COS_SIMPloop;};}res;})
;
res;})
;}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int ATAN_SIMP(int F){
int res;
int temp1;
ATAN_SIMPloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG1(F))))) && fast_numeqp(fast_convert(ARG1(F)),fast_convert(fast_immediate(1)))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fmakesym("PI"),Fcons(Fmakeint(4),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("/"),Fcons(Fmakeint(1),Fcons(Fmakesym("SQRT"),Fcons(Fcons(Fmakeint(3),NIL),NIL)))))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fmakesym("PI"),Fcons(Fmakeint(6),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)))))))) != NIL){
res = Fcons(Fmakesym("/"),Fcons(Fmakesym("PI"),Fcons(Fmakeint(3),NIL)));}
else if((Fapply(Fcar(Fmakesym("NUMBER?")),Flist1(fast_inverse(ARG1(F)))) && fast_numeqp(fast_convert(ARG1(F)),fast_convert(fast_immediate(-1)))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fmakesym("PI"),Fcons(Fmakeint(4),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fmakeint(1),Fcons(Fmakesym("SQRT"),Fcons(Fcons(Fmakeint(3),NIL),NIL)))),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fmakesym("PI"),Fcons(Fmakeint(6),NIL))),NIL)));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fmakeint(3),NIL)),NIL))))))))) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fcons(Fmakesym("/"),Fcons(Fmakesym("PI"),Fcons(Fmakeint(3),NIL))),NIL)));}
else{
res = ({int res;int ARG = fast_convert(SIMPS(ARG1(F)));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(ARG),Flist1(fast_inverse(ARG1(F))))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("ATAN")),Flist1(fast_inverse(ARG)))));res;});}
else{
{
temp1 = fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("ATAN")),Flist1(fast_inverse(SIMPS(ARG1(F)))))));
if(CELLRANGE(F)) Fshelterpop();
F = temp1;
goto ATAN_SIMPloop;};}res;})
;
res;})
;}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int SINH_SIMP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(ARG1(F))))) && fast_eq(fast_convert(OP(ARG1(F))),fast_convert(Fmakesym("*"))) && fast_eq(fast_convert(ARG1(ARG1(F))),fast_convert(Fmakesym("I")))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fmakesym("I")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Flist1(fast_inverse(Fapply(Fcar(Fmakesym("(QUOTE SIN)")),Flist1(fast_inverse(ARG2(ARG1(F)))))))))))))));res;});}
else{
res = F;}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int exclamationSIMP(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_eqgreaterp(fast_convert(ARG1(F)),fast_convert(fast_immediate(0))) != NIL){
res = FACTORIAL(ARG1(F));}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(FACTORIAL(fast_convert(Fcallsubr(Fcar(Fmakesym("ABS")),Flist1(fast_inverse(ARG1(F))))))))));res;});}res;})
;
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int FACTORIAL(int N){
int res;
if(CELLRANGE(N)) Fshelterpush(N);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = fast_immediate(1);}
else{
res = fast_mult(fast_convert(N),fast_convert(FACTORIAL(fast_minus(fast_convert(N),fast_convert(fast_immediate(1))))));}res;})
;
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int SIMPS(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(Fapply(Fcar(Fmakesym("ATOM?")),Flist1(fast_inverse(F))) != NIL){
res = F;}
else{
res = ({int res;
if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("+"),NIL)) != NIL){
res = plusSIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("-"),NIL)) != NIL){
res = _SIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("*"),NIL)) != NIL){
res = starSIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("/"),NIL)) != NIL){
res = slashSIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("^"),NIL)) != NIL){
res = hatSIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("SIN"),NIL)) != NIL){
res = SIN_SIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("COS"),NIL)) != NIL){
res = COS_SIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("ATAN"),NIL)) != NIL){
res = ATAN_SIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("SINH"),NIL)) != NIL){
res = SINH_SIMP(F);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("!"),NIL)) != NIL){
res = exclamationSIMP(F);}
else{
res = F;}
;res;});}res;})
;
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int SIMPF(int FF){
int res;
int temp1;
SIMPFloop:
if(CELLRANGE(FF)) Fshelterpush(FF);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int FS = fast_convert(SIMPS(FF));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(FF),Flist1(fast_inverse(FS)))));res;}) != NIL){
res = FF;}
else{
{
temp1 = FS;
if(CELLRANGE(FF)) Fshelterpop();
FF = temp1;
goto SIMPFloop;};}res;})
;
res;})
;
if(CELLRANGE(FF)) Fshelterpop();
return(res);}
int starCOMNUM(int F,int NUMB,int SYMB,int IMAG){
int res;
int temp1,temp2,temp3,temp4;
starCOMNUMloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(NUMB)) Fshelterpush(NUMB);
if(CELLRANGE(SYMB)) Fshelterpush(SYMB);
if(CELLRANGE(IMAG)) Fshelterpush(IMAG);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))));res;}) != NIL){
res = ({int res;int N = fast_convert(starNUMB(NUMB));int I = fast_convert(starIMAG(IMAG));res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(N)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(I))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(SYMB))));res;});}
else if((fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(N))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(I))))) != NIL){
res = Fcons(fast_inverse(N),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(SYMB))))));}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(N)))) && fast_not(fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(I)))))) != NIL){
res = Fcons(fast_inverse(I),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(SYMB))))));}
else{
res = ({int res;
if(Fapply(Fcar(Fmakesym("ATOMP")),Flist1(fast_inverse(I))) != NIL){
res = Fcons(fast_inverse(I),fast_inverse(Fcons(fast_inverse(N),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(SYMB))))))));}
else{
res = Fcons(fast_inverse(Fmakesym("I")),fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("-")),Flist1(fast_inverse(N))))),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(SYMB))))))));}res;})
;}
;res;});
res;})
;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(fast_convert(fast_car(F)))))) != NIL){
{
temp1 = fast_convert(fast_cdr(F));
temp2 = Fcons(fast_inverse(fast_convert(fast_car(F))),fast_inverse(NUMB));
temp3 = SYMB;
temp4 = IMAG;
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(NUMB)) Fshelterpop();
if(CELLRANGE(SYMB)) Fshelterpop();
if(CELLRANGE(IMAG)) Fshelterpop();
F = temp1;
NUMB = temp2;
SYMB = temp3;
IMAG = temp4;
goto starCOMNUMloop;};}
else if(fast_eq(fast_convert(fast_convert(fast_car(F))),fast_convert(Fmakesym("I"))) != NIL){
{
temp1 = fast_convert(fast_cdr(F));
temp2 = NUMB;
temp3 = SYMB;
temp4 = Fcons(fast_inverse(fast_convert(fast_car(F))),fast_inverse(IMAG));
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(NUMB)) Fshelterpop();
if(CELLRANGE(SYMB)) Fshelterpop();
if(CELLRANGE(IMAG)) Fshelterpop();
F = temp1;
NUMB = temp2;
SYMB = temp3;
IMAG = temp4;
goto starCOMNUMloop;};}
else{
{
temp1 = fast_convert(fast_cdr(F));
temp2 = NUMB;
temp3 = Fcons(fast_inverse(fast_convert(fast_car(F))),fast_inverse(SYMB));
temp4 = IMAG;
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(NUMB)) Fshelterpop();
if(CELLRANGE(SYMB)) Fshelterpop();
if(CELLRANGE(IMAG)) Fshelterpop();
F = temp1;
NUMB = temp2;
SYMB = temp3;
IMAG = temp4;
goto starCOMNUMloop;};}
;res;});
if(CELLRANGE(IMAG)) Fshelterpop();
if(CELLRANGE(SYMB)) Fshelterpop();
if(CELLRANGE(NUMB)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int starNUMB(int S){
int res;
if(CELLRANGE(S)) Fshelterpush(S);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(S))));res;}) != NIL){
res = Fmakesym("NIL");}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(Fcons(fast_inverse(Fmakesym("*")),fast_inverse(S))))));res;});}res;})
;
if(CELLRANGE(S)) Fshelterpop();
return(res);}
int starIMAG(int S){
int res;
if(CELLRANGE(S)) Fshelterpush(S);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(S))));res;}) != NIL){
res = Fmakesym("NIL");}
else{
res = ({int res;
if(Fmember(fast_inverse(fast_mod(fast_convert(Flength(S)),fast_convert(fast_immediate(4)))),Fcons(Fmakeint(1),NIL)) != NIL){
res = Fmakesym("I");}
else if(Fmember(fast_inverse(fast_mod(fast_convert(Flength(S)),fast_convert(fast_immediate(4)))),Fcons(Fmakeint(2),NIL)) != NIL){
res = fast_immediate(-1);}
else if(Fmember(fast_inverse(fast_mod(fast_convert(Flength(S)),fast_convert(fast_immediate(4)))),Fcons(Fmakeint(3),NIL)) != NIL){
res = Fcons(Fmakesym("*"),Fcons(Fmakeint(-1),Fcons(Fmakesym("I"),NIL)));}
else if(Fmember(fast_inverse(fast_mod(fast_convert(Flength(S)),fast_convert(fast_immediate(4)))),Fcons(Fmakeint(0),NIL)) != NIL){
res = fast_immediate(1);}
;res;});}res;})
;
if(CELLRANGE(S)) Fshelterpop();
return(res);}
int plusCOMNUM(int F,int NUMB,int SYMB){
int res;
int temp1,temp2,temp3;
plusCOMNUMloop:
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(NUMB)) Fshelterpush(NUMB);
if(CELLRANGE(SYMB)) Fshelterpush(SYMB);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))));res;}) != NIL){
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(NUMB))));res;}) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(SYMB))));res;});}
else if(fast_eq(fast_convert(Flength(NUMB)),fast_convert(fast_immediate(1))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("APPEND")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(SYMB))))),Flist1(fast_inverse(NUMB)))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("REVERSE")),Flist1(fast_inverse(Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("EVAL")),Flist1(fast_inverse(Fcons(fast_inverse(Fmakesym("+")),fast_inverse(NUMB))))))),fast_inverse(SYMB))))));res;});}
;res;});}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(fast_convert(fast_car(F)))))) != NIL){
{
temp1 = fast_convert(fast_cdr(F));
temp2 = Fcons(fast_inverse(fast_convert(fast_car(F))),fast_inverse(NUMB));
temp3 = SYMB;
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(NUMB)) Fshelterpop();
if(CELLRANGE(SYMB)) Fshelterpop();
F = temp1;
NUMB = temp2;
SYMB = temp3;
goto plusCOMNUMloop;};}
else{
{
temp1 = fast_convert(fast_cdr(F));
temp2 = NUMB;
temp3 = Fcons(fast_inverse(fast_convert(fast_car(F))),fast_inverse(SYMB));
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(NUMB)) Fshelterpop();
if(CELLRANGE(SYMB)) Fshelterpop();
F = temp1;
NUMB = temp2;
SYMB = temp3;
goto plusCOMNUMloop;};}
;res;});
if(CELLRANGE(SYMB)) Fshelterpop();
if(CELLRANGE(NUMB)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int COMNUM(int F){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))));res;}) != NIL){
res = Fmakesym("NIL");}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(F)))) != NIL){
res = F;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(OP(F))))) && fast_eq(fast_convert(Flength(F)),fast_convert(fast_immediate(2)))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(OP(F)),Flist1(fast_inverse(COMNUM(ARG1(F)))))));res;});}
else if((fast_eq(fast_convert(OP(F)),fast_convert(Fmakesym("^"))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG1(F))))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NUMBERP")),Flist1(fast_inverse(ARG2(F)))))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EXPT")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(ARG2(F))))));res;});}
else if(fast_eq(fast_convert(OP(F)),fast_convert(Fmakesym("*"))) != NIL){
res = ({int res;int ANS = fast_convert(starCOMNUM(fast_convert(fast_cdr(F)),Fmakesym("NIL"),Fmakesym("NIL"),Fmakesym("NIL")));res = ({int res=NIL;
if(fast_eq(fast_convert(Flength(ANS)),fast_convert(fast_immediate(1))) != NIL){
res = fast_convert(fast_car(ANS));}
else if(LAT(ANS) != NIL){
res = Fcons(fast_inverse(Fmakesym("*")),fast_inverse(ANS));}
else{
res = Fcons(fast_inverse(Fmakesym("*")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("COMNUM"))),Flist1(fast_inverse(ANS)))))));}
;res;});
res;})
;}
else if(fast_eq(fast_convert(OP(F)),fast_convert(Fmakesym("+"))) != NIL){
res = ({int res;int ANS = fast_convert(plusCOMNUM(fast_convert(fast_cdr(F)),Fmakesym("NIL"),Fmakesym("NIL")));res = ({int res=NIL;
if(fast_eq(fast_convert(Flength(ANS)),fast_convert(fast_immediate(1))) != NIL){
res = fast_convert(fast_car(ANS));}
else if(LAT(ANS) != NIL){
res = Fcons(fast_inverse(Fmakesym("+")),fast_inverse(ANS));}
else{
res = Fcons(fast_inverse(Fmakesym("+")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(Fcar(Fmakesym("COMNUM"))),Flist1(fast_inverse(ANS)))))));}
;res;});
res;})
;}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(OP(F)),Fcons(fast_inverse(COMNUM(ARG1(F))),Flist1(fast_inverse(COMNUM(ARG2(F))))))));res;});}
;res;});
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int SIMPC(int FF){
int res;
int temp1;
SIMPCloop:
if(CELLRANGE(FF)) Fshelterpush(FF);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int FC = fast_convert(COMNUM(FF));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(FF),Flist1(fast_inverse(FC)))));res;}) != NIL){
res = FF;}
else{
{
temp1 = FC;
if(CELLRANGE(FF)) Fshelterpop();
FF = temp1;
goto SIMPCloop;};}res;})
;
res;})
;
if(CELLRANGE(FF)) Fshelterpop();
return(res);}
int SIMPL(int FF){
int res;
if(CELLRANGE(FF)) Fshelterpush(FF);
if(Ffreecell() < 900) Fgbc();
res = SIMPC(SIMPF(FF));
if(CELLRANGE(FF)) Fshelterpop();
return(res);}
int starAUX(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(Fapply(Fcar(Fmakesym("NULL?")),Flist1(fast_inverse(F))) != NIL){
res = Fmakesym("NIL");}
else{
res = Fcons(fast_inverse(Fcons(fast_inverse(DERIVE(fast_convert(fast_car(F)),VAR)),fast_inverse(fast_convert(fast_cdr(F))))),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashmath3"),Fcons(F,Fcons(T,NIL)));Fcar(Fmakesym("dotslashexampleslashmath3"));})),Flist1(fast_inverse(starAUX(fast_convert(fast_cdr(F)),VAR))))))));}res;})
;
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int starDERIV(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = Fcons(fast_inverse(Fmakesym("+")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashmath4"),Fcons(T,NIL));Fcar(Fmakesym("dotslashexampleslashmath4"));})),Flist1(fast_inverse(starAUX(fast_convert(fast_cdr(FMLA)),VAR))))))));
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int slashDERIV(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("-")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(DERIVE(ARG1(FMLA),VAR)),Flist1(fast_inverse(ARG2(FMLA)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(ARG1(FMLA)),Flist1(fast_inverse(DERIVE(ARG2(FMLA),VAR)))))))))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(ARG2(FMLA)),Flist1(fast_inverse(fast_immediate(2)))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int plusDERIV(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = Fcons(fast_inverse(Fmakesym("+")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashmath5"),Fcons(VAR,Fcons(T,NIL)));Fcar(Fmakesym("dotslashexampleslashmath5"));})),Flist1(fast_inverse(fast_convert(fast_cdr(FMLA)))))))));
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int _DERIV(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = Fcons(fast_inverse(Fmakesym("-")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("MAPCAR")),Fcons(fast_inverse(({Fset_cdr(Fmakesym("dotslashexampleslashmath6"),Fcons(VAR,Fcons(T,NIL)));Fcar(Fmakesym("dotslashexampleslashmath6"));})),Flist1(fast_inverse(fast_convert(fast_cdr(FMLA)))))))));
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int DERIVE(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(FMLA))));res;}) != NIL){
res = ({int res;
if(fast_eq(fast_convert(FMLA),fast_convert(VAR)) != NIL){
res = fast_immediate(1);}
else{
res = fast_immediate(0);}res;})
;}
else if(FREE(FMLA,VAR) != NIL){
res = fast_immediate(0);}
else{
res = ({int res;
if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("+"),NIL)) != NIL){
res = plusDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("-"),NIL)) != NIL){
res = _DERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("*"),NIL)) != NIL){
res = starDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("/"),NIL)) != NIL){
res = slashDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("^"),NIL)) != NIL){
res = hatDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("SIN"),NIL)) != NIL){
res = SDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("COS"),NIL)) != NIL){
res = CDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("TAN"),NIL)) != NIL){
res = TDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("ASIN"),NIL)) != NIL){
res = ASDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("ACOS"),NIL)) != NIL){
res = ACDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("ATAN"),NIL)) != NIL){
res = ATDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("LOG"),NIL)) != NIL){
res = LOGDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("SINH"),NIL)) != NIL){
res = SHDERIV(FMLA,VAR);}
else if(Fmember(fast_inverse(OP(FMLA)),Fcons(Fmakesym("COSH"),NIL)) != NIL){
res = CHDERIV(FMLA,VAR);}
else{
res = Fmakestr("Undefined");}
;res;});}
;res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int SDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(ARG1(F))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int CDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(ARG1(F))))))))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int TDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(ARG1(F))))))),Flist1(fast_inverse(fast_immediate(2)))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int ASDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(Fcons(Fmakesym("SQRT"),Fcons(Fcons(Fmakesym("-"),Fcons(Fmakeint(1),Fcons(Fcons(Fmakesym("^"),Fcons(Fmakesym("X"),Fcons(Fmakeint(2),NIL))),NIL))),NIL))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int ACDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(Fcons(Fmakesym("SQRT"),Fcons(Fcons(Fmakesym("-"),Fcons(Fmakeint(1),Fcons(Fcons(Fmakesym("^"),Fcons(Fmakesym("X"),Fcons(Fmakeint(2),NIL))),NIL))),NIL))))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int ATDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(Fcons(Fmakesym("+"),Fcons(Fmakeint(1),Fcons(Fcons(Fmakesym("^"),Fcons(Fmakesym("X"),Fcons(Fmakeint(2),NIL))),NIL)))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int LOGDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(ARG1(F)))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int SHDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COSH")),Flist1(fast_inverse(ARG1(F))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int CHDERIV(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(DERIVE(ARG1(F),VAR)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SINH")),Flist1(fast_inverse(ARG1(F))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int hatDERIV(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((DEPEND(FMLA,VAR) && FREE(ARG2(FMLA),VAR)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(ARG2(FMLA)),Flist1(fast_inverse(DERIVE(ARG1(FMLA),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(ARG1(FMLA)),Flist1(fast_inverse(fast_minus(fast_convert(ARG2(FMLA)),fast_convert(fast_immediate(1)))))))))))))));res;});}
else if((DEPEND(FMLA,VAR) && FREE(ARG1(FMLA),VAR)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(DERIVE(ARG2(FMLA),VAR)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(Fmakesym("E")),Flist1(fast_inverse(ARG2(FMLA)))))))))))));res;});}
else{
res = Fapply(Fcar(Fmakesym("^DAUX")),Fcons(fast_inverse(FMLA),Flist1(fast_inverse(VAR))));}
;res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int DEPEND(int FMLA,int VAR){
int res;
int temp1,temp2;
DEPENDloop:
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ATOM")),Flist1(fast_inverse(FMLA))));res;}) != NIL){
res = ({int res;
if(fast_eq(fast_convert(FMLA),fast_convert(VAR)) != NIL){
res = T;}
else{
res = NIL;}res;})
;}
else if(fast_eq(fast_convert(Flength(FMLA)),fast_convert(fast_immediate(2))) != NIL){
{
temp1 = ARG1(FMLA);
temp2 = VAR;
if(CELLRANGE(FMLA)) Fshelterpop();
if(CELLRANGE(VAR)) Fshelterpop();
FMLA = temp1;
VAR = temp2;
goto DEPENDloop;};}
else if(fast_eq(fast_convert(Flength(FMLA)),fast_convert(fast_immediate(3))) != NIL){
res = ({int res;
if((res=DEPEND(ARG1(FMLA),VAR)) == NIL)
if((res=DEPEND(ARG2(FMLA),VAR)) !=NIL)
res=res;
else res=NIL;
else res=res;res;})
;}
else if(DEPEND(CDDR(FMLA),VAR) != NIL){
res = T;}
else{
res = NIL;}
;res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int FREE(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = fast_not(DEPEND(FMLA,VAR));
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int NDERIVE(int N,int FMLA,int VAR){
int res;
int temp1,temp2,temp3;
NDERIVEloop:
if(CELLRANGE(N)) Fshelterpush(N);
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(fast_numeqp(fast_convert(N),fast_convert(fast_immediate(0))) != NIL){
res = SIMPL(FMLA);}
else{
{
temp1 = fast_minus(fast_convert(N),fast_convert(fast_immediate(1)));
temp2 = SIMPL(DERIVE(FMLA,VAR));
temp3 = VAR;
if(CELLRANGE(N)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
if(CELLRANGE(VAR)) Fshelterpop();
N = temp1;
FMLA = temp2;
VAR = temp3;
goto NDERIVEloop;};}res;})
;
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
if(CELLRANGE(N)) Fshelterpop();
return(res);}
int DIF2(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = SIMPL(NDERIVE(fast_immediate(2),FMLA,VAR));
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int DIFF(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = PREFIX_greaterINFIX(DIF(INFIX_greaterPREFIX(FMLA),VAR));
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int DIF(int FMLA,int VAR){
int res;
if(CELLRANGE(FMLA)) Fshelterpush(FMLA);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = SIMPL(DERIVE(FMLA,VAR));
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FMLA)) Fshelterpop();
return(res);}
int SINT(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(DERIVE(ARG1(F),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(ARG1(F))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int CINT(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(DERIVE(ARG1(F),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(ARG1(F))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int TINT(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(-1)),Flist1(fast_inverse(DERIVE(ARG1(F),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LOG")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("COS")),Flist1(fast_inverse(ARG1(F)))))))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int CTINT(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(DERIVE(ARG1(F),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LOG")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SIN")),Flist1(fast_inverse(ARG1(F)))))))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int LINT(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(DERIVE(ARG1(F),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("-")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(VAR),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LOG")),Flist1(fast_inverse(ARG1(F))))))))))))),Flist1(fast_inverse(VAR))))))))))));res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int hatINT(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((MLIN(ARG1(F),VAR) && FREE(ARG2(F),VAR)) != NIL){
res = ({int res=NIL;
if(fast_eq(fast_convert(ARG2(F)),fast_convert(fast_immediate(-1))) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(DERIVE(ARG1(F),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LOG")),Flist1(fast_inverse(ARG1(F))))))))))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_plus(fast_convert(ARG2(F)),fast_convert(fast_immediate(1)))),Flist1(fast_inverse(DERIVE(ARG1(F),VAR)))))))))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(fast_plus(fast_convert(ARG2(F)),fast_convert(fast_immediate(1)))))))))))))));res;});}
;res;});}
else if((fast_eq(fast_convert(ARG1(F)),fast_convert(Fmakesym("E"))) && MLIN(ARG2(F),VAR)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(DERIVE(ARG2(F),VAR)))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(Fmakesym("E")),Flist1(fast_inverse(ARG2(F)))))))))))));res;});}
else{
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Flist1(fast_inverse(DERIVE(ARG2(F),VAR))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LOG")),Flist1(fast_inverse(ARG1(F))))))))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("-")),Fcons(fast_inverse(ARG1(F)),Flist1(fast_inverse(ARG2(F)))))))))))))))))));res;});}
;res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int MLIN(int FF,int VAR){
int res;
if(CELLRANGE(FF)) Fshelterpush(FF);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((DEPEND(FF,VAR) && FREE(SIMPL(DERIVE(FF,VAR)),VAR)) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(FF)) Fshelterpop();
return(res);}
int INTF(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if(FREE(F,VAR) != NIL){
res = Fcons(fast_inverse(Fmakesym("*")),fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(F),Flist1(fast_inverse(VAR)))))));}
else if(fast_eq(fast_convert(F),fast_convert(VAR)) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(Fapply(Fcar(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(fast_immediate(2)))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("^")),Fcons(fast_inverse(F),Flist1(fast_inverse(fast_immediate(2)))))))))))));res;});}
else{
res = ({int res;
if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("SIN"),NIL)) != NIL){
res = SINT(F,VAR);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("COS"),NIL)) != NIL){
res = CINT(F,VAR);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("TAN"),NIL)) != NIL){
res = TINT(F,VAR);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("COT"),NIL)) != NIL){
res = CTINT(F,VAR);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("LOG"),NIL)) != NIL){
res = LINT(F,VAR);}
else if(Fmember(fast_inverse(OP(F)),Fcons(Fmakesym("^"),NIL)) != NIL){
res = hatINT(F,VAR);}
else{
res = ({int res=NIL;
if(MATCHF(Fcons(Fmakesym("/"),Fcons(Fmakeint(1),Fcons(Fmakesym("X"),NIL))),F,VAR) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("LOG")),Flist1(fast_inverse(ARG1(F))))));res;});}
else if(MATCHF(Fcons(Fmakesym("/"),Fcons(Fmakeint(1),Fcons(Fcons(Fmakesym("+"),Fcons(Fcons(Fmakesym("^"),Fcons(Fmakesym("X"),Fcons(Fmakeint(2),NIL))),Fcons(Fmakesym("?C"),NIL))),NIL))),F,VAR) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Fcons(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(fast_immediate(1)),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SQRT")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("?C"))))))))))))))),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("ATAN")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(VAR),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SQRT")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("?C")))))))))))))))))))))))));res;});}
else if(MATCHF(Fcons(Fmakesym("/"),Fcons(Fmakeint(1),Fcons(Fcons(Fmakesym("SQRT"),Fcons(Fcons(Fmakesym("-"),Fcons(Fmakesym("?C"),Fcons(Fcons(Fmakesym("^"),Fcons(Fmakesym("X"),Fcons(Fmakeint(2),NIL))),NIL))),NIL)),NIL))),F,VAR) != NIL){
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("*")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("ASIN")),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("/")),Fcons(fast_inverse(VAR),Flist1(fast_inverse(fast_convert(Fcallsubr(Fcar(Fmakesym("LIST")),Fcons(fast_inverse(Fmakesym("SQRT")),Flist1(fast_inverse(fast_convert(Fcdr(Fmakesym("?C"))))))))))))))))))))))));res;});}
;res;});}
;res;});}
;res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int INTL(int F,int VAR){
int res;
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;int FI = fast_convert(SIMPL(INTF(F,VAR)));res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(FI),Flist1(fast_inverse(F)))));res;}) != NIL){
res = F;}
else{
res = SIMPL(FI);}res;})
;
res;})
;
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
return(res);}
int VARP(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((res = fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(X))))) != NIL)
if((res=fast_convert(Fcallsubr(Fcar(Fmakesym("CHAR=")),Fcons(fast_inverse(CHARACTER(X)),Flist1(fast_inverse(Fmakechar("?"))))))) !=NIL)
res=res;
else res=NIL;
else res=NIL;res;})
;
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int CHARACTER(int X){
int res;
if(CELLRANGE(X)) Fshelterpush(X);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("ELT")),Fcons(fast_inverse(fast_convert(Fconvert(fast_inverse(X),Fmakesym("<STRING>")))),Flist1(fast_inverse(fast_immediate(0))))));res;});
if(CELLRANGE(X)) Fshelterpop();
return(res);}
int MEMBERP(int A,int B){
int res;
if(CELLRANGE(A)) Fshelterpush(A);
if(CELLRANGE(B)) Fshelterpush(B);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if(({int res;
 res=fast_convert(Fcallsubr(Fcar(Fmakesym("MEMBER")),Fcons(fast_inverse(A),Flist1(fast_inverse(B)))));res;}) != NIL){
res = T;}
else{
res = NIL;}res;})
;
if(CELLRANGE(B)) Fshelterpop();
if(CELLRANGE(A)) Fshelterpop();
return(res);}
int MATCHF1(int P,int F,int VAR){
int res;
if(CELLRANGE(P)) Fshelterpush(P);
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res;
if((MATCHF2(ARG1(P),ARG1(F),VAR) && MATCHF2(ARG2(P),ARG2(F),VAR)) != NIL){
res = T;}
else{
res = ({int res;
if((MEMBERP(OP(P),Fcons(Fmakesym("+"),Fcons(Fmakesym("*"),NIL))) && MATCHF2(ARG2(P),ARG1(F),VAR) && MATCHF2(ARG1(P),ARG2(F),VAR)) != NIL){
res = T;}
else{
res = NIL;}res;})
;}res;})
;
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(P)) Fshelterpop();
return(res);}
int MATCHF2(int P,int F,int VAR){
int res;
int temp1,temp2,temp3;
MATCHF2loop:
if(CELLRANGE(P)) Fshelterpush(P);
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
res = ({int res=NIL;
if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(P)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))))) != NIL){
res = T;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(P)))) || fast_convert(Fcallsubr(Fcar(Fmakesym("NULL")),Flist1(fast_inverse(F))))) != NIL){
res = T;}
else if(fast_convert(Fcallsubr(Fcar(Fmakesym("EQUAL")),Fcons(fast_inverse(P),Flist1(fast_inverse(F))))) != NIL){
res = T;}
else if(VARP(P) != NIL){
res = ({int res;
 res = Fset_cdr(Fmakesym("?C"),fast_inverse(F));res;});
res = T;}
else if((fast_eq(fast_convert(F),fast_convert(VAR)) && fast_convert(Fcallsubr(Fcar(Fmakesym("SYMBOLP")),Flist1(fast_inverse(P))))) != NIL){
res = T;}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(P)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(F)))) && fast_eq(fast_convert(OP(P)),fast_convert(OP(F))) && fast_numeqp(fast_convert(Flength(F)),fast_convert(fast_immediate(3)))) != NIL){
res = MATCHF1(P,F,VAR);}
else if((fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(P)))) && fast_convert(Fcallsubr(Fcar(Fmakesym("CONSP")),Flist1(fast_inverse(F)))) && fast_eq(fast_convert(OP(P)),fast_convert(OP(F))) && fast_numeqp(fast_convert(Flength(F)),fast_convert(fast_immediate(2)))) != NIL){
{
temp1 = ARG1(P);
temp2 = ARG1(F);
temp3 = VAR;
if(CELLRANGE(P)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(VAR)) Fshelterpop();
P = temp1;
F = temp2;
VAR = temp3;
goto MATCHF2loop;};}
else{
res = NIL;}
;res;});
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(P)) Fshelterpop();
return(res);}
int MATCHF(int P,int F,int VAR){
int res;
if(CELLRANGE(P)) Fshelterpush(P);
if(CELLRANGE(F)) Fshelterpush(F);
if(CELLRANGE(VAR)) Fshelterpush(VAR);
if(Ffreecell() < 900) Fgbc();
({int res;
 res = Fset_cdr(Fmakesym("?C"),fast_inverse(Fmakesym("NIL")));res;});
res = MATCHF2(P,F,VAR);
if(CELLRANGE(VAR)) Fshelterpop();
if(CELLRANGE(F)) Fshelterpop();
if(CELLRANGE(P)) Fshelterpop();
return(res);}
void init_tfunctions(void){
(deftfunc)("ODDP" , f_ODDP);
(deftfunc)("EVENP" , f_EVENP);
(deftfunc)("ZEROP" , f_ZEROP);
(deftfunc)("SQUARE" , f_SQUARE);
(deftfunc)("SET-AREF1" , f_SET_AREF1);
(deftfunc)("AREF1" , f_AREF1);
(deftfunc)("MULT-SCALAR-MAT" , f_MULT_SCALAR_MAT);
(deftfunc)("MATRIX-IDENT" , f_MATRIX_IDENT);
(deftfunc)("SQUARE-MATRIX-P" , f_SQUARE_MATRIX_P);
(deftfunc)("TR" , f_TR);
(deftfunc)("SUB-MATRIX" , f_SUB_MATRIX);
(deftfunc)("DET" , f_DET);
(deftfunc)("DET1" , f_DET1);
(deftfunc)("SIGN" , f_SIGN);
(deftfunc)("TRANSPOSE" , f_TRANSPOSE);
(deftfunc)("INV" , f_INV);
(deftfunc)("INV0" , f_INV0);
(deftfunc)("INV1" , f_INV1);
(deftfunc)("INV2" , f_INV2);
(deftfunc)("SUM" , f_SUM);
(deftfunc)("PRODUCT" , f_PRODUCT);
(deftfunc)("FOR-ALL" , f_FOR_ALL);
(deftfunc)("AT-LEAST" , f_AT_LEAST);
(deftfunc)("GAUSS-PRIMES" , f_GAUSS_PRIMES);
(deftfunc)("COPRIMEP" , f_COPRIMEP);
(deftfunc)("DIVISIBLEP" , f_DIVISIBLEP);
(deftfunc)("EQMODP" , f_EQMODP);
(deftfunc)("PRIMEP" , f_PRIMEP);
(deftfunc)("DETERMINISTIC-PRIME-P" , f_DETERMINISTIC_PRIME_P);
(deftfunc)("PRIMEPI" , f_PRIMEPI);
(deftfunc)("TAU" , f_TAU);
(deftfunc)("EXPT-1" , f_EXPT_1);
(deftfunc)("LIOUVILLE-LAMBDA" , f_LIOUVILLE_LAMBDA);
(deftfunc)("dotslashexampleslashmath0" , f_dotslashexampleslashmath0);
(deftfunc)("OMEGA" , f_OMEGA);
(deftfunc)("G" , f_G);
(deftfunc)("SIGMA2" , f_SIGMA2);
(deftfunc)("SIGMA" , f_SIGMA);
(deftfunc)("PERFECTP" , f_PERFECTP);
(deftfunc)("MERSENNE" , f_MERSENNE);
(deftfunc)("DOUBLE-PERFECT-NUMBER-P" , f_DOUBLE_PERFECT_NUMBER_P);
(deftfunc)("FIND-DOUBLE-PERFECT" , f_FIND_DOUBLE_PERFECT);
(deftfunc)("FERMATP" , f_FERMATP);
(deftfunc)("LUCASP" , f_LUCASP);
(deftfunc)("FERMAT-NUMBER" , f_FERMAT_NUMBER);
(deftfunc)("RM1" , f_RM1);
(deftfunc)("RM2" , f_RM2);
(deftfunc)("RM3" , f_RM3);
(deftfunc)("RM4" , f_RM4);
(deftfunc)("RABIN-MILLER-P" , f_RABIN_MILLER_P);
(deftfunc)("GAUSSMOD" , f_GAUSSMOD);
(deftfunc)("TWIN-PRIMES" , f_TWIN_PRIMES);
(deftfunc)("DIVISORS" , f_DIVISORS);
(deftfunc)("PRIME-FACTORS" , f_PRIME_FACTORS);
(deftfunc)("FACTORIZE" , f_FACTORIZE);
(deftfunc)("dotslashexampleslashmath1" , f_dotslashexampleslashmath1);
(deftfunc)("PHI" , f_PHI);
(deftfunc)("PRIMITIVE-ROOT-P" , f_PRIMITIVE_ROOT_P);
(deftfunc)("EXPMOD" , f_EXPMOD);
(deftfunc)("PRIMITIVE-ROOT" , f_PRIMITIVE_ROOT);
(deftfunc)("IND" , f_IND);
(deftfunc)("HIGHLY-COMPOSITE-NUMBER-P" , f_HIGHLY_COMPOSITE_NUMBER_P);
(deftfunc)("MAX-TAU" , f_MAX_TAU);
(deftfunc)("CADR" , f_CADR);
(deftfunc)("CDDR" , f_CDDR);
(deftfunc)("ARG1" , f_ARG1);
(deftfunc)("ARG2" , f_ARG2);
(deftfunc)("ARG3" , f_ARG3);
(deftfunc)("OP" , f_OP);
(deftfunc)("SUBST" , f_SUBST);
(deftfunc)("REMOVE" , f_REMOVE);
(deftfunc)("OPCODE" , f_OPCODE);
(deftfunc)("WEIGHT" , f_WEIGHT);
(deftfunc)("INFIX->PREFIX" , f_INFIX_greaterPREFIX);
(deftfunc)("INFIP" , f_INFIP);
(deftfunc)("INF1" , f_INF1);
(deftfunc)("INF2" , f_INF2);
(deftfunc)("INF3" , f_INF3);
(deftfunc)("PREFIX->INFIX" , f_PREFIX_greaterINFIX);
(deftfunc)("PRETF" , f_PRETF);
(deftfunc)("PRET1" , f_PRET1);
(deftfunc)("PRET2" , f_PRET2);
(deftfunc)("/NESTP" , f_slashNESTP);
(deftfunc)("+NESTP" , f_plusNESTP);
(deftfunc)("*SIMP1" , f_starSIMP1);
(deftfunc)("dotslashexampleslashmath2" , f_dotslashexampleslashmath2);
(deftfunc)("*SIMP" , f_starSIMP);
(deftfunc)("LAT" , f_LAT);
(deftfunc)("+SIMP" , f_plusSIMP);
(deftfunc)("-SIMP" , f__SIMP);
(deftfunc)("/SIMP" , f_slashSIMP);
(deftfunc)("^SIMP" , f_hatSIMP);
(deftfunc)("SIN-SIMP" , f_SIN_SIMP);
(deftfunc)("COS-SIMP" , f_COS_SIMP);
(deftfunc)("ATAN-SIMP" , f_ATAN_SIMP);
(deftfunc)("SINH-SIMP" , f_SINH_SIMP);
(deftfunc)("!SIMP" , f_exclamationSIMP);
(deftfunc)("FACTORIAL" , f_FACTORIAL);
(deftfunc)("SIMPS" , f_SIMPS);
(deftfunc)("SIMPF" , f_SIMPF);
(deftfunc)("*COMNUM" , f_starCOMNUM);
(deftfunc)("*NUMB" , f_starNUMB);
(deftfunc)("*IMAG" , f_starIMAG);
(deftfunc)("+COMNUM" , f_plusCOMNUM);
(deftfunc)("COMNUM" , f_COMNUM);
(deftfunc)("SIMPC" , f_SIMPC);
(deftfunc)("SIMPL" , f_SIMPL);
(deftfunc)("dotslashexampleslashmath3" , f_dotslashexampleslashmath3);
(deftfunc)("*AUX" , f_starAUX);
(deftfunc)("dotslashexampleslashmath4" , f_dotslashexampleslashmath4);
(deftfunc)("*DERIV" , f_starDERIV);
(deftfunc)("/DERIV" , f_slashDERIV);
(deftfunc)("dotslashexampleslashmath5" , f_dotslashexampleslashmath5);
(deftfunc)("+DERIV" , f_plusDERIV);
(deftfunc)("dotslashexampleslashmath6" , f_dotslashexampleslashmath6);
(deftfunc)("-DERIV" , f__DERIV);
(deftfunc)("DERIVE" , f_DERIVE);
(deftfunc)("SDERIV" , f_SDERIV);
(deftfunc)("CDERIV" , f_CDERIV);
(deftfunc)("TDERIV" , f_TDERIV);
(deftfunc)("ASDERIV" , f_ASDERIV);
(deftfunc)("ACDERIV" , f_ACDERIV);
(deftfunc)("ATDERIV" , f_ATDERIV);
(deftfunc)("LOGDERIV" , f_LOGDERIV);
(deftfunc)("SHDERIV" , f_SHDERIV);
(deftfunc)("CHDERIV" , f_CHDERIV);
(deftfunc)("^DERIV" , f_hatDERIV);
(deftfunc)("DEPEND" , f_DEPEND);
(deftfunc)("FREE" , f_FREE);
(deftfunc)("NDERIVE" , f_NDERIVE);
(deftfunc)("DIF2" , f_DIF2);
(deftfunc)("DIFF" , f_DIFF);
(deftfunc)("DIF" , f_DIF);
(deftfunc)("SINT" , f_SINT);
(deftfunc)("CINT" , f_CINT);
(deftfunc)("TINT" , f_TINT);
(deftfunc)("CTINT" , f_CTINT);
(deftfunc)("LINT" , f_LINT);
(deftfunc)("^INT" , f_hatINT);
(deftfunc)("MLIN" , f_MLIN);
(deftfunc)("INTF" , f_INTF);
(deftfunc)("INTL" , f_INTL);
(deftfunc)("VARP" , f_VARP);
(deftfunc)("CHARACTER" , f_CHARACTER);
(deftfunc)("MEMBERP" , f_MEMBERP);
(deftfunc)("MATCHF1" , f_MATCHF1);
(deftfunc)("MATCHF2" , f_MATCHF2);
(deftfunc)("MATCHF" , f_MATCHF);
}void init_declare(void){
Fsetcatchsymbols(NIL);Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("WHEN"),Fcons(Fcons(Fmakesym("TEST"),Fcons(Fmakesym(":REST"),Fcons(Fmakesym("BODY"),NIL))),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("TEST"),NIL)),Fcons(Fcons(Fmakesym("PROGN"),Fcons(Fcons(Fmakesym("UNQUOTE-SPLICING"),Fcons(Fmakesym("BODY"),NIL)),NIL)),NIL))),NIL)),NIL)))));
Feval(Fcons(Fmakesym("DEFMACRO"),Fcons(Fmakesym("UNLESS"),Fcons(Fcons(Fmakesym("TEST"),Fcons(Fmakesym(":REST"),Fcons(Fmakesym("BODY"),NIL))),Fcons(Fcons(Fmakesym("QUASI-QUOTE"),Fcons(Fcons(Fmakesym("IF"),Fcons(Fcons(Fmakesym("NOT"),Fcons(Fcons(Fmakesym("UNQUOTE"),Fcons(Fmakesym("TEST"),NIL)),NIL)),Fcons(Fcons(Fmakesym("PROGN"),Fcons(Fcons(Fmakesym("UNQUOTE-SPLICING"),Fcons(Fmakesym("BODY"),NIL)),NIL)),NIL))),NIL)),NIL)))));
Fset_cdr(Fmakesym("*E*"),Fmakestrflt("2.718281828459045"));Fset_opt(Fmakesym("*E*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("*GAMMA*"),Fmakestrflt("0.5772156649015329"));Fset_opt(Fmakesym("*GAMMA*"),FAST_GLOBAL);
Fset_cdr(Fmakesym("?C"),Fmakesym("NIL"));Fset_opt(Fmakesym("?C"),FAST_GLOBAL);
}