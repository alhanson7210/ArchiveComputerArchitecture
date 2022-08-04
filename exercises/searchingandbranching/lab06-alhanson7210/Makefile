PROGS = find_max_main max3_main fib_rec_main lab06

OBJS = find_max_c.o find_max_s.o fib_rec_c.o fib_rec_s.o \
       max3_c.o max3_s.o

CFLAGS = -g

%.o : %.s
	as ${CFLAGS} -o $@ $^

all : ${PROGS}

find_max_main : find_max_main.c find_max_c.o find_max_s.o
	gcc ${CFLAGS} -o $@ $^

fib_rec_main : fib_rec_main.c fib_rec_c.o fib_rec_s.o
	gcc ${CFLAGS} -o $@ $^

max3_main : max3_main.c max3_c.o max3_s.o
	gcc ${CFLAGS} -o $@ $^	

clean :
	rm -rf ${PROGS} ${OBJS} *~

check :
	cd ../../../maketest && \
	git pull && \
	make -eks DIR=~/Desktop/cs315/labs/lab06/lab06-alhanson7210 && \
	cd ~/Desktop/cs315/labs/lab06/lab06-alhanson7210 && \
	make clean && \
	rm *.actual *.score && \
	ls
