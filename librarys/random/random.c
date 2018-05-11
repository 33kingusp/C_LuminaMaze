//Write by 33kingusp

#include "random.h"

Random NewRandom(int seed)
{
	Random random;

	random.seed = seed;
	random.q = seed;
	random.value = seed;
	random.value = GetRandom(&random);

	return random;
}

int GetRandom(Random *random)
{	
	random->q = random->q * 1103515245UL + 12345UL;
	random->value = random->q & 2147483647UL;

	return random->value;
}

void Shuffle(Random *random, int size, int *list)
{
	int i = size, j = 0, k = 0;

	while (i > 1)
	{
		j = GetRandom(random) % i;
		i--;
		k = list[i];
		list[i] = list[j];
		list[j] = k;
	}
}
