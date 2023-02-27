(defun domain-error-handler (condition)
   (let ((data ()))
     (setq data
	   (cons (domain-error-object condition)
		 (domain-error-expected-class condition)))
     (throw 'c-domain-error data)))
	 
(defglobal data nil)
;;; <stream-error>
(defglobal data nil)
(setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (stream-error-stream 1))))
($test (car data) 1 eql)
($test (eq (cdr data) (class <stream-error>)) t)

