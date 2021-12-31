(defconstant rows 40)
(defconstant cols 10)


(defglobal ed-scroll nil)
(defglobal ed-footer nil)
(defglobal ed-row nil)
(defglobal ed-col nil)
(defglobal ed-start nil)
(defglobal ed-end nil)
(defglobal ed-ins t)
(defglobal ed-tab 0)
(defglobal ed-indent t)
(defglobal ed-name nil)
(defglobal ed-data (create-array `(,rows ,cols) 0))


(defun ed (fname)
    (system "stty raw -echo")
    (setq ed-row 0)
    (setq ed-col 0)
    (setq ed-start 0)
    (setq ed-end 24)
    (setq ed-scroll 21)
    (setq ed-footer 24)
    (esc-cls)
    (display-header fname)
    (display-screen)
    (edit-screen fname)
    (system "stty -raw echo"))


(defun display-header (fname) )

(defun display-screen ()
    (for ((r ed-start (+ r 1)))
         ((> r ed-end) t)
         (display-line r)))

(defun display-line (r)
    (for ((c 0 (+ c 1)))
         ((or (and (numberp (aref ed-data r c))(= (aref ed-data r c) 0)) (> c cols)) t)
         (format-char (standard-output) (aref ed-data r c))))

(defun edit-screen (fname)
    (let ((quit nil))
        (while (not quit)
            (setq quit (edit-loop fname)))))


(defun edit-loop (fname)
    (block loop
        (let ((c nil))
            (while t
                (setq c (read-char))
                (case c
                    ((#\^Z) (return-from loop t))
                    (t (set-aref c ed-data ed-row ed-col)
                       (setq ed-col (+ ed-col 1))
                       (display-line ed-row)))))))
    



(defun esc-move (r c)
    (progn 
        (format-char (standard-output) #\escape)
        (format-char (standard-output) #\[)
        (format-integer (standard-output) r 10)
        (format-char (standard-output) #\;)
        (format-integer (standard-output) c 10)
        (format-char (standard-output) #\backspace)))


(defun esc-cls ()
    (progn 
        (format-char (standard-output) #\escape)
        (format-char (standard-output) #\[)
        (format-integer (standard-output) 2 10)
        (format-char (standard-output) #\return)))

(defun esc-clear-line () )

