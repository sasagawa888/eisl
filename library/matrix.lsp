(defmodule matrix
           (import "seq" map every reduce)

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

           (defgeneric element-wise-operate (operator x y))

           (defmethod element-wise-operate ((operator <function>) x y)
             (funcall operator x y))

           (defmethod element-wise-operate ((operator <function>) (x <general-vector>) (y <general-vector>)) 
             (check-same-dimensions x y)
             (map '<general-vector> (lambda (x y) (element-wise-operate operator x y)) x y))

           (defmethod element-wise-operate ((operator <function>) (x <general-array*>) (y <general-array*>))
             (check-matrix x)
             (check-matrix y)
             (check-same-dimensions x y)
             (rows->matrix 
               (map '<general-vector> (lambda (x y) (element-wise-operate operator x y)) (rows x) (rows y))))

           (defun add (x y)
             (element-wise-operate #'+ x y))

           (defun sub (x y)
             (element-wise-operate #'- x y))

           (defun element-wise-product (x y)
             (element-wise-operate #'* x y))

           (defgeneric mult (x y))

           (defmethod mult ((x <number>) (y <number>))
             (* x y))

           (defmethod mult ((x <number>) (y <general-vector>))
             (map '<general-vector> (lambda (component) (mult x component)) y))

           (defmethod mult ((x <general-vector>) (y <number>))
             (mult y x))

           (defmethod mult ((x <number>) (y <general-array*>))
             (check-matrix y)
             (rows->matrix 
               (map '<general-vector> 
                    (lambda (row) (mult x row)) 
                    (rows y))))

           (defmethod mult ((x <general-array*>) (y <number>))
             (check-matrix x)
             (mult y x))

           (defmethod mult ((x <general-vector>) (y <general-array*>))
             (check-matrix y)
             (map '<general-vector> (lambda (col) (dot col x)) (columns y)))

           (defmethod mult ((x <general-array*>) (y <general-array*>))
             (check-matrix x)
             (check-matrix y)
             (rows->matrix 
               (map '<general-vector> 
                    (lambda (row) (mult row y)) 
                    (rows x))))

           (defun dot (x  y)
             (assure <general-vector> x)
             (assure <general-vector> y)
             (check-same-dimensions x y)
             (reduce (lambda (x y) (add x y)) 
                     0 
                     (element-wise-product x y))))


