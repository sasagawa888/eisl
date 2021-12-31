(defconstant rows 4000)
(defconstant cols 80)


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
(defglobal ed-data (create-array `(,rows ,cols) #\null))


(defun editor (fname)
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
         ((or (char= (aref ed-data r c) #\null) (c > cols)) t)
         (format-char (standard-output) (aref ed-data r c))))

(defun edit-screen (fname)
    (let ((quit nil))
        (while (not quit)
            (setq quit (edit-loop fname)))))


(defun edit-loop (fname) )



(defun esc-move (r c)
    (progn 
        (format-char (standard-output) #\escape)
        (format-char (standard-output) #\[)
        (format-integer (standard-output) r 10)
        (format-char (standard-output) #\;)
        (format-integer (standard-output) c 10)
        (format-char (standard-output) #\newline)))


(defun esc-cls () )

(defun esc-clear-line () )

