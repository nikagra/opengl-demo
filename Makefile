CC=g++
CFLAGS=-Wall
LDFLAGS=-lglut -lGL -lGLEW
SRCS=gldemo.cpp
OBJS=$(SRCS:.cpp=.o)
PROGRAM=gldemo

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<
	
clean:
	-rm *.o $(PROGRAM)
