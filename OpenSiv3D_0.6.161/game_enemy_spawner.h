
#pragma once

#include "game_object.h"

class GameEnemySpawner : public GameObject
{
private:
	float m_elpased_time{};

public:
	GameEnemySpawner(GameWorld* world, const Float2& position);
	void Update(float delta_time) override;
	void Draw() const override;
};
