myshell:myshell.c myerr.h myerr.c
	gcc -o myshell myshell.c myerr.c
clean:
	rm myshell
