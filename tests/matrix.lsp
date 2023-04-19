(import "test")
(import "matrix")

(let ((test-vector #(1 2 3))
      (identity-matrix 
        #2a((1 0 0)
            (0 1 0)
            (0 0 1)))
      (zeros-matrix
        #2a((0 0 0)
            (0 0 0)
            (0 0 0)))
      (test-matrix 
        #2a((1 2 3)
            (4 5 6)
            (7 8 9))))
  ($test (rows identity-matrix)
         #(#(1 0 0) #(0 1 0) #(0 0 1)))
  ($test (rows test-matrix)
         #(#(1 2 3) #(4 5 6) #(7 8 9)))
  ($test (columns test-matrix)
         #(#(1 4 7) #(2 5 8) #(3 6 9)))
  ($test (rows->matrix (rows test-matrix)) test-matrix)
  ($test (transpose (transpose test-matrix)) test-matrix)
  ($test (transpose (transpose test-vector)) test-vector)
  ($test (columns->matrix (columns test-matrix)) test-matrix)

  ($test (add 1 2) 3)
  ($test (add #(1 2 3) #(4 5 6)) #(5 7 9))
  ($test (add identity-matrix identity-matrix) 
         #2a((2 0 0)
             (0 2 0)
             (0 0 2)))
  
  ($test (sub 2 1) 1)
  ($test (sub #(4 5 6) #(1 2 3)) #(3 3 3))
  ($test (sub test-matrix identity-matrix)
         #2a((0 2 3)
             (4 4 6)
             (7 8 8)))
  ($test (sub test-matrix test-matrix) zeros-matrix)

  ($test (dot #(1 2 3) #(1 1 1)) 6)
  ($test (dot #(1 2 3) #(0 0 0)) 0)

  ($test (mult 2 3) 6)
  ($test (mult #(1 2 3) 2) #(2 4 6))
  ($test (mult test-vector identity-matrix) test-vector)
  ($test (mult test-matrix identity-matrix) test-matrix)
  

  )
