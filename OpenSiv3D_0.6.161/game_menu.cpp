//=============================================================================
// Contents   : game_menu.cpp
//              メニューシステム
// Author     : GU ANYI
// LastUpdate : 2026/09/07
// Since      : 2026/09/07
//=============================================================================

#include "game_menu.h"

void GameMenu::Reset()
{
	m_selected_index = 0;
}

GameMenuResult GameMenu::Update()
{
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
		if (m_selected_index == 0)
		{
			return GameMenuResult::NextRound;
		}

		return GameMenuResult::Market;
	}

	return GameMenuResult::None;
}

void GameMenu::Draw(int completed_round) const
{
	Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.0, 0.0, 0.0, 0.72 });

	const Float2 center = Scene::CenterF();

	m_title_font(Format(U"ROUND ", completed_round, U" CLEAR")).drawAt(center + Float2{ 0.0f, -170.0f }, Palette::Gold);

	const Array<String> options
	{
		U"NEXT ROUND",
		U"MARKET",
	};

	for (int i = 0; i < static_cast<int>(options.size()); ++i)
	{
		const Float2 option_position = center + Float2{ 0.0f, -30.0f + i * 70.0f };

		if (i == m_selected_index)
		{
			RectF{ Arg::center = option_position, 360.0, 54.0 }.draw(ColorF{ 0.9, 0.65, 0.1, 0.45 });
			m_option_font(Format(U"> ", options[i])).drawAt(option_position, Palette::Yellow);
		}
		else
		{
			m_option_font(options[i]).drawAt(option_position, Palette::White);
		}
	}

	m_message_font(U"W/S or Arrow Keys: Select   Enter: Confirm")
		.drawAt(center + Float2{ 0.0f, 160.0f }, Palette::Lightgray);
}
