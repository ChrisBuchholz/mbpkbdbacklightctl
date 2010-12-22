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
#include <X11/extensions/scrnsaver.h>

/* output debugging information to log file */
const char* debug_file = "/var/log/mbpkbdbacklight.log";

/* brightness file of which brightness value is written to and read from */
const char* brightness_file = "/sys/devices/platform/applesmc.768/leds/smc::kbd_backlight/brightness";

/* basic brightness parameters */
const int max_brightness = 255;
const int min_brightness = 0;
const int default_brightness = 75;

/* polling interval */
const int poll_interval = 0.2;

/*
 *
 */
int get_backlight() {
    std::ifstream infile(brightness_file);
    if(infile.is_open()) {
        int brightness;
        infile >> brightness;
        infile.close();
        return brightness;
    }
    return default_brightness;
}

/*
 * Writes the keyboard backlight brightness value to the system
 * from second argument which should be an interger value in
 * the range of min_brightness and max_brightness
 */
void set_backlight(int brightness) {
    std::ofstream outfile(brightness_file);
    if(outfile.is_open()) {
        outfile << brightness;
        outfile.close();
    }
}

/*
 *
 */
int get_idle_time() {
    XScreenSaverInfo *info = XScreenSaverAllocInfo();
    Display *display = XOpenDisplay(0);
    XScreenSaverQueryInfo(display, DefaultRootWindow(display), info);
    return (info->idle / 1000);
}

/*
 *
 */
void loopdeloop() {
    int old_brightness,
        new_brightness;
    int idle_time = 0,
        max_idle_time = 5;

    while(1) {
        old_brightness = get_backlight();
        new_brightness = old_brightness;

        idle_time = get_idle_time();
        
        if(idle_time > max_idle_time && new_brightness > min_brightness) {
            new_brightness = min_brightness;
        }
        else if(idle_time < max_idle_time && new_brightness == min_brightness) {
            new_brightness = default_brightness;
        }

        if(new_brightness != old_brightness) {
            set_backlight(new_brightness);
        }

        sleep(poll_interval);
    }
}

int main(int argc, char* argv[]) {
    if(argc > 1) {
        set_backlight(atoi(argv[1]));
    }
    else {
        set_backlight(default_brightness);
    }

    loopdeloop();

    return 0;
}
