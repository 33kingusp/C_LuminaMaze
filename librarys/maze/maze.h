//Write by 33kingusp
#ifndef MAZE_H
#define MAZE_H

#include "../random/random.h"

typedef struct
{
	//サイズ
	int w, h;
	int *cell;
	//部屋番号
	int start;
	int goal;
	int *enemynum;
	Random r;
} Maze;

extern Maze *NewMaze(int w, int h);
extern void FreeMaze(Maze *maze);

extern Maze *MazeSetCell(Maze *maze, int x, int y, int n);
extern int MazeGetCell(Maze *maze, int x, int y);

extern Maze *MakeMaze(Maze *maze, int seed);

extern char *MazeToWalldata(Maze maze);

#endif
