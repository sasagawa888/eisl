(import "test")

;;; matrix library
(defglobal identity-matrix 
           #2a((1 0 0)
               (0 1 0)
               (0 0 1)))

(defglobal zeros-matrix
          #2a((0 0 0)
              (0 0 0)
              (0 0 0)))

(defglobal test-matrix 
          #2a((1 2 3)
              (4 5 6)
              (7 8 9)))

(defglobal a #2a((1 2 3)(4 5 6)))
(defglobal b #2a((2 3 4)(5 6 7)))
(defglobal c #2a((2 3)(5 6)(8 9)))

(defun matrixp (x)
    (and (eq (class-of x) (class <general-array*>))
         (= (length (array-dimensions x)) 2)))

(defun vectorp (x)
    (and (eq (class-of x) (class <general-vector>))
         (= (length x) 3)))

(defun matrix-add (x y)
    (let ((dx (array-dimensions x))
          (dy (array-dimensions y)))
        (if (not (equal dx dy)) (error "matrix-add: not adapted"))
        (let ((r (elt dx 0))
              (c (elt dx 1))
              (a (create-array dx)))
           (for ((i 0 (+ i 1)))
                ((= i r) a)
                (for ((j 0 (+ j 1)))
                     ((= j c))
                     (set-aref (+ (aref x i j) (aref y i j)) a i j))))))

(defun matrix-sub (x y)
    (let ((dx (array-dimensions x))
          (dy (array-dimensions y)))
        (if (not (equal dx dy)) (error "matrix-sub: not adapted"))
        (let ((r (elt dx 0))
              (c (elt dx 1))
              (a (create-array dx)))
           (for ((i 0 (+ i 1)))
                ((= i r) a)
                (for ((j 0 (+ j 1)))
                     ((= j c))
                     (set-aref (- (aref x i j) (aref y i j)) a i j))))))

(defun matrix-mult (x y)
    (let ((dx (array-dimensions x))
          (dy (array-dimensions y)))
        (if (not (= (elt dx 1) (elt dy 0))) (error "matrix-nult: not adapted"))
        (let* ((r (elt dx 0))
               (c (elt dy 1))
               (m (elt dx 1))
               (a (create-array (list r c))))
              (for ((i 0 (+ i 1)))
                   ((= i r) a)
                   (for ((j 0 (+ j 1)))
                        ((= j c))
                        (for ((k 0 (+ k 1))
                              (l 0))
                             ((= k m) (set-aref l a i j))
                             (setq l (+ l (* (aref x i k) (aref y k j))))))))))



(defun matrix-hadamard (x y)
    (let ((dx (array-dimensions x))
          (dy (array-dimensions y)))
        (if (not (equal dx dy)) (error "matrix-hadamard: not adapted"))
        (let ((r (elt dx 0))
              (c (elt dx 1))
              (a (create-array dx)))
           (for ((i 0 (+ i 1)))
                ((= i r) a)
                (for ((j 0 (+ j 1)))
                     ((= j c))
                     (set-aref (* (aref x i j) (aref y i j)) a i j))))))

(defmacro vector-cartesian (:rest vectors)
    `(matrix::cartesian-product ,@vectors) )

(defun matrix-transpose (x)
    (let* ((dx (array-dimensions x))
           (r (elt dx 0))
           (c (elt dx 1))
           (a (create-array (list c r))))
        (for ((i 0 (+ i 1)))
             ((= i r) a)
             (for ((j 0 (+ j 1)))
                  ((= j c))
                  (set-aref (aref x i j) a j i)))))

(defun matrix-negate (x)
    (let* ((dx (array-dimensions x))
           (r (elt dx 0))
           (c (elt dx 1))
           (a (create-array dx)))
       (for ((i 0 (+ i 1)))
            ((= i r) a)
            (for ((j 0 (+ j 1)))
                 ((= j c))
                 (set-aref (* -1 (aref x i j)) a i j)))))

(defun vector-dot (x y)
    (+ (* (elt x 0) (elt y 0))
       (* (elt x 1) (elt y 1))
       (* (elt x 2) (elt y 2))))

(defun vector-cross (x y)
    (vector (- (* (elt x 1) (elt y 2)) (* (elt x 2) (elt y 0)))
            (- (* (elt x 2) (elt y 0)) (* (elt x 0) (elt y 2)))
            (- (* (elt x 0) (elt y 1)) (* (elt x 1) (elt y 0)))))

(defun vector-norm (x)
    (sqrt (matrix-dot x x)))

(defun vector-normalize (x)
    (matrix-::normalize x) )

(defun matrix-elt (x i j)
    (aref x (- i 1) (- j 1)) )

(defun matrix-set-elt (v x i j)
    (set-aref v x (- i 1) (- j 1) ))


    
    
;;; NORMALIZE normalizes vector X
;;; The normalized vector is a unit vector with the same direction of X
(defun normalize (x)
    (let ((norm1 (norm x)))
        (if (= 0 norm1)
            (error "Cant normalize a zero-length vector!"))
           (mult x (reciprocal norm1))))

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

(defmodule matrix

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
                 ((> i n) (round result))
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
           (set-elt tmp1 mat1 (- i 1))
           (set-elt tmp2 mat2 (- i 1))))

    
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
                 (exchange-zero-row1 i n))))

    
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


($assert (matrixp a) t)
($ap 2 "transpose")
($ap 3 "transpose matrix")
($assert (matrix-transpose (matrix-transpose test-matrix)) test-matrix)

($ap 3 "add matrix")
($assert (matrix-add identity-matrix identity-matrix) 
         #2a((2 0 0)
             (0 2 0)
             (0 0 2)))

($ap 2 "sub")
;($ap 2 "sub scalar")
;($assert (matrix-sub 2 1) 1)
;($ap 2 "sub vector")
;($assert (matrix-sub #(4 5 6) #(1 2 3)) #(3 3 3))
($ap 2 "sub matrix")
($assert (matrix-sub test-matrix identity-matrix)
         #2a((0 2 3)
             (4 4 6)
             (7 8 8)))
($assert (matrix-sub test-matrix test-matrix) zeros-matrix)

($ap 2 "dot")
($assert (vector-dot #(1 2 3) #(1 1 1)) 6)
($assert (vector-dot #(1 2 3) #(0 0 0)) 0)

($ap 2 "mult")
;($ap 3 "mult scalar scalar")
;($assert (matrix-mult 2 3) 6)
;($ap 3 "mult vector scalar")
;($assert (matrix-mult #(1 2 3) 2) #(2 4 6))
;($ap 3 "mult vector matrix")
;($assert (matrix-mult test-vector identity-matrix) test-vector)
($ap 3 "mult matrix matrix")
($assert (matrix-mult test-matrix identity-matrix) test-matrix)

($ap 2 "cross")
;($assert (vector-cross #(1 2 3) #(4 5 6)) #(-3 6 -3))
  
($ap 2 "determinant")
;($test (matrix-det #2a((3 1 1 2) (5 1 3 4) (2 0 1 0) (1 3 2 1))) -22 eql)