#pragma once
class Game
{
public:
	Game();
	~Game();
	int GetGameRule();

private:
	int m_gameRule;
	bool SetGameRule();
};

