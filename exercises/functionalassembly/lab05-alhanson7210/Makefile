PROGS = add4_main quadratic_main min_main lab05

OBJS = add4_c.o add4_s.o quadratic_c.o quadratic_s.o min_c.o min_s.o

CFLAGS = -g

all : ${PROGS}

add4_main : add4_main.c add4_c.o add4_s.o
	gcc ${CFLAGS} -o $@ $^

quadratic_main : quadratic_main.c quadratic_c.o quadratic_s.o
	gcc ${CFLAGS} -o $@ $^

min_main : min_main.c min_c.o min_s.o
	gcc ${CFLAGS} -o $@ $^

check :
	cd ../../../maketest/ \
	&& make -eks DIR=~/Desktop/cs315/labs/lab05/lab05-alhanson7210 \
	&& cd ~/Desktop/cs315/labs/lab05/lab05-alhanson7210 \
	&& make clean && rm *.score *.actual

clean :
	rm -rf ${PROGS} ${OBJS} *~
