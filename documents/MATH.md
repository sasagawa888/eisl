# Math library
A library of elementary mathematics written in ISLisp.
I ported what I wrote in Scheme to understand linear algebra and elementary number theory to ISLisp.

# Functions
- (oddp n)
    
- (evenp n)
    
- (zerop n)

- (square n)

- (sum f ls)
Sum of the values of the list ls after applying the function f to each element.

- (product f ls)
Apply the function f to each element of ls then find the product.

- (for-all f ls)
Does the function f hold for all the elements in the list ls? 

- (at-least f ls)
Does the function f hold for at least one of the list ls?

- (gauss-primes x)
Returns an approximate number of prime numbers less than or equal to X by Gauss's prime number theorem.

- (coprimep m n)
If m and n are relatively prime then t, otherwise nil
    
- (divisiblep m n)
Whether m is divisible by n. If divisible t otherwise nil 
   
- (eqmodp m n a)
Whether m and n are congruent in law a. If congruent t otherwise nil 
   
- (primep n)
Primality test. If n is less than 10 ^ 11, the definitive judgment algorithm is used. If greater, the Rabin mirror method is used.

- (deterministic-prime-p n)
Returns whether n is a prime number in a definitive way.

- (prime n)
Returns nth prime number (N <= 1229)

- (primepi n)
π (n) Returns a number of prime numbers less than or equal to n.
   
- (tau n)
τ (n) Returns the number of divisors. It is calculated by factoring into prime factors.

- (liouville-lambda n)
Ryuville's lambda function.

- (perfectp n)
If n is a perfect number t otherwise nil.

- (mersenne p)
Calculates and returns Mersenne prime numbers,
i.e. of the form 2^p - 1.

- (double-perfect-number-p n)
Double perfect number?

- (find-double-perfect n)
Returns a list of double perfect numbers less than or equal to n.

- (fermatp n)
Probabilistically determine prime numbers using Fermat's Little Theorem.
If n is a prime number, t, otherwise nil.
Generate random numbers from 2 to n-1 at the bottom and try 10 times.

- (lucasp p)
Lucas test against Mersenne number 2^p - 1.
If it is a prime number, t, otherwise nil.

- (fermat-number n)
Fermat number

- (rabin-miller-p n)
Rabin mirror test.
Function body:
generate a base from 2 to n-1 (however, less than or equal to 32767) with a random number and try 10 times.
T for prime numbers, nil for composite numbers.
The probability of being a pseudoprime is 0.25 ^ 10 approximately 0.000095% 

- (gaussmod a k m)
When the result is the method m in the mod calculation by the iterative square method, it is expressed by -m / 2 to m / 2.

- (twin-primes n m)
Search for twin prime numbers between n and n + m.

- (divisors n)
Find divisors and return them as a list.

- (prime-factors n)
Factor n into prime factors. Returns a simple list of prime numbers instead of exponential format.
    
- (factorize n)
Factor n into prime factors and return it in canonical form. p^a + q^b + r^c is encoded as `((p a) (q b) (r c))`.

- (phi n)
(n=p^a q^b r^c) = n(1-1/p)(1-1/q)(1-1/r)  
Euler's φ function.
Returns the number of numbers less than or equal to n that are relatively prime to n.

- (primitive-root-p n p)
Judgment of primitive roots.
If n is a primitive root modulo the prime number p, then t.
If it is a prime number, it always exists, but if the conditions are not met, nil is returned.

- (expmod a n m)
a^n (mod m)  
Modulo calculation by iterative squares.
Calculate a ^ n (mod m).

- (primitive-root p)
Returns the smallest primitive root of the prime number p.
We decided to use the smallest primitive root to test the theorem that holds for any primitive root of p.
Because the calculation is easy. 

- (ind r a p)
Index calculation.
Find the exponent for a modulo the prime number p with the primitive root r as the base.
The exponent always exists, but nil is returned if the given value does not meet the conditions.

- (highly-composite-number-p n)
Highly composite number?

- (max-tau n m)

- (signum n)
Computes the sign or signum function
