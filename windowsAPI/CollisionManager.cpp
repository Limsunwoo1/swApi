#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"

namespace sw
{
    void CollisionManager::Tick()
    {
        Scene* PlayScene = SceneManager::GetInstance()->GetPlayScene();

        for (int row = 0; row < COLLIDER_LAYER; row++)
        {
            for (int col = 0; col < COLLIDER_LAYER; col++)
            {
                if (mMatrix[row] & (1 << col))
                {
                    LayerCollision(PlayScene, (eColliderLayer)row, (eColliderLayer)col);
                }
            }
        }
    }

    void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
    {
        UINT row = 0;
        UINT col = 0;

        UINT iLeft = (UINT)left;
        UINT iRight = (UINT)right;

        if (iLeft < iRight)
        {
            row = (UINT)left;
            col = (UINT)right;
        }
        else
        {
            row = (UINT)right;
            col = (UINT)left;
        }

        if (value == true)
            mMatrix[row] |= (1 << col);
        else
            mMatrix[row] &= ~(1 << col);
    }

    void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
    {
        std::vector<GameObject*>& lefts = scene->GetGameObject(left);
        std::vector<GameObject*>& rights = scene->GetGameObject(right);

        for (auto leftObject : lefts)
        {
            if (leftObject->GetComponent<Collider>() == nullptr)
                continue;

            for (auto rightObject : rights)
            {
                if (rightObject->GetComponent<Collider>() == nullptr)
                    continue;

                if (leftObject == rightObject)
                    continue;

                if (Intersect(leftObject->GetComponent<Collider>(),
                    rightObject->GetComponent<Collider>()))
                {
                    // 충돌
                    int a = 0;
                }
                else
                {
                    // 충돌 x
                    int a = 0;
                }
            }
        }
    }

    bool CollisionManager::Intersect(Collider* left, Collider* right)
    {
        Vector2 leftPos = left->GetPos();
        Vector2 leftScale = left->GetScale();


        Vector2 rightPos = right->GetPos();
        Vector2 rightScale = right->GetScale();

        if (fabs(leftPos.x - rightPos.x) < fabs(leftScale.x / 2.0f + rightScale.x / 2.0f)
            && fabs(leftPos.y - rightPos.y) < fabs(leftScale.y / 2.0f + rightScale.y / 2.0f))
        {
            return true;
        }

        return false;
    }
}