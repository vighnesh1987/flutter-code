#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define RANGE 50

typedef struct {
  int width;
  int height;
  unsigned char** data;
} Matrix;

void parseArguments(int argc, char* argv[], Matrix* matrix);
void initMatrix(Matrix* matrix);
void fillRandomData(Matrix* matrix); 
void printMatrix(Matrix* matrix); 

int main(int argc, char* argv[]) {

  int width, height;
  Matrix matrix;
  parseArguments(argc, argv, &matrix);
  initMatrix(&matrix);
  fillRandomData(&matrix);
  printMatrix(&matrix);

  /*unsigned char** dx = differentiateX(&matrix);*/
  return 0;
}

void parseArguments(int argc, char* argv[], Matrix* matrix) {
  if (argc != 3) {
    printf("Usage: Invoke as below\n  %s <width> <height>\n", argv[0]);
    exit(1);
  }
  matrix->width = atoi(argv[1]);
  matrix->height = atoi(argv[2]);
}

void initMatrix(Matrix* matrix) {
  matrix->data = malloc(sizeof(unsigned char*) * (matrix->width) );
  for (int x = 0; x < matrix->width; x++) {
    matrix->data[x] = malloc(sizeof(unsigned char) * (matrix->height) );
  }
}

void fillRandomData(Matrix* matrix) {
  srand ( time(NULL) );
  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      matrix->data[x][y] = rand() % RANGE + 1;
    }
  }
}

void printMatrix( Matrix* matrix) {
  for (int y = matrix->height - 1; y >= 0; y--) {
    for (int x = 0; x < matrix->width; x++) {
      printf("%5u ", matrix->data[x][y]);
    }
    printf("\n");
  }
}

unsigned char** differentiateX(unsigned char** matrix, int width, int height) {

}

