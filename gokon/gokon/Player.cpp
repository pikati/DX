#include "Player.h"
#include "Input.h"
#include "main.h"

void Player::Initialize(float x, float y, float w, float h, float u, float v, float tw, float th) {
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
	m_u = u;
	m_v = v;
	m_tw = tw;
	m_th = th;
}

void Player::Update() {
	if (Input::GetKey(DIK_UP)) {
		m_y += 1.0f;
	}
	if (Input::GetKey(DIK_DOWN)) {
		m_y += -1.0f;
	}
	/*当たり判定とかいろいろ処理*/
}

void Player::Draw() {
	VERTEX vertex[4];
	LPDIRECT3DDEVICE9 d3dDevice = GetDevice();
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
	vertex[0].deffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	vertex[1].deffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	vertex[2].deffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	vertex[3].deffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	if (SUCCEEDED(d3dDevice->BeginScene()))
	{
		d3dDevice->SetFVF(FVF_VERTEX);
		d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		d3dDevice->SetTexture(0, m_texture);
		d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(VERTEX));
		d3dDevice->SetTexture(0, NULL);
		d3dDevice->EndScene();
	}
}

void Player::Finalize() {
	SAFE_RELEASE(m_texture);
	m_texture = NULL;
}