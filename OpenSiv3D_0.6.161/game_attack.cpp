//=============================================================================
// Contents   : game_attack.cpp
//              Definition of class GameAttack、攻撃オブジェクト
// Author     : GU ANYI
// LastUpdate : 2026/06/09
// Since      : 2026/06/09
//=============================================================================

#include "stdafx.h"
#include "game_attack.h"
#include "game_world.h"
#include "game_object_container.h"
#include "game_damage.h"

GameAttack::GameAttack(GameWorld* world, const Float2& position, const Float2& direction, const std::string& owner_tag, int power)
	: GameObject(world, position, "Attack")
	, m_direction(direction)
	, m_power(power)
	, m_owner_tag(owner_tag) {
	if (m_direction.isZero()) {
		m_direction = Float2{ 1.0f, 0.0f };
	}
	else {
		m_direction.normalize();
	}
}

void GameAttack::Update(float delta_time)
{
	m_elapsed_time += delta_time;

	if (!m_has_damaged) {
		GameObjectContainer objects = GetWorld()->GetGameObjects(GetCollision());
		const std::string target_tag = getTargetTag();
		bool is_hit = false;

		GameDamage damage;
		damage.SetSlash(static_cast<float>(m_power));

		for (size_t i = 0; i < objects.GetCount(); ++i) {
			GameObject* object = objects.GetGameObject(i);
			if (object->GetTag() == target_tag) {
				object->Damage(damage);
				is_hit = true;
			}
		}

		if (is_hit) {
			m_has_damaged = true;
			Destory();
			return;
		}
	}

	if (m_elapsed_time >= m_life_time) {
		Destory();
	}
}

void GameAttack::Draw() const
{
	const Circle attack_area = GetCollision();
	attack_area.draw(ColorF{ 1.0, 0.7, 0.2, 0.35 });
	attack_area.drawFrame(2.0, Palette::Orange);
	Line{ GetPosition() - m_direction * 28.0f, GetPosition() + m_direction * 28.0f }.draw(6.0, Palette::Orange);
}

Circle GameAttack::GetCollision() const
{
	return Circle{ GetPosition(), m_radius };
}

std::string GameAttack::getTargetTag() const
{
	if (m_owner_tag == "Player") {
		return "Enemy";
	}

	if (m_owner_tag == "Enemy") {
		return "Player";
	}

	return "";
}
