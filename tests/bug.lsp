
 (defun domain-error-handler (condition)
   (let ((data ()))
     (setq data
	   (cons (domain-error-object condition)
		 (domain-error-expected-class condition)))
     (throw 'c-domain-error data)))

(defglobal data nil)
(setq data (catch 'c-domain-error
		    (with-handler #'domain-error-handler
				  (arithmetic-error-operation 1))))
 