(defglobal cc nil)

(defmacro catch-condition (&rest form)
	 `(catch 'c
	    (with-handler 
	     (lambda (c) 
	       (setq cc c) 
	       (throw 'c cc))
	     ,@form)))

(setq cc (catch-condition (let ($test (str (create-string-input-stream "hi")))
	      (read-char str)
	      (read-char str)
	      (read-char str))))