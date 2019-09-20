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
	//オブジェクトの属性
	int		m_attribute;
	//移動速度
	float	m_speed;
	//オブジェクトの向き
	DIR		m_dir;
	//1フレーム前の向き
	DIR		m_oldDir;
	//オブジェクトのテクスチャ
	LPDIRECT3DTEXTURE9 m_texture;
	//デバイス
	LPDIRECT3DDEVICE9 m_d3dDevice;

	virtual void Inversion() = 0;
	virtual void TextureInverse() = 0;
public:
	virtual void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 texture) = 0;
	virtual void Finalize() = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual float GetW() = 0;
	virtual float GetH() = 0;
	
};