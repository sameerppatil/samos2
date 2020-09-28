#include "../include/types.h"
#include "../include/gdt.h"
#include "../include/interrupts.h"
#include "../include/terminal.h"

TerminalManager terminal;

void printf(char *str)
{
    terminal.writeStr(str);
    //static uint16_t* vidMemory = (uint16_t *) 0xb8000;
    //for(uint32_t i = 0; str[i] != '\0'; i++)
    //{
        //vidMemory[i] = (vidMemory[i] & 0xFF00) | str[i];
    //}
}

typedef void (*constructor) ();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callContructors(void)
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
}


extern "C" void kernel_main(const void *multiboot_struc, uint32_t magic_num)
{
	//printf("Hello, kernel World!\n");
    terminal.initialize();
    terminal.writeStr("Terminal Init done\n");
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt, &terminal);

    interrupts.Activate();
    while(1);
}
