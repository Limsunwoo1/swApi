#include "SceneManager.h"
#include "LogoScene.h"

namespace sw
{
	Scene* SceneManager::mScenes[(UINT)eSceneType::Max] = {};
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		// �������� �ʱ�ȭ
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->Initialize();

		// �ڽ� > �θ� (��ĳ����)
		mPlayScene = mScenes[(UINT)eSceneType::Logo];

		// �θ� > �ڽ� (�ٿ�ĳ����)
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		// ����� ������
		mPlayScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		// ���α׷��� ����ɶ� �ѹ��� ȣ��
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}
}