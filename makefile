CXX = g++
CXXFLAGS = -c -g -Wall -std=c++17

SRCS = main.cpp Queue.h graphClass_2.h
OBJS = $(SRCS:.cpp=.o)

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)