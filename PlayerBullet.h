#pragma once
#include "Object.h"
class PlayerBullet :
	public Object
{
public:
	PlayerBullet(int num, Vector3 moveDir);
	virtual ~PlayerBullet();

	int num;
	float speed;
	texture* img;
	Vector3 moveDir;
	Timer* desT;
	Timer* eT;
	Timer* udoT;
	bool udo = false;
	float radius = 0;
	// Object��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

