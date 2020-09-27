#include "../include/types.h"
#include "../include/gdt.h"
#include "../include/interupts.h"

void printf(char *str)
{
    static uint16_t* vidMemory = (uint16_t *) 0xb8000;
    for(uint32_t i = 0; str[i] != '\0'; i++)
    {
        vidMemory[i] = (vidMemory[i] & 0xFF00) | str[i];
    }
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
	printf("Hello, kernel World!\n");
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    //interrupts.Activate();
    while(1);
}
