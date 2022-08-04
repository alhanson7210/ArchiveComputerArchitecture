PROG = lab04
PROGS = $(PROG) ntcalc
OBJS = scan.o parse.o eval.o ntcalc.o
CC = gcc
CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	$(CC) ${CFLAGS} -c -o $@ $< -lm

%.o : %.s
	as -o $@ $< -lm

all : ${PROGS}

ntcalc : ntcalc.h $(OBJS)
	$(CC) ${CFLAGS} -o $(PROG) $(OBJS) -lm

lab04 : ntcalc

check :
	make
	./lab04 -e "1 + 2"
	./lab04 -e "(1 + 2) * 3"
	./lab04 -e "4 * (10 / 5)"
	./lab04 -e "(2 * (3 + (1 + 1)))"
	./lab04 -e "-4 + 3"
	./lab04 -e "-4 + -4"
	./lab04 -e "~(0 - 1)" -b 2
	./lab04 -e "2 * (1 + (8 << 1))" -b 2
	./$(PROG) -e "0b101 + 0b101" -b 2
	make clean
	
clean :
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM *.actual *.score
