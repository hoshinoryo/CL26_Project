/*
    ファイル名：game_item.h
    作成者：張 楽晨
    作成日：2026/07/14
    内容：エネミーを倒した時にランダムで落ち、プレイヤーが取得できるフィールドアイテムクラス
*/
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
    }

    void Update(float) override
    {
    }

    void Draw() const override
    {
        const Circle base{ GetPosition(), 20.0 };

        switch (m_type) {
        case GameItemType::Potion:
            base.draw(Palette::Red);
            base.drawFrame(3.0, Palette::White);
            break;
        case GameItemType::Sword:
            base.draw(Palette::Silver);
            Line{ GetPosition() + Float2{ -12.0f, 12.0f }, GetPosition() + Float2{ 12.0f, -12.0f } }
                .draw(5.0, Palette::White);
            break;
        case GameItemType::Coin:
            base.draw(Palette::Gold);
            base.drawFrame(3.0, Palette::Orange);
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
