;;;;;;;;;;;;;;;;;
;; project to understand Riemannian geometry and general theory of relativity.
;;;  since 2021/5
;;; calculating   Schwarzschild 
(import "plot")

#|
(defglobal G 6.67430e-11)
(defglobal M 5.972e24)
(defglobal C 2.99792458e8)
|#

(defglobal G 6.67430)
(defglobal M 5.972)
(defglobal C 2.99792458)

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
             (setf (elt result i) (* (aref ten i i) (elt dx i)) ))))

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


(defglobal dt 0.001)
(defglobal dr 0.001)
(defglobal dtheta 0.000001)
(defglobal dphi 0.000001)
(defglobal dx (vector dt dr dtheta dphi))
(defglobal pos (vector 0 50 0 0))

(defun foo (times file)
    (let ((stream (open-output-file file))
          (g (make-metric (elt pos 1) (elt pos 2)))
          (d nil))
        (for ((i 0 (+ i 1)))
             ((= i times) t)
             (vadd pos (tangent g dx))
             (print pos)
             (setq d (polar-to-cartesian pos))
             (format stream "~G ~G ~G~%" (elt d 1) (elt d 2) (elt d 3))
             (setq g (make-metric (elt pos 1) (elt pos 2))))
        (close stream)))


(defun draw ()
    (gbc)
    (foo 1000 "data1.txt")
    (open-plot)
    (send-plot "splot \"data1.txt\" ")
    (close-plot)
    (system "rm -rf data1.txt"))





