#pragma once
#include "Common.h"
#include "Texture.h"

namespace sw
{
	template <typename T>
	class ResourceManager
	{
	public:
		typedef std::map<std::wstring, Texture*>::iterator ResourceIter;

		static T* Find(const std::wstring& key)
		{
			ResourceIter iter = mResource.find(key);

			// ���ҽ��� �̹� map �ȿ� �����Ұ��
			if (iter != mResource.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			return nullptr;
		}

		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Find(key);
			// �ش� Ű�� �̹� �ε��Ȱ� ������ ���ҽ��� ��ȯ
			if (resource)
				return resource;

			// ���ҽ��� ���°��
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"image Load Failed!!", L"Error", MB_OK);
			}

			resource->SetKey(key);
			resource->SetPath(path);

			mResource.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

	private:
		static std::map<std::wstring, Texture*> mResource;
	};

	template<typename T>
	std::map<std::wstring, Texture*> ResourceManager<T>::mResource;
}

