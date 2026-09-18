#pragma once

#include "primitive.h"


namespace MySquare
{
	class Square : public Primitive
	{
	private:

		Primitive* m_pPrimitive{ nullptr };
		Float2 m_Offset{};

	public:

		Square() = default;

		Square(Primitive* pPrimitive, const Float2& offset)
			: m_pPrimitive(pPrimitive)
			, m_Offset(offset)
		{
		}

		~Square() = default;

		void Draw(const Float2& position) const override
		{
			if (m_pPrimitive)
			{
				m_pPrimitive->Draw(position);
			}

			const Float2 draw_position = position + m_Offset;

			RoundRect{
				RectF{
					draw_position.x - 48.0f,
					draw_position.y - 41.0f,
					96.0f,
					82.0f
				},
				12.0
			}
				.draw(ColorF{ 0.95, 0.75, 0.38 })
				.drawFrame(4.0, ColorF{ 0.55, 0.30, 0.12 });
		}
	};
}
