//Write by 33kingusp
#include <stdlib.h>

#include "../database/database.h"
#include "../random/random.h"
#include "../vector/vector.h"
#include "./maze.h"

Maze *NewMaze(int w, int h)
{
	Maze *maze;
	int x, y;

	maze = (Maze *)malloc(sizeof(Maze));
	if (maze == NULL) return NULL;

	maze->w = (w * 2) + 1;
	maze->h = (h * 2) + 1;

	maze->cell = (int *)malloc(sizeof(int) * maze->w * maze->h);
	if (maze->cell == NULL)
	{
		free(maze);
		return NULL;
	}

	for (y = 0; y < maze->h; y++)
		for (x = 0; x < maze->w ; x++)
			MazeSetCell(maze, x, y, 0);

	maze->r = NewRandom(0);

	return maze;
}

void FreeMaze(Maze *maze)
{
	free(maze->cell);
	free(maze);
}

Maze *MazeSetCell(Maze *maze, int x, int y, int n)
{
	if (x < 0 || x >= maze->w || y < 0 || y >= maze->h) return maze;

	maze->cell[y * maze->w + x] = n;

	return maze;
}

int MazeGetCell(Maze *maze, int x, int y)
{
	if (x < 0 || x >= maze->w || y < 0 || y >= maze->h) return 0;

	return maze->cell[y * maze->w + x];
}

Maze *MakeMaze(Maze *maze, int seed)
{
	int x, y, n = 0, m, px, py, r, w, h;
	Vector *sp;
	int spsize;
	int *spnum;
	int *roomnum;

	spsize = ((maze->w - 3) / 2) * ((maze->h - 3) / 2);
	if (spsize >= 1);
	{
		spnum = (int *)malloc(sizeof(int) * spsize);
		sp = (Vector *)malloc(sizeof(Vector) * spsize);
	}
	//部屋数
	w = (maze->w - 1) / 2;
	h = (maze->h - 1) / 2;

	roomnum = (int *)malloc(sizeof(int) * w * h);
	maze->enemynum = (int *)malloc(sizeof(int) * w * h);
	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
		{
			roomnum[y * w + x] = y * w + x;
			maze->enemynum[y * w + x] = 0;
		}
	//迷路の外周を壁、それ以外を通路
	for (y = 0; y < maze->h; y++)
		for (x = 0; x < maze->w; x++)
			if (x == 0 || x == maze->w -1 || y == 0 || y == maze->h - 1)
				MazeSetCell(maze, x, y, 1);
	//x, yともに偶数となる座標を壁伸ばし開始座標としてリストアップ
			else if (x % 2 == 0 && y % 2 == 0)
			{
				MazeSetCell(maze, x, y, 0);
				sp[n] = NewVector(x, y);
				spnum[n] = n;
				n++;
			}
			else MazeSetCell(maze, x, y, 0);

	if (spsize <= 0) return maze;

	//開始座標からランダムで座標を取り出し、通路の場合のみ壁伸ばし処理

	maze->r = NewRandom(seed);
	GetRandom(&maze->r);
	Shuffle(&maze->r, spsize, spnum);


	for (n = 0; n < spsize; n++)
	{
		m = spnum[n];
		if (MazeGetCell(maze, sp[m].x, sp[m].y) != 0) continue;	
		do
		{
			x = sp[m].x;
			y = sp[m].y;
			px = x;
			py = y;

			MazeSetCell(maze, x, y, 2);
			r = GetRandom(&maze->r);
			switch (r % 8)
			{
				case 0: case 1: py -=1; y -= 2; break;
				case 2: case 3: py +=1; y += 2; break;
				case 4: case 5: px -=1; x -= 2; break;
				case 6: case 7: px +=1; x += 2; break;
			}
			if (MazeGetCell(maze, x, y) == 2) continue;
			MazeSetCell(maze, px, py, 2);

			if (MazeGetCell(maze, x, y) == 1) break;
			MazeSetCell(maze, x, y, 2);
			
			sp[m].x = x;
			sp[m].y = y;
		} while (1);	

		for (y = 0; y < maze->h; y++)
			for (x = 0; x < maze->h; x++)
				if (MazeGetCell(maze, x, y) == 2)
					MazeSetCell(maze, x, y, 1);
	}

	//スタート、ゴールを決める
	Shuffle(&maze->r, w * h, roomnum);
	maze->start = roomnum[0];
	maze->goal = roomnum[1];
	//敵を設置したりしなかったりする
	for (y = 2; y < h; y++)
	{
		for (x = 2; x < w; x++)
		{
			r = GetRandom(&maze->r);
			switch (r % 5)
			{
				case 0: maze->enemynum[roomnum[y * w + x]] = 0; break;
				case 1: case 4: maze->enemynum[roomnum[y * w + x]] = 1; break;
				case 2: case 3: maze->enemynum[roomnum[y * w + x]] = 2; break;
			}
		}
	}

	free(sp);
	free(spnum);
	free(roomnum);

	return maze;
}

char *MazeToWalldata(Maze maze)
{
	char *data, *room, *rd;
	int x, y, w, h, n, rx, ry;

	w = (maze.w - 1) / 2;
	h = (maze.h - 1) / 2;

	data = (char *)malloc(sizeof(char) * (w * 15) * (h * 15));
	if (data == NULL) return NULL;

	//Maze.cellを部屋番号に変換
	for (y = 1; y < maze.h; y += 2)
	{
		for (x = 1; x < maze.w; x += 2)
		{
			n = 0;
			if (MazeGetCell(&maze, x, y - 1) == 0) n += 1;
			if (MazeGetCell(&maze, x, y + 1) == 0) n += 2;
			if (MazeGetCell(&maze, x - 1, y) == 0) n += 4;
			if (MazeGetCell(&maze, x + 1, y) == 0) n += 8;
			MazeSetCell(&maze, x, y, n);
		}
	}
	//部屋番号をもとにmapを形成
	for (y = 0; y * 2 + 1 < maze.h; y++)
		for (x = 0; x * 2 + 1 < maze.w; x++)
		{
			switch (MazeGetCell(&maze, x * 2 + 1, y * 2 + 1))
			{
				case 0: room = LoadData("Assets/Map/0_0.map"); break;
				case 1: room = LoadData("Assets/Map/1_0.map"); break;
				case 2: room = LoadData("Assets/Map/2_0.map"); break;
				case 3: room = LoadData("Assets/Map/3_0.map"); break;
				case 4: room = LoadData("Assets/Map/4_0.map"); break;
				case 5: room = LoadData("Assets/Map/5_0.map"); break;
				case 6: room = LoadData("Assets/Map/6_0.map"); break;
				case 7: room = LoadData("Assets/Map/7_0.map"); break;
				case 8: room = LoadData("Assets/Map/8_0.map"); break;
				case 9:	room = LoadData("Assets/Map/9_0.map"); break;
				case 10: room = LoadData("Assets/Map/10_0.map"); break;
				case 11: room = LoadData("Assets/Map/11_0.map"); break;
				case 12: room = LoadData("Assets/Map/12_0.map"); break;
				case 13: room = LoadData("Assets/Map/13_0.map"); break;
				case 14: room = LoadData("Assets/Map/14_0.map"); break;
				case 15: room = LoadData("Assets/Map/15_0.map"); break;
			}
			rd = GetLines(room, 15, 15, " \t\n\rdata", ';');
			for (ry = 0; ry < 15; ry++)
				for (rx = 0; rx < 15; rx++)
					data[(ry + (y * 15)) * w * 15 + (rx + (x * 15))] = rd[ry * 15 + rx];
			
			free(room);
			free(rd);
		}
	
	return data;
}
