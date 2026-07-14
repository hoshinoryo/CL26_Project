/*
    ファイル名：game_enemy.cpp
    作成者：張 楽晨
    作成日：2026/06/11
    内容：エネミーがプレイヤーを追いかけ、近づいたら攻撃し、倒されたらランダムアイテムを落とす
*/
#include "stdafx.h"
#include "game_enemy.h"
#include "game_object_container.h"
#include "game_world.h"
#include "game_attack.h"
#include "game_item.h"

GameEnemy::GameEnemy(GameWorld* world, const Float2& position)
    : GameCharacter(world, position, 80, "Enemy")
{
    TextureAsset::Register(U"Enemy_Normal", 0xF11EA_icon, 48);
}

void GameEnemy::Update(float delta_time)
{
    move(delta_time);
    attack(delta_time);
}

void GameEnemy::Draw() const
{
    TextureAsset(U"Enemy_Normal").drawAt(GetPosition(), Palette::Crimson);

    const float hp_rate = static_cast<float>(GetHp()) / static_cast<float>(GetHpCapacity());
    RectF{ GetPosition().x - 35.0f, GetPosition().y - 55.0f, 70.0f, 7.0f }.draw(Palette::Darkgray);
    RectF{ GetPosition().x - 35.0f, GetPosition().y - 55.0f, 70.0f * hp_rate, 7.0f }.draw(Palette::Red);
}

void GameEnemy::Damage(const GameDamage& damage)
{
    const int amount = static_cast<int>(damage.GetTotalDamage());
    const bool is_dead = DecreaseHP(amount);

    if (is_dead) {
        dropItem();
    }
}

void GameEnemy::move(float delta_time)
{
    GameObjectContainer players = GetWorld()->GetGameObjects("Player");

    if (players.GetCount() == 0) {
        return;
    }

    Float2 to_player = players.GetGameObject(0)->GetPosition() - GetPosition();
    const float distance = to_player.length();

    if (to_player.isZero()) {
        return;
    }

    to_player.normalize();
    m_face_direction = to_player;

    if (distance <= 95.0f) {
        return;
    }

    constexpr float ENEMY_MOVE_SPEED{ 120.0f };
    SetPosition(GetPosition() + to_player * ENEMY_MOVE_SPEED * delta_time);
}

void GameEnemy::attack(float delta_time)
{
    if (m_attack_cool_time > 0.0f) {
        m_attack_cool_time -= delta_time;
    }

    GameObjectContainer players = GetWorld()->GetGameObjects("Player");
    if (players.GetCount() == 0 || m_attack_cool_time > 0.0f) {
        return;
    }

    Float2 to_player = players.GetGameObject(0)->GetPosition() - GetPosition();
    if (to_player.isZero()) {
        to_player = m_face_direction;
    }

    const float distance = to_player.length();
    if (distance <= 105.0f) {
        to_player.normalize();
        m_face_direction = to_player;
        const Float2 attack_position = GetPosition() + m_face_direction * 62.0f;
        GetWorld()->Register(new GameAttack(GetWorld(), attack_position, m_face_direction, "Enemy", 10));
        m_attack_cool_time = 1.0f;
    }
}

void GameEnemy::dropItem()
{
    if (m_has_dropped_item) {
        return;
    }

    m_has_dropped_item = true;

    const GameItemType type = static_cast<GameItemType>(Random(0, 2));
    GetWorld()->Register(new GameItem(GetWorld(), GetPosition(), type));
}
