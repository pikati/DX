#include "Collision.h"
#include <math.h>


template<typename T>
bool Collision::IsCollisionEnter(T a, T b) {
	if (abs(a.x - b.x) < (a.w / 2 + b.w / 2)) {
		if (abs(a.y - b.y) < (a.h / 2 + b.h / 2)) {
			return true;
		}
	}
	return false;
}


template<typename T>
DIR Collision::CollisionDirection(T a, T b) {
	if (a.x > b.x) {
		return DIR_RIGHT;
	}
	else if (a.x <= b.x) {
		return DIR_LEFT;
	}
	else if (a.y <= b.y) {
		return DIR_DOWN;
	}
	else {
		return DIR_UP;
	}
}