#include "SceneTitle.h"
#include "main.h"
#include "Input.h"
#include "SceneManager.h"

SceneTitle::~SceneTitle() {
	SAFE_RELEASE(m_texture);
}

void SceneTitle::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th, LPDIRECT3DTEXTURE9 texture) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
	m_texture = texture;
}

void SceneTitle::Update() {
	
}

void SceneTitle::Draw() {
	VERTEX vertex[4];
	LPDIRECT3DDEVICE9 d3dDevice = GetDevice();
	IDirect3DVertexBuffer9* pVertex;
	/*2D用の設定*/
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;

	/*頂点座標設定*/
	vertex[0].x = m_x;
	vertex[0].y = m_y;
	vertex[1].x = m_x + m_w;
	vertex[1].y = m_y;
	vertex[2].x = m_x;
	vertex[2].y = m_y + m_h;
	vertex[3].x = m_x + m_w;
	vertex[3].y = m_x + m_h;

	/*テクスチャ座標設定*/
	vertex[0].tu = m_u;
	vertex[0].tv = m_v;
	vertex[1].tu = m_u + m_tw;
	vertex[1].tv = m_v;
	vertex[2].tu = m_u;
	vertex[2].tv = m_v + m_th;
	vertex[3].tu = m_u + m_tw;
	vertex[3].tv = m_v + m_th;

	/*頂点色設定*/
	vertex[0].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[1].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[2].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[3].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//空の頂点バッファ作成
	d3dDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX,
		D3DPOOL_MANAGED,
		&pVertex,
		NULL);

	void *pData;
	if (D3D_OK == pVertex->Lock(0, sizeof(VERTEX) * 4, (void**)&pData, 0)) {
		memcpy(pData, vertex, sizeof(VERTEX) * 4);
		pVertex->Unlock();
	}

	if (SUCCEEDED(d3dDevice->BeginScene()))
	{
		d3dDevice->SetStreamSource(0, pVertex, 0, sizeof(VERTEX));
		d3dDevice->SetFVF(FVF_VERTEX);
		d3dDevice->SetTexture(0, m_texture);
		d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		d3dDevice->SetTexture(0, NULL);
		d3dDevice->EndScene();
	}
	SAFE_RELEASE(d3dDevice);
}

void SceneTitle::Finalize() {
	m_texture = NULL;
	m_x = 0;
	m_y = 0;
	m_w = 0;
	m_h = 0;
	m_u = 0;
	m_v = 0;
	m_tw = 0;
	m_th = 0;
}