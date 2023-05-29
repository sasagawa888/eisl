# Hash 

The hash library was written by M. Hiroi.

# Acknowledgement
Thanks to Mr. Hiroi.

# Usage 

```lisp
(import "hash")

```

# Specification

- create (class <hash>)
Generate a hash table (specify the size of the hash table with "size").

- gethash ht key
Retrieve the value of key from the hash table ht. If the key is not found, it returns nil.

- sethash ht key val
Register the key (key) and value (val) in the hash table ht.

- remhash ht key
Remove the key (key) from the hash table ht. If the key is successfully removed, it returns t; if the key is not found, it returns nil.

- clrhash ht
Empty the hash table ht.

- hash-count ht
Return the number of elements registered in the hash table.

- maphash fn ht
Apply the function fn to each element (key, val) of the hash table. Unlike mapcar, the return values of fn are discarded.


# Example

```
>(defglobal h (create (class )))
H
>(sethash h "foo" 10)
10
>(sethash h "bar" 20)
20
>(sethash h "baz" 20)
20
>(sethash h "baz" 30)
30
>(sethash h "oops" 40)
40
>(hash-count h)
4
>(gethash h "foo")
10
>(gethash h "bar")
20
>(gethash h "baz")
30
>(gethash h "oops")
40
>(gethash h "Oops")
NIL
>(maphash (lambda (x y) (format (standard-output) "~A ~D~%" x y)) h)
bar 20
baz 30
foo 10
oops 40
NIL
>(remhash h "foo")
T
>(hash-count h)
3
>(remhash h "foo")
NIL
>(remhash h "bar")
T
>(remhash h "baz")
T
>(remhash h "oops")
T
>(hash-count h)
0

```