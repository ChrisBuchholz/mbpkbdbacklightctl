# mbpkbdbacklightctl.cpp - control keyboard backlight for MacBook Pro
# Copyright (C) 2010  Chris Buchholz <christoffer.buchholz@gmail.com>
#
# This file is part of mbpkbdbacklightctl
#
# mbpkbdbacklightctl is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# mbpkbdbacklightctl is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with mbpkbdbacklightctl. If not, see <http://www.gnu.org/licenses/>.

CC=g++
CFLAGS=-g -Wall -lXss

all: mbpkbdbacklightctl

mbpkbdbacklightctl: src/mbpkbdbacklightctl.cpp
	mkdir -p build/
	$(CC) $(CFLAGS) src/mbpkbdbacklightctl.cpp -o build/mbpkbdbacklightctl

.PHONY: clean

clean:
	rm -rfv build/
	
    
