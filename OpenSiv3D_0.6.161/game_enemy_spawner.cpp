//=============================================================================
// Contents   : game_enemy_spawner.h
//              エネミーの生成管理
// Author     : GU ANYI
// LastUpdate : 2026/09/07
// Since      : 2026/06/11
//=============================================================================

#include "stdafx.h"
#include "game_enemy_spawner.h"
#include "game_world.h"
#include "game_enemy.h"

GameEnemySpawner::GameEnemySpawner(GameWorld* world, const Float2& position, int spawn_limit)
	: GameObject(world, position, "EnemySpawner")
	, m_spawn_limit(spawn_limit)
{
	TextureAsset::Register(U"Enemy_Spawner", 0xF0BCA_icon, 128);
}

void GameEnemySpawner::Update(float delta_time)
{
	if (m_spawn_count >= m_spawn_limit)
	{
		Destory();
		return;
	}

	m_elpased_time += delta_time;

	constexpr float SPAWN_INTERVAL{ 1.5f };

	if (m_elpased_time > SPAWN_INTERVAL)
	{
		m_elpased_time -= SPAWN_INTERVAL;

		GetWorld()->Register(new GameEnemy(GetWorld(), GetPosition()));

		++m_spawn_count;

		if (m_spawn_count >= m_spawn_limit)
		{
			Destory();
		}
	}
}

void GameEnemySpawner::Draw() const
{
	TextureAsset(U"Enemy_Spawner").drawAt(GetPosition(), Palette::Crimson);
}
