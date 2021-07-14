# Bit
bitwise library 

# functions
### logand
logand returns the bitwise AND of the two arguments.

```
> (logand #b0101 #b0011)
1
```

### logior
logior returns the bitwise OR for the two arguments.

```
> (logior #b0101 #b0011)
7
```

### logxor
logxor returns the bit-by-bit exclusive OR for the two arguments. 


```
> (logxor #b0101 #b0011)
6
```

###lognot
lognot returns a bit-by-bit logical negation of the argument. 

```
> (lognot 0)
-1  ; #b1111 .... 1111

> (logand 0 -1)
0
> (lognot 1)
-2  ; #b1111 .... 1110

> (logand 1 -2)
0
```

###logtest
logtest returns NIL if the result of logand is 0, T otherwise. 

```
> (logtest 3 1)
T

> (logand 3 1)
1

> (logtest 3 4)
NIL

> (logand 3 4)
0

```

###logbitp
logbitp returns T if the bit of the integer at the position of the subscript index is 1.
Conversely, if it is 0, NIL is returned. Bit positions are counted from 0, as in arrays. 

```
> (logbitp 0 #b0101)
T

> (logbitp 1 #b0101)
NIL
```

### logcount
logcount counts and returns 1 bit if integer is a positive value.
If it is a negative value, it counts and returns 0 bits. 

```
> (logcount 13)
3   ; #b...0001101

> (logcount -13)
2   ; #b...1110011
```

### ash
ash shifts integer to the left by count bits.
The low-order bit is inserted with 0. If count is negative, it shifts count bits to the right. 

```
> (ash 1 8)
256
> (ash -1 8)
-256
> (ash 256 -8)
1
```