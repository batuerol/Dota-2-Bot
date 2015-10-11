#include "Pixel.h"
#include <cmath>
#include <iostream>

bool Pixel::compare(Pixel& rhs, int diff /* = 0 */)
{
	return this->distance(rhs) < diff;
}

bool Pixel::compare(unsigned char r, unsigned char g, unsigned char b, int diff /* = 0 */)
{
	return this->distance(r, g, b) < diff;
}

bool Pixel::operator==(Pixel& rhs)
{
	return this->distance(rhs) == 0;
}

bool Pixel::operator!=(Pixel& rhs)
{
	return !(*this == rhs);
}

int Pixel::distance(Pixel& rhs)
{
	return distance(rhs.r, rhs.g, rhs.b);
}

int Pixel::distance(unsigned char r, unsigned char g, unsigned char b)
{
	int dR = r - this->r;
	int dG = g - this->g;
	int dB = b - this->b;
	
	return (int)round(sqrt(dR * dR + dG * dG + dB * dB));
}