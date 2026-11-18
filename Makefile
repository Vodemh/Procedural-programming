CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
SOURCES := $(wildcard *.cpp)
TARGET := KR

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) tasks.h
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) KR_asan
