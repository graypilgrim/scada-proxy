CXX = g++
CXXFLAGS = -c -Wall -pedantic -o2 -std=c++11
LINK_FLAGS = -lpthread
BINARY = proxy.out

SOURCES = \
		src/main.cpp \
		src/Buffer.cpp \
		src/Configuration.cpp \
		src/Thread.cpp \
		src/ConnectionThread.cpp \
		src/ClientThread.cpp \
		src/Logger.cpp \
		src/Message.cpp \
		src/ClientData.cpp \
		src/ServerThread.cpp \

OBJECTS=$(SOURCES:.cpp=.o)

$(BINARY): $(OBJECTS)
	$(CXX) $^ -o $@ $(LINK_FLAGS)
	@echo "Built completed"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	@rm -f $(BINARY)
	@rm -f src/*.o src/*.gch

.PHONY:
	clean
