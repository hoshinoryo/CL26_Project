//=============================================================================
// Contents   : game_item.h
//              アイテムクラス
// Author     : GU ANYI
// LastUpdate : 2026/09/07
// Since      : 2026/07/14
//=============================================================================

#pragma once

#include "game_object.h"
#include "game_inventory_item.h"

class GameItem : public GameObject
{
private:

    GameItemType m_type{ GameItemType::Potion };

public:

    GameItem(GameWorld* world, const Float2& position, GameItemType type)
        : GameObject(world, position, "Item")
        , m_type(type)
    {
		switch (m_type)
		{
		case GameItemType::Potion:
			TextureAsset::Register(U"Item_Potion", 0xF1131_icon, 40);
			break;

		case GameItemType::Sword:
			TextureAsset::Register(U"Item_Sword", 0xF04E5_icon, 40);
			break;

		case GameItemType::Coin:
			TextureAsset::Register(U"Item_Coin", 0xF0813_icon, 40);
			break;
		}
    }

    void Update(float) override
    {
    }

    void Draw() const override
    {
        const Circle base{ GetPosition(), 20.0 };

        switch (m_type)
		{
        case GameItemType::Potion:
			TextureAsset(U"Item_Potion").drawAt(GetPosition(), Palette::Red);
            break;

        case GameItemType::Sword:
			TextureAsset(U"Item_Sword").drawAt(GetPosition(), Palette::Silver);
            break;

        case GameItemType::Coin:
			TextureAsset(U"Item_Coin").drawAt(GetPosition(), Palette::Gold);
            break;
        }
    }

    Circle GetCollision() const override
    {
        return Circle{ GetPosition(), 20.0 };
    }

    GameItemType PickUp()
    {
        Destory();
        return m_type;
    }
};
