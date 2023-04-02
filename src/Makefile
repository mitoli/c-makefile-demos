CXX = g++
CXXFLAGS = -O3 -std=c++17 -pthread
WARNING = -Wall -Wextra

TARGETS = $(patsubst %.cc, %, $(wildcard *.cc))

all: $(TARGETS)

%: %.cc Makefile
	$(CXX) -MMD -MP $(CXXFLAGS) $(WARNING) $@.cc -o $@

.PHONY: all clean

clean:
	rm -f $(TARGETS) *.o *.d
