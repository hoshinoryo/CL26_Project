//=============================================================================
// Contents   : game_inventory_item.cpp
//              アイテム種類に対応する表示名と所持数の処理
// Author     : GU ANYI
// LastUpdate : 2026/07/14
// Since      : 2026/07/14
//=============================================================================

#include "stdafx.h"
#include "game_inventory_item.h"

GameInventoryItem::GameInventoryItem(GameItemType type)
    : m_type(type)
{
    switch (m_type)
	{
    case GameItemType::Potion:
        m_name = U"Potion";
        break;

    case GameItemType::Sword:
        m_name = U"Sword";
        break;

    case GameItemType::Coin:
        m_name = U"Coin";
        break;
    }
}

GameItemType GameInventoryItem::GetType() const
{
    return m_type;
}

const String& GameInventoryItem::GetName() const
{
    return m_name;
}

int GameInventoryItem::GetCount() const
{
    return m_count;
}

void GameInventoryItem::AddCount(int amount)
{
    if (amount > 0)
	{
        m_count += amount;
    }
}

void GameInventoryItem::RemoveCount(int amount)
{
	if (amount > 0 && amount <= m_count)
	{
		m_count -= amount;
	}
}
