(import "math")

(defglobal p 257)

(defglobal omega 3)

(defglobal n 256)


(defglobal a #(1 2 0 0 0 0 0 0))
(defglobal b #(0 0 0 0 0 0 0 0))


(defglobal base (expmod omega (div n (length a)) p))

(defun inv-n (n)
    (expmod n (- p 2) p))

(defun w-factor (k)
    (expmod base k p))

(defun plusmod (x y)
    (mod (+ x y) p))

(defun minusmod (x y)
    (mod (+ (- x y) p) p))

(defun multmod (x y)
    (mod (* x y) p))

(defun invmod (x)
    (expmod x (- p 2) p))



(defun ntt ()
    (let* ((h (div (length a) 2)))
        (set-reverse)
        (ntt1 h 0)))

(defun ntt1 (h pos)
    (cond ((= h 0) t)
          (t (ntt1 (div h 2) pos)
             (ntt1 (div h 2) (+ pos h))
             (let ((temp nil))
                (for ((i 0 (+ i 1)))
                     ((>= i h) t)
                     (setq temp (plusmod (aref a (+ pos i)) (multmod (w-factor i) (aref a (+ pos i h)))))
                     (set-aref (plusmod (aref a (+ pos i)) (multmod (w-factor (+ i h)) (aref a (+ pos i h)))) a (+ pos i h))
                     (set-aref temp a  (+ pos i))
                     (print a))))))


(defun intt ()
    (let* ((h (div (length a) 2))
           (invbase (invmod base))
           (invm (invmod (length a))))
        (set-reverse)
        (setq base invbase)
        (ntt1 h 0)
        (for ((i 0 (+ i 1)))
             ((>= i 8) t)
             (set-aref (multmod (aref a i) invm) a i))))



(defun bit-reverse (n)
    (elt '(0 4 2 6 1 5 3 7) n))

(defun set-reverse ()
    (for ((i 0 (+ i 1)))
         ((>= i 8) t)
         (set-aref (aref a i) b (bit-reverse i)))
    (for ((i 0 (+ i 1)))
         ((>= i 8) t)
         (set-aref (aref b i) a i)))  



