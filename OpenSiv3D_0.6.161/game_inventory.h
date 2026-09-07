//=============================================================================
// Contents   : game_inventory.h
//              std::listへのアイテム追加、検索、集計、画面表示
// Author     : GU ANYI
// LastUpdate : 2026/07/14
// Since      : 2026/07/14
//=============================================================================

#pragma once

#include <list>
#include "game_inventory_item.h"

class GameInventory
{
private:

    std::list<GameInventoryItem> m_items;

public:

    void AddItem(GameItemType type);
	bool RemoveItem(GameItemType type, int amount);
    int GetItemCount(GameItemType type) const;
    int GetTotalItemCount() const;

    bool IsEmpty() const;
    void Clear();
    void Draw(const Float2& position) const;
};
