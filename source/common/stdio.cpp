#include <common/types.h>
#include <common/stdio.h>

using namespace gros;
using namespace gros::common;

namespace gros
{

namespace common
{

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

}

}
