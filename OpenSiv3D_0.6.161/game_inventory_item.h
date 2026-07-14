//=============================================================================
// Contents   : game_inventory_item.h
//              アイテム種類に対応する表示名と所持数の処理
// Author     : GU ANYI
// LastUpdate : 2026/07/14
// Since      : 2026/07/14
//=============================================================================

#pragma once

enum class GameItemType
{
    Potion,
    Sword,
    Coin,
};

class GameInventoryItem
{
private:

    GameItemType m_type{ GameItemType::Potion };
    String m_name{ U"Potion" };
    int m_count{ 1 };

public:

    explicit GameInventoryItem(GameItemType type);

    GameItemType GetType() const;
    const String& GetName() const;
    int GetCount() const;
    void AddCount(int amount = 1);
};
