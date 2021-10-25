TARGET = run
OBJS = main.o interface.o double_strobe.o
CFLAGS = -g -Wall -O2
LIBS = -lwiringPi

all :$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

main.o interface.o double_strobe.o: led.h

.PHONY:clean

clean:
	rm -f $(TARGET) $(OBJS) core*

