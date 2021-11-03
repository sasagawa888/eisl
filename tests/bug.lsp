
(defgeneric foo-36 (a b &rest c)
   (:method (a b &rest c)
	    (list 'default a b))
   (:method ((a <string>) (b <string>) &rest c)
	    (list (call-next-method) (string-append a b)))
   (:method ((a <integer>) (b <number>) &rest c)
	    (list (call-next-method) (list 'number a b)))
   (:method ((a <integer>) (b <integer>) &rest c)
	    (let ((x (list (foo-36 "foo" "bar" "yab"))))
	      ;;
	      (setq a (* a 10))
	      (setq b (* b 10))
	      (if (next-method-p)
		  (setq x (cons (call-next-method) x)))
	      (setq x (cons (list a b c) x))
	      x)))

;($test (foo-36 4 5 6 7 8)
; ((40 50 (6 7 8))
;  ((default 4 5) (number 4 5))
;  ((default "foo" "bar") "foobar"))
; equal)
;;


(defun disp (x)
    (mapcar #'eisl-get-method-body (eisl-get-method x)))