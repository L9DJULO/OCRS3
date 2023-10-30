#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graphics/utils/lines.h"
#include "Graphics/utils/linked_list.h"
#include "Graphics/utils/utils.h"

int main(int argc, char **argv)
{
  // Checking the number of arguments for correct usage
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s image\n", argv[0]);
    return 1;
  }

  // Load the input image
  SDL_Surface *surface = IMG_Load(argv[1]);

  // Convert the image format to 32bits
  surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
  SDL_Surface *copy = copySurface(surface);

  grayscale(copy);
  saveSurface(copy, "output/steps/1-grayscale.jpg");

  contrast(copy);
  saveSurface(copy, "output/steps/2-contrast.jpg");

  denoise(copy);
  saveSurface(copy, "output/steps/3-denoise.jpg");

  localThreshold(copy);
  saveSurface(copy, "output/steps/4-local_threshold.jpg");

  SDL_Surface *surfaceToSplit = copySurface(copy);
  invert(surfaceToSplit);

  sobelEdgeDetection(copy);
  saveSurface(copy, "output/steps/5-sobel.jpg");

  List *lines = initList();
  houghTransform(copy, lines);
  lineCleaning(lines);

  SDL_Color black = {0, 0, 0, 255};
  drawLines(surfaceToSplit, lines, black, 15);

  SDL_Color color = {255, 0, 0, 255};
  SDL_Surface *surfacelines = copySurface(copy);
  drawLines(surfacelines, lines->next, color, 1);
  saveSurface(surfacelines, "output/steps/6-lines.jpg");

  double angle = getRotationAngle(lines);

  saveSurface(copy, "output/steps/8-rotate.jpg");

  List *squares = squareDetection(lines, surface->w, surface->h);
  squares = squareFilter(squares);

  SDL_Surface *drawSquareSurface = copySurface(copy);
  drawSquares(drawSquareSurface, squares, color);
  saveSurface(drawSquareSurface, "output/steps/9-draw_squares.jpg");

  SudokuCell sudokuCell = selectSudoku(drawSquareSurface, squares);
  saveSurface(drawSquareSurface, "output/steps/10-draw_sudoku.jpg");

  int distX = sudokuCell.xTopRight - sudokuCell.xBottomLeft;
  int distY = sudokuCell.yTopRight - sudokuCell.yBottomLeft;
  splitImage(surfaceToSplit, sudokuCell.xBottomLeft, sudokuCell.yBottomLeft, distX, distY);

  // Clean up and free surfaces
  SDL_FreeSurface(surface);
  SDL_FreeSurface(copy);
  SDL_FreeSurface(surfaceToSplit);
  SDL_FreeSurface(surfacelines);
  SDL_FreeSurface(drawSquareSurface);

  return 0;
}
