#include "Object.h"
#include "Polygons.h"

void Object::SetPosition(float x, float y, float w, float h, float u, float v, float tw, float th) {
	Polygons::SetPosition(x, y, w, h, u, v, tw, th);
}

void Object::SetColor(D3DCOLOR deffuse) {
	Polygons::SetColor(deffuse);
}
void Object::Draw(LPDIRECT3DTEXTURE9 texture) {
	Polygons::Draw(texture);
}