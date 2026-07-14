/*
    ファイル名：game_attack.h
    作成者：張 楽晨
    作成日：2026/06/11
    内容：プレイヤーとエネミーの近接攻撃判定を表すクラス
*/
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
