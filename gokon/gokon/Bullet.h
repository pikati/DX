#pragma once
#include "Object.h"
#include "main.h"
class Bullet : public Object
{
private:
	ATTRBUTE	m_attr;
	DIR			m_dir;
	int			m_atk;
	void Move();
public:
	Bullet(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir);
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir);
	void Update();
	void Draw(LPDIRECT3DTEXTURE9 texture);
	void Finalize();
	int  HitDamage();
	void Erase();
	float GetX() override;
	float GetY() override;
	float GetW() override;
	float GetH() override;
	void SetX(float x) override;
	void Sety(float y) override;
	void SetW(float w) override;
	void SetH(float h) override;
};

