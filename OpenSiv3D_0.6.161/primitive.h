#pragma once

#include <Siv3D.hpp>


class Primitive
{
public:

	Primitive() = default;

	virtual ~Primitive() = default;

	virtual void Draw(const Float2& position) const = 0;
};
