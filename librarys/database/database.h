//Write by 33kingusp
#ifndef DATABASE_H
#define DATAVASE_H

#include "../object/object.h"
#include "../layer/layer.h"

extern char *LoadData(char *pass);

char *GetLines(char *data, int w, int h, char cut[], char end);

extern void SetupColor();

extern Obj *NewPlayer();
extern Obj *NewEnemy(int n);
extern Obj *NewTreasure();

extern Obj *NewStageObj(int n);
extern Layer *NewStageWall(char *data);

extern Obj *NewTitle();
extern Obj *NewGameover();
#endif
