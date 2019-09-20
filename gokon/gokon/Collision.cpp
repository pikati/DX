#define _CRT_SECURE_NO_WARNINGS
#include "Collision.h"
#include <math.h>
#include "Utility.h"


bool Collision::IsCollisionEnter(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh, int i) {
	//MyOutputDebugString("左側の式:%f < %f  右側の式:%f < %f\n", (ax + aw / 2) - (bx + bw / 2), (aw / 2 + bw / 2), fabs(ay + ah / 2) - (by + bh / 2), (ah / 2 + bh / 2));
	MyOutputDebugString("ax:%f aw:%f  ay:%f ah:%f\n", ax, aw + ax, ay, ay + ah);
	if (i == 4)
		MyOutputDebugString("bx:%f bw:%f  by:%f bh:%f\n", bx, bw + bx, by, by + bh);
	if (fabs((ax + aw / 2) - (bx + bw / 2)) < (aw / 2 + bw / 2)) {
		if (fabs((ay + ah / 2) - (by + bh / 2)) < (ah / 2 + bh / 2)) {
			return true;
		}
	}
	return false;
}


DIR Collision::CollisionDirection(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh) {


	/*プレイヤーの右端よりもbの左端のほうが小さくプレイヤーの左端よりもbの右端が大きいとき*/
	if (ax + aw - 30.0f > bx && ax + 30.0f < bx + bw) {
		/*bの下側よりもプレイヤーの上側が上にあり、bの上側よりもプレイヤーの下側が下にある時*/
		if (by + bw < ay && by > ay) {
			//MyOutputDebugString("右側の式:%f > %f  左側の式:%f < %f\n", ax + aw - 30.0f, bx, ax + 30.0f, bx + bw);
			return DOWN;
		}
		else if (by < ay + ah && by + bh > ay + ah) {
			//MyOutputDebugString("右側の式:%f > %f  左側の式:%f < %f\n", by, ay + ah, by + bh, ay + ah);
			return UP;
		}
	}
	if (ay < by + bh && ay + ah > by) {
		/*bの左側よりもプレイヤーの右側が大きいかつbの左側よりもプレイヤーの左側が小さい*/
		if (bx < ax + aw && ax < bx) {
			return LEFT;
		}
		else if (bx + bw < ax && ax + aw > bx + bw) {
			return RIGHT;
		}
	}
	//MyOutputDebugString("右側の式:%f > %f  左側の式:%f < %f\n", ax + aw - 30.0f, bx, ax + 30.0f, bx + bw);
	return NON;
}