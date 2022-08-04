PROG = project04
OBJS = armasm.o scan.o parse.o codegen.o
HEADERS = armasm.h
CFLAGS = -g
ELF = elf/elf.a

%.o: %.c
	gcc -c ${CFLAGS} -o $@ $<

all : ${PROG}

$(ELF):
	make -C elf

${PROG} : ${OBJS} ${HEADERS} ${ELF}
	gcc ${CFLAGS} -o $@ ${OBJS} ${ELF}
	
clean :
	make -C elf clean
	rm -rf ${PROG} ${OBJS} *~ *.dSYM *.o *.hex *.actual *.score

test :
	cd ../../../maketest && \
	make -eks DIR=~/Desktop/cs315/projects/project04/project04-alhanson7210 && \
	cd ~/Desktop/cs315/projects/project04/project04-alhanson7210 && \
	make clean
