#include <iostream>
#include <sstream>
using namespace std;

void parseArguments(int argc, char* argv[], int* wptr, int* hptr);

int main(int argc, char* argv[]) {
  int  width, height;
  parseArguments(argc, argv, &width, &height);
  cout << width << height << " "<< height*width << endl;
  return 0;
}

void parseArguments(int argc, char* argv[], int* wptr, int* hptr) {
  if (argc != 3) {
    cout << "Usage: Invoke as below\n" << argv[0] << " <width> <height>" << endl;
    exit(1);
  }
  stringstream sw(argv[1]); sw >> *wptr;
  stringstream sh(argv[2]); sh >> *hptr;
}


