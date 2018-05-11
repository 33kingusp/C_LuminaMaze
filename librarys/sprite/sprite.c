//Write by 33kingusp

#include <stdlib.h>

#include "../graphics/graphics.h"

#include "./sprite.h"

Spr *NewSpr(int size)
{
	Spr *spr;

	spr = (Spr *)malloc(sizeof(Spr));
	if (spr == NULL) return NULL;

	spr->size = size;
	spr->page = 0;
	spr->speed = 0;
	spr->time = 0;

	spr->grp = (Grp **)malloc(sizeof(Grp *) * size);
	if (spr->grp == NULL)
	{
		free(spr);
		return NULL;
	}

	return spr;
}

void FreeSpr(Spr *spr)
{
	free(spr->grp);
	free(spr);
}

void DeleteSpr(Spr *spr)
{
	int n;

	for (n = 0; n < spr->size; n++)
		FreeGrp(spr->grp[n]);

	FreeSpr(spr);
}

Spr *SprSetGrp(Spr *spr, int n, Grp *grp)
{
	if (n < spr->size)
		spr->grp[n] = grp;

	return spr;
}

Spr *UpdateSpr(Spr *spr)
{
	spr->time += spr->speed;
	if (spr->time >= 10.0)
	{
		spr->time -= 10.0;
		spr->page++;
		if (spr->page >= spr->size)
			spr->page = 0;
	}
	return spr;
}
