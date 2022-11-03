#pragma once
#include "Texture.h"

namespace sw
{
	class Image : public Texture
	{
	public:
		Image();
		virtual ~Image();

		static Image* Create(const std::wstring& key, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;

		HDC GetDC() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

