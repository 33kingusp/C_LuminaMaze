//Write by 33kingusp
#include <time.h>

#include "../random/random.h"
#include "../vector/vector.h"
#include "../object/object.h"
#include "../stage/stage.h"
#include "./enemy.h"

void MoveEnemy(Obj *obj, Stage *stage)
{
	Vector p;
	p = obj->pos;
	Random r;
	r = NewRandom(time(NULL));

	switch (obj->num)
	{
		case 0:
			obj->speed = 1.2;
			switch (obj->state)
			{
				case 0: MoveObj(obj, NewVector(0, -obj->speed)); break;
				case 1: MoveObj(obj, NewVector(+obj->speed, 0)); break;
				case 2: MoveObj(obj, NewVector(0, +obj->speed)); break;
				case 3: MoveObj(obj, NewVector(-obj->speed, 0)); break;
				default: obj->state = 0; break;
			}
			break;
		case 1:
			obj->speed = 1.0;
			switch (obj->state)
			{
				case 0: case 7:
					MoveObj(obj, NewVector(0, -obj->speed));
					obj->count--;
				break;
				case 1: case 6:
					MoveObj(obj, NewVector(+obj->speed, 0));	
					obj->count--;
				break;
				case 2: case 5:
					MoveObj(obj, NewVector(0, +obj->speed));
					obj->count--;
				break;
				case 3: case 4:
					MoveObj(obj, NewVector(-obj->speed, 0));
					obj->count--;
				break;
				default: obj->state = 0; break;
			}
			if (obj->count <= 0)
			{
				obj->state = GetRandom(&r) % 8;
				obj->count = GetRandom(&r) % 10 + 5;
			}
			break;
	}
	if (IsCollisionObjs(obj, stage->wall->size, stage->wall->obj))
	{
		GotoObj(obj, p);
		obj->state++;
	}
}
