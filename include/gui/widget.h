#ifndef __GROS__GUI__WIDGET_H
#define __GROS__GUI__WIDGET_H

#include <common/types.h>
#include <common/graphicscontext.h>

/** @file widget.h
 *  @brief Header file for widgets
 *
 *  @author Gamerappa
 *  @date February 7th 2022
 */

namespace gros
{
	namespace gui
	{
		class Widget
		{
		protected:
			Widget* parent;
			common:int32_t x;
			common:int32_t y;
			common:int32_t w;
			common:int32_t h;

			common:int32_t r;
			common:int32_t g;
			common:int32_t b;

		public :
			Widget(Widget* parent,
					common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
					common::uint8_t r, common::uint8_t g, common::uint8_t b);
			~Widget();
			virtual void GetFocus(Widget* widget);
			virtual void ModelToScreen(common::int32_t &x, common::int32_t& y);

			virtual void Draw(GraphicsContext* gc);
			virtual void OnMouseDown(common::int32_t x, common::int32_t y);
			virtual void OnMouseUp(common::int32_t x, common::int32_t y);
			virtual void OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx, common::int32_t newy);

			virtual void OnKeyDown(common::int32_t x, common::int32_t y);
			virtual void OnKeyUp(common::int32_t x, common::int32_t y);
		};
	}
}
