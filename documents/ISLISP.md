# ISLISP functions

## array
- (BASIC-ARRAY-P obj) `boolean` Check if obj is an array, string or vector
- (BASIC-ARRAY*-P obj) `boolean` Check if obj is an array
- (GENERAL-ARRAY*-P obj) `boolean` Check if obj is a general-array
- (CREATE-ARRAY dimensions initial-element +) `<basic-array>` Generate an array
- (AREF basic-array z *) `<object>` Return the zth element of the basic-array
- (GAREF general-array z *) `<object>` Return the zth element of the general-array
- (SET-AREF obj basic-array z *) `<object>` Set the zth element of the basic-array to obj
- (SET-GAREF obj general-array z *) `<object>` Set the zth element of the general-array to obj
- (ARRAY-DIMENSIONS basic-array) `<list>` Return a list of the dimensions of a basic-array

## char
- (CHARACTERP obj) `boolean` Check if obj is a string
- (CHAR= char1 char2) `boolean` Check if the characters char1 and char2 are equal
- (CHAR/= char1 char2) `boolean` Check if the characters char1 and char2 are not equal
- (CHAR< char1 char2) `boolean` Check if the character code of char1 is less than char2
- (CHAR> char1 char2) `boolean` Check if the character code of char1 is greater than char2
- (CHAR<= char1 char2) `boolean` Check if the character code of char1 is less than or equal to char2
- (CHAR>= char1 char2) `boolean` Check if the character code of char1 is greater than or equal to char2

## cond
- (error error-string obj *) `<object>` Signal an error
- (cerror continue-string error-string obj *) `<object>` Signal a continuable error
- (signal-condition condition continuable) `<object>` Signal a condition
- (ignore-errors form *) `<object>` Ignore errors (special form)
- (report-condition condition stream) `<condition>` Report the condition 'condition' to stream 'stream' 
- (condition-continuable condition) `<object>` Check if a condition is continuable
- (continue-condition condition value +) `<object>` Continue from a condition
- (with-handler handler form *) `<object>` Evaluate the handler and execute the form (special form)
- (arithmetic-error-operation arithmetic-error) `<function>` Return the operation of an arithmetic error
- (arithmetic-error-operands arithmetic-error) `<list>` Return the operands of an arithmetic error
- (domain-error-object domain-error) `<object>`  Return the object supplied when creating the domain error 'domain-error'
- (domain-error-expected-class domain-error) `<class>` Domain error, return the desired domain supplied when creating 'domain-error'
- (parse-error-string parse-error) `<string>` Parsing error, return the string supplied when creating 'parse-error
- (parse-error-expected-class parse-error) `<class>`  Parsing error, return the desired class supplied when creating 'parse-error'
- (simple-error-format-string simple-error) `<string>` Return the string supplied when creating 'simple-error'
- (simple-error-format-arguments simple-error) `<list>` Return the list of arguments supplied when creating 'simple-error'
- (stream-error-stream stream-error) `<stream>` Stream error, return the stream supplied when creating 'stream-error'
- (undefined-entity-name undefined-entity) `<symbol>` Return the symbol supplied when createing the undefined entity 'undefined-entity'
- (undefined-entity-namespace undefined-entity) `<symbol>` Return the namespace supplied when createing the undefined entity 'undefined-entity'

## control
- (quote obj) `<object>` Return a reference to obj (special form)
- (setq var form) `<object>` Assign the result of evaluating 'form' to the variable 'var' (special form)
- (setf place form) `<object>` Assign the result of evaluating 'form' to 'place' (special form)
- (let ((var form) *) body-form *) `<object>` Define local variables and execute 'body-form ...' in that environment (special form)
- (let* ((var form) *) body-form *) `<object>`  Similar to let, except that local variables are bound sequentially (special form)
- (dynamic var) `<object>` Return the binding of a dynamic variable (special form)
- (setf (dynamic var) form) `<object>` Assign a value to a dynamic variable (special form)
- (dynamic-let ((var form) *) body-form *) `<object>` Temporarily bind dynamic variables (special form)
- (if test-form then-form else-form+) `<object>` Branch according to a condition (special form)
- (cond (test form *) *) `<object>` Branch according to a condition (special form)
- (case keyform ((key *) form *) * (t form *)+) `<object>` Branches in various ways depending on the value of keyform (special form)
- (case-using predform keyform ((key *) form *) * (t form *) +) `<object>` Almost the same as the case statement, but using the predicate function 'predform' for comparison (special form)
- (progn form*) `<object>` Perform sequential execution (special format)
- (while test-form body-form *) `<null>` Execute body-form repeatedly as long as 'test-form' is not nil (special form)
- (for (iteration-spec *) (end-test result *) form *) `<object>` Iterate repeatedly while end-test is not nil, using the initial values and steppers indicated by iteration-spec (special form)
- (block name form *) `<object>` Execute sequentially with block tags (special format)
- (return-from name result-form) transfers-control-and-data Exit the 'name' block (special form)
- (catch tag-form form *) `<object>` Catch tag-form and execute 'form ...' (special form)
- (throw tag-form result-form) transfers-control-and-data Throw tag-form (special form)
- (tagbody tagbody-tag * form *) `<object>` Execute sequentially with optional 'tagbody-tag' labels (special form)
- (go tagbody-tag) transfers-control Transfer control to 'tagbody-tag' in a tagbody (special format)
- (unwind-protect form cleanup-form *) `<object>`  Execute 'cleanup-form ...' whenever the evaluation of 'form' finishes (special form)

## declare
- (THE class-name form) `<object>` Declare the class of the execution result of 'form' as class-name (special form)
- (ASSURE class-name form) `<object>` Claim the class of the execution result of 'form' as class-name, if it is different, an error will occur (special form)
- (CONVERT obj class-name) `<object>` Convert obj to class 'class-name' (special form)

## files
- (probe-file filename) `boolean` Check if a file 'filename' exists
- (file-position stream) `<integer>` Return the current file position of a stream
- (set-file-position stream z) `<integer>` Set the file position of 'stream' to z
- (file-length filename element-class) `<integer>` Return the size of the file 'filename' as an 'element-class' file

## formeval
- (functionp obj) `boolean` Check if obj is a function
- (function function-name) `<function>` Returns a function named function-name (special form)
- (lambda lambda-list form *) `<function>` Generate a lambda expression (special form)
- (labels ((function-name lambda-list form *) *) body-forms *) `<object>`  Like 'flet', but binds local functions sequentially (recursive definition is possible) (special form)
- (flet ((function-name lambda-list form *) *) body-forms *) `<object>`  Binds local functions (special form)
- (apply function obj * list) `<object>` Apply function
- (funcall function obj *) `<object>` Call function
- (defconstant name form) `<symbol>` Define a constant (special form)
- (defglobal name form) `<symbol>` Define a global variable (special form)
- (defdynamic name form) `<symbol>` Define a dynamic variable (special form)
- (defun function-name lambda-list form *) `<symbol>` Define a function (special form)

## io
- (read input-stream + eos-error-p + eos-value +) `<object>` Read an S-expression from 'input-stream'
- (read-char input-stream + eos-error-p + eos-value +) `<object>` Read one character from 'input-stream'
- (preview-char input-stream + eos-error-p + eos-value +) `<object>`  Returnsthe next character that will be read (one character look-ahead, file position does not change)
- (read-line input-stream + eos-error-p + eos-value +) `<object>` Read one line as a string
- (stream-ready-p input-stream) `boolean` Is the stream readable?
- (format output-stream format-string obj *) `<null>` Output obj according to format-string
- (format-char output-stream char) `<null>` Output one character
- (format-float output-stream float) `<null>` Output as a floating point number
- (format-fresh-line output-stream) `<null>` Begin on a new line
- (format-integer output-stream integer radix) `<null>` Output as an integer
- (format-object output-stream obj escape-p) `<null>` Output as an object
- (format-tab output-stream column) `<null>` Output ASCII TAB
- (read-byte input-stream eos-error-p + eos-value +) `<integer>` Read as a byte
- (write-byte z output-stream) `<integer>` Write as a byte

## list
- (CONSP obj) `boolean` Check if obj is a cons
- (CONS obj1 obj2) `<cons>` Generate a cons
- (CAR cons) `<object>` Return the Car part of a cons
- (CDR cons) `<object>` Return the Cdr part of a cons
- (SET-CAR obj cons) `<object>` Set the Car part of a cons
- (SET-CDR obj cons) `<object>` Set the Cdr part of a cons
- (NULL obj) `boolean` Check if obj is null
- (LISTP obj) `boolean` Check if obj is a list
- (CREATE-LIST i initial-element +) `<list>` Generates a list with length i and initial values 'initial-element'
- (LIST obj *) `<list>` Generate a list with every element set to obj
- (REVERSE list) `<list>` Reverse the list (do not destroy the original list)
- (NREVERSE list) `<list>` Reverse the list (the original list is destroyed)
- (APPEND list *) `<list>` Concatenate lists
- (MEMBER obj list) `<list>`  If the list list contains obj, it returns a partial list starting with obj
- (MAPCAR function list +) `<list>` Execute the function function on the elements of list 'list' and return a list of results
- (MAPC function list +) `<list>`  Execute the function function on the elements of list 'list' and return the 'list' argument
- (MAPCAN function list +) `<list>`  Like 'mapcar', but the list is destroyed
- (MAPLIST function list +) `<list>`  Execute 'function' on a part of 'list' and return a list of results
- (MAPL function list +) `<list>`  Executes the 'function' on a part of 'list' and return the 'list' argument
- (MAPCON function list +) `<list>` Like 'maplist', but the list is destroyed
- (ASSOC obj association-list) `<cons>`  Return an obj-keyed value from association-list

## macro
- (defmacro macro-name lambda-list form *) `<symbol>` Define a macro (special form)

## misc
- (IDENTITY obj) `<object>` Return obj as is
- (GET-UNIVERSAL-TIME) `<integer>` Returns universal time (seconds)
- (GET-INTERNAL-RUN-TIME) `<integer>` Return the execution time
- (GET-INTERNAL-REAL-TIME) `<integer>` Return elapsed time
- (internal-time-units-per-second) `<integer>` Return internal time units per second

## number
- (NUMBERP obj) `boolean` Test if 'obj' is a number
- (PARSE-NUMBER string) `<number>` Parse the string 'string' and convert it into a number
- (= x1 x2) `boolean` Test if two numeric values are equal
- (/= x1 x2) `boolean` Test if two numeric values are not equal
- (>= x1 x2) `boolean` Test if numeric value 'x1' is greater than or equal to 'x2'
- (<= x1 x2) `boolean` Test if numeric value 'x1' is less than or equal to 'x2'
- (> x1 x2) `boolean` Test if numeric value 'x1' is greater than 'x2'
- (< x1 x2) `boolean` Test if numeric value 'x1' is less than 'x2'
- (+ x *) `<number>` Sum of the numbers 'x ...'
- (* x *) `<number>` Product of the numbers 'x ...'
- (- x y *) `<number>` Successive subtraction of 'x y ...'
- (QUOTIENT dividend divisor +) `<number>` Successive division of 'dividend' by 'divisor ...'
- (RECIPROCAL x) `<number>` Return 1/x
- (MAX x y *) `<number>` Return the maximum of 'x y ...'
- (MIN x y *) `<number>` Return the minimum of 'x y ...'
- (ABS x) `<number>` Return the absolute value of 'x'
- (EXP x) `<number>` Return e^x
- (LOG x) `<number>` Return the natural logarithm of x
- (EXPT x1 x2) `<number>` Return x1 to the power of x2
- (SQRT x) `<number>` Return the positive square root of x
- (SIN x) `<number>` Return the sine of x
- (COS x) `<number>` Return the cosine of x
- (TAN x) `<number>` Return the tangent of x
- (ATAN x) `<number>` Return the arctangent of x
- (ATAN2 x1 x2) `<number>` Convert from rectangular coordinates (x1, x2) to the angle part of a polar coordinate
- (SINH x) `<number>` Return the hyperbolic sine of x
- (COSH x) `<number>` Return the hyperbolic cosine of x
- (TANH x) `<number>` Return the hyperbolic tangent of x
- (ATANH x) `<number>` Return the hyperbolic tangent of x
- (FLOATP obj) `boolean` Test if 'obj' is a floating-point number
- (FLOAT x) `<float>` Convert 'x' to a floating-point number
- (FLOOR x) `<integer>` Truncation towards negative infinity
- (CEILING x) `<integer>` Truncation towards positive infinity
- (TRUNCATE x) `<integer>` Truncation towards 0
- (ROUND x) `<integer>` Round to integer nearest 'x'
- (INTEGERP obj) `boolean` Check if 'obj' is an integer
- (DIV z1 z2) `<integer>` Integer division
- (MOD z1 z2) `<integer>` Modulus
- (GCD z1 z2) `<integer>` 'Greatest Common Divisor' or 'Highest Common Factor'
- (LCM z1 z2) `<integer>` 'Lowest Common Multiple'
- (ISQRT z) `<integer>` Integer square root, i.e. greatest integer <= '(sqrt z)'

## object
- (defclass class-name (sc-name *) (slot-spec *) class-opt *) `<symbol>`  Define a class (special form)
- (generic-function-p obj) `boolean` Test of 'obj' is a generic function
- (defgeneric func-spec lambda-list option * method-desc *) `<symbol>`  Define a generic function (special form)
- (defmethod func-spec method-qualifier * parameter-profile form *) `<symbol>` Define a method (special form)
- (call-next-method) `<object>` Call the next method in a class's precedence order (special form)
- (next-method-p) `boolean` Test if a next method exists (special form)
- (create class initarg * initval *) `<object>` Create an instance of a class (generic function)
- (initialize-object instance initialization-list) `<object>` Initialize an object
- (class-of obj) `<class>` Return the class of an object
- (instancep obj class) `boolean` Test whether 'obj' is an instance of 'class'
- (subclassp class1 class2) `boolean` Test for a subclass relation
- (class class-name) `<class>` Return the class named 'class-name' (special form)

## pred
- (EQ obj1 obj2) `boolean` Test whether obj1 and obj2 are 'eq'
- (EQL obj1 obj2) `boolean` Test whether obj1 and obj2 are 'eql'
- (EQUAL obj1 obj2) `boolean` Test whether obj1 and obj2 are 'equal'
- (NOT obj) `boolean` Return the logical NOT of 'obj'
- (AND form *) `<object>` Logical AND of the forms 'form ...' (special form)
- (OR form *) `<object>` logical OR of the forms 'form ...' (special form)

## seq
- (LENGTH sequence) `<integer>` Return the length of 'sequence'
- (ELT sequence z) `<object>` Return element no. 'z' of 'sequence'
- (SET-ELT obj sequence z) `<object>` Set item 'z' of 'sequence' to 'obj'
- (SUBSEQ sequence z1 z2) sequence Get the portion of 'sequence' from indexes z1 to z2
- (MAP-INTO destination function seq *) sequence  Apply 'function' to the elements of 'sequence' in turn, then store the results in 'destination'

## stream
- (streamp obj) `boolean` Predicate that is true for streams
- (open-stream-p obj) `boolean` Predicate is true for open streams
- (input-stream-p obj) `boolean` Predicate that is true for input streams
- (output-stream-p obj) `boolean` Predicate that is true for output streams
- (standard-input) `<stream>` Return the standard input stream
- (standard-output) `<stream>` Return the standard output stream
- (error-output) `<stream>` Return the standard error stream
- (with-standard-input stream-form form *) `<object>`  Evaluate the forms form ... with standard-output set to the result of 'steram-form' (special form)
- (with-standard-output stream-form form *) `<object>` Evaluate the forms form ... with standard-output set to the result of 'steram-form' (special form)
- (with-error-output stream-form form *) `<object>`  Evaluate the forms form ... with standard-error set to the result of 'stream-form' (special form)
- (open-input-file filename element-class +) `<stream>` Open the file 'filename' as an input stream
- (open-output-file filename element-class +) `<stream>` Open the file 'filename' as an output stream
- (open-io-file filename element-class +) `<stream>` Open the file 'filename' for as an input/output stream
- (with-open-input-file (name file element-class +) form *) `<object>` Evaluate 'form' with standard-input redirected from 'file' and afterwards close it (special form)
- (with-open-output-file (name file element-class +) form *) `<object>` Evaluate 'form' with standard-output redirected to 'file' and afterwards close it (special form)
- (with-open-io-file (name file element-class +) form *) `<object>` Evaluate 'form' with both standard-input and standard-output streams redirected to/from 'file' and afterwards close it (special form)
- (close stream) implementation-defined Close a stream
- (create-string-input-stream string) `<stream>` Create a string input stream
- (create-string-output-stream) `<stream>` Create a string output stream
- (get-output-stream-string stream) `<string>` Return a string containing the output that was sent to a string output stream

## string
- (STRINGP obj) `boolean` Predicate that is true for strings
- (CREATE-STRING i initial-element+) `<string>` Create a string of length 'i' filled with 'initial-element'
- (STRING= string1 string2) quasi-boolean Are two strings equal?
- (STRING/= string1 string2) quasi-boolean Are two strings not equal?
- (STRING< string1 string2) quasi-boolean Is 'string1' before 'string2' in sort order?
- (STRING> string1 string2) quasi-boolean Is 'string1' after 'string2' in sort order?
- (STRING>= string1 string2) quasi-boolean Is 'string1' after or equal to 'string2' in sort order?
- (STRING<= string1 string2) quasi-boolean Is 'string1' before or equal to 'string2' in sort order?
- (CHAR-INDEX character string start-position +) `<object>` Return the position where 'character' occurs in 'string'
- (STRING-INDEX substring string start-position +) `<object>` Return the position where 'substring' occurs in 'string'
- (STRING-APPEND string *) `<string>` Concatenate the strings string ...

## symbol
- (SYMBOLP obj) `boolean` Predicate that is true for `<symbol>` objects
- (PROPERTY symbol property-name obj +) `<object>` Return a property of a symbol
- (SET-PROPERTY obj symbol property-name) `<object>` Set a property of a symbol
- (REMOVE-PROPERTY symbol property-name) `<object>` Remove a property from a symbol
- (GENSYM) `<symbol>` Create an anonymous symbol

## vector
- (BASIC-VECTOR-P obj) `boolean` Predicate that is true for `<basic-vector>` objects
- (GENERAL-VECTOR-P obj) `boolean` Predicate that is true for `<general-vector>` objects
- (CREATE-VECTOR i initial-element +) `<general-vector>`  Create a vector of length 'i', with each element initialised to 'initial-element'
- (VECTOR obj *) `<general-vector>` Create a vector from the elements obj ...

## extension of Easy-ISlisp
- (load file) T Load 'file' (extension) )
- (time form) `<object>` Show the time to evaluate 'form' (special form) (extension)
- (eval form) `<object>` Evaluate 'form' (extension)
- (compile-file file) `boolean` Compile 'file' (extension)
- (gbc) `<null>` Force garbage collection (extension)
- (quit) transfers-control Exit the ISLisp interpreter (extension)
