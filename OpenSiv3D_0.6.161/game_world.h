/*
    ファイル名：game_world.h
    作成者：張 楽晨
    作成日：2026/06/11
    内容：ゲームオブジェクト全体の更新、描画、検索、リスタート用の初期化、スコアを管理するクラス
*/
#pragma once

#include "game_object_container.h"

class GameObject;

class GameWorld
{
private:

    static constexpr int CONTAINER_CAPACITY{ 400 };
    GameObjectContainer m_container{ CONTAINER_CAPACITY };
    int m_score{};

public:

    ~GameWorld();
    void Register(GameObject* game_object);
    void Update(float delta_time);
    void Draw() const;
    void Clear();
    void SetScore(int score);
    int GetScore() const;
    bool IsPlayerDead() const;
    GameObjectContainer GetGameObjects(const Circle& collision) const;
    GameObjectContainer GetGameObjects(const std::string& tag) const;
};
