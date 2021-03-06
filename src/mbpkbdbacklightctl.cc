/*
 * mbpkbdbacklightctl - control keyboard backlight for MacBook Pro
 * Copyright (C) 2010  chrisbuchholz <http://chrisbuchholz.me/>
 *
 * This file is part of mbpkbdbacklightctl
 *
 * mbpkbdbacklightctl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mbpkbdbacklightctl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mbpkbdbacklightctl. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <X11/extensions/scrnsaver.h>

/* output debugging information to log file */
const char* debug_file = "/var/log/mbpkbdbacklightctl.log";

/* brightness file of which brightness value is written to and read from */
const char* brightness_file = "/sys/devices/platform/applesmc.768/leds/smc::kbd_backlight/brightness";

/* basic brightness parameters */
const unsigned short max_brightness = 255,
                     min_brightness = 0,
                     default_brightness = 75;

/* polling interval (in microseconds for usleep) */
const unsigned long poll_interval = 0.2*1000000;

/*
 *
 */
unsigned short get_backlight() {
    std::ifstream infile(brightness_file);
    if(infile.is_open()) {
        unsigned short brightness;
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
void set_backlight(unsigned short brightness) {
    std::ofstream outfile(brightness_file);
    if(outfile.is_open()) {
        outfile << brightness;
        outfile.close();
    }
}

/*
 *
 */
unsigned long get_idle_time(Display *x11_display) {
    XScreenSaverInfo *x11_info = XScreenSaverAllocInfo();
    XScreenSaverQueryInfo(x11_display, DefaultRootWindow(x11_display), x11_info);
    // convert from milliseconds to seconds and return
    return ((x11_info->idle) / 1000);
}

/*
 *
 */
void loopdeloop() {
    unsigned short old_brightness,
                   new_brightness;
    unsigned short idle_time = 0,
                   max_idle_time = 20;

    // connect to Xorg display
    std::string the_display = ":0.0";
    Display *x11_display = XOpenDisplay(the_display.c_str());
    if(x11_display != NULL) {
        while(1) {
            old_brightness = get_backlight();
            new_brightness = old_brightness;
            
            // query idle time from get_idle_time() and pass along x11_display
            // x11_display so we dont need to connect to a new XServer display
            // on every poll
            idle_time = get_idle_time(x11_display);
            
            if(idle_time > max_idle_time && new_brightness > min_brightness) {
                new_brightness = min_brightness;
            }
            else if(idle_time < max_idle_time && new_brightness == min_brightness) {
                new_brightness = default_brightness;
            }

            if(new_brightness != old_brightness) {
                set_backlight(new_brightness);
            }

            usleep(poll_interval);
        }
        XCloseDisplay(x11_display);
    }
    else {
        // grapping a XServer display failed, so we wait
        // and try again
        usleep(poll_interval);
        loopdeloop();
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
