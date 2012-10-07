CC=c99
CFLAGS=-O3
EXECUTABLE=differentiate
SOURCE=differentiate.c

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $@

.PHONY: clean
clean:
	rm $(EXECUTABLE)

