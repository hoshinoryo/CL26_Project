//=============================================================================
// Contents   : Main.cpp
// Author     : GU ANYI
// LastUpdate : 2026/09/16
// Since      : 2026/06/09
//=============================================================================

# include <Siv3D.hpp> // Siv3D v0.6.16

#include "primitive.h"
#include "skewer.h"
#include "square.h"
#include "circle.h"
#include "triangle.h"


void Main()
{
	Window::Resize(1080, 720);
	Window::SetTitle(U"ちび太のおでん");
	Scene::SetBackground(ColorF{ 0.76, 0.6, 0.41 });

	//const Font title_font{ 38 };

	MySkewer::Skewer skewer;

	MySquare::Square square(&skewer, Float2{ 0.0f, 100.0f }); // ここが飾っているところ！！
	MyCircle::Circle circle(&square, Float2{ 0.0f, 0.0f }); // ここが飾っているところ！！
	MyTriangle::Triangle triangle(&circle, Float2{ 0.0f, -115.0f }); // ここが飾っているところ！！

	while (System::Update())
	{
		triangle.Draw(Float2{ 540.0f, 370.0f });
	}
}
