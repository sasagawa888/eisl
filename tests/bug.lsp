

(defun test-boundary1 ()
  ;; zero arguments
  123)


(defun test-boundary2 (x)
  ;; nil input
  (if (null x) 'nil-case 'non-nil-case))


(defun foo ()
  (list (test-boundary1)
        (test-boundary2 t)))