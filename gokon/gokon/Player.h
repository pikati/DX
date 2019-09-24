#pragma once
#include <vector>
#include "Animation.h"
#include "Texture.h"
#include "Object.h"
#include "Bullet.h"

/*テクスチャ関係*/
class Player : public Object
{
private:
	Texture				m_texture;
	Animation			anim;
	std::vector<Bullet> m_bullet;
	float				m_upPower;
	bool				m_isGround;
	const float			JUMP_POWER = -15.0f;
	int					m_mhp;
	int					m_hp;
	int					m_mmp;
	int					m_mp;
	int					m_atk;
	float				m_move;
	int					m_exp;
	void TextureInverse();
	void Attack();
	void CheckHP();
	void CheckBullet();
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) override;
	void Update() override;
	void Draw(LPDIRECT3DTEXTURE9 texture) override;
	void Finalize() override;
	void UpdateJump();
	float GetX() override;
	float GetFirstX();
	float GetY() override;
	float GetW() override;
	float GetH() override;	
	void SetX(float x) override;
	void Sety(float y) override;
	void SetW(float w) override;
	void SetH(float h) override;
	void Grounded(bool isGround);
	void Jump();
	void SetY(float y);
	void SetX(DIR dir);
	std::vector<Bullet>* GetBullet();
	void Damage(int damage);
	int GetAtk();
	int GetMaxHP();
	int GetHP();
	int GetMaxMP();
	int GetMP();
	void GetEXP(int exp);
};

