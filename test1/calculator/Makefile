libmymath.a:my_add.o my_sub.o my_mul.o my_div.o
	ar -rc $@ $^
my_add.o:my_add.c
	gcc -c my_add.c
my_sub.o:my_sub.c
	gcc -c my_sub.c
my_mul.o:my_mul.c
	gcc -c my_mul.c
my_div.o:my_div.c
	gcc -c my_div.c

#libmymath.so:my_add.o my_sub.o my_mul.o my_div.o
#	gcc -shared -o $@ $^
#my_add.o:my_add.c
#	gcc -fPIC -c  my_add.c
#my_sub.o:my_sub.c
#	gcc -fPIC -c  my_sub.c
#my_mul.o:my_mul.c
#	gcc -fPIC -c  my_mul.c
#my_div.o:my_div.c
	gcc -fPIC -c  my_div.c
.PHONY:output
output:
	mkdir -p  lib/lib
	mkdir -p lib/include
	cp -rf *.h lib/include
	cp -rf *.so lib/lib
#	cp -rf *.a lib/lib
.PHONY:clean
clean:
	rm -f *.o *.so *.a
