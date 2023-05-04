CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Delta.cpp Huffman.cpp LZ77.cpp Helper.cpp RLE.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=compression_tool
ARGS=/home/grad1/shivi09/DataCompressionDataSorting/Workload/Workload10MB/100_100.txt /home/grad1/shivi09/DataCompressionDataSorting/Workload/output.txt 4

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)