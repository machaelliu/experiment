.PHONE: all clean

CFLAGS= -g -Wall -I.
LDFLAGS= -lpthread


all: main 

main: main.o pthread_once.o pthread_key.o
	gcc -o $@ $(LDFLAGS) $^

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $^

clean:
	-rm -f *.o main


