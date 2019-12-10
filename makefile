CC := gcc
eisl : main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o
	$(CC) -O3 -Wall main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o -o eisl -lm -ldl
main.o : main.c eisl.h
	$(CC)  -O3 -Wall -c main.c -ldl
function.o : function.c -lm eisl.h
	$(CC) -O3  -Wall -c function.c -ldl
data.o : data.c eisl.h
	$(CC) -O3  -Wall -c data.c -ldl
gbc.o : gbc.c eisl.h
	$(CC) -O3  -Wall -c gbc.c -ldl
cell.o : cell.c eisl.h
	$(CC) -O3  -Wall -c cell.c -ldl
syntax.o : syntax.c eisl.h
	$(CC) -O3  -Wall -c syntax.c -ldl
bignum.o : bignum.c eisl.h
	$(CC) -O3  -Wall -c bignum.c -ldl
compute.o : compute.c  eisl.h
	$(CC) -O3  -Wall -c compute.c -ldl
error.o : error.c eisl.h
	$(CC) -O3  -Wall -c error.c -ldl
extension.o : extension.c eisl.h
	$(CC) -O3  -Wall -c extension.c -ldl
edit.o : edit.c eisl.h
	$(CC) -O3 -Wall -c edit.c  -ldl
.PHONY: clean
clean: -lm
	rm -f eisl *.o
