CFLAGS	= -Wall -Wextra -pedantic -std=c++11 
DEBUG	= -g -ggdb
PROG	= maze
OBJ	= maze.o main.o cell.o path.o svgprocessor.o binaryprocessor.o \
args_parser.o depthfirstsearchsolver.o \
maze_generator.o

%.o: %.cpp
	@echo "##### Compiling........"
	g++ $(CFLAGS) $(DEBUG) -c $< -o $@

all: $(OBJ)
	@echo "##### Linking........"
	g++ -o $(PROG) $(OBJ)

clean: 
	@echo "##### Cleaning.........."
	rm -f $(OBJ) $(PROG)

.PHONY:prep
prep:
	@echo "##### Preparing........."
	source /opt/rh/devtoolset-2/enable
