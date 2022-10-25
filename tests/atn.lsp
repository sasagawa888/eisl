#|
ATN Argumented Transition Network
((subj (det the) (n dog)) (v bites) (o (n postman)) ) 

s subject
n noun
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
      (dog n)
      (book n)
      (postman n)
      (jhon  npr)
      (mary npr)
      (bites tv)
      (runs iv)
      (likes tv)))

(defun part (x)
    (elt (assoc x dictionary) 1))


(defun start (s)
    (atn t s nil))

(defpattern atn
    ((t (_x :rest _y) _stack) (when (eq (part _x) 'det))
     (atn 's/det _y `(det ,_x)))
    ((s/det (_x :rest _y) _stack) (when (eq (part _x) 'n))
     (cons `(s ,_stack (n ,_x) ) (atn 's/n _y nil)))
    ((s/n (_x :rest _y) _stack) (when (eq (part _x) 'tv))
     (cons `(v (tv ,_x)) (atn 'o _y _stack)))
    ((o empty _stack) nil) 
    ((o (_x :rest _y) _stack) (when (eq (part _x) 'n))
     (cons `(o (n ,_x)) (atn 'o _y _stack)))
    ((c empty _stack) nil)
    ((_x _y _stack) (error "syntax-error" (list _x _y))))
    



