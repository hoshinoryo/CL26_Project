//=============================================================================
// Contents   : game_menu.h
//              メニューシステム
// Author     : GU ANYI
// LastUpdate : 2026/09/07
// Since      : 2026/09/07
//=============================================================================

#pragma once

enum class GameMenuResult
{
	None,
	NextRound,
	Market,
};

class GameMenu
{
private:

	int m_selected_index{};

	Font m_title_font  { 54 };
	Font m_option_font { 34 };
	Font m_message_font{ 22 };

public:

	void Reset();
	GameMenuResult Update();
	void Draw(int completed_round) const;
};
