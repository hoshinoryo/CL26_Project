#pragma once

#include "primitive.h"

namespace MyTriangle
{
	class Triangle : public Primitive
	{
	private:

		Primitive* m_pPrimitive{ nullptr };
		Float2 m_Offset{};

	public:

		Triangle() = default;

		Triangle(Primitive* pPrimitive, const Float2& offset)
			:m_pPrimitive(pPrimitive), m_Offset(offset) {

		}

		~Triangle() = default;

		void Draw(const Float2& position) const override
		{
			if (m_pPrimitive)
			{
				m_pPrimitive->Draw(position);
			}

			const Float2 draw_position = position + m_Offset;

			s3d::Triangle{
				draw_position + Float2{ 0.0f, -55.0f },
				draw_position + Float2{ -70.0f, 40.0f },
				draw_position + Float2{ 70.0f, 40.0f }
			}
				.draw(ColorF{ 0.72, 0.65, 0.52 })
				.drawFrame(4.0, ColorF{ 0.42, 0.35, 0.25 });
		}
	};
}

