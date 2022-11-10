#pragma once

#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <functional>
#include <filesystem>

#include "def.h"
#include "Maths.h"


#pragma comment(lib, "Msimg32.lib")


struct WindowData
{
	HWND hWnd;
	HDC hdc;
	HBITMAP backTexture;
	HDC backbuffer;
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

struct Pen
{
private:
	HDC mHdc;
	HPEN mOldPen;
	HPEN mPen;

public:
	Pen(HDC hdc, HPEN pen)
		: mHdc(hdc)
		, mOldPen(NULL)
		, mPen(pen)
	{
		mOldPen = (HPEN)SelectObject(mHdc, pen);
	}

	~Pen()
	{
		SelectObject(mHdc, mOldPen);
		DeleteObject(mPen);
	}
};

struct Brush
{
private:
	HDC mHdc;
	HBRUSH mOldBrush;
	HBRUSH mBrush;

public:
	Brush(HDC hdc, HBRUSH brush)
		: mHdc(hdc)
		, mOldBrush(NULL)
		, mBrush(brush)
	{
		mOldBrush = (HBRUSH)SelectObject(mHdc, brush);
	}

	~Brush()
	{
		SelectObject(mHdc, mOldBrush);
		DeleteObject(mBrush);
	}
};