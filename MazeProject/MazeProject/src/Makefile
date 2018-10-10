PROGRAM=maze
DEBUG=-g
CFLAGS	= -Wall -Wextra -pedantic -std=c++14 $(DEBUG)

all: $(OBJS)
	g++ $(FLAGS) -o $(PROGRAM) *.cpp

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o *.out core $(PROGRAM)

DEBUG:
	g++ $(FLAGS) -o $(PROGRAM) *.cpp -DDEBUG
	