CC=gcc
CFLAGS=-I. -I/l/tewodrod/spike/tssim/spike/libspatialindex/include
LDFLAGS=-lgsl -lgslcblas -lm  -L/l/tewodrod/spike/tssim/spike/libspatialindex/build/bin/ -lspatialindex_c
DEPS = tssim.h
OBJ = tssimtest.o tssim.o 

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

tssimtest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
