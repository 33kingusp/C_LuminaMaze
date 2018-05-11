//Write by 33kingusp
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

//#include "./librarys/graphics/graphics.h"
#include "./librarys/input/input.h"
#include "./librarys/control/control.h"
#include "./librarys/database/database.h"
#include "./librarys/random/random.h"
#include "./librarys/maze/maze.h"
#include "./librarys/object/object.h"
#include "./librarys/layer/layer.h"
#include "./librarys/stage/stage.h"
#include "./librarys/update/update.h"
#include "./librarys/canvas/canvas.h"

void Start()
{
	initscr();
	SetupInput();
	SetupColor();
	//キーストロークを設定：不具合が起こりやすいので廃止
	//system("xset r rate 1 33");
}

int Title()
{
	//return
	int r = 'e';
	//Canvas
	int w, h;
	getmaxyx(stdscr, h, w);
	Canvas *canvas;
	canvas = NewCanvas(w, h);
	//Layer
	Vector view = NewVector(0, 0);
	Layer *mob;
	mob = NewLayer(8);
	//Object
	Obj *player, *tre;
	Obj *ti;

	player = NewPlayer();
	tre = NewTreasure();
	ti = NewTitle();

	LayerSetObj(mob, 0, player);
	LayerSetObj(mob, 1, tre);
	LayerSetObj(mob, 2, ti);
	
	//Input
	int i = IN_NONE;

	GotoObj(player, NewVector(-8, 0));
	GotoObj(tre, NewVector(24, 11));	
	GotoObj(ti, NewVector(0, 0));

	while(i != IN_EXIT)
	{
		i = Input();
		
		if (i == IN_A)
		{
			r = 'a';
			break;
		}
		else if(i == IN_B) break;

		//Update
		
		//Drow
		view = DifVector(DifVector(ti->pos, NewVector(-16, 0)), NewVector(w / 4, h / 4));
		CanvasSetLayer(canvas, mob, view);
		DrawCanvas(canvas);
		attrset(0);
		mvprintw(h / 2 + 10, w / 2 - 10, "[z]Start");
		mvprintw(h / 2 + 11, w / 2 - 10, "[x]Exit ");
	}
	erase();
	refresh();
	FreeCanvas(canvas);
	DeleteLayer(mob);
	usleep(20000);
	return r;
}

int Gameover(int s)
{
	//return
	int r = 'e';
	//Canvas
	int w, h;
	getmaxyx(stdscr, h, w);
	Canvas *canvas;
	canvas = NewCanvas(w, h);
	//Layer
	Vector view = NewVector(0, 0);
	Layer *mob;
	mob = NewLayer(8);
	//Object
	Obj *ti;

	ti = NewGameover();

	LayerSetObj(mob, 0, ti);
	
	//Input
	int i = IN_NONE;

	GotoObj(ti, NewVector(0, 0));

	//キーを離すまで待つ
	while(Input() != IN_NONE)
	{
		
	}

	while(i != IN_EXIT)
	{
		i = Input();
		
		if (i == IN_A)
		{
			break;
		}
		//Update
		
		//Drow
		view = DifVector(DifVector(ti->pos, NewVector(-16, 0)), NewVector(w / 4, h / 4));
		CanvasSetLayer(canvas, mob, view);
		DrawCanvas(canvas);
		attrset(0);
		mvprintw(h / 2 + 9, w / 2 - 10, "You Creared Maze : %d", s);
		mvprintw(h / 2 + 10, w / 2 - 11, "[z]Title");
	}
	erase();
	refresh();
	FreeCanvas(canvas);
	DeleteLayer(mob);
	usleep(20000);
	return r;
}

int Update(int s, int sw, int sh)
{
	//return
	int r = 'e';
	//Canvas
	int w, h;
	getmaxyx(stdscr, h, w);
	Canvas *canvas;
	canvas = NewCanvas(w, h);
	//Layer
	Vector view = NewVector(0, 0);
	Layer *mob;
	mob = NewLayer(8);
	//Stage	
	Stage *stage;
	stage = NewStage(sw, sh);
	MakeStage(stage, s);
	//Object
	Obj *player;

	player = NewPlayer();

	LayerSetObj(mob, 0, player);
	
	//Input
	int i = IN_NONE;

	GotoObj(player, stage->startpos);


	while(i != IN_EXIT)
	{
		i = Input();

		//Update
		UpdateObj(player, stage);
		UpdateStage(stage);
		//control
		ControlPlayer(player, i, stage->wall);

		//clear
		if (IsCollisionObj(player, LayerGetObj(stage->event, 0))) 
		{
			r = 'n';
			break;
		}
		//damage
		if (IsCollisionObjs(player, stage->enemy->size, stage->enemy->obj))
		{
			r = 'd';
			break;
		}
		
		//Drow
		view = DifVector(player->pos, NewVector(w / 4, h / 4));
		CanvasSetLayer(canvas, stage->wall, view);
		CanvasSetLayer(canvas, stage->event, view);
		CanvasSetLayer(canvas, stage->enemy, view);
		CanvasSetLayer(canvas, mob, view);
		DrawCanvas(canvas);
		move(h-1, 0);
		attrset(0);
		printw("WASD or Arrow:move Q:exit");
		usleep(10000);
	}
	erase();
	refresh();
	FreeCanvas(canvas);
	DeleteLayer(mob);
	DeleteStage(stage);
	usleep(20000);
	return r;
}

void End()
{
	endwin();
	
	//system("xset r rate 500 33");
}

int main()
{
	int s = 0, n = 0, sw = 3, sh = 3;
	Start();
	while(n != 'e')
	{
		if (Input() != IN_NONE) continue;
		n = Title();
		s = 0;
		sw = 3;
		sh = 3;
		while (n != 'e')
		{
			if (n == 'a' || n == 'n') n = Update(s, sw, sh);
			else break;
			if (n == 'd')
			{
				Gameover(s);
				n = 0;
				break;
			}
			else s++;
			if (s >= 5)
			{
				s = 0;
				if (sw <= sh) sw++;
				else sh++;
				if (sw >= 100) sw = 100;
				if (sh >= 100) sh = 100;
				
			}
		}
	}
	End();
	return 0;
}
