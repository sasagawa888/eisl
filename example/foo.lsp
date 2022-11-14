(DEFUN FOO (X) (+ X 1))
(DEFUN FACT (N) (COND ((= N 0) 1) (T (* N (FACT (- N 1))))))
(DEFUN FIB (N) (COND ((= N 0) 0) ((= N 1) 1) (T (+ (FIB (- N 1)) (FIB (- N 2))))))
