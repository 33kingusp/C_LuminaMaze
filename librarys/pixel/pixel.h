//Write by 33kingusp
#ifndef PIXEL_H
#define PIXEL_H

typedef struct
{
	char ch;
	int f, b;
} Pixel;

extern Pixel NewPixel(char ch, int f, int b);
extern Pixel MargePixel(Pixel a, Pixel b);
extern int IsEqualPixel(Pixel a, Pixel b);

#endif
