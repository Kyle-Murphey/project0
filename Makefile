all: project0.c
	gcc project0.c -o project0

zip:
	zip project0.zip *.c Makefile README.txt

clean:
	rm -f project0 *.o
