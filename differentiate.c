#include<stdio.h>
#include<stdlib.h>

void parseArguments(int argc, char* argv[], int* wptr, int* hptr);

int main(int argc, char* argv[]) {

  int width, height;
  parseArguments(argc, argv, &width, &height);
  printf("w: %d, h: %d, %d\n", width, height, width*height);

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

