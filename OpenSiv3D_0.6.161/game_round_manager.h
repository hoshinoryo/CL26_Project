#pragma once

class GameWorld;

class GameRoundManager
{
private:

	static constexpr int LAST_ROUND{ 3 };

	int m_current_round{ 1 };

public:

	void StartNewGame(GameWorld& world);
	void StartNextRound(GameWorld& world);

	bool IsRoundCleared(const GameWorld& world) const;
	bool IsLastRound() const;

	int GetCurrentRound() const { return m_current_round; }

private:

	int getSpawnLimit() const;
	void setupRound(GameWorld& world) const;
};
