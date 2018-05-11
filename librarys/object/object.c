//Write by 33kingusp
#include <stdlib.h>

#include "../vector/vector.h"
#include "../graphics/graphics.h"
#include "./object.h"

Obj *NewObj(int spr_size)
{
	Obj *obj;

	obj = (Obj *)malloc(sizeof(Obj));
	if (obj == NULL) return NULL;

	obj->pos = NewVector(0, 0);
	obj->size = NewVector(0, 0);

	obj->spr_size = spr_size;
	obj->spr_num = 0;

	obj->spr = (Spr **)malloc(sizeof(Spr *) * spr_size);
	if (obj->spr == NULL)
	{
		free(obj);
		return NULL;
	}

	obj->func = (void *)malloc(sizeof(void));
	if (obj->func == NULL)
	{
		free(obj->spr);
		free(obj);
		return NULL;
	}

	obj->func = NULL;
	obj->num = 0;
	obj->count = 0;
	obj->state = 0;
	obj->speed = 1;

	return obj;
}

void FreeObj(Obj *obj)
{
	free(obj->spr);
	obj->func = NULL;
	free(obj->func);
	free(obj);
}

void DeleteObj(Obj *obj)
{
	int n;
	
	for (n = 0; n < obj->spr_size; n++)
		DeleteSpr(obj->spr[n]);

	FreeObj(obj);
}

Obj *ObjSetSpr(Obj *obj, int n, Spr *spr)
{
	if (n < obj->spr_size)
		obj->spr[n] = spr;

	return obj;
}

Obj *MoveObj(Obj *obj, Vector vel)
{
	obj->pos = SumVector(obj->pos, vel);
	return obj;
}

Obj *GotoObj(Obj *obj, Vector vel)
{
	obj->pos = vel;
	return obj;
}

int IsCollisionObj(Obj *a, Obj *b)
{
	Vector pa = DifVector(a->pos, DivVector(a->size, 2));
	Vector pb = DifVector(b->pos, DivVector(b->size, 2));
	Vector ads = AdsVector(DifVector(pa, pb));
	Vector sum = SumVector(a->size, b->size);

	if (ads.x < sum.x && ads.y < sum.y) return 1;

	return 0;
}

int IsCollisionObjs(Obj *a, int size, Obj **b)
{
	int n;

	for (n = 0; n < size; n++)
	{
		if (b[n] == NULL) continue;
		if (IsCollisionObj(a, b[n])) return 1;
	}
	return 0;
}
