#pragma once

#include "primitive.h"


namespace MySkewer
{
	class Skewer : public Primitive
	{
	public:

		Skewer() = default;

		~Skewer() = default;

		void Draw(const Float2& position) const override
		{
			Line{
				position + Float2{ 0.0f, -180.0f },
				position + Float2{ 0.0f, 180.0f }
			}.draw(10.0, ColorF{ 0.45, 0.25, 0.1 });
		}
	};
}
