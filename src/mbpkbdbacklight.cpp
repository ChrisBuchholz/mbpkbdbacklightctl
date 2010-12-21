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
#include <string>
#include <stdlib.h>

const char* bfile = "/sys/devices/platform/applesmc.768/leds/smc::kbd_backlight/brightness";
const int initAmount = 75;

std::string get_backlight() {
    std::string amount;
    std::ifstream file(bfile);
    getline(file, amount);
    file.close();
    return amount;
}

void set_backlight(int amount) {
    std::ofstream file(bfile);
    file << amount;
    file.close();
}

void automate() {}

int main(int argc, char* argv[]) {
    std::cout << "test" << std::endl;
    if(argc > 1) {
        set_backlight(atoi(argv[1]));
    }
    else {
        set_backlight(initAmount);
    }

    automate();
    
    return 0;
}
