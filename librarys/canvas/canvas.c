//Write by 33kinguspi
#include <stdlib.h>
#include <ncurses.h>

#include "../vector/vector.h"
#include "../graphics/graphics.h"
#include "../sprite/sprite.h"
#include "../object/object.h"
#include "../layer/layer.h"
#include "./canvas.h"

Canvas *NewCanvas(int w, int h)
{
	Canvas *canvas;
	int x, y;

	canvas = (Canvas *)malloc(sizeof(Canvas));
	if (canvas == NULL) return NULL;

	canvas->w = w;
	canvas->h = h;

	canvas->pixel = (Pixel *)malloc(sizeof(Pixel) * w * h);
	if (canvas->pixel == NULL)
	{
		free(canvas);
		return NULL;
	}
	canvas->befor = (Pixel *)malloc(sizeof(Pixel) * w * h);
	if (canvas->befor == NULL)
	{
		free(canvas->pixel);
		free(canvas);
		return NULL;
	}

	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
		{
			canvas->pixel[y * w + x] = NewPixel(' ', 0, 0);
			canvas->befor[y * w + x] = NewPixel(' ', 0, 0);
		}

	return canvas;
}

void FreeCanvas(Canvas *canvas)
{
	free(canvas->pixel);
	free(canvas->befor);
	free(canvas);
}

Canvas *CanvasSetGrp(Canvas *canvas, Grp *grp, Vector pos, Vector view)
{
	int x, y, px, py, cw = canvas->w, ch = canvas->h, gw = grp->w, gh = grp->h;

	for (y = 0; y < gh; y++)
		for (x = 0; x < gw; x++)
		{
			px = x + pos.x - view.x;
			py = y + pos.y - view.y;
			if (px < 0 || px >= cw || py < 0 || py >= ch) continue;
			canvas->pixel[py * cw + px] = MargePixel(canvas->pixel[py * cw + px], grp->pixel[y * gw + x]);
		}
	return canvas;
}

Canvas *CanvasSetSpr(Canvas *canvas, Spr *spr, Vector pos, Vector view)
{
	pos.x *= 2;
	view.x *= 2;
	return CanvasSetGrp(canvas, spr->grp[spr->page], pos, view);
}

Canvas *CanvasSetObj(Canvas *canvas, Obj *obj, Vector view)
{
	return CanvasSetSpr(canvas, obj->spr[obj->spr_num], obj->pos, view);
}

Canvas *CanvasSetLayer(Canvas *canvas, Layer *layer, Vector view)
{
	int n;

	for (n = 0; n < layer->size; n++)
		if (layer->obj[n] == NULL) continue;
		else CanvasSetObj(canvas, layer->obj[n], view);

	return canvas;
}

void DrawCanvas(Canvas *canvas)
{
	int x, y, w = canvas->w, h = canvas->h;

	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
		{
			if (IsEqualPixel(canvas->pixel[y * w + x], canvas->befor[y * w + x]) == 0)
			{
				canvas->befor[y * w + x] = canvas->pixel[y * w + x];
				move(y, x);
				attron(COLOR_PAIR(canvas->pixel[y * w + x].f * 8 + canvas->pixel[y * w + x].b + 1));
				addch(canvas->pixel[y * w + x].ch);
			}
			canvas->pixel[y * w + x] = NewPixel(' ', 0, 0);
		}
	move(0, 0);
}
