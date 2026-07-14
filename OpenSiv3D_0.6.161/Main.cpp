//=============================================================================
// Contents   : Main.cpp
// Author     : GU ANYI
// LastUpdate : 2026/07/14
// Since      : 2026/06/09
//=============================================================================

# include <Siv3D.hpp> // Siv3D v0.6.16

#include "game_world.h"
#include "game_player.h"
#include "game_enemy_spawner.h"

void SetupGame(GameWorld& world)
{
    world.Clear();
    world.SetScore(0);

    world.Register(new GamePlayer(&world, Scene::CenterF()));
	world.Register(new GameEnemySpawner(&world, { Scene::Size().x * 0.15f, Scene::Size().y * 0.3f }));
    world.Register(new GameEnemySpawner(&world, Scene::Size() * 0.85f));
}

void DrawGameOver(const Font& title_font, const Font& message_font, int score)
{
    Rect{ 0, 0, Scene::Width(), Scene::Height() }.draw(ColorF{ 0.0, 0.0, 0.0, 0.65 });

    title_font(U"GAME OVER").drawAt(Scene::CenterF() + Float2{ 0.0f, -100.0f }, Palette::White);
    message_font(Format(U"Score: ", score)).drawAt(Scene::CenterF() + Float2{ 0.0f, -25.0f }, Palette::Gold);
    message_font(U"Rキーでリスタート").drawAt(Scene::CenterF() + Float2{ 0.0f, 35.0f }, Palette::Yellow);
    message_font(U"Press R to Restart").drawAt(Scene::CenterF() + Float2{ 0.0f, 75.0f }, Palette::White);
}

void Main()
{
    Window::Resize(1080, 720);
    Window::SetTitle(U"CL26-03 STL list Inventory");
    Scene::SetBackground(ColorF{ 0.6, 0.7, 0.8 });

    const Font title_font{ 64 };
    const Font message_font{ 28 };

    GameWorld world;
    bool is_game_over{ false };

    SetupGame(world);

    while (System::Update())
	{
        if (!is_game_over)
		{
            world.Update(Scene::DeltaTime());

            if (world.IsPlayerDead())
			{
                is_game_over = true;
            }
        }
        else {
            if (KeyR.down())
			{
                SetupGame(world);
                is_game_over = false;
            }
        }

        world.Draw();

        if (is_game_over)
		{
            DrawGameOver(title_font, message_font, world.GetScore());
        }
    }
}
