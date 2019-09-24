#pragma once
#include <vector>
#include "Animation.h"
#include "Texture.h"
#include "Object.h"
#include "Bullet.h"
#include "LevelUp.h"

/*テクスチャ関係*/
class Player : public Object
{
private:
	Texture				m_texture;
	Animation			anim;
	LevelUp				m_l;
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
	float				m_healSpeed;
	int					m_lvhp[MAX_LV];
	int					m_lvmp[MAX_LV];
	int					m_lvatk[MAX_LV];
	float				m_lvheal[MAX_LV];
	void TextureInverse();
	void Attack();
	void CheckHP();
	void CheckBullet();
	void HealMP();
	void InitializeHP();
	void InitializeMP();
	void InitializeATK();
	void InitializeHeal();
	void SetHP();
	void SetMP();
	void SetATK();
	void SetHeal();
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
	int SetEXP();
	void Heal(int heal);
};

