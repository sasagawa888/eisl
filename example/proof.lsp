#|
CNF for toy prover
and  ^
or   v
not  ~
imply ->
CNF (AvB)^(CvD) (in logic) -> ((A B)(C D)) (in lisp)
|#


(import "elixir")
(import "test")

(defun foo (x)
    (cnf (and-or-not x)))

;; Conjunctive normal form
(defpattern cnf 
    ;; simple logic
    ((_x)(when (atom _x)) _x)
    ;; de-morgan
    (((~ (^ _x _y))) (cnf `(v (~ ,_x) (~ ,_y))))
    (((~ (v _x _y))) (cnf `(^ (~ ,_x) (~ ,_y))))
    ;; double negation
    (((~ (~ _x))) (cnf _x)) 
    ;; negation
    (((~ _x)) (let ((x1 (cnf _x))) `(~ ,x1)))
    ;; conjunction
    (((^ _x _y)) (let ((x1 (cnf _x)) (y1 (cnf _y))) `(,x1 ,y1)))
    ;; disjunction
    (((v (^ _a _b) (^ _c _d)))
     (let ((a1 (cnf _a))(b1 (cnf _b))(c1 (cnf _c))(d1 (cnf _d))) `((,a1 ,c1)(,a1 ,d1)(,b1 ,c1)(,b1 ,d1))))
    (((v _a (^ _b _c))) (let ((a1 (cnf _a))(b1 (cnf _b))(c1 (cnf _c))) `((,a1 ,b1)(,a1 ,c1))))
    (((v (^ _a _b) _c)) (let ((a1 (cnf _a))(b1 (cnf _b))(c1 (cnf _c))) `((,a1 ,c1)(,b1 ,c1))))
    (((v _a (v _b _c))) (let ((a1 (cnf _a))(b1 (cnf _b))(c1 (cnf _c))) `((,a1 ,b1 ,c1))))
    (((v _a _b)) (let ((a1 (cnf _a)) (b1 (cnf _b))) `(,a1 ,b1)))
)

(defpattern and-or-not
    ;; simple logic
    ((_x)(when (atom _x)) _x)
    ;; imply
    (((-> _a _b)) (and-or-not `(v (~ ,_a) ,_b)))
    ;; recursive or
    (((v _a _b)) (let ((a1 (and-or-not _a))(b1 (and-or-not _b))) `(v ,a1 ,b1)))
    ;; recursive negation
    (((~ _a)) (let ((a1 (and-or-not _a))) `(~ ,a1))))
  

($test (foo '(-> a (-> b c))) (((~ a) (~ b) c)))
($test (foo '(-> a (-> b a))) (((~ a) (~ b) a)))
($test (cnf '(~ (^ a (~ (^ a (~ b))))))  ((~ a) (a (~ b))))
($test (cnf '(~ (~ a))) a)
($test (cnf '(~ (~ (~ (~ a))))) a)
($test (and-or-not '(-> a (-> b c))) (v (~ a) (v (~ b) c)))
($test (and-or-not '(-> a (-> b a))) (v (~ a) (v (~ b) a)))

