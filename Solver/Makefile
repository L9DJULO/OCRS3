# Makefile

CC=gcc -fsanitize=address
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=

SRC= solver.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: solver

-include ${DEP}

solver: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} solver

# END
