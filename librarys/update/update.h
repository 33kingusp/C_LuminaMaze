//Write by 33kingusp
#ifndef UPDATE_H
#define UPDATE_H

#include "../object/object.h"
#include "../layer/layer.h"
#include "../stage/stage.h"
#include "./update.h"

extern Obj *UpdateObj(Obj *obj, Stage *stage);
extern Layer *UpdateLayer(Layer *layer, Stage *stage);
extern Stage *UpdateStage(Stage *stage);

#endif
