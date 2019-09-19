#pragma once
#include "Object.h"

class Menu
{
private:
	/*選択肢の管理用変数*/
	int				m_cursor;
	/*選択肢の数*/
	int				m_maxCursor;
	/*テクスチャ*/
	unsigned int	m_texture[4];
	/*説明を表示するか -1:表示しない それ以外:対応した説明を表示*/
	int				m_dispInst;
	
public:
};
