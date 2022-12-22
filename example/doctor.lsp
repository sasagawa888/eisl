;; Doctor 
(defglobal flag nil)

(defun string->list (str)
    (string->list1 (convert str <list>) "" nil))

(defun string->list1 (ls word result)
    (cond ((null ls) (reverse (cons (convert word <symbol>) result)))
          ((char= (car ls) #\space) (string->list1 (cdr ls) "" (cons (convert word <symbol>) result)))
          (t (string->list1 (cdr ls) (string-append word (convert (car ls) <string>)) result))))

(defun list->string (ls)
    (if (null ls)
        ""
        (string-append (convert (car ls) <string>) " " (list->string (cdr ls)))))

(defun doctor ()
    (format (standard-output) "Hi!,I am a doctor~%")
    (format (standard-output) "   Speak up~%")
)

(defpattern rule
    (((I am worried about :rest _x)) (append '(How long have you been worried) _x))
    (((stop)) '(I am sorry our time is up))
    ((_x)(when (member 'mother _x)) (setq flag t) '(Tell me more about your family))
    ((_x)(when (member 'computer _x)) '(Do machines frighten you?))
    (((yes)) '(Please do not be so short with me))
    (((no)) '(Please do not be so short with me))
    ((_x)(when (= (lentgh (convert _x <string>)) 4)) '(Please do not use Words like that))
    ((_)(when (not (null flag))) (setq flag nil) '(Earlier you spoke of your mother))
    ((_) '(I see,tell me more)))


