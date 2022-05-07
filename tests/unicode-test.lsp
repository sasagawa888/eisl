#|
Unicode extention tests
|#

(import "test")

($test (char= #\笹 #\笹) t)
($test (char= #\笹 #\川) nil)
($test (string= "こんにちは世界" "こんにちは世界") t)
($test (string= "こんにちは世界" "こんちは世界") nil)
($test (convert "こんにちは世界" <list>) (#\こ #\ん #\に #\ち #\は #\世 #\界))
($test (convert #\山 <string>) "山")
($test (convert #\山 <integer>) 23665)
($test (elt "笹川賢一" 0) #\笹)
($test (elt "笹川賢一" 1) #\川)
($test (subseq "笹川賢一" 0 2) "笹川")
