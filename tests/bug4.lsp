(import "test")

(defdynamic *dyn1* 1)

($test
    (dynamic *dyn1*)
    1)

(dynamic-let ((*dyn1* 2)
              (*dyn2* 3))
  ($test (dynamic *dyn1*) 2)
  ($test (dynamic *dyn2*) 3)
  (set-dynamic 4 *dyn1*) 
  ($test (dynamic *dyn1*) 4))

($test (dynamic *dyn1*) 1)


