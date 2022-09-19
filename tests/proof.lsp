(import "elixir")

(defpattern cnf
    ;; simple logic
    ((_x)(when (atom _x)) _x)
    ;; de-morgan
    (((~ (& _x _y))) (display 'rule-1) (cnf `(v (~ ,_x) (~ ,_y))))
    ;; double negation
    (((~ (~ _x))) (display 'rule-2) (cnf _x)) 
    ;; distributive law
    (((v (& _a _b) (& _a _c))) (display 'rule-3) (cnf `(& ,_a (v ,_b ,_c))))
    ;; recursive and
    (((& _a _b)) (display 'rule-4) (let ((a1 (cnf _a))(b1 (cnf _b))) `(& ,a1 ,b1)))
    ;; recursive or
    (((v _a _b)) (display 'rule-5) (let ((a1 (cnf _a))(b1 (cnf _b))) `(v ,a1 ,b1)))
    ;; recursive negation
    (((~ _a)) (display 'rule-6) (let ((a1 (cnf _a))) `(~ ,a1)))
    ;; imply
    (((-> _a _b)) (display 'rule-7) (cnf `(v (~ ,_a) ,_b))))
    



(defun display (x)
    (format (standard-output) "~A-> " x))

(defglobal exp1 '(~ (& a (~ (& a (~ b))))))
