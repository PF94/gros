#ifndef __STDIO_H
#define __STDIO_H

#include "types.h"

namespace gros
{

	namespace common
	{
	void printf(char*);
	void printf(char*, uint8_t, uint8_t);
	void printfHex(uint8_t);
	}
}

#endif