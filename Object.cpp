#include "DXUT.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}


void Object::TransformUpdate()
{
	Matrix scale, rotation[3], position;
	D3DXMatrixScaling(&scale, vSize.x, vSize.y, vSize.z);
	D3DXMatrixTranslation(&position, vPos.x, vPos.y, vPos.z);

	D3DXMatrixRotationX(&rotation[0], D3DXToRadian(vRot.x));
	D3DXMatrixRotationY(&rotation[1], D3DXToRadian(vRot.y));
	D3DXMatrixRotationZ(&rotation[2], D3DXToRadian(vRot.z));

	R = rotation[0] * rotation[1] * rotation[2];

	matWorld = scale * R * position;
}

void Object::MovePos(Vector3 pos, bool delta)
{
	Vector3 vecDir = pos;
	D3DXVec3TransformNormal(&vecDir, &vecDir, &R);
	if (delta)
		vPos += vecDir * D_TIME;
	else
		vPos += vecDir;

}

void Object::RotatePos(Vector3 rot, bool delta)
{
	if (delta)
		vRot += rot * D_TIME;
	else
		vRot += rot;
}
