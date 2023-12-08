CC=gcc
CFLAGS=-I. -Ispatialindex/include
LDFLAGS=-lgsl -lgslcblas -lm  -Lspatialindex/bin -lspatialindex_c
DEPS = tssim.h
OBJ = tssimtest.o tssim.o 

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

tssimtest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
