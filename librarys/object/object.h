//Write by 33kingusp
#ifndef OBJECT_H
#define OBJECT_H

#include "../vector/vector.h"
#include "../sprite/sprite.h"

typedef struct
{
	Vector pos;
	Vector size;

	int spr_size, spr_num;
	Spr **spr;
	//enemy動作用
	void (*func)();
	int num;
	int state;
	int count;
	double speed;
	
} Obj;

extern Obj *NewObj(int spr_size);
extern void FreeObj(Obj *obj);
extern void DeleteObj(Obj *obj);

extern Obj *ObjSetSpr(Obj *obj, int n, Spr *spr);

extern Obj *MoveObj(Obj *obj, Vector vel);
extern Obj *GotoObj(Obj *obj, Vector vel);

extern int IsCollisionObj(Obj *a, Obj *b);
extern int IsCollisionObjs(Obj *a, int size, Obj **b);

#endif
