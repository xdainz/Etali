CFLAGS = -lcurl

all: etali

etali: main.o
	@echo "Compiling etali"
	g++ $(CFLAGS) main.o -o etali

main.o: main.cpp
	@echo "Compiling main file"
	g++ $(CFLAGS) -c main.cpp

clean:
	@echo "Cleaning..."
	rm etali *.o
