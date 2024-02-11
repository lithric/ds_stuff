CC=g++
CFLAGS=-Wall
TARGET=project1

all: $(TARGET) clean

$(TARGET): main.o point.o fraction.o
	$(CC) $(CFLAGS) main.o point.o fraction.o -o $(TARGET)

main.o: main.cc point.h fraction.h
	$(CC) $(CFLAGS) -c main.cc

point.o: point.cc point.h fraction.h
	$(CC) $(CFLAGS) -c point.cc

fraction.o: fraction.cc fraction.h
	$(CC) $(CFLAGS) -c fraction.cc

clean:
	rm *.o