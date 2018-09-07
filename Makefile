CXX = g++
# CXX = clang++

CXXFLAGS = -pipe -g
INCPATH =
LIBPATH =
LIBRARY = -lopencv_core

TARGET = test_rotatedrect

.PHONY = test

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $^

$(TARGET): % : %.o
	$(CXX) $(CXXFLAGS) $(LIBPATH) $^ $(LIBRARY) -o $*

test: all
	./test_rotatedrect
