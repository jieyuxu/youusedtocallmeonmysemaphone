make: control.c writer.c
	gcc -g -o control.out control.c
	gcc -g -o writer.out writer.c

clean: 
	rm -rf *dSYM