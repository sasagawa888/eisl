(defmacro unless (test :rest body)
  `(if (not ,test) (progn ,@body)))

(defglobal memory (create-vector 200 0))

(defglobal code (create-vector 200 0))

(defglobal pointer 0)

(defglobal pc 0)

(defglobal nest 0)

(defun get-code ()
  (convert (elt code pc) <character>))

(defmacro inc (x)
  `(setq ,x (+ ,x 1)))

(defmacro dec (x)
  `(setq ,x (- ,x 1)))


(defun inc-mem ()
  (setf (elt memory pointer) (+ (elt memory pointer) 1)))

(defun dec-mem ()
  (setf (elt memory pointer) (- (elt memory pointer) 1)))


(defun set-mem ()
  (setf (elt memory pointer) (convert (read-char) <integer>)))

(defun ref-mem ()
  (convert (elt memory pointer) <character>))


 
(defun repl ()
   (for ((input (read-line)(read-line)))
       ((string= input "end") 'end)
       (init)
       (read-BF-code input)
       (operate-BF-code)
       (format (standard-output) "~%bf> ")))

(defun init ()
  (setq pointer 0)
  (for ((i 0 (+ i 1)))
       ((>= i 200))
       (set-elt 0 memory i))
  (for ((i 0 (+ i 1)))
       ((>= i 200))
       (set-elt 0 code i)))




(defun read-BF-code (str)
  (unless (string= str "")
    (let ((len (length str)))
      (for ((i 0 (+ i 1)))
           ((>= i len))
           (set-elt (elt str i) code i)))))
      

(defun operate-BF-code ()
  (setq pc 0)
  (for ((op (get-code) (get-code)))
       ((char= op #\null) nil)
       (cond ((char= op #\>) (inc pointer)(inc pc))
             ((char= op #\<) (dec pointer)(inc pc))
             ((char= op #\+) (inc-mem)(inc pc))
             ((char= op #\-) (dec-mem)(inc pc))
             ((char= op #\.)
              (format-char (standard-output) (ref-mem))
              (inc pc))
             ((char= op #\,) (set-mem)(ref-mem)(inc pc))
             ((and (char= op #\[)(char= (ref-mem) #\null))
                   (jump-forward)(inc pc))
             ((and (char= op #\])(not (char= (ref-mem) #\null)))
              (jump-backward)(inc pc))
             (t (inc pc)))))
            


(defun jump-forward ()
  (setq nest 0)
  (for ((op (get-code) (get-code)))
       ((and (char= op #\])(= nest 1)) t)
       (cond ((and (char= op #\])(> nest 1))
              (dec nest)(inc pc))
             ((char= op #\[)
              (inc nest)(inc pc))
             (t (inc pc)))))

(defun jump-backward ()
  (setq nest 0)
  (for ((op (get-code) (get-code)))
       ((and (char= op #\[)(= nest 1)) t)
       (cond ((and (char= op #\[)(> nest 1))
              (dec nest)(dec pc))
             ((char= op #\])
              (inc nest)(dec pc))
             (t (dec pc)))))
          


