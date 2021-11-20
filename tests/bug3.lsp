(defgeneric foo-31 (x)
   (:method ((x <integer>))
	    (lambda (y) (* y (call-next-method))))
   (:method ((x <number>))
	    (* x x)))

(defglobal x (foo-31 3))
;($test (funcall x 5) 45 eql)
;($test (funcall x 5) 45 eql)
;;