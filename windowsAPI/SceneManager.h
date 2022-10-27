#pragma once
#include "Common.h"


namespace sw
{
	class Scene;

	class SceneManager
	{
	public:
		static void Initalize();
		static void Tick();
		static void Render(HDC hdc);
		static void Release();

		static void ChangeScene(eSceneType type);

		static Scene* GetPlayScene() { return mPlayScene; }

	private:
		static Scene* mScenes[(UINT)eSceneType::Max];
		static Scene* mPlayScene;
	};
}
