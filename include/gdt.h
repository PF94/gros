#ifndef __GDT_H
#define __GDT_H

/** @file gdt.h
 *  @brief Header file for the Global Descriptor Table
 *
 *  @author Gamerappa
 */

#include <common/types.h>
namespace gros
{
	class GlobalDescriptorTable
	{
		public:

			class SegmentDescriptor
			{
				private:
					gros::common::uint16_t limit_lo;
					gros::common::uint16_t base_lo;
					gros::common::uint8_t base_hi;
					gros::common::uint8_t type;
					gros::common::uint8_t limit_hi;
					gros::common::uint8_t base_vhi;

				public:
					SegmentDescriptor(gros::common::uint32_t base, gros::common::uint32_t limit, gros::common::uint8_t type);
					gros::common::uint32_t Base();
					gros::common::uint32_t Limit();
			} __attribute__((packed));

		private:
			SegmentDescriptor nullSegmentSelector;
			SegmentDescriptor unusedSegmentSelector;
			SegmentDescriptor codeSegmentSelector;
			SegmentDescriptor dataSegmentSelector;

		public:

			GlobalDescriptorTable();
			~GlobalDescriptorTable();

			gros::common::uint16_t CodeSegmentSelector();
			gros::common::uint16_t DataSegmentSelector();
	};
}
#endif
