#pragma once
#pragma comment(lib,"legacy_stdio_definitions.lib")
#pragma comment(lib, "dsound.lib")

#include <iostream>
#include <stdio.h>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <time.h>

using namespace std;
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Vector4 = D3DXVECTOR4;
using Matrix = D3DXMATRIX;

#define g_device DXUTGetD3D9Device()
#define D_TIME DXUTGetElapsedTime()

const int WINSIZEX = 1920;
const int WINSIZEY = 1080;
static bool isWindowed = false;
#include "InputManager.h"
#include "CameraManager.h"
#include "ImageManager.h"
#include "ObjectManager.h"
#include "MathManager.h"
#include "SoundManager.h"
#include "Timer.h"
#include "SceneManager.h"
