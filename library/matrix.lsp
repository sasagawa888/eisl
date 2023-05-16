;;; extended matrix library

(defun matrixp (x)
    (and (eq (class-of x) (class <general-array*>))
         (= (length (array-dimensions x)) 2)))

;;;  matrix data structure
(defclass <rows> ()
    ((data :accessor data :initform 0 :initarg data)) )
(defclass <columns> ()
    ((data :accessor data :initform 0 :initarg data)) )

;;; constructer
(defun create-rows (x)
    (create (class <rows>) 'data x) )

(defun create-columns (x)
    (create (class <columns>) 'data x) )


;;; convert data structure
(defmacro matrix-convert (x type)
    `(matrix-convert1 ,x (class ,type)) )

(defun matrix-convert1 (x y)
    (cond ((and (eq (class-of x) (class <rows>))
                (eq y (class <general-array*>)))
           (matrix::rows->matrix (data x)))
          ((and (eq (class-of x) (class <columns>))
                (eq y (class <general-array*>)))
           (matrix::columns->matrix (data x)))
          ((and (eq (class-of x) (class <general-array*>))
                (eq y (class <rows>)))
           (create-rows (matrix::rows x)))
          ((and (eq (class-of x) (class <general-array*>))
                (eq y (class <columns>)))
           (create-columns (matrix::columns x)))
          (t (error "matrix-convert no adapted data type"))))


(defmacro matrix-add (:rest operands)
    `(matrix::add ,@operands) )

(defmacro matrix-sub (:rest operands)
    `(matrix::sub ,@operands) )

(defmacro matrix-mult (:rest operands)
    `(matrix::mult ,@operands) )

(defmacro matrix-hadamard (:rest operands)
    `(matrix::element-wise-product ,@operands) )

(defmacro vector-cartesian (:rest vectors)
    `(matrix::cartesian-product ,@vectors) )

(defun matrix-transpose (x)
    (matrix::transpose x) )

(defun matrix-negate (x)
    (matrix::negate x) )

(defun vector-dot (x y)
    (matrix::dot x y) )

(defun vector-cross (x y)
    (matrix::cross x y) )

(defun vector-norm (x)
    (matrix::norm x) )

(defun vector-normalize (x)
    (matrix-::normalize x) )

(defun matrix-elt (m i j)
    (matrix::aref1 m i j) )

(defun matrix-set-elt (v m i j)
    (matrix::set-aref1 v m i j) )

(defmodule matrix
    (import "seq" map every reduce concatenate)
    (defun check-matrix (array)
        (when (/= (length (array-dimensions array)) 2)
              (error "Argument must be a matrix")))

    ;;; ROWS returns the row vectors of a matrix
    (defun rows (matrix)
        (check-matrix matrix)
        (let* ((dimensions (array-dimensions matrix))
               (number-of-rows (elt dimensions 0))
               (number-of-columns (elt dimensions 1))
               (rows (create-vector number-of-rows)) )
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
               (matrix (create-array (convert dimensions <list>))) )
            (dotimes (row-index number-of-rows)
               (let ((row (elt rows row-index)))
                  (dotimes (col-index number-of-columns)
                     (setf (garef matrix row-index col-index) (elt row col-index)))))
            matrix))

    ;;; COLUMNS->MATRIX converts a vector of column vectors into a matrix
    (defun columns->matrix (columns)
        (transpose (rows->matrix columns)))

    ;;; TRANSPOSE transposes a matrix or vector X
    (defgeneric transpose (x))

    (defmethod transpose
               ((matrix <general-array*>))
               (check-matrix matrix)
               (let ((matrix-columns (columns matrix)))
                  (if (= (length matrix-columns) 1)
                      (elt matrix-columns 0)
                      (rows->matrix matrix-columns))))
    (defmethod transpose
               ((vector <general-vector>))
               (columns->matrix (vector vector)))
    ;;; COLUMNS returns the column vectors of matrix MATRIX
    (defun columns (matrix)
        (check-matrix matrix)
        (let ((get-col (lambda (&rest column-fields) (convert column-fields <general-vector>)))
              (map (function map)) )
           (apply map
                  '<general-vector>
                  get-col
                  (convert (rows matrix) <list>))))

    ;;; VECTOR-OF-VECTORS-DIMENSIONS returns a vector with the dimensions of VECTOR-OF-VECTORS
    ;;; The first element of the returned vector is the number of vectors in VECTOR-OF-VECTORS
    ;;; The second element of the returned vector is the length of each of the vectors in VECTOR-OF-VECTORS
    ;;; All vectors in VECTOR-OF-VECTORS must have the same length
    (defun vector-of-vectors-dimensions (vector-of-vectors)
        (let ((first-vector-length (length (elt vector-of-vectors 0))))
           (if (every (lambda (vector) (= (length vector) first-vector-length))
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

    (defmethod element-operate-2
               ((operator <function>) x y)
               (funcall operator x y))
    (defmethod element-operate-2
               ((operator <function>) (x <general-vector>) (y <general-vector>))
               (check-same-dimensions x y)
               (map '<general-vector>
                    (lambda (x y) (element-operate-2 operator x y))
                    x
                    y))
    (defmethod element-operate-2
               ((operator <function>) (x <general-array*>) (y <general-array*>))
               (check-matrix x)
               (check-matrix y)
               (check-same-dimensions x y)
               (rows->matrix
                (map '<general-vector>
                     (lambda (x y) (element-operate-2 operator x y))
                     (rows x)
                     (rows y))))
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

    (defmethod mult-2 ((x <number>) (y <number>)) (* x y))
    (defmethod mult-2
               ((x <number>) (y <general-vector>))
               (map '<general-vector>
                    (lambda (component) (mult-2 x component))
                    y))
    (defmethod mult-2 ((x <general-vector>) (y <number>)) (mult-2 y x))
    (defmethod mult-2
               ((x <number>) (y <general-array*>))
               (check-matrix y)
               (rows->matrix (map '<general-vector> (lambda (row) (mult-2 x row)) (rows y))))
    (defmethod mult-2
               ((x <general-array*>) (y <number>))
               (check-matrix x)
               (mult-2 y x))
    (defmethod mult-2
               ((x <general-vector>) (y <general-array*>))
               (check-matrix y)
               (map '<general-vector> (lambda (col) (dot col x)) (columns y)))
    (defmethod mult-2
               ((x <general-array*>) (y <general-array*>))
               (check-matrix x)
               (check-matrix y)
               (rows->matrix (map '<general-vector> (lambda (row) (mult-2 row y)) (rows x))))
    ;;; MULT multiplies operands OPERANDS together from left to right
    (defun mult (&rest operands)
        (reduce (lambda (x y) (mult-2 x y)) (car operands) (cdr operands)))

    ;;; NEGATE negates X
    ;;; Multiplies by negative 1
    (defun negate (x)
        (mult-2 x -1))

    ;;; DOT calculates dot product of X and Y
    (defun dot (x y)
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
               (x-mat (rows->matrix (vector (vector 0 -x3 x2) (vector x3 0 -x1) (vector -x2 x1 0)))) )
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
                   (reduce (lambda (accumulated y) (concatenate '<general-vector>
                                           accumulated
                                           (map '<list>
                                                (lambda (x) (concatenate '<general-vector> x (vector y)))
                                                previous-product)))
                           (vector)
                           next-vector)))
            (reduce #'next-cartesian-product #(#()) vectors)))

    ;;; set element to matrix (index is start from 1)
    (defun set-aref1 (val mat i j)
        (set-aref val mat (- i 1) (- j 1)))

    ;;; get element from matrix (index is start from 1)
    (defun aref1 (mat i j)
        (aref mat (- i 1) (- j 1)))

    (defun square-matrix-p (x)
        (let ((dim (array-dimensions x)))
           (and (= (length dim) 2) (= (elt dim 0) (elt dim 1)))))

    ;;; calculate trace of matrix
    (defpublic matrix-tr (x)
        (unless (square-matrix-p x) (error "tr require square matrix" x))
        (let ((l (elt (array-dimensions x) 0)))
           (for ((i 1 (+ i 1))
                 (y 0) )
                ((> i l)
                 y )
                (setq y (+ (aref1 x i i) y)))))

    
    ;;; for determinant and inverse
    ;; original matrix
    (defglobal mat1 nil)
    ;; inverse matrix in inverse
    (defglobal mat2 nil)

    ;;; determinant of matrix
    (defpublic matrix-det (x)
        (det x))

    ;;; transform to upper triang and calculate product of diagonal
    (defun det (mat)
        (unless (square-matrix-p mat) (error "matrix-det not square matrix"))
        (let ((n (elt (array-dimensions mat) 0))
              (result 1))
            (setq mat1 (rows mat))
            (setq mat2 (rows (ident n))) ; ignore mat2
            (exchange-zero-row n)
            (erase-lower-triang n)
            (for ((i 1 (+ i 1)))
                 ((> i n) result)
                 (setq result (* result (rowref1 mat1 i i))))))



    ;;; inverse Gauss sweep out method
    
    ;; access element (i,j) in rows matrix
    (defun rowref1 (mat i j)
        (elt (elt mat (- i 1)) (- j 1)))

    ;; ident matrix n*n
    (defun ident (n)
        (let ((mat (create-array (list n n) 0)))
           (for ((i 1 (+ i 1)))
                ((> i n)
                 mat )
                (set-aref1 1 mat i i))))

    ;; elementaly operations
    (defun exchange-row (i j)
        (let ((tmp1 (elt mat1 (- i 1)))
              (tmp2 (elt mat2 (- i 1))) )
           (set-elt (elt mat1 (- j 1)) mat1 (- i 1))
           (set-elt (elt mat2 (- j 1)) mat2 (- i 1))
           (set-elt tmp mat1 (- i 1))
           (set-elt tmp mat2 (- i 1))))

    
    ;; row(i) = row(i)-r*row(j)
    (defun sub-multed-row (i j r)
        (set-elt (sub (elt mat1 (- i 1)) (mult r (elt mat1 (- j 1))))
                 mat1
                 (- i 1))
        (set-elt (sub (elt mat2 (- i 1)) (mult r (elt mat2 (- j 1))))
                 mat2
                 (- i 1)))

    ;; row(i) = r*row(i)
    (defun mult-row (i r)
        (set-elt (mult r (elt mat1 (- i 1))) mat1 (- i 1))
        (set-elt (mult r (elt mat2 (- i 1))) mat2 (- i 1)))

    ;; inverse
    (defpublic matrix-inverse (mat)
        (inverse mat))

    (defun inverse (mat)
        (unless (square-matrix-p mat) (error "matrix-inverse not square matrix"))
        (let ((n (elt (array-dimensions mat) 0)))
           (setq mat1 (rows mat))
           (setq mat2 (rows (ident n)))
           (exchange-zero-row n)
           (erase-lower-triang n)
           (erase-upper-triang n)
           (normalize-diagonal n))
        (rows->matrix mat2))

    (defun exchange-zero-row (n)
        (for ((i 1 (+ i 1)))
             ((> i n))
             (if (= (rowref1 mat1 i i) 0)
                 (exchange-zero-row1 m n))))

    
    (defun exchange-zero-row1 (m n)
        (block exit
           (for ((i (+ m 1) (+ i 1)))
                ((> i n)
                 (error "matrix-inverse not regular matrix") )
                (cond ((/= (rowref1 mat1 i m) 0) (exchange-row i m) (return-from exit nil))))))

    

    (defun normalize-diagonal (n)
        (for ((i 1 (+ i 1)))
             ((> i n))
             (if (/= (rowref1 mat1 i i) 1)
                 (mult-row i (quotient 1 (rowref1 mat1 i i))))))

    (defun erase-lower-triang (n)
        (for ((i 1 (+ i 1)))
             ((> i n))
             (for ((j (+ i 1) (+ j 1)))
                  ((> j n))
                  (if (/= (rowref1 mat1 j i) 0)
                      (if (/= (rowref1 mat1 i i) 0)
                          (sub-multed-row j i (quotient (rowref1 mat1 j i) (rowref1 mat1 i i)))
                          (error "matrix-inverse not regular matrix"))))))

    (defun erase-upper-triang (n)
        (for ((i 2 (+ i 1)))
             ((> i n))
             (for ((j 1 (+ j 1)))
                  ((>= j i))
                  (if (/= (rowref1 mat1 j i) 0)
                      (if (/= (rowref1 mat1 i i) 0)
                          (sub-multed-row j i (quotient (rowref1 mat1 j i) (rowref1 mat1 i i)))
                          (error "matrix-inverse not regular matrix"))))))

    
)


