# Chaitin's omega
The eval function is extended to test the stopping probability (Ω) of Chitin' theory.

see The LIMITS of MATHEMATICS by Gregory J. Chaitin.

# extended eval
(try limit-time S-expression binary-list)

try function converts binary-list to ascii code character and make string-input-stream.
and evaluate S-expression in limit-time.

### limit-time
limit-time(integer)  micro seconds
or 'no-time-limit symbol 

If symbol no-time-limit is geven to the first argument, the S-expression second argument is evaluated with no time limitation.

If an integer is given to the first argument, the S-expression of the second argument is evaluated with that time as the limit.

If the calculation finishes within the time
Returns a list of the following three values:

(success value argument-of-calculation-process)

If the calculation did not finish within the time
Returns a list of the following three values:

(false out-of-time argument-of-calculation-process)

If the calculation occures error
Returns a list of the following three values:

(false out-of-data argument-of-calculation-process)

### S-expression
e.g.  (eval (read-exp))

read-exp function is for try function. It read stream that created by binary-list.

### binary-list
8 bits ascii code.

e.g. 1 -> (0 0 1 1 0 0 0 1)(49(10))

ommit control code(0~31) and non ascii code(128~255)

# sample code

see example/chaitin.lsp