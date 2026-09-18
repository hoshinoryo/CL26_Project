#pragma once

#include "primitive.h"


namespace MyCircle
{
	class Circle : public Primitive
	{
	private:

		Primitive* m_pPrimitive{ nullptr };
		Float2 m_Offset{};

	public:

		Circle() = default;

		Circle(Primitive* pPrimitive, const Float2& offset)
			: m_pPrimitive(pPrimitive)
			, m_Offset(offset)
		{
		}

		~Circle() = default;

		void Draw(const Float2& position) const override
		{
			if (m_pPrimitive)
			{
				m_pPrimitive->Draw(position);
			}

			const Float2 draw_position = position + m_Offset;

			s3d::Circle{
				draw_position,
				48.0
			}
				.draw(ColorF{ 0.82, 0.55, 0.25 })
				.drawFrame(4.0, ColorF{ 0.50, 0.28, 0.10 });
		}
	};
}
