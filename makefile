make: control.c writer.c
	gcc -g -o drake.out control.c writer.c

clean: 
	rm -rf *dSYM