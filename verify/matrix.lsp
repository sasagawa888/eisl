(import "test")
(import "matrix")

;;; matrix library
(defglobal identity-matrix #2a((1 0 0) (0 1 0) (0 0 1)))

(defglobal zeros-matrix #2a((0 0 0) (0 0 0) (0 0 0)))

(defglobal test-matrix #2a((1 2 3) (4 5 6) (7 8 9)))

(defglobal test-vector #(1 2 3))

(defglobal d #2a((3 1 1 2) (5 1 3 4) (2 0 1 0) (1 3 2 1)))

(defglobal f #2a((1.0 1.0 -1.0)(-3.0 -1.0 1.0)(-1.0 -2.0 1.0)))

(defglobal a #2a((1 2 3) (4 5 6)))
(defglobal b #2a((2 3 4) (5 6 7)))
(defglobal c #2a((2 3) (5 6) (8 9)))


($assert (matrixp a) t)
($ap 2 "transpose")
($ap 3 "transpose matrix")
($assert (matrix-transpose (matrix-transpose test-matrix))
         test-matrix)

($ap 3 "add matrix")
($assert (add identity-matrix identity-matrix)
         #2a((2 0 0) (0 2 0) (0 0 2)))

($ap 2 "sub")
($ap 2 "sub scalar")
($assert (sub 2 1) 1)
($ap 2 "sub vector")
($assert (sub #(4 5 6) #(1 2 3)) #(3 3 3))
($ap 2 "sub matrix")
($assert (sub test-matrix identity-matrix)
         #2a((0 2 3) (4 4 6) (7 8 8)))
($assert (sub test-matrix test-matrix) zeros-matrix)

($ap 2 "dot")
($assert (vector-dot #(1 2 3) #(1 1 1)) 6)
($assert (vector-dot #(1 2 3) #(0 0 0)) 0)

($ap 2 "mult")
($ap 3 "mult scalar scalar")
($assert (mult 2 3) 6)
($ap 3 "mult vector scalar")
($assert (mult #(1 2 3) 2) #(2 4 6))
($ap 3 "mult vector matrix")
($assert (mult test-vector identity-matrix) #2a((1 2 3)))
($ap 3 "mult matrix matrix")
($assert (mult test-matrix identity-matrix) test-matrix)

($ap 2 "cross")
($assert (vector-cross #(1 2 3) #(4 5 6)) #(-3 6 -3))
($ap 2 "determinant")
($test (matrix-det #2a((3 1 1 2) (5 1 3 4) (2 0 1 0) (1 3 2 1)))
       -22
       eql)

($ap 2 "inverse")
($test (matrix-inverse f) #2a((-0.5 -0.5 0.0) (-1.0 0.0 -1.0) (-2.5 -0.5 -1.0)))