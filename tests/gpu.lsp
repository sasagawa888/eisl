
(defglobal a #2f((1.0 2.0)(3.0 4.0)))

(defglobal b #2f((1.0 2.0)(3.0 4.0)))

(print (gpu-mult a b))
(print (gpu-add a b))