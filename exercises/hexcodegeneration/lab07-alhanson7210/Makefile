PROG = lab07
OBJS = armasm.o scan.o parse.o codegen.o
HEADERS = armasm.h
CFLAGS = -g

%.o: %.c
	gcc -c ${CFLAGS} -o $@ $<

all : ${PROG}

${PROG} : ${OBJS} ${HEADERS}
	gcc ${CFLAGS} -o $@ ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS} *~ *.dSYM *.o *.hex *.score *.actual

test :
	cd ../../../maketest && \
	make -eks DIR=~/Desktop/cs315/labs/lab07/lab07-alhanson7210 && \
	cd ~/Desktop/cs315/labs/lab07/lab07-alhanson7210 && \
	make clean && \
	git status && \
	ls
