CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
TARGETS = stl_vector stl_iterator stl_map stl_unordered_map

all: $(TARGETS)

stl_vector: src/consigna01.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

stl_iterator: src/consigna02.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

stl_map: src/consigna03.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

stl_unordered_map: src/consigna04.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: all
	@echo "=== Consigna 1: vector ===" && ./stl_vector
	@echo "=== Consigna 2: iterator ===" && ./stl_iterator
	@echo "=== Consigna 3: map ===" && ./stl_map
	@echo "=== Consigna 4: unordered_map ===" && ./stl_unordered_map

clean:
	rm -f $(TARGETS) obj/*.o

.PHONY: all run clean
