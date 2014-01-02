#pragma once
class Vector
{
public:
	Vector(void);
	~Vector(void);
	Vector(float, float);
	float X;
	float Y;
	float GetMagnitude(void);
	void Add(Vector);
	void Subtract(Vector);
	void Multiply(float);
	void Divide(float);
	float DotProduct(Vector);
	Vector Project(Vector);
	Vector UnitVector(void);
	Vector operator+(Vector);
	Vector operator-(Vector);
	float GetDistance(Vector);
	void Rotate(Vector, float, float);
	//void BounceBallOffWall(, Vector);
};

