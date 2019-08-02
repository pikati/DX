#include "SceneTitle.h"
#include "main.h"
#include "Input.h"
#include "SceneManager.h"

SceneTitle::~SceneTitle() {
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pVB);	
	SAFE_RELEASE(m_d3dDevice);
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
	m_d3dDevice = GetDevice();
}

void SceneTitle::Update() {
	
}

void SceneTitle::Draw() {
	VERTEX vertex[4];
	/*2D�p�̐ݒ�*/
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;

	/*���_���W�ݒ�*/
	vertex[0].x = m_x;
	vertex[0].y = m_y;
	vertex[1].x = m_x + m_w;
	vertex[1].y = m_y;
	vertex[2].x = m_x;
	vertex[2].y = m_y + m_h;
	vertex[3].x = m_x + m_w;
	vertex[3].y = m_x + m_h;

	/*�e�N�X�`�����W�ݒ�*/
	vertex[0].tu = m_u;
	vertex[0].tv = m_v;
	vertex[1].tu = m_u + m_tw;
	vertex[1].tv = m_v;
	vertex[2].tu = m_u;
	vertex[2].tv = m_v + m_th;
	vertex[3].tu = m_u + m_tw;
	vertex[3].tv = m_v + m_th;

	/*���_�F�ݒ�*/
	vertex[0].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[1].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[2].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[3].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//��̒��_�o�b�t�@�쐬
	m_d3dDevice->CreateVertexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	void *pData;
	if (D3D_OK == m_pVB->Lock(0, sizeof(VERTEX) * 4, (void**)&pData, 0)) {
		memcpy(pData, vertex, sizeof(VERTEX) * 4);
		m_pVB->Unlock();
	}

	m_d3dDevice->CreateIndexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);

	WORD* pI;
	if (D3D_OK == m_pIB->Lock(0, 0, (void**)&pI, 0)) {
		pI[0] = 0;
		pI[1] = 1;
		pI[2] = 2;
		pI[3] = 3;
	}

	if (SUCCEEDED(m_d3dDevice->BeginScene()))
	{
		m_d3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX));
		m_d3dDevice->SetIndices(m_pIB);
		m_d3dDevice->SetFVF(FVF_VERTEX);
		m_d3dDevice->SetTexture(0, m_texture);
		m_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
		m_d3dDevice->SetTexture(0, NULL);
		m_d3dDevice->EndScene();
	}
	
}

void SceneTitle::Finalize() {
	m_pIB = NULL;
	m_pVB = NULL;
	m_d3dDevice = NULL;
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