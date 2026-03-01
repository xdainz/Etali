CFLAGS = -lcurl -ljsoncpp
DEPENDENCIES = jsoncpp curl gcc-libs glibc 

all: etali

etali: main.o fetch.o parse_json.o help.o
	@echo "Compiling etali"
	g++ $(CFLAGS) main.o fetch.o parse_json.o help.o -o etali

main.o: main.cpp
	@echo "Compiling main file"
	g++ $(CFLAGS) -c main.cpp

fetch.o: fetch/fetch.cpp
	@echo "Compiling fetch"
	g++ $(CFLAGS) -c fetch/fetch.cpp

parse_json.o: parse/parse_json.cpp
	@echo "Compiling json parser"
	g++ $(CFLAGS) -c parse/parse_json.cpp

help.o: cli/help.cpp
	@echo "Compiling cli help"
	g++ $(CFLAGS) -c cli/help.cpp

prepare:
	@echo "Installing dependencies..."
	sudo pacman -S --needed --noconfirm  $(DEPENDENCIES)

clean:
	@echo "Cleaning..."
	rm etali *.o
