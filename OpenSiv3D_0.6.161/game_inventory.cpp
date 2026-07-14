//=============================================================================
// Contents   : game_inventory.cpp
//              std::listへのアイテム追加、検索、集計、画面表示
// Author     : GU ANYI
// LastUpdate : 2026/07/14
// Since      : 2026/07/14
//=============================================================================

#include "stdafx.h"
#include "game_inventory.h"
#include <algorithm>

void GameInventory::AddItem(GameItemType type)
{
    // 同じ種類のアイテムがあるか、find_ifとラムダ式で検索する
    const auto it = std::find_if(
        m_items.begin(),
        m_items.end(),
        [type](const GameInventoryItem& item)
        {
            return item.GetType() == type;
        });

    if (it != m_items.end())
	{
        it->AddCount();
    }
    else
	{
        // listの末尾に新しいアイテム情報を直接構築する
        m_items.emplace_back(type);
    }
}

int GameInventory::GetItemCount(GameItemType type) const
{
    const auto it = std::find_if(
        m_items.begin(),
        m_items.end(),
        [type](const GameInventoryItem& item)
        {
            return item.GetType() == type;
        });

    if (it == m_items.end())
	{
        return 0;
    }

    return it->GetCount();
}

int GameInventory::GetTotalItemCount() const
{
    int total_count = 0;

    // 範囲for文でlist内の全アイテムを集計する
    for (const GameInventoryItem& item : m_items)
	{
        total_count += item.GetCount();
    }

    return total_count;
}

bool GameInventory::IsEmpty() const
{
    return m_items.empty();
}

void GameInventory::Clear()
{
    m_items.clear();
}

void GameInventory::Draw(const Float2& position) const
{
    constexpr double PANEL_WIDTH = 280.0;
    constexpr double HEADER_HEIGHT = 48.0;
    constexpr double ROW_HEIGHT = 32.0;

    const size_t row_count = m_items.empty() ? 1 : m_items.size();
    const double panel_height = HEADER_HEIGHT + ROW_HEIGHT * static_cast<double>(row_count) + 14.0;
    const RectF panel{ position.x, position.y, PANEL_WIDTH, panel_height };

    panel.draw(ColorF{ 0.08, 0.10, 0.14, 0.82 });
    panel.drawFrame(2.0, Palette::White);

    FontAsset(U"PlayerStatusFont")(
        Format(U"INVENTORY  Total: ", GetTotalItemCount()))
        .draw(position + Float2{ 14.0f, 10.0f }, Palette::White);

    double y = position.y + HEADER_HEIGHT;

    if (m_items.empty()) {
        FontAsset(U"PlayerStatusFont")(U"(No items)")
            .draw(position.x + 18.0, y, Palette::Lightgray);
        return;
    }

    for (const GameInventoryItem& item : m_items)
	{
        FontAsset(U"PlayerStatusFont")(
            Format(U"- ", item.GetName(), U"  x ", item.GetCount()))
            .draw(position.x + 18.0, y, Palette::White);
        y += ROW_HEIGHT;
    }
}
