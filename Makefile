# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -O3 -g
LIBS = `pkg-config --cflags sdl2 SDL2_image` -lm
LDFLAGS = `pkg-config --libs sdl2 SDL2_image`

# Source files
SOURCES = main.c \
    Graphics/GridDetection/hough_transform.c \
    Graphics/GridDetection/local_threshold.c \
    Graphics/GridDetection/sobel.c \
    Graphics/Traitement/contrast.c \
    Graphics/Traitement/grayscale.c \
    Graphics/Traitement/noise_reduction.c \
    Graphics/utils/lines.c \
    Graphics/utils/linked_list.c \
    Graphics/utils/splitting.c \
    Graphics/utils/utils.c

# Object files (automatically generated from source files)
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXECUTABLE = main_program
DIRNAME = output
DIRNAME_2 = output/steps
DIRNAME_3 = output/tiles

all: $(EXECUTABLE) $(DIRNAME) $(DIRNAME_2) $(DIRNAME_3)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBS) $(LDFLAGS)

$(DIRNAME):
	mkdir -p $(DIRNAME)

$(DIRNAME_2):
	mkdir -p $(DIRNAME_2)

$(DIRNAME_3):
	mkdir -p $(DIRNAME_3)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -r output
