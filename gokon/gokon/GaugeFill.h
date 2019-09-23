#pragma once
#include "Object.h"

enum KINDGAUGE
{
	HP,
	MP
};

class GaugeFill : public Object
{
private:
	int m_max;
	int m_now;
	float m_length;
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) override;
	void Update() override;
	void Draw(LPDIRECT3DTEXTURE9 texture) override;
	void Finalize() override;
	float GetX() override;
	float GetY() override;
	float GetW() override;
	void SetX(float x) override;
	void Sety(float y) override;
	void SetW(float w) override;
	void SetH(float h) override;
	float GetH() override;
	void SetAttr(KINDGAUGE kind);
	void SetValue(int max, int now);
	void SetPosition(float x, float y);
	void SetLength(float length);
};

