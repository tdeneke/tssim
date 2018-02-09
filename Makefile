CC=gcc
CFLAGS=-I.
DEPS = tssim.h
OBJ = tssimtest.o tssim.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tssimtest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
