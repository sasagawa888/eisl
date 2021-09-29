/*
 * Common definitions for the interpreter and compiler 
 */

#ifndef FFI_H
#define FFI_H

#define CELLSIZE 20000000
static const int NIL = 0;
static const int T = 2;
static const int SMALL_INT_MAX = 1000000000;
static const int SMALL_INT_MIN = -1000000000;
static const int INT_FLAG = 1073741824;	// #b01000000_00000000_00000000_00000000
static const int INT_MASK = 1073741823;	// #b00111111_11111111_11111111_11111111
static inline bool
CELLRANGE(int x)
{
    return (x < CELLSIZE && x >= 0);
}

enum Option {
    CONSTN = 1,
    IMMUTABLE,
    SYSTEM,			// class of provided by system
    USER,			// class of user' definition
    GLOBAL,			// global variable
    CONTINUABLE,		// continuable condition
    NOTCONT,			// no continuable condition
    ABSTRACT,			// abstract class

    // *** WARNING: THE FOLLOWING ARE INTERNAL VALUES THAT CLIENTS SHOULD
    // NOT USE ***
    AROUND, BEFORE, PRIORITY, AFTER, EISL_OPEN, EISL_INPUT, EISL_OUTPUT,
    EISL_INSTR, EISL_OUTSTR, EISL_CLOSESTR,
};

typedef int     (*fn0)(void);
typedef int     (*fn1)(int);
typedef int     (*fn2)(int, int);
typedef int     (*fn3)(char *);
typedef long long int (*fn4)(int);
typedef int     (*fn5)(int, int, int);
typedef char   *(*fn6)(int);
typedef double  (*fn7)(int);
typedef int     (*fn8)(double);
typedef void    (*tfunc)(const char *, int(*func)(int));

enum { CHECKGBC_IDX, GBC_IDX, FRESHCELL_IDX, FREECELL_IDX,
    GBCSW_IDX, GETWP_IDX, ARGPOP_IDX, SHELTERPOP_IDX,
    POP_IDX, GETDYNPT_IDX, NUM_FN0S
};
enum { CAR_IDX, CDR_IDX, CADR_IDX, CADDR_IDX,
    CAAR_IDX, CADAR_IDX, LIST1_IDX, EVAL_IDX,
    AUX_IDX, LENGTH_IDX, SUBRP_IDX, FSUBRP_IDX,
    FUNCTIONP_IDX, MACROP_IDX, INTEGERP_IDX, LONGNUMP_IDX,
    BIGNUMP_IDX, GETINT_IDX, MAKEINT_IDX, MAKEINTLONG_IDX,
    VECTOR_IDX, FASTCAR_IDX, FASTCDR_IDX, FINDENV_IDX,
    FINDDYN_IDX, ARGPUSH_IDX, SHELTERPUSH_IDX, PUSH_IDX,
    GETOPT_IDX, GETPROP_IDX, SETDYNPT_IDX, SETCATCHSYMBOLS_IDX,
    NUM_FN1S
};
enum { CONS_IDX, NTH_IDX, SETCAR_IDX, SETCDR_IDX,
    SETAUX_IDX, SETOPT_IDX, CALLSUBR_IDX, LIST2_IDX,
    NTHCDR_IDX, APPLY_IDX, PLUS_IDX, MINUS_IDX,
    MULT_IDX, QUOTIENT_IDX, REMAINDER_IDX, DIVIDE_IDX,
    EQP_IDX, EQLP_IDX, NUMEQP_IDX, SMALLERP_IDX,
    EQSMALLERP_IDX, GREATERP_IDX, EQGREATERP_IDX, MEMBER_IDX,
    CONVERT_IDX, ARRAY_IDX, SETDYNENV_IDX, ADDDYNENV_IDX,
    SETDYNAMIC_IDX, SETPROP_IDX, ADAPTP_IDX, NUM_FN2S
};
enum { MAKESTR_IDX, MAKESYM_IDX, MAKECHAR_IDX, MAKESTRFLT_IDX,
    MAKEBIG_IDX, MAKESTRLONG_IDX, MAKEFASTSTRLONG_IDX, NUM_FN3S
};
enum { GETLONG_IDX, NUM_FN4S };
enum { STRINGSET_IDX, ARRAYSET_IDX, MEMBER1_IDX, NUM_FN5S };
enum { GETNAME_IDX, NUM_FN6S };
enum { GETFLT_IDX, NUM_FN7S };
enum { MAKEDOUBLEFLT_IDX, NUM_FN8S };

#endif
