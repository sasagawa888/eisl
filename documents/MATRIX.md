# Matrix
A library for working with vectors and matrices

## Usage

```lisp
(import "matrix")
```

## Specification


### data type

#### matrix
e.g. #2a((1 2)(3 4))
#### vector
e.g. #(1 2 3)
#### rows
Matrix it's elements are row vectors
#### columns
Matrix it's elements are column vectors

### Functions

#### (matrixp x)
If x is matrix data return t, else nil.

#### (vectorp x)
If x is vector data return t, else nil.

#### (matrix-elt m i j)
Returns element (i,j) of matrix m. Index i and j are start from 1. 

#### (matrix-set-elt v m i j)
Set v to element(i,j) of matrix m.

#### (matrix-transpose x)
Transposes a vector or matrix `x`

#### (add x y)
Adds x and y
x and y are number,vector,matrix

#### (sub x y)
Subtracts y from x
x and y are number,vector,matrix

#### (matrix-hadamard x y)`
This is also known as the Hadamard product

#### (mult x y)
Multiplies x and y.
x and y are number,vector,matrix

#### (matrix-negate x)
Negates `x`

#### (vector-dot x y)
Calculates the dot product of `x` and `y`

#### (vector-cross x y)
Calculates the cross product of `x` and `y`

#### (vector-norm x)
Calculates the Euclidean norm of vector `x`

#### (matrix-det x)
Returns matrix determinant of matrix `x`

#### (matrix-tr x)
Retruns matrix trace of matrix `x`

### (matrix-inverse x)
Returns inverse-matrix of matrix `x`