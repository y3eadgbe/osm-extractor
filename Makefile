.PHONY: clean

TARGET = extract_vertex extract_edge
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall
OBJS = convert.o

all: $(TARGET)

clean:
	-@rm $(TARGET) -rf *.o
