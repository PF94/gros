#ifndef __GROS__GUI__DESKTOP_H
#define __GROS__GUI__DESKTOP_H

/** @file desktop.h
*  @brief Header for the desktop.
*
*  @author Gamerappa
*  @date February 7th 2022
*/

#include <gui/widget.h>
#include <drivers/mouse.h>

namespace gros
{
	namespace gui
	{
		class Desktop : public CompositeWidget, public gros::drivers::MouseEventHandler
		{
		protected:
			common::uint32_t MouseX;
			common::uint32_t MouseY;

		public:
			Desktop(common::int32_t w, common::int32_t h,
					common::uint8_t r, common::uint8_t g, common::uint8_t b);
			~Desktop();

			void Draw(common::GraphicsContext* gc);

			void OnMouseDown(common::uint8_t button);
			void OnMouseUp(common::uint8_t button);
			void OnMouseMove(int x, int y);
		};
	}
}

#endif
