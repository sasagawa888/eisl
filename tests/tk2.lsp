;; tic-tac-toe

(import "tcltk")

;; element of board.  0=empty, 1=human, 2=computer
(defglobal board (create-array '(3 3) 0))
(defglobal init t)
(defglobal end nil)

(defun game ()
  (tk::init)
  (tk::canvas 'c0 '-width 600 '-height 600)
  (tk::configure 'root '-menu 'm)
  (tk::menu 'm)
  (tk::add 'm "cascade" '-label "Game" '-underline 0 '-menu '(m m1))
  (tk::menu '(m m1) '-tearoff 'no)
  (tk::add '(m m1) "command" '-label "Restart" '-underline 0 '-command '(game-init))
  (tk::add '(m m1) "command" '-label "Exit" '-underline 0 '-command '(tk::exit))
  (game-init)
  (tk::pack 'c0)
  (tk::bind 'c0 "<Button-1>" `(human %x %y))
  (tk::mainloop)
)


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
  (setq end nil)
  (for ((i 0 (+ i 1)))
       ((> i 2) t)
       (for ((j 0 (+ j 1)))
            ((> j 2) t)
            (set-aref 0 board i j) 
            (tk::create 'c0 (rectangle (* 200 i) (* 200 j) (+ (* 200 i) 200) (+ (* 200 j) 200)) '-fill 'white )))
)


(defun human (x y) 
   (block human
      (if end (return-from human t))
      (let* ((rx (tk::winfo "rootx" 'root))
             (ry (tk::winfo "rooty" 'root))
             (j (div (- x rx) 200))  ;j is col of matrix
             (i (div (- y ry) 200))) ;i is row of matrix
         (set-aref 1 board i j) 
         (paint i j 'blue)
         (if (win-p 1) 
             (progn (setq end t)
                    (tk::create 'c0 (text 250 300) '-text "Win human!" '-anchor 'nw)
                    (return-from human t)))
         (let ((res (computer i j)))
            (if (null res)
                (progn (setq end t)
                       (tk::create 'c0 (text 250 300) '-text "Game over!" '-anchor 'nw)
                       (return-from human t)))
            (let ((ri (elt res 0))
                  (rj (elt res 1)))
                    (set-aref 2 board ri rj)
                    (paint ri rj 'red)))
         (if (win-p 2) 
             (progn (setq end t)
                    (tk::create 'c0 (text 250 300) '-text "Win computer!" '-anchor 'nw)
                    (return-from human t))))))

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
      ;; if computer player one-more, get win
      (let ((res (one-more-p 2)))
        (if res (return-from after res)))
      ;; if human player one-more, disturb win
      (let ((res (one-more-p 1)))
        (if res (return-from after res)))
      ;; if not one-more, occupy corner
      (let ((res (computer-free-corner)))
        (if res (return-from after res)))
      ;; other case occupy free position
      (let ((res (computer-free)))
        (if res (return-from after res)))))
      

;; if one-more of human(x=1) or computer(x=2) return position to get win or disturb win, else return nil 
(defun one-more-p (x)
    (cond ((and (= (aref board 0 0) 0)(= (aref board 0 1) x) (= (aref board 0 2) x)) (list 0 0))
          ((and (= (aref board 0 0) 0)(= (aref board 1 0) x) (= (aref board 2 0) x)) (list 0 0))
          ((and (= (aref board 0 0) 0)(= (aref board 1 1) x) (= (aref board 2 2) x)) (list 0 0))
          ((and (= (aref board 0 1) 0)(= (aref board 0 0) x) (= (aref board 0 2) x)) (list 0 1))
          ((and (= (aref board 0 1) 0)(= (aref board 1 1) x) (= (aref board 2 1) x)) (list 0 1))
          ((and (= (aref board 0 2) 0)(= (aref board 0 0) x) (= (aref board 0 1) x)) (list 0 2))
          ((and (= (aref board 0 2) 0)(= (aref board 2 2) x) (= (aref board 1 2) x)) (list 0 2))
          ((and (= (aref board 0 2) 0)(= (aref board 1 1) x) (= (aref board 2 0) x)) (list 0 2))
          ((and (= (aref board 1 0) 0)(= (aref board 1 1) x) (= (aref board 1 2) x)) (list 1 0))
          ((and (= (aref board 1 0) 0)(= (aref board 0 0) x) (= (aref board 2 0) x)) (list 1 0))
          ((and (= (aref board 1 1) 0)(= (aref board 0 0) x) (= (aref board 2 2) x)) (list 1 1))
          ((and (= (aref board 1 1) 0)(= (aref board 0 1) x) (= (aref board 2 1) x)) (list 1 1))
          ((and (= (aref board 1 1) 0)(= (aref board 0 2) x) (= (aref board 2 0) x)) (list 1 1))
          ((and (= (aref board 1 1) 0)(= (aref board 1 0) x) (= (aref board 1 2) x)) (list 1 1))
          ((and (= (aref board 1 2) 0)(= (aref board 1 0) x) (= (aref board 1 1) x)) (list 1 2))
          ((and (= (aref board 1 2) 0)(= (aref board 2 2) x) (= (aref board 0 2) x)) (list 1 2))
          ((and (= (aref board 2 0) 0)(= (aref board 0 0) x) (= (aref board 1 0) x)) (list 2 0))
          ((and (= (aref board 2 0) 0)(= (aref board 1 1) x) (= (aref board 0 2) x)) (list 2 0))
          ((and (= (aref board 2 0) 0)(= (aref board 2 1) x) (= (aref board 2 2) x)) (list 2 0))
          ((and (= (aref board 2 1) 0)(= (aref board 2 0) x) (= (aref board 2 2) x)) (list 2 1))
          ((and (= (aref board 2 1) 0)(= (aref board 0 1) x) (= (aref board 1 1) x)) (list 2 1))
          ((and (= (aref board 2 2) 0)(= (aref board 2 0) x) (= (aref board 2 1) x)) (list 2 2))
          ((and (= (aref board 2 2) 0)(= (aref board 0 2) x) (= (aref board 1 2) x)) (list 2 2))
          ((and (= (aref board 2 2) 0)(= (aref board 1 1) x) (= (aref board 0 0) x)) (list 2 2))
          (t nil)))


;; if not one-more of human and computer, occupy free corner
(defun computer-free-corner ()
  (cond ((= (aref board 0 0) 0) (list 0 0))
        ((= (aref board 2 0) 0) (list 2 0))
        ((= (aref board 0 2) 0) (list 0 2))
        ((= (aref board 2 2) 0) (list 2 2))))

;; if other case return free position
(defun computer-free ()
   (block test
      (for ((i 0 (+ i 1)))
           ((> i 2) nil)
           (for ((j 0 (+ j 1)))
                ((> j 2) nil)
                (if (= (aref board i j) 0)
                    (return-from test (list i j)))))))


(defun paint (i j color)
    (tk::create 'c0 (oval (+ (* 200 j) 20) (+ (* 200 i) 20) (+ (* 200 j) 180) (+ (* 200 i) 180)) '-fill color))