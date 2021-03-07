
 (defun domain-error-handler (condition)
   (let ((data ()))
     (setq data
	   (cons (domain-error-object condition)
		 (domain-error-expected-class condition)))
     (throw 'c-domain-error data)))
;;; <basic-array>
(defglobal data nil)

(setq data
	     (catch 'c-domain-error
	       (with-handler #'domain-error-handler
			     (aref 1))))

