#ifndef __GROS__DRIVERS__KEYBOARD_H
#define __GROS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace gros
{
	namespace drivers
	{
		class KeyboardEventHandler
		{
		public:
			KeyboardEventHandler();

			virtual void OnKeyDown(char);
			virtual void OnKeyUp(char);
		};

		class KeyboardDriver : public gros::hardwarecommunication::InterruptHandler, public Driver
		{
			gros::hardwarecommunication::Port8Bit dataport;
			gros::hardwarecommunication::Port8Bit commandport;

			KeyboardEventHandler* handler;
		public:
			KeyboardDriver(InterruptManager* manager, KeyboardEventHandler* handler);
			~KeyboardDriver();
			virtual gros::common::uint32_t HandleInterrupt(gros::common::uint32_t esp);
			virtual void Activate();
		};
	}
}
#endif
