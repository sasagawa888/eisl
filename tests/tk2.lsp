;; tic-tac-toe

(import "tcltk")

;; element of board.  0=empty, 1=human, 2=computer
(defglobal board (create-array '(3 3) 0))
(defglobal init t)

(defun game ()
  (tk::init)
  (tk::canvas 'c0 '-width 600 '-height 600)
  (tk::configure 'root '-menu 'm)
  (tk::menu 'm)
  (tk::add 'm "cascade" '-label "Game" '-underline 0 '-menu '(m m1))
  (tk::menu '(m m1) '-tearoff 'no)
  (tk::add '(m m1) "command" '-label "Exit" '-underline 0 '-command "exit")
  (game-init)
  (tk::pack 'c0)
  (tk::bind 'c0 "<Button-1>" `(human %x %y))
  (tk::mainloop)
)

(defun game-over-p ()
    (block test
      (for ((i 0 (+ i 1)))
           ((> i 2) t)
           (for ((j 0 (+ j 1)))
                ((> j 2) t)
                (if (= (aref board i j) 0)
                    (return-from test nil))))))

(defun win-p (x)
    (cond ((and (= (aref board 0 0) x) (= (aref board 1 1) x) (= (aref board 2 2) x)) t)
          ((and (= (aref board 0 2) x) (= (aref board 1 1) x) (= (aref board 2 0) x)) t)
          ((and (= (aref board 0 0) x) (= (aref board 0 1) x) (= (aref board 0 2) x)) t)
          ((and (= (aref board 1 0) x) (= (aref board 1 1) x) (= (aref board 1 2) x)) t)
          ((and (= (aref board 2 0) x) (= (aref board 2 1) x) (= (aref board 2 2) x)) t)
          ((and (= (aref board 0 0) x) (= (aref board 1 0) x) (= (aref board 2 0) x)) t)
          ((and (= (aref board 0 1) x) (= (aref board 1 1) x) (= (aref board 2 1) x)) t)
          ((and (= (aref board 0 2) x) (= (aref board 1 2) x) (= (aref board 2 2) x)) t)))

(defun game-init ()
  (setq init t)
  (for ((i 0 (+ i 1)))
       ((> i 2) t)
       (for ((j 0 (+ j 1)))
            ((> j 2) t)
            (set-aref 0 board i j) 
            (tk::create 'c0 (rectangle (* 200 i) (* 200 j) (+ (* 200 i) 200) (+ (* 200 j) 200)) )))
)


(defun human (x y) 
   (let* ((rx (tk::winfo "rootx" 'root))
          (ry (tk::winfo "rooty" 'root))
          (i (div (- x rx) 200))
          (j (div (- y ry) 200)))
      (set-aref 1 board i j)
      (paint i j 'blue)
      (if (win-p 1) (print "win human"))
      (let* ((res (computer i j))
             (ri (elt res 0))
             (rj (elt res 1)))
         (set-aref 2 board ri rj)
         (paint ri rj 'red))
      (if (win-p 2) (print "win computer"))
      (if (game-over-p) (print "game-over"))))

(defun computer (i j)
   (cond (init (computer1 i j))
         (t (computer2))))

;; first step
(defun computer1 (i j)
   (cond ((and (= i 1) (= j 1)) (setq init nil) (list 0 0))
         (t (setq init nil) (list 1 1))))

;; after first step
(defun computer2 ()
    (block after
      (let ((res (reach-p 1)))
        (if res (return-from after res)))
      (let ((res (reach-p 2)))
        (if res (return-from after res)))
      (let ((res (computer-free-corner)))
        (if res (return-from after res)))
      (let ((res (computer-free)))
        (if res (return-from after res)))))
      

;; if reach of human disturb win else return nil 
(defun reach-p (x)
    (cond ((and (= (aref board 0 0) 0)(= (aref board 0 1) x) (= (aref board 0 2) x)) (list 0 0))
          ((and (= (aref board 0 0) 0)(= (aref board 1 0) x) (= (aref board 2 0) x)) (list 0 0))
          ((and (= (aref board 0 0) 0)(= (aref board 1 1) x) (= (aref board 2 2) x)) (list 0 0))
          ((and (= (aref board 0 1) 0)(= (aref board 0 0) x) (= (aref board 0 2) x)) (list 0 1))
          ((and (= (aref board 0 1) 0)(= (aref board 1 1) x) (= (aref board 2 1) x)) (list 0 1))
          ((and (= (aref board 0 2) 0)(= (aref board 0 0) x) (= (aref board 0 1) x)) (list 0 2))
          ((and (= (aref board 0 2) 0)(= (aref board 0 0) x) (= (aref board 0 1) x)) (list 0 2))
          ((and (= (aref board 0 2) 0)(= (aref board 1 1) x) (= (aref board 2 0) x)) (list 0 2))
          ((and (= (aref board 1 0) 0)(= (aref board 1 1) x) (= (aref board 1 2) x)) (list 1 0))
          ((and (= (aref board 1 0) 0)(= (aref board 0 0) x) (= (aref board 2 0) x)) (list 1 0))
          ((and (= (aref board 1 1) 0)(= (aref board 0 0) x) (= (aref board 2 2) x)) (list 1 1))
          ((and (= (aref board 1 1) 0)(= (aref board 0 1) x) (= (aref board 2 1) x)) (list 1 1))
          ((and (= (aref board 1 1) 0)(= (aref board 0 2) x) (= (aref board 2 0) x)) (list 1 1))
          ((and (= (aref board 1 1) 0)(= (aref board 1 0) x) (= (aref board 1 2) x)) (list 1 1))
          ((and (= (aref board 1 2) 0)(= (aref board 1 0) x) (= (aref board 1 1) x)) (list 1 2))
          ((and (= (aref board 2 0) 0)(= (aref board 0 0) x) (= (aref board 1 0) x)) (list 2 0))
          ((and (= (aref board 2 0) 0)(= (aref board 2 1) x) (= (aref board 2 2) x)) (list 2 0))
          ((and (= (aref board 2 0) 0)(= (aref board 1 1) x) (= (aref board 0 2) x)) (list 2 0))
          ((and (= (aref board 2 1) 0)(= (aref board 2 0) x) (= (aref board 2 2) x)) (list 2 1))
          ((and (= (aref board 2 1) 0)(= (aref board 0 1) x) (= (aref board 1 1) x)) (list 2 1))
          ((and (= (aref board 2 2) 0)(= (aref board 2 0) x) (= (aref board 2 1) x)) (list 2 2))
          ((and (= (aref board 2 2) 0)(= (aref board 2 0) x) (= (aref board 2 1) x)) (list 2 2))
          ((and (= (aref board 2 2) 0)(= (aref board 1 1) x) (= (aref board 0 0) x)) (list 2 2))
          (t nil)))


;; if not reach of human and computer, occupy free corner
(defun computer-free-corner ()
  (cond ((= (aref board 0 0) 0) (list 0 0))
        ((= (aref board 2 0) 0) (list 2 0))
        ((= (aref board 0 2) 0) (list 0 2))
        ((= (aref board 2 2) 0) (list 2 2))))

;; if other case return free position
(defun computer-free ()
   (block test
      (for ((i 0 (+ i 1)))
           ((> i 2) t)
           (for ((j 0 (+ j 1)))
                ((> j 2) t)
                (if (= (aref board i j) 0)
                    (return-from test (list i j)))))))


(defun paint (i j color)
    (tk::create 'c0 (oval (* 200 i) (* 200 j) (+ (* 200 i) 200) (+ (* 200 j) 200)) '-fill color))