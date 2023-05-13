;;; extended matrix library

(defun matrixp (x)
  (instancep x (class <matrix>)))

;;;  matrix number
(defclass <matrix> ()
  ((data :accessor data :initform 0 :initarg data)))

(defclass <row-vector> ()
  ((data :accessor data :initform 0 :initarg data)))

(defclass <col-vector> ()
  ((data :accessor data :initform 0 :initarg data)))

;;; constructer
(defun matrix (x)
  (create (class <matrix>) 'data x))    

(defun row-vector (x)
  (create (class <row-vector>) 'data x))

(defun col-vector (x)
  (create (class <col-vector>) 'data x))

;;; display matrix
(defun mprint (x)
    (print (data x)))

;;; matrix operator
(defun madd (x y)
  (matrix (madd1 x y)))

(defun madd1 (x y)
    (let* ((x1 (data x)) 
           (y1 (data y))
           (dim (array-dimensions x1))
           (dx (elt dim 0))
           (dy (elt dim 1))
           (z1 (create-array dim)))
        (for ((i 0 (+ i 1)))
             ((>= i dx) z1)
             (for ((j 0 (+ j 1)))
                  ((>= j dy))
                  (set-aref (+ (aref x1 i j) (aref y1 i j)) z1 i j)))))
          

(defun msub (x y)
  (matrix (msub1 x y)))


(defun madd1 (x y)
    (let* ((x1 (data x)) 
           (y1 (data y))
           (dim (array-dimensions x1))
           (dx (elt dim 0))
           (dy (elt dim 1))
           (z1 (create-array dim)))
        (for ((i 0 (+ i 1)))
             ((>= i dx) z1)
             (for ((j 0 (+ j 1)))
                  ((>= j dy))
                  (set-aref (- (aref x1 i j) (aref y1 i j)) z1 i j)))))
          
(defmodule matrix
           (import "seq" map every reduce concatenate)

           (defun check-matrix (array)
             (when (/= (length (array-dimensions array)) 
                       2)
               (Error "Argument must be a matrix")))

           ;;; ROWS returns the row vectors of a matrix
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

           ;;; ROWS->MATRIX converts a vector of row vectors into a matrix
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

           ;;; COLUMNS->MATRIX converts a vector of column vectors into a matrix
           (defun columns->matrix (columns)
             (transpose (rows->matrix columns)))

           ;;; TRANSPOSE transposes a matrix or vector X
           (defgeneric transpose (x))

           (defmethod transpose ((matrix <general-array*>))
             (check-matrix matrix)
             (let ((matrix-columns (columns matrix))) 
               (if (= (length matrix-columns) 1) 
                   (elt matrix-columns 0)
                   (rows->matrix matrix-columns))))

           (defmethod transpose ((vector <general-vector>))
             (columns->matrix (vector vector)))

           ;;; COLUMNS returns the column vectors of matrix MATRIX
           (defun columns (matrix)
             (check-matrix matrix)
             (let ((get-col (lambda (&rest column-fields) (convert column-fields <general-vector>)))
                   (map (function map)))
               (apply map '<general-vector> get-col (convert (rows matrix) <list>))))

           ;;; VECTOR-OF-VECTORS-DIMENSIONS returns a vector with the dimensions of VECTOR-OF-VECTORS
           ;;; The first element of the returned vector is the number of vectors in VECTOR-OF-VECTORS
           ;;; The second element of the returned vector is the length of each of the vectors in VECTOR-OF-VECTORS
           ;;; All vectors in VECTOR-OF-VECTORS must have the same length
           (defun vector-of-vectors-dimensions (vector-of-vectors)
             (let ((first-vector-length (length (elt vector-of-vectors 0))))
               (if (every (lambda (vector) 
                            (= (length vector) first-vector-length)) 
                          vector-of-vectors)
                   (vector (length vector-of-vectors) first-vector-length)
                   (error "All sub-vectors must have the same length"))))

           ;;; CHECK-SAME-DIMENSIONS checks that arrays X and Y have the same dimensions.
           ;;; If they do not, an error is signalled
           (defun check-same-dimensions (x y)
             (when (not (equal (array-dimensions x) (array-dimensions y)))
               (error "All arguments must have the same dimensions")))

           ;;; ELEMENT-OPERATE-2 performs an element-wise operation on X and Y
           ;;; Operator OPERATOR is the function that performs the operation.
           ;;; OPERATOR must take at least two arguments
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

           ;;; ELEMENT-OPERATE performs an element-wise operation on any number of operands in OPERANDS.
           ;;; DYADIC-OPERATOR is an function that takes at least two argumenst
           ;;; The element-wise operation is performed from left-to-right
           (defun element-operate (dyadic-operator &rest operands)
             (reduce (lambda (x y) (element-operate-2 dyadic-operator x y)) 
                     (car operands) 
                     (cdr operands)))

           ;;; ADD adds the operands OPERANDS together
           (defun add (&rest operands)
             (apply #'element-operate #'+ operands))

           ;;; SUB subtracts the OPERANDS from left to right
           (defun sub (&rest operands)
             (apply #'element-operate #'- operands))

           ;;; ELEMENT-WISE-PRODUCT performs the element-wise-product of the operands OPERANDS
           ;;; This is also known as the Hadamard product
           (defun element-wise-product (&rest operands)
             (apply #'element-operate #'* operands))

           ;;; MULT-2 multiplies X and Y together
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

           ;;; MULT multiplies operands OPERANDS together from left to right
           (defun mult (&rest operands)
             (reduce (lambda (x y) (mult-2 x y)) 
                     (car operands) 
                     (cdr operands)))

           ;;; NEGATE negates X
           ;;; Multiplies by negative 1
           (defun negate (x)
             (mult-2 x -1)) 

           ;;; DOT calculates dot product of X and Y
           (defun dot (x  y)
             (assure <general-vector> x)
             (assure <general-vector> y)
             (check-same-dimensions x y)
             (reduce #'add 0 (element-wise-product x y)))

           ;;; CROSS calculates cross product of X and Y
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

           ;;; NORM calculates the Euclidean norm of x
           (defun norm (x)
             (sqrt (dot x x)))

           ;;; NORMALIZE normalizes vector X
           ;;; The normalized vector is a unit vector with the same direction of X
           (defun normalize (x)
             (let ((norm (norm x))) 
               (if (= 0 norm) 
                   (error "Cant normalize a zero-length vector!"))
               (mult x (reciprocal norm))))

           ;;; CARTESIAN-PRODUCT returns the cartesian product of the vectors in VECTORS
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


