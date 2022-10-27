#include "SceneManager.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "EndScene.h"

namespace sw
{
	Scene* SceneManager::mScenes[(UINT)eSceneType::Max] = {};
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		// �������� �ʱ�ȭ
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->Initialize();

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Title]->Initialize();

		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play]->Initialize();

		mScenes[(UINT)eSceneType::End] = new EndScene();
		mScenes[(UINT)eSceneType::End]->Initialize();

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

	void SceneManager::ChangeScene(eSceneType type)
	{
		if (mPlayScene == nullptr)
		{
			mPlayScene = mScenes[(UINT)eSceneType::Logo];
		}
		else
		{
			mPlayScene->Exit();
			mPlayScene = mScenes[(UINT)type];
		}

		mPlayScene->Enter();
	}
}