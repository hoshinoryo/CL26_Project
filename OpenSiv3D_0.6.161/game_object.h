/*
    ファイル名：game_object.h
    作成者：張 楽晨
    作成日：2026/06/11
    内容：ゲーム内オブジェクトの基本クラス
*/
#pragma once

class GameDamage;
class GameWorld;

class GameObject
{
private:
	Float2 m_position{};
	bool m_is_destory{ false };
	std::string m_tag;
	GameWorld* m_world{ nullptr };

protected:
	void SetPosition(const Float2& position) { m_position = position; }
	void Destory() { m_is_destory = true; }
	GameWorld* GetWorld() const { return m_world; }

public:
	const Float2& GetPosition() const { return m_position; }
	bool IsDestory() const { return m_is_destory; }
	const std::string& GetTag() const { return m_tag; }

public:
	GameObject(GameWorld* world, const Float2& position, std::string tag)
		: m_position(position)
		, m_tag(tag)
		, m_world(world) {
	}
	virtual ~GameObject() = default;
	virtual void Update(float) {}
	virtual void Draw() const {}
	virtual void Damage(const GameDamage&) {}
	virtual Circle GetCollision() const { return {}; }
};
