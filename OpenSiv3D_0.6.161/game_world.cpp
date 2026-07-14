/*
    ファイル名：game_world.cpp
    作成者：張 楽晨
    作成日：2026/06/11
    内容：ゲームオブジェクトの登録、更新、描画、当たり判定検索、削除、リスタート用の初期化、スコア保存を行う
*/
#include "stdafx.h"
#include "game_world.h"
#include "game_object_container.h"
#include "game_object.h"

GameWorld::~GameWorld()
{
    Clear();
}

void GameWorld::Register(GameObject* game_object)
{
    m_container.Register(game_object);
}

void GameWorld::Update(float delta_time)
{
    m_container.Remove();

    for (size_t i = 0; i < m_container.GetCount(); ++i)
	{
        GameObject* object = m_container.GetGameObject(i);

        if (!object->IsDestory())
		{
            object->Update(delta_time);
        }
    }

    m_container.Remove();
}

void GameWorld::Draw() const
{
    for (size_t i = 0; i < m_container.GetCount(); ++i) {
        GameObject* object = m_container.GetGameObject(i);

        if (!object->IsDestory()) {
            object->Draw();
        }
    }
}

void GameWorld::Clear()
{
    m_container.DeleteAll();
}

void GameWorld::SetScore(int score)
{
    m_score = score;
}

int GameWorld::GetScore() const
{
    return m_score;
}

bool GameWorld::IsPlayerDead() const
{
    return GetGameObjects("Player").GetCount() == 0;
}

GameObjectContainer GameWorld::GetGameObjects(const Circle& collision) const
{
    GameObjectContainer container(m_container.GetCount());

    for (size_t i = 0; i < m_container.GetCount(); ++i) {
        GameObject* p = m_container.GetGameObject(i);
        if (!p->IsDestory() && p->GetCollision().intersects(collision)) {
            container.Register(p);
        }
    }

    return container;
}

GameObjectContainer GameWorld::GetGameObjects(const std::string& tag) const
{
    GameObjectContainer container(m_container.GetCount());

    for (size_t i = 0; i < m_container.GetCount(); ++i) {
        GameObject* p = m_container.GetGameObject(i);
        if (!p->IsDestory() && p->GetTag() == tag) {
            container.Register(p);
        }
    }

    return container;
}
