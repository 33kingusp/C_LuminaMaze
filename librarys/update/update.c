//Write by 33kingusp
#include <stdlib.h>

#include "../object/object.h"
#include "../layer/layer.h"
#include "../stage/stage.h"
#include "./update.h"

Obj *UpdateObj(Obj *obj, Stage *stage)
{
	UpdateSpr(obj->spr[obj->spr_num]);
	if (obj->func != NULL)
	{
		obj->func(obj, stage);
	}
	return obj;
}

Layer *UpdateLayer(Layer *layer, Stage *stage)
{
	int n;

	for (n = 0; n < layer->size; n++)
		if (layer->obj[n] != NULL)
			UpdateObj(layer->obj[n], stage);

	return layer;
}

Stage *UpdateStage(Stage *stage)
{
	UpdateLayer(stage->wall, stage);
	UpdateLayer(stage->enemy, stage);
	UpdateLayer(stage->event, stage);

	return stage;
}

