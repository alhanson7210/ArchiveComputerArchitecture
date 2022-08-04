PROG = lab03
PROGS = $(PROG) ntcalc
OBJS = scan.o parse.o ntcalc.o
CC = gcc
CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	$(CC) ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<

all : ${PROGS}

ntcalc : ntcalc.h $(OBJS)
	$(CC) ${CFLAGS} -o $(PROG) $(OBJS)

lab03 : ntcalc

check :
	make
	./lab03 -e "1 + 2"
	./lab03 -e "(1 + 2) * 3"
	./lab03 -e "4 * (10 / 5)"
	./lab03 -e "(2 * (3 + (1 + 1)))"
	./lab03 -e "-4 + 3"
	./lab03 -e "-4 + -4"
	make clean
	
clean :
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM
