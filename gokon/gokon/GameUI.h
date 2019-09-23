#pragma once
#include "Texture.h"
#include "GaugeFrame.h"
#include "GaugeFill.h"
class GameUI
{
private:
	Texture	   m_texture;
	GaugeFrame m_gaugeFrameHP;
	GaugeFrame m_gaugeFrameMP;
	GaugeFill  m_gaugeHP;
	GaugeFill  m_gaugeMP;
public:
	void Initialize();
	void Update();
	void Draw();
	void Fianlize();
};

