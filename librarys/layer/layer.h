//Write by 33kingusp
#ifndef LAYER_H
#define LAYER_H

#include "../object/object.h"

typedef struct
{
	int size;
	Obj **obj;
} Layer;

extern Layer *NewLayer(int size);
extern void FreeLayer(Layer *layer);
extern void DeleteLayer(Layer *layer);

extern Layer *LayerSetObj(Layer *layer, int n, Obj *obj);
extern Obj *LayerGetObj(Layer *layer, int n);

#endif
