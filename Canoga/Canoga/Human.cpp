#include "Human.h"
#include <iostream>
#include <string>



Human::Human()
{
}


Human::~Human()
{
}

bool Human::verifyInput(string a_selection)
{
	return true;
}

bool Human::verifyGameRule(string a_selection)
{
	int gameRule;
	try {
		gameRule = stoi(a_selection);
	}
	catch (invalid_argument& e) {
		cerr << e.what() << endl;
		return false;
	}

	if (gameRule < 9 || gameRule > 12) return false;
	return true;
}
