#|
I will port this code to openGL

;;Copyright (C) Takeshi Yoshida. All Rights Reserved. 
素数夜曲より　ｐ７３９
 使い方
(open-window)

(repdec (lambda (x) (check1 1 2539 x)) 300)
イロイロとパラメータを変えて遊ぶ。
(close-window)
 |#


(set-origin 300 300)
(set-zoom 20)

(defun check (a b i)
   (if (= i 0)
       (mod a b)
       (mod (* 10 (check a b (- i 1))) b)))

(defun check1 (a b i)
   (if (= i 0)
       (div a b)
       (div (* 10 (check a b (- i 1))) b)))

(defun colors (n)
   (case n
     ((0) 'blue)
     ((1) 'red)
     ((2) 'green)
     ((3) 'cyan)
     ((4) 'brown)
     ((5) 'purple)
     ((6) 'orange)
     ((7) 'yellow)
     ((8) 'magenta)
     ((9) 'black)))


(defun repdec (proc n)
   (let* ((num (quotient (+ 1 (sqrt 5)) 2))
          (ang (quotient (* 2 *pi*) (+ 1 num)))
          (size 0.1)
          (k (lambda (x) (* 10 (expt 0.998 x)))))
     (mapc (lambda (t1)
             (pen-color (colors (funcall proc t1)))
             (circle (* (k t1) (cos (* t1 ang)))
                     (* (k t1) (sin (* t1 ang)))
                     (* (k t1) size)
                     t))
           (iota (- n 1)))
     t))

(defun iota (n :rest opt)
  (let ((start (if (>= (length opt) 1) (elt opt 0) 1))
        (step (if (= (length opt) 2) (elt opt 1) 1)))
    (for ((m start (+ m step))
          (ls nil (cons m ls)))
         ((> m n)
          (reverse ls)))))

