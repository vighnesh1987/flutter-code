CC=g++
CFLAGS=-O3
EXECUTABLE=differentiate
SOURCE=differentiate.cpp

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $@

.PHONY: clean
clean:
	rm $(EXECUTABLE)

