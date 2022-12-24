;; Doctor 
(import "elixir")

(defglobal flag nil)

(defun string->list (str)
    (string->list1 (capitalize (convert str <list>)) "" nil))

(defun string->list1 (ls word result)
    (cond ((null ls) (reverse (cons (convert word <symbol>) result)))
          ((char= (car ls) #\space) (string->list1 (cdr ls) "" (cons (convert word <symbol>) result)))
          (t (string->list1 (cdr ls) (string-append word (convert (car ls) <string>)) result))))

(defun capitalize (ls)
    (mapcar (lambda (x) (capitalize1 x)) ls))

(defun capitalize1 (c)
    (let ((i (convert c <integer>)))
        (if (and (>= i 97)(<= i 122))
            (convert (- i 32) <character>)
            c)))

(defun print-list (ls para)
    (if (null (cdr ls))
        (cond ((eq para 'p) (format (standard-output) "~A.~%" (car ls)))
              ((eq para 'q) (format (standard-output) "~A?~%" (car ls)))
              (t (format (standard-output) "~A~%" (car ls))))
        (progn (format (standard-output) "~A " (car ls)) (print-list (cdr ls) para))))

(defun doctor ()
    (format (standard-output) "Hi!,I am a doctor~%")
    (format (standard-output) "   Speak up~%")
    (let ((input nil))
        (while (not (equal input '(stop)))
            (setq input (string->list (read-line)))
            (print input)
            (rule input))))

(defpattern rule
    (((I am worried about :rest _x)) (print-list (append '(How long have you been worried) _x) 'p))
    (((stop)) (setq flag nil) (print-list '(I am sorry our time is up) 'p))
    ((_x)(when (member 'mother _x)) (setq flag t) (print-list '(Tell me more about your family) `p))
    ((_x)(when (member 'computer _x)) (print-list '(Do machines frighten you) 'q))
    (((yes)) (print-list '(Please do not be so short with me) 'p))
    (((no)) (print-list '(Please do not be so short with me) `p))
    (((_x))(when (= (length (convert _x <string>)) 4)) (print-list '(Please do not use Words like that) 'p))
    ((_)(when (not (null flag))) (setq flag nil) (print-list '(Earlier you spoke of your mother) 'p))
    ((_)(when (null flag)) (print-list '(You say so before, too) 'q))
    ((_) (print-list '(I see,tell me more) `p)))

