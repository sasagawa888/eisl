;; bitwise library
;; compile before use


(defun logand (x y)
    (c-lang "res = INT_FLAG | ((INT_MASK & X) & (INT_MASK & Y));"))

(defun logior (x y)
    (c-lang "res = INT_FLAG | ((INT_MASK & X) | (INT_MASK & Y));"))
  
(defun logxor (x y)
    (c-lang "res = INT_FLAG | ((INT_MASK & X) ^ (INT_MASK & Y));"))


(defun lognot (x)
    (c-lang "res = INT_FLAG | ~~(INT_MASK & X);"))


(defun logtest (x y)
    (c-lang "int z; z = ((INT_MASK & X) & (INT_MASK & Y));")
    (c-lang "if(z==0) res=NIL; else res = T;"))

;;bit test
(defun logbitp (n m)
  (if (>= n 0)
      (c-lang "int x; x = (INT_MASK & M) << (INT_MASK & N);
               if(x % 2 == 1) res = T; else res = NIL;")
      (error "logbitp: not positive" n)))

(defun logcount (n)
    (if (>= n 0)
        (c-lang "int x,i; x = (INT_MASK & N); i = 0;
                 while(x != 0){
                    if(x % 2 == 1) i++;
                    x = x >> 1;
                 }
                 res = INT_FLAG | i;")
        (c-lang "int x,i; x = (INT_MASK & N); i = 0;
                 while(x != 0){
                    if(x % 2 == 0) i++;
                    x = x >> 1;
                 }
                 res = INT_FLAG | i;")))
  
;;bit shift
(defun ash (n m)
  (if (>= m 0)
      (c-lang "res = INT_FLAG | ((INT_MASK & N) << (INT_MASK & M));")
      (if (>= n 0)
          (let ((m1 (- m)))
            (c-lang "res = INT_FLAG | ((INT_MASK & N) >> (INT_MASK & M1));"))
          (let ((m1 (- m)))
            (c-lang "res = INT_FLAG | (N >> (INT_MASK & M1));")))))
          
