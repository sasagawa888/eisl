# Matrix
A library for working with vectors and matrices

## Usage

```lisp
(import "matrix")
```

## Specification

### Functions

#### (**rows** *matrix*)
Returns the row vectors of matrix `matrix`

#### (**rows->matrix** *rows*)
Converts a vector of row vectors into a matrix

#### (**columns** *matrix*)
Returns the column vectors of matrix `matrix`

#### (**colmuns->matrix** *columns*)
Converts a vector of column vectors into a matrix

#### (**transpose** *x*)
Transposes a vector or matrix `x`

#### (**add** *operand* *operand+*)
Adds the operands `operand` together

#### (**sub** *operand* *operand+*)
Subtracts the operands `operand` from left to right

#### (**element-wise-product** *operand* *operand+*)`
Performs the element-wise product on operands `operand`.
This is also known as the Hadamard product

#### (**mult** *operands* *operand+*)
Multiplies operands `operand` together from left to right

#### (**negate** *x*)
Negates `x`

#### (**dot** *x* *y*)
Calculates the dot product of `x` and `y`

#### (**cross** *x* *y*)
Calculates the cross product of `x` and `y`

#### (**norm** *x*)
Calculates the Euclidean norm of vector `x`

#### (**normalize** *x*)
Normalizes vector `x`

#### (**cartesian-product** *vector+*)
Returns the cartesian product of the vectors `vector`