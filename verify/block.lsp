(import "test")

($eval 
 (defun bar-2 (x y)
   (let ((foo #'car))
     (let ((result
	    (block bl
		   (setq foo (lambda () (return-from bl 'first-exit)))
		   (if x (return-from bl 'second-exit) 'third-exit))))
       (if y (funcall foo) nil)
       result))))
($test (bar-2 t nil) second-exit)
($test (bar-2 nil nil) third-exit)
($error (bar-2 nil t) <control-error>)
($error (bar-2 t t) <control-error>)