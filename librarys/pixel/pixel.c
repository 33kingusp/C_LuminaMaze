//Write by 33kingusp

#include "./pixel.h"

Pixel NewPixel(char ch, int f, int b)
{
	Pixel pix;

	pix.ch = ch;
	pix.f = f;
	pix.b = b;

	return pix;
}

Pixel MargePixel(Pixel a, Pixel b)
{
	Pixel pix;

	if (b.b < 0 || b.b >= 8)
	{
		pix.b = a.b;
		if (b.f < 0 || b.f >= 8 || b.ch == ' ')
		{
			pix.ch = a.ch;
			pix.f = a.f;
		}
		else
		{
			pix.ch = b.ch;
			pix.f = b.f;
		}
	}
	else
	{
		pix.ch = b.ch;
		pix.f = b.f;
		pix.b = b.b;
	}

	return pix;
}

int IsEqualPixel(Pixel a, Pixel b)
{
	return (a.ch == b.ch && a.f == b.f && a.b == b.b);
}
