

(defun test10 ()
  ;; labels + mapcar, but no lambda calls labels-local function
  (labels ((square (x)
             (* x x)))
    (mapcar #'square '(1 2 3 4))))