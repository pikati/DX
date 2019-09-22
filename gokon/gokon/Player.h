#pragma once
#include <vector>
#include "Animation.h"
#include "Texture.h"
#include "Object.h"
#include "Bullet.h"

#define JUMP_POWER -15.0f
/*テクスチャ関係*/
class Player : public Object
{
private:
	Texture				m_texture;
	Animation			anim;
	std::vector<Bullet> m_bullet;
	DIR					m_oldDir;
	ATTRBUTE			m_attr;
	float				m_oldY;
	float				m_upPower;
	bool				m_isGround;
	void Inversion();
	void TextureInverse();
	void Attack();
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) override;
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

