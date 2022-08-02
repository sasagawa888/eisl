;; Edlis unicode test

(defun bar (x) 
    (cond ((string= x "thank you") 'english)
          ((string= x "ありがとう") 'japan)
          ((string= x "Дякую") 'ukraine)
          ((string= x "رەھمەت سىزگە") 'wiggle)))





