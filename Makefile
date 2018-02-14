CC=gcc
CFLAGS=-I.
LDFLAGS=-lgsl -lgslcblas -lm
DEPS = tssim.h
OBJ = tssimtest.o tssim.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tssimtest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
