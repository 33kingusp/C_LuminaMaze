//Write by 33kingusp
#ifndef STAGE_H
#define STAGE_H

#include "../vector/vector.h"
#include "../layer/layer.h"
#include "../maze/maze.h"

typedef struct
{
	int w, h;
	Maze *maze;

	char *walldata;
	Layer *wall;
	Layer *event;
	Layer *enemy;

	Vector startpos;
	Vector goalpos;
} Stage;

extern Stage *NewStage(int w, int h);
extern void FreeStage(Stage *stage);
extern void DeleteStage(Stage *stage);

extern Stage *MakeStage(Stage *stage, int seed);
extern Layer *DataToWall(Stage *stage);

#endif 
