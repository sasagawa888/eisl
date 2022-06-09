(import "math")

(defglobal p 257)

(defglobal omega 3)

(defglobal n 256)


(defglobal base (expmod omega (div n 8) p))

(defun inv-n (n)
    (expmod n (- p 2) p))


(defglobal a #(1 2 3 4 5 6 7 8))
(defglobal b #(0 0 0 0 0 0 0 0))


(defun w-factor (k m)
    (let ((base (expmod omega (div n m) p)))
        (expmod base k p)))

(defun plusmod (x y)
    (mod (+ x y) p))

(defun minusmod (x y)
    (mod (+ (- x y) p) p))

(defun multmod (x y)
    (mod (* x y) p))

(defun invmod (x)
    (expmod x (- p 2) p))

(defun ntt ()
    (let* ((m (length a))
           (base (expmod omega (div n m) p)))
        (ntt1 m base 0)
        (set-reverse)))

(defun ntt1 (n base pos)
    (cond ((= n 1) t)
          (t (let ((half (div n 2))
                   (temp nil))
                (for ((i 0 (+ i 1)))
                     ((>= i half))
                     (setq temp (plusmod (aref a (+ pos i)) (multmod (w-factor i n) (aref a (+ pos i half)))))
                     (set-aref (plusmod (aref a (+ pos i)) (multmod (w-factor(+ i half) n) (aref a (+ pos i half)))) a (+ pos i half))
                     (set-aref temp a  (+ pos i half)))
                (print a)
                (ntt1 (div n 2) (multmod base base) pos)
                (ntt1 (div n 2) (multmod base base) (+ pos half))))))


(defun intt ()
    (let* ((m (length a))
           (base (expmod omega (div n m) p))
           (invbase (invmod base))
           (invm (invmod m)))
        (ntt1 m invbase 0)
        (set-reverse)
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



