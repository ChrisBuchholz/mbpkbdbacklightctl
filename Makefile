CC=g++
CFLAGS=-g -Wall -lXss

all: mbpkbdbacklight

mbpkbdbacklight: src/mbpkbdbacklight.cpp
	mkdir -p build/
	$(CC) $(CFLAGS) src/mbpkbdbacklight.cpp -o build/mbpkbdbacklight

.PHONY: clean

clean:
	rm -rfv build/
	
    
