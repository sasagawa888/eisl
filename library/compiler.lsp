;;FAST compiler ver5.00
#|
(defun xxx (x1 x2 ...) (foo1 x)(foo2 x2) ...)
#include "fast.h"
code0 prototype
code1 int f_xxx(int arglist){xxx(x1,x2,...,th)} th is thread number
code2 int xxx(int x1, int x2 ... , int th)
code3 void init_tfunctions(void){
(deftfunc)("XXX" ,(int)f_XXX);
}
code4 ex (defglobal abc 1)
void declare(){signal(SIGINT, signal_handler_c);
               Fset_cdr(makesym("abc"),makeint(1));
               Fset_opt(makesym("abc"),GLOBAL)};
init_deftfunc{
deftfunc("XXX",f_xxx);
}
code5,6,7 for lambda-form ex(lambda (x) x)
f_gensym(int x){
int res;
res = x;
return(res);
}
type inference code
example (tarai x y z) x,y,z = <fixnum>
code0 prototype
int f_tarai(int x, int y, int z)
code1
int f_tarai(int x, int y, int z){
    return(F_makeint(tarai(F_getint(x),F_getint(y),F_getint(z))));
}
code2
int tarai(int x, int y, int z){
    if(x <= y)
        return(y);
    else
        return(tarai(tarai(x-1,y,z),
               tarai(y-1,z,x),
               tarai(z-1,x,y)));
}
example (tarai x y z) x,y,z = <float>
code0 prototype
int f_tarai(int x, int y, int z)
code1
int f_tarai(int x, int y, int z){
    return(makeflt(tarai(get_float(x),get_float(y),get_float(z))));
}
code2
double tarai(double x, double y, double z){
    if(x <= y)
        return(y);
    else
        return(tarai(tarai(x-1,y,z),
               tarai(y-1,z,x),
               tarai(z-1,x,y)));
}
(defgeneric XXX (arg))
defgeneric compile
    ILOS compile code.
    basic idea is follwoing
    <<parameter>>
    if(Fadapt(...) && Fadapt(...) && ...) qualifier-method body compile code
    if(Fmatchp(...) && Fmatchp(...) && ...)) primariy-method compile code or qualifier-method that has (call-next-method)
   <<body>>
    if compiler (call-next-method) 
    1. caller is primary-method, generate one next method.
    2. caller is qualifier-method, generate all next methods. 
       in this case if(...) is Fadapt(...) for super class   
    3. when (call-next-method) after that, compiler compaire method-args and next-method-parameter.
       if method-args is superclass than next-method-parameter, compiler ignore next-method. 
    
|#
(defmodule compiler
    (defmacro when (test :rest body)
        `(if ,test (progn ,@body)) )

    (defmacro unless (test :rest body)
        `(if (not ,test) (progn ,@body)) )

    (defun any (f ls)
        (cond ((null ls) nil)
              ((funcall f (car ls)) t)
              (t (any f (cdr ls))) ))

    (defun every (f ls)
        (cond ((null ls) t)
              ((funcall f (car ls)) (every f (cdr ls)))
              (t nil)))

    (defun take (n ls)
        (if (= n 0)
            nil
            (cons (car ls) (take (- n 1) (cdr ls)))))

    (defun drop (n ls)
        (if (= n 0)
            ls
            (drop (- n 1) (cdr ls))))

    (defun last (ls)
        (car (reverse ls)))

    (defun second-last (ls)
        (elt (reverse ls) 1))

    (defun butlast (x)
        (cond ((null x) nil)
              ((null (cdr x)) nil)
              (t (cons (car x) (butlast (cdr x))))))

    (defun remove (x ls)
        (cond ((null ls) nil)
              ((eq x (car ls)) (remove x (cdr ls)))
              (t (cons (car ls) (remove x (cdr ls))))))

    (defun append! (x y)
        (while (not (null (cdr x)))
           (setq x (cdr x)))
        (set-cdr y x))

    (defun position (x ls)
        (cond ((eq x (car ls)) 0)
              (t (+ 1 (position x (cdr ls))))))

    (defun filename (str)
        (if (eql (substring str 0 0) ".")
            (filename2 str)
            (filename1 str)))

    (defun filename1 (str)
        (let* ((n (char-index #\. str)))
            (if (null n)
                (error* "lack of filename ext" str))
            (substring str 0 (- n 1))))

    ;; e.g. ./example/test.lsp 
    (defun filename2 (str)
        (let* ((n (char-index #\. (dropstring str 1))))
            (if (null n)
                (error* "lack of filename ext" str))
            (substring str 0 n)))

    ;; e.g. tests/boo/lisp -> lisp
    (defun remove-dir (str)
        (let* ((n (char-index #\/ str)))
            (if (null n)
                str
                (remove-dir (substring str (+ n 1) (- (length str) 1))))))

    (defun dropstring (str n)
        (substring str n (- (length str) 1)))
    
    (defun cutstring (str n)
        (substring str 0 (- (length str) n 1)))

    (defun substring (str m n)
        (for ((i m (+ i 1))
              (str1 "") )
             ((> i n)
              str1 )
             (setq str1 (string-append str1 (create-string 1 (elt str i))))))

    ;; e.g. (a b) -> (asubst bsubst) 
    (defun subst (vars)
        (if (null vars)
            '()
            (cons (convert (string-append (convert (conv-name (car vars)) <string>) "subst")
                           <symbol>)
                  (subst (cdr vars)))))

    (defun alpha-conv (x vars subst)
        (cond ((null x) nil)
              ((and (symbolp x) (member x vars))
               (nth subst (- (length vars) (length (member x vars)))))
              ((atom x) x)
              (t (cons (alpha-conv (car x) vars subst)
                       (alpha-conv (cdr x) vars subst)))))

    (defun nth (x n)
        (if (= n 0)
            (car x)
            (nth (cdr x) (- n 1))))

    (defglobal instream nil)
    (defglobal not-need-res
               '(return-from go tagbody while the c-lang c-define c-include c-option c-return))
    
    (defglobal not-need-colon '(c-lang c-define c-include c-option c-return))
    (defglobal builtin-class 
    '(<OBJECT> <BASIC-ARRAY> <GENERAL-ARRAY*> <BASIC-ARRAY*> <BASIC-VECTOR> <GENERAL-VECTOR>
       <STRING> <BUILT-IN-CLASS> <CHARACTER> <FUNCTION> <GENERIC-FUNCTION>
       <STANDARD-GENERIC-FUNCTION> <LIST> <CONS> <NULL> <SYMBOL> <NUMBER> <FLOAT> <INTEGER>
       <SERIOUS-CONDITION> <ERROR> <ARITHMETIC-ERROR> <DIVISION-BY-ZERO>
       <FLOATING-POINT-OVERFLOW> <FLOATING-POINT-UNDERFLOW> <CONTROL-ERROR> <PARSE-ERROR>
       <PROGRAM-ERROR> <DOMAIN-ERROR> <CLASS-ERROR> <UNDEFINED-ENTITY> <UNBOUND-VARIABLE>
       <UNDEFINED-FUNCTION> <SIMPLE-ERROR> <STREAM-ERROR> <END-OF-STREAM> <STORAGE-EXHAUSTED>
       <STANDARD-CLASS> <STANDARD-OBJECT> <STREAM> <INVALID> <FIXNUM> <LONGNUM> <BIGNUM>))
    (defglobal user-class nil)
    (defglobal global-variable nil)
    (defglobal dynamic-variable nil)
    (defglobal function-arg nil)
    (defglobal generic-name-arg nil)
    (defglobal catch-block-tag nil)
    (defglobal unwind-cleanup nil)
    (defglobal unwind-nest 0)
    (defglobal file-name-and-ext nil)
    (defglobal lambda-count 0)
    (defglobal lambda-nest 0)
    (defglobal lambda-root 0)
    (defglobal lambda-history nil)
    (defglobal c-lang-option nil)
    (defglobal optimize-enable nil)
    (defglobal inference-name nil)
    (defglobal code0 nil)
    (defglobal code1 nil)
    (defglobal code2 nil)
    (defglobal code3 nil)
    (defglobal code4 nil)
    (defglobal code5 nil)
    (defglobal code6 nil)
    (defglobal code7 nil)

    (defun error* (str x)
        (format (standard-output) "compile error ~A ~A ~%" str x)
        (throw 'exit t))

    ;; This function generate C code and write to file *.c
    ;; Caution! for raspi "gcc -O3 -w -shared -fPIC -o ";
    (defpublic compile-file (x :rest rm-opt)
        (setq file-name-and-ext x)
        (setq type-function nil)
        (inference-file x)
        (catch 'exit
               (unwind-protect (compile-file1 x rm-opt)
                               (if instream
                                   (close instream))
                               (setq lambda-nest 0)
                               (setq lambda-count 0)
                               (setq lambda-root 0)
                               (setq lambda-history nil)
                               (eisl-ignore-toplevel-check nil)))
        t)

    (defun compile-file1 (x rm-opt)
        (let* ((include
               (let ((prefix (getenv "EASY_ISLISP")))
                  (if (null prefix)
                      "-I$HOME/eisl "
                      "-I$EASY_ISLISP ")))
               (option
               (cond ((member (self-introduction) '(linux openbsd))
                      "cc -O3 -w -shared -fPIC -s -o ")
                     ((eq (self-introduction) 'freebsd) "cc -O3 -w -shared -fPIC -s -o ")
                     ((eq (self-introduction) 'macos) "cc -O3 -w -shared -fPIC -Wl,-S,-x -o ")))
               (fname (filename x))
               (infnames
               (string-append fname
                              "0.c "
                              fname
                              "1.c "
                              fname
                              "5.c "
                              fname
                              "6.c "
                              fname
                              "7.c "
                              fname
                              "2.c "
                              fname
                              "3.c "
                              fname
                              "4.c "))
               (env-cflags (getenv "CFLAGS"))
               (env-cflags-str (if env-cflags
                                  env-cflags
                                  ""))
               (env-ldflags (getenv "LDFLAGS"))
               (env-ldflags-str (if env-ldflags
                                   env-ldflags
                                   "")) )
            (eisl-ignore-toplevel-check t)
            (format (standard-output) "initialize~%")
            (initialize fname ".c")
            (format (standard-output) "pass1~%")
            (pass1 x)
            (format (standard-output) "pass2~%")
            (pass2 x)
            (eisl-ignore-toplevel-check nil)
            (format (standard-output) "finalize~%")
            (finalize (remove-dir fname) ".c")
            (format (standard-output) "invoke CC~%")
            (system
             (string-append option
                            fname
                            ".o "
                            include
                            fname
                            "0.c "
                            c-lang-option
                            " "
                            env-cflags-str
                            " "
                            env-ldflags-str))
            (cond ((null rm-opt) (system (string-append "rm " infnames)))
                  ((eq (car rm-opt) nil) nil)
                  ((eq (car rm-opt) t) (system (string-append "sudo rm " infnames))))))

    ;; not lisp code compile only C compile. 
    (defpublic compile-file* (x :rest rm-opt)
        (setq c-lang-option "")
        (let* ((include
               (let ((prefix (getenv "EASY_ISLISP")))
                  (if (null prefix)
                      "-I$HOME/eisl "
                      "-I$EASY_ISLISP ")))
               (option
               (cond ((member (self-introduction) '(linux openbsd))
                      "cc -O3 -w -shared -fPIC -s -o ")
                     ((eq (self-introduction) 'freebsd) "cc -O3 -w -shared -fPIC -s -o ")
                     ((eq (self-introduction) 'macos) "cc -O3 -w -shared -fPIC -Wl,-S,-x -o ")))
               (fname (filename x))
               (infnames
               (string-append fname
                              "0.c "
                              fname
                              "1.c "
                              fname
                              "5.c "
                              fname
                              "6.c "
                              fname
                              "7.c "
                              fname
                              "2.c "
                              fname
                              "3.c "
                              fname
                              "4.c "))
               (env-cflags (getenv "CFLAGS"))
               (env-cflags-str (if env-cflags
                                  env-cflags
                                  ""))
               (env-ldflags (getenv "LDFLAGS"))
               (env-ldflags-str (if env-ldflags
                                   env-ldflags
                                   "")) )
            (system (string-append 
                            option
                            fname
                            ".o "
                            include
                            fname
                            "0.c "
                            c-lang-option
                            " "
                            env-cflags-str
                            " "
                            env-ldflags-str))))
            


    (defun pass1 (x)
        (setq instream (open-input-file x))
        (let ((sexp nil))
           (while (setq sexp (read instream nil nil))
              (cond ((and (consp sexp) (eq (car sexp) 'defmodule)) (module-check sexp))
                    (t (check-args-count sexp)
                       (find-catch-block-tag (macroexpand-all sexp))
                       (find-user-class sexp))))
           (close instream)
           (setq instream nil)
           (mapc (lambda (x) (remove-property x 'unwind-nest))
                 catch-block-tag)))

    (defun module-check (x)
        (for ((name (car (cdr x)))
              (body (cdr (cdr x)) (cdr body)) )
             ((null body)
              t )
             (let ((sexp (eisl-modulesubst (car body) name nil)))
                (check-args-count sexp)
                (find-catch-block-tag (macroexpand-all sexp))))
        (eval x))

    (defun check-args-count (x)
        (cond ((eq (car x) 'defun)
               (when (assoc (elt x 1) function-arg)
                     (error* "duplicate definition" (elt x 1)))
               (setq function-arg
                     (cons (cons (elt x 1) (count-args (elt x 2))) function-arg)))
              ((eq (car x) 'defpattern)
               (when (assoc (elt x 1) function-arg)
                     (error* "duplicate definition" (elt x 1)))
               (setq function-arg (cons (cons (elt x 1) -1) function-arg)))
              ((eq (car x) 'defmacro)
               (unless (symbolp (elt x 1))
                       (error* "defmacro: not symbol" (elt x 1)))
               (unless (listp (elt x 2))
                       (error* "defmacro: not list" (elt x 2)))
               (when (null (cdr (cdr (cdr x))))
                     (error* "defmacro: not exist body" x))
               (when (assoc (elt x 1) function-arg)
                     (error* "duplicate definition" (elt x 1)))
               (setq function-arg
                     (cons (cons (elt x 1) (count-args (elt x 2))) function-arg))
               (eval x))
              ((eq (car x) 'defglobal)
               (unless (= (length x) 3) (error* "defglobal: illegal form" x))
               (unless (symbolp (elt x 1))
                       (error: "defglobal: not symbol" (elt x 1)))
               (setq global-variable (cons (elt x 1) global-variable))
               (if (atom (elt x 2))
                   (eval x)))
              ((eq (car x) 'defdynamic)
               (unless (= (length x) 3) (error* "defdynamic: illegal form" x))
               (unless (symbolp (elt x 1))
                       (error: "defdynamic: not symbol" (elt x 1)))
               (setq dynamic-variable (cons (elt x 1) dynamic-variable))
               (if (atom (elt x 2))
                   (eval x)))
              ((eq (car x) 'defconstant)
               (unless (= (length x) 3) (error* "defconstant: illegal form" x))
               (unless (symbolp (elt x 1))
                       (error: "defconstant: not symbol" (elt x 1)))
               (setq global-variable (cons (elt x 1) global-variable))
               (if (atom (elt x 2))
                   (eval x)))
              ((eq (car x) 'defclass)
               (unless (symbolp (elt x 1))
                       (error* "defclass: not symbol" (elt x 1)))
               (unless (listp (elt x 2))
                       (error* "defclass: not list" (elt x 2)))
               (eval x))
              ((eq (car x) 'defgeneric)
               (unless (or (symbolp (elt x 1)) (listp (elt x 1)))
                       (error* "defgeneric: not symbol " (elt x 1)))
               (unless (listp (elt x 2))
                       (error* "defgeneric: not list " (elt x 2)))
               (when (assoc (elt x 1) function-arg)
                     (error* "duplicate definition" (elt x 1)))
               (setq function-arg
                     (cons (cons (elt x 1) (count-args (elt x 2))) function-arg))
               (let* ((fname0 (elt x 1))
                      (fname (if (listp fname0)
                                (elt fname0 1)
                                fname0)) )
                   (setq generic-name-arg
                         (cons (cons fname (elt x 2)) generic-name-arg)))
               (eval x))
              ((eq (car x) 'defmethod)
               (unless (or (symbolp (elt x 1)) (listp (elt x 1)))
                       (error* "defmethod: not symbol" (elt x 1)))
               (unless (or (listp (elt x 2)) (symbolp (elt x 2)))
                       (error* "defmethod: not list" (elt x 2)))
               (when (and (listp (elt x 2)) (null (cdr (cdr (cdr x)))))
                     (error* "defmethod: not exist body" x))
               (when (and (symbolp (elt x 2)) (null (cdr (cdr (cdr (cdr x))))))
                     (error* "defmethod: not exist body" x))
               (eval x))))

    (defun find-catch-block-tag (x)
        (cond ((null x) nil)
              ((atom x) nil)
              ((and (eq (car x) 'catch)
                    (>= (length x) 3)
                    (consp (elt x 1))
                    (= (length (elt x 1)) 2))
               (if (not (member (elt (elt x 1) 1) catch-block-tag))
                   (setq catch-block-tag (cons (elt (elt x 1) 1) catch-block-tag))))
              ((and (eq (car x) 'block) (>= (length x) 3) (symbolp (elt x 1)))
               (if (not (member (elt x 1) catch-block-tag))
                   (setq catch-block-tag (cons (elt x 1) catch-block-tag)))
               (find-catch-block-tag (cdr (cdr x))))
              ((consp (car x)) (find-catch-block-tag (car x)) (find-catch-block-tag (cdr x)))
              (t (find-catch-block-tag (cdr x)))))
    
    (defun find-user-class (x) 
        (cond ((and (consp x) (eq (car x) 'defclass))
               (setq user-class (cons (elt x 1) user-class)))
              (t nil)))

    (defun pass2 (x)
        (setq instream (open-input-file x))
        (declare-catch-block-buffer)
        (let ((sexp nil))
           (while (setq sexp (read instream nil nil))
              (if (optimize-p sexp)
                  (setq optimize-enable (elt sexp 1))
                  (setq optimize-enable nil))
              (compile sexp))
           (close instream)
           (setq instream nil))
        (mapc (lambda (x) (remove-property x 'unwind-nest))
              catch-block-tag))

    (defun count-args (ls)
        (cond ((null ls) 0)
              ((= (length ls) 1) 1)
              ((eq (second-last ls) ':rest) (* -1 (- (length ls) 1)))
              ((eq (second-last ls) '&rest) (* -1 (- (length ls) 1)))
              (t (length ls))))

    (defun compile (x)
        (cond ((eq (car x) 'defun) (comp-defun x))
              ((eq (car x) 'defpattern) (comp-defun (macroexpand-all x)))
              ((eq (car x) 'defglobal) (comp-defglobal x))
              ((eq (car x) 'defdynamic) (comp-defdynamic x))
              ((eq (car x) 'defconstant) (comp-defconstant x))
              ((eq (car x) 'defmacro) (comp-defmacro x))
              ((eq (car x) 'defclass) (comp-defclass x))
              ((eq (car x) 'defgeneric) (comp-defgeneric x))
              ((eq (car x) 'defmethod) (comp-defmethod x))
              ((eq (car x) 'defmodule) (comp-defmodule x))
              ((eq (car x) 'import) (comp-import x))
              (t (comp code4 x nil nil nil nil t nil nil)
                 (format code4 ";")))
        (setq lambda-history nil))

    ;; x object to compile
    ;; env environment (local variables)
    ;; args arguments of function or lambda
    ;; tail tail recursive?
    ;; name function name, lambda name
    ;; global global-variables
    ;; test test part of if syntax?
    ;; clos free-variables that closure has.
    (defun comp (stream x env args tail name global test clos)
        (cond ((and (fixnump x) (not global))
               (cond ((not optimize-enable)
                      (format stream "fast_immediate(")
                      (format-integer stream x 10)
                      (format stream ")"))
                     (t (format-integer stream x 10))))
              ((and (fixnump x) global)
               (format stream "Fmakeint(")
               (format-integer stream x 10)
               (format stream ")"))
              ((floatp x)
               (cond ((not optimize-enable)
                      (format stream "Fmakestrflt(\"")
                      (format-float stream x)
                      (format stream "\")"))
                     (t (format-float stream x))))
              ((longnump x)
               (format stream "Fmakestrlong(\"")
               (format-integer stream x 10)
               (format stream "\")"))
              ((bignump x)
               (format stream "Fmakebig(\"")
               (format-integer stream x 10)
               (format stream "\")"))
              ((stringp x) (format stream "Fmakestr(\"~A\")" x))
              ((characterp x)
               (cond ((or (char= x #\\)
                          (char= x (convert 34 <character>)) ;"
                          (char= x (convert 39 <character>))) ;'
                      (format stream "Fmakechar(\"\\~C\")" x))
                     ((special-char-p x)
                      (format stream "Fmakechar(\"~A\")" (print-special-char x)))
                     (t (format stream "Fmakechar(\"~C\")" x))))
              ((general-vector-p x)
               (format stream "Fvector(")
               (list-to-c1 stream (convert x <list>))
               (format stream ")"))
              ((general-array*-p x)
               (format stream "Farray(")
               (format-integer stream (length (array-dimensions x)) 10)
               (format stream ",")
               (list-to-c1 stream (eisl-readed-array-list x))
               (format stream ")"))
              ((and (symbolp x) clos)
               ;;closure has free-variable
               (cond ((eq x nil) (format stream "NIL"))
                     ((eq x t) (format stream "T"))
                     ((member x clos)
                      (format stream "Fnth(")
                      (format-integer stream (position x clos) 10)
                      (format stream ",Fcdr(Fmakesym(\"~A" (lambda-name-with-root name))
                      (format stream "\")))"))
                     ((member x env) (format stream (convert (conv-name x) <string>)))
                     (t (format stream "Fcdr(Fmakesym(\"")
                        (format stream (convert x <string>))
                        (format stream "\"))"))))
              ((and (symbolp x) (not clos))
               ;;closure does not have free-variable
               (cond ((eq x nil) (format stream "NIL"))
                     ((eq x t) (format stream "T"))
                     ((member x env) 
                      (cond ((free-variable-in-history-p x lambda-history)
                            ;; free-variable in out of lambda
                              (let* ((history (free-variable-in-history-p x lambda-history))
                                     (root (car history))
                                     (free (cdr history)))
                                 (format stream "Fnth(")
                                 (format-integer stream (position x free) 10)
                                 (format stream ",Fcdr(Fmakesym(\"~A" root)
                                 (format stream "\")))")))
                            ;; normal local variable
                            (t (format stream (convert (conv-name x) <string>)))))
                     ((member x builtin-class)
                      (format stream "Fmakesym(\"")
                      (format stream (convert x <string>))
                      (format stream "\")"))
                     ((member x user-class)
                      (format stream "Fmakesym(\"")
                      (format stream (convert x <string>))
                      (format stream "\")"))
                     (t (when (and (not (member x global-variable))
                                   (not (eq x '*pi*))
                                   (not (eq x '*most-negative-float*))
                                   (not (eq x '*most-positive-float*))
                                   (not (eq x '*positive-infinity*))
                                   (not (eq x '*negative-infinity*)))
                              (error* "undefined global variable" x))
                        (format stream "Fcdr(Fmakesym(\"")
                        (format stream (convert x <string>))
                        (format stream "\"))"))))
              ((and (consp x) (eq (car x) 'lambda)) (comp-lambda x env global))
              ((and (consp x) (macrop (car x)))
               (comp stream
                     (macroexpand-1 x)
                     env
                     args
                     tail
                     name
                     global
                     test
                     clos))
              ((and (consp x) (eq (car x) 'quote))
               (cond ((symbolp (elt x 1))
                      (format stream "Fmakesym(\"")
                      (format stream (convert (elt x 1) <string>))
                      (format stream "\")"))
                     ((consp (elt x 1)) (list-to-c1 stream (elt x 1)))
                     (t (comp stream (elt x 1) env args tail name global test clos))))
              ((and (consp x) (eq (car x) 'quasi-quote))
               (comp stream
                     (quasi-transfer (elt x 1) 0)
                     env
                     args
                     tail
                     name
                     global
                     test
                     clos))
              ((and (consp x) (eq (car x) 'if))
               (comp-if stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'cond))
               (comp-cond stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'case))
               (comp-case stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'case-using))
               (comp-case-using stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'flet))
               (comp-flet stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'labels))
               (comp-labels stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'let))
               (comp-let stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'let*))
               (comp-let* stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mt-let))
               (comp-mt-let stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mt-call))
               (comp-mt-call stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mt-exec))
               (comp-mt-exec stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mp-call))
               (comp-mp-call stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mp-exec))
               (comp-mp-exec stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mp-and))
               (comp-mp-and stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mp-or))
               (comp-mp-or stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'dp-call))
               (comp-dp-call stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'dp-exec))
               (comp-dp-exec stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'dp-and))
               (comp-dp-and stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'dp-or))
               (comp-dp-or stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'with-open-input-file))
               (comp-with-open-input-file stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'with-open-output-file))
               (comp-with-open-output-file stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'with-open-io-file))
               (comp-with-open-io-file stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'with-handler))
               (comp-with-handler stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'and))
               (if test
                   (comp-test-and stream x env args tail name global test clos)
                   (comp-and stream x env args tail name global test clos)))
              ((and (consp x) (eq (car x) 'or))
               (if test
                   (comp-test-or stream x env args tail name global test clos)
                   (comp-or stream x env args tail name global test clos)))
              ((and (consp x) (eq (car x) 'progn))
               (comp-progn stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'mt-lock))
               (comp-mt-lock stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'for))
               (comp-for stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'while))
               (comp-while stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'setq))
               (comp-setq stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'tagbody))
               (comp-tagbody stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'go))
               (comp-go stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'block))
               (comp-block stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'return-from))
               (comp-return-from stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'convert))
               (comp-convert stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'function))
               (comp-function stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'symbol-function))
               (comp-symbol-function stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'class))
               (comp-class stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'symbol-class))
               (comp-symbol-class stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'catch))
               (comp-catch stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'throw))
               (comp-throw stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'unwind-protect))
               (comp-unwind-protect stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'setf))
               (comp-setf stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'dynamic))
               (comp-dynamic stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'set-dynamic))
               (comp-set-dynamic stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'dynamic-let))
               (comp-dynamic-let stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'the)) t)
              ((and (consp x) (eq (car x) 'not))
               (comp-not stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'car))
               (comp-car stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'cdr))
               (comp-cdr stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'cons))
               (comp-cons stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'length))
               (comp-length stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'c-include)) (comp-c-include x))
              ((and (consp x) (eq (car x) 'c-define)) (comp-c-define x))
              ((and (consp x) (eq (car x) 'c-lang)) (comp-c-lang x))
              ((and (consp x) (eq (car x) 'c-option)) (comp-c-option x))
              ((and (consp x) (eq (car x) 'c-return)) nil)
              ((and (consp x)
                    (= (length x) 3)
                    (member (car x) '(= < <= > >= + - * mod eq)))
               (comp-numeric stream x env args tail name global test clos))
              ((and (consp x) (eq (car x) 'call-next-method))
               (comp-call-next-method stream env args tail name global test clos))
              ((and (consp x) (eq (car x) 'next-method-p))
               (comp-next-method-p stream env args tail name global test clos))
              ((and (consp x) (subrp (car x)))
               (comp-subrcall stream x env args tail name global test clos))
              ((and (consp x) (consp (car x)) (eq (car (car x)) 'lambda))
               (comp stream (cons 'funcall x) env args tail name global test clos))
              ((listp x) (comp-funcall stream x env args tail name global test clos))))

    (defun special-char-p (x)
        (member x
                '(#\alarm
                  #\backspace
                  #\delete
                  #\escape
                  #\return
                  #\newline
                  #\null
                  #\space
                  #\tab)))

    (defun print-special-char (x)
        (cond ((char= x #\alarm) "ALARM")
              ((char= x #\backspace) "BACKSPACE")
              ((char= x #\delete) "DELETE")
              ((char= x #\escape) "ESCAPE")
              ((char= x #\return) "RETURN")
              ((char= x #\newline) "NEWLINE")
              ((char= x #\null) "NULL")
              ((char= x #\space) "SPACE")
              ((char= x #\tab) "TAB")))

    (defun initialize (fname ext)
        (setq global-variable nil)
        (setq dynamic-variable nil)
        (setq function-arg nil)
        (setq generic-name-arg nil)
        (setq catch-block-tag nil)
        (setq user-class nil)
        (setq c-lang-option "")
        (setq code0 (open-output-file (string-append fname "0" ext)))
        (setq code1 (open-output-file (string-append fname "1" ext)))
        (setq code2 (open-output-file (string-append fname "2" ext)))
        (setq code3 (open-output-file (string-append fname "3" ext)))
        (setq code4 (open-output-file (string-append fname "4" ext)))
        (setq code5 (open-output-file (string-append fname "5" ext)))
        (setq code6 (open-output-file (string-append fname "6" ext)))
        (setq code7 (open-output-file (string-append fname "7" ext)))
        (format code0 "#include \"fast.h\"~%")
        (format code3 "void init_tfunctions(void){~%")
        (format code4 "void init_declare(void){int th=0;~%signal(SIGINT, signal_handler_c);~%"))

    (defun declare-catch-block-buffer ()
        (format code4 "Fsetcatchsymbols(")
        (list-to-c1 code4 catch-block-tag)
        (format code4 ");")
        (for ((tag catch-block-tag (cdr tag)))
             ((null tag)
              t )
             (format code0 "jmp_buf c_~A[50];~%" (conv-name (car tag)))))

    (defun finalize (fname ext)
        (format code0 "#include \"~A\"~%" (string-append fname "1" ext))
        (format code0 "#include \"~A\"~%" (string-append fname "5" ext))
        (format code0 "#include \"~A\"~%" (string-append fname "6" ext))
        (format code0 "#include \"~A\"~%" (string-append fname "7" ext))
        (format code0 "#include \"~A\"~%" (string-append fname "2" ext))
        (format code0 "#include \"~A\"~%" (string-append fname "3" ext))
        (format code0 "#include \"~A\"~%" (string-append fname "4" ext))
        (format code3 "}")
        (format code4 "}")
        (close code0)
        (close code1)
        (close code2)
        (close code3)
        (close code4)
        (close code5)
        (close code6)
        (close code7))

    (defun comp-defun (x)
        (format (standard-output) "compiling ~A ~%" (elt x 1))
        (unless (symbolp (elt x 1))
                (error* "defun: not symbol " (elt x 1)))
        (unless (listp (elt x 2)) (error* "defun: not list " (elt x 2)))
        (when (null (cdr (cdr (cdr x))))
              (error* "defun: not exist body" (elt x 1)))
        (comp-defun0 x)
        (comp-defun1 x)
        (comp-defun2 x)
        (comp-defun3 x))

    ;;create lambda as SUBR and invoke the SUBR.
    (defun comp-lambda (x env global)
        (unless (listp (elt x 1)) (error* "lambda: not list" (elt x 1)))
        (when (null (cdr (cdr x))) (error* "lambda: not exist body" x))
        (setq lambda-nest (+ lambda-nest 1))
        (cond ((= lambda-nest 1) (setq lambda-root lambda-count)))
        (let* ((name (lambda-name))
               (args (elt x 1))
               (body (cdr (cdr x)))
               (free (find-free-variable body args env))
               (stream (lambda-stream-caller global)) )
            (comp-lambda0 x name)
            (comp-lambda1 x name)
            (comp-lambda2 body env args name free)
            (comp-lambda3 name)
            ;; only root lambda has free-variable-list
            (cond ((= lambda-nest 1)
                   (format stream "({Fset_cdr(Fmakesym(\"~A\")," name)
                   (free-variable-list stream free)
                   (format stream ");Fcar(Fmakesym(\"~A\"));})" name)
                   (setq lambda-history (cons (cons name free) lambda-history)))
                  (t (format stream "({Fcar(Fmakesym(\"~A\"));})" name)))
            (setq lambda-nest (- lambda-nest 1))))

    (defun lambda-name ()
        (let ((name
              (conv-name
               (convert (string-append (filename file-name-and-ext)
                                       (convert lambda-count <string>))
                        <symbol>))))
           (setq lambda-count (+ lambda-count 1))
           name))
    
    ;; abcd12 -> abcd3 when lambda-root is 3
    ;; innested lambda free-variables are saved in root lambda
    ;; so,generate root-lambda-name from current state.
    (defun lambda-name-with-root (name)
        (let ((count-length (length (convert (- lambda-count 1) <string>)))
              (name-str (convert name <string>)))
            (convert (string-append  (cutstring name-str count-length)
                                     (convert lambda-root <string>))
                     <symbol>)))

    (defun comp-defgeneric (x)
        (format (standard-output) "compiling ~A ~%" (elt x 1))
        (comp-defgeneric0 x)
        (comp-defgeneric1 x)
        (comp-defgeneric2 x)
        (comp-defgeneric3 x))

    (defun comp-defmodule (x)
        (let ((name (car (cdr x)))
              (body (cdr (cdr x)))
              (public nil) )
           (for ((s body (cdr s)))
                ((null s)
                 t )
                (if (and (consp (car s)) (eq (car (car s)) 'defpublic))
                    (setq public (cons (elt (car s) 1) public)))
                (if (and (consp (car s))
                         (eq (car (car s)) 'import)
                         (cdr (cdr (car s))))
                    (setq public (append (cdr (cdr (car s))) public)))
                (compile (eisl-modulesubst (car s) name public)))))

    (defun comp-import (x)
        (let* ((name (elt x 1))
               (name1 (string-append "/usr/local/share/eisl/library/" name ".o"))
               (name2 (string-append "/usr/local/share/eisl/library/" name ".lsp"))
               (code
               `(cond ((probe-file ,name1) (load ,name1)) ((probe-file ,name2) (load ,name2)))) )
            (compile code)))

    (defun comp-defun0 (x)
        (let* ((name (elt x 1))
               (args (elt x 2))
               (n (length args)) )
            (format code0 "static int f_~A(int arglist, int th);" (conv-name name))
            (format code0 "static int ~A" (conv-name name))
            (if (not optimize-enable)
                (gen-arg2 code0 args)
                (type-gen-arg2 code0 args (argument-type name)))
            (format code0 ";~%")))

    (defun comp-lambda0 (x name)
        (let* ((args (elt x 1))
               (n (length args)) )
            (format code0 "static int f_~A(int arglist, int th);" (conv-name name))
            (format code0 "static int ~A" (conv-name name))
            (gen-arg2 code0 args)
            (format code0 ";~%")))

    (defun comp-defgeneric0 (x)
        (let* ((name0 (elt x 1))
               (name (if (listp name0)
                        (elt name0 1)
                        name0))
               ; e.g. (setf foo)
               (args (elt x 2))
               (n (length args)) )
            (format code0 "static int f_~A(int arglist, int th);" (conv-name name))
            (format code0 "static int ~A" (conv-name name))
            (gen-arg2 code0 args)
            (format code0 ";~%")))

    ;;generate f_XXX(int arg){...}
    (defun comp-defun1 (x)
        (let* ((name (elt x 1))
               (args (elt x 2))
               (n (count-args args)) )
            (format code1 "static int f_~A(int arglist, int th){~%" (conv-name name))
            (gen-arg1 (abs n))
            (gen-assign n)
            (if (not optimize-enable)
                (gen-call (conv-name name) (abs n))
                (type-gen-call name (abs n)))
            (format code1 "}~%")))

    (defun comp-lambda1 (x name)
        (let* ((args (elt x 1))
               (n (count-args args)) )
            (format code1 "static int f_~A(int arglist, int th){~%" (conv-name name))
            (gen-arg1 (abs n))
            (gen-assign n)
            (gen-call (conv-name name) (abs n))
            (format code1 "}~%")))

    (defun comp-defgeneric1 (x)
        (let* ((name0 (elt x 1))
               (name (if (listp name0)
                        (elt name0 1)
                        name0))
               ; e.g. (setf foo)
               (args (elt x 2))
               (n (count-args args)) )
            (format code1 "static int f_~A(int arglist, int th){~%" (conv-name name))
            (gen-arg1 (abs n))
            (gen-assign n)
            (gen-call (conv-name name) (abs n))
            (format code1 "}~%")))

    ;;genrate int XXX(int x, ...){...} this is main function.
    (defun comp-defun2 (x)
        (let ((name (elt x 1))
              (args (elt x 2))
              (body (cdr (cdr (cdr x)))) )
           (format code2 "static int ~A" (conv-name name))
           (if (not optimize-enable)
               (gen-arg2 code2 args)
               (type-gen-arg2 code2 args (argument-type name)))
           (format code2 "{~%")
           (format code2 "int res;~%")
           (cond ((and (not optimize-enable)
                       (has-tail-recur-p (macroexpand-all body) name))
                  ;;for tail recursive tempn var;
                  (gen-arg3 (length args)))
                 ((and optimize-enable
                       (has-tail-recur-p (macroexpand-all body) name))
                  (type-gen-arg3 (length args) (argument-type name))))
           (cond ((has-tail-recur-p (macroexpand-all body) name)
                  (format-object code2 (conv-name name) nil)
                  (format code2 "loop:~% if(exit_flag == 1){exit_flag = 0; Fjump_to_repl();}")))
           (cond ((not optimize-enable) (gen-shelterpush code2 args) (gen-checkgc)))
           (for ((body1 body (cdr body1)))
                ((null (cdr body1))
                 (if (and (not (not-need-res-p (car body1)))
                         (not (tailcallp (car body1) t name)))
                    (format code2 "res = "))
                 (comp code2 (car body1) args args t name nil nil nil)
                 (if (not (not-need-colon-p (car body1)))
                    (format code2 ";~%"))
                 (if (not optimize-enable)
                    (gen-shelterpop code2 (reverse args)))
                 (format code2 "return(res);}~%") )
                (comp code2 (car body1) args args nil name nil nil nil)
                (if (not (not-need-colon-p (car body1)))
                    (format code2 ";~%")))))

    (defun comp-lambda2 (body env args name clos)
        (let ((stream (lambda-stream-callee)))
           (format stream "static int ~A" (conv-name name))
           (gen-arg2 stream args)
           (format stream "{~%")
           (format stream "int res;~%")
           (cond ((has-tail-recur-p body name)
                  (format-object stream (conv-name name) nil)
                  (format stream "loop:~%")))
           (gen-shelterpush stream args)
           (for ((body1 body (cdr body1)))
                ((null (cdr body1))
                 (if (not (not-need-res-p (car body1)))
                    (format stream "res = "))
                 (comp stream (car body1) (append args env) args nil name nil nil clos)
                 (format stream ";~%")
                 (gen-shelterpop stream (reverse args))
                 (format stream "return(res);}~%") )
                (comp stream (car body1) args args nil name nil nil clos)
                (format stream ";~%"))))

    ;;when lambda nest, select nested file
    ;;for lambda callee
    (defun lambda-stream-callee ()
        (cond ((= lambda-nest 0) code5)
              ((= lambda-nest 1) code5)
              ((= lambda-nest 2) code6)
              ((= lambda-nest 3) code7)
              (t (error* "lambda: over nesting" lambda-nest))))

    (defun lambda-stream-caller (global)
        (cond (global code4)
              ((= lambda-nest 1) code2)
              ((= lambda-nest 2) code5)
              ((= lambda-nest 3) code6)
              (t (error* "lambda: over nesting" lambda-nest))))

    ;;for lambda find free-variable. 
    (defun find-free-variable (x args env)
        (find-free-variable2 (find-free-variable1 x args env)))

    (defun find-free-variable1 (x args env)
        (cond ((null x) nil)
              ((and (symbolp x) (not (member x args)) (member x env)) (list x))
              ((atom x) nil)
              (t
               (append (find-free-variable1 (car x) args env)
                       (find-free-variable1 (cdr x) args env)))))

    ;; remove dupilicate variable
    (defun find-free-variable2 (x)
        (cond ((null x) nil)
              ((member (car x) (cdr x)) (find-free-variable2 (cdr x)))
              (t (cons (car x) (find-free-variable2 (cdr x))))))
    
    ;;lambda-history is used in following code.
    ;;(defun foo (x)
    ;;(let ((a 0))
    ;;    ((lambda (x) (setq a x)) x)
    ;;    a))
    ;;variable a has a side effect. 
    ;;lambda-history save lambda-root symbol and free-variables
    ;;avobe case history is (lambda-name a)
    (defun free-variable-in-history-p (x history)
        (cond ((null history) nil)
              ((member x (cdr (car history))) (car history))
              (t (free-variable-in-history-p x (cdr history)))))
               

    
    ;;create free-variable list to set lambda-name symbol
    (defun free-variable-list (stream x)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(~A," (conv-name (car x)))
                 (free-variable-list stream (cdr x))
                 (format stream ")"))))

    ;; find free-variable outer lambda
    ;; free-var  ((v1 v2 .. lambda-sym1)(v1 v2 .. lambda-sym2)...)
    (defun find-free-variable-outer-lambda (x free-var)
        (cond ((null free-var) nil)
              ((member x (car free-var)) (car free-var))
              (t (find-free-variable-outer-lambda x (cdr free-var)))))

    (defun comp-defgeneric2 (x)
        (let* ((name0 (elt x 1))
               (name (if (listp name0)
                        (elt name0 1)
                        name0))
               ;e.g. (setf foo)
               (args (varlis-to-lambda-args (elt x 2)))
               (method (eisl-get-method name)) )
            (setq generic-args args)
            (format code2 "static int ")
            (format code2 (convert (conv-name name) <string>))
            (gen-arg2 code2 args)
            (format code2 "{~%")
            (format code2 "int res=20000000;~%")
            (gen-shelterpush code2 args)
            (gen-arg2-copy code2 args)
            (gen-checkgc)
            (comp-defgeneric-body method)
            (gen-shelterpop code2 (reverse args))
            (format code2
                    "if(res==20000000) FILOSerror(Fmakesym(\"~A\"),"
                    name)
            (gen-error-argument args)
            (format code2 ");~%")
            (format code2 "return(res);}~%"))
        (setq rest-method nil)
        (setq method-args nil)
        (setq generic-args nil)
        (setq caller-priority nil)
        (setq multiple-call-next-method nil))

    

    (defconstant around 11)
    (defconstant befor 12)
    (defconstant primary 13)
    (defconstant after 14)
    ;;geberate ILOSerror arguments list
    (defun gen-error-argument (args)
        (cond ((null args) (format code2 "NIL"))
              ((or (eq (car args) '&rest) (eq (car args) ':rest)) (gen-error-argument (cdr args)))
              (t (format code2 "Fcons(~A," (conv-name (car args)))
                 (gen-error-argument (cdr args))
                 (format code2 ")"))))

    ;;ex ((x <list>)y :rest z) -> (x y z)
    (defun varlis-to-lambda-args (x)
        (cond ((null x) nil)
              ((eq (car x) ':rest) (cdr x))
              ((eq (car x) ':rest) (cdr x))
              ((symbolp (car x)) (cons (car x) (varlis-to-lambda-args (cdr x))))
              ((consp (car x)) (cons (car (car x)) (varlis-to-lambda-args (cdr x))))
              (t (error* "defgeneric" x))))

    ;; x is methods 
    (defun comp-defgeneric-body (x)
        (cond ((null x) (setq multiple-call-next-method nil))
              (t (let* ((varbody (eisl-get-method-body (car x)))
                        (varlis (alpha-conv-varlis (car varbody) generic-args))
                        (body
                        (alpha-conv-method (cdr varbody)
                                           (method-varlis-to-substlist (car varbody) generic-args)))
                        (priority (eisl-get-method-priority (car x))) )
                     (setq method-args varlis)
                     (setq rest-method x)
                     (setq caller-priority priority)
                     (setq multiple-call-next-method
                           (has-multiple-call-next-method-p body))
                     (format code2 "if(")
                     (cond ((= priority primary)
                            (comp-defgeneric-primary-cond varlis
                                                          code2
                                                          (varlis-to-lambda-args method-args)
                                                          nil
                                                          nil
                                                          nil
                                                          nil
                                                          nil
                                                          nil))
                           (t
                            (comp-defgeneric-qualifier-cond varlis
                                                            code2
                                                            (varlis-to-lambda-args method-args)
                                                            nil
                                                            nil
                                                            nil
                                                            nil
                                                            nil
                                                            nil)))
                     (format code2 ")~%{")
                     (comp-defgeneric-body1 body (varlis-to-lambda-args varlis))
                     (if (= priority around)
                         (format code2 "return(res);"))
                     (if (and (= priority primary)
                              (not (has-after-qualifier-p (cdr x))))
                         (format code2 "return(res);"))
                     (format code2 "}~%"))
                 (comp-defgeneric-body (cdr x)))))

    ;;x is the method bodies
    (defun comp-defgeneric-body1 (x env)
        (cond ((null x) t)
              (t (format code2 "res = ")
                 (comp code2 (car x) env generic-args nil nil nil nil nil)
                 (if (not (not-need-colon-p (car x)))
                     (format code2 ";~%"))
                 (comp-defgeneric-body1 (cdr x) env))))

    ;;has after-qualifier?
    (defun has-after-qualifier-p (next-method)
        (cond ((null next-method) nil)
              (t
               (let* ((priority (eisl-get-method-priority (car next-method))))
                   (if (or (= priority befor) (= priority after))
                       t
                       (has-after-qualifier-p (cdr next-method)))))))

    (defun has-multiple-call-next-method-p (x)
        (let ((count 0)
              (ls x) )
           (block call
              (while (not (null ls))
                 (if (has-multiple-call-next-method-p1 (car ls))
                     (setq count (+ count 1)))
                 (if (has-multiple-call-next-method-p2 (car ls))
                     (return-from call t))
                 (setq ls (cdr ls)))
              (if (>= count 2)
                  t
                  nil))))

    (defun has-multiple-call-next-method-p1 (x)
        (cond ((null x) nil)
              ((and (symbolp x) (eq x 'call-next-method)) t)
              ((atom x) nil)
              ((or (has-multiple-call-next-method-p1 (car x))
                   (has-multiple-call-next-method-p1 (cdr x)))
               t)
              (t nil)))

    ;;e.g. (list (call-next-method) (call-next-method))
    (defun has-multiple-call-next-method-p2 (x)
        (cond ((atom x) nil)
              (t
               (let ((count 0)
                     (ls x) )
                  (while (not (null ls))
                     (if (has-multiple-call-next-method-p1 (car ls))
                         (setq count (+ count 1)))
                     (setq ls (cdr ls)))
                  (if (>= count 2)
                      t
                      nil)))))

    

    (defun comp-call-next-method (stream env args tail name global test clos)
        (format stream "({int res;")
        (let ((save1 rest-method)
              (save2 caller-priority) )
           (if (not (null rest-method))
               (setq rest-method (cdr rest-method)))
           (comp-call-next-method-set-original-argument stream env args tail name global test clos)
           (comp-call-next-method1 stream env args tail name global test clos)
           (comp-call-next-method-restore-argument stream env args tail name global test clos)
           (format stream "res;})~%")
           (if multiple-call-next-method
               (setq rest-method save1))
           (setq caller-priority save2)))

    ;;when (call-next-method) call, argument must be original parameter
    (defun comp-call-next-method-set-original-argument (stream env args tail name global test clos)
        (if (not clos)
            (for ((ls1 (remove '&rest (remove ':rest generic-args)) (cdr ls1)))
                 ((null ls1)
                  t )
                 (format stream "Fpargpush(~A,th);~%" (conv-name (car ls1)))
                 (format stream "~A = ~Acopy;~%" (conv-name (car ls1)) (conv-name (car ls1))))
            nil))

    (defun comp-call-next-method-restore-argument (stream env args tail name global test clos)
        (if (not clos)
            (for ((ls1 (reverse (remove '&rest (remove ':rest generic-args)))
                      (cdr ls1)))
                 ((null ls1)
                  t )
                 (format stream "~A = Fpargpop(th);~%" (conv-name (car ls1))))
            nil))

    

    (defglobal rest-method nil)
    (defglobal method-args nil)
    (defglobal generic-args nil)
    (defglobal caller-priority nil)
    (defglobal multiple-call-next-method nil)
    (defun comp-call-next-method1 (stream env args tail name global test clos)
        (cond ((null rest-method) t)
              (t
               (let* ((varbody (eisl-get-method-body (car rest-method)))
                      (varlis (alpha-conv-varlis (car varbody) generic-args))
                      (body
                      (alpha-conv-method (cdr varbody)
                                         (method-varlis-to-substlist (car varbody) generic-args)))
                      (priority (eisl-get-method-priority (car rest-method)))
                      (save caller-priority) )
                   ;; if parameter of next-method is subclass of method-args, ignore this next-method 
                   (cond ((not (eisl-superp-for-compiler varlis method-args))
                          (setq rest-method (cdr rest-method))
                          (comp-call-next-method1 stream env args tail name global test clos))
                         (t (setq caller-priority priority)
                            (format stream "if(")
                            (comp-defgeneric-qualifier-cond
                             varlis
                             stream
                             env
                             args
                             tail
                             name
                             global
                             test
                             clos)
                            (format stream ")~%{")
                            (comp-call-next-method2 body
                                                    (varlis-to-lambda-args varlis)
                                                    stream
                                                    env
                                                    args
                                                    tail
                                                    name
                                                    global
                                                    test
                                                    clos)
                            (format stream "};~%")
                            (setq caller-priority save)
                            ;; if next-method is primary then end, else generate rest-methods
                            (if (and (= caller-priority around) (not (null rest-method)))
                                (progn (setq rest-method (cdr rest-method))
                                       (comp-call-next-method1
                                        stream
                                        env
                                        args
                                        tail
                                        name
                                        global
                                        test
                                        clos)))))))))

    (defun comp-call-next-method2 (body para stream env args tail name global test clos)
        (cond ((null body) t)
              (t (format stream "res = ")
                 (comp stream
                       (car body)
                       para
                       generic-args
                       tail
                       name
                       global
                       test
                       clos)
                 (if (not (not-need-colon-p (car body)))
                     (format stream ";~%"))
                 (comp-call-next-method2 (cdr body)
                                         para
                                         stream
                                         env
                                         args
                                         tail
                                         name
                                         global
                                         test
                                         clos))))

    (defun comp-next-method-p (stream env args tail name global test clos)
        (if (comp-next-method-p1 rest-method)
            (format stream "T")
            (format stream "NIL")))

    (defun comp-next-method-p1 (next-method)
        (cond ((null next-method) nil)
              (t
               (let* ((varbody (eisl-get-method-body (car next-method)))
                      (varlis (alpha-conv-varlis (car varbody) generic-args)) )
                   (if (eisl-superp-for-compiler varlis method-args)
                       t
                       (comp-next-method-p1 (cdr next-method)))))))

    

    ;; ((x <integer>) (y <integer>)) (a b) -> ((a <integer>) (b <integer>))
    ;; ((x <integer>) y) (a b) -> ((a <integer>) b)
    (defun alpha-conv-varlis (x y)
        (cond ((null x) nil)
              ((symbolp (car x)) (cons (car y) (alpha-conv-varlis (cdr x) (cdr y))))
              (t (cons (list (car y) (elt (car x) 1))
                       (alpha-conv-varlis (cdr x) (cdr y))))))

    

    ;; ((x <integer>) (y <integer>)) (a b) -> ((x . a) (y . b))
    ;; ((x <integer>) y) (a b) -> ((x . a) (y . b))
    (defun method-varlis-to-substlist (x y)
        (cond ((null x) nil)
              ((symbolp (car x))
               (cons (cons (car x) (car y))
                     (method-varlis-to-substlist (cdr x) (cdr y))))
              (t (cons (cons (car (car x)) (car y))
                       (method-varlis-to-substlist (cdr x) (cdr y))))))

    ;; (COND ((= N 1) 1) ((= N 2) 1) (T (+ (GFIB (- N 1)) (GFIB (- N 2)))))) ((n . a)) -> 
    ;; (COND ((= a 1) 1) ((= a 2) 1) (T (+ (GFIB (- a 1)) (GFIB (- a 2))))))
    (defun alpha-conv-method (x y)
        (cond ((null x) nil)
              ((and (symbolp x) (alpha-var x y)) (alpha-var x y))
              ((atom x) x)
              (t (cons (alpha-conv-method (car x) y)
                       (alpha-conv-method (cdr x) y)))))

    ;; if x is alpha-conv variable substitute 
    ;; else return nil
    ;; x ((x . a)) -> a
    ;; y ((x . a)) -> nil
    (defun alpha-var (x y)
        (cond ((null y) nil)
              ((eq x (car (car y))) (cdr (car y)))
              (t (alpha-var x (cdr y)))))

    ;;varlis -> C condition
    (defun comp-defgeneric-qualifier-cond (x stream env args tail name global test clos)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ;;when method has only one symbol argument, require "1"
              ((symbolp (car x))
               (format stream "1")
               (comp-defgeneric-qualifier-cond (cdr x) stream env args tail name global test clos))
              ((consp (car x))
               (format stream "Fadaptp(")
               (comp stream
                     (elt (car x) 0)
                     env
                     args
                     tail
                     name
                     global
                     test
                     clos)
               (format stream ",Fmakesym(\"~A\"))" (elt (car x) 1))
               (comp-defgeneric-qualifier-cond1 (cdr x) stream env args tail name global test clos))
              (t (error* "defgeneric" x))))

    ;; generate Fadapt(P1) && Fadapt(P2) ... && Fadapt(Pn)  P is each parameter
    ;; Fadaptp check sameclass or superclass.
    (defun comp-defgeneric-qualifier-cond1 (x stream env args tail name global test clos)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ((symbolp (car x))
               (comp-defgeneric-qualifier-cond1 (cdr x) stream env args tail name global test clos))
              ((consp (car x))
               (format stream " && Fadaptp(")
               (comp stream
                     (elt (car x) 0)
                     env
                     args
                     tail
                     name
                     global
                     test
                     clos)
               (format stream ",Fmakesym(\"~A\"))" (elt (car x) 1))
               (comp-defgeneric-qualifier-cond1 (cdr x) stream env args tail name global test clos))
              (t (error* "defgeneric" x))))

    ;;generate Feqlassp(P1) && Fmatchp(P2) ... && Fmatchp(Pn)
    ;; Feqlassp check has equal same class.
    (defun comp-defgeneric-primary-cond (x stream env args tail name global test clos)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ;;when method has only one symbol argument, require "1"
              ((symbolp (car x))
               (format stream "1")
               (comp-defgeneric-primary-cond1 (cdr x) stream env args tail name global test clos))
              ((consp (car x))
               (format stream "Fmatchp(")
               (comp stream
                     (elt (car x) 0)
                     env
                     args
                     tail
                     name
                     global
                     test
                     clos)
               (format stream ",Fmakesym(\"~A\"))" (elt (car x) 1))
               (comp-defgeneric-primary-cond1 (cdr x) stream env args tail name global test clos))
              (t (error* "defgeneric" x))))

    (defun comp-defgeneric-primary-cond1 (x stream env args tail name global test clos)
        (cond ((null x) t)
              ((eq (car x) ':rest) t)
              ((eq (car x) '%rest) t)
              ((symbolp (car x))
               (comp-defgeneric-primary-cond1 (cdr x) stream env args tail name global test clos))
              ((consp (car x))
               (format stream " && Fmatchp(")
               (comp stream
                     (elt (car x) 0)
                     env
                     args
                     tail
                     name
                     global
                     test
                     clos)  
               (format stream ",Fmakesym(\"~A\"))" (elt (car x) 1))
               (comp-defgeneric-primary-cond1 (cdr x) stream env args tail name global test clos))
              (t (error* "defgeneric" x))))

    ;;generate define code
    (defun comp-defun3 (x)
        (let ((name (elt x 1)))
           (format code3 "(deftfunc)(\"~A\" , f_~A);~%" name (conv-name name))))

    (defun comp-lambda3 (name)
        (format code3 "(deftfunc)(\"~A\" , f_~A);~%" name (conv-name name)))

    (defun comp-defgeneric3 (x)
        (let* ((name0 (elt x 1))
               (name (if (listp name0)
                        (elt name0 1)
                        name0)) )
            (format code3 "(deftfunc)(\"~A\" , f_~A);~%" name (conv-name name))))

    ;; int arg1,arg2...argn;
    (defun gen-arg1 (n)
        (unless (= n 0)
                (format code1 "int ")
                (for ((m 1 (+ m 1)))
                     ((= m n)
                      (format code1 "arg~A;~%" m))
                     (format code1 "arg~A," m))))

    ;; (x y z) -> (int x, int y, int z, int th)
    ;; (x y :rest z) -> (int x, int y, int z, int th)
    ;; output to stream of string
    (defun gen-arg2 (stream ls)
        (format stream "(")
        (if (null ls)
            (format stream "int th)")
            (for ((ls1 (remove '&rest (remove ':rest ls)) (cdr ls1)))
                 ((null (cdr ls1))
                  (format stream "int ~A, int th)" (conv-name (car ls1))))
                 (format stream "int ~A," (conv-name (car ls1))))))

    ;;for generic-function (call-next-method)
    ;;make copy original arguments. (call-next-method) uses this copy 
    (defun gen-arg2-copy (stream ls)
        (for ((ls1 (remove '&rest (remove ':rest ls)) (cdr ls1)))
             ((null ls1)
              t )
             (format stream "int ~Acopy = ~A;~%" (conv-name (car ls1)) (conv-name (car ls1)))))

    ;; int temp1,temp2...tempn.tempn+1,tempn+2;
    ;; Since the number of arguments for tail is unknown 
    ;; when args includes rest parameters, 
    ;; compiler define two additional arguments as a precaution.
    (defun gen-arg3 (n)
        (unless (= n 0)
                (format code2 "int ")
                (for ((m 1 (+ m 1)))
                     ((= m (+ n 2)) ;see comment
                      (format code2 "temp~D;~%" m))
                     (format code2 "temp~D," m))))

    ;;arg1 = Fnth(1,arglist);
    ;;arg2 = Fnth(2,arglist);
    ;;when :rest parameter argn = Fnthcdr(n,arglist);
    (defun gen-assign (n)
        (cond ((= n 0) t)
              ((< n 0)
               (for ((m 1 (+ m 1)))
                    ((= m (abs n))
                     (format code1 "arg~D = Fnthcdr(~D,arglist);~%" m (- m 1)))
                    (format code1 "arg~D= Fnth(~D,arglist);~%" m (- m 1))))
              (t
               (for ((m 1 (+ m 1)))
                    ((> m n)
                     t )
                    (format code1 "arg~D = Fnth(~D,arglist);~%" m (- m 1))))))

    ;;(foo arg1 arg2) ->
    ;;  return(foo(arg1,arg2,0));
    (defun gen-call (name n)
        (cond ((= n 0)
               (format code1 "return(~A(th) );~%" name))
              (t (format code1 "return(~A(" name)
                 (for ((m 1 (+ m 1)))
                      ((= m n)
                       (format code1 "arg~D,th));~%" m))
                      (format code1 "arg~D," m)))))

    ;; args = (x)
    ;; if(CELLRANGE(x)) Fshelterpush(x)
    (defun gen-shelterpush (stream ls)
        (unless (null ls)
                (for ((ls1 (remove ':rest (remove '&rest ls)) (cdr ls1)))
                     ((null ls1)
                      t )
                     (format stream "if(CELLRANGE(~A)) Fpshelterpush(~A,th);~%"
                           (conv-name (car ls1)) (conv-name (car ls1))))))

    ;; args = (x)
    ;; if(CELLRANGE(x)) Fshelterpop(x)
    (defun gen-shelterpop (stream ls)
        (unless (null ls)
                (for ((ls1 (remove ':rest (remove '&rest ls)) (cdr ls1)))
                     ((null ls1)
                      t )
                     (format stream "if(CELLRANGE(~A)) ~A=Fpshelterpop(th);~%" 
                        (conv-name (car ls1)) (conv-name (car ls1))))))
                     

    ;;Fcheckgbc();
    (defun gen-checkgc ()
        (format code2 "Fcheckgbc(th);~%"))

    (defun comp-if (stream x env args tail name global test clos)
        (unless (or (= (length x) 3) (= (length x) 4))
                (error* "if: illegal form" x))
        (cond ((= (length x) 3)
               (format stream "({int res;~%if(")
               (comp stream (elt x 1) env args tail name global t clos)
               (if (not optimize-enable)
                   (format stream " != NIL){~%")
                   (format stream "){~%"))
               (if (and (not (not-need-res-p (elt x 2)))
                        ;;if cond etc ...
                        (not (tailcallp (elt x 2) tail name)))
                   ;;tail recur
                   (format stream "res = "))
               (comp stream (elt x 2) env args tail name global test clos)
               (format stream ";}~% else res = NIL;res;})~%"))
              ((= (length x) 4)
               (format stream "({int res;~%if(")
               (comp stream (elt x 1) env args tail name global t clos)
               (if (not optimize-enable)
                   (format stream " != NIL){~%")
                   (format stream "){~%"))
               (if (and (not (not-need-res-p (elt x 2)))
                        ;;if cond etc ...
                        (not (tailcallp (elt x 2) tail name)))
                   ;;tail recur
                   (format stream "res = "))
               (comp stream (elt x 2) env args tail name global test clos)
               (format stream ";}~%")
               (format stream "else{~%")
               (if (and (not (not-need-res-p (elt x 3)))
                        (not (tailcallp (elt x 3) tail name)))
                   (format stream "res = "))
               (comp stream (elt x 3) env args tail name global test clos)
               (format stream ";}res;})~%"))))

    ;;two arguments numeric function ex (= x y) etc...
    (defun comp-numeric (stream x env args tail name global test clos)
        (cond ((not optimize-enable)
               (cond ((eq (elt x 0) 'eq) (format stream "fast_eq("))
                     ((eq (elt x 0) '=) (format stream "fast_numeqp("))
                     ((eq (elt x 0) '<) (format stream "fast_smallerp("))
                     ((eq (elt x 0) '<=) (format stream "fast_eqsmallerp("))
                     ((eq (elt x 0) '>) (format stream "fast_greaterp("))
                     ((eq (elt x 0) '>=) (format stream "fast_eqgreaterp("))
                     ((eq (elt x 0) '+) (format stream "fast_plus("))
                     ((eq (elt x 0) '-) (format stream "fast_minus("))
                     ((eq (elt x 0) '*) (format stream "fast_mult("))
                     ((eq (elt x 0) 'mod) (format stream "fast_mod(")))
               (comp stream (elt x 1) env args nil name global test clos)
               (format stream ",")
               (comp stream (elt x 2) env args nil name global test clos)
               (format stream ")"))
              (t (comp stream (elt x 1) env args nil name global test clos)
                 (cond ((eq (elt x 0) 'eq) (format stream "=="))
                       ((eq (elt x 0) '=) (format stream "=="))
                       ((eq (elt x 0) '<) (format stream "<"))
                       ((eq (elt x 0) '<=) (format stream "<="))
                       ((eq (elt x 0) '>) (format stream ">"))
                       ((eq (elt x 0) '>=) (format stream ">="))
                       ((eq (elt x 0) '+) (format stream "+"))
                       ((eq (elt x 0) '-) (format stream "-"))
                       ((eq (elt x 0) '*) (format stream "*"))
                       ((eq (elt x 0) 'mod) (format stream "%")))
                 (comp stream (elt x 2) env args nil name global test clos))))

    ;; (foo x y z) -> foo(x,y,z)
    (defun comp-funcall (stream x env args tail name global test clos)
        (cond ((and tail (eq (car x) name))
               ;;tail call
               (comp-funcall1 stream x env args tail name global test clos))
              ((not (assoc (car x) function-arg))
               ;;interpreter
               (comp-funcall2 stream x env args tail name global test clos))
              (clos
               ;;has free variable
               (format stream "res=")
               (comp-funcall-clang-left-to-right stream x env args tail name global test clos))
              ((null (cdr x))
               ;;thunk
               (unless (= (cdr (assoc (car x) function-arg)) 0)
                       (error* "call: illegal argument count" x))
               (format stream "~A(th)" (conv-name (car x))))
              (optimize-enable (comp-funcall-clang stream x env args tail name global test clos))
              (t (comp-funcall-clang-left-to-right stream x env args tail name global test clos))))

    (defun comp-funcall-clang-left-to-right (stream x env args tail name global test clos)
        (let ((n (cdr (assoc (car x) function-arg))))
           (when (and (> n 0) (/= (length (cdr x)) n))
                 (error* "call: illegal arument count" x))
           (cond ((null (cdr x)) (format stream "({int res;"))
                 (t (format stream "({int ")
                    (for ((ls (cdr x) (cdr ls))
                          (m 1 (+ m 1)) )
                         ((null ls)
                          t )
                         (format stream "arg~D," m))
                    (format stream "res;~%")
                    (for ((ls (cdr x) (cdr ls))
                          (m 1 (+ m 1)) )
                         ((null ls)
                          t )
                         (format stream "arg~D = " m)
                         (comp stream (car ls) env args nil name global test clos)
                         (format stream ";~%"))))
           (format stream "res = ~A(" (conv-name (car x)))
           (comp-funcall-clang-left-to-right1 stream 1 n (length (cdr x)))
           (format stream ",th);~%")
           (format stream ";res;})")))

    (defun comp-funcall-clang-left-to-right1 (stream m n o)
        (cond ((>= n 0)
               (cond ((> m n))
                     ((= m n) (format stream "arg") (format-integer stream m 10))
                     (t (format stream "arg~D," m)
                        (comp-funcall-clang-left-to-right1 stream (+ m 1) n o))))
              (t
               (cond ((>= m (abs n)) (comp-funcall-clang-left-to-right2 stream m o))
                     (t (format stream "arg~D," m)
                        (comp-funcall-clang-left-to-right1 stream (+ m 1) n o))))))

    (defun comp-funcall-clang-left-to-right2 (stream m n)
        (cond ((> m n) (format stream "NIL"))
              (t (format stream "Fcons(arg~D," m)
                 (comp-funcall-clang-left-to-right2 stream (+ m 1) n)
                 (format stream ")"))))

    
    ;; if optimize-enable funcall is like C function call
    ;; e.g. (foo x) -> foo(x,th)
    (defun comp-funcall-clang (stream x env args tail name global test clos)
        (let ((n (cdr (assoc (car x) function-arg))))
           (when (and (> n 0) (/= (length (cdr x)) n))
                 (error* "call: illegal arument count" x))
           (cond ((> n 0)
                  (format stream "~A(" (conv-name (car x)))
                  (for ((ls (cdr x) (cdr ls)))
                       ((null (cdr ls))
                        (comp stream (car ls) env args nil name global test clos)
                        (format stream ",th)") )
                       (comp stream (car ls) env args nil name global test clos)
                       (format stream ",")))
                 (t (format stream "~A(" (conv-name (car x)))
                    (for ((ls (cdr x) (cdr ls))
                          (m (abs n) (- m 1)) )
                         ((= m 1)
                          (comp-funcall-clang1 stream ls env args nil name global test clos)
                          (format stream ",th)") )
                         (comp stream (car ls) env args nil name global test clos)
                         (format stream ","))))))

    (defun comp-funcall-clang1 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-funcall-clang1 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))

    

    ;;tail recurcive function call
    ;;{temp1=...; temp2=...; ... x=temp1;y=temp2; goto NAMEloop;}
    (defun comp-funcall1 (stream x env args tail name global test clos)
        (let ((n (cdr (assoc (car x) function-arg))))
           (format stream "{~%")
           (for ((ls (cdr x) (cdr ls))
                 (m 1 (+ m 1)) )
                ((null ls)
                 t )
                (format stream "temp~D = " m)
                (comp stream (car ls) env args nil name global test clos)
                (format stream ";~%"))
           (if (not optimize-enable)
               (gen-shelterpop stream args))
           (cond ((>= n 0)
                  (for ((ls args (cdr ls))
                        (m 1 (+ m 1)) )
                       ((null ls)
                        t )
                       (format stream "~A = temp~D;~%" (conv-name (car ls)) m)
                       (format-integer stream m 10)
                       (format stream ";~%"))
                  (format stream "goto ~Aloop;}" (conv-name name)))
                 (t (for ((ls (remove ':rest (remove '&rest args)) (cdr ls))
                          (m 1 (+ m 1)) )
                         ((>= m (abs n))
                          (format stream "~A = " (conv-name (car ls)))
                          (comp-funcall11 stream m (length (cdr x)))
                          (format stream ";~%") )
                         (format stream "~A = temp~D;~%" (conv-name (car ls)) m))
                    (format stream "goto ~Aloop;}" (conv-name name))))))

    ;;tail call with rest parameter
    (defun comp-funcall11 (stream m n)
        (cond ((> m n) (format stream "NIL"))
              (t (format stream "Fcons(temp~D," m)
                 (comp-funcall11 stream (+ m 1) n)
                 (format stream ")"))))

    ;;funcall for not SUBR function.
    ;;apply(func,args)
    (defun comp-funcall2 (stream x env args tail name global test clos)
        (format stream "Fpapply(Fcar(Fmakesym(\"~A\"))," (car x))
        (comp-funcall3 stream (cdr x) env args nil name global test clos)
        (format stream ",th)"))

    (defun comp-funcall3 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              ((null (cdr x))
               (format stream "Flist1(")
               (comp stream (car x) env args nil name global test clos)
               (format stream ")"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args nil name global test clos)
                 (format stream ",")
                 (comp-funcall3 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))

    ;;SUBR call
    (defun comp-subrcall (stream x env args tail name global test clos)
        (if (simple-subrcall-p (cdr x))
            (comp-subrcall1 stream x env args tail name global test clos)
            (comp-subrcall2 stream x env args tail name global test clos)))

    ;;Simple subrcall arguments are all subr or atom
    (defun comp-subrcall1 (stream x env args tail name global test clos)
        (format stream "Fpcallsubr(Fcar(Fmakesym(\"~A\"))," (car x))
        (comp-funcall3 stream (cdr x) env args nil name global test clos)
        (format stream ",th)~%"))

    ;;Not tail call subr.To avoid data loss by GC, push each data to shelter
    ;; ({int arg1,...,argn,res;
    ;;   arg1 = code1;
    ;;   Fshelterpush(arg1);
    ;;   ...
    ;;   argn = coden;
    ;;   Fshelterpush(argn);
    ;;   res = fcallsubr(_,arg1,...arg2);
    ;;   argn = Fshelterpop();
    ;;   ...
    ;;   arg1 = Fshelterpop();
    ;;   res;})
    ;; 
    (defun comp-subrcall2 (stream x env args tail name global test clos)
        (cond ((null (cdr x)) (format stream "({int res;"))
              (t (format stream "({int ")
                 (for ((ls (cdr x) (cdr ls))
                       (n 1 (+ n 1)) )
                      ((null ls)
                       t )
                      (format stream "arg~D," n))
                 (format stream "res;~%")
                 (for ((ls (cdr x) (cdr ls))
                       (n 1 (+ n 1)) )
                      ((null ls)
                       t )
                      (format stream "arg~D = " n)
                      (comp stream (car ls) env args nil name global test clos)
                      (format stream ";~%")
                      (format stream "Fpshelterpush(arg~D,th);~%" n))))
        (format stream "res = Fpcallsubr(Fcar(Fmakesym(\"~A\"))," (car x))
        (comp-subrcall3 stream 1 (length (cdr x)))
        (format stream ",th);~%")
        (cond ((not (null (cdr x)))
               (for ((ls (cdr x) (cdr ls))
                     (n (length (cdr x)) (- n 1)) )
                    ((null ls)
                     t )
                    (format stream "arg~A=Fpshelterpop(th);~%" n))))
        (format stream ";res;})"))

    (defun comp-subrcall3 (stream m n)
        (cond ((> m n) (format stream "NIL"))
              ((= m n)
               (format stream "Flist1(arg~D)" m))
              (t (format stream "Fcons(arg~D," m)
                 (comp-subrcall3 stream (+ m 1) n)
                 (format stream ")"))))

    (defun simple-subrcall-p (x)
        (cond ((null x) t)
              ((and (consp (car x)) (subrp (car (car x)))) (simple-subrcall-p (cdr x)))
              ((atom (car x)) (simple-subrcall-p (cdr x)))
              (t nil)))

    ;;; alpha convert before labels
    (defun comp-flet (stream x env args tail name global test clos)
        (comp-labels stream (comp-flet1 x) env args tail name global test clos))

    ;; if body is nested (flet ...) 
    (defun comp-flet1 (x)
        (if (eq (car (elt x 2)) 'flet)
            (comp-flet2 x)
            x))

    ;; (flet ((f (x)
    ;;           (+ x 3) ))
    ;;    (flet ((f (x)
    ;;               (+ x (f x)) ))
    ;;        (f x)))
    ;;       | convert
    ;;       v
    ;; (flet ((f (x)
    ;;           (+ x 3) ))
    ;;    (flet ((fsubst (x)
    ;;               (+ x (f x)) ))
    ;;        (fsubst x)))
    (defun comp-flet2 (x)
        (let* ((nest (elt x 2))
               (forms (elt nest 1))
               (fn1 (mapcar #'car forms))
               (fn2 (subst fn1))
               (forms1 (mapcar (lambda (x y) (cons x (cdr y))) fn2 forms))
               (end (alpha-conv (elt nest 2) fn1 fn2)) )
            (list (elt x 0) (elt x 1) (list (elt nest 0) forms1 end))))

    ;;labels syntax. flet syntax is same as labels
    (defun comp-labels (stream x env args tail name global test clos)
        (format stream "({int res;")
        (comp-labels1 stream (elt x 1) env args tail name global test clos)
        (for ((body1 (cdr (cdr x)) (cdr body1)))
             ((null body1)
              (format stream ";res;})~%")
              (setq function-arg (drop (length (elt x 1)) function-arg)) )
             (if (not (not-need-res-p (car body1)))
                 (format stream "res = "))
             (comp stream (car body1) env args tail name global test clos)
             (format stream "~%")))

    (defun comp-labels1 (stream x env args tail name global test clos)
        (cond ((null x) t)
              (t (comp-labels2 stream (car x) env args tail name global test clos)
                 (comp-labels1 stream (cdr x) env args tail name global test clos))))

    (defun comp-labels2 (stream x env args tail name global test clos)
        (when (< (length x) 3) (error* "labels: illegal form" x))
        (unless (symbolp (elt x 0))
                (error* "labels: not symbol" (elt x 0)))
        (unless (listp (elt x 1)) (error* "labels: not list" (elt x 1)))
        (when (null (cdr (cdr x))) (error* "labels: not exist body" x))
        (let ((local-name (elt x 0))
              (args (elt x 1))
              (body (cdr (cdr x))) )
           (setq function-arg
                 (cons (cons local-name (count-args args)) function-arg))
           (format code2 "int ")
           (format-object code2 (conv-name local-name) nil)
           (if (not optimize-enable)
               (gen-arg2 code2 args)
               (type-gen-arg2 code2 args (local-argument-type name local-name)))
           (format code2 "{~%")
           (format code2 "int res;~%")
           (cond ((and (not optimize-enable) (has-tail-recur-p body local-name))
                  ;;for tail recursive tempn var;
                  (gen-arg3 (length args)))
                 ((and optimize-enable (has-tail-recur-p body local-name))
                  (type-gen-arg3 (length args) (local-argument-type name local-name))))
           (cond ((has-tail-recur-p body local-name)
                  (format-object code2 (conv-name local-name) nil)
                  (format code2 "loop:~%")))
           (cond ((not optimize-enable) (gen-shelterpush code2 args) (gen-checkgc)))
           (for ((body1 body (cdr body1)))
                ((null body1)
                 (if (not optimize-enable)
                    (gen-shelterpop code2 (reverse args)))
                 (format code2 "return(res);}~%") )
                (if (not (not-need-res-p (car body1)))
                    (format code2 "res = "))
                (comp code2
                      (car body1)
                      (append args env)
                      args
                      tail
                      name
                      global
                      test
                      clos)
                (format code2 ";~%"))))

    (defun comp-let (stream x env args tail name global test clos)
        (unless (listp (elt x 1)) (error* "let: not list" (elt x 1)))
        (format stream "({int res;")
        (comp-let1 stream (elt x 1) env args tail name global test clos)
        (for ((body1 (cdr (cdr x)) (cdr body1)))
             ((null (cdr body1))
              (if (and (not (tailcallp (car body1) tail name))
                      (not (not-need-res-p (car body1))))
                 (format stream "res = "))
              (comp stream
                   (car body1)
                   (append (mapcar #'car (elt x 1)) env)
                   args
                   tail
                   name
                   global
                   test
                   clos)
              (if (not (not-need-colon-p (car body1)))
                 (format stream ";~%"))
              (format stream "res;})~%") )
             (comp stream
                   (car body1)
                   (append (mapcar #'car (elt x 1)) env)
                   args
                   tail
                   name
                   global
                   test
                   clos)
             (if (not (not-need-colon-p (car body1)))
                 (format stream ";~%"))))

    (defun comp-let* (stream x env args tail name global test clos)
        (unless (listp (elt x 1)) (error* "let*: not list" (elt x 1)))
        (format stream "({int res;")
        (comp-let1 stream
                   (elt x 1)
                   (append (mapcar #'car (elt x 1)) env)
                   args
                   tail
                   name
                   global
                   test
                   clos)
        (for ((body1 (cdr (cdr x)) (cdr body1)))
             ((null (cdr body1))
              (if (and (not (tailcallp (car body1) tail name))
                      (not (not-need-res-p (car body1))))
                 (format stream "res = "))
              (comp stream
                   (car body1)
                   (append (mapcar #'car (elt x 1)) env)
                   args
                   tail
                   name
                   global
                   test
                   clos)
              (if (not (not-need-colon-p (car body1)))
                 (format stream ";~%"))
              (format stream "res;})~%") )
             (comp stream
                   (car body1)
                   (append (mapcar #'car (elt x 1)) env)
                   args
                   tail
                   name
                   global
                   test
                   clos)
             (if (not (not-need-colon-p (car body1)))
                 (format stream ";~%"))))

    (defun comp-mt-let (stream x env args tail name global test clos)
        (format stream "({int num[PARASIZE];")
        (let ((env1 (comp-mt-let1 stream x env args tail name global test clos)))
            (comp-progn1 stream (cdr (cdr x)) (append env1 env) args tail name global test clos))
        (format stream "res;})"))
        
    (defun comp-mt-let1 (stream x env args tail name global test clos)
        ;; eval_para
        (for ((arg1 (elt x 1) (cdr arg1))
              (num 0 (+ num 1)))
             ((null arg1) nil)
             ;;num[N] = Fcons(Fmakesym(function-sym),FlistM(arg1,arg2,...argM));
             (format stream "num[~D] = Feval_para(Fcons(Fmakesym(\"~A\")," num (car (elt (car arg1) 1)))
             (comp-argument stream (cdr (elt (car arg1) 1)) 0 (car (elt (car arg1) 1)) env args tail name global test clos)
             (format stream "));~%"))     
        ;; wait
        (format stream "Fwait_para();~%")     
        ;; var = Fget_para_output(N);
        (for ((arg1 (elt x 1) (cdr arg1))
              (num 0 (+ num 1)))
             ((null arg1) nil)
             (format stream "int ~A = Fget_para_output(num[~D]);~%" (elt (elt arg1 0) 0) num)) 
        (mapcar (lambda (y) (car y)) (elt x 1))) 

    (defun comp-mt-call (stream x env args tail name global test clos)
        (format stream "({int num[PARASIZE];")
        (comp-mt-call1 stream x env args tail name global test clos)
        (format stream "res;})"))
    

    (defun comp-mt-call1 (stream x env args tail name global test clos)
        ;; eval_para
        (for ((arg1 (cdr (cdr x)) (cdr arg1))
              (num 0 (+ num 1)))
             ((null arg1) nil)
             ;;num[N] = Fcons(Fmakesym(function-sym),Fcons(arg1,Fcons(arg2,...NIL));
             (format stream "num[~D] = Feval_para(Fcons(Fmakesym(\"~A\")," num (car (car arg1)))
             (comp-argument stream (cdr (car arg1)) 0 (car (car arg1)) env args tail name global test clos)
             (format stream "));~%"))        
        ;; wait
        (format stream "Fwait_para();~%")
        ;; TEMP0 = Fget_para_output(0); TEMP1 = Fget_para_output(1); ...
        ;; if function of argument is optimizable, convert data.
        (for ((argument (cdr (cdr x)) (cdr argument))
              (num 0 (+ num 1)))
             ((null argument) (format stream "~%"))
             (cond ((not (eq (car (car argument)) optimize-enable))
                    (format stream "int TEMP~D = Fget_para_output(num[~D]);" num num))
                   ((eq (return-type (car (car argument))) (class <fixnum>))
                    (format stream "int TEMP~D = Fgetint(Fget_para_output(num[~D]));" num num))
                   ((eq (return-type (car (car argument))) (class <float>))
                    (format stream "int TEMP~D = Fgetflt(Fget_para_output(num[~D]));" num num))))
        ;; res = comp((fun temp0 temp1 ... tempn));
        (let ((argument '(temp0 temp1 temp2 temp3 temp4 temp5 temp6 temp7)))
            (format stream "res = ")
            (comp stream (cons (elt (elt x 1) 1) (take (length (cdr (cdr x))) argument))
                  (append argument env) args nil name global test clos)
            (format stream ";~%")))

    (defun comp-mt-exec (stream x env args tail name global test clos)
        (format stream "({int num[PARASIZE];")
        (comp-mt-exec1 stream x env args tail name global test clos)
        (format stream "res;})"))
    

    (defun comp-mt-exec1 (stream x env args tail name global test clos)
        ;; eval_para
        (for ((arg1 (cdr x) (cdr arg1))
              (num 0 (+ num 1)))
             ((null arg1) nil)
             ;;num[N] = Fcons(Fmakesym(function-sym),Fcons(arg1,Fcons(arg2,...argM)));
             (format stream "num[~D] = Feval_para(Fcons(Fmakesym(\"~A\")," num (car (car arg1)))
             (comp-argument stream (cdr (car arg1)) 0 (car (car arg1)) env args tail name global test clos)
             (format stream "));~%"))        
        ;; wait
        (format stream "Fwait_para();~%")
        ;; result
        (format stream "res = Fget_para_output(num[~D]);~%" (- (length (cdr x)) 1)))

    (defun comp-argument (stream x argnum fun env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              ((not (eq fun optimize-enable))
               (format stream "Fcons(")
               (comp stream (car x) env args tail name global test clos)
               (format stream ",")
               (comp-argument stream (cdr x) (+ argnum 1) fun env args tail name global test clos)
               (format stream ")")) 
              ((eq (elt (argument-type fun) argnum) (class <fixnum>))
               (format stream "Fcons(Fmakeint(" )
               (comp stream (car x) env args tail name global test clos)
               (format stream "),")
               (comp-argument stream (cdr x) (+ argnum 1) fun env args tail name global test clos)
               (format stream ")"))
              ((eq (elt (argument-type fun) argnum) (class <float>))
               (format stream "Fcons(Fmakedoubleflt(" )
               (comp stream (car arg2) env args tail name global test clos)
               (format stream "),")
               (comp-argument stream (cdr x) (+ argnum 1) fun env args tail name global test clos)
               (format stream ")"))))
    
    (defun comp-mp-call (stream x env args tail name global test clos)
        (format stream "({int res;")
        (comp-mp-call1 0 stream (cdr (cdr x)) env args tail name global test clos)
        (comp-mp-call3 stream (cdr x) env args tail name global test clos)
        (format stream "res;})"))

    ;; write to pipe
    (defun comp-mp-call1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fwrite_to_pipe(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-mp-call2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-mp-call1 (+ i 1) stream (cdr x) env args tail name global test clos))))
                 
    ;; eval args
    (defun comp-mp-call2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-mp-call2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))

    ;; apply received args
    (defun comp-mp-call3 (stream x env args tail name global test clos)
        (format stream "res=Fpapply(")
        (comp stream (car x) env args tail name global test clos)
        (format stream ",")
        (comp-mp-call4 stream 0 (length (cdr x)))
        (format stream ",0);"))
    
    ;; receive args from pipe
    (defun comp-mp-call4 (stream i n)
        (cond ((= i n) (format stream "NIL"))
              (t (format stream "Fcons(Fstr_to_sexp(Fread_from_pipe(~A))," i)
                 (comp-mp-call4 stream (+ i 1) n)
                 (format stream ")"))))

    (defun comp-mp-exec (stream x env args tail name global test clos)
        (format stream "({int res;")
        (comp-mp-exec1 0 stream (cdr x) env args tail name global test clos)
        (comp-mp-exec3 stream (cdr x) env args tail name global test clos)
        (format stream "res;})"))

    ;; write to pipe
    (defun comp-mp-exec1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fwrite_to_pipe(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-mp-exec2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-mp-exec1 (+ i 1) stream (cdr x) env args tail name global test clos))))

    ;; eval args
    (defun comp-mp-exec2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-mp-exec2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))


    ;; received args
    (defun comp-mp-exec3 (stream x env args tail name global test clos)
        (comp-mp-exec4 stream 0 (length x)))
    
    ;; receive args from pipe
    (defun comp-mp-exec4 (stream i n)
        (cond ((= i n) nil)
              (t (format stream "res=Fstr_to_sexp(Fread_from_pipe(~A));" i)
                 (comp-mp-exec4 stream (+ i 1) n))))

    (defun comp-mp-and (stream x env args tail name global test clos)
        (format stream "({int res;")
        (format stream "Fclear_child_signal();")
        (comp-mp-and1 0 stream (cdr x) env args tail name global test clos)
        (comp-mp-and3 stream (cdr x) env args tail name global test clos)
        (format stream "exit: Fkill_rest_process(~A);" (length (cdr x)))
        (format stream "res;})"))

    ;; write to pipe
    (defun comp-mp-and1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fwrite_to_pipe(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-mp-and2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-mp-and1 (+ i 1) stream (cdr x) env args tail name global test clos))))

    ;; eval args
    (defun comp-mp-and2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-mp-and2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))


    ;; received args
    (defun comp-mp-and3 (stream x env args tail name global test clos)
        (comp-mp-and4 stream 0 (length x)))
    
    ;; receive args from pipe(option=t)
    (defun comp-mp-and4 (stream i n)
        (cond ((= i n) nil)
              (t (format stream "res=Fstr_to_sexp(Fread_from_pipe_part(~A));" n)
                 (format stream "if(res != NIL) goto exit;")
                 (comp-mp-and4 stream (+ i 1) n))))

    (defun comp-mp-or (stream x env args tail name global test clos)
        (format stream "({int res;")
        (format stream "Fclear_child_signal();")
        (comp-mp-or1 0 stream (cdr x) env args tail name global test clos)
        (comp-mp-or3 stream (cdr x) env args tail name global test clos)
        (format stream "exit: Fkill_rest_process(~A);" (length (cdr x)))
        (format stream "res;})"))

    ;; write to pipe
    (defun comp-mp-or1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fwrite_to_pipe(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-mp-or2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-mp-or1 (+ i 1) stream (cdr x) env args tail name global test clos))))

    ;; eval args
    (defun comp-mp-or2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-mp-or2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))


    ;; received args
    (defun comp-mp-or3 (stream x env args tail name global test clos)
        (comp-mp-or4 stream 0 (length x)))
    
    ;; receive args from pipe(option=nil)
    (defun comp-mp-or4 (stream i n)
        (cond ((= i n) nil)
              (t (format stream "res=Fstr_to_sexp(Fread_from_pipe_part(~A));" n)
                 (format stream "if(res == NIL) goto exit;")
                 (comp-mp-or4 stream (+ i 1) n))))

    ;; receive args from pipe(option=t)
    (defun comp-mp-or5 (stream i n)
        (cond ((= i n) nil)
              (t (format stream "res=Fstr_to_sexp(Fread_from_pipe_part(~A));" n)
                 (format stream "if(res != NIL) goto exit;")
                 (comp-mp-or5 stream (+ i 1) n))))


    (defun comp-dp-call (stream x env args tail name global test clos)
        (format stream "({int res; Fclear_parent_buffer(~A);" (length x))
        (comp-dp-call1 0 stream (cdr (cdr x)) env args tail name global test clos)
        (format stream "Fwait_all(~A);" (length (cdr (cdr x))))
        (comp-dp-call3 stream (cdr x) env args tail name global test clos)
        (format stream "res;})"))

    ;; send to child
    (defun comp-dp-call1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fsend_to_child(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-dp-call2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-dp-call1 (+ i 1) stream (cdr x) env args tail name global test clos))))
                 
    ;; eval args
    (defun comp-dp-call2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-dp-call2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))

    ;; apply received args
    (defun comp-dp-call3 (stream x env args tail name global test clos)
        (format stream "res=Fpapply(")
        (comp stream (car x) env args tail name global test clos)
        (format stream ",")
        (comp-dp-call4 stream 0 (length (cdr x)))
        (format stream ",0);"))
    
    ;; receive args from child
    (defun comp-dp-call4 (stream i n)
        (cond ((= i n) (format stream "NIL"))
              (t (format stream "Fcons(Fstr_to_sexp(Freceive_from_child(~A))," i)
                 (comp-dp-call4 stream (+ i 1) n)
                 (format stream ")"))))

    (defun comp-dp-exec (stream x env args tail name global test clos)
        (format stream "({int res; Fclear_parent_buffer(~A);" (length x))
        (comp-dp-exec1 0 stream (cdr x) env args tail name global test clos)
        (format stream "Fwait_all(~A);" (length (cdr x)))
        (comp-dp-exec3 stream (cdr x) env args tail name global test clos)
        (format stream "res;})"))

    ;; send to child
    (defun comp-dp-exec1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fsend_to_child(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-dp-exec2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-dp-exec1 (+ i 1) stream (cdr x) env args tail name global test clos))))

    ;; eval args
    (defun comp-dp-exec2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-dp-exec2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))


    ;; received args
    (defun comp-dp-exec3 (stream x env args tail name global test clos)
        (comp-dp-exec4 stream 0 (length x)))
    
    ;; receive args from child
    (defun comp-dp-exec4 (stream i n)
        (cond ((= i n) nil)
              (t (format stream "res=Fstr_to_sexp(Freceive_from_child(~A));" i)
                 (comp-dp-exec4 stream (+ i 1) n))))

    (defun comp-dp-and (stream x env args tail name global test clos)
        (format stream "({int res; Fclear_parent_buffer(~A);" (length (cdr x)))
        (comp-dp-and1 0 stream (cdr x) env args tail name global test clos)
        (format stream "res = Fwait_and(~A); res;})" (length (cdr x))))


    ;; send to child
    (defun comp-dp-and1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fsend_to_child(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-dp-and2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-dp-and1 (+ i 1) stream (cdr x) env args tail name global test clos))))

    ;; eval args
    (defun comp-dp-and2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-dp-and2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))


     (defun comp-dp-or (stream x env args tail name global test clos)
        (format stream "({int res; Fclear_parent_buffer(~A);" (length (cdr x)))
        (comp-dp-or1 0 stream (cdr x) env args tail name global test clos)
        (format stream "res=Fwait_or(~A); res;})" (length (cdr x))))

    ;; send to child
    (defun comp-dp-or1 (i stream x env args tail name global test clos)
        (cond ((null x) nil)
              (t (format stream "Fsend_to_child(~A,Fsexp_to_str(Fcons(Fmakesym(\"~A\")," i (car (car x)))
                 (comp-dp-or2 stream (cdr (car x)) env args tail name global test clos)
                 (format stream ")));~%")
                 (comp-dp-or1 (+ i 1) stream (cdr x) env args tail name global test clos))))

    ;; eval args
    (defun comp-dp-or2 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "NIL"))
              (t (format stream "Fcons(")
                 (comp stream (car x) env args tail name global test clos)
                 (format stream ",")
                 (comp-dp-or2 stream (cdr x) env args tail name global test clos)
                 (format stream ")"))))


    (defun not-need-res-p (x)
        (and (consp x) (member (car x) not-need-res)))

    (defun not-need-colon-p (x)
        (and (consp x) (member (car x) not-need-colon)))

    (defun tailcallp (x tail name)
        (and tail (and (consp x) (eq (car x) name))))

    (defun comp-let1 (stream x env args tail name global test clos)
        (cond ((null x) t)
              (t (comp-let2 stream (car x) env args tail name global test clos)
                 (comp-let1 stream (cdr x) env args tail name global test clos))))

    (defun comp-let2 (stream x env args tail name global test clos)
        (unless (symbolp (elt x 0)) (error* "let: illegal let form" x))
        (format stream "int ")
        (format stream (convert (conv-name (elt x 0)) <string>))
        (format stream " = ")
        (comp stream (elt x 1) env args nil name global test clos)
        (format stream ";"))

    (defun comp-with-open-input-file (stream x env args tail name global test clos)
        (unless (listp (elt x 1))
                (error* "with-open-input-file: not list" (elt x 1)))
        (unless (symbolp (elt (elt x 1) 0))
                (error* "with-open-input-file: illegal file name" x))
        (format stream "({int res;")
        (format stream "int ")
        (format stream (convert (conv-name (elt (elt x 1) 0)) <string>))
        (format stream " = ")
        (comp stream
              (list 'open-input-file (elt (elt x 1) 1))
              env
              args
              nil
              name
              global
              test
              clos)
        (format stream ";")
        (comp-progn stream
                    (cons 'progn
                          (append (cdr (cdr x)) (list (list 'close (elt (elt x 1) 0)))))
                    (cons (elt (elt x 1) 0) env)
                    args
                    tail
                    name
                    global
                    test
                    clos)
        (format stream ";res;})"))

    (defun comp-with-open-output-file (stream x env args tail name global test clos)
        (unless (listp (elt x 1))
                (error* "with-open-output-file: not list" (elt x 1)))
        (unless (symbolp (elt (elt x 1) 0))
                (error* "with-open-output-file: illegal file name" x))
        (format stream "({int res;")
        (format stream "int ")
        (format stream (convert (conv-name (elt (elt x 1) 0)) <string>))
        (format stream " = ")
        (comp stream
              (list 'open-output-file (elt (elt x 1) 1))
              env
              args
              nil
              name
              global
              test
              clos)
        (format stream ";")
        (comp-progn stream
                    (cons 'progn
                          (append (cdr (cdr x)) (list (list 'close (elt (elt x 1) 0)))))
                    (cons (elt (elt x 1) 0) env)
                    args
                    tail
                    name
                    global
                    test
                    clos)
        (format stream ";res;})"))

    (defun comp-with-open-io-file (stream x env args tail name global test clos)
        (unless (listp (elt x 1))
                (error* "with-open-io-file: not list" (elt x 1)))
        (unless (symbolp (elt (elt x 1) 0))
                (error* "with-open-io-file: illegal file name" x))
        (format stream "({int res;")
        (format stream "int ")
        (format stream (convert (conv-name (elt (elt x 1) 0)) <string>))
        (format stream " = ")
        (comp stream
              (list 'open-io-file (elt (elt x 1) 1))
              env
              args
              nil
              name
              global
              test
              clos)
        (format stream ";")
        (comp-progn stream
                    (cons 'progn
                          (append (cdr (cdr x)) (list (list 'close (elt (elt x 1) 0)))))
                    (cons (elt (elt x 1) 0) env)
                    args
                    tail
                    name
                    global
                    test
                    clos)
        (format stream ";res;})"))

    ;;          
    ;; error_handler = (handlerN ... handler2 handler1) 
    ;; set subr of compiled handler
    (defun comp-with-handler (stream x env args tail name global test clos)
        (format stream "({int res;")
        (format stream "int handler = ")
        (comp stream (elt x 1) env args nil name global test clos)
        (format stream ";")
        (format stream
                "Fset_error_handler(Fcons(handler,Fget_error_handler()));")
        (format stream "res = ")
        (comp-progn1 stream (cdr (cdr x)) env args nil name global test clos)
        (format stream ";")
        (format stream "Fset_error_handler(Fcdr(Fget_error_handler()));")
        (format stream "res;})"))

    (defun comp-cond (stream x env args tail name global test clos)
        (format stream "({int res=NIL;~%if(")
        (comp stream (car (elt x 1)) env args tail name global t clos)
        (if (not optimize-enable)
            (format stream " != NIL){~%")
            (format stream "){~%"))
        (comp-cond2 stream
                    (cdr (elt x 1))
                    env
                    args
                    tail
                    name
                    global
                    test
                    clos)
        (comp-cond1 stream (cdr (cdr x)) env args tail name global test clos))

    (defun comp-cond1 (stream x env args tail name global test clos)
        (cond ((null x) (format stream ";res;})"))
              ((eq (car (car x)) t)
               (format stream "else{~%")
               (comp-cond2 stream (cdr (car x)) env args tail name global test clos)
               (format stream ";res;})"))
              (t (format stream "else if(")
                 (comp stream (car (car x)) env args nil name global t clos)
                 (if (not optimize-enable)
                     (format stream " != NIL){~%")
                     (format stream "){~%"))
                 (comp-cond2 stream (cdr (car x)) env args tail name global test clos)
                 (comp-cond1 stream (cdr x) env args tail name global test clos))))

    (defun comp-cond2 (stream x env args tail name global test clos)
        (when (null x) (error* "cond: illegal form*" x))
        (cond ((null (cdr x))
               (if (and (not (tailcallp (car x) t name))
                        (not (not-need-res-p (car x))))
                   (format stream "res = "))
               (comp stream (car x) env args t name global test clos)
               (if (not (not-need-colon-p (car x)))
                   (format stream ";"))
               (format stream "}~%"))
              (t (format stream "res = ")
                 (comp stream (car x) env args nil name global test clos)
                 (if (not (not-need-colon-p (car x)))
                     (format stream ";~%"))
                 (comp-cond2 stream (cdr x) env args tail name global test clos))))

    (defun comp-case (stream x env args tail name global test clos)
        (unless (consp (car (elt x 2)))
                (error* "case: illegal form" (car (elt x 2))))
        (format stream "({int res;~%if(Fmember(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ",")
        (list-to-c1 stream (car (elt x 2)))
        (format stream ") != NIL){~%")
        (comp-cond2 stream
                    (cdr (elt x 2))
                    env
                    args
                    tail
                    name
                    global
                    test
                    clos)
        (comp-case1 stream
                    (cdr (cdr (cdr x)))
                    env
                    args
                    tail
                    name
                    global
                    test
                    clos
                    (elt x 1)))

    (defun comp-case1 (stream x env args tail name global test clos key)
        (cond ((null x) (format stream ";res;})"))
              ((eq (car (car x)) t)
               (format stream "else{~%")
               (comp-cond2 stream (cdr (car x)) env args nil name global test clos)
               (format stream ";res;})"))
              (t (format stream "else if(Fmember(")
                 (comp stream key env args nil name global test clos)
                 (format stream ",")
                 (list-to-c1 stream (car (car x)))
                 (format stream ") != NIL){~%")
                 (comp-cond2 stream (cdr (car x)) env args nil name global test clos)
                 (comp-case1 stream (cdr x) env args tail name global test clos key))))

    (defun comp-case-using (stream x env args tail name global test clos)
        (format stream "({int res;~%if(Fmember1(")
        (comp stream (elt x 2) env args tail name global test clos)
        (format stream ",")
        (list-to-c1 stream (car (elt x 3)))
        (format stream ",")
        (comp stream (elt x 1) env args nil name global test clos)
        (format stream ") != NIL){~%")
        (comp-cond2 stream
                    (cdr (elt x 3))
                    env
                    args
                    tail
                    name
                    global
                    test
                    clos)
        (comp-case-using1 stream
                          (cdr (cdr (cdr (cdr x))))
                          env
                          args
                          tail
                          name
                          global
                          test
                          clos
                          (elt x 2)
                          (elt x 1)))

    (defun comp-case-using1 (stream x env args tail name global test clos key pred)
        (cond ((null x) (format stream ";res;})"))
              ((eq (car (car x)) t)
               (format stream "else{~%")
               (comp-cond2 stream (cdr (car x)) env args nil name global test clos)
               (format stream ";res;})"))
              (t (format stream "else if(Fmember1(")
                 (comp stream key env args nil name global test clos)
                 (format stream ",")
                 (list-to-c1 stream (car (car x)))
                 (format stream ",")
                 (comp stream pred env args nil name global test clos)
                 (format stream ") != NIL){~%")
                 (comp-cond2 stream (cdr (car x)) env args nil name global test clos)
                 (comp-case-using1 stream
                                   (cdr x)
                                   env
                                   args
                                   tail
                                   name
                                   global
                                   test
                                   clos
                                   key
                                   pred))))

    (defun has-tail-recur-p (x name)
        (cond ((null x) nil)
              (t (has-tail-recur-p1 (last x) name))))

    (defun has-tail-recur-p1 (x name)
        (cond ((null x) nil)
              ((atom x) nil)
              ((not (consp x)) nil)
              ((eq (car x) name) t)
              ((eq (car x) 'cond) (any (lambda (y) (has-tail-recur-p (cdr y) name)) (cdr x)))
              ((eq (car x) 'if)
               (or (has-tail-recur-p1 (elt x 2) name)
                   (and (= (length x) 4) (has-tail-recur-p1 (elt x 3) name))))
              ((eq (car x) 'let) (has-tail-recur-p (cdr (cdr x)) name))
              ((eq (car x) 'let*) (has-tail-recur-p (cdr (cdr x)) name))
              ((eq (car x) 'plet) (has-tail-recur-p (cdr (cdr x)) name))
              ((eq (car x) 'dynamic-let) (has-tail-recur-p (cdr (cdr x)) name))
              ((eq (car x) 'progn) (has-tail-recur-p (cdr x) name))
              ((eq (car x) 'block) (has-tail-recur-p (cdr (cdr x)) name))
              (t nil)))

    ;; comp-for alpha convert e.g.
    ;; from
    ;; (defun iota (n m)
    ;;  (for ((m m (- m 1))
    ;;        (a nil (cons m a)))
    ;;       ((< m n) a)))
    ;; to 
    ;; (defun iota (n m)
    ;;  (for ((msubst m (- msubst 1))
    ;;        (asubst nil (cons msubst asubst)))
    ;;       ((< msubst n) asubst)))
    (defun comp-for (stream x env args tail name global test clos)
        ;;alpha-convert variables.
        (let* ((vars1 (elt x 1))
               (var2 (mapcar #'car vars1))
               (var1 (subst var2))
               (vars (comp-for3 vars1 var2 var1))
               (end (alpha-conv (elt x 2) var2 var1))
               (body (alpha-conv (cdr (cdr (cdr x))) var2 var1)) )
            (when (any (lambda (x) (eq (elt x 0) (elt x 1))) vars)
                  (error* "for: illegal variable" vars))
            (when (any (lambda (x) (not (symbolp x))) var1)
                  (error* "for: illegal variable" vars))
            (format stream "({int res;~%")
            (format stream "Fcheckgbc(th);~%")
            (comp-let1 stream vars env args nil name global test clos)
            (gen-arg3 (length vars))
            (format stream "while(")
            (comp stream
                  (elt end 0)
                  (append var1 env)
                  args
                  nil
                  name
                  global
                  test
                  clos)
            (format stream " == NIL){~%")
            (comp-for1 stream
                       body
                       (append var1 env)
                       args
                       nil
                       name
                       global
                       test
                       clos)
            (comp-for2 stream
                       vars
                       (append var1 env)
                       args
                       nil
                       name
                       global
                       test
                       clos)
            (if (not (null (cdr end)))
                (comp-progn1 stream
                             (cdr end)
                             (append var1 env)
                             args
                             tail
                             name
                             global
                             test
                             clos)
                (format stream "res=NIL;"))
            (format stream "res;})")))

    (defun comp-for1 (stream x env args tail name global test clos)
        (cond ((null x) t)
              (t (comp stream (car x) env args tail name global test clos)
                 (format stream ";~%")
                 (comp-for1 stream (cdr x) env args tail name global test clos))))

    (defun comp-for2 (stream x env args tail name global test clos)
        (for ((update x (cdr update))
              (n 1 (+ n 1)) )
             ((null update)
              t )
             (when (= (length (car update)) 3)
                   (format stream "temp")
                   (format stream (convert n <string>))
                   (format stream " = ")
                   (comp stream
                         (elt (car update) 2)
                         env
                         args
                         tail
                         name
                         global
                         test
                         clos)
                   (format stream ";~%")))
        (for ((update x (cdr update))
              (n 1 (+ n 1)) )
             ((null update)
              t )
             (when (= (length (car update)) 3)
                   (format stream (convert (elt (car update) 0) <string>))
                   (format stream " = temp")
                   (format stream (convert n <string>))
                   (format stream ";~%")))
        (format stream "}~%"))

    ;; alpha convert vars list
    (defun comp-for3 (vars var subst)
        (mapcar (lambda (x) (if (= (length x) 3)
                       (list (alpha-conv (elt x 0) var subst)
                             (elt x 1)
                             (alpha-conv (elt x 2) var subst))
                       (list (alpha-conv (elt x 0) var subst) (elt x 1))))
                vars))

    (defun comp-progn (stream x env args tail name global test clos)
        (format stream "({int res;~%")
        (comp-progn1 stream (cdr x) env args tail name global test clos)
        (format stream "res;})"))

    (defun comp-progn1 (stream x env args tail name global test clos)
        (cond ((null x) t)
              ((null (cdr x))
               (if (and (not (not-need-res-p (car x)))
                        (not (tailcallp (car x) tail name)))
                   (format stream "res = "))
               (comp stream (car x) env args tail name global test clos)
               (if (not (not-need-colon-p (car x)))
                   (format stream ";")))
              (t (comp stream (car x) env args nil name global test clos)
                 (if (not (not-need-colon-p (car x)))
                     (format stream ";~%"))
                 (comp-progn1 stream (cdr x) env args tail name global test clos))))

    (defun comp-mt-lock (stream x env args tail name global test clos)
        (format stream "({int res;~%")
        (format stream "pthread_mutex_lock(&plock_mutex);")
        (comp-plock1 stream (cdr x) env args tail name global test clos)
        (format stream "pthread_mutex_unlock(&plock_mutex);")
        (format stream "res;})"))

    (defun comp-mt-lock1 (stream x env args tail name global test clos)
        (cond ((null x) t)
              ((null (cdr x))
               (if (and (not (not-need-res-p (car x)))
                        (not (tailcallp (car x) tail name)))
                   (format stream "res = "))
               (comp stream (car x) env args tail name global test clos)
               (if (not (not-need-colon-p (car x)))
                   (format stream ";")))
              (t (comp stream (car x) env args nil name global test clos)
                 (if (not (not-need-colon-p (car x)))
                     (format stream ";~%"))
                 (comp-mt-lock1 stream (cdr x) env args tail name global test clos))))



    (defun comp-and (stream x env args tail name global test clos)
        (format stream "({int res;~%if((res = ")
        (comp stream (elt x 1) env args nil name global test clos)
        (format stream ") != NIL)~%")
        (comp-and1 stream (cdr (cdr x)) env args nil name global test clos)
        (format stream "else res=NIL;res;})~%"))

    (defun comp-and1 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "res=res;"))
              ((null (cdr x))
               (format stream "if((res=" env args tail name global)
               (comp stream (car x) env args nil name global test clos)
               (format stream ") !=NIL)~%res=res;~%else res=NIL;~%"))
              (t (format stream "if((res=")
                 (comp stream (car x) env args nil name global test clos)
                 (format stream ") != NIL)~%")
                 (comp-and1 stream (cdr x) env args nil name global test clos)
                 (format stream "else res=NIL;"))))

    (defun comp-or (stream x env args tail name global test clos)
        (format stream "({int res;~%if((res=")
        (comp stream (elt x 1) env args nil name global test clos)
        (format stream ") == NIL)~%")
        (comp-or1 stream (cdr (cdr x)) env args nil name global test clos)
        (format stream "else res=res;res;})~%"))

    (defun comp-or1 (stream x env args tail name global test clos)
        (cond ((null x) (format stream "res = res;"))
              ((null (cdr x))
               (format stream "if((res=" env args tail name global)
               (comp stream (car x) env args nil name global test clos)
               (format stream ") !=NIL)~%res=res;~%else res=NIL;~%"))
              (t (format stream "if((res=")
                 (comp stream (car x) env args nil name global test clos)
                 (format stream ") == NIL)~%")
                 (comp-or1 stream (cdr x) env args nil name global test clos)
                 (format stream "else res=res;"))))

    (defun comp-test-and (stream x env args tail name global test clos)
        (format stream "(")
        (comp-test-and1 stream (cdr x) env args tail name global test clos)
        (format stream ")"))

    (defun comp-test-and1 (stream x env args tail name global test clos)
        (cond ((null (cdr x)) (comp stream (car x) env args nil name global test clos))
              (t (comp stream (car x) env args nil name global test clos)
                 (format stream " && ")
                 (comp-test-and1 stream (cdr x) env args tail name global test clos))))

    (defun comp-test-or (stream x env args tail name global test clos)
        (format stream "(")
        (comp-test-or1 stream (cdr x) env args tail name global test clos)
        (format stream ")"))

    (defun comp-test-or1 (stream x env args tail name global test clos)
        (cond ((null (cdr x)) (comp stream (car x) env args nil name global test clos))
              (t (comp stream (car x) env args nil name global test clos)
                 (format stream " || ")
                 (comp-test-or1 stream (cdr x) env args tail name global test clos))))

    (defun comp-while (stream x env args tail name global test clos)
        (format stream "({int res;~%while(")
        (comp stream (elt x 1) env args tail name global t clos)
        (format stream " !=NIL){~%")
        (format stream "Fcheckgbc(th);")
        (comp-progn1 stream (cdr (cdr x)) env args tail name global test clos)
        (format stream "};res;})~%"))

    (defun comp-setq (stream x env args tail name global test clos)
        (unless (symbolp (elt x 1)) (error* "setq: not symbol" x))
        (cond ((member (elt x 1) clos)
               (format stream "({int res;~% res = ")
               (format stream "fast_setnth(Fcdr(Fmakesym(\"~A" (lambda-name-with-root name))
               (format stream "\")),")
               (format-integer stream (position (elt x 1) clos) 10)
               (format stream ",")
               (comp stream (elt x 2) env args tail name global test clos)
               (format stream ");res;})"))
              ((member (elt x 1) env)
               (format stream "({int res;~% res = ")
               (format-object stream (conv-name (elt x 1)) nil)
               (format stream " = ")
               (comp stream (elt x 2) env args tail name global test clos)
               (format stream ";res;})~%"))
              (t (format stream "({int res;~% res = ")
                 (format stream "Fset_cdr(Fmakesym(\"")
                 (format stream (convert (elt x 1) <string>))
                 (format stream "\"),")
                 (comp stream (elt x 2) env args nil name global test clos)
                 (format stream ");res;})"))))

    (defun comp-tagbody (stream x env args tail name global test clos)
        (unless (symbolp (elt x 1))
                (error* "tagbody: not symbol" (elt x 1)))
        (format stream "({")
        (format stream (convert (conv-name (elt x 1)) <string>))
        (format stream ":~%")
        (comp-tagbody1 stream (cdr (cdr x)) env args tail name global test clos)
        (format stream "res;})~%"))

    (defun comp-tagbody1 (stream x env args tail name global test clos)
        (cond ((null x) t)
              ((symbolp (car x))
               (format stream (convert (conv-name (car x)) <string>))
               (format stream ":~%")
               (comp-tagbody1 stream (cdr x) env args tail name global test clos))
              ((null (cdr x))
               (if (and (not (not-need-res-p (car x)))
                        (not (tailcallp (car x) tail name)))
                   (format stream "res = "))
               (comp stream (car x) env args tail name global test clos)
               (format stream ";"))
              (t (comp stream (car x) env args nil name global test clos)
                 (format stream ";~%")
                 (comp-tagbody1 stream (cdr x) env args tail name global test clos))))

    (defun comp-go (stream x env args tail name global test clos)
        (unless (symbolp (elt x 1)) (error* "go: not symbol" (elt x 1)))
        (format stream "goto ")
        (format stream (convert (conv-name (elt x 1)) <string>))
        (format stream ";~%"))

    (defun comp-convert (stream x env args tail name global test clos)
        (unless (symbolp (elt x 2)) (error* "convert: not symbol" x))
        (unless (= (length x) 3) (error* "convert: illegal form" x))
        (format stream "Fconvert(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ",Fmakesym(\"")
        (format-object stream (elt x 2) nil)
        (format stream "\"))"))

    (defun comp-function (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "function: illegal form" x))
        (unless (symbolp (elt x 1)) (error* "function: illegal form" x))
        (format stream "Fcar(Fmakesym(\"")
        (format-object stream (elt x 1) nil)
        (format stream "\"))"))

    (defun comp-symbol-function (stream x env args tail name global test clos)
        (unless (symbolp (elt x 1))
                (error* "symbol-function: illegal form" x))
        (unless (= (length x) 2)
                (error* "symbol-function: illegal form" x))
        (format stream "Fcar(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ")"))

    (defun comp-class (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "class: illegal form" x))
        (unless (symbolp (elt x 1)) (error* "class: illegal form" x))
        (format stream "Faux(Fmakesym(\"")
        (format-object stream (elt x 1) nil)
        (format stream "\"))"))

    (defun comp-symbol-class (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "class: illegal form" x))
        (unless (symbolp (elt x 1)) (error* "class: illegal form" x))
        (format stream "Faux(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ")"))

    (defun comp-catch (stream x env args tail name global test clos)
        (let ((tag (elt (elt x 1) 1)))
           (set-property unwind-nest tag 'unwind-nest)
           (format stream "({int res,ret,i;~% ")
           (format stream "Fset_error_flag(1);~%")
           (format stream "i = Fgetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"));~%")
           (format stream "Fsetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"),i+1);~%")
           (format stream "ret=setjmp(c_")
           (format-object stream (conv-name tag) nil)
           (format stream "[i]);")
           (format stream "if(ret == 0){~%")
           (comp-progn1 stream (cdr (cdr x)) env args tail name global test clos)
           (format stream "Fsetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"),i);~%")
           (format stream "}~% else{~%")
           (format stream "ret = 0;~%")
           (format stream
                   "if(Fget_error_flag()){Frestore_error_handler();}~%")
           (format stream "res=catch_arg;}~%")
           (format stream "res;})")))

    (defun comp-throw (stream x env args tail name global test clos)
        (let ((tag (elt (elt x 1) 1)))
           (when (not (member tag catch-block-tag))
                 (error* "throw: tag not exist " tag))
           (format stream "({int res,i;~%")
           ;; while executing unwind-protect, throw execute cleanup before.
           (cond ((and (property tag 'unwind-nest)
                       (/= (property tag 'unwind-nest) unwind-nest))
                  (comp-progn1 stream
                               (car unwind-cleanup)
                               env
                               args
                               tail
                               name
                               global
                               test
                               clos)
                  (setq unwind-cleanup (cdr unwind-cleanup))))
           (comp-progn1 stream (cdr (cdr x)) env args tail name global test clos)
           (format stream "catch_arg=res;~% ")
           (format stream "i = Fgetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"));~%")
           (format stream "Fsetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"),i-1);~%")
           (format stream "longjmp(c_")
           (format-object stream (conv-name tag) nil)
           (format stream "[i-1],1);res;})~%")))

    (defun comp-block (stream x env args tail name global test clos)
        (unless (symbolp (elt x 1))
                (error* "block: not symbol" (elt x 1)))
        (let ((tag (elt x 1)))
           (format stream "({int res,ret,i;~% ")
           (format stream "i = Fgetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"));~%")
           (format stream "Fsetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"),i+1);~%")
           (format stream "ret=setjmp(c_")
           (format-object stream (conv-name tag) nil)
           (format stream "[i]);")
           (format stream "if(ret == 0){~%")
           (comp-progn1 stream (cdr (cdr x)) env args tail name global test clos)
           (format stream "Fsetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"),i);~%")
           (format stream "}~% else{~%")
           (format stream "ret = 0;~%")
           (format stream "res=block_arg;}~%")
           (format stream "res;})")))

    (defun comp-return-from (stream x env args tail name global test clos)
        (unless (symbolp (elt x 1))
                (error* "return-from: not symbol" (elt x 1)))
        (let ((tag (elt x 1)))
           (format stream "({int res,i;~%")
           ;; while executing unwind-protect, return-from execute cleanup before.
           (cond ((and (property tag 'unwind-nest)
                       (/= (property tag 'unwind-nest) unwind-nest))
                  (comp-progn1 stream
                               (car unwind-cleanup)
                               env
                               args
                               tail
                               name
                               global
                               test
                               clos)
                  (setq unwind-cleanup (cdr unwind-cleanup))))
           (comp-progn1 stream (cdr (cdr x)) env args tail name global test clos)
           (format stream "block_arg=res;~% ")
           (format stream "i = Fgetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"));~%")
           (format stream "Fsetprop(Fmakesym(\"")
           (format-object stream tag nil)
           (format stream "\"),i-1);~%")
           (format stream "longjmp(c_")
           (format-object stream (conv-name tag) nil)
           (format stream "[i-1],1);res;})~%")))

    ;;; memo
    ;;; if body has throw, throw execute cleanup.
    ;;; As the result unwind-cleanup is nothing.
    ;;; normal case unwind-nest and length of unwind-cleanup is equal.
    ;;; when equal unwind-protect execute clean up.
    ;;; if nested unwind-protect unwind-cleanup is following.
    ;;; unwind-cleanup= (thunkn ... thunk2 thunk1)
    (defun comp-unwind-protect (stream x env args tail name global test clos)
        (setq unwind-nest (+ unwind-nest 1))
        (format stream "({int res;~%")
        (setq unwind-cleanup (cons (cdr (cdr x)) unwind-cleanup))
        (format stream "res=")
        (comp stream (elt x 1) env args tail name global test clos)
        (cond ((= (length unwind-cleanup) unwind-nest)
               (format stream ";")
               (comp-progn1 stream
                            (car unwind-cleanup)
                            env
                            args
                            tail
                            name
                            global
                            test
                            clos)
               (setq unwind-cleanup (cdr unwind-cleanup))))
        (format stream ";res;})")
        (setq unwind-nest (- unwind-nest 1)))

    (defun comp-setf (stream x env args tail name global test clos)
        (unless (= (length x) 3) (error* "setf: illegal form" x))
        (when (or (eq (elt x 1) t) (eq (elt x 1) nil))
              (error* "setf: can't modify" x))
        (let* ((form1 (elt x 1))
               (form (if (and (consp form1) (macrop (car form1)))
                        (macroexpand-1 form1)
                        form1))
               (val (elt x 2)) )
            (cond ((and (consp form) (eq (car form) 'aref))
                   (let ((newform (cons 'set-aref (cons val (cdr form)))))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form) (eq (car form) 'garef))
                   (let ((newform (cons 'set-garef (cons val (cdr form)))))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form) (eq (car form) 'elt))
                   (let ((newform (cons 'set-elt (cons val (cdr form)))))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form) (eq (car form) 'property))
                   (let ((newform (cons 'set-property (cons val (cdr form)))))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form) (= (length form) 2) (eq (car form) 'car))
                   (let ((newform (list 'set-car val (elt form 1))))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form) (= (length form) 2) (eq (car form) 'cdr))
                   (let ((newform (list 'set-cdr val (elt form 1))))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form) (eq (car form) 'dynamic))
                   (let ((newform (list 'set-dynamic (elt form 1) val)))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form)
                        (= (length form) 2)
                        (symbolp (elt form 0))
                        (symbolp (elt form 1)))
                   (let ((newform
                         (list 'set-slot-value
                               val
                               (elt form 1)
                               (list 'quote (eval (list (elt form 0) nil))))))
                      (comp stream newform env args tail name global test clos)))
                  ((and (consp form))
                   (let ((newform (cons (car form) (cons val (cdr form)))))
                      (comp stream newform env args tail name global test clos)))
                  ((symbolp form)
                   (comp-setq stream
                              (list 'setq form val)
                              env
                              args
                              tail
                              name
                              global
                              test
                              clos))
                  (t (error* "setf: illegal form" x)))))

    (defun comp-dynamic (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "dynamic: illegal form" x))
        (unless (symbolp (elt x 1)) (error* "dynamic: illegal form" x))
        (format stream "Fpfinddyn(Fmakesym(\"")
        (format-object stream (elt x 1) nil)
        (format stream "\"),th)"))

    (defun comp-dynamic-let (stream x env args tail name global test clos)
        (let ((dyn dynamic-variable))
            (format stream "({int res,val,save,dynpt;~% save=Fgetdynpt();~%")
            (comp-dynamic-let1 stream (elt x 1) env args tail name global test clos)
            (comp-progn1 stream (cdr (cdr x)) env args tail name global test clos)
            (format stream "Fsetdynpt(save);res;})")
            (setq dynamic-variable dyn)))

    (defun comp-dynamic-let1 (stream x env args tail name global test clos)
        (cond ((null x) t)
              (t (comp-dynamic-let2 stream (car x) env args tail name global test clos)
                 (comp-dynamic-let1 stream (cdr x) env args tail name global test clos))))

    (defun comp-dynamic-let2 (stream x env args tail name global test clos)
        (unless (symbolp (elt x 0))
                (error* "dynamic-let: illegal let form" x))
        (let ((symbol (elt x 0))
              (value (elt x 1)) )
           (setq dynamic-variable (cons symbol dynamic-variable))
           (format stream
                   "dynpt=Fgetdynpt();Fpshelterpush(dynpt,th);Fsetdynpt(save);~%")
           (format stream "val=")
           (comp stream value env args nil name global test clos)
           (format stream ";Fsetdynpt(dynpt);Fpshelterpop(th);")
           (format stream "Fpadddynenv(Fmakesym(\"")
           (format-object stream symbol nil)
           (format stream "\"),val,th);")))

    (defun comp-not (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "not: illegal form" x))
        (format stream "fast_not(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ")"))

    (defun comp-car (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "car: illegal form" x))
        (unless (or (symbolp (elt x 1)) (consp (elt x 1)))
                (error* "car: illegal argument" x))
        (format stream "fast_car(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ")"))

    (defun comp-cdr (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "cdr: illegal form" x))
        (unless (or (symbolp (elt x 1)) (consp (elt x 1)))
                (error* "cdr: illegal argument" x))
        (format stream "fast_cdr(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ")"))

    (defun comp-cons (stream x env args tail name global test clos)
        (unless (= (length x) 3) (error* "cons: illegal form" x))
        (format stream "Fcons(")
        (comp stream (elt x 1) env args nil name global test clos)
        (format stream ",")
        (comp stream (elt x 2) env args nil name global test clos)
        (format stream ")"))

    (defun comp-length (stream x env args tail name global test clos)
        (unless (= (length x) 2) (error* "length: illegal form" x))
        (unless (or (symbolp (elt x 1))
                    (listp (elt x 1))
                    (stringp (elt x 1))
                    (general-vector-p (elt x 1)))
                (error* "length: illegal argument" x))
        (format stream "Flength(")
        (comp stream (elt x 1) env args tail name global test clos)
        (format stream ")"))

    ;;add code0 stream #include C code.
    (defun comp-c-include (x)
        (unless (or (= (length x) 2) (= (length x) 3))
                (error* "c-include: illegal form" x))
        (unless (stringp (elt x 1))
                (error* "c-include: argument must be string" x))
        (cond ((and (= (length x) 3) (eq (self-introduction) (elt x 2)))
               (format code0 "#include ")
               (format code0 (elt x 1))
               (format code0 "~%"))
              ((= (length x) 2)
               (format code0 "#include ")
               (format code0 (elt x 1))
               (format code0 "~%"))))

    ;;add code2 stream C define
    (defun comp-c-define (x)
        (unless (= (length x) 3) (error* "c-define: illegal form" x))
        (unless (stringp (elt x 1))
                (error* "c-define: argument must be string" x))
        (format code0 "#define ")
        (format code0 (elt x 1))
        (format code0 " ")
        (format code0 (elt x 2))
        (format code0 "~%"))

    ;;add code2 stream C language code.
    (defun comp-c-lang (x)
        (unless (= (length x) 2) (error* "c-lang: illegal form" x))
        (unless (stringp (elt x 1))
                (error* "c-lang: argument must be string" x))
        (format code2 (elt x 1) nil)
        (format code2 "~%"))

    ;;add compile option
    (defun comp-c-option (x)
        (unless (or (= (length x) 2) (= (length x) 3))
                (error* "c-option: illegal form" x))
        (unless (stringp (elt x 1))
                (error* "c-option: argument must be string" x))
        (cond ((and (= (length x) 3) (eq (self-introduction) (elt x 2)))
               (setq c-lang-option (elt x 1)))
              ((= (length x) 2) (setq c-lang-option (elt x 1)))))

    ;;defglobal
    (defun comp-defglobal (x)
        (let ((symbol (elt x 1))
              (value (elt x 2)) )
           (format code4 "Fset_cdr(Fmakesym(\"")
           (format-object code4 symbol nil)
           (format code4 "\"),Fbigxtoparmanent(")
           (comp code4 value nil nil nil nil t nil nil)
           (format code4 "));")
           (format code4 "Fset_opt(Fmakesym(\"")
           (format-object code4 symbol nil)
           (format code4 "\"),GLOBAL);~%")))

    ;;defconstant
    (defun comp-defconstant (x)
        (let ((symbol (elt x 1))
              (value (elt x 2)) )
           (format code4 "({int th=0;Fset_cdr(Fmakesym(\"")
           (format-object code4 symbol nil)
           (format code4 "\"),")
           (comp code4 value nil nil nil nil t nil nil)
           (format code4 ");")
           (format code4 "Fset_opt(Fmakesym(\"")
           (format-object code4 symbol nil)
           (format code4 "\"),CONSTN);});~%")))

    ;;defdynamic
    (defun comp-defdynamic (x)
        (unless (= (length x) 3) (error* "defdynamic: illegal form" x))
        (unless (symbolp (elt x 1))
                (error: "defdynamic: not symbol" (elt x 1)))
        (let ((symbol (elt x 1))
              (value (elt x 2)) )
           (format code4 "Fpsetdynenv(Fmakesym(\"")
           (format-object code4 symbol nil)
           (format code4 "\"),")
           (comp code4 value nil nil nil nil t nil nil)
           (format code4 ",0);")))

    ;;set-dynamic
    (defun comp-set-dynamic (stream x env args tail name global test clos)
        (unless (= (length x) 3) (error* "set-dynamic: illegal form" x))
        (unless (symbolp (elt x 1))
                (error: "set-dynamic: not symbol" (elt x 1)))
        (let ((symbol (elt x 1))
              (value (elt x 2)) )
           (format stream "Fpsetdynamic(Fmakesym(\"")
           (format-object stream symbol nil)
           (format stream "\"),")
           (comp stream value env args tail name global test clos)
           (format stream ",th)")))
                
                 

    ;;defmacro
    (defun comp-defmacro (x)
        (format code4 "Fpeval(")
        (list-to-c1 code4 '(eisl-ignore-toplevel-check t))
        (format code4 ",0);~%")
        (format code4 "Fpeval(")
        (list-to-c1 code4 x)
        (format code4 ",0);~%")
        (format code4 "Fpeval(")
        (list-to-c1 code4 '(eisl-ignore-toplevel-check nil))
        (format code4 ",0);~%"))

    ;;defclass
    (defun comp-defclass (x)
        (comp code4
              '(eisl-ignore-toplevel-check t)
              nil
              nil
              nil
              nil
              nil
              nil
              nil)
        (format code4 ";Fpeval(")
        (list-to-c1 code4 x)
        (format code4 ",0);")
        (comp code4
              '(eisl-ignore-toplevel-check nil)
              nil
              nil
              nil
              nil
              nil
              nil
              nil)
        (format code4 ";~%"))

    ;;defmethod only create initialize-object
    ;;these are nead to save as C-list
    (defun comp-defmethod (x)
        (cond ((or (eq (elt x 1) 'create) (eq (elt x 1) 'initialize-object))
               (format code4 "Fpeval(")
               (list-to-c1 code4 x)
               (format code4 ",0);~%"))
              (t
               (let* ((name0 (elt x 1))
                      (name (if (listp name0)
                               (elt name0 1)
                               name0))
                      (arg (if (listp (elt x 2))
                              (elt x 2)
                              (elt x 3)))
                      (res (assoc name generic-name-arg)) )
                   (when (null res) (error* "not exist defgeneric " name))))))

    ;;ex prime-factors -> prime_factors
    (defun conv-name (sym)
        (convert (conv-name1 (convert (convert sym <string>) <list>))
                 <symbol>))

    (defun conv-name1 (ls)
        (cond ((char= (car ls) #\0) (string-append "zero" (conv-name2 (cdr ls))))
              ((char= (car ls) #\1) (string-append "one" (conv-name2 (cdr ls))))
              ((char= (car ls) #\2) (string-append "two" (conv-name2 (cdr ls))))
              ((char= (car ls) #\3) (string-append "three" (conv-name2 (cdr ls))))
              ((char= (car ls) #\4) (string-append "four" (conv-name2 (cdr ls))))
              ((char= (car ls) #\5) (string-append "five" (conv-name2 (cdr ls))))
              ((char= (car ls) #\6) (string-append "six" (conv-name2 (cdr ls))))
              ((char= (car ls) #\7) (string-append "seven" (conv-name2 (cdr ls))))
              ((char= (car ls) #\8) (string-append "eight" (conv-name2 (cdr ls))))
              ((char= (car ls) #\9) (string-append "nine" (conv-name2 (cdr ls))))
              (t (conv-name2 ls))))

    (defun conv-name2 (ls)
        (cond ((null ls) "")
              ((char= (car ls) #\-) (string-append "_" (conv-name2 (cdr ls))))
              ((char= (car ls) #\+) (string-append "plus" (conv-name2 (cdr ls))))
              ((char= (car ls) #\*) (string-append "star" (conv-name2 (cdr ls))))
              ((char= (car ls) #\/) (string-append "slash" (conv-name2 (cdr ls))))
              ((char= (car ls) #\!) (string-append "exclamation" (conv-name2 (cdr ls))))
              ((char= (car ls) #\%) (string-append "percent" (conv-name2 (cdr ls))))
              ((char= (car ls) #\$) (string-append "dollar" (conv-name2 (cdr ls))))
              ((char= (car ls) #\&) (string-append "and" (conv-name2 (cdr ls))))
              ((char= (car ls) #\=) (string-append "equal" (conv-name2 (cdr ls))))
              ((char= (car ls) #\^) (string-append "hat" (conv-name2 (cdr ls))))
              ((char= (car ls) #\~) (string-append "tilde" (conv-name2 (cdr ls))))
              ((char= (car ls) #\\) (string-append "yen" (conv-name2 (cdr ls))))
              ((char= (car ls) #\|) (string-append "vertical" (conv-name2 (cdr ls))))
              ((char= (car ls) #\@) (string-append "atmark" (conv-name2 (cdr ls))))
              ((char= (car ls) #\#) (string-append "sharp" (conv-name1 (cdr ls))))
              ((char= (car ls) #\:) (string-append "colon" (conv-name2 (cdr ls))))
              ((char= (car ls) #\>) (string-append "greater" (conv-name2 (cdr ls))))
              ((char= (car ls) #\<) (string-append "smaller" (conv-name2 (cdr ls))))
              ((char= (car ls) #\[) (string-append "lbracket" (conv-name2 (cdr ls))))
              ((char= (car ls) #\]) (string-append "rbracket" (conv-name2 (cdr ls))))
              ((char= (car ls) #\{) (string-append "lcurl" (conv-name2 (cdr ls))))
              ((char= (car ls) #\}) (string-append "rcurl" (conv-name2 (cdr ls))))
              ((char= (car ls) #\?) (string-append "question" (conv-name2 (cdr ls))))
              ((char= (car ls) #\.) (string-append "dot" (conv-name2 (cdr ls))))
              (t (string-append (create-string 1 (car ls)) (conv-name2 (cdr ls))))))

    ;; fixnum translate to immediate
    (defun list-to-c (stream x)
        (cond ((null x) (format stream "NIL"))
              ((fixnump x)
               (format stream "fast_immediate(")
               (format stream (convert x <string>))
               (format stream ")"))
              ((floatp x)
               (format stream "Fmakestrflt(\"")
               (format-float stream x)
               (format stream "\")"))
              ((or (bignump x) (longnump x))
               (format stream "Fmakebig(\"")
               (format-integer stream x 10)
               (format stream "\")"))
              ((stringp x) (format stream "Fmakestr(\"~A\")" x))
              ((characterp x)
               (cond ((or (char= x #\\)
                          (char= x (convert 34 <character>))
                          ;;"
                          (char= x (convert 39 <character>)))
                      ;;'
                      (format stream "Fmakechar(\"\\~C\")" x))
                     (t (format stream "Fmakechar(\"~C\")" x))))
              ((general-vector-p x)
               (format stream "Fvector(")
               (list-to-c1 stream (convert x <list>))
               (format stream ")"))
              ((general-array*-p x)
               (format stream "Farray(")
               (format-integer stream (length (array-dimensions x)) 10)
               (format stream ",")
               (list-to-c1 stream (eisl-readed-array-list x))
               (format stream ")"))
              ((symbolp x)
               (cond ((eq x t) (format stream "T"))
                     ((eq x nil) (format stream "NIL"))
                     (t (format stream "Fmakesym(\"")
                        (format stream (convert x <string>))
                        (format stream "\")"))))
              ((stringp x)
               (format stream "Fmakestr(\"")
               (format-object stream x nil)
               (format stream "\")"))
              (t (format stream "Fcons(")
                 (list-to-c stream (car x))
                 (format stream ",")
                 (list-to-c stream (cdr x))
                 (format stream ")"))))

    ;;translate fixnum to int-cell
    (defun list-to-c1 (stream x)
        (cond ((null x) (format stream "NIL"))
              ((fixnump x)
               (format stream "Fmakeint(")
               (format stream (convert x <string>))
               (format stream ")"))
              ((floatp x)
               (format stream "Fmakestrflt(\"")
               (format-float stream x)
               (format stream "\")"))
              ((or (bignump x) (longnump x))
               (format stream "Fmakebig(\"")
               (format-integer stream x 10)
               (format stream "\")"))
              ((stringp x) (format stream "Fmakestr(\"~A\")" x))
              ((characterp x)
               (cond ((or (char= x #\\)
                          (char= x (convert 34 <character>))
                          ;;"
                          (char= x (convert 39 <character>)))
                      ;;'
                      (format stream "Fmakechar(\"\\~C\")" x))
                     ((special-char-p x)
                      (format stream "Fmakechar(\"~A\")" (print-special-char x)))
                     (t (format stream "Fmakechar(\"~C\")" x))))
              ((general-vector-p x)
               (format stream "Fvector(")
               (list-to-c1 stream (convert x <list>))
               (format stream ")"))
              ((general-array*-p x)
               (format stream "Farray(")
               (format-integer stream (length (array-dimensions x)) 10)
               (format stream ",")
               (list-to-c1 stream (eisl-readed-array-list x))
               (format stream ")"))
              ((symbolp x)
               (cond ((eq x t) (format stream "T"))
                     ((eq x nil) (format stream "NIL"))
                     (t (format stream "Fmakesym(\"")
                        (format stream (convert x <string>))
                        (format stream "\")"))))
              ((stringp x)
               (format stream "Fmakestr(\"")
               (format-object stream x nil)
               (format stream "\")"))
              (t (format stream "Fcons(")
                 (list-to-c1 stream (car x))
                 (format stream ",")
                 (list-to-c1 stream (cdr x))
                 (format stream ")"))))

    ;;quasi-quote
    (defun quasi-transfer (x n)
        (cond ((null x) nil)
              ((atom x) (list 'quote x))
              ((and (consp x) (eq (car x) 'unquote) (= n 0)) (elt x 1))
              ((and (consp x) (eq (car x) 'unquote-splicing) (= n 0)) (elt x 1))
              ((and (consp x) (eq (car x) 'quasi-quote))
               (list 'list
                     (list 'quote 'quasi-quote)
                     (quasi-transfer (elt x 1) (+ n 1))))
              ((and (consp x)
                    (consp (car x))
                    (eq (car (car x)) 'unquote)
                    (= n 0))
               (list 'cons (elt (car x) 1) (quasi-transfer (cdr x) n)))
              ((and (consp x)
                    (consp (car x))
                    (eq (car (car x)) 'unquote-splicing)
                    (= n 0))
               (list 'append (elt (car x) 1) (quasi-transfer (cdr x) n)))
              ((and (consp x) (consp (car x)) (eq (car (car x)) 'unquote))
               (list 'cons
                     (list 'list
                           (list 'quote 'unquote)
                           (quasi-transfer (elt (car x) 1) (- n 1)))
                     (quasi-transfer (cdr x) n)))
              ((and (consp x)
                    (consp (car x))
                    (eq (car (car x)) 'unquote-splicing))
               (list 'cons
                     (list 'list
                           (list 'quote 'unquote-splicing)
                           (quasi-transfer (elt (car x) 1) (- n 1)))
                     (quasi-transfer (cdr x) n)))
              (t (list 'cons
                       (quasi-transfer (car x) n)
                       (quasi-transfer (cdr x) n)))))

    ;;-----------type inferrence-------------
    ;;if following all test is true, it is optimizable
    ;;output type is fixnum or float
    ;;input type is all fixnum or float,
    ;;if it has local function,the output type and input types are
    ;;fixnum or float
    (defun optimize-p (x)
        (if (> (length x) 1)
            (let* ((fn (elt x 1))
                   (dt (assoc fn type-function)) )
                (cond ((null dt) nil)
                      ((and (eq (elt x 0) 'defun)
                            (member (elt dt 1) (list (class <fixnum>) (class <float>)))
                            (subsetp (elt dt 2) (list (class <fixnum>) (class <float>)))
                            (optimize-p1 (cdr (cdr (cdr dt)))))
                       t)
                      (t nil)))
            nil))

    ;;local type is optimizable?
    (defun optimize-p1 (x)
        (cond ((null x) t)
              ((and (member (elt (car x) 1) (list (class <fixnum>) (class <float>)))
                    (subsetp (elt (car x) 2) (list (class <fixnum>) (class <float>))))
               (optimize-p1 (cdr x)))
              (t nil)))

    ;;global function, return output type
    (defun return-type (x)
        (elt (assoc x type-function) 1))

    ;;global function, return input argument type
    (defun argument-type (x)
        (elt (assoc x type-function) 2))

    ;;local function, return output type
    ;;x is global name, y is local name
    (defun local-return-type (x y)
        (let ((local (elt (assoc x type-function) 3)))
           (elt (assoc y local) 1)))

    ;;local function, return input argument type
    ;;x is global name, y is local name
    (defun local-argument-type (x y)
        (let ((local (elt (assoc x type-function) 3)))
           (elt (assoc y local) 2)))

    ;; (x y z) -> (int x, double y, int z, int th) when (<fixnum> <float> <fixnum>)
    ;; output to stream of string
    (defun type-gen-arg2 (stream ls type)
        (format stream "(")
        (if (null ls)
            (format stream "int th)")
            (for ((ls1 ls (cdr ls1))
                  (n 0 (+ n 1)) )
                 ((null (cdr ls1))
                  (cond ((eq (elt type n) (class <fixnum>))
                        (format stream "int ")
                        (format-object stream (conv-name (car ls1)) nil)
                        (format stream ", int th)"))
                       ((eq (elt type n) (class <float>))
                        (format stream "double ")
                        (format-object stream (conv-name (car ls1)) nil)
                        (format stream ",int th)"))) )
                 (cond ((eq (elt type n) (class <fixnum>))
                        (format stream "int ")
                        (format-object stream (conv-name (car ls1)) nil)
                        (format stream ","))
                       ((eq (elt type n) (class <float>))
                        (format stream "double ")
                        (format-object stream (conv-name (car ls1)) nil)
                        (format stream ","))))))

    ;;for tail call
    ;; when ls=(<fixnum> <float> <fixnum>) -> int temp1; double temp2; int temp3;
    (defun type-gen-arg3 (n ls)
        (unless (= n 0)
                (for ((m 1 (+ m 1)))
                     ((> m n)
                      (format code2 "~%") )
                     (cond ((eq (car ls) (class <fixnum>)) (format code2 "int "))
                           ((eq (car ls) (class <float>)) (format code2 "double ")))
                     (format code2 "temp")
                     (format code2 (convert m <string>))
                     (format code2 ";"))))

    ;;(foo arg1 arg2) ->
    ;;  return(F_makeint(foo(Fgetint(arg1),Fgetint(arg2))));
    (defun type-gen-call (name n)
        (let ((name1 (conv-name name))
              (return (return-type name))
              (argument (argument-type name)) )
           (cond ((= n 0)
                  (cond ((eq return (class <fixnum>))
                         (format code1 "return(Fmakeint(")
                         (format code1 (convert name1 <string>))
                         (format code1 "(th) ));~%"))
                        ((eq return (class <float>))
                         (format code1 "return(Fmakedoubleflt(")
                         (format code1 (convert name1 <string>))
                         (format code1 "(th) ));~%"))))
                 (t (cond ((eq return (class <fixnum>))
                           (format code1 "return(Fmakeint(")
                           (format code1 (convert name1 <string>))
                           (format code1 "("))
                          ((eq return (class <float>))
                           (format code1 "return(Fmakedoubleflt(")
                           (format code1 (convert name1 <string>))
                           (format code1 "(")))
                    (for ((m 1 (+ m 1)))
                         ((= m n)
                          (cond ((eq (elt argument (- m 1)) (class <fixnum>))
                                (format code1 "Fgetint(arg")
                                (format code1 (convert m <string>))
                                (format code1 "),th)));~%"))
                               ((eq (elt argument (- m 1)) (class <float>))
                                (format code1 "Fgetflt(arg")
                                (format code1 (convert m <string>))
                                (format code1 "),th)));~%"))) )
                         (cond ((eq (elt argument (- m 1)) (class <fixnum>))
                                (format code1 "Fgetint(arg")
                                (format code1 (convert m <string>))
                                (format code1 "),"))
                               ((eq (elt argument (- m 1)) (class <float>))
                                (format code1 "Fgetflt(arg")
                                (format code1 (convert m <string>))
                                (format code1 "),"))))))))

    (defun subsetp (x y)
        (cond ((null x) t)
              ((member (car x) y) (subsetp (cdr x) y))
              (t nil)))

    (defmacro assert (sym :rest class)
        `(set-property (list (mapcar #'eval ',class)) ',sym 'inference))

    (defmacro assertz (sym :rest class)
        `(let
          ((old (property ',sym 'inference)))
          (set-property (append old (list (mapcar #'eval ',class)))
                        ',sym
                        'inference)))

    (defun class-dynamic (c)
        (cond ((eq c '<string>) (class <string>))
              ((eq c '<list>) (class <list>))
              ((eq c '<number>) (class <number>))
              ((eq c '<vector>) (class <vector>))
              ((eq c '<float>) (class <float>))
              (t (class <object>))))

    ;;type-function ((name output-type (input-type1 input-typr2 ...) (local-type-function)) ...)
    (defglobal file-name-and-ext nil)
    (defglobal instream nil)
    (defglobal type-function nil)
    ;; for global defun
    (defglobal local-type-function nil)
    ;;for labels flet syntax
    (defun warning (str x env)
        (format (standard-output)
                "warning ~A ~A ~A ~A~%"
                inference-name
                str
                x 
                env))

    ;;for debug
    (defpublic type* ()
        (print type-function))

    ;;type inference s-expression(s) in file x.
    ;;x is string of filename.
    (defun inference-file (x)
        (format (standard-output) "type inference~%")
        (setq file-name-and-ext x)
        (setq type-function nil)
        (setq instream (open-input-file x))
        (let ((sexp nil))
           (while (setq sexp (read instream nil nil))
              (cond ((and (consp sexp) (eq (car sexp) 'defun)) (eval sexp) (inference-defun sexp)))
              (cond ((and (consp sexp) (eq (car sexp) 'defmodule)) (inference-defmodule sexp)))
              (cond ((and (consp sexp) (eq (car sexp) 'import)) (eval sexp))))
           (close instream)
           (setq instream nil))
        t)

    (defun inference-defmodule (x)
        (for ((name (car (cdr x)))
              (body (cdr (cdr x)) (cdr body)) )
             ((null body)
              t )
             (let ((sexp (eisl-modulesubst (car body) name nil)))
                (if (and (consp sexp) (eq (car sexp) 'defun))
                    (inference-defun sexp)))))

    (defun inference-defun (x)
        (let* ((name (elt x 1))
               (arg (elt x 2))
               (body (cdr (cdr (cdr x))))
               (init-type-input (create-list (length arg) (class <object>)))
               (init-env (create-init-env arg)) )
            (setq inference-name name)
            (setq type-function
                  (cons (list name (class <object>) init-type-input)
                        type-function))
            (let ((type-env (inference-all body init-env name nil)))
               (if (not (eq type-env 'no))
                   (set-type-function-input name (find-argument-class arg type-env)))
               (if (not (null local-type-function))
                   (add-type-function-local name)))))

    (defun inference-labels (x type-env)
        (setq local-type-function nil)
        (let ((labels-func (elt x 1))
              (labels-body (cdr (cdr x)))
              (local-type-env nil) )
           (while (not (null labels-func))
              (let* ((func (car labels-func))
                     (name (elt func 0))
                     (arg (elt func 1))
                     (body (cdr (cdr func)))
                     (init-type-input (create-list (length arg) (class <object>)))
                     (init-env (create-init-env arg)) )
                  (setq local-type-function
                        (cons (list name (class <object>) init-type-input)
                              local-type-function))
                  (setq local-type-env
                        (inference-all body (append init-env type-env) name t))
                  (if (not (eq local-type-env 'no))
                      (set-local-type-function-input name (find-argument-class arg local-type-env)))
                  (setq labels-func (cdr labels-func))))
           local-type-env))

    ;;transform from data in ls to class data.
    (defun find-argument-class (ls type-env)
        (for ((arg ls (cdr arg))
              (result nil) )
             ((null arg)
              (reverse result) )
             (setq result (cons (find-class (car arg) type-env) result))))

    ;;create list that length is length of ls. all element is <object>
    (defun create-init-env (ls)
        (for ((arg ls (cdr arg))
              (result nil) )
             ((null arg)
              (reverse result) )
             (setq result (cons (cons (car arg) (class <object>)) result))))

    ;; inference a s-expression
    ;; if x is true return type-env else return 'no
    (defun inference (x type-env)
        (cond ((and (symbolp x) (eq x t)) type-env)
              ((and (symbolp x) (eq x nil)) type-env)
              ((symbolp x)
               (let ((y (refer x type-env)))
                  (if y
                      type-env
                      (unify x (class <object>) type-env))))
              ((atom x) type-env)
              ((and (consp x) (macrop (car x))) (inference (macroexpand-1 x) type-env))
              ((and (consp x) (eq (car x) 'the)) (unify (class* (elt x 1)) (elt x 2) type-env))
              ((and (consp x) (eq (car x) 'not)) ; ignore not function
               type-env)
              ((and (consp x) (eq (car x) 'setq))
               (cond ((not (symbolp (elt x 1))) (warning "setq type mismatch" (elt x 1) type-env) type-env)
                     (t (cons (cons (elt x 1) (find-class (elt x 2) type-env)) type-env))))
              ((and (consp x) (eq (car x) 'convert)) ; ignore convert function
               type-env)
              ((and (consp x) (eq (car x) 'catch)) (inference (elt x 2) type-env))
              ((and (consp x) (eq (car x) 'throw)) (inference (elt x 2) type-env))
              ((and (consp x) (eq (car x) 'quote)) type-env)
              ((and (consp x) (eq (car x) 'cond)) (inference-cond x type-env))
              ((and (consp x) (eq (car x) 'case)) (inference-case x type-env))
              ((and (consp x) (eq (car x) 'if)) (inference-if x type-env))
              ((and (consp x) (eq (car x) 'let)) (inference-let x type-env))
              ((and (consp x) (eq (car x) 'let*)) (inference-let x type-env))
              ((and (consp x) (eq (car x) 'plet)) (inference-let x type-env))
              ((and (consp x) (eq (car x) 'for)) (inference-for x type-env))
              ((and (consp x) (eq (car x) 'while)) (inference-while x type-env))
              ((and (consp x) (eq (car x) 'labels)) (inference-labels x type-env))
              ((and (consp x) (eq (car x) 'flet)) (inference-labels x type-env))
              ((and (consp x) (eq (car x) 'function)) (inference-function x type-env))
              ((and (consp x) (eq (car x) 'pcall)) (inference (cdr x) type-env))
              ((and (consp x) (macrop x)) (inference (macroexpand-1 x) type-env))
              ((and (consp x) (member (car x) '(+ - * = > < >= <= /=)))
               (inference-numeric x type-env))
              ((and (consp x) (subrp (car x)))
               (let ((type-subr (property (car x) 'inference)))
                  (block exit-inference
                     (for ((type type-subr (cdr type)))
                          ((null type)
                           (warning "subr type mismatch" x type-env)
                           'no )
                          (let ((new-env (inference-arg (cdr x) (cdr (car type)) type-env)))
                             (if (not (eq new-env 'no))
                                 (return-from exit-inference new-env)))))))
              ((consp x)
               (let ((type (find-function-type (car x))))
                  (if type
                      (inference-arg (cdr x) (elt type 1) type-env))))
              (t (warning "can't inference " x type-env) 'no)))

    ;; inference s-expressions
    ;; if all success return type-env else return 'no
    (defun inference-all (x type-env fn local)
        (let ((result (inference-all1 x type-env fn)))
           (cond ((and (not (eq result 'no)) (not local))
                  (set-type-function-output fn (find-class (last x) result)))
                 ((and (not (eq result 'no)) local)
                  (set-local-type-function-output fn (find-class (last x) result))))
           result))

    (defun inference-all1 (x type-env fn)
        (cond ((null x) type-env)
              ((and (consp (car x))
                    (member (car (car x)) '(+ - * = > < >= <= /=)))
               (let ((new-env (inference (car x) type-env)))
                  (cond (new-env (inference-all1 (cdr x) new-env fn))
                        (t (warning "numeric type mismatch" x type-env) 'no))))
              ((and (consp (car x)) (subrp (car (car x))))
               (let ((type-subr (property (car (car x)) 'inference)))
                  (block exit-all
                     (for ((type type-subr (cdr type)))
                          ((null type)
                           'no )
                          (let ((new-env (inference-arg (cdr (car x)) (cdr (car type)) type-env)))
                             (if (eq new-env 'no) (warning "type mismatch" (car x) type-env))
                             (if (not (eq new-env 'no))
                                 (let ((result (inference-all1 (cdr x) new-env fn)))
                                    (if (not (eq result 'no))
                                        (return-from exit-all result)))))))))
              (t
               (let ((new-env (inference (car x) type-env)))
                  (cond ((eq new-env 'no) (warning "type mismatch" (car x) type-env) 'no)
                        (t (inference-all1 (cdr x) new-env fn)))))))

    ;;cond syntax
    (defun inference-cond (x type-env)
        (inference-cond1 (cdr x) type-env))

    (defun inference-cond1 (x type-env)
        (cond ((null x) type-env)
              (t
               (let ((new-env (inference-cond2 (car x) type-env)))
                  (cond ((not (eq new-env 'no)) (inference-cond1 (cdr x) new-env))
                        (t (warning "cond mismatch" (car x) type-env)
                           (inference-cond1 (cdr x) type-env)))))))

    (defun inference-cond2 (x type-env)
        (cond ((null x) type-env)
              (t
               (let ((new-env (inference (car x) type-env)))
                  (cond ((not (eq new-env 'no)) (inference-cond2 (cdr x) new-env))
                        (t (warning "cond mismatch" x type-env)
                           (inference-cond2 (cdr x) type-env)))))))

    ;;case syntax
    (defun inference-case (x type-env)
        (inference-case1 (cdr (cdr x)) type-env))

    (defun inference-case1 (x type-env)
        (cond ((null x) type-env)
              (t
               (let ((new-env (inference-case2 (cdr (car x)) type-env)))
                  (if (not (eq new-env 'no))
                      (inference-case1 (cdr x) new-env)
                      (warning "case mismatch" x type-env))))))

    (defun inference-case2 (x type-env)
        (if (null x)
            type-env
            (inference-case2 (cdr x) (inference (car x) type-env))))

    ;;if syntax
    (defun inference-if (x type-env)
        (if (= (length x) 4)
            (inference-if1 x type-env)
            (inference-if2 x type-env)))

    ;;(if test true else)
    (defun inference-if1 (x type-env)
        (let ((test (inference (elt x 1) type-env)))
           (if (not (eq test 'no))
               (let ((else (inference (elt x 3) test)))
                  (if (not (eq else 'no))
                      (let ((true (inference (elt x 2) else)))
                         (if (not (eq true 'no))
                             true
                             (progn (warning "if mismatch" x type-env) 'no)))
                      'no))
               'no)))

    ;;(if test true)
    (defun inference-if2 (x type-env)
        (let ((test (inference (elt x 1) type-env)))
           (if (not (eq test 'no))
               (let ((true (inference (elt x 2) test)))
                  (if (not (eq true 'no))
                      true
                      (progn (warning "if mismatch" x type-env) 'no)))
               'no)))

    ;; +-* ...
    (defun inference-numeric (x type-env)
        (cond ((every (lambda (x) (eq (class <fixnum>) (find-class x type-env)))
                      (cdr x)) type-env)
              ((and (any (lambda (x) (eq (class <float>) (find-class x type-env)))
                         (cdr x))
                    (every (lambda (x) (numeric-type-p (find-class x type-env)))
                         (cdr x)))
               (estimate (cdr x) (class <float>) type-env))
              ((and (any (lambda (x) (eq (class <integer>) (find-class x type-env)))
                         (cdr x))
                    (every (lambda (x) (numeric-type-p (find-class x type-env)))
                         (cdr x)))
               (estimate (cdr x) (class <integer>) type-env))
              ((and (any (lambda (x) (eq (class <fixnum>) (find-class x type-env)))
                         (cdr x))
                    (every (lambda (x) (numeric-type-p (find-class x type-env)))
                         (cdr x)))
               (estimate (cdr x) (class <integer>) type-env))
              ((every (lambda (x) (let ((type (find-class x type-env)))
                            (or (null type)
                                (eq type (class <object>))
                                (eq type (class <number>))
                                (eq type (class <longnum>))
                                (eq type (class <bignum>)))))
                      (cdr x))
               (estimate (cdr x) (class <number>) type-env))
              (t (warning "numerical argument type mismatch" x type-env) 'no)))

    (defun numeric-type-p (x)
        (or (subclassp x (class <number>))
            (eq x (class <number>))
            (eq x (class <object>))))

    ;;let syntax
    (defun inference-let (x type-env)
        (let ((vars (elt x 1))
              (body (cdr (cdr x))) )
           (if (null vars)
               (inference-all1 body type-env nil)
               (block exit-let
                  (for ((vars1 vars (cdr vars1)))
                       ((null vars1))
                       (setq type-env
                             (unify (elt (car vars1) 0) (elt (car vars1) 1) type-env))
                       (if (eq type-env 'no)
                           (return-from exit-let 'no)))
                  (inference-all1 body type-env nil)))))



    ;;for syntax
    (defun inference-for (x type-env)
        (let ((vars (elt x 1))
              (end (elt x 2))
              (body (cdr (cdr (cdr x)))) )
           (block exit-for
              (for ((vars1 vars (cdr vars1)))
                   ((null vars1))
                   (setq type-env (inference (car vars1) type-env))
                   (if (eq type-env 'no)
                       (return-from exit-for 'no)))
              (for ((end1 end (cdr end1)))
                   ((null end1))
                   (setq type-env (inference (car end1) type-env))
                   (if (eq type-env 'no)
                       (return-from exit-for 'no)))
              (inference-all1 body type-env nil))))

    (defun inference-while (x type-env)
        (inference-while1 (cdr x) type-env))

    (defun inference-while1 (x type-env)
        (cond ((null x) type-env)
              (t (inference-while1 (cdr x) (inference (car x) type-env)))))

    (defun inference-function (x type-env)
        (let ((new-env (unify (car (cdr x)) (class <symbol>) type-env)))
           (cond ((eq new-env 'no) (warning "function mismatch" x type-env) type-env)
                 (t new-env))))

    ;;find type-data of user defined function.
    ;;first look for in type-function environment
    ;;second look for int local-type-function environment
    ;;return list as (output-class (input-class ...))
    (defun find-function-type (x)
        (let ((y (assoc x type-function)))
           (if (null y)
               (let ((z (assoc x local-type-function)))
                  (if (null z)
                      nil
                      (cdr z)))
               (cdr y))))

    ;;if argument is atom, unify the atom and type of argument.
    ;;else if argument is cons, inference the cons.
    ;;and unify the cons and type of argument.
    (defun inference-arg (x y type-env)
        (block exit-arg
           (for ((arg x (cdr arg))
                 (type y
                      (if (and (>= (length type) 2) (eq (elt type 1) 'repeat)) ;e.g. funcall
                          type
                          (cdr type))) )
                ((or (null arg) (null type))
                 (cond ((and (null arg) (null type)) type-env)
                      ((and (null arg)
                            (and (>= (length type) 2) (eq (elt type 1) 'repeat)))
                       type-env)
                      (t 'no)) )
                (cond ((atom (car arg))
                       (let ((new-env (unify (car arg) (car type) type-env)))
                          (if (eq new-env 'no)
                              (return-from exit-arg 'no)
                              (setq type-env new-env))))
                      (t
                       (let ((new-env (inference (car arg) type-env)))
                          (cond ((eq new-env 'no) (return-from exit-arg 'no))
                                (t
                                 (let ((output-class (find-class (car arg) type-env)))
                                    (if (not
                                         (or (eq output-class (car type))
                                             (subclassp output-class (car type))
                                             (subclassp (car type) output-class)))
                                        (return-from exit-arg 'no)))))
                          (setq type-env new-env)))))))

    ;;if x is registed in type-function data,
    ;;return t (if the output-class is <object>)
    ;;return nil (if the output-class is not <object>)
    (defun function-type-object-p (x)
        (let ((y (assoc (elt x 1) type-function)))
           (if (not y)
               nil
               (eq (elt y 0) (class <object>)))))

    ;;find class of s-exp
    (defun find-class (x type-env)
        (cond ((null x) (class <null>))
              ((and (symbolp x) (eq x 't)) (class <symbol>))
              ((symbolp x) (refer x type-env))
              ((atom x) (class-of x))
              ((and (consp x) (member (car x) '(+ - * = > < >= <= /=)))
               (find-class-numeric x type-env))
              ((and (consp x) (subrp (car x)))
               (let ((type-subr (property (car x) 'inference)))
                  ;;if car x is compiled user function, return nil
                  (if type-subr
                      (car (car type-subr))
                      nil)))
              ((and (consp x) (type-function-p (car x))) (elt (find-function-type (car x)) 0))
              ((and (consp x) (eq (car x) 'labels)) (find-class (last (cdr (cdr x))) type-env))
              ((and (consp x) (eq (car x) 'flet)) (find-class (last (cdr (cdr x))) type-env))
              ((and (consp x) (eq (car x) 'cond)) (find-class-cond (cdr x) type-env))
              ((and (consp x) (eq (car x) 'if)) (find-class-if x type-env))
              ((and (consp x) (eq (car x) 'quote)) (class-of (elt x 1)))
              ((and (consp x) (eq (car x) 'the)) nil)
              ((and (consp x) (eq (car x) 'setq)) (find-class (elt x 1) type-env))
              ((and (consp x) (eq (car x) 'convert)) (class-dynamic (elt x 2)))
              ((and (consp x) (eq (car x) 'catch)) (find-class (elt x 1) type-env))
              ((and (consp x) (eq (car x) 'throw)) (find-class (elt x 2) type-env))
              ((and (consp x) (eq (car x) 'let)) (find-class (last (cdr (cdr x))) type-env))
              ((and (consp x) (eq (car x) 'let*)) (find-class (last (cdr (cdr x))) type-env))
              ((and (consp x) (eq (car x) 'while)) (class <null>))
              ((and (consp x) (eq (car x) 'lambda)) (class <function>))
              ((and (consp x) (eq (car x) 'c-return)) (find-class (elt x 1) type-env))
              ((and (consp x) (macrop x)) (find-class (macroexpand-1 x) type-env))
              ((consp x) (class <object>))
              (t (class <object>))))

    (defun find-class-if (x type-env)
        (find-class (elt x 2) type-env))

    (defun find-class-cond (x type-env)
        (cond ((null x) (class <object>))
              (t (find-class (last (car x)) type-env))))

    (defun find-class-numeric (x type-env)
        (cond ((every (lambda (x) (let ((type (find-class x type-env)))
                            (or (null type) (eq type (class <object>)))))
                      (cdr x))
               (class <number>))
              ((every (lambda (x) (eq (class <fixnum>) (find-class x type-env)))
                      (cdr x))
               (class <fixnum>))
              ((any (lambda (x) (eq (class <float>) (find-class x type-env)))
                    (cdr x))
               (class <float>))
              ((any (lambda (x) (eq (class <integer>) (find-class x type-env)))
                    (cdr x))
               (class <integer>))
              ((any (lambda (x) (eq (class <fixnum>) (find-class x type-env)))
                    (cdr x))
               (class <integer>))
              (t (class <number>))))

    ;;reference symbol x in type-env
    (defun refer (x type-env)
        (let ((y (assoc x type-env)))
           (cond ((null y) (class <object>))
                 (t (cdr y)))))

    ;;assign type destructive in type-function
    ;;set output class
    (defun set-type-function-output (fn y)
        (let ((z (assoc fn type-function)))
           (setf (elt z 1) y)))

    ;;set input class
    (defun set-type-function-input (fn y)
        (let ((z (assoc fn type-function)))
           (setf (elt z 2) y)))

    ;;add local function type data
    (defun add-type-function-local (fn)
        (let ((z (assoc fn type-function)))
           (append! z (list local-type-function))))

    ;;local type-function
    ;;assign type destructive in local-type-function
    ;;set output class
    (defun set-local-type-function-output (fn y)
        (let ((z (assoc fn local-type-function)))
           (setf (elt z 1) y)))

    ;;set input class
    (defun set-local-type-function-input (fn y)
        (let ((z (assoc fn local-type-function)))
           (setf (elt z 2) y)))

    ;;if x is registed in type-function return not nil
    ;;elt return nil
    (defun type-function-p (x)
        (assoc x type-function))

    ;;if eq(x,y) subclassp(x,y) or subclassp(y,x),then unify is success
    ;;if success return type-env else return 'no.
    ;;type-env  ((x . (class integer))(x . (class <number>))(x . y))
    ;;first x unify number-class,second x unify integer-class.
    (defun unify (x y type-env)
        (cond ((and (not (variablep x)) (not (variablep y)))
               (let ((x1 (if (not (classp x))
                            (find-class x type-env)
                            x))
                     (y1 (if (not (classp y))
                            (find-class y type-env)
                            y)) )
                  (if (or (eq x1 y1) (subclassp* x1 y1) (subclassp* y1 x1))
                      type-env
                      'no)))
              ((and (variablep x) (not (variablep y)))
               (let ((x1 (refer x type-env))
                     (y1 (if (not (classp y))
                            (find-class y type-env)
                            y)) )
                  (cond ((null x1) (setq type-env (cons (cons x y1) type-env)) type-env)
                        ((eq x1 y1) type-env)
                        ((subclassp* x1 y1) type-env)
                        ((subclassp* y1 x1) (cons (cons x y1) type-env))
                        (t 'no))))
              ((and (not (variablep x)) (variablep y))
               (let ((x1 (if (not (classp x))
                            (find-class x type-env)
                            x))
                     (y1 (refer y type-env)) )
                  (cond ((null y1) (setq type-env (cons (cons y x1) type-env)) type-env)
                        ((eq x1 y1) type-env)
                        ((subclassp* x1 y1) (cons (cons y x1) type-env))
                        ((subclassp* y1 x1) type-env)
                        (t 'no))))
              (t (setq type-env (cons (cons x y) type-env)) type-env)))

    ;;symbol is variable in unify.
    ;;but nil and t are not variable.
    (defun variablep (x)
        (and (symbolp x) (not (null x)) (not (eq x t))))

    (defun subclassp* (x y)
        (cond ((or (eq x nil) (eq x t) (eq y nil) (eq y t)) nil)
              (t (subclassp x y))))

    ;;unify all data in ls with class.
    (defun estimate (ls class type-env)
        (for ((ls1 ls (cdr ls1)))
             ((null ls1)
              type-env )
             (cond ((not (symbolp (car ls1))) t)
                   (t (setq type-env (unify (car ls1) class type-env))))))

    (defun class* (x)
        (symbol-class x))

    ;;subr type data
    ;;       fn          output           input
    (assert parse-number (class <number>) (class <string>))
    (assert sin (class <float>) (class <number>))
    (assert cos (class <float>) (class <number>))
    (assert tan (class <float>) (class <number>))
    (assert atan (class <float>) (class <number>))
    (assert atan2 (class <float>) (class <number>) (class <number>))
    (assert sinh (class <float>) (class <number>))
    (assert cosh (class <float>) (class <number>))
    (assert tanh (class <float>) (class <number>))
    (assert floor (class <integer>) (class <number>))
    (assert ceiling (class <integer>) (class <number>))
    (assert truncate (class <integer>) (class <number>))
    (assert round (class <integer>) (class <number>))
    (assert mod (class <integer>) (class <integer>) (class <integer>))
    (assert div (class <integer>) (class <number>) (class <number>))
    (assert gcd (class <integer>) (class <integer>) (class <integer>))
    (assert lcm (class <integer>) (class <integer>) (class <integer>))
    (assert isqrt (class <number>) (class <integer>))
    (assert char=
            (class <object>)
            (class <character>)
            (class <character>))
    (assert char/=
            (class <object>)
            (class <character>)
            (class <character>))
    (assert char<
            (class <object>)
            (class <character>)
            (class <character>))
    (assert char>
            (class <object>)
            (class <character>)
            (class <character>))
    (assert char<=
            (class <object>)
            (class <character>)
            (class <character>))
    (assert char>=
            (class <object>)
            (class <character>)
            (class <character>))
    (assert quotient
            (class <number>)
            (class <number>)
            (class <number>))
    (assert reciprocal (class <number>) (class <number>))
    (assert max (class <number>) (class <number>) 'repeat)
    (assert min (class <number>) (class <number>) 'repeat)
    (assert abs (class <number>) (class <number>))
    (assert exp (class <number>) (class <number>))
    (assert log (class <number>) (class <number>))
    (assert expt (class <number>) (class <number>) (class <number>))
    (assert sqrt (class <number>) (class <number>))
    (assert cons (class <object>) (class <object>) (class <object>))
    (assert car (class <object>) (class <list>))
    (assert cdr (class <object>) (class <list>))
    (assert set-car (class <null>) (class <object>) (class <list>))
    (assert set-cdr (class <null>) (class <object>) (class <list>))
    (assert create-list (class <list>))
    (assertz create-list (class <list>) (class <integer>))
    (assert list (class <list>) (class <object>) 'repeat)
    (assert reverse (class <list>) (class <list>))
    (assert nreverse (class <list>) (class <list>))
    (assert assoc (class <list>) (class <object>) (class <list>))
    (assert member (class <object>) (class <object>) (class <list>))
    (assert mapcar
            (class <list>)
            (class <function>)
            (class <list>)
            'repeat)
    (assert mapc
            (class <list>)
            (class <function>)
            (class <list>)
            'repeat)
    (assert mapcan
            (class <list>)
            (class <function>)
            (class <list>)
            'repeat)
    (assert maplist
            (class <list>)
            (class <function>)
            (class <list>)
            'repeat)
    (assert mapcl
            (class <list>)
            (class <function>)
            (class <list>)
            'repeat)
    (assert mapcon
            (class <list>)
            (class <function>)
            (class <list>)
            'repeat)
    (assert create-array
            (class <basic-array>)
            (class <list>)
            (class <object>)
            'repeat)
    (assert array-dimensions (class <list>) (class <basic-array>))
    (assert create-vector (class <general-vector>) (class <integer>))
    (assert vector (class <general-vector>) (class <object>) 'repeat)
    (assert create-string
            (class <string>)
            (class <integer>)
            (class <object>)
            'repeat)
    (assert string=
            (class <object>)
            (class <string>)
            (class <string>))
    (assert string/=
            (class <object>)
            (class <string>)
            (class <string>))
    (assert string<
            (class <object>)
            (class <string>)
            (class <string>))
    (assert string>
            (class <object>)
            (class <string>)
            (class <string>))
    (assert string>=
            (class <object>)
            (class <string>)
            (class <string>))
    (assert string<=
            (class <object>)
            (class <string>)
            (class <string>))
    (assert funcall
            (class <object>)
            (class <function>)
            (class <object>)
            'repeat)
    (assert char-index (class <object>) (class <character>))
    (assertz char-index
             (class <object>)
             (class <character>)
             (class <integer>))
    (assert string-index
            (class <object>)
            (class <string>)
            (class <string>))
    (assertz string-index
             (class <object>)
             (class <string>)
             (class <string>)
             (class <integer>))
    (assert length (class <integer>) (class <list>))
    (assertz length (class <integer>) (class <general-vector>))
    (assertz length (class <integer>) (class <string>))
    (assert elt (class <object>) (class <list>) (class <integer>))
    (assertz elt
             (class <object>)
             (class <general-vector>)
             (class <integer>))
    (assertz elt (class <object>) (class <string>) (class <integer>))
    (assert null (class <symbol>) (class <object>))
    (assert eq (class <symbol>) (class <object>) (class <object>))
    (assert not (class <object>) (class <object>))
    (assert format
            (class <null>)
            (class <stream>)
            (class <string>)
            (class <object>)
            'repeat)
    (assert format-integer
            (class <null>)
            (class <stream>)
            (class <integer>)
            'repeat)
    (assert format-float
            (class <null>)
            (class <stream>)
            (class <float>)
            'repeat)
    (assert format-char
            (class <null>)
            (class <stream>)
            (class <character>)
            'repeat)
    (assert format-object
            (class <null>)
            (class <stream>)
            (class <object>)
            'repeat)
    (assert format-tab
            (class <null>)
            (class <stream>)
            (class <object>))
    (assert format-fresh-line (class <null>) (class <stream>))
    (assert standard-input (class <stream>))
    (assert standard-output (class <stream>))
    (assert system (class <string>))
    (assert open-input-file (class <string>))
    (assert open-output-file (class <stream>) (class <string>))
    (assert open-io-file (class <string>))
    (assert eval (class <object>) (class <object>))
    (assert atom (class <object>) (class <object>))
    (assert consp (class <object>) (class <object>))
    (assert symbolp (class <object>) (class <object>))
    (assert listp (class <object>) (class <object>))
    (assert consp (class <object>) (class <object>))
    (assert numberp (class <object>) (class <object>))
    (assert integerp (class <object>) (class <object>))
    (assert floatp (class <object>) (class <object>))
    (assert fixnump (class <object>) (class <object>))
    (assert longnump (class <object>) (class <object>))
    (assert bignump (class <object>) (class <object>))
    (assert stringp (class <object>) (class <object>))
    (assert characterp (class <object>) (class <object>))
    (assert functionp (class <object>) (class <object>))
    (assert general-vector-p (class <object>) (class <object>))
    (assert general-array*-p (class <object>) (class <object>))
    (assert property
            (class <object>)
            (class <symbol>)
            (class <symbol>))
    (assert set-property
            (class <object>)
            (class <object>)
            (class <symbol>)
            (class <symbol>))
    (assert read (class <object>))
    (assertz read (class <object>) (class <object>))
    (assertz read (class <object>) (class <object>) (class <object>))
    (assert eval (class <object>) (class <object>))
    (assert append
            (class <list>)
            (class <list>)
            (class <list>)
            'repeat)
    (assert error (class <object>) (class <string>))
    (assertz error (class <object>) (class <string>) (class <object>))
    (assert string-append (class <string>) (class <string>) 'repeat)
    (assert symbol-function (class <function>) (class <symbol>))
    (assert apply (class <function>) (class <object>) 'repeat)
    (assert print (class <null>) (class <object>))
    (assert aref
            (class <object>)
            (class <general-array*>)
            (class <integer>)
            'repeat)
    (assertz aref
             (class <object>)
             (class <general-vector>)
             (class <integer>))
    (assert garef
            (class <object>)
            (class <general-array*>)
            (class <integer>)
            'repeat)
    (assert set-aref
            (class <null>)
            (class <object>)
            (class <general-array*>)
            (class <integer>)
            (class <integer>))
    (assert array-dimensions (class <list>) (class <general-array*>))
    (assert create-array (class <general-array*>) (class <list>))
    (assert equal (class <object>) (class <object>) (class <object>))
    (assert instancep
            (class <object>)
            (class <object>)
            (class <object>))
    (assert open (class <stream>) (class <string>))
    (assert close (class <null>) (class <object>))
    (assert standard-input (class <stream>))
    (assert standard-output (class <stream>))
    (assert error-output (class <stream>))
    (assert create-string-input-stream (class <stream>))
    (assert create-string-output-stream (class <stream>))
    (assert get-output-stream-string
            (class <string>)
            (class <object>))
    (assert open-input-file (class <stream>))
    (assert open-output-file (class <stream>))
    (assert open-io-file (class <stream>))
    (assert finish-output (class <null>) (class <stream>))
    (assert eisl-ignore-toplevel-check
            (class <object>)
            (class <object>))
    (assert system (class <null>) (class <string>))
    (assert macroexpand-1 (class <list>) (class <list>))
    (assert eisl-get-method (class <object>) (class <object>))
    (assert eisl-get-method-body (class <object>) (class <object>))
    (assert eisl-get-method-priority
            (class <object>)
            (class <object>))
    (assert eisl-readed-array-list (class <object>) (class <object>))
    (assert class-of (class <object>) (class <object>))
    (assert subclassp
            (class <object>)
            (class <object>)
            (class <object>))
    (assert read-byte (class <object>) (class <stream>))
    (assert read-char (class <object>))
    (assertz read-char (class <object>) (class <stream>))
    (assert write-byte
            (class <null>)
            (class <object>)
            (class <stream>))
    (assert probe-file (class <object>) (class <string>))
    (assert file-position (class <integer>) (class <stream>))
    (assert set-file-position
            (class <integer>)
            (class <stream>)
            (class <integer>))
    (assert file-length
            (class <object>)
            (class <stream>)
            (class <integer>))
    (assert cerror
            (class <object>)
            (class <string>)
            (class <string>)
            (class <object>))
    (assert signal-condition
            (class <object>)
            (class <object>)
            (class <object>))
    (assert condition-continuable (class <object>) (class <object>))
    (assert continue-condition (class <object>) (class <object>))
    (assert arithmetic-error-operation
            (class <function>)
            (class <object>))
    (assert arithmetic-error-operands (class <list>) (class <object>))
    (assert domain-error-object (class <object>) (class <object>))
    (assert domain-error-expected-class
            (class <object>)
            (class <object>))
    (assert parse-error-string (class <string>) (class <object>))
    (assert parse-error-expected-class
            (class <object>)
            (class <object>))
    (assert simple-error-format-string
            (class <string>)
            (class <object>))
    (assert simple-error-format-arguments
            (class <list>)
            (class <object>))
    (assert stream-error-stream (class <stream>) (class <object>))
    (assert read-line (class <object>) (class <stream>))
    (assertz read-line
             (class <object>)
             (class <stream>)
             (class <object>))
    (assert subseq
            (class <string>)
            (class <string>)
            (class <integer>)
            (class <integer>))
    (assertz subseq
             (class <general-vector>)
             (class <general-vector>)
             (class <integer>)
             (class <integer>))
    (assertz subseq
             (class <list>)
             (class <list>)
             (class <integer>)
             (class <integer>))
    (assert random (class <integer>) (class <integer>))
    (assert random-real (class <float>))
    (assert eql (class <object>) (class <object>) (class <object>))
    (assert quotient
            (class <float>)
            (class <number>)
            (class <number>))
    (assert subrp (class <object>) (class <object>))
    (assert c-lang (class <null>) (class <string>))
    (assert eisl-modulesubst
            (class <object>)
            (class <object>)
            (class <symbol>)
            (class <symbol>))
    
)
