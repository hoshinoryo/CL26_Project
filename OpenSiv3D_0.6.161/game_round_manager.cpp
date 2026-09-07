//=============================================================================
// Contents   : game_round_manager.cpp
//              Round機能管理システム
// Author     : GU ANYI
// LastUpdate : 2026/09/08
// Since      : 2026/09/08
//=============================================================================

#include "stdafx.h"
#include "game_round_manager.h"
#include "game_world.h"
#include "game_player.h"
#include "game_enemy_spawner.h"

void GameRoundManager::StartNewGame(GameWorld& world)
{
	world.Clear();
	world.SetScore(0);

	m_current_round = 1;

	world.Register(new GamePlayer(&world, Scene::CenterF()));

	setupRound(world);
}

void GameRoundManager::StartNextRound(GameWorld& world)
{
	m_current_round++;

	setupRound(world);
}

bool GameRoundManager::IsRoundCleared(const GameWorld& world) const
{
	const bool has_enemy   = world.GetGameObjects("Enemy").GetCount() > 0;
	const bool has_spawner = world.GetGameObjects("EnemySpawner").GetCount() > 0;
	const bool has_item    = world.GetGameObjects("Item").GetCount() > 0;

	return !has_enemy && !has_spawner && !has_item;
}

bool GameRoundManager::IsLastRound() const
{
	return m_current_round >= LAST_ROUND;
}

int GameRoundManager::getSpawnLimit() const
{
	switch (m_current_round)
	{
	case 1:
		return 7;

	case 2:
		return 14;

	case 3:
		return 21;

	default:
		return 0;
	}
}

void GameRoundManager::setupRound(GameWorld& world) const
{
	const int spawn_limit = getSpawnLimit();

	world.Register(new GameEnemySpawner(&world, { Scene::Size().x * 0.15f, Scene::Size().y * 0.3f }, spawn_limit));
	world.Register(new GameEnemySpawner(&world, Scene::Size() * 0.85f, spawn_limit));
}
