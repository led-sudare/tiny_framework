CXX			:= g++
CXXFLAGS	:= -Wall -std=c++11

TARGET		:= tiny_framework
PROJ_ROOT	:= $(realpath .)
INCLUDES	:= `pkg-config --cflags opencv4`
SRCS		:= $(wildcard *.cpp)
LIBS		:= -lsudare -pthread `pkg-config --libs opencv4`
OBJS		:= $(SRCS:.cpp=.o)

### Rules ######################################################################

.PHONY: all
all: $(TARGET)

.PHONY: make
make: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) *.o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
