#pragma once

#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>

#include "def.h"
#include "Maths.h"



struct WindowData
{
	HWND hWnd;
	HDC hdc;
	HDC backhdc;
	UINT height;
	UINT width;

	void clear()
	{
		hWnd = nullptr;
		hdc = nullptr;
		HDC hdc = nullptr;
		height = 0;
		width = 0;
	}
};