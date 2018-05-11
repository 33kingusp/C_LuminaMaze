//Write by 33kingusp
#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
	double x;
	double y;
} Vector;

extern Vector NewVector(double x, double y);

extern Vector SumVector(Vector a, Vector b);
extern Vector DifVector(Vector a, Vector b);
extern Vector MulVector(Vector a, double b);
extern Vector DivVector(Vector a, double b);
extern Vector AdsVector(Vector a);

#endif
