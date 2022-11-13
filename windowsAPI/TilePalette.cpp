#include "TilePalette.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Tile.h"
#include "Scene.h"
#include "ToolScene.h"
#include "Input.h"

namespace sw
{
	TilePalette::TilePalette()
		: bObserver(false)
	{
		mImage = ResourceManager::GetInstance()->
			Load<Image>(L"TileAtlas", L"..\\Resource\\Image\\Tile.bmp");
	}

	TilePalette::~TilePalette()
	{

	}

	void TilePalette::TileObserver()
	{
		std::unordered_map<UINT64, Tile*>::iterator iter;
		iter = mTiles.begin();

		for (; iter != mTiles.end();)
		{
			if (iter->second == nullptr)
			{
				iter = mTiles.erase(iter);
				continue;
			}
			++iter;
		}
	}

	void TilePalette::Tick()
	{
		if (bObserver)
			TileObserver();

		if (KEY_PRESSE(eKeyCode::LBTN))
		{
			if (GetFocus())
			{
				Vector2 mousePos = Input::GetInstance()->GetMousePos();

				int x = mousePos.x / (TILE_SIZE * TILE_SCALE);
				int y = mousePos.y / (TILE_SIZE * TILE_SCALE);

				Scene* scene = SceneManager::GetInstance()->GetPlayScene();
				ToolScene* toolscene = dynamic_cast<ToolScene*>(scene);
				UINT index = toolscene->GetTileIndex();

				CreateTile(index, Vector2(x, y));
			}
		}
		else if (KEY_PRESSE(eKeyCode::RBTN))
		{
			if (GetFocus())
			{
				Vector2 mousePos = Input::GetInstance()->GetMousePos();

				int x = mousePos.x / (TILE_SIZE * TILE_SCALE);
				int y = mousePos.y / (TILE_SIZE * TILE_SCALE);

				Scene* scene = SceneManager::GetInstance()->GetPlayScene();
				ToolScene* toolscene = dynamic_cast<ToolScene*>(scene);
				UINT index = toolscene->GetTileIndex();

				DeleteTile(mousePos);
			}
		}
	}

	void TilePalette::Render(HDC hdc)
	{

	}

	void TilePalette::CreateTile(UINT index, Vector2 indexPos)
	{
		TileID key(indexPos.x, indexPos.y);
		key.ID;

		std::unordered_map<UINT64, Tile*>::iterator iter;
		iter = mTiles.find(key.ID);

		if (iter != mTiles.end())
		{
			// ÇöÀç Å¸ÀÏ index ·Î ¹Ù²ãÁÜ
			if(iter->second != nullptr)
				iter->second->SetIndex(index);

			return;
		}

		Vector2 objectPos = indexPos * (TILE_SIZE * TILE_SCALE);
		Tile* tile = new Tile(objectPos);
		tile->Initialize(mImage, index);

		EventInfo info;
		info.Type = EventType::AddObejct;
		info.Parameter1 = new eColliderLayer(eColliderLayer::Tile);
		info.Parameter2 = tile;

		EventManager::GetInstance()->EventPush(info);

		mTiles.insert(std::make_pair(key.ID, tile));
	}

	void TilePalette::DeleteTile(Vector2 mousePos)
	{
		std::unordered_map<UINT64, Tile*>::iterator iter;

		for (iter = mTiles.begin();iter != mTiles.end(); ++iter)
		{
			Vector2 iterPos = iter->second->GetPos();
			Vector2 iterScale = iter->second->GetScale();

			if (iterPos.x > mousePos.x || iterPos.x + (TILE_SIZE * TILE_SCALE) < mousePos.x)
				continue;

			if (iterPos.y > mousePos.y || iterPos.y + (TILE_SIZE * TILE_SCALE) < mousePos.y)
				continue;

			if (iter->second == nullptr)
				return;

			EventInfo info;
			info.Type = EventType::DeleteObject;
			info.Parameter1 = new eColliderLayer(eColliderLayer::Tile);
			info.Parameter2 = iter->second;

			EventManager::GetInstance()->EventPush(info);

			iter->second = nullptr;
			bObserver = true;
		}
	}
}