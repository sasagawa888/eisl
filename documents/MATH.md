# Math library
A library of elementary mathematics written in ISLisp. 
I ported what I wrote in Scheme to understand linear algebra and elementary number theory to ISLisp. 
It also tests the EISL compiler. 
Linear algebra relations assume that subscripts start from 1 as in mathematics. 

# function
### (oddp n)
    
### (evenp n)
    
### (zerop n)

### (square n)
    
### (mult-scalar-mat s x)
Multiply the elements of the matrix x by a.

### (matrix-ident n)
identity matrix

### (square-matrix-p x)

### (tr x)
trace of matrix x

### (sub-matrix x r s)
Submatrix of x for position (r, s)    

### (det x)
Determinant of matrix x

### (transpose x)
transposed matrix of x    

### (inv x)
Inverse matrix Cramer's rule. The efficiency is not good, but there is no problem if it is about 5 dimensions. 

### (sum f ls)
Sum of the values of the list ls with the function f applied.

### (product f ls)
Apply the function f to each element of ls to find the product.  

### (for-all f ls)
Does the function f hold for all the elements in the list ls? 

### (at-least f ls)
Does the function f hold in at least one of the list ls?

### (gauss-primes x)
Returns an approximate number of prime numbers less than or equal to X by Gauss's prime number theorem 

### (coprimep m n)
If m and n are relatively prime, then t otherwise nil
    
### (divisiblep m n)
Whether m is divisible by n. If divisible t otherwise nil 
   
### (eqmodp m n a)
Whether m and n are congruent in law a. If congruent t otherwise nil 
   
### (primep n)
If it is smaller than 10 ^ 11, it is judged by the definitive judgment algorithm, and if it is larger, it is judged by the Rabin mirror method.

### (deterministic-prime-p n)
Returns whether n is a prime number in a definitive way. 

### (primepi n)
π (n) Returns a number of prime numbers less than or equal to n.
   
### (tau n)
τ (n) Returns the number of divisors. It is calculated by factoring into prime factors.

### (liouville-lambda n)
Ryuville's lambda function 

### (perfectp n)
If perfect number t otherwise nil 

### (mersenne p)
Calculates and returns Mersenne prime numbers.
2 ^ p -1 

### (double-perfect-number-p n)
Double perfect number?

### (find-double-perfect n)
Returns a list of double perfect numbers less than or equal to n. 

### (fermatp n)
Probabilistically determine prime numbers using Fermat's Little Theorem.
If it is a prime number, t, otherwise nil
Generate random numbers from 2 to n-1 at the bottom and try 10 times. 

### (lucasp p)
Lucas-test against Mersenne number (2 ^ p-1)
If it is a prime number, t, otherwise nil.

### (fermat-number n)
Fermat number

### (rabin-miller-p n)
Rabin mirror test
Function body
Generate a base from 2 to n-1 (however, 32767 or less) with a random number and try 10 times.
T for prime numbers nil for composite numbers
The probability of being a pseudoprime is 0.25 ^ 10 approximately 0.000095% 

### (gaussmod a k m)
When the result is the method m in the mod calculation by the iterative square method, it is expressed by -m / 2 to m / 2. 

### (twin-primes n m)
Search for twin prime numbers from n to n + m.

### (divisors n)
Find the divisors and return them as a list. 

### (prime-factors n)
Factor n into prime factors. Returns a simple list of prime numbers instead of exponential format. 
    
### (factorize n)
Factor n into prime factors and return it in canonical form. p ^ a + q ^ b + r ^ c ((p a) (q b) (r c)) 


### (phi n)
(n=p^a q^b r^c) = n(1-1/p)(1-1/q)(1-1/r)   
Euler's φ function
Returns the number of numbers less than or equal to n that are relatively prime to n. 

### (primitive-root-p n p)
Judgment of primitive roots
If n is a primitive root modulo the prime number p, then t
If it is a prime number, it always exists, but if the conditions are not met, nil is returned. 

### (expmod a n m)
a^n (mod m)    
Modulo calculation by iterative squares.
Calculate a ^ n (mod m). 

### (primitive-root p)
Returns the smallest primitive root of the prime number p.
We decided to use the smallest primitive root to test the theorem that holds for any primitive root of p.
Because the calculation is easy. 

### (ind r a p)
Index calculation
Find the exponent for a modulo the prime number p with the primitive root r as the base
The exponent always exists, but nil is returned if the given value does not meet the conditions. 

### (highly-composite-number-p n)
Highly composite number?

### (max-tau n m)
   
