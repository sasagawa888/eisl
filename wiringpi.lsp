
(c-include "<wiringPi.h>")
(c-include "<wiringPiSPI.h>")
(c-option "-lwiringPi")


(defun wiringpi-setup-gpio ()
  (c-lang "Fmakeint(wiringPiSetupGpio());"))

(defun wiringpi-spi-setup-ch-speed (x y)
  (if (not (integerp x)) (error "wiringgpi-spi-setup-ch-spped: not integer" x))
  (if (not (integerp y)) (error "wiringgpi-spi-setup-ch-spped: not integer" y))
  (c-lang "Fmakeint(wiringPiSPISetup( (INT_MASK & X), (INT_MASK & Y)));"))

(defun pwm-set-mode (x)
  (cond ((eq x 'pwm-mode-ms)
         (c-lang "pwmSetMode(PWM_MODE_MS);"))
        ((eq x 'pwm-mode-bal)
         (c-lang "pwmSetMode(PWM_MODE_BAL);"))
        (t (error "pwm-set-mode: not integer" x)))
  t)
  

(defun pwm-set-range (x)
  (if (not (integerp x)) (error "pwm-set-range: not integer" x))
  (c-lang "pwmSetRange(INT_MASK & X);")
  t)

(defun pwm-set-clock (x)
  (if (not (integerp x)) (error "pwm-set-clock: not integer" x))
  (c-lang "pwmSetClock(INT_MASK & X);")
  t)


(defun pin-mode (x y)
  (cond ((eq y 'input)
         (c-lang "pinMode( (INT_MASK & X), INPUT);"))
        ((eq y 'output)
         (c-lang "pinMode( (INT_MASK & X), OUTPUT);"))
        ((eq y 'pwm-output)
         (c-lang "pinMode( (INT_MASK & X),PWM_OUTPUT);"))
        (t (error "pin-mode: illegal argument" y)))
   t)


(defun digital-write (x y)
  (if (not (integerp x)) (error "digital-write: not integer" x))
  (if (not (integerp y)) (error "digital-write: not integer" y))
  
  (c-lang "digitalWrite((INT_MASK & X),(INT_MASK & Y));")
  t)

(defun digital-write-byte (x)
  (if (not (integerp x)) (error "digital-write-byte: not integer" x))
  (c-lang "digitalWriteByte(INT_MASK & X);")
  t)


(defun pwm-write (x y)
  (if (not (integerp x)) (error "pwm-write: not integer" x))
  (if (not (integerp y)) (error "pwm-write: not integer" y))
  (c-lang "pwmWrite((INT_MASK & X),(INT_MASK & Y));")
  t)
          
(defun pull-up-dn-control (x y)
  (if (not (integerp x)) (error "pull-up-dn-control" x))
  (if (not (integerp y)) (error "pull-up-dn-control" y))
  (c-lang "pullUpDnControl((INT_MASK & X),(INT_MASK & Y));")
  t)

(defun digital-read (x)
  (if (not (integerp x)) (error "digital-read: not integer" x))
  (c-lang "Fmakeint(digitalRead(INT_MASK & X));"))

(defun delay (x)
  (if (not (integerp x)) (error "delay: not integer" x))
  (c-lang "delay(INT_MASK & X);")
  t)

(defun delay-microseconds (x)
  (if (not (integerp x)) (error "delay: not integer" x))
  (c-lang "delayMicroseconds(INT_MASK & X);")
  t)












