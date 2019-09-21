#define _CRT_SECURE_NO_WARNINGS
#include "Collision.h"
#include <math.h>
#include "Utility.h"


bool Collision::IsCollisionEnter(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh) {
	//MyOutputDebugString("�����̎�:%f < %f  �E���̎�:%f < %f\n", (ax + aw / 2) - (bx + bw / 2), (aw / 2 + bw / 2), fabs(ay + ah / 2) - (by + bh / 2), (ah / 2 + bh / 2));
	//MyOutputDebugString("ax:%f aw:%f  ay:%f ah:%f\n", ax, aw + ax, ay, ay + ah);
	if (fabs((ax + aw / 2) - (bx + bw / 2)) < (aw / 2 + bw / 2)) {
		if (fabs((ay + ah / 2) - (by + bh / 2)) < (ah / 2 + bh / 2)) {
			return true;
		}
	}
	return false;
}


DIR Collision::CollisionDirection(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh) {


	/*�v���C���[�̉E�[����b�̍��[�̂ق����������v���C���[�̍��[����b�̉E�[���傫���Ƃ�*/
	if (ax + aw - 30.0f > bx && ax + 30.0f < bx + bw) {
		/*b�̉��������v���C���[�̏㑤����ɂ���Ab�̏㑤�����v���C���[�̉��������ɂ��鎞*/
		if (by + bh > ay && by < ay) {
			//MyOutputDebugString("�E���̎�:%f > %f  �����̎�:%f < %f\n", ax + aw - 30.0f, bx, ax + 30.0f, bx + bw);
			return DOWN;
		}
		else if (by < ay + ah && by + bh > ay + ah) {
			//MyOutputDebugString("�E���̎�:%f > %f  �����̎�:%f < %f\n", by, ay + ah, by + bh, ay + ah);
			return UP;
		}
	}
	if ((ay < by + bh && ay > by) || (ay < by && by < ay + ah)) {
		/*b�̍��������v���C���[�̉E�����傫������b�̍��������v���C���[�̍�����������*/
		if (bx < ax + aw && ax < bx) {
			return LEFT;
		}
		else if (ax < bx + bw && bx < ax) {
			return RIGHT;
		}
	}
	//MyOutputDebugString("�E���̎�:%f > %f  �����̎�:%f < %f\n", ax + aw - 30.0f, bx, ax + 30.0f, bx + bw);
	return NON;
}