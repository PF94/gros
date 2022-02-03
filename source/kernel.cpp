#include <grverp.h>
#include <types.h>
#include <gdt.h>
#include <interrupts.h>
#include <driver.h>
#include <keyboard.h>
#include <mouse.h>
#include <stdio.h>
#include <bouncy_ball.h>

using namespace gros;
using namespace gros::common;
using namespace gros::drivers;
using namespace gros::hardwarecommunication;

/**
* Prints a string of text at (posX, posY)
*
* @param str Text string
* @param posX X position of where the text should start.
* @param posY Y position of where the text should start.
*/
void printf(char* str, uint8_t posX, uint8_t posY)
{
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

	static uint8_t x=0, y=0;

	// Only override cursor pos if called from the correct overload.
	if (posX != 255 && posY != 255) {
		x = posX; y = posY;
	}

	for(int i = 0; str[i] != '\0'; ++i)
	{
		switch(str[i])
		{
			case '\n':
				y++;
				x = 0;
				break;
			default:
				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
				x++;
				break;
		}

		if(x >= 80)
		{
			y++;
			x = 0;
		}
		if (y >= 25)
		{
			for(y = 0; y < 25; y++)
				for(x = 0; x < 80; x++)
					VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';

		x = 0;
		y = 0;
		}
	}
}

/**
* Prints a string of text at the current cursor position.
*
* @param str Text string
*/
void printf(char* str) {
	printf(str, 255, 255);
}

/**
* Prints a string of two hex numbers.
*
* @param key Interrupt number(?)
*/
void printfHex(uint8_t key)
{
	char* foo = "00";
	char* hex = "0123456789ABCDEF";
	foo[0] = hex[(key >> 4) & 0xF];
	foo[1] = hex[key & 0xF];
	printf(foo);
}

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

	printf("Init hardware Stage 2\n");
		drvManager.ActivateAll();

	printf("Init hardware Stage 3\n");
	interrupts.Activate();

	while(1);
}
