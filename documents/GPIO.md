# GPIO (libgpiod)

On Raspberry Pi, Easy-ISLisp can access GPIO through libgpiod.
If libgpiod-dev is installed, these functions are available.
Otherwise they are disabled.

# Spec

```
EISL <==================================> C (libgpiod)

;; Initialize GPIO chip
(gpio-init) <===> gpiod_chip_open("/dev/gpiochip0")
;; Returns: T on success, NIL on failure.

;; Close GPIO chip
(gpio-close) <===> gpiod_chip_close(struct gpiod_chip *)
;; Returns: T on success.

;; Set pin mode
(gpio-set-mode pin 'input | 'output) <===> gpiod_line_request_input/output(line, "easy-islisp")
;; Returns: T on success. Raises error on failure or invalid args.

;; Write pin value
(gpio-write pin value) <===> gpiod_line_set_value(line, value)
;; value: 0 or 1
;; Returns: 0 on success, negative value on failure.

;; Read pin value
(gpio-read pin) <===> gpiod_line_get_value(line)
;; Returns: 0 or 1. Raises error on failure.

;; Request event detection on pin
(gpio-event-request pin 'rising | 'falling | 'both) <===> gpiod_line_request_*_edge_events(line, "easy-islisp")
;; Returns: 0 on success, negative value on failure. Raises error on invalid args.

;; Wait for event with timeout
(gpio-event-wait pin timeout-ms) <===> gpiod_line_event_wait(line, &ts)
;; timeout-ms: integer, milliseconds
;; Returns: 1 if event occurred, 0 if timeout, negative on error.

;; Read last event
(gpio-event-read pin) <===> gpiod_line_event_read(line, &event)
;; Returns: symbol 'rising or 'falling for the detected event.
;; Raises error if no valid event.
```

# Examples

```
(import "unistd")

;; blink LED
(defun blink-led (pin count)
  (gpio-init)
  (gpio-set-mode pin 'output)
  (blink-step pin count 0)  
  (gpio-close))

(defun blink-step (pin max i)
  (if (<= i max)
      (progn
        (gpio-write pin 1)
        (usleep 500000)
        (gpio-write pin 0)
        (usleep 500000)
        (blink-step pin max (+ i 1)))
      T))


;; Button input with event detection (pin 18)
(defun button-demo ()
  (gpio-init)
  (gpio-set-mode 18 'input)
  (gpio-event-request 18 'rising)
  (button-loop 18))

(defun button-loop (pin)
  (if (gpio-event-wait pin 5000)   ;; wait 5s
      (progn
        (format (standard-output) "~A~%" (gpio-event-read pin))
        (button-loop pin))          ;; recursive loop
      (format (standard-output) "timeout~%")))

```