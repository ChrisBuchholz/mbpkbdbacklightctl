/*
 *  mbpkbdbacklight.cpp - control  keyboard  backlight  for MacBook Pro
 *  Copyright (C) 2010  Chris Buchholz <christoffer.buchholz@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation,  either version  3 of  the License, or
 *  (at your option)any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without  even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  v0.1
 *  notes: 
 *      Able to initate an amount and set value to passed argument
 *        if one is given.
 *
 *  tested on:
 *    MacBook Pro 5,5 13" (Core2Duo 2.53GHz) 
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>

const char* debug_file = "/var/log/mbpkbdbacklight.log";
const char* brightness_file = "/sys/devices/platform/applesmc.768/leds/smc::kbd_backlight/brightness";
const int max_brightness = 255;
const int min_brightness = 0;
const int default_brightness = 75;
int brightness = 0;

void get_backlight() {
    std::ifstream infile(brightness_file);
    if(infile.is_open()) {
        infile >> brightness;
        infile.close();
    }
}

void set_backlight(int amount) {
    std::ofstream outfile(brightness_file);
    if(outfile.is_open()) {
        outfile << amount;
        outfile.close();
    }
}

void automate() {}

int main(int argc, char* argv[]) {
    if(argc > 1) {
        set_backlight(atoi(argv[1]));
    }
    else {
        set_backlight(default_brightness);
    }

    automate();

    return 0;
}
