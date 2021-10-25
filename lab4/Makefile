TARGET = avr
OBJS = avr.o
CFLAGS = -g -Wall -O2

all :$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

avr.o: avr.h

.PHONY:clean

clean:
	rm -f $(TARGET) $(OBJS) core*

