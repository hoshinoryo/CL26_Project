/*
    ファイル名：game_damage.h
    作成者：張 楽晨
    作成日：2026/06/11
    内容：攻撃で与えるダメージの種類と合計ダメージを管理するクラス
*/
#pragma once

class GameDamage
{
private:
	float m_lightning{};
	float m_fire{};
	float m_ice{};
	float m_slash{};
	float m_strike{};
	float m_thrust{};

public:
	void SetLightning(float damage) { m_lightning = damage; }
	void SetFire(float damage) { m_fire = damage; }
	void SetIce(float damage) { m_ice = damage; }
	void SetSlash(float damage) { m_slash = damage; }
	void SetStrike(float damage) { m_strike = damage; }
	void SetThrust(float damage) { m_thrust = damage; }

	float GetLightning() const { return m_lightning; }
	float GetFire() const { return m_fire; }
	float GetIce() const { return m_ice; }
	float GetSlash() const { return m_slash; }
	float GetStrike() const { return m_strike; }
	float GetThrust() const { return m_thrust; }

	float GetTotalDamage() const {
		return m_lightning + m_fire + m_ice + m_slash + m_strike + m_thrust;
	}
};
