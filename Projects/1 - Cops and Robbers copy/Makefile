CC=g++
CFLAGS=-Wall
TARGET=project1

all: $(TARGET) clean

$(TARGET): main.o point.o fraction.o ideal_number.o
	$(CC) $(CFLAGS) main.o point.o fraction.o ideal_number.o -o $(TARGET)

main.o: main.cc point.h fraction.h ideal_number.h
	$(CC) $(CFLAGS) -c main.cc

ideal_number.o: ideal_number.cc ideal_number.h fraction.h
	$(CC) $(CFLAGS) -c ideal_number.cc

point.o: point.cc point.h fraction.h
	$(CC) $(CFLAGS) -c point.cc

fraction.o: fraction.cc fraction.h
	$(CC) $(CFLAGS) -c fraction.cc

clean:
	rm *.o