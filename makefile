eisl : main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o
	gcc -O3 -Wall main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o -o eisl -lm -ldl
main.o : main.c eisl.h
	gcc  -O3 -Wall -c main.c -lm -ldl
function.o : function.c eisl.h
	gcc -O3  -Wall -c function.c -lm -ldl
data.o : data.c eisl.h
	gcc -O3  -Wall -c data.c -lm -ldl
gbc.o : gbc.c eisl.h
	gcc -O3  -Wall -c gbc.c -lm -ldl
cell.o : cell.c eisl.h
	gcc -O3  -Wall -c cell.c -lm -ldl
syntax.o : syntax.c eisl.h
	gcc -O3  -Wall -c syntax.c -lm -ldl
bignum.o : bignum.c eisl.h
	gcc -O3  -Wall -c bignum.c -lm -ldl
compute.o : compute.c eisl.h
	gcc -O3  -Wall -c compute.c -lm -ldl
error.o : error.c eisl.h
	gcc -O3  -Wall -c error.c -lm -ldl
extension.o : extension.c eisl.h
	gcc -O3  -Wall -c extension.c -lm -ldl
edit.o : edit.c eisl.h
	gcc -O3 -Wall -c edit.c -lm -ldl
.PHONY: clean
clean: -lm
	rm -f eisl *.o
