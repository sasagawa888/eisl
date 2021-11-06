(import "test")

(defgeneric (setf foo-18) (x y z))
(defmethod (setf foo-18) (x y z) (list x y z))
($test (setf (foo-18 1 2) 3) (3 1 2) equal)
($error (setf (foo-18 1) 2) <program-error>)
($error (setf (foo-18 1 2 3) 4) <program-error>)
($error (setf (bar 1 2) 3) <error>)
;;
($eval (defgeneric (setf nil) (x y z)))
($eval (defmethod (setf nil) (x y z) (list x y z)))
($test (setf (nil 1 2) 3) (3 1 2) equal)
($error (setf (nil 1) 2) <program-error>)
($error (setf (nil 1 2 3) 4) <program-error>)

