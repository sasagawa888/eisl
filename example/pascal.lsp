#| 
PL/0 instant compiler

program = block "." .

block = [ "const" ident "=" number {"," ident "=" number} ";"]
        [ "var" ident {"," ident} ";"]
        { "procedure" ident ";" block ";" } statement .
statement = [ ident ":=" expression | "call" ident |
            "begin" statement {";" statement } "end" |
            "if" condition "then" statement |
            "while" condition "do" statement ].
condition = "odd" expression |
            expression ("="|"#"|"<"|"<="|">"|">=") expression .
expression = [ "+"|"-"] term { ("+"|"-") term}.
term = factor {("*"|"/") factor}.
factor = ident | number | "(" expression ")".

usage 
e.g.
(compile-file "example/gcd.pas")

Compiler generates exmaple/gcd.lsp
|# 

(import "elixir")
(import "formula")
(import "formatter")

(defun compile-file (filename)
        (let* ((filename* (string-append (subseq filename 0 (char-index #\. filename)) ".lsp"))
               (instream (open-input-file filename))
               (outstream (open-output-file filename*))
               (sexp nil))
           (while (not (file-end-p sexp))
              (setq sexp (compile (read instream nil "the end")))
              (if (not (file-end-p sexp))
                  (format outstream "~A~%" sexp)))
           (close instream)
           (close outstream)
           (formatter filename*))
        t)

(defun file-end-p (x)
        (and (stringp x) (string= x "the end")))

(defun compile (x) 
    (if (file-end-p x)
        x
        (comp x)))

(defpattern comp
    (((program _x :rest _y)) `(defmodule ,_x ,@(comp-block _y))))

(defpattern comp-block 
    ((empty) nil)
    ((((const :rest _x) :rest _r)) (append (comp-const _x) (comp-block _r)))
    ((((var :rest _x) :rest _r)) (append (comp-var _x) (comp-block _r)))
    ((((procedure _x :rest _y) _r)) (cons (comp-procedure _x (car _y)) (comp-block _r)))
    ((_x) (comp-statement _x)))
    

(defpattern comp-const
    ((empty) nil)
    ((((_x = _y) :rest _r)) (cons `(defconstant ,_x ,_y) (comp-const _r))))

(defpattern comp-var
    ((empty) nil)
    (((_x :rest _r)) (cons `(defglobal ,_x nil) (comp-var _r))))

(defun comp-procedure (name body)
    `(defun ,name nil ,(comp-body body)))

(defpattern comp-body
     ((empty) nil)
     ((((var :rest _x) :rest _r)) `(let ,(let-var _x) ,@(comp-body _r)))
     ((((const :rest _x) :rest _r)) `(let ,(let-const _x) ,@(comp-body)))
     ((_x) (comp-statement _x)))

(defpattern comp-statement
    ((empty) nil)
    ((((_x := _y) :rest _r)) (cons `(setq ,_x ,(infix->prefix _y)) (comp-statement _r)))
    ((((while _x do _y) :rest _r)) (cons `(while ,(infix->prefix _x) ,@(comp-statement (list _y)))
                                                (comp-statement _r)))
    ((((if _x then _y else _z) :rest _r)) (cons `(if ,(infix->prefix _x) 
                                                           ,@(comp-statement (list _y))
                                                           ,@(comp-statement (list _z)))
                                               (comp-statement _r)))
    ((((call _x) :rest _r)) (cons `(,_x) (comp-statement _r)))
    ((((write _x) :rest _r)) (cons `(format (standard-output) "~A",_x) (comp-statement _r)))
    ((_x) (error "syntax-error" _x)))


(defun let-var (x)
    (if (null x)
        nil
        (cons (list (car x) nil)
              (let-var (cdr x)))))

(defun let-const (x)
    (if (null x)
        nil
        (cons (list (elt (car x 0)) (elt (car x) 2))
              (let-const (cdr x)))))