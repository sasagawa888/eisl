#|
ATN Argumented Transition Network
((subj (det the) (n dog)) (v bites) (o (n postman)) ) 

s subject
n noun
np noun phrase
det determiner
v verb
tv transitive verb 
iv intransitive verb
o object
c complement

basic grammer
S V
S V C
S V O 
S V O O
S V O C

|#

(import "elixir")

;; dictionary
(defconstant dictionary 
    '((the det)
      (a det)
      (dog n)
      (book n)
      (postman n)
      (jhon  npr)
      (mary npr)
      (bites tv)
      (runs iv)
      (likes tv)))

(defglobal reg nil)

(defun part (x)
    (elt (assoc x dictionary) 1))


(defun start (s)
    (atn t s))

(defpattern atn
    ((t _x)
     (let ((succ (atn 'np _x))) (cons `(s ,reg) (atn 's succ))))
    ((s (_x :rest _y)) (when (eq (part _x) 'tv))
     (cons `(v (tv ,_x)) (atn 'tv _y)))
    ((s (_x :rest _y)) (when (eq (part _x) 'iv))
     (cons `(v (iv ,_x)) (atn 'iv _y)))
    ((tv _x)
     (let ((succ (atn 'np _x))) (cons `(o ,reg) (atn 'o succ))))
    ((iv _x) nil)
    ((o empty) nil)
    ((np (_x :rest _y)) (when (eq (part _x) 'det))
     (setr `(det ,_x)) (atn 'np/det _y))
    ((np (_x :rest _y)) (when (eq (part _x) 'n))
     (setr `(n ,_x)) _y)
    ((np/det (_x :rest _y)) (when (eq (part _x) 'n))
     (setr `(,reg (n ,_x))) _y)
    ((_x _y) (error "syntax-error" (list _x _y))))
    

(defun setr (x) 
    (setq reg x))

