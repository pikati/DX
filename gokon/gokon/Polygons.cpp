#include "Polygons.h"
#include "SceneManager.h"

VERTEX Polygons::vertex[4];

void Polygons::Draw(float x, float y, float w, float h, float tx, float ty, float tw, float th, int tex_id) {
	LPDIRECT3DDEVICE9 d3dDvice = GetDevice();
	//頂点バッファ
	IDirect3DVertexBuffer9* pVB;
	//インデックスバッファ
	LPDIRECT3DINDEXBUFFER9 pIB;

	/*2D用の設定*/
	vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;
	vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;

	/*頂点座標設定*/
	vertex[0].x = x;
	vertex[0].y = y;
	vertex[1].x = x + w;
	vertex[1].y = y;
	vertex[2].x = x;
	vertex[2].y = y + h;
	vertex[3].x = x + w;
	vertex[3].y = x + h;

	/*テクスチャ座標設定*/
	vertex[0].tu = tx;
	vertex[0].tv = ty;
	vertex[1].tu = tx + tw;
	vertex[1].tv = ty;
	vertex[2].tu = tx;
	vertex[2].tv = ty + th;
	vertex[3].tu = tx + tw;
	vertex[3].tv = ty + th;

	/*頂点色設定*/
	vertex[0].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[1].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[2].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[3].deffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	//空の頂点バッファ作成
	d3dDvice->CreateVertexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX,
		D3DPOOL_MANAGED,
		&pVB,
		NULL);

	void *pData;
	if (D3D_OK == pVB->Lock(0, sizeof(VERTEX) * 4, (void**)&pData, 0)) {
		memcpy(pData, vertex, sizeof(VERTEX) * 4);
		pVB->Unlock();
	}

	d3dDvice->CreateIndexBuffer(sizeof(VERTEX) * 4, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIB, NULL);

	WORD* pI;
	if (D3D_OK == pIB->Lock(0, 0, (void**)&pI, 0)) {
		pI[0] = 0;
		pI[1] = 1;
		pI[2] = 2;
		pI[3] = 3;
	}

	if (SUCCEEDED(d3dDvice->BeginScene()))
	{
		d3dDvice->SetStreamSource(0, pVB, 0, sizeof(VERTEX));
		d3dDvice->SetIndices(pIB);
		d3dDvice->SetFVF(FVF_VERTEX);
		d3dDvice->SetTexture(0, SceneManager::GetTexture(tex_id));
		d3dDvice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);
		d3dDvice->SetTexture(0, NULL);
		d3dDvice->EndScene();
	}
	SAFE_RELEASE(pIB);
	SAFE_RELEASE(pVB);
}