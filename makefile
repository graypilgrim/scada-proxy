CXX = g++
CXXFLAGS = -c -Wall -pedantic -o2 -std=c++11
BINARY = proxy.out

SOURCES = \
		src/main.cpp \
		src/Buffer.cpp \
		src/Configuration.cpp \

OBJECTS=$(SOURCES:.cpp=.o)

$(BINARY): $(OBJECTS)
	$(CXX) $^ -o $@
	@echo "Built completed"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	@rm -f $(BINARY)
	@rm -f src/*.o src/*.gch

.PHONY:
	clean
