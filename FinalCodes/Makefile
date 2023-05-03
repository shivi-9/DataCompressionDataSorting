CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Delta.cpp Huffman.cpp LZ77.cpp RLE.cpp Helper.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=compression_tool
ARGS=./Workload/Workload10MB/100_1.txt output.txt 1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)