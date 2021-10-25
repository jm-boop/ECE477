TARGET = lab2
OBJS =  main.o phases.o 
CFLAGS = -g -Wall -O2

.PHONY:clean

all :$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o phases.o: header.h

clean:
	rm -f $(TARGET) $(OBJS) core*
