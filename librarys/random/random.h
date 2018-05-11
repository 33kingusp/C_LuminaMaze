//Write by 33kingusp
#ifndef RANDOM_H
#define RANDOM_H

typedef struct
{
	int seed, q, value;
} Random;

extern Random NewRandom(int seed);

extern int GetRandom(Random *random);

extern void Shuffle(Random *random, int size, int *list);

#endif
