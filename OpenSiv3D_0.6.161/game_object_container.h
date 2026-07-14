/*
    ファイル名：game_object_container.h
    作成者：張 楽晨
    作成日：2026/06/11
    内容：ゲーム内のオブジェクトをまとめて管理するコンテナクラス
*/
#pragma once
#include <cassert>
#include "game_object.h"
class GameObject;

class GameObjectContainer
{
private:
	GameObject** m_objects{};
	size_t m_capacity{};
	size_t m_count{ 0 };

public:
	GameObjectContainer() = default;
	GameObjectContainer(size_t capacity)
		: m_objects(new GameObject* [capacity])
		, m_capacity(capacity) {
	}

	~GameObjectContainer() {
		delete[] m_objects;
	}

	GameObjectContainer& operator=(const GameObjectContainer& container) {
		if (this == &container) {
			return *this;
		}

		delete[] m_objects;
		m_capacity = container.m_capacity;
		m_count = container.m_count;
		m_objects = new GameObject * [m_capacity];

		for (size_t i = 0; i < m_count; ++i) {
			m_objects[i] = container.m_objects[i];
		}

		return *this;
	}

	GameObjectContainer(const GameObjectContainer& container) {
		*this = container;
	}

	size_t GetCount() const { return m_count; }

	GameObject* GetGameObject(size_t index) const {
		assert(m_objects);
		assert(index < m_count);
		return m_objects[index];
	}

	void Register(GameObject* object) {
		assert(m_objects);
		assert(m_count < m_capacity);
		m_objects[m_count++] = object;
	}

	void Remove() {
		for (size_t i = 0; i < m_count;) {
			if (m_objects[i]->IsDestory()) {
				delete m_objects[i];
				m_objects[i] = m_objects[m_count - 1];
				--m_count;
			}
			else {
				++i;
			}
		}
	}

	void DeleteAll() {
		for (size_t i = 0; i < m_count; ++i) {
			delete m_objects[i];
		}
		m_count = 0;
	}
};
