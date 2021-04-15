# CSV

read csv format data from file and return list of data.


# Usage 

(import "csv")

# function

### (read-csv stream)
read from stream and one line data as list.

### (parse-csv stream)
read from stream and all lines as nested list.

### example

```
> (load "tests/csv-test.lsp")
T
> (test)
("Month" "Average" "2005" "2006" "2007" "2008" "2009" "2010" "2011" "2012" "2013" "2014" "2015")
(("Month" "Average" "2005" "2006" "2007" "2008" "2009" "2010" "2011" "2012" "2013" "2014" "2015") ("May" 0.1 0 0 1 1 0 0 0 2 0 0 0) ("Jun" 0.5 2 1 1 0 0 1 1 2 2 0 1) ("Jul" 0.7 5 1 1 2 0 1 3 0 2 2 1) ("Aug" 2.3 6 3 2 4 4 4 7 8 2 2 3) ("Sep" 3.5 6 4 7 4 2 8 5 2 5 2 5) ("Oct" 2.0 8 0 1 3 2 5 1 5 2 3 0) ("Nov" 0.5 3 0 0 1 1 0 1 0 1 0 1) ("Dec" 0.0 1 0 1 0 0 0 0 0 0 0 1) NIL)
<undef>
> 

```