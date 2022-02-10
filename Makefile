CFLAGS=-g

wc: wc.c
	gcc -o wc wc.c -std=gnu11 -g -Werror -Wall

clean:
	rm wc

