//=============================================================================
// Contents   : game_market.h
//              マーケット機能定義
// Author     : GU ANYI
// LastUpdate : 2026/09/08
// Since      : 2026/09/08
//=============================================================================


#pragma once

class GameWorld;

class GameMarket
{
private:

	int m_selected_index{};

	String m_result_message{};

	Font m_title_font{ 58 };
	Font m_option_font{ 30 };
	Font m_message_font{ 26 };

public:

	void Reset();

	bool Update(GameWorld& world);
	void Draw(const GameWorld& world) const;
};
