
CC=$(CROSS_COMPILE)gcc

all: writer

writer: writer.c
	$(CC) -o $@ writer.c

.PHONY:	clean

clean:
	rm -f *~ writer
