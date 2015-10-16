#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	Color();
	Color(float red, float blue, float green, float alpha);
	~Color();

	bool operator==(const Color &c) const;
	bool operator!=(const Color &c) const;
	Color operator-(const Color &c) const;
	Color operator+(const Color &c) const;
	Color operator/(float divider) const;
	Color operator*(float scaleFactor) const;

	float r, b, g, a;
};

#endif