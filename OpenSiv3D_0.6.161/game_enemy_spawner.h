//=============================================================================
// Contents   : game_enemy_spawner.h
//              エネミーの生成管理
// Author     : GU ANYI
// LastUpdate : 2026/09/07
// Since      : 2026/06/11
//=============================================================================

#pragma once

#include "game_object.h"

class GameEnemySpawner : public GameObject
{
private:
	float m_elpased_time{};
	int m_spawn_count{};
	int m_spawn_limit{};

public:
	GameEnemySpawner(GameWorld* world, const Float2& position, int spawn_limit);
	void Update(float delta_time) override;
	void Draw() const override;
};
