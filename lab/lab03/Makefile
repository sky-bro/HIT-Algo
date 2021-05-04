.PHONY: all clean
CXXFLAGS = -g -Wall -std=c++11 -lglpk
SOURCES  = main.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BINARY   = main

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

main.o: Sampler.hpp LPRoundingSetCover.hpp

clean:
	$(RM) $(BINARY) $(OBJECTS)
