(import "test")

;;
($eval (defgeneric foo-g-3 (x)))
($error (defmethod foo-g-3 ((x undef))) <undefined-entity>)
($error (defgeneric foo-g-3 (x)
	  (:method ((x undef))))
	<undefined-entity>)
;;