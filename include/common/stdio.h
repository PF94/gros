#ifndef __STDIO_H
#define __STDIO_H

#include <common/types.h>

/** @file stdio.h
 *  @brief Header file for STDIO functions
 *
 *  @author Gamerappa
 *  @author ROllerozxa
 */

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
