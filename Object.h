#pragma once

enum RenderType : char
{
	FIRST,
	THREE,
	TWO,
	FINSH
};

class Object
{
public:
	Object();
	virtual ~Object();

	Vector3 vPos = { 0,0,0 };
	Vector3 vRot = { 0,0,0 };
	Vector3 vSize = { 1,1,1 };

	Matrix matWorld, R;
	bool isDestroy = false;

	RenderType renderType = RenderType::FIRST;

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual void TransformUpdate();
	virtual void MovePos(Vector3 pos, bool delta);
	virtual void RotatePos(Vector3 rot, bool delta);

	bool CheckDestroy() { return isDestroy; }
};

