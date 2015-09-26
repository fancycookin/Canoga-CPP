#pragma once
#include "Human.h"
#include "Computer.h"
#include "BoardView.h"
#include "Board.h"
class Game
{
public:
	Game();
	Game(Human& a_human, Computer& a_computer);
	~Game();
	int getGameRule();
	static string getInputFromUser(Human &a_user, string a_inputType);
	bool playGame(int a_roundNumber);

	Human *m_human;
	Computer *m_computer;
	Player *m_firstPlayer;
	bool setGameRule(string a_gameRule);
	bool setGameRule(int a_gameRule);
	int m_gameRule;
	bool isWon();
	void setWon(Player& a_player);
	bool isFirstPlay();
	void setIsFirstPlay();

	void setLoadedRound(vector<string> a_computerRow, vector<string> a_humanRow);



	void setNewRound();
	void askGameRule();
	void askSaveGame();
	Player* getWinner();
	Player* getFirstPlayer();
	Board* getBoardObjet();
	BoardView* getBoardViewObject();

	bool playRound();
	int rollDice(Player& a_player);
	int rollDie(Player& a_player);
	//bool playTurn();
	void setFirstPlayer();

	int m_playerDiceSum, m_computerDiceSum;
	Computer::Moves m_computerMoves;
	bool saveGame();
	bool isGameStarted();
	bool isLoaded();
	void setIsLoaded(bool a_flag);
	bool m_diceFile;
private:
	bool m_gameStarted;
	bool m_isWonGame;
	bool m_firstPlay;
	bool m_didHumanMove;
	bool m_didComputerMove;
	bool m_isLoaded;

	BoardView m_boardView;
	Board m_board;



};

