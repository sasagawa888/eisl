(defun bar (x)
    (cond ((= x 1)            ;nnnnnnnnn 
           asdfdfhhhhhhhhhhhhhhhhhhhhhhhh) ;asdf
          ((= x 2) dfgdfg)    ;vbn
          ((= x 3) kjdsfds)   ;asdfasd
          ((= x 4) lkjlklkjl) ))
;asdfsdd


(defun foo (x)
    (if (= x 1)
        2                     ;adsfsadlkjhkjh
        3                     ;kakj;lkj;lkjl
         ))

(defmacro when (test :rest body)
    `(if ,test (progn ,@body)) )
