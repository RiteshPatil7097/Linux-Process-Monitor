CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lncurses
INC = -Iinclude

SRC = src/main.cpp src/cli/cli.cpp src/core/monitor.cpp src/core/parser.cpp src/core/process_control.cpp

all:
	$(CXX) $(SRC) $(INC) $(CXXFLAGS) $(LDFLAGS) -o monitor

clean:
	rm -f monitor
