//=============================================================================
// Contents   : game_attack.h
//              Definition of class GameAttack、攻撃オブジェクト
// Author     : GU ANYI
// LastUpdate : 2026/09/08
// Since      : 2026/06/09
//=============================================================================

#pragma once

#include "game_object.h"

class GameAttack : public GameObject
{
private:
	Float2 m_direction{ 1.0f, 0.0f };
	float m_elapsed_time{};
	float m_life_time{ 0.15f };
	float m_radius{ 48.0f };
	int m_power{ 10 };
	std::string m_owner_tag;
	bool m_has_damaged{ false };

public:
	GameAttack(GameWorld* world, const Float2& position, const Float2& direction, const std::string& owner_tag, int power);
	void Update(float delta_time) override;
	void Draw() const override;
	Circle GetCollision() const override;

private:
	std::string getTargetTag() const;
};
