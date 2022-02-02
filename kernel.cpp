#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "driver.h"
#include "keyboard.h"
#include "mouse.h"
#include "stdio.h"
#include "bouncy_ball.h"

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

	printf("GROS (build [placeholder])\n",0,0);

	GlobalDescriptorTable gdt;
	InterruptManager interrupts(0x20, &gdt);

	printf("Init hardware Stage 1",0,0);
	DriverManager drvManager;
		MouseDriver mouse(&interrupts);
		drvManager.AddDriver(&mouse);

		KeyboardDriver keyboard(&interrupts);
		drvManager.AddDriver(&keyboard);

	printf("Init hardware Stage 2",0,0);
		drvManager.ActivateAll();

	printf("Init hardware Stage 3",0,0);
	interrupts.Activate();

	while(1);
}
