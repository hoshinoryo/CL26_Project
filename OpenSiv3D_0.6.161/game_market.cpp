#include "game_market.h"
#include "game_world.h"
#include "game_player.h"

namespace
{
	GamePlayer* FindPlayer(const GameWorld& world)
	{
		GameObjectContainer players = world.GetGameObjects("Player");

		if (players.GetCount() == 0)
		{
			return nullptr;
		}

		return static_cast<GamePlayer*>(players.GetGameObject(0));
	}
}

void GameMarket::Reset()
{
	m_selected_index = 0;
	m_result_message.clear();
}

bool GameMarket::Update(GameWorld& world)
{
	if (KeyEscape.down() || KeyBackspace.down())
	{
		return true;
	}

	if (KeyUp.down() || KeyW.down())
	{
		m_selected_index--;

		if (m_selected_index < 0)
		{
			m_selected_index = 1;
		}
	}

	if (KeyDown.down() || KeyS.down())
	{
		m_selected_index++;

		if (m_selected_index > 1)
		{
			m_selected_index = 0;
		}
	}

	if (KeyEnter.down())
	{
		GamePlayer* player = FindPlayer(world);

		if (!player)
		{
			return true;
		}

		GameItemType purchase_type = GameItemType::Potion;

		if (m_selected_index == 1)
		{
			purchase_type = GameItemType::Sword;
		}

		if (player->PurchaseItem(purchase_type))
		{
			if (purchase_type == GameItemType::Potion)
			{
				m_result_message = U"Purchased Potion";
			}
			else
			{
				m_result_message = U"Purchased Sword";
			}
		}
		else
		{
			m_result_message = U"Not enough Coins";
		}
	}

	return false;
}

void GameMarket::Draw(const GameWorld& world) const
{
	Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.03, 0.04, 0.08, 0.94 });

	const Float2 center = Scene::CenterF();

	int potion_count{};
	int sword_count{};
	int coin_count{};

	const GamePlayer* player = FindPlayer(world);
	if (player)
	{
		const GameInventory& inventory = player->GetInventory();

		potion_count = inventory.GetItemCount(GameItemType::Potion);
		sword_count = inventory.GetItemCount(GameItemType::Sword);
		coin_count = inventory.GetItemCount(GameItemType::Coin);
	}

	m_title_font(U"MARKET").drawAt(center + Float2{ 0.0f, -100.0f }, Palette::Gold);

	m_option_font(Format(U"Coins: ", coin_count))
		.drawAt(center + Float2{ 0.0f, -170.0f }, Palette::Gold);

	const Array<String> options
	{
		Format(U"POTION  -  1 Coin   Owned: ", potion_count),
		Format(U"SWORD  -  2 Coins   Owned: ", sword_count),
	};

	for (int i = 0; i < static_cast<int>(options.size()); i++)
	{
		const Float2 option_position = center + Float2{ 0.0f, -60.0f + i * 80.0f };

		if (i == m_selected_index)
		{
			RectF{Arg::center = option_position, 520.0, 58.0}.draw(ColorF{ 0.9, 0.65, 0.1, 0.45 });

			m_option_font(Format(U"> ", options[i])).drawAt(option_position, Palette::Yellow);
		}
		else
		{
			m_option_font(options[i]).drawAt(option_position, Palette::White);
		}
	}

	if (!m_result_message.isEmpty())
	{
		const Color message_color = (m_result_message == U"Not enough Coins")
			? Palette::Red
			: Palette::Limegreen;

		m_message_font(m_result_message).drawAt(center + Float2{ 0.0f, 135.0f }, message_color);
	}

	m_message_font(U"W/S or Arrow Keys: Select   Enter: Buy")
		.drawAt(center + Float2{ 0.0f, 200.0f }, Palette::Lightgray);

	m_message_font(U"Escape / Backspace: Return")
		.drawAt(center + Float2{ 0.0f, 235.0f }, Palette::Lightgray);
}
