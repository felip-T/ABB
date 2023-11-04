CC = g++
LD = g++

CFLAGS = -Wall -g
LDFLAGS = -Wall -g

OBJS = main.o 

TARGET = main

.cpp.o:
	$(CC) $(CFLAGS) -c $<

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f *.o $(TARGET)
