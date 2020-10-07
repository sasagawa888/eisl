all: eisl edlis
CC := gcc

eisl : main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o 
	$(CC) -O3 -Wall main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o -o eisl -lm -ldl 

raspi: main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o 
	$(CC) -O3 -Wall main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o -o eisl -lm -ldl -lwiringPi


main.o : main.c eisl.h
	$(CC)  -O3 -Wall -c main.c
function.o : function.c -lm eisl.h
	$(CC) -O3  -Wall -c function.c
data.o : data.c eisl.h
	$(CC) -O3  -Wall -c data.c
gbc.o : gbc.c eisl.h
	$(CC) -O3  -Wall -c gbc.c
cell.o : cell.c eisl.h
	$(CC) -O3  -Wall -c cell.c
syntax.o : syntax.c eisl.h
	$(CC) -O3  -Wall -c syntax.c
bignum.o : bignum.c eisl.h
	$(CC) -O3  -Wall -c bignum.c
compute.o : compute.c  eisl.h
	$(CC) -O3  -Wall -c compute.c
error.o : error.c eisl.h
	$(CC) -O3  -Wall -c error.c
extension.o : extension.c eisl.h
	$(CC) -O3  -Wall -c extension.c
edit.o : edit.c eisl.h
	$(CC) -O3 -Wall -c edit.c
.PHONY: clean
clean: -lm
	rm -f *.o
	rm eisl
	rm edlis


edlis : edlis.o
	$(CC) -O3 -Wall edlis.o -o edlis
edlis.o : edlis.c edlis.h
	$(CC)  -O3 -Wall -c edlis.c