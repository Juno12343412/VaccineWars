#pragma once

template <typename T>
class singleton
{
public:
	static T* p;
	static T* GetInstance()
	{
		if (!p)
			p = new T;
		return p;
	}
	static void ReleaseInstance()
	{
		if (p)
			delete p;
		p = nullptr;
	}
};

template <typename T>
T* singleton<T>::p = nullptr;
