(defmodule foo
    
    (defun substring (str m n)
        (for ((i m (+ i 1))
              (str1 "") )
           ((> i n)
             str1 )
            (setq str1 (string-append str1 (convert (elt str i) <string>)))))
    
)

