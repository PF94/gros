#include <common/types.h>
#include <common/stdio.h>

/** @file stdio.cpp
*  @brief Yep... we have to do this...
*
*  @author Gamerappa
*/

// TODO: Move functions to the right files.

using namespace gros;
using namespace gros::common;

namespace gros
{

namespace common
{

enum {
    CPUID_FEAT_ECX_SSE3         = 1 << 0,
    CPUID_FEAT_ECX_PCLMUL       = 1 << 1,
    CPUID_FEAT_ECX_DTES64       = 1 << 2,
    CPUID_FEAT_ECX_MONITOR      = 1 << 3,
    CPUID_FEAT_ECX_DS_CPL       = 1 << 4,
    CPUID_FEAT_ECX_VMX          = 1 << 5,
    CPUID_FEAT_ECX_SMX          = 1 << 6,
    CPUID_FEAT_ECX_EST          = 1 << 7,
    CPUID_FEAT_ECX_TM2          = 1 << 8,
    CPUID_FEAT_ECX_SSSE3        = 1 << 9,
    CPUID_FEAT_ECX_CID          = 1 << 10,
    CPUID_FEAT_ECX_SDBG         = 1 << 11,
    CPUID_FEAT_ECX_FMA          = 1 << 12,
    CPUID_FEAT_ECX_CX16         = 1 << 13,
    CPUID_FEAT_ECX_XTPR         = 1 << 14,
    CPUID_FEAT_ECX_PDCM         = 1 << 15,
    CPUID_FEAT_ECX_PCID         = 1 << 17,
    CPUID_FEAT_ECX_DCA          = 1 << 18,
    CPUID_FEAT_ECX_SSE4_1       = 1 << 19,
    CPUID_FEAT_ECX_SSE4_2       = 1 << 20,
    CPUID_FEAT_ECX_X2APIC       = 1 << 21,
    CPUID_FEAT_ECX_MOVBE        = 1 << 22,
    CPUID_FEAT_ECX_POPCNT       = 1 << 23,
    CPUID_FEAT_ECX_TSC          = 1 << 24,
    CPUID_FEAT_ECX_AES          = 1 << 25,
    CPUID_FEAT_ECX_XSAVE        = 1 << 26,
    CPUID_FEAT_ECX_OSXSAVE      = 1 << 27,
    CPUID_FEAT_ECX_AVX          = 1 << 28,
    CPUID_FEAT_ECX_F16C         = 1 << 29,
    CPUID_FEAT_ECX_RDRAND       = 1 << 30,
    CPUID_FEAT_ECX_HYPERVISOR   = 1 << 31,

    CPUID_FEAT_EDX_FPU          = 1 << 0,
    CPUID_FEAT_EDX_VME          = 1 << 1,
    CPUID_FEAT_EDX_DE           = 1 << 2,
    CPUID_FEAT_EDX_PSE          = 1 << 3,
    CPUID_FEAT_EDX_TSC          = 1 << 4,
    CPUID_FEAT_EDX_MSR          = 1 << 5,
    CPUID_FEAT_EDX_PAE          = 1 << 6,
    CPUID_FEAT_EDX_MCE          = 1 << 7,
    CPUID_FEAT_EDX_CX8          = 1 << 8,
    CPUID_FEAT_EDX_APIC         = 1 << 9,
    CPUID_FEAT_EDX_SEP          = 1 << 11,
    CPUID_FEAT_EDX_MTRR         = 1 << 12,
    CPUID_FEAT_EDX_PGE          = 1 << 13,
    CPUID_FEAT_EDX_MCA          = 1 << 14,
    CPUID_FEAT_EDX_CMOV         = 1 << 15,
    CPUID_FEAT_EDX_PAT          = 1 << 16,
    CPUID_FEAT_EDX_PSE36        = 1 << 17,
    CPUID_FEAT_EDX_PSN          = 1 << 18,
    CPUID_FEAT_EDX_CLFLUSH      = 1 << 19,
    CPUID_FEAT_EDX_DS           = 1 << 21,
    CPUID_FEAT_EDX_ACPI         = 1 << 22,
    CPUID_FEAT_EDX_MMX          = 1 << 23,
    CPUID_FEAT_EDX_FXSR         = 1 << 24,
    CPUID_FEAT_EDX_SSE          = 1 << 25,
    CPUID_FEAT_EDX_SSE2         = 1 << 26,
    CPUID_FEAT_EDX_SS           = 1 << 27,
    CPUID_FEAT_EDX_HTT          = 1 << 28,
    CPUID_FEAT_EDX_TM           = 1 << 29,
    CPUID_FEAT_EDX_IA64         = 1 << 30,
    CPUID_FEAT_EDX_PBE          = 1 << 31
};

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
