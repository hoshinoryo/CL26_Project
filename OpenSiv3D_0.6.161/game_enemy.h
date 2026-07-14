/*
    ファイル名：game_enemy.h
    作成者：張 楽晨
    作成日：2026/06/11
    内容：エネミーの追跡、攻撃、死亡時のアイテムドロップを管理するクラス
*/
#pragma once

#include "game_character.h"

class GameEnemy : public GameCharacter
{
private:
	float m_attack_cool_time{};
	bool m_has_dropped_item{ false };
	Float2 m_face_direction{ 1.0f, 0.0f };

public:
	GameEnemy(GameWorld* world, const Float2& position);
	void Update(float delta_time) override;
	void Draw() const override;
	void Damage(const GameDamage&) override;
	Circle GetCollision() const override {
		return Circle{ GetPosition(), 48.0 };
	}

private:
	void move(float delta_time);
	void attack(float delta_time);
	void dropItem();
};
