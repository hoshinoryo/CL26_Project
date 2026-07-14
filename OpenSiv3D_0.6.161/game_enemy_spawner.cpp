/*
    ファイル名：game_enemy_spawner.cpp
    作成者：張 楽晨
    作成日：2026/06/11
    内容：エネミーの生成タイミングと最大数を管理する
*/
#include "stdafx.h"
#include "game_enemy_spawner.h"
#include "game_world.h"
#include "game_enemy.h"

GameEnemySpawner::GameEnemySpawner(GameWorld* world, const Float2& position)
	: GameObject(world, position, "EnemySpawner")
{
	TextureAsset::Register(U"Enemy_Spawner", 0xF0BCA_icon, 128);
}

void GameEnemySpawner::Update(float delta_time)
{
	m_elpased_time += delta_time;

	if (m_elpased_time > 1.5f) {
		m_elpased_time -= 1.5f;

		if (GetWorld()->GetGameObjects("Enemy").GetCount() < 3) {
			GetWorld()->Register(new GameEnemy(GetWorld(), GetPosition()));
		}
	}
}

void GameEnemySpawner::Draw() const
{
	TextureAsset(U"Enemy_Spawner").drawAt(GetPosition(), Palette::Crimson);
}
