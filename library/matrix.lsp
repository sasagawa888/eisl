(defmodule matrix
           (import "seq" map every reduce concatenate)

           (defun check-matrix (array)
             (when (/= (length (array-dimensions array)) 
                       2)
               (Error "Argument must be a matrix")))

           (defun rows (matrix)
             (check-matrix matrix)
             (let* ((dimensions (array-dimensions matrix))
                    (number-of-rows (elt dimensions 0))
                    (number-of-columns (elt dimensions 1))
                    (rows (create-vector number-of-rows))
                    )
               (dotimes (row-index number-of-rows)
                 (let ((fields (create-vector number-of-columns))) 
                   (dotimes (column-index number-of-columns)
                     (setf (elt fields column-index) 
                           (aref matrix row-index column-index)))
                   (setf (elt rows row-index) fields)))
               rows))

           (defun rows->matrix (rows)
             (let* ((dimensions (vector-of-vectors-dimensions rows))
                    (number-of-rows (elt dimensions 0))
                    (number-of-columns (elt dimensions 1))
                    (matrix (create-array (convert dimensions <list>))))
               (dotimes (row-index number-of-rows)
                 (let ((row (elt rows row-index))) 
                   (dotimes (col-index number-of-columns)
                     (setf (garef matrix row-index col-index)
                           (elt row col-index)))))
               matrix))

           (defun columns->matrix (columns)
             (transpose (rows->matrix columns)))

           (defgeneric transpose (x))

           (defmethod transpose ((matrix <general-array*>))
             (check-matrix matrix)
             (let ((matrix-columns (columns matrix))) 
               (if (= (length matrix-columns) 1) 
                   (elt matrix-columns 0)
                   (rows->matrix matrix-columns))))

           (defmethod transpose ((vector <general-vector>))
             (columns->matrix (vector vector)))

           (defun columns (matrix)
             (check-matrix matrix)
             (let ((get-col (lambda (&rest column-fields) (convert column-fields <general-vector>)))
                   (map (function map)))
               (apply map '<general-vector> get-col (convert (rows matrix) <list>))))

           (defun vector-of-vectors-dimensions (vector-of-vectors)
             (let ((first-vector-length (length (elt vector-of-vectors 0))))
               (if (every (lambda (vector) 
                            (= (length vector) first-vector-length)) 
                          vector-of-vectors)
                   (vector (length vector-of-vectors) first-vector-length)
                   (error "All sub-vectors must have the same length"))))

           (defun check-same-dimensions (x y)
             (when (not (equal (array-dimensions x) (array-dimensions y)))
               (error "All arguments must have the same dimensions")))

           (defgeneric element-operate-2 (operator x y))

           (defmethod element-operate-2 ((operator <function>) x y)
             (funcall operator x y))

           (defmethod element-operate-2 ((operator <function>) (x <general-vector>) (y <general-vector>)) 
             (check-same-dimensions x y)
             (map '<general-vector> (lambda (x y) (element-operate-2 operator x y)) x y))

           (defmethod element-operate-2 ((operator <function>) (x <general-array*>) (y <general-array*>))
             (check-matrix x)
             (check-matrix y)
             (check-same-dimensions x y)
             (rows->matrix 
               (map '<general-vector> (lambda (x y) (element-operate-2 operator x y)) (rows x) (rows y))))

           (defun element-operate (dyadic-operator &rest operands)
             (reduce (lambda (x y) (element-operate-2 dyadic-operator x y)) 
                     (car operands) 
                     (cdr operands)))

           (defun add (&rest operands)
             (apply #'element-operate #'+ operands))

           (defun sub (&rest operands)
             (apply #'element-operate #'- operands))

           (defun element-wise-product (&rest operands)
             (apply #'element-operate #'* operands))

           (defgeneric mult-2 (x y))

           (defmethod mult-2 ((x <number>) (y <number>))
             (* x y))

           (defmethod mult-2 ((x <number>) (y <general-vector>))
             (map '<general-vector> (lambda (component) (mult-2 x component)) y))

           (defmethod mult-2 ((x <general-vector>) (y <number>))
             (mult-2 y x))

           (defmethod mult-2 ((x <number>) (y <general-array*>))
             (check-matrix y)
             (rows->matrix 
               (map '<general-vector> 
                    (lambda (row) (mult-2 x row)) 
                    (rows y))))

           (defmethod mult-2 ((x <general-array*>) (y <number>))
             (check-matrix x)
             (mult-2 y x))

           (defmethod mult-2 ((x <general-vector>) (y <general-array*>))
             (check-matrix y)
             (map '<general-vector> (lambda (col) (dot col x)) (columns y)))

           (defmethod mult-2 ((x <general-array*>) (y <general-array*>))
             (check-matrix x)
             (check-matrix y)
             (rows->matrix 
               (map '<general-vector> 
                    (lambda (row) (mult-2 row y)) 
                    (rows x))))

           (defun mult (&rest operands)
             (reduce (lambda (x y) (mult-2 x y)) 
                     (car operands) 
                     (cdr operands)))

           (defun negate (x)
             (mult-2 x -1)) 

           (defun dot (x  y)
             (assure <general-vector> x)
             (assure <general-vector> y)
             (check-same-dimensions x y)
             (reduce #'add 0 (element-wise-product x y)))

           (defun cross (x y)
             (let* ((x1 (elt x 0))
                    (-x1 (- x1))
                    (x2 (elt x 1))
                    (-x2 (- x2))
                    (x3 (elt x 2))
                    (-x3 (- x3))
                    (x-mat (rows->matrix (vector
                                           (vector 0 -x3 x2)
                                           (vector x3 0 -x1)
                                           (vector -x2 x1 0)))))
               (transpose (mult x-mat (transpose y)))))

           (defun cartesian-product (&rest vectors)
             (flet ((next-cartesian-product (previous-product next-vector)
                      (reduce 
                        (lambda (accumulated y) 
                          (concatenate '<general-vector> 
                                       accumulated 
                                       (map '<list> 
                                            (lambda (x) (concatenate '<general-vector> x (vector y))) 
                                            previous-product)))
                        (vector)
                        next-vector)))
               (reduce #'next-cartesian-product #(#()) vectors))))


