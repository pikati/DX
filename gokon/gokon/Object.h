#pragma once
#include "main.h"
typedef struct {
	/*座標情報*/
	float x, y, z;		//D3DFVF_XYZRHWのXYZの部分
	/*おまじないでおｋ*/
	float rhw;          //射影変換完了フラグ D3DFVF_XYZRHWのRHWの部分 パイプラインの最後に行うスケール変換の値で構造体の中にあると頂点が座標変換済みであると判断される
	/*ポリゴンの色情報*/
	D3DCOLOR deffuse;	//D3DFVF_DIFFUSE
	/*テクスチャ座標*/
	float tu, tv;		//D3DFVF_TEX1
}VERTEX;

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
	//頂点バッファ
	IDirect3DVertexBuffer9* m_pVB;
	//インデックスバッファ
	LPDIRECT3DINDEXBUFFER9 m_pIB;
public:
	virtual void Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, LPDIRECT3DTEXTURE9 texture) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};