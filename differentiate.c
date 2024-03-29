#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#define RANGE (UCHAR_MAX + 1)
#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC/1000)

typedef struct {
  int width;
  int height;
  unsigned char** data;
} Matrix;

void parseArguments( int argc, char* argv[], Matrix* matrix );
void initMatrix( Matrix* matrix );
void fillRandomData( Matrix* matrix );
int** differentiateX( Matrix* matrix );
int** differentiateY( Matrix* matrix );
static inline int max(int** arr, int width, int height);
static inline int min(int** arr, int width, int height);

void printMatrix( Matrix* matrix );
void printArray( int** arr, int width, int height );

int main(int argc, char* argv[]) {
  Matrix matrix;
  /*Read in height and width*/
  parseArguments(argc, argv, &matrix);
  /*Allocate matrix on the heap*/
  initMatrix(&matrix);
  /*Fill with random unsigned chars*/
  fillRandomData(&matrix);
  /*Start timer*/
  double start,mid1, mid2, end;
  start = (double) clock();
  /*Differentiate*/
  int** dx = differentiateX(&matrix);
  mid1 = (double) clock();
  int** dy = differentiateY(&matrix);
  mid2 = (double) clock();
  /*Compute min and max*/
  printf("The max and min for dx are: %d and %d\n", max(dx, matrix.width, matrix.height), min(dx, matrix.width, matrix.height));
  printf("The max and min for dy are: %d and %d\n", max(dy, matrix.width, matrix.height), min(dy, matrix.width, matrix.height));
  /*End timer*/
  end = (double) clock();
  printf("Total time taken: %.4f msec\n", (end-start) / CLOCKS_PER_MSEC);
  printf("dx takes %f, dy takes %f msec\n", (mid1 - start) / CLOCKS_PER_MSEC, (mid2 - mid1) / CLOCKS_PER_MSEC);
  /*Print*/
  /*printMatrix(&matrix);*/
  /*printArray(dx, matrix.width, matrix.height);*/
  /*printArray(dy, matrix.width, matrix.height);*/
  /*Free everything*/
  for (int x = 0; x < matrix.width; x++) {
    free(matrix.data[x]);
    free(dx[x]);
    free(dy[x]);
  }
  free(matrix.data);
  free(dx);
  free(dy);
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
      matrix->data[x][y] = rand() % RANGE;
    }
  }
}

int** differentiateX(Matrix* matrix) {
  /*Initialize*/
  int** dx = malloc(sizeof(int*) * (matrix->width));
  for (int x = 0; x < matrix->width; x++) {
    dx[x] = malloc(sizeof(int) * (matrix->height) );
  }
  unsigned char** data = matrix->data;
  int h = matrix->height, w = matrix->width;
  /*Convolve with [-1, 0, 1]*/
  for (int y = 0; y < matrix->height; y++) {
    dx[0][y] = data[1][y];
    dx[w-1][y] = - data[w-2][y];
  }
  for (int x = 1; x < w - 1; x++) {
    for (int y = 0; y < h; y++) {
      dx[x][y] = (int) data[x+1][y] - data[x-1][y];
    }
  }
  return dx;
}

int** differentiateY(Matrix* matrix) {
  int** dy = malloc(sizeof(int*) * (matrix->height));
  for (int y = 0; y < matrix->height; y++) {
    dy[y] = malloc(sizeof(int) * (matrix->width ) );
  }
  unsigned char** data = matrix->data;
  int h = matrix->height, w = matrix->width;
  for (int x = 0; x < w; x++) {
    dy[x][0] = data[x][1];
    for (int y = 1; y < h - 1; y++) {
      dy[x][y] = (int) data[x][y+1] - data[x][y-1];
    }
    dy[x][h - 1] = - data[x][h - 2];
  }
  return dy;
}

static inline int max(int** arr, int width, int height) {
  int max = - UCHAR_MAX;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (arr[x][y] > max) max = arr[x][y];
    }
  }
  return max;
}

static inline int min(int** arr, int width, int height) {
  int min =  UCHAR_MAX;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (arr[x][y] < min) min = arr[x][y];
    }
  }
  return min;
}

void printMatrix( Matrix* matrix) {
  printf("\n");
  for (int y = matrix->height - 1; y >= 0; y--) {
    for (int x = 0; x < matrix->width; x++) {
      printf("%5u ", matrix->data[x][y]);
    }
    printf("\n");
  }
}

void printArray( int** arr, int width, int height ) {
  printf("\n");
  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++) {
      printf("%5d ", arr[x][y]);
    }
    printf("\n");
  }
}

