//Write by 33kingusp
#ifndef CANVAS_H
#define CANVAS_H

typedef struct
{
	int w, h;
	Pixel *pixel, *befor;
} Canvas;

extern Canvas *NewCanvas(int w, int h);
extern void FreeCanvas(Canvas *canvas);

extern Canvas *CanvasSetGrp(Canvas *canvas, Grp *grp, Vector pos, Vector view);
extern Canvas *CanvasSetSpr(Canvas *canvas, Spr *spr, Vector pos, Vector view);
extern Canvas *CanvasSetObj(Canvas *canvas, Obj *obj, Vector view);
extern Canvas *CanvasSetLayer(Canvas *canvas, Layer *layer, Vector view);

extern void DrawCanvas(Canvas *canvas);

#endif
