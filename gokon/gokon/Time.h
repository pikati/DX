#pragma once
#include "Texture.h"
class Time {
private:
	Texture			m_texture;
	int				m_frame;
	int				m_oneDigit;
	int				m_tenDigit;
	int				m_handredDigit;
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};