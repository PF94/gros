#include "keyboard.h"


KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(0x21, manager),
dataport(0x60),
commandport(0x64)
{
    while(commandport.Read() & 0x1)
        dataport.Read();
}

KeyboardDriver::~KeyboardDriver()
{

}

void printf(char*);

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

        char* foo = "KEYBOARD 0x00";
        char* hex = "0123456789ABCDEF";
        foo[11] = hex[(key >> 4) & 0xF];
        foo[12] = hex[key & 0xF];
        printf(foo);

    return esp;
}
