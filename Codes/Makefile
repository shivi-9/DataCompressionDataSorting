CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Helper.cpp Delta.cpp Huffman.cpp LZ77.cpp RLE.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main
ARGS=/home/grad1/shivi09/DataCompressionDataSorting/Workload-10%/Workload40KB/0_0.txt /home/grad1/shivi09/DataCompressionDataSorting/output.txt 4 

all: $(SOURCES) $(EXECUTABLE) run

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(EXECUTABLE) $(ARGS)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
