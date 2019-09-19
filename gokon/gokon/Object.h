#pragma once
#include "main.h"


class Object
{
protected:
	//オブジェクトの左上のx座標
	float m_x;
	//オブジェクトの左上のy座標
	float m_y;
	//オブジェクトの横幅
	float m_w;
	//オブジェクトの縦幅
	float m_h;
	//テクスチャの左上のx座標
	float m_u;
	//テクスチャの左上のy座標
	float m_v;
	//テクスチャの横幅
	float m_tw;
	//テクスチャの縦幅
	float m_th;
	//オブジェクトのテクスチャ
	LPDIRECT3DTEXTURE9 m_texture;
	//デバイス
	LPDIRECT3DDEVICE9 m_d3dDevice;
public:
	virtual void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 texture) = 0;
	virtual void Finalize() = 0;
};