#pragma once
#include "Animation.h"
#include "Texture.h"
#include "Object.h"

#define JUMP_POWER -15.0f
/*テクスチャ関係*/
class Player : public Object
{
private:
	Texture				texture;
	Animation			anim;
	DIR					m_oldDir;
	float				m_oldY;
	float				m_upPower;
	bool				m_isGround;
	void Gravity();
	void Inversion() override;
	void TextureInverse() override;
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) override;
	void Update() override;
	void Draw(LPDIRECT3DTEXTURE9 texture) override;
	void Finalize() override;
	void UpdateJump();
	float GetX() override;
	float GetY() override;
	float GetW() override;
	float GetH() override;
	void Grounded(bool isGround);
	void Jump();
	void SetY(float y);
	void SetX(DIR dir);
};

