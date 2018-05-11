//Write by 33kingusp
#ifndef SPRITE_H
#define SPRITE_H

#include "../graphics/graphics.h"

typedef struct
{
	int size, page;
	double speed, time;
	Grp **grp;
} Spr;

extern Spr *NewSpr(int size);
extern void FreeSpr(Spr *spr);
extern void DeleteSpr(Spr *spr);

extern Spr *SprSetGrp(Spr *spr, int n, Grp *grp);
extern Spr *UpdateSpr(Spr *spr);

#endif

