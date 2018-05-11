//Write by 33kingusp
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "../graphics/graphics.h"
#include "../sprite/sprite.h"
#include "../object/object.h"
#include "../layer/layer.h"
#include "../stage/stage.h"
#include "../enemy/enemy.h"

#include "./database.h"

char *LoadData(char *pass)
{
	FILE *fp;
	char *data;
	int n = 0, c = 0;

	if ((fp = fopen(pass, "r")) == NULL) return NULL;

	data = (char *)malloc(sizeof(char) * 4096);
	
	while ((c = fgetc(fp)) != EOF)
	{
		*data = c;
		data++;
		n++;
	}
	fclose(fp);

	return data - n;
}

char *GetLines(char *data, int w, int h, char cut[], char end)
{
	char *lines;
	int n = 0, i, size = w * h;

	lines = (char *)malloc(sizeof(char) * (w * h + 64));

	while (*data != end)
	{
		i = 0;
		while (*data != cut[i])
		{
			if (cut[i] == '\0')
			{
				*lines = *data;
				lines++;
				size--;
				n++;
				break;
			}
			i++;
		}
		data++;
	}
	return lines - n;
}

void SetupColor()
{
	int f, b;

	start_color();

	for (b = 0; b < 8; b++)
		for (f = 0; f < 8; f++)
			init_pair(f * 8 + b + 1, f ,b);
}

Obj *NewPlayer()
{
	char *data;
	Obj *obj;

	obj = NewObj(2);
	
	ObjSetSpr(obj, 0, NewSpr(1));
	data = LoadData("Assets/Grp/player_0.grp");
	SprSetGrp(obj->spr[0], 0, DataToGrp(data));
	
	ObjSetSpr(obj, 1, NewSpr(1));
	data = LoadData("Assets/Grp/player_1.grp");
	SprSetGrp(obj->spr[1], 0, DataToGrp(data));

	//obj->spr_num = 1;

	obj->size = NewVector(4, 4);

	free(data);

	return obj;
}

Obj *NewEnemy(int n)
{
	char *data;
	Obj *obj;

	obj = NewObj(1);
	ObjSetSpr(obj, 0, NewSpr(1));

	switch (n)
	{
		case 0:	data = LoadData("Assets/Grp/guardian_0.grp"); break;
		case 1:	data = LoadData("Assets/Grp/guardian_1.grp"); break;
		default: LoadData("Assets/Grp/default.grp"); break;
	}

	SprSetGrp(obj->spr[0], 0, DataToGrp(data));

	obj->size = NewVector(4, 4);

	obj->func = &MoveEnemy;	
	obj->num = n;

	free(data);

	return obj;
}

Obj *NewTreasure()
{
	char *data;
	Obj *obj;

	obj = NewObj(1);
	ObjSetSpr(obj, 0, NewSpr(1));

	data = LoadData("Assets/Grp/treasure.grp");

	SprSetGrp(obj->spr[0], 0, DataToGrp(data));

	obj->size = NewVector(4, 4);
	
	free(data);

	return obj;

}

Obj *NewStageObj(int n)
{
	char *data;
	Obj *obj;

	obj = NewObj(1);
	ObjSetSpr(obj, 0, NewSpr(1));

	data = LoadData("Assets/Grp/block.grp");

	SprSetGrp(obj->spr[0], 0, DataToGrp(data));

	obj->size = NewVector(4, 4);

	free(data);

	return obj;
}

Obj *NewTitle()
{
	char *data;
	Obj *obj;

	obj = NewObj(1);
	ObjSetSpr(obj, 0, NewSpr(1));

	data = LoadData("Assets/Grp/title.grp");
	
	SprSetGrp(obj->spr[0], 0, DataToGrp(data));

	free(data);

	return obj;

}

Obj *NewGameover()
{
	char *data;
	Obj *obj;

	obj = NewObj(1);
	ObjSetSpr(obj, 0, NewSpr(1));

	data = LoadData("Assets/Grp/gameover.grp");
	
	SprSetGrp(obj->spr[0], 0, DataToGrp(data));

	free(data);

	return obj;

}
