//Write by 33kingusp
#include <stdlib.h>
#include <string.h>

#include "../database/database.h"
#include "../object/object.h"
#include "../layer/layer.h"
#include "./stage.h"

Stage *NewStage(int w, int h)
{
	Stage *stage;

	stage = (Stage *)malloc(sizeof(Stage));
	if (stage == NULL) return NULL;

	stage->w = w;
	stage->h = h;

	stage->maze = NewMaze(w, h);
	stage->walldata = NULL;
	stage->wall = NULL;
	
	stage->event = NewLayer(w * h);	
	stage->enemy = NewLayer(w * h);	

	stage->startpos = NewVector(0, 0);
	stage->goalpos = NewVector(0, 0);

	return stage;
}

void FreeStage(Stage *stage)
{
	FreeMaze(stage->maze);
	free(stage->walldata);
	FreeLayer(stage->wall);
	FreeLayer(stage->enemy);
	free(stage);
}

void DeleteStage(Stage *stage)
{
	FreeMaze(stage->maze);
	free(stage->walldata);
	DeleteLayer(stage->wall);
	DeleteLayer(stage->event);
	DeleteLayer(stage->enemy);
	free(stage);
}

Stage *MakeStage(Stage *stage, int seed)
{
	int x, y, w, h;
	Vector p;

	stage->maze = NewMaze(stage->w, stage->h);
	MakeMaze(stage->maze, seed);

	stage->walldata = MazeToWalldata(*stage->maze);
	stage->wall = DataToWall(stage);
	//スタート位置、ゴール位置決定
	w = (stage->maze->w - 1) / 2;
	h = (stage->maze->h - 1) / 2;

	x = ((stage->maze->start % w) * 15 + 7) * 8;
	y = ((stage->maze->start / w) * 15 + 7) * 8;

	stage->startpos = NewVector(x, y);

	x = ((stage->maze->goal % w) * 15 + 7) * 8;
	y = ((stage->maze->goal / w) * 15 + 7) * 8;

	stage->goalpos = NewVector(x, y);
	//宝箱
	LayerSetObj(stage->event, 0, NewTreasure());
	GotoObj(LayerGetObj(stage->event, 0), stage->goalpos);
	//敵
	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
		{
			switch (stage->maze->enemynum[y * w + x])
			{
				case 1: LayerSetObj(stage->enemy, y * w + x, NewEnemy(0)); break;
				case 2: LayerSetObj(stage->enemy, y * w + x, NewEnemy(1)); break;
				default: continue; break;
			}
			p = NewVector((((y * w + x) % w) * 15 + 7) * 8,(((y * w + x) / w) * 15 + 7) * 8 );
			GotoObj(LayerGetObj(stage->enemy, y * w + x), p);
		}

	return stage;
}

Layer *DataToWall(Stage *stage)
{
	int x, y, w, h, n = 0;

	w = stage->w * 15;
	h = stage->h * 15;

	stage->wall = NewLayer(w * h);

	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
			if (stage->walldata[y * w + x] == '1')
			{
				LayerSetObj(stage->wall, n, GotoObj(NewStageObj(1), NewVector(x * 8, y * 8)));
				n++;
			}

	return stage->wall;
}
