CC=gcc
CFLAGS=-I.
DEPS = math_functions.h
OBJ = neural_network_xor_training.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

neural_network_xor_training: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

.PHONY: clean

clean:
	rm -f *.o neural_network_xor_training
