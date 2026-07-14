//=============================================================================
// Contents   : game_player.cpp
//              Definition of class GamePlayer 
// Author     : GU ANYI
// LastUpdate : 2026/07/14
// Since      : 2026/06/09
//=============================================================================

#include "stdafx.h"
#include "game_player.h"
#include "game_world.h"
#include "game_attack.h"
#include "game_item.h"
#include "game_object_container.h"

GamePlayer::GamePlayer(GameWorld* world, const Float2& position)
    : GameCharacter(world, position, 100, "Player")
{
    TextureAsset::Register(U"Player_Normal", 0xF064B_icon, 128);
    TextureAsset::Register(U"Player_Attack", 0xF17C4_icon, 128);

    FontAsset::Register(U"PlayerStatusFont", 24);
    FontAsset::Register(U"ItemEffectFont", 28);

    GetWorld()->SetScore(m_score);
}

void GamePlayer::Update(float delta_time)
{
    updateItemEffect(delta_time);
    move(delta_time);
    attack(delta_time);
    pickUpItems();
}

void GamePlayer::Draw() const
{
	std::u32string label = m_is_attack ? U"Player_Attack" : U"Player_Normal";
	TextureAsset(label).drawAt(GetPosition());

    const float hp_rate = static_cast<float>(GetHp()) / static_cast<float>(GetHpCapacity());
    RectF{ GetPosition().x - 50.0f, GetPosition().y - 80.0f, 100.0f, 10.0f }.draw(Palette::Darkgray);
    RectF{ GetPosition().x - 50.0f, GetPosition().y - 80.0f, 100.0f * hp_rate, 10.0f }.draw(Palette::Limegreen);

    if (m_item_effect_time > 0.0f && !m_item_effect_text.isEmpty())
	{
        FontAsset(U"ItemEffectFont")(m_item_effect_text)
            .drawAt(GetPosition() + Float2{ 0.0f, -120.0f }, Palette::Yellow);
    }

    FontAsset(U"PlayerStatusFont")(
        Format(U"HP: ", GetHp(), U" / ", GetHpCapacity()))
        .draw(20, 20, Palette::Black);
    FontAsset(U"PlayerStatusFont")(
        Format(U"Attack: ", m_attack_power, U"   Score: ", m_score))
        .draw(20, 50, Palette::Black);
    FontAsset(U"PlayerStatusFont")(
        U"WASD: Move   Space: Attack   Touch item: Pick up")
        .draw(20, 80, Palette::Black);

    // 取得したアイテムを表示する
    const Float2 inventory_position{
        static_cast<float>(Scene::Width()) - 300.0f,
        20.0f
    };
    m_inventory.Draw(inventory_position);
}

void GamePlayer::Damage(const GameDamage& damage)
{
    const int amount = static_cast<int>(damage.GetTotalDamage());
    DecreaseHP(amount);
}

void GamePlayer::move(float delta_time)
{
	Float2 dir{};

	if (KeyW.pressed()) { dir.y += -1.0f; }
	if (KeyA.pressed()) { dir.x += -1.0f; }
	if (KeyS.pressed()) { dir.y += 1.0f; }
	if (KeyD.pressed()) { dir.x += 1.0f; }

	if (!dir.isZero())
	{
		dir.normalize();
	}

	constexpr float PLAYER_MOVE_SPEED{ 128.0f };

	SetPosition(GetPosition() + dir * PLAYER_MOVE_SPEED * delta_time);
}

void GamePlayer::attack(float delta_time)
{
    if (m_attack_effect_time > 0.0f) {
        m_attack_effect_time -= delta_time;
        if (m_attack_effect_time <= 0.0f) {
            m_attack_effect_time = 0.0f;
            m_is_attack = false;
        }
    }

    if (m_attack_cool_time > 0.0f) {
        m_attack_cool_time -= delta_time;
    }

    if (KeySpace.down() && m_attack_cool_time <= 0.0f) {
        m_is_attack = true;
        m_attack_effect_time = 0.18f;
        m_attack_cool_time = 0.35f;

        const Float2 attack_position = GetPosition() + m_face_direction * 82.0f;
        GetWorld()->Register(new GameAttack(
            GetWorld(), attack_position, m_face_direction, "Player", m_attack_power));
    }
}

void GamePlayer::pickUpItems()
{
    GameObjectContainer objects = GetWorld()->GetGameObjects(GetCollision());

    for (size_t i = 0; i < objects.GetCount(); ++i)
	{
        GameObject* object = objects.GetGameObject(i);

        if (object->GetTag() == "Item")
		{
            GameItem* item = static_cast<GameItem*>(object);
            addItem(item->PickUp());
        }
    }
}

void GamePlayer::addItem(GameItemType type)
{
    // どの種類でも、取得時に必ずインベントリのstd::listへ追加する
    m_inventory.AddItem(type);

    switch (type)
	{
    case GameItemType::Potion:
        RecoverHP(30);
        showItemEffect(U"Potion obtained: HP +30");
        break;

    case GameItemType::Sword:
        m_attack_power += 10;
        showItemEffect(U"Sword obtained: Attack +10");
        break;

    case GameItemType::Coin:
        m_score += 100;
        GetWorld()->SetScore(m_score);
        showItemEffect(U"Coin obtained: Score +100");
        break;
    }
}

void GamePlayer::updateItemEffect(float delta_time)
{
    if (m_item_effect_time > 0.0f)
	{
        m_item_effect_time -= delta_time;

        if (m_item_effect_time <= 0.0f)
		{
            m_item_effect_time = 0.0f;
            m_item_effect_text.clear();
        }
    }
}

void GamePlayer::showItemEffect(const String& text)
{
    m_item_effect_text = text;
    m_item_effect_time = 1.0f;
}
