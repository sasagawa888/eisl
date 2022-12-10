;;pascal instant compiler

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
      (print z))))

(defun compile (x) (parse x nil))

(defpattern parse
    (((program _x :rest _y) _type) `(defmodule ,_x ,@(parse-program _y _type))))

(defpattern parse-program 
    ((empty _type) nil)
    ((((const :rest _x) :rest _r) _type) (append (parse-const _x _type) (parse-program _r _type)))
    ((((var :rest _x) :rest _r) _type) (append (parse-var _x _type) (parse-program _r _type)))
    ((((procedure _x :rest _y) _r) _type) (cons (procedure _x (car _y) _type) (parse-program _r _type)))
    ((((call _x) :rest _r) _type) (cons `(,_x) (parse-program _r _type)))
    ((((print _x) :rest _r) _type) (cons `(print ,_x) (parse-program _r _type))))

(defpattern parse-const
    ((empty _type) nil)
    ((((_x = _y) :rest _r) _type) (cons `(defconstant ,_x ,_y) (parse-const _r _type))))

(defpattern parse-var
    ((empty _type) nil)
    (((_x :rest _r) _type) (cons `(defglobal ,_x nil) (parse-var _r _type))))

(defun procedure (name body type)
    `(defun ,name nil ,(parse-procedure body type)))


(defpattern parse-procedure
    ((empty _type) nil)
    ((((var :rest _x) :rest _r) _type) `(let ,(let-var _x) ,@(parse-procedure _r _type)))
    ((((_x := _y) :rest _r) _type) (cons `(setq ,_x ,(infix->prefix _y)) (parse-procedure _r _type)))
    ((((while _x do _y) :rest _r) _type) (cons `(while ,(infix->prefix _x) ,@(parse-procedure _y _type))
                                                (parse-procedure _r _type)))
    ((((if _x then _y else _z) :rest _r) _type) (cons `(if ,(infix->prefix _x) 
                                                           ,@(parse-procedure (list _y) _type)
                                                           ,@(parse-procedure (list _z) _type))
                                               (parse-procedure _r _type)))
    ((_x _type) _x))


(defun let-var (x)
    (if (null x)
        nil
        (cons (list (car x) nil)
              (let-var (cdr x)))))