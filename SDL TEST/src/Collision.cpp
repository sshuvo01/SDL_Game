#include "Collision.h"
#include <cmath>

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::DetectRectCollision(const Rectangle & rect1, const Rectangle & rect2)
{
	if (rect1.position.X() < rect2.position.X() + rect2.width 
		&& rect1.position.X() + rect1.width > rect2.position.X() 
		&& rect1.position.Y() < rect2.position.Y() + rect2.height 
		&& rect1.position.Y() + rect1.height > rect2.position.Y()) 
	{
		return true;
	}

	return false;
}
