.PHONY:all
all:test1 test2
test1:test1.c
	gcc -o $@ $^
test2:test2.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f test1 test2
