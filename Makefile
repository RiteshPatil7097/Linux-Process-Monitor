CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++17 -lncurses

SRC=src/main.cpp src/cli/cli.cpp src/core/monitor.cpp src/core/parser.cpp
INC=-Iinclude

all:
	$(CXX) $(SRC) $(INC) $(CXXFLAGS) -o monitor

clean:
	rm -f monitor