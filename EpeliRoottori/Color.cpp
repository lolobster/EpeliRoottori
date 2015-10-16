#include "Color.h"


Color::Color()
{
	// defaulted to white
	r = b = g = a = 255;
}

Color::Color(float red, float blue, float green, float alpha)
{
	r = red;
	b = blue;
	g = green;
	a = alpha;
}

Color::~Color()
{

}

bool Color::operator==(const Color &color) const
{
	return r == color.r && b == color.b && g == color.g &&  a == color.a;
}

bool Color::operator!=(const Color &color) const
{
	return !(*this == color);
}

Color Color::operator-(const Color &color) const
{
	return Color(r - color.r, b - color.b, g - color.g, a - color.a);
}

Color Color::operator+(const Color &color) const
{
	return Color(r + color.r, b + color.b, g + color.g, a + color.a);
}

Color Color::operator/(float divider) const
{
	return Color(r / divider, b / divider, g / divider, a / divider);
}

Color Color::operator*(float scaleFactor) const
{
	return Color(r * scaleFactor, b * scaleFactor, g * scaleFactor, a * scaleFactor);
}