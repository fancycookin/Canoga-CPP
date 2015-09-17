#include "Tournment.h"



Tournment::Tournment()
{
}


Tournment::~Tournment()
{
}

int Tournment::GetRounds()
{
	return m_rounds;
}

void Tournment::newGame()
{
	Game newRound = Game(m_human,m_computer);
	newRound.playRound();
}
