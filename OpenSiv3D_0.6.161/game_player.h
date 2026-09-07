//=============================================================================
// Contents   : game_player.h
//              Definition of class GamePlayer 
// Author     : GU ANYI
// LastUpdate : 2026/09/08
// Since      : 2026/06/09
//=============================================================================

#pragma once

#include "game_character.h"
#include "game_inventory.h"

class GamePlayer : public GameCharacter
{
private:

    bool m_is_attack{ false };
    float m_attack_effect_time{};
    float m_attack_cool_time{};
    Float2 m_face_direction{ 1.0f, 0.0f };

    GameInventory m_inventory;
    int m_attack_power{ 40 };
    int m_score{};

    String m_item_effect_text{};
    float m_item_effect_time{};

public:

    GamePlayer(GameWorld* world, const Float2& position);

    void Update(float delta_time) override;
    void Draw() const override;
    void Damage(const GameDamage&) override;
    Circle GetCollision() const override
    {
        return Circle{ GetPosition(), 64.0 };
    }
	const GameInventory& GetInventory() const
	{
		return m_inventory;
	}

	bool PurchaseItem(GameItemType type);

private:
    void move(float delta_time);
    void attack(float delta_time);

    void pickUpItems();
    void addItem(GameItemType type);

    void updateItemEffect(float delta_time);
    void showItemEffect(const String& text);
};
