#include "Image.h"
#include "Application.h"
#include "ResourceManager.h"

namespace sw
{
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{

	}

	Image::~Image()
	{
		HWND hWnd = Application::GetInstance().GetWindowData().hWnd;
		ReleaseDC(hWnd, mHdc);
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), 
			IMAGE_BITMAP, 0, 0, 
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (!mBitmap)
		{
			return E_FAIL;
		}

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);

		return S_OK;
	}

	Image* Image::Create(const std::wstring& key, UINT width, UINT height)
	{
		// �켱 ���� �̹����� �ִ��� üũ
		Image* image = ResourceManager::GetInstance()->Find<Image>(key);
		if (image != nullptr)
		{
			MessageBox(nullptr, L"�ߺ� Ű �̹��� ����", L"�̹��� ���� ����!", MB_OK);
			return nullptr;
		}

		// �̹����� ������ ����Ѵ�
		image = new Image();
		HDC mainhdc = Application::GetInstance().GetWindowDC();

		image->mBitmap = CreateCompatibleBitmap(mainhdc, width, height);
		image->mHdc = CreateCompatibleDC(mainhdc);

		if (image->mBitmap == NULL
			|| image->mHdc == NULL)
			return nullptr;

		// ���� ������ ��Ʈ�ʰ� DC �� ���� ������ �־����
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(defaultBitmap);

		// ���� ���� Ȯ��
		BITMAP bitmap = {};
		GetObject(image->mBitmap, sizeof(BITMAP), &bitmap);

		image->mWidth = bitmap.bmWidth;
		image->mHeight = bitmap.bmHeight;

		image->SetKey(key);
		ResourceManager::GetInstance()->Insert<Image>(key, image);

		return image;
	}
}
