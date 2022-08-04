PROG = project02
OBJS = scan.o parse.o eval.o ntcalc.o conv.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c ntcalc.h
	gcc ${CFLAGS} -c -o $@ $<

${PROG} : ${OBJS}
	gcc ${CFLAGS} -o $@ ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS} *~ *.dSYM *.actual *.score

check :
	cd ../../../maketest && make -eks DIR=~/Desktop/cs315/projects/project02/project02-alhanson7210 && cd ~/Desktop/cs315/projects/project02/project02-alhanson7210 && make clean
