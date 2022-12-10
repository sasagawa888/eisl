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
|# 

(import "elixir")
(import "formula")

(defglobal dt 
 '(program gcd
     (const (x = 10)(y = 45))
     (var z)
     (procedure gcd1 
        ((var a b)
         (a := x) (b := y)
         (while (a /= b) do
            ((if (a < b) then (b := (b - a)) else (a := (a - b)))))
         (z := a)))
     ((call gcd1)
      (write z))))

(defun compile (x) (comp x nil))

(defpattern comp
    (((program _x :rest _y) _type) `(defmodule ,_x ,@(comp-block _y _type))))

(defpattern comp-block 
    ((empty _type) nil)
    ((((const :rest _x) :rest _r) _type) (append (comp-const _x _type) (comp-block _r _type)))
    ((((var :rest _x) :rest _r) _type) (append (comp-var _x _type) (comp-block _r _type)))
    ((((procedure _x :rest _y) _r) _type) (cons (comp-procedure _x (car _y) _type) (comp-block _r _type)))
    ((_x _type) (comp-statement _x _type)))
    

(defpattern comp-const
    ((empty _type) nil)
    ((((_x = _y) :rest _r) _type) (cons `(defconstant ,_x ,_y) (comp-const _r _type))))

(defpattern comp-var
    ((empty _type) nil)
    (((_x :rest _r) _type) (cons `(defglobal ,_x nil) (comp-var _r _type))))

(defun comp-procedure (name body type)
    `(defun ,name nil ,(comp-body body type)))

(defpattern comp-body
     ((empty _type) nil)
     ((((var :rest _x) :rest _r) _type) `(let ,(let-var _x) ,@(comp-body _r _type)))
     ((_x _type) (comp-statement _x _type)))

(defpattern comp-statement
    ((empty _type) nil)
    ((((_x := _y) :rest _r) _type) (cons `(setq ,_x ,(infix->prefix _y)) (comp-statement _r _type)))
    ((((while _x do _y) :rest _r) _type) (cons `(while ,(infix->prefix _x) ,@(comp-statement _y _type))
                                                (comp-statement _r _type)))
    ((((if _x then _y else _z) :rest _r) _type) (cons `(if ,(infix->prefix _x) 
                                                           ,@(comp-statement (list _y) _type)
                                                           ,@(comp-statement (list _z) _type))
                                               (comp-statement _r _type)))
    ((((call _x) :rest _r) _type) (cons `(,_x) (comp-statement _r _type)))
    ((((write _x) :rest _r) _type) (cons `(format (standard-output) "~A",_x) (comp-statement _r _type)))
    ((_x _type) (error "syntax-error" _x)))


(defun let-var (x)
    (if (null x)
        nil
        (cons (list (car x) nil)
              (let-var (cdr x)))))