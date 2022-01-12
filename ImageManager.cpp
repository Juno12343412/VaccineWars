#include "DXUT.h"
#include "ImageManager.h"
#include <mutex>
void texture::CenterRender(Vector3 pos, Vector3 rot, Vector3 size, D3DCOLOR color)
{
	IMAGE->CenterRender(this, pos, rot, size, color);
}

void texture::Render(Vector3 pos, Vector3 rot, Vector3 size, RECT rect, D3DCOLOR color)
{
	IMAGE->Render(this, pos, rot, size, rect, color);
}

void texture::Release()
{
	SAFE_RELEASE(texturePtr);
}

VECtexture::VECtexture()
{
}

VECtexture::~VECtexture()
{
	for (auto iter : vecTex)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	vecTex.clear();
}

void VECtexture::ADDIMAGE(texture* tempImage)
{
	vecTex.push_back(tempImage);
}

texture* VECtexture::FINDIMAGE(int count)
{

	return vecTex[count];
}

void ImageManager::Init()
{
	D3DXCreateSprite(g_device, &sprite);
}

void ImageManager::Release()
{
	for (auto iter : imageMap)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	imageMap.clear();
	for (auto iter : vecImageMap)
	{
		SAFE_DELETE(iter.second);
	}
	vecImageMap.clear();
	sprite->Release();

	for (auto iter : meshMap)
	{
		iter.second->Destroy();
		SAFE_RELEASE(iter.second->m_pMesh);
		SAFE_DELETE(iter.second);
	}
	meshMap.clear();
}

ImageManager::ImageManager()
	:sprite(nullptr)
{
	Init();
}

ImageManager::~ImageManager()
{
	Release();
}
mutex ImageMutex;
texture* ImageManager::AddImage(wstring key, wstring path, bool isMapping)
{
	auto find = imageMap.find(key);
	if (find == imageMap.end())
	{
	first:
		LPDIRECT3DTEXTURE9 texturePtr;
		D3DXIMAGE_INFO info;
		TCHAR ch[256];

		if (!isMapping)
		{
			wsprintf(ch, L"./Resource/2D/%s.png", path.c_str());
		}
		else
		{
			wsprintf(ch, L"%s", path.c_str());
		}
		D3DXGetImageInfoFromFile(ch, &info);
		if (D3DXCreateTextureFromFileEx(g_device, ch, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &info, nullptr, &texturePtr) == S_OK)
		{
			texture* text = new texture(texturePtr, info);
			lock_guard<mutex> lock(ImageMutex);
			imageMap.insert(make_pair(key, text));
			return text;
		}
		return nullptr;
	}
	find->second->Release();
	SAFE_DELETE(find->second);
	imageMap.erase(find);
	goto first;

}

texture* ImageManager::FindImage(wstring key)
{
	return imageMap[key];

}
mutex VecImageMutex;
VECtexture* ImageManager::ADDVECIMAGE(wstring key, wstring path, int max)
{
	auto find = vecImageMap.find(key);
	if (find != vecImageMap.end())
		return find->second;

	VECtexture* vec = new VECtexture;

	for (int i = 0; i <= max; i++)
	{
		LPDIRECT3DTEXTURE9 lpTexture;
		D3DXIMAGE_INFO info;

		TCHAR ch[256];

		wsprintf(ch, L"./Resource/2D/%s/(%d).png", path.c_str(), i);


		D3DXGetImageInfoFromFile(ch, &info);

		if (D3DXCreateTextureFromFileEx(g_device, ch, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &info, nullptr, &lpTexture) == S_OK)
		{
			texture* text = new texture(lpTexture, info);
			vec->ADDIMAGE(text);
		}
	}
	lock_guard<mutex> lock(VecImageMutex);
	vecImageMap.insert(make_pair(key, vec));
	return vec;
}

VECtexture* ImageManager::FINDVECIMAGE(wstring key)
{
	return vecImageMap[key];
}

CMeshLoader* ImageManager::AddMesh(wstring key, wstring path)
{
	auto find = meshMap.find(key);
	if (find == meshMap.end())
	{
		CMeshLoader* mesh = new CMeshLoader();
		WCHAR ch[256];
		wsprintf(ch, L"./Resource/3D/%s.obj", path.c_str());
		mesh->Create(g_device, ch);
		if (mesh)
		{
			meshMap.insert(make_pair(key, mesh));
			return mesh;
		}
		return nullptr;
	}
	return find->second;
}

CMeshLoader* ImageManager::FindMesh(wstring key)
{
	return meshMap[key];

}

void ImageManager::Begin(bool isUi, bool isBill)
{
	if (isBill)
	{
		sprite->SetWorldViewLH(NULL, &CAMERA->matView);
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_BILLBOARD | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	}
	else
	{
		if (!isUi)
		{
			sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
		}
		else
		{
			sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
		}
	}
}

void ImageManager::ReBegin(bool isUi, bool isBill)
{
	End(); Begin(isUi, isBill);
}

void ImageManager::End()
{
	sprite->End();
}

void ImageManager::CenterRender(texture* texturePtr, Vector3 pos, Vector3 rot, Vector3 size, D3DCOLOR color)
{
	if (texturePtr)
	{
		Matrix matWorld;
		g_device->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&matWorld));
		Matrix mSize, mPos, mRot[3], R;
		D3DXMatrixScaling(&mSize, size.x, size.y, size.z);
		D3DXMatrixTranslation(&mPos, pos.x, pos.y, pos.z);
		D3DXMatrixRotationX(&mRot[0], D3DXToRadian(rot.x));
		D3DXMatrixRotationY(&mRot[1], D3DXToRadian(rot.y));
		D3DXMatrixRotationZ(&mRot[2], D3DXToRadian(rot.z));
		R = mRot[0] * mRot[1] * mRot[2];
		sprite->SetTransform(&(mSize * R * mPos));
		sprite->Draw(texturePtr->texturePtr, NULL, &Vector3(texturePtr->info.Width / 2, texturePtr->info.Height / 2, 0), NULL, color);
	}

}

void ImageManager::Render(texture* texturePtr, Vector3 pos, Vector3 rot, Vector3 size, RECT rect, D3DCOLOR color)
{
	if (texturePtr)
	{
		Matrix matWorld;
		g_device->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&matWorld));
		Matrix mSize, mPos, mRot[3], R;
		D3DXMatrixScaling(&mSize, size.x, size.y, size.z);
		D3DXMatrixTranslation(&mPos, pos.x, pos.y, pos.z);
		D3DXMatrixRotationX(&mRot[0], D3DXToRadian(rot.x));
		D3DXMatrixRotationY(&mRot[1], D3DXToRadian(rot.y));
		D3DXMatrixRotationZ(&mRot[2], D3DXToRadian(rot.z));
		R = mRot[0] * mRot[1] * mRot[2];
		sprite->SetTransform(&(mSize * R * mPos));
		sprite->Draw(texturePtr->texturePtr, &rect,nullptr , nullptr, color);
	}
}

void ImageManager::MeshRender(CMeshLoader* meshPtr, Matrix matWorld, bool isCCW)
{
	if (meshPtr)
	{
		if (isCCW)
			g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		else
			g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		g_device->SetTransform(D3DTS_WORLD, &matWorld);

		for (int i = 0; i < meshPtr->GetNumMaterials(); ++i)
		{
			g_device->SetTexture(0, meshPtr->GetMaterial(i)->pTexture);
			meshPtr->GetMesh()->DrawSubset(i);
		}
		Matrix iden;
		D3DXMatrixIdentity(&iden);
		g_device->SetTransform(D3DTS_WORLD, &iden);

		g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}
}

void ImageManager::TextDraw(wstring str, Vector3 pos, float size, D3DCOLOR color, bool center, bool isBill)
{
	Matrix mat, mSize, mPos;
	if(!isBill)
		D3DXMatrixScaling(&mSize, 1, 1, 1);
	else
		D3DXMatrixScaling(&mSize, 1, -1, 1);
	if (!center)
	{
		D3DXCreateFontA(g_device, size, 0, 10, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "System", &lpFont);
		D3DXMatrixTranslation(&mPos, pos.x, pos.y, pos.z);
	}
	else
	{
		D3DXCreateFontA(g_device, size, 0, 0, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "System", &lpFont);
		D3DXMatrixTranslation(&mPos, pos.x - size * (str.size() * 0.25f), pos.y / 2.f, pos.z);
	}
	mat = mSize * mPos;
	sprite->SetTransform(&mat);
	lpFont->DrawTextW(sprite, str.c_str(), str.size(), NULL, DT_NOCLIP, color);

	SAFE_RELEASE(lpFont);
}

void ImageManager::LostDevice()
{
	sprite->OnLostDevice();
}

void ImageManager::ResetDevice()
{
	sprite->OnResetDevice();
}
