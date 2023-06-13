# Queue

Queue 
written by M.Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Spec 

enqueue(q, x)	add queue(q) data(x)
dequeue(q) 	get data from queue(q)
emptyp(q) 	if queue(q) is empty return T

# Usage

```
> (import "queue")
T
> (defglobal q (create (class <queue>)))
Q
> (emptyp q)
T
> (enqueue q 1)
(1)
> (enqueue q 2)
(2)
> (enqueue q 3)
(3)
> (enqueue q 4)
(4)
> (emptyp q)
NIL
> (dequeue q)
1
> (dequeue q)
2
> (dequeue q)
3
> (dequeue q)
4
> (dequeue q)
empty Queue

> (emptyp q)
T
```