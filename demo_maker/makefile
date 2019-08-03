PROGNAME := demo_maker
OUTDIR := build/objs
TARGET := $(PROGNAME)
LIBDIR := ..
INCLUDE := -I$(LIBDIR) `pkg-config --cflags opencv4`
SRCS := $(wildcard *.cpp) $(wildcard $(LIBDIR)/action.cpp)
LIBS := -lsudare `pkg-config --libs opencv4`
OBJS := $(addprefix $(OUTDIR)/,$(patsubst %.cpp,%.o,$(SRCS)))

CXX := g++
CXXFLAGS := -Wall -fPIC -std=c++17 -O2

UNAME := ${shell uname}
ifeq ($(UNAME), Linux)
CXXFLAGS := $(CXXFLAGS) -DENABLE_SPI
endif

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

$(OUTDIR)/%.o:%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OPT) -o $@ -c $<

clean:
	rm -rf build $(TARGET)
