#include "Vector.h"
#include <math.h>


Vector::Vector(void)
{
	X = 0;
	Y = 0;
}


Vector::~Vector(void)
{
}

Vector::Vector(float x, float y)
{
	X = x;
	Y = y;
}


float Vector::GetMagnitude()
{
	return sqrt(pow(X,2) + pow(Y,2));
}

//Adds v to this
void Vector::Add(Vector v)
{
	X += v.X;
	Y += v.Y;
}

//Subtract v form this
void Vector::Subtract(Vector v)
{
	X -= v.X;
	Y -= v.Y;
}

//Multiply X and Y by f
void Vector::Multiply(float f)
{
	X *= f;
	Y *= f;
}

//Divide X and Y by f
void Vector::Divide(float f)
{
	X /= f;
	Y /= f;
}

//Return dot product with v
float Vector::DotProduct(Vector v)
{
	return (X * v.X) + (Y * v.Y);
}

//Projection of V onto this vector
Vector Vector::Project(Vector v)
{
	Vector p(X,Y);
	p.Divide(GetMagnitude());
	p.Multiply(DotProduct(v) / GetMagnitude());
	
	return p;
}

//Return unit vector of this
Vector Vector::UnitVector()
{
	Vector p(X,Y);
	p.Divide(GetMagnitude());
	return p;
}

//Return sum of this and v
Vector Vector::operator+(Vector v)
{
	return Vector(X + v.X, Y + v.Y);
}

//Return subtraction of this and v
Vector Vector::operator-(Vector v)
{
	return Vector(X - v.X, Y - v.Y);
}

//Get distance between this and v
float Vector::GetDistance(Vector v)
{
	return sqrt(pow((X - v.X), 2) + pow((Y - v.Y),2));
}

//Rotates this around vector o, given sin and cosine values
void Vector::Rotate(Vector o, float s, float c)
{
	X = (c * (X-o.X)) - (s * (Y - o.Y)) + o.X;
	Y = (s * (X-o.X)) + (c * (Y - o.Y)) + o.Y;
}