;; stat library test

(import "test")
(import "stat")

($test (mean '(1 2 3)) 2)

($test (median '(1 2 3)) 2)

($test (mode '(2 3 1 2)) 2)

($test (variance '(1 2 3)) 0.66666666666666666666666 =)

($test (sd '(1 2 3)) 0.81649658051 =)
