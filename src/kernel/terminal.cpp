#include "../include/terminal.h"

//uint16_t* TerminalManager::VGA_MEMORY = (uint16_t*) 0xb800;

//size_t TerminalManager::terminal_row = 0;
//size_t TerminalManager::terminal_col = 0;
//uint8_t TerminalManager::terminal_color = 0;
//uint16_t* TerminalManager::terminal_buffer = 0;
void printf(char* str);

TerminalManager::TerminalManager()
{

}

TerminalManager::~TerminalManager()
{
}
void TerminalManager::initialize(void)
{
    terminal_row = 0;
    terminal_color = VGA_COLOR_LIGHT_RED;
    terminal_col = 0;
}

void TerminalManager::putentryat(uint8_t c, uint8_t color, size_t x, size_t y)
{
    //color unused for now
    static uint16_t* vidMemory = (uint16_t *) 0xb8000;
    //vidMemory[y*80 + x] = (vidMemory[y*80 + 80] & 0xFF0C) | c;
    vidMemory[y*80 + x] = vga_entry(c, VGA_COLOR_RED);
}

void TerminalManager::clearScreen(void)
{
    //undefined
    terminal_row = terminal_col = 0;
    writeStr("clearScreen(): undefined");
    return;
}

void TerminalManager::putchar(char c)
{
    putentryat(c, terminal_color, terminal_col, terminal_row);
    terminal_col++;
    if(terminal_col == 80)
    {
        terminal_col = 0;
        terminal_row++;
        if(terminal_row == 25)
            clearScreen();
    }
}

void TerminalManager::write(const char* data, size_t size)
{
    //const char* str = "terminal init done";
    for(uint32_t i = 0; data[i] != '\0'; i++)
    {
        putchar(data[i]);
    }
    putchar(' ');
}

void TerminalManager::writeStr(const char* data)
{
    write(data, 0);
}

