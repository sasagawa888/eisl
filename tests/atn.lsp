#|
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
    ((t _x)
     (let ((cont (atn 'np/ _x))) (cons `(s ,@reg) (atn 's/ cont))))
    ((s/ _x)
     (let ((cont (atn 'vp/ _x)))
        (cond ((transitivep reg) (cons `(v ,@reg) (atn 'v/ cont)))
              ((intransitivep reg) `((v ,@reg))))))
    ((v/ _x)
     (let ((cont (atn 'np/ _x))) (cons `(o ,@reg) (atn 'o/ cont))))
    ((o/ empty) nil)
    ;; noun phrase
    ((np/ (_x :rest _y)) (when (eq (part _x) 'det))
     (setr `(det ,_x)) (atn 'np/det/ _y))
    ((np/ (_x :rest _y)) (when (eq (part _x) 'n))
     (setr `(n ,_x)) _y)
    ((np/det/ (_x :rest _y)) (when (eq (part _x) 'n))
     (setr `(,reg (n ,_x))) _y)
    ;; verb phrase
    ((vp/ (_x :rest _y)) (when (eq (part _x) 'vt))
     (setr `((vt ,_x))) _y)
    ((vp/ (_x :rest _y)) (when (eq (part _x) 'vi))
     (setr `((vi ,_x))) _y)
    ((vp/ (_x :rest _y)) (when (eq (part _x) 'adv))
     (setr `(adv ,_x)) (atn 'vp/adv/ _y))
    ((vp/ (_x :rest _y)) (when (eq (part _x) 'aux))
     (setr `(aux ,_x)) (atn 'vp/aux/ _y))
    ((vp/adv/ (_x :rest _y)) (when (eq (part _x) 'vt))
     (setr `(,reg (vt ,_x))) _y)
    ((vp/adv/ (_x :rest _y)) (when (eq (part _x) 'vi))
     (setr `(,reg (vi ,_x))) _y)
    ((vp/aux/ (_x :rest _y)) (when (eq (part _x) 'vt))
     (setr `(,reg (vt ,_x))) _y)
    ((vp/aux/ (_x :rest _y)) (when (eq (part _x) 'vi))
     (setr `(,reg (vi ,_x))) _y)
    ;; syntax error
    ((_x _y) (error "syntax-error" (list _x _y))))
    

(defun setr (x) 
    (setq reg x))


(defun intransitivep (x)
    (cond ((null x) nil)
          ((and (consp (car x)) (eq (car (car x)) 'vi)) t)
          (t (intransitivep (cdr x)))))

(defun transitivep (x)
    (cond ((null x) nil)
          ((and (consp (car x)) (eq (car (car x)) 'vt)) t)
          (t (transitivep (cdr x)))))