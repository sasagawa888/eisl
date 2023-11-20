#|
The Rules of Representing Roman Numerals:

I, V, X, L, C, D, M represent 1, 5, 10, 50, 100, 500, 1000 respectively.

repeat same symbol max 3 times.

subtruct when right numeric is 5 or 10 times multiple number of left numeric. 

|#

(import "test")
(import "roman")


($test (roman-to-arabic "XXIII") 23)
($test (roman-to-arabic "VI") 6)
($test (roman-to-arabic "IV") 4)
($test (roman-to-arabic "XCIX") 99)
($test (roman-to-arabic "CMXCIX") 999)

($error (roman-to-arabic "XIIXI") <simple-error>)
($error (roman-to-arabic "IC") <simple-error>)
($error (roman-to-arabic "DCDXCIX") <simple-error>)

($test (arabic-to-roman 2) "II")
($test (arabic-to-roman 6) "VI")
($test (arabic-to-roman 4) "IV")
($test (arabic-to-roman 99) "XCIX")
($test (arabic-to-roman 999) "CMXCIX")

