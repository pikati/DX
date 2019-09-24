#pragma once
#include "Object.h"
#include "Texture.h"
class Scaffold :
	public Object
{
private:
	float m_firstX;
	bool  m_aria;
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir);
	void Update();
	void Draw(LPDIRECT3DTEXTURE9 texture);
	void Finalize();
	float GetX() override;
	float GetFirstX();
	float GetY() override;
	float GetW() override;
	float GetH() override;
	void SetX(float x) override;
	void Sety(float y) override;
	void SetW(float w) override;
	void SetH(float h) override;
};

