#include "SceneManager.h"
#include "LogoScene.h"

namespace sw
{
	Scene* SceneManager::mScenes[(UINT)eSceneType::Max] = {};
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		// 모든씬들을 초기화
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->Initialize();

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
}