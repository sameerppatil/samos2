#ifndef __TERMINAL_H
#define __TERMINAL_H

#include "vga.h"

class TerminalManager {
    //private:
        //const size_t VGA_WIDTH  = 80;
        //const size_t VGA_HEIGHT = 25;
         //TODO: make this const
        //uint16_t* VGA_MEMORY;

        size_t terminal_row;
        size_t terminal_col;
        uint8_t terminal_color;
        //uint16_t* terminal_buffer;
        //size_t termStrLen(const char* data);
        void clearScreen(void);
    public:
        TerminalManager();
        ~TerminalManager();
        void initialize(void);
        void writeStr(const char* data);
        void write(const char* data);
        void write(const char* data, size_t size);
        void putchar(char c);
        void putentryat(uint8_t c, uint8_t color, size_t x, size_t y);
};

#endif
