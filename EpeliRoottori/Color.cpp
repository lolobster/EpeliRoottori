#include "Color.h"

Color::Color()
{
	// Defaults to white
	r = 255;
	b = 255;
	g = 255;
	a = 255;
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
	return r == color.r && b == color.b && g == color.g  && a == color.a;
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

Color Color::operator*(float scale) const
{
	return Color(r * scale, b * scale, g * scale, a * scale);
}