#pragma once
#include "Vector2.h"

struct Rectangle
{
	Vector2 position;
	int width, height;
};

class Collision
{
private:
public:
	Collision();
	~Collision();

	static bool DetectRectCollision(const Rectangle& rect1, const Rectangle& rect2);
};