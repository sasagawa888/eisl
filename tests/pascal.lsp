;;pascal instant compiler

(import "elixir")

(defpattern parse
    (((program _x :rest _y) _type) (parse-program _y _type)))

(defpattern parse-program 
    ((((const :rest _x) :rest _r) _type) (cons (parse-const _x _type) (parse-program _r _type)))
    ((((var :rest x) :rest _r) _type) (cons (parse-var _x _type) (parse-program _r _type)))
    ((((procedure _x :rest _y) _r) _type) (cons (parse-procedure _x _y _type) (parse-program _r _type)))
    ((((call _x) :rest _r) _type) (cons (parse-call _x _type) (parse-program _r _type))))

(defpattern parse-const
    ((empty _type) nil)
    ((((_x = _y) :rest _r) _type) (cons `(defconstant ,_x ,_y) (parse-const _r _type))))

