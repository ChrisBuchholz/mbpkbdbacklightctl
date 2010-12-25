CC=g++
CFLAGS=-g -Wall -lXss

all: mbpkbdbacklightctl

mbpkbdbacklightctl: src/mbpkbdbacklightctl.cpp
	mkdir -p build/
	$(CC) $(CFLAGS) src/mbpkbdbacklightctl.cpp -o build/mbpkbdbacklightctl

.PHONY: clean

clean:
	rm -rfv build/
	
    
