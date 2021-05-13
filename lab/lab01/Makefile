.PHONY: all clean
CXXFLAGS = -g -Wall -std=c++14
SOURCES  = main.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
BINARY   = main

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

main.o: Point.hpp PointsSampler.hpp ConvexHull.hpp BruteForceCH.hpp GrahamScanCH.hpp DivAndConCH.hpp DivAndConCH2.hpp

clean:
	$(RM) $(BINARY) $(OBJECTS)
