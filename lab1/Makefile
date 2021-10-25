TARGET = main
OBJS =  main.o something_cool.o
CFLAGS = -g -Wall
LIBS = -lm

.PHONY:clean

all :$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

something_cool.o: cool.h

clean:
	rm -f $(TARGET) $(OBJS) core*
