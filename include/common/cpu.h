#ifndef __GROS__COMMON__CPU_H
#define __GROS__COMMON__CPU_H

/** @file cpu.h
 *  @brief Header file for CPU functions
 *
 *  @author Gamerappa
 *  @date February 4th 2022
 */

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
	bool check_apic();
	}
}

#endif
