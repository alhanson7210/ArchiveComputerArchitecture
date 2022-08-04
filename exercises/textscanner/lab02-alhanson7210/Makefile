PROG = lab02

OBJS = scan.o

CC = gcc

CFLAGS = -c -g -Wall

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

$(PROG) : $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -rf $(PROG) $(OBJS)

all : $(PROG)

test:
	clear
	make
	cat simple.ntc
	./$(PROG) simple.ntc
	cat vars.ntc
	./$(PROG) vars.ntc
	cat funcs.ntc
	./$(PROG) funcs.ntc
	make clean

check:
	clear
	make
	cat test.ntc
	./$(PROG) test.ntc
	make clean
