#|
study of English grammar (under construction)
ATN Argumented Transition Network 
((subj (det the) (n dog)) (v (vt bites)) (o (n postman)) ) 

s subject
n noun
npr noun pronoun
np noun phrase
det determiner
v verb
vt  verb transitvie
vi  verb intransitvie
vp verb phrase
aux auxiliary
adv adverb
adj adjectvie
o object
c complement

basic grammar
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
      (can aux)
      (beautiful adj)
      (bites vt)
      (runs vi)
      (likes vt)))

(defglobal reg nil)

(defun part (x)
    (let ((y (assoc x dictionary)))
        (if (null y) (error "not exist dictionary" x)
            (elt y 1))))


(defun start (s)
    (atn t s))

(defpattern atn
    ;; sentence SV SVO SVC SVOO SVOC
    ((t _x)
     (let ((cont (atn 'np/ _x))) (cons `(s ,@(popr)) (atn 's/ cont))))
    ((s/ _x)
     (let ((cont (atn 'vp/ _x)))
        (cond ((transitivep reg) (cons `(v ,@(popr)) (atn 'v/ cont)))
              ((intransitivep reg) (cons `(v ,@(popr)) nil)))))
    ((v/ _x)
     (let ((cont (atn 'np/ _x))) (cons `(o ,@(popr)) (atn 'o/ cont))))
    ((o/ empty) nil)
    ;; noun phrase
    ((np/ (_x :rest _y)) (when (member (part _x) '(det adj)))
     (pushr `(,(part _x) ,_x)) (atn 'np/ _y))
    ((np/ (_x :rest _y)) (when (eq (part _x) 'n))
     (pushr `(n ,_x)) _y)
    ;; verb phrase
    ((vp/ (_x :rest _y)) (when (member (part _x) '(vt vi)))
     (pushr `(,(part _x) ,_x)) _y)
    ((vp/ (_x :rest _y)) (when (member (part _x) '(adv aux)))
     (pushr `(,(part _x) ,_x)) (atn 'vp/ _y))
    ;; syntax error
    ((_x _y) (error "syntax-error" (list _x _y))))
    

(defun setr (x) 
    (setq reg x))

(defun pushr (x)
    (setq reg (cons x reg)))

(defun popr ()
    (let ((y (reverse reg)))
        (setq reg nil)
        y))

(defun intransitivep (x)
    (cond ((null x) nil)
          ((and (consp (car x)) (eq (car (car x)) 'vi)) t)
          (t (intransitivep (cdr x)))))

(defun transitivep (x)
    (cond ((null x) nil)
          ((and (consp (car x)) (eq (car (car x)) 'vt)) t)
          (t (transitivep (cdr x)))))