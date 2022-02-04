#include <common/types.h>
#include <common/stdio.h>
#include <common/cpu.h>

/** @file cpu.cpp
*  @brief CPU functions???
*
*  @author Gamerappa
*  @date February 4th 2022
*/

using namespace gros;
using namespace gros::common;

namespace gros
{

namespace common
{

static inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
	/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
	* Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
	* The  outb  %al, %dx  encoding is the only option for all other cases.
	* %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ( "inb %1, %0"
				: "=a"(ret)
				: "Nd"(port) );
	return ret;
}

static inline void io_wait(void)
{
	outb(0x80, 0);
}

static inline unsigned long save_irqdisable(void)
{
	unsigned long flags;
	asm volatile ("pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory");
	return flags;
}

static inline void irqrestore(unsigned long flags)
{
	asm ("push %0\n\tpopf" : : "rm"(flags) : "memory","cc");
}

static inline void lidt(void* base, uint16_t size)
{   // This function works in 32 and 64bit mode
	struct {
		uint16_t length;
		void*    base;
	} __attribute__((packed)) IDTR = { size, base };

	asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

// TODO: MOVE THIS TO A "CPU" FILE
/** issue a single request to CPUID. Fits 'intel features', for instance
*  note that even if only "eax" and "edx" are of interest, other registers
*  will be modified by the operation, so we need to tell the compiler about it.
*/
static inline void cpuid(int code, uint32_t *a, uint32_t *d) {
asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}

static inline int cpuid_string(int code, int where[4]) {
__asm__ volatile ("cpuid":"=a"(*where),"=b"(*(where+0)),
			"=d"(*(where+1)),"=c"(*(where+2)):"a"(code));
return (int)where[0];
}

const char * const cpu_string() {
	static char s[16] = "BogusProces!";
	cpuid_string(0, (int*)(s));
	printf(s); // This is fucking dumb.
	return s;
}

static inline uint64_t rdtsc()
{
	uint64_t ret;
	asm volatile ( "rdtsc" : "=A"(ret) );
	return ret;
}

static inline unsigned long read_cr0(void)
{
	unsigned long val;
	asm volatile ( "mov %%cr0, %0" : "=r"(val) );
	return val;
}

static inline void invlpg(void* m)
{
	/* Clobber memory to avoid optimizer re-ordering access before invlpg, which may cause nasty bugs. */
	asm volatile ( "invlpg (%0)" : : "b"(m) : "memory" );
}


static inline void wrmsr(uint32_t msr_id, uint64_t msr_value)
{
	asm volatile ( "wrmsr" : : "c" (msr_id), "A" (msr_value) );
}

static inline uint64_t rdmsr(uint32_t msr_id)
{
	uint64_t msr_value;
	asm volatile ( "rdmsr" : "=A" (msr_value) : "c" (msr_id) );
	return msr_value;
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * 80 + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

bool check_apic() {
   uint32_t eax, edx;
   cpuid(1, &eax, &edx);
   return edx & CPUID_FEAT_EDX_APIC;
}

}

}
