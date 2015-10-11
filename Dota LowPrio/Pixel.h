#pragma once

#include <Windows.h>

class Pixel
{
public:
	static const unsigned int EPSILON = 25;

	Pixel() : x(0), y(0), r(0), g(0), b(0) {}
	Pixel(int x, int y, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0) :
		x(x), y(y), r(r), g(g), b(b)
	{
	}

	bool compare(Pixel& rhs, int diff = 0);
	bool compare(unsigned char r, unsigned char g, unsigned char b, int diff = 0);
	bool operator==(Pixel& rhs);
	bool operator!=(Pixel& rhs);

	int getX() { return x; }
	int getY() { return y; }

private:
	int x, y;
	unsigned char r, g, b;

	int distance(Pixel& rhs);
	int distance(unsigned char r, unsigned char g, unsigned char b);
};