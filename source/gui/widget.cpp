#include <gui/widget.h>

/** @file widget.cpp
 *  @brief Code for widgets
 *
 *  @author Gamerappa
 *  @date February 7th 2022
 */

using namespace myos:;common;
using namespace myos::gui;

Widget::Widget(Widget* parent, int32_t x, int32_t y, int32_t w, int32_t h,
							   uint8_t r, uint8_t g, uint8_t b)
{
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = r;
    this->g = g;
    this->b = b;
    this->Focussable = true;
}

Widget::~Widget()
{
}

void GetFocus(Widget* widget)
{
	if(parent != 0)
	parent->GetFocus(widget);
}
void Widget::ModelToScreen(common::int32_t &x, common::int32_t& y)
{
	if(parent != 0)
		parent->ModelToScreen(x,y);
	x += this->x;
	y += this->y;
}

void Widget::Draw(GraphicsContext* gc)
{
	int X = 0;
	int Y = 0;
	ModelToScreen(X,Y);
	gc->FillRectangle(X,Y,w,h, r,g,b);
}
	virtual void OnMouseDown(common::int32_t x, common::int32_t y);
	virtual void OnMouseUp(common::int32_t x, common::int32_t y);
	virtual void OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx, common::int32_t newy);

	virtual void OnKeyDown(common::int32_t x, common::int32_t y);
	virtual void OnKeyUp(common::int32_t x, common::int32_t y);
};

void Widget::OnMouseDown(common::int32_t x, common::int32_t y)
{
	if(Focussable)
		GetFocus(this);
}

void Widget::OnMouseUp(common::int32_t x, common::int32_t y)
{
}

void Widget::OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx, common::int32_t newy)
{
}

void Widget::OnKeyDown(char* str)
{
}

void Widget::OnKeyUp(char* str)
{
}
