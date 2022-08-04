PROG = project03
#SORT = sort2
OBJS = $(PROG).o reverse_c.o reverse_s.o search_c.o search_s.o sort_c.o sort_s.o #sort_s2.o sort_c2.o
AS=~/Desktop/cs315/projects/project04/project04-alhanson7210/project04
# AS=as

%.o: %.c
	gcc -c -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

$(PROG): $(OBJS)
	gcc -o $(PROG) $(OBJS)

clean :
	rm -rf $(PROG) $(OBJS) *~ *.actual *.score

test :
	cd ../../../maketest && \
	git pull && \
	make -eks DIR=~/Desktop/cs315/projects/project03/project03-alhanson7210 && \
	cd ~/Desktop/cs315/projects/project03/project03-alhanson7210 && \
	make clean && \
	ls

isa :
	cd ~/Desktop/cs315/projects/project04/project04-alhanson7210 && \
	make && \
	cd ~/Desktop/cs315/projects/project03/project03-alhanson7210
	AS=as
	echo "using as below"
	make clean && \
	make && \
	./project03 reverse "foobar" && \
	./project03 sort 87 53 63 23 204 8 42 0 && \
	./project03 search 4 1 2 4 8 16 32 64 128
	AS=~/Desktop/cs315/projects/project04/project04-alhanson7210/project04
	echo "using project04 assembler"
	make clean && \
	make && \
	./project03 reverse "foobar" && \
	./project03 sort 87 53 63 23 204 8 42 0 && \
	./project03 search 4 1 2 4 8 16 32 64 128
	make clean
#sort2 :
#	make && \
#	./$(PROG) $(SORT) 4 7 5 9 3 2 4 && \
#	make clean 
