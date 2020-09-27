#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"


class InterruptManager
{
    protected:
        struct GateDescriptor
        {
            uint16_t handlerAddrLowBits;
            uint16_t gdt_codeSegment;
            uint8_t reserved;
            uint8_t access;
            uint16_t handleAddrHighBits;
        } __attribute__ ((packed));

        static GateDescriptor interruptDescriptorTable[256];
        struct interruptDescriptorTablePointer
        {
            uint16_t size;
            uint16_t base;
        } __attribute__ ((packed));

        static void SetInterruptDescriptorTableEntry(
                uint8_t intNumber,
                uint32_t codeSegmentSelectorOffset,
                void (*handler)(),
                uint8_t DescriptorPrivilegeLevel,
                uint8_t DescriptorType);
        Port8bitSlow picMasterCommand;
        Port8bitSlow picMasterData;
        Port8bitSlow picSlaveCommand;
        Port8bitSlow picSlaveData;

    public:

        InterruptManager(GlobalDescriptorTable *gdt);
        ~InterruptManager();
        static uint32_t handleInterrupt(uint8_t intNumber, uint32_t esp);
        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
        static void Activate();
};

#endif
