#pragma once
class Scene abstract
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

