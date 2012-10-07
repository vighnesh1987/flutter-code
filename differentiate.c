#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define RANGE 50

void parseArguments(int argc, char* argv[], int* wptr, int* hptr);
unsigned char** generateRandomMatrix(int width, int height);
void printMatrix( unsigned char** matrix, int width, int height);

int main(int argc, char* argv[]) {

  int width, height;
  parseArguments(argc, argv, &width, &height);
  unsigned char** matrix = generateRandomMatrix(width, height);
  printMatrix(matrix, width, height);

  return 0;
}

void parseArguments(int argc, char* argv[], int* wptr, int* hptr) {
  if (argc != 3) {
    printf("Usage: Invoke as below\n  %s <width> <height>\n", argv[0]);
    exit(1);
  }
  *wptr = atoi(argv[1]);
  *hptr = atoi(argv[2]);
}

unsigned char** generateRandomMatrix(int width, int height) {
  srand ( time(NULL) );
  unsigned char** matrix = malloc(sizeof(unsigned char*)*width);
  for (int x = 0; x < width; x++) {
    matrix[x] = malloc(sizeof(unsigned char)*height);
    for (int y = 0; y < height; y++) {
      matrix[x][y] = rand() % RANGE + 1;
    }
  }
  return matrix;
}

void printMatrix( unsigned char** matrix, int width, int height) {
  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++) {
      printf("%5u ", matrix[x][y]);
    }
    printf("\n");
  }
}


