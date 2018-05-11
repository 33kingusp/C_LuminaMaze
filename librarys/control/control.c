//Write by 33kingusp
#include <ncurses.h>

#include "../vector/vector.h"
#include "../object/object.h"
#include "../layer/layer.h"
#include "../input/input.h"
#include "./control.h"

Obj *ControlPlayer(Obj *player, int input, Layer *wall)
{
	Vector p = player->pos;

	switch (input)
	{
		case IN_UP:    MoveObj(player, NewVector( 0.0, -1.0)); player->spr_num = 1; break;
		case IN_DOWN:  MoveObj(player, NewVector( 0.0, +1.0)); player->spr_num = 0; break;
		case IN_LEFT:  MoveObj(player, NewVector(-1.0,  0.0)); break;
		case IN_RIGHT: MoveObj(player, NewVector(+1.0,  0.0)); break;
		default: MoveObj(player, NewVector(0.0, 0.0)); break;
	}

	if (IsCollisionObjs(player, wall->size, wall->obj))
		GotoObj(player, p);	

	return player;
}
