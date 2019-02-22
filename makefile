eisl : main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o
	gcc -O3 -Wno-pointer-to-int-cast -Wall main.o function.o data.o gbc.o cell.o syntax.o bignum.o compute.o error.o extension.o edit.o -o eisl -lm -ldl
main.o : main.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c main.c -lm
function.o : function.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c function.c -lm -ldl
data.o : data.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c data.c -lm
gbc.o : gbc.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c gbc.c -lm
cell.o : cell.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c cell.c -lm
syntax.o : syntax.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c syntax.c -lm
bignum.o : bignum.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c bignum.c -lm
compute.o : compute.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c compute.c -lm
error.o : error.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c error.c -lm
extension.o : extension.c eisl.h
	gcc -O3  -Wno-pointer-to-int-cast -Wall -c extension.c -lm
edit.o : edit.c eisl.h
	gcc -O3 -Wno-pointer-to-int-cast -Wall -c edit.c -lm
.PHONY: clean
clean: -lm
	rm -f eisl *.o
