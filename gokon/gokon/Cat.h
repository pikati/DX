#pragma once
#include "Object.h"
#include "Texture.h"
#include "Animation.h"
#include <vector>
#include "Bullet.h"
#include "Animation.h"
#include "GaugeFrame.h"
#include "GaugeFill.h"

class Cat :
	public Object
{
private:
	Texture				m_texture;
	Animation			anim;
	std::vector<Bullet> m_bullet;
	GaugeFrame			m_hpFrame;
	GaugeFill			m_hpFill;
	DIR					m_oldDir;
	float				m_upPower;
	int					m_mhp;
	int					m_hp;
	int					m_atk;
	int					m_frame;
	int					m_frameEffect;
	float				m_firstX;
	bool				m_aria;
	void TextureInverse();
	void Attack();
	void Gravity();
	void Destroy();
	void CheckBullet();
	void Move();
	void CheckAria();
public:
	void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, ATTRBUTE attr, DIR dir) override;
	void Update() override;
	void Draw(LPDIRECT3DTEXTURE9 texture) override;
	void Finalize() override;
	float GetX() override;
	float GetFirstX();
	float GetY() override;
	float GetW() override;
	float GetH() override;
	void SetX(float x) override;
	void Sety(float y) override;
	void SetW(float w) override;
	void SetH(float h) override;
	void SetY(float y);
	void SetX(DIR dir);
	void Damage(int damage);
	void SetDirection(DIR dir);
	std::vector<Bullet>* GetBullet();
	int GetAtk();
	bool GetActive();
	bool CheckHP();
};

