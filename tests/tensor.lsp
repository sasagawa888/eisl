;;;;;;;;;;;;;;;;;
;; project to understand Riemannian geometry and general theory of relativity.
;;;  since 2021/5
;;; calculating   Schwarzschild 

(defglobal G 6.67430e-11)
(defglobal M 5.972e24)
(defglobal C 2.99792458e8)
(defglobal scale 10e-23)

(defun / (x y) (quotient x y))
(defun ^ (x y) (expt x y))

(defun make-metric (r theta)
    (let ((tensor (create-tensor '(4 4))))
        (setf (aref tensor 0 0) (- 1 (/ (* 2 G M) (* r (^ c 2)))))
        (setf (aref tensor 1 1) (- (/  1 (- 1 (/ (* 2 G M) (* r (^ c 2)))))))
        (setf (aref tensor 2 2) (- (^ r 2)))
        (setf (aref tensor 3 3) (- (* (^ r 2) (^ (sin theta) 2))))
        tensor))

(defun create-tensor (dimension)
    (create-array dimension 0))


;; ds^2
(defun distance (ten dx)
    (let* ((result 0))
        (for ((i 0 (+ i 1)))
             ((= i 4) result)
             (for ((j 0 (+ j 1)))
                  ((= j 4) nil)
                  (setq result (+ result (* (aref ten i j) (elt dx i) (elt dx j))))))))

;; tangent vector
(defun tangent (ten dx)
    (let* ((result (create-vector 4)))
        (for ((i 0 (+ i 1)))
             ((= i 4) result)
             (setf (elt result i) (* (aref ten i i) (elt dx i) scale) ))))

;; vector operation
(defun vadd (x y)
    (for ((i 0 (+ i 1)))
         ((= i 4) x)
         (setf (elt x i) (+ (elt x i) (elt y i)))))


(defun polar-to-cartesian (v)
    (let ((r (elt v 1))
          (theta (elt v 2))
          (phi (elt v 3)))
        (vector 0
                (* r (sin phi) (cos theta))
                (* r (sin phi) (sin theta))
                (* r (cos phi)))))

;t = 0
;x = r * sin(φ) * cos(θ)
;y = r * sin(φ) * sin(θ)
;z = r * cos(φ)


(defglobal r 10e6)
(defglobal theta 0)
(defglobal phi 0)
(defglobal dt 0)
(defglobal dr (/ r 1000))
(defglobal dtheta (/ *pi* 1000))
(defglobal dphi 0)
(defglobal dx (vector dt dr dtheta dphi))
(defglobal pos (vector 0 r theta phi))

(defun foo ()
    (let ((g (make-metric (elt pos 1) (elt pos 2))))
        (for ((i 0 (+ i 1)))
             ((= i 10) t)
             (vadd pos (tangent g dx))
             (print pos)
             (print (polar-to-cartesian pos))
             (setq g (make-metric (elt pos 1) (elt pos 2))))))

    





