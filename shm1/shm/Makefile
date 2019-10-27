ser=server#使用变量，等号右边是变量内容
cli=client
cc=gcc
.PHONY:all
all:$(ser) $(cli)#表示一次生成的可执行程序是ser和cli
$(ser):server.c
	$(cc) -o $@ $^
$(cli):client.c
	$(cc) -o $@ $^
.PHONY:clean
clean:
	rm -f $(ser) $(cli)
