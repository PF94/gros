#include <common/grverp.h>
#include <common/types.h>
#include <common/stdio.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <bouncy_ball.h>

/** @file kernel.cpp
 *  @brief GROS Kernel Code
 *
 *  @author Gamerappa
 *  @author ROllerozxa
 */

using namespace gros;
using namespace gros::common;
using namespace gros::drivers;
using namespace gros::hardwarecommunication;

/**
* Keyboard shit.
*/
class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
	void OnKeyDown(char c)
	{
		char* foo = " ";
		foo[0] = c;
		printf(foo);
	}
};

/**
* Mouse shit.
*/
class MouseToConsole : public MouseEventHandler
{
	int8_t x, y;
public:

	MouseToConsole()
	{
	}

	virtual void OnActivate()
	{
		uint16_t* VideoMemory = (uint16_t*)0xb8000;
		x = 40;
		y = 12;
		VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
							| (VideoMemory[80*y+x] & 0xF000) >> 4
							| (VideoMemory[80*y+x] & 0x00FF);
	}

	virtual void OnMouseMove(int xoffset, int yoffset)
	{
		static uint16_t* VideoMemory = (uint16_t*)0xb8000;
		VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
							| (VideoMemory[80*y+x] & 0xF000) >> 4
							| (VideoMemory[80*y+x] & 0x00FF);

		x += xoffset;
		if(x >= 80) x = 79;
		if(x < 0) x = 0;
		y += yoffset;
		if(y >= 25) y = 24;
		if(y < 0) y = 0;

		VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
							| (VideoMemory[80*y+x] & 0xF000) >> 4
							| (VideoMemory[80*y+x] & 0x00FF);
	}

};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
	// FIXME: Port... the entire C/C++ libraries? FUCK FUCK FUCK FUCK FUCK
	/*
	for (uint8_t i = 0; i < 79; i++) {
		for (uint8_t j = 0; j < 25; j++) {
			printf("#", i, j);
		}
	} */

	// FIXME: This is ugly code.
	printf("GROS Version ");
	printf(majorVersion);
	printf(".");
	printf(minorVersion);
	printf(" (build ");
	printf(buildNumber);
	printf(")\n\n");
	update_cursor(16,8); // this is a placeholder

	GlobalDescriptorTable gdt;
	InterruptManager interrupts(0x20, &gdt);

	printf("Init hardware Stage 1\n");
	DriverManager drvManager;
		MouseToConsole mousehandler;
		MouseDriver mouse(&interrupts, &mousehandler);
		drvManager.AddDriver(&mouse);

	PrintfKeyboardEventHandler kbhandler;
		KeyboardDriver keyboard(&interrupts, &kbhandler);
		drvManager.AddDriver(&keyboard);

		PeripheralComponentInterconnectController PCIController;
		PCIController.SelectDrivers(&drvManager);

	printf("Init hardware Stage 2\n");
		drvManager.ActivateAll();

	printf("Init hardware Stage 3\n");
	interrupts.Activate();

	while(1);
}
