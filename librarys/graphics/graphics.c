//Write by 33kingusp

#include <stdlib.h>
#include <string.h>

#include "../pixel/pixel.h"
#include "./graphics.h"

Grp *NewGrp(int w, int h)
{
	Grp *grp;

	grp = (Grp *)malloc(sizeof(Grp));
	if (grp == NULL) return NULL;

	grp->w = w;
	grp->h = h;

	grp->pixel = (Pixel *)malloc(sizeof(Pixel) * w * h);
	if (grp->pixel == NULL)
	{
		free(grp);
		return NULL;
	}

	return grp;
}

void FreeGrp(Grp *grp)
{
	free(grp->pixel);
	free(grp);
}

Grp *DataToGrp(char *data)
{
	Grp *grp;
	int w = 1, h = 1;
	Pixel *pixel = NULL;

	char *arg;
	char cut[] = {" \t\n\r"};
	int x, y;

	arg = strtok(data, cut);
	if (strcmp(arg, "grp")) return NULL;

	while ((arg = strtok(NULL, cut)))
	{
		if (strcmp(arg, "w") == 0)
			w = atoi(strtok(NULL, cut));	
		else if (strcmp(arg, "h") == 0)
			h = atoi(strtok(NULL, cut));
		else if (strcmp(arg, "pixel") == 0)
		{
				pixel = (Pixel *)malloc(sizeof(Pixel) * w * h);
				if (pixel == NULL) return NULL;
		}
		else if (strcmp(arg, "ch") == 0)
		{
			for (y = 0; y < h; y++)
			{
				arg = strtok(NULL, "\t\n\r");
				for (x = 0; x < w; x++)
					pixel[y * w + x].ch = arg[x];
			}
		}
		else if (strcmp(arg, "f_color") == 0)
		{
			for (y = 0; y < h; y++)
			{
				arg = strtok(NULL, "\t\n\r");
				for (x = 0; x < w; x++)
					pixel[y * w + x].f = arg[x] - '0';
			}
		}
		else if (strcmp(arg, "b_color") == 0)
		{
			for (y = 0; y < h; y++)
			{
				arg = strtok(NULL, "\t\n\r");
				for (x = 0; x < w; x++)
					pixel[y * w + x].b = arg[x] - '0';
			}
		}
	}

	grp = NewGrp(w, h);
	grp->pixel = pixel;

	return grp;
}
