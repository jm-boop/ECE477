TARGET = PWM
OBJS = readPWM.o
CFLAGS = -g -Wall -O2
LIBS = -lwiringPi -lpthread

all :$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

.PHONY:clean

clean:
	rm -f $(TARGET) $(OBJS) core*

