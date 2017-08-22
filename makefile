TARGET := ../Library/libindex.so
SRCS := $(wildcard *.c)

CFLAG := -I ../Include

${TARGET} : ${SRCS}
	gcc -fPIC -shared ${CFLAG} $^ -o $@

clean:
	rm ${TARGET}
