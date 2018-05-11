//Write by 33ingusp

#include <math.h>

#include "./vector.h"

Vector NewVector(double x, double y)
{
	Vector v;

	v.x = x;
	v.y = y;

	return v;
}

Vector SumVector(Vector a, Vector b)
{
	Vector v = NewVector(0, 0);

	v.x = a.x + b.x;
	v.y = a.y + b.y;

	return v;
}

Vector DifVector(Vector a, Vector b)
{
	Vector v = NewVector(0, 0);

	v.x = a.x - b.x;
	v.y = a.y - b.y;

	return v;
}

Vector MulVector(Vector a, double b)
{
	Vector v = NewVector(0, 0);

	v.x = a.x * b;
	v.y = a.y * b;

	return v;
}

Vector DivVector(Vector a, double b)
{
	Vector v = NewVector(0, 0);

	v.x = a.x / b;
	v.y = a.y / b;

	return v;
}

Vector AdsVector(Vector a)
{
	Vector v = NewVector(0, 0);

	v.x = fabs(a.x);
	v.y = fabs(a.y);

	return v;
}

