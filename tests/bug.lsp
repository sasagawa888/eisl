(defgeneric plus (x y))

(defmethod plus ((x <integer>)(y <integer>))
    (+ x y))

(defmethod plus ((x <float>)(y <float>))
    (+ x y))
