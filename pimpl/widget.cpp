#include "widget.h"
#include "gadget.h"

struct Widget::Impl {
	std::string name;
	std::vector<double> data;
	Gadget g1, g2, g3;
};

Widget::Widget()
: pImpl(std::make_unique<Impl>())
{
	pImpl->name = "Widget Impl change";
}

Widget::~Widget() = default;

std::string Widget::getName()
{ return pImpl->name; }
