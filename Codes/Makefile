CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lsnappy
SOURCES=main.cpp Snappy.cpp Helper.cpp Delta.cpp Huffman.cpp LZ77.cpp RLE.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main
ARGS=<path to the workload> <path where you want to save the encoded file> <choice of encoding algorithm> 

all: $(SOURCES) $(EXECUTABLE) run

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(EXECUTABLE) $(ARGS)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)