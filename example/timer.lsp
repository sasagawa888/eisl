;;; Show a simple timer using "virtty".
;;; Ported from https://github.com/HiTECNOLOGYs/cl-charms/blob/master/examples/timer.lisp

(import "virtty")
;; Please compile virtty.lsp in library beforehand.

(defglobal *start* nil)
(defglobal *stop* nil)

(defun start-stop-clear ()
   ;; Start, stop, and clear the timer successively.
   (cond (*stop* (setq *start* nil)
                 (setq *stop* nil))
         ((not *start*) (setq *stop* nil)
          (setq *start* (get-internal-real-time)))
         (t (setq *stop* (get-internal-real-time)))))

(defun time-elapsed ()
   ;; Compute the time elapsed since *START* (to *END* if set). If the timer hasn't started, return NIL.
   (and *start*
        (quotient (- (or *stop* (get-internal-real-time))
                     *start*)
                  (internal-time-units-per-second))))

(defun paint-time ()
   ;; Paint the elapsed time to the center of the screen.
   (let* ((width (tyxmax))
          (height (tyymax))
          (dt (time-elapsed))
          (str (create-string-output-stream))
          (printed-time (if dt
                            (progn (format str "~G" dt)
                                   (get-output-stream-string str))
                            "Press [SPACE] to start/stop/clear"))
          (half-length (floor (quotient (length printed-time) 2))))
         (tyco (- (floor (quotient width 2)) half-length) (floor (quotient height 2)) printed-time)))

(defun main ()
   ;; Start the timer program.
   (typrologue)
   (nodelay)
   (for ((c (tyi) (tyi)))
        ((member (convert c <character>) '(#\q #\Q)))
        (tycls)
        (paint-time)
        (tyflush)
        (if (char= (convert c <character>) #\Space)
            (start-stop-clear)))
   (tyepilogue))
