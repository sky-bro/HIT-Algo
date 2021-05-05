.PHONY: all clean
CXXFLAGS = -g -Wall -std=c++14 #-fsanitize=address,undefined
SOURCES  = main.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BINARY   = main

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

main.o: BFPRT.hpp lazyselect.hpp mrandom.hpp

clean:
	$(RM) $(BINARY) $(OBJECTS)
