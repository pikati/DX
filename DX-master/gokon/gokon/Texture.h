#pragma once
#include "main.h"

class Texture
{
private:
	LPDIRECT3DTEXTURE9 m_texture;
public:
	/// <summary>
	/// 画像を読み込む
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	void SetTexture(const char *fileName);

	/// <summary>
	/// 画像を返す
	/// </summary>
	/// <returns>テクスチャオブジェクトのポインタ</returns>
	LPDIRECT3DTEXTURE9 GetTexture();
	~Texture();
};

