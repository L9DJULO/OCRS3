CC = gcc
CFLAGS = -fsanitize=address -Wall -Wextra -std=c99 -O2 -MMD -D_XOPEN_SOURCE=500
LDFLAGS = -fsanitize=address -lm
DEPS = math_functions.h
OBJ = NN_xor.o math_functions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

NN_xor: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(OBJ) NN_xor *.d
