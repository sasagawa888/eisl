(defglobal f nil)
(defgeneric foo-39 (x y))
(defmethod foo-39 (x y) (list x y))
(defmethod foo-39 ((x <integer>) (y <integer>))
	 (setq x (* x 10))
	 (setq y (* y 10))
	 (setq f (lambda () 
		   (if (next-method-p) (list x y (call-next-method)))))
	 (list x y))

;($test (foo-39 2 3) (20 30) equal)
;($test (funcall f) (20 30 (2 3)) equal)
;;
