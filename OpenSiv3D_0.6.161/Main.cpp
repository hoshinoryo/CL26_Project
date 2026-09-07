//=============================================================================
// Contents   : Main.cpp
// Author     : GU ANYI
// LastUpdate : 2026/09/08
// Since      : 2026/06/09
//=============================================================================

# include <Siv3D.hpp> // Siv3D v0.6.16

#include "game_world.h"
//#include "game_player.h"
//#include "game_enemy_spawner.h"
#include "game_menu.h"
#include "game_market.h"
#include "game_round_manager.h"


namespace
{
	enum class GameState
	{
		RoundTitle,
		Playing,
		Menu,
		Market,
		GameOver,
		GameClear,
	};

	void DrawRoundTitle(const Font& title_font, const Font& message_font, int round)
	{
		Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.0, 0.0, 0.0, 0.68 });

		title_font(Format(U"ROUND ", round)).drawAt(Scene::CenterF(), Palette::Gold);
		message_font(U"Press Space to Start").drawAt(Scene::CenterF() + Float2{ 0.0f, 90.0f }, Palette::White);
	}

	void DrawGameOver(const Font& title_font, const Font& message_font, int score)
	{
		Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.0, 0.0, 0.0, 0.72 });

		title_font(U"GAME OVER").drawAt(Scene::CenterF() + Float2{ 0.0f, -100.0f }, Palette::White);
		message_font(Format(U"Score: ", score)).drawAt(Scene::CenterF() + Float2{ 0.0f, -25.0f }, Palette::Gold);
		message_font(U"Press R to Restart").drawAt(Scene::CenterF() + Float2{ 0.0f, 55.0f }, Palette::White);
	}

	void DrawGameClear(const Font& title_font, const Font& message_font, int score)
	{
		Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.0, 0.0, 0.0, 0.72 });

		title_font(U"GAME CLEAR").drawAt(Scene::CenterF() + Float2{ 0.0f, -100.0f }, Palette::Gold);
		message_font(Format(U"Final Score: ", score)).drawAt(Scene::CenterF() + Float2{ 0.0f, -20.0f }, Palette::White);
		message_font(U"Press R to Restart").drawAt(Scene::CenterF() + Float2{ 0.0f, 60.0f }, Palette::White);
	}
}

void Main()
{
    Window::Resize(1080, 720);
    Window::SetTitle(U"CL26-03 STL list Inventory");
    Scene::SetBackground(ColorF{ 0.6, 0.7, 0.8 });

    const Font title_font{ 72 };
    const Font message_font{ 28 };

    GameWorld world;
	GameRoundManager round_manager;
	GameMenu menu;
	GameMarket market;
	GameState state{ GameState::RoundTitle };

	round_manager.StartNewGame(world);

    while (System::Update())
	{
		switch (state)
		{
		case GameState::RoundTitle:
			if (KeySpace.down())
			{
				state = GameState::Playing;
			}
			break;

		case GameState::Playing:
			world.Update(Scene::DeltaTime());

			if (world.IsPlayerDead())
			{
				state = GameState::GameOver;
			}
			else if (round_manager.IsRoundCleared(world))
			{
				if (round_manager.IsLastRound())
				{
					state = GameState::GameClear;
				}
				else
				{
					menu.Reset();
					state = GameState::Menu;
				}
			}
			break;

		case GameState::Menu:
		{
			const GameMenuResult result = menu.Update();

			if (result == GameMenuResult::NextRound)
			{
				round_manager.StartNextRound(world);
				state = GameState::RoundTitle;
			}
			else if (result == GameMenuResult::Market)
			{
				market.Reset();
				state = GameState::Market;
			}
			break;
		}
		case GameState::Market:
		{
			if (market.Update(world))
			{
				state = GameState::Menu;
			}
			break;
		}
		case GameState::GameOver:
		{
			if (KeyR.down())
			{
				round_manager.StartNewGame(world);
				state = GameState::RoundTitle;
			}
			break;
		}
		case GameState::GameClear:
		{
			if (KeyR.down())
			{
				round_manager.StartNewGame(world);
				state = GameState::RoundTitle;
			}
			break;
		}
		}

        world.Draw();

		switch (state)
		{
		case GameState::RoundTitle:
			DrawRoundTitle(title_font, message_font, round_manager.GetCurrentRound());
			break;

		case GameState::Menu:
			menu.Draw(round_manager.GetCurrentRound());
			break;

		case GameState::Market:
			market.Draw(world);
			break;

		case GameState::GameOver:
			DrawGameOver(title_font, message_font, world.GetScore());
			break;

		case GameState::GameClear:
			DrawGameClear(title_font, message_font, world.GetScore());
			break;

		case GameState::Playing:
			break;
		}
    }
}
