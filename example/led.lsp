(defglobal pin 5)
(defglobal flag nil)

(defun test (n)
    (cond ((null flag) (wiringpi-setup-gpio) (setq flag t)) )
    (pin-mode pin 'output)
    (for ((i 0 (+ i 1)))
         ((> i n)
          t )
         (digital-write pin 1)
         (delay-seconds 1
         (digital-write pin 0)
         (delay-seconds 1)))

(defun setup ()
    (cond ((null flag) (wiringpi-setup-gpio) (setq flag t)) )
    (pin-mode 18 'pwm-output)
    (pwm-set-mode 'pwm-mode-ms)
    (pwm-set-clock 400)
    (pwm-set-range 1024))

(defun test1 (n)
    (pwm-write 18 n) )
