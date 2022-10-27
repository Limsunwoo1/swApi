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
		// 모든씬들을 초기화
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->Initialize();

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Title]->Initialize();

		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play]->Initialize();

		mScenes[(UINT)eSceneType::End] = new EndScene();
		mScenes[(UINT)eSceneType::End]->Initialize();

		// 자식 > 부모 (업캐스팅)
		mPlayScene = mScenes[(UINT)eSceneType::Logo];

		// 부모 > 자식 (다운캐스팅)
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		// 현재씬 렌더링
		mPlayScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		// 프로그램이 종료될때 한번만 호출
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