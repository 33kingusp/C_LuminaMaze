//Write by 33kingusp
#include <stdlib.h>
#include <ncurses.h>
#include "../object/object.h"
#include "./layer.h"

Layer *NewLayer(int size)
{
	Layer *layer;
	int n;

	layer = (Layer *)malloc(sizeof(Layer));
	if (layer == NULL) return NULL;

	layer->size = size;

	layer->obj = (Obj **)malloc(sizeof(Layer*) * size);
	if (layer->obj == NULL)
	{
		free(layer);
		return NULL;
	}

	for (n = 0; n < size; n++)
		layer->obj[n] = NULL;

	return layer;
}

void FreeLayer(Layer *layer)
{
	free(layer->obj);
	free(layer);
}

void DeleteLayer(Layer *layer)
{
	int n = 0;

	for (n = 0; n < layer->size; n++)
		if (layer->obj[n] != NULL)
			DeleteObj(layer->obj[n]);

	FreeLayer(layer);
}

Layer *LayerSetObj(Layer *layer, int n, Obj *obj)
{
	if(n < layer->size)
		layer->obj[n] = obj;

	return layer;
}

Obj *LayerGetObj(Layer *layer, int n)
{
	if(n >= layer->size) return NULL;
	return layer->obj[n];
}
