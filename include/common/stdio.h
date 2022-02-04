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
	static inline void outb(uint16_t, uint8_t);
	static inline uint8_t inb(uint16_t port);
	static inline void io_wait(void);
	static inline unsigned long save_irqdisable(void);
	static inline void irqrestore(unsigned long flags);
	static inline void lidt(void*, uint16_t);
	static inline void cpuid(int, uint32_t*, uint32_t*);
	static inline int cpuid_string(int, int);
	const char * const cpu_string();
	static inline uint64_t rdtsc();
	static inline unsigned long read_cr0(void);
	static inline void invlpg(void* m);
	static inline void wrmsr(uint32_t msr_id, uint64_t msr_value);
	static inline uint64_t rdmsr(uint32_t msr_id);
	void update_cursor(int, int);
	bool check_apic();
	}
}

#endif
