#ifndef __GROS__DRIVERS__MOUSE_H
#define __GROS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace gros
{
	namespace drivers
	{
		class MouseEventHandler
		{
		public:
			MouseEventHandler();

			virtual void OnActivate();
			virtual void OnMouseDown(uint8_t button);
			virtual void OnMouseUp(uint8_t button);
			virtual void OnMouseMove(int x, int y);
		};

		class MouseDriver : public gros::hardwarecommunication::InterruptHandler, public Driver
		{
			Port8Bit dataport;
			Port8Bit commandport;

			gros::common::uint8_t buffer[3];
			gros::common::uint8_t offset;
			gros::common::uint8_t buttons;

			MouseEventHandler* handler;
			int8_t x, y;
		public:
			MouseDriver(gros::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
			~MouseDriver();
			virtual uint32_t HandleInterrupt(uint32_t esp);
			virtual void Activate();
		};
	}
}
#endif
