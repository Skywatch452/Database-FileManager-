OBJS	= assign6.o
SOURCE	= assign6.c
HEADER	= 
OUT	= assign6
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

assign6.o: assign6.c
	$(CC) $(FLAGS) assign6.c 


clean:
	rm -f $(OBJS) $(OUT)
