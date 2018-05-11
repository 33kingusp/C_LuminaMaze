//Write by 33kingusp
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../pixel/pixel.h"

typedef struct
{
	int w, h;
	Pixel *pixel;
} Grp;

extern Grp *NewGrp(int w, int h);
extern void FreeGrp(Grp *grp);
extern Grp *DataToGrp(char *data);

#endif
