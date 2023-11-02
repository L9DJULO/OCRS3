#include <stdio.h>
#include <stdlib.h>

int solve(int grid[9][9]);
int isValid(int grid[9][9], int row, int col, int num);
void printGrid(int grid[9][9], FILE *file);
int find_empty_cell(int[9][9], int *, int *);

void printGrid(int grid[9][9], FILE *file)
{
  for (int i = 0; i < 9; i++)
  {
    if (i % 3 == 0 && i != 0)
    {
      fprintf(file, "---------------------\n");
    }
    for (int j = 0; j < 9; j++)
    {
      if (j % 3 == 0 && j != 0)
      {
        fprintf(file, "| ");
      }
      if (grid[i][j] < 0)
      {
        fprintf(file, "0 ");
      }
      else
      {
        fprintf(file, "%d ", grid[i][j]);
      }
    }
    fprintf(file, "\n");
  }
}

/*****************************************************************/


int main(int argc, char *argv[])
{
    char gridchar[9][9];
    int grid[9][9];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
      fprintf(stderr, "Error opening file.\n");
      return 1;
    }

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
          fscanf(file, " %c", &gridchar[i][j]);

          if (gridchar[i][j] == '.')
          {
            grid[i][j] = 0;
          }
          else
          {
            grid[i][j] = gridchar[i][j] - '0';
          }
        }
    }

    fclose(file);

    printf("Initial Sudoku Grid:\n");
    printGrid(grid, stdout);

    if (solve(grid))
    {
        printf("\n\nSolution:\n");

        char choice;
        printf("Do you want to print the solution in the console? (y/n): ");
        scanf(" %c", &choice);

        if(choice == 'y' || choice == 'Y')
            printGrid(grid, stdout);

        char result_filename[256];
        sprintf(result_filename, "%s.result", argv[1]);

        FILE *result_file = fopen(result_filename, "w");

        if(result_file == NULL)
        {
            fprintf(stderr, "Error creating result file.\n");
            return 1;
        }

        printGrid(grid, result_file);
        
        fclose(result_file);
        
        printf("\nSolution written to file: %s\n", result_filename);
        
    }
    else
    {
        printf("\n\nNO SOLUTION FOUND\n\n");
    }

    return 0;
}
/*****************************************************************/
int isValid(int grid[9][9], int row, int column, int guess)
{
  int corner_x = row / 3 * 3;
  int corner_y = column / 3 * 3;

  for (int x = 0; x < 9; ++x)
  {
    if (grid[row][x] == guess)
      return 0;
    if (grid[x][column] == guess)
      return 0;
    if (grid[corner_x + (x % 3)][corner_y + (x / 3)] == guess)
      return 0;
  }
  return 1;
}

/*****************************************************************/
int find_empty_cell(int grid[9][9], int *row, int *column)
{
  for (int x = 0; x < 9; x++)
  {
    for (int y = 0; y < 9; y++)
    {
      if (!grid[x][y])
      {
        *row = x;
        *column = y;

        return 1;
      }
    }
  }
  return 0;
}

/*****************************************************************/
int solve(int grid[9][9])
{
  int row;
  int column;

  if (!find_empty_cell(grid, &row, &column))
    return 1;

  for (int guess = 1; guess < 10; guess++)
  {
    if (isValid(grid, row, column, guess))
    {
      grid[row][column] = guess;

      if (solve(grid))
        return 1;
      grid[row][column] = 0;
    }
  }
  return 0;
}