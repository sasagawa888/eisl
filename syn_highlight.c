#include <string.h>
#include <stdbool.h>
#include "term.h"

#define NELEM(X) (sizeof(X) / sizeof((X)[0]))

// special form token. use in Edlis indentation
static const char *special[] = {
    "defun", "defmacro", "defglobal", "defdynamic", "defconstant",
    "let", "let*", "plet", "case", "while", "progn", "defmodule",
};

// syntax token
static const char *syntax[] = {
    "lambda", "labels", "flet", "let", "let*", "setq", "setf",
    "defconstant", "defun", "defmacro", "defglobal", "defdynamic",
    "dynamic", "set-dynamic", "function", "function*", "symbol-function",
    "class",
    "and", "or", "if", "cond", "while", "for", "block", "return-from",
    "case", "case-using", "progn", "defclass", "defgeneric", "defgeneric*",
    "defmethod", "dynamic-let", "ignore-errors", "catch", "throw",
    "tagbody", "go", "unwind-protect", "with-standard-input",
    "with-standard-output", "with-error-output", "with-handler",
    "convert", "with-open-input-file", "with-open-output-file",
    "with-open-io-file", "the", "assure", "time", "trace", "untrace",
    "defmodule", "defpublic", "modulesubst",
};

// builtin token
static const char *builtin[] = {
    "-", "*", "/=", "+", "<", "<=", "=", ">", ">=",
    "abs", "append", "apply", "aref", "arithmetic-error-operands",
    "arithmetic-error-operation", "array-dimensions", "assoc", "atan",
    "atan2", "atanh", "atom", "basic-array-p", "basic-array*-p",
    "basic-vector-p", "call-next-method", "car", "cdr", "ceiling",
    "cerror", "char-index", "char/=", "char<", "char<=", "char=",
    "char>", "char>=", "characterp", "class-of", "close",
    "condition-continuable", "cons", "consp", "continue-condition",
    "cos", "cosh", "create-array", "create-list",
    "create-string-input-stream",
    "create-string-output-stream", "create-string", "create-vector",
    "create",
    "div", "domain-error-object", "domain-error-expected-class",
    "dummyp", "elt", "eq", "eql", "equal", "error-output", "error",
    "eval", "exp", "expt", "file-length", "file-position", "finish-output",
    "float", "floatp", "floor", "format-char", "format-fresh-line",
    "format-float", "format-integer", "format-object", "format-tab",
    "format",
    "funcall", "functionp", "garef", "gbc", "gcd", "general-array*-p",
    "general-vector-p", "generic-function-p", "gensym",
    "get-internal-real-time",
    "get-internal-run-time",
    "get-output-stream-string", "get-universal-time", "identity",
    "initialize-object*", "input-stream-p", "instancep", "integerp",
    "internal-time-units-per-second", "isqrt", "lcm", "length", "list",
    "listp", "load", "log", "map-into", "mapc", "mapcar", "mapcan",
    "mapcon", "mapl", "maplist", "max", "member", "min", "mod",
    "next-method-p", "not", "nreverse", "null", "numberp",
    "open-input-file", "open-io-file", "open-output-file", "open-stream-p",
    "output-stream-p", "parse-error-string", "parse-error-expected-class",
    "parse-number", "preview-char", "prin1", "print", "probe-file",
    "property", "quit", "quotient", "read-byte", "read-char", "read-line",
    "read", "reciprocal", "remove-property", "reverse", "round",
    "set-aref",
    "set-car", "set-cdr", "set-elt", "set-file-position", "set-garef",
    "set-property", "signal-condition", "simple-error-format-argument",
    "simple-error-format-string", "sin", "sinh", "slot-value", "sqrt",
    "standard-input", "standard-output", "stream-error-stream", "streamp",
    "stream-ready-p", "string-append", "string-index", "string/=",
    "string<", "string<=", "string=", "string>", "string>=", "stringp",
    "subclassp",
    "subseq", "symbolp", "tan", "tanh", "truncate",
    "undefined-entity-name",
    "undefined-entity-namespace", "vector", "write-byte", "import",
};

// extended function
static const char *extended[] = {
    "random-real", "random", "set-random", "heapdump", "instance",
    "nconc", "fast-address", "macroexpand-1", "macroexpand-all",
    "backtrace", "subrp", "funcp", "macrop", "fixnump", "longnump",
    "bignump", "prof", "create-server-socket", "create-client-socket",
    "send-socket", "recv-socket", "close-socket",
    "break", "edit", "set-editor", "wiringpi-setup-gpio",
    "delay-microseconds", "wiringpi-spi-setup", "digital-write-byte",
    "wiringpi-spi-setup-ch-speed", "pwm-set-mode", "pwm-set-range",
    "pwm-set-clock", "pin-mode", "digital-write", "digital-read",
    "pwm-write", "pull-up-dn-control", "delay-seconds", "compile-file",
    "formatter", "line-argument", "getenv", "system",
    "c-include", "c-define", "c-lang", "c-option", "try", "read_exp",
    "mt-create", "mt-let", "mt-call", "mt-exec", "mt-lock", "mt-close",
    "mp-create", "mp-exec", "mp-close", "mp-call", "mp-and", "mp-or",
    "mp-report", "mp-eval", "dp-setid", "dp-senderr", "dp-and", "dp-or",
    "dp-create", "dp-let", "dp-close", "dp-eval", "dp-transfer", "dp-halt",
    "dp-load", "dp-compile", "dp-call", "dp-exec", "dp-trace", "dp_untrace", 
    "gpio-init", "gpio-set-mode", "gpio-write", "gpio-read", "gpio-event-request",
    "gpio-event-wait", "gpio-event-read", "gpio-close",
};

static bool in_syntax_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(syntax); i++) {
	if (strcmp(syntax[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

static bool in_builtin_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(builtin); i++) {
	if (strcmp(builtin[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

static bool in_extended_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(extended); i++) {
	if (strcmp(extended[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

bool in_special_table(const char *str)
{
    int i;

    for (i = 0; i < (int) NELEM(special); i++) {
	if (strcmp(special[i], str) == 0) {
	    return true;
	}
    }
    return false;
}

enum HighlightToken maybe_match(const char *str)
{
    if (in_syntax_table(str)) {
	return HIGHLIGHT_SYNTAX;
    }
    if (in_builtin_table(str)) {
	return HIGHLIGHT_BUILTIN;
    }
    if (in_extended_table(str)) {
	return HIGHLIGHT_EXTENDED;
    }
    return HIGHLIGHT_NONE;
}

void
gather_fuzzy_matches(const char *str, const char *candidates[],
		     int *candidate_pt)
{
    int i;

    for (i = 0; i < (int) NELEM(syntax); i++) {
	if (strstr(syntax[i], str) != NULL && syntax[i][0] == str[0]) {
	    candidates[*candidate_pt] = syntax[i];
	    *candidate_pt = (*candidate_pt) + 1;
	}
    }
    for (i = 0; i < (int) NELEM(builtin); i++) {
	if (strstr(builtin[i], str) != NULL && builtin[i][0] == str[0]) {
	    candidates[*candidate_pt] = builtin[i];
	    *candidate_pt = (*candidate_pt) + 1;
	}
    }
    for (i = 0; i < (int) NELEM(extended); i++) {
	if (strstr(extended[i], str) != NULL && extended[i][0] == str[0]) {
	    candidates[*candidate_pt] = extended[i];
	    *candidate_pt = (*candidate_pt) + 1;
	}
    }
}
