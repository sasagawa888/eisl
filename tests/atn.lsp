#|
ATN Argumented Transition Network
((subj (det the) (n dog)) (v bytes) (o (n postman)) ) 

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
      (jhon  npr)
      (mary npr)
      (bytes tv)
      (runs iv)
      (likes tv)))

(defun part (x)
    (elt (assoc x dictionaly) 1))


(defun start (s)
    (atn s np/))

(defpattern atn
    ((t (_x :rest _y) _stack) (when (eq (part _x) 'det))
     (atn s/det _y `(det ,_x)))
    ((s/det (_x :rest _y) _stack) (when (eq (part _x) 'n))
     (cons `(s ,_stack (n ,_x) ) (atn s/n _y )
    ((s/n (_x :rest _y) _stack) (when (eq (part _x) 'tv))
     (atn o `(o  ))
    ((o      (_x :rest _y) _stack) t)
    ((c      (_x :rest _y) _stack) t)))))
    



