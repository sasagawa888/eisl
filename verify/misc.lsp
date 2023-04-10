(import "test")
(import "datetime")
;;;
;;;  Miscellaneous
;;;

($ap 1 "Miscellaneous")

;;;
;;; (IDENTITY obj) --> <object>
;;;
($ap 2 "identity" P.120)
($test (let ((x '(a b c))) (eql (identity x) x)) t)
;;;
($argc identity 1 0 0)
;;;
($test (let ((x "abc")) (eql (identity x) x)) t)
($test (let ((x #(a b c))) (eql (identity x) x)) t)

;;;
;;; (GET-UNIVERSAL-TIME) --> <integer>
;;;
($ap 2 "get-universal-time" P.120)
;;;
($argc get-universal-time 0 0 0)
;;;
($test (let ((time (get-universal-time))) (and (integerp time) (< 0 time))) t)
($test (let ((t1 (get-universal-time))
             (dummy (sleep 2))
             (t2 (get-universal-time)))
         (< t1 t2))
       t)

;;;
;;; (GET-INTERNAL-RUN-TIME) --> <integer>
;;;
($ap 2 "get-internal-run-time" P.121)
;;;
($argc get-internal-run-time 0 0 0)
;;;
($test (let ((time (get-internal-run-time))) (and (integerp time) (< 0 time))) t)
($test (let ((t1 (get-internal-run-time))
       (dummy (sleep 1))  
       (t2 (get-internal-run-time)))
   (< t1 t2))
 t)

;;;
;;; (GET-INTERNAL-REAL-TIME) --> <integer>
;;;
($ap 2 "get-internal-real-time" P.121)
;;;
($argc get-internal-real-time 0 0 0)
;;;
($test (let ((time (get-internal-real-time))) (and (integerp time) (< 0 time))) t)
($test (let ((t1 (get-internal-real-time))
       (dummy (sleep 1))
       (t2 (get-internal-real-time)))
   (< t1 t2))
 t)

;;;
;;; (internal-time-units-per-second) --> <integer>
;;;
($ap 2 "internal-time-units-per-second" P.121)
;;;
($argc internal-time-units-per-second 0 0 0)
;;;
($test (< 0 (internal-time-units-per-second)) t)
