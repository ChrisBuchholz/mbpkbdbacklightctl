CC=g++
CFLAGS=-c -Wall

all: mbpkbdbacklight.cpp

mbpkbdbacklight.cpp:
	mkdir -p build/
	$(CC) $(CFLAGS) src/mbpkbdbacklight.cpp -o build/mbpkbdbacklight

clean:
	rm -rfv build/
	
    
