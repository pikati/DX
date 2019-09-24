#pragma once
#include "Texture.h"

#define MAX_LV 9


class LevelUp
{
private:
	int m_hpl;
	int m_mpl;
	int m_atkl;
	int m_heal;
	int m_hpexp[MAX_LV];
	int m_mpexp[MAX_LV];
	int m_atkexp[MAX_LV];
	int m_healexp[MAX_LV];
	Texture m_texture;
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void UpHP(int *exp);
	void UpMP(int *exp);
	void UpATK(int *exp);
	void UpHeal(int *exp);
	int GetHPLV();
	int GetMPLV();
	int GetATKLV();
	int GetHealLV();
	void DrawEXP(int exp, float x);
};

