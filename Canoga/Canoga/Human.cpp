/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#include "Human.h"
#include <iostream>
#include <string>
#include <regex>

/* *********************************************************************
Function Name: Human
Purpose: Default constructor for class Human
Parameters: none
Return Value:none
Local Variables: none
Algorithm: inherits Player's default constructor
Assistance Received: none
********************************************************************* */
Human::Human()  : Player()
{
	Player::setPlayerType("Human");
	m_gameRule = 0;
}

/* *********************************************************************
Function Name: Human
Purpose: default destructor
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Human::~Human()
{
}


/* *********************************************************************
Function Name: verifyInput
Purpose: verify the user input
Parameters: string a_input - user's input
			string a_inputType - type of input , for what purpose
Return Value: bool returns true or false if input is correct which is returned
			  from the corresponding verify functions
Local Variables: none
Algorithm: check input type which is specified in specific segments of the program,
			then check the input for that type, then return true for valid, false for 
			invalid
Assistance Received: none
********************************************************************* */
bool Human::verifyInput(string a_input, string a_inputType) {

	if (a_inputType == "start") {
		return verifyStartGame(a_input);
	}
	else if (a_inputType == "help") {
		return verifyHelp(a_input);
	}
	else if (a_inputType == "roll") {
		return verifyRollDice(a_input);
	}
	else if (a_inputType == "one") {
		return verifyOneRoll(a_input);
	}
	else if (a_inputType == "two") {
		return verifyTwoRoll(a_input);
	}
	else if (a_inputType == "rollchoice") {
		return verifyRollChoice(a_input);
	}
	else if (a_inputType == "cover") {
		return verifyCoverSquare(a_input);
	}
	else if (a_inputType == "uncover") {
		return verifyUncoverSquare(a_input);
	}
	else if (a_inputType == "coveruncover") {
		return verifyCoverUncoverSquare(a_input);
	}
	else if (a_inputType == "number") {
		return verifyNumber(a_input);
	}
	else if (a_inputType == "gamerule") {
		return verifyGameRule(a_input);
	}
	else if (a_inputType == "filename") {
		return verifyFileName(a_input);
	}
	else if (a_inputType == "save") {
		return verifySaveGame(a_input);
	}
	else {
		return false;
	}
	
	return true;
}
/* *********************************************************************
Function Name: verifyGameRule
Purpose: verify the board size number input
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - user's input in lower case
Algorithm: check if input is a number: 9 10 or 11
Assistance Received: none
********************************************************************* */
bool Human::verifyGameRule(string a_selection)
{
	if ((is_number(a_selection) && stoi(a_selection) == 9) || (is_number(a_selection) && stoi(a_selection) == 10) || (is_number(a_selection) && stoi(a_selection) == 11)) {
		return true;
	}
	else return false;
}
/* *********************************************************************
Function Name: verifyHelp
Purpose: verify ask for help input
Parameters: string a_selection - users input
Return Value: true if help valid, false if not
Local Variables: string selection - user's input in lower case
Algorithm: check if input is a request for 'help'
Assistance Received: none
********************************************************************* */
bool Human::verifyHelp(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "help") return true;
	else return false;
}
/* *********************************************************************
Function Name: verifyRollDice
Purpose: verify request for 'roll' dice
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid input
Local Variables: string selection - user's input in lower case
Algorithm: check if input is a request for 'roll'
Assistance Received: none
********************************************************************* */
bool Human::verifyRollDice(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "roll") return true;
	else return false;
}
/* *********************************************************************
Function Name: verifyOneRoll
Purpose: verify request for 'one' die roll
Parameters:  string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - users input in lower case
Algorithm: check if input is a request for 'one' roll die
Assistance Received: none
********************************************************************* */
bool Human::verifyOneRoll(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "one") return true;
	else return false;
}
/* *********************************************************************
Function Name: verifyTwoRoll
Purpose: verify request for 'two' die roll
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - user's input in lower case
Algorithm: check if input is a request for 'two' roll die
Assistance Received: none
********************************************************************* */
bool Human::verifyTwoRoll(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "two") return true;
	else return false;
}
/* *********************************************************************
Function Name: verifyRollChoice
Purpose: verify roll choice
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - user's input in lower case
Algorithm: chec if input is a reuqest for a roll choice
Assistance Received: none
********************************************************************* */
bool Human::verifyRollChoice(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "one" || selection == "two") return true;
	else return false;
}
/* *********************************************************************
Function Name: verifyCoverSquare
Purpose: verify cover or help request
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - users input in lowercase
Algorithm: check if input is a request for cover or help
Assistance Received: none
********************************************************************* */
bool Human::verifyCoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "cover" || selection == "help") return true;
	return false;
}
/* *********************************************************************
Function Name: verifyUncoverSquare
Purpose: verify uuncover or help selection request
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - users input in lowercase
Algorithm: check if input is a request for uncover or help
Assistance Received: none
********************************************************************* */
bool Human::verifyUncoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "uncover" || selection == "help") return true;
	return false;
}
/* *********************************************************************
Function Name: verifyFileName
Purpose: verify file name
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: bool found - flag if file was found
				 string selection - file name in lower case
				 regex_iterator myIterator - iterator to iterate thru returned regex
				 regex_iterator endItertor - end position of returned regex
Algorithm: check file name for any invalid characters
Assistance Received: none
********************************************************************* */
bool Human::verifyFileName(string a_selection)
{
	bool found = false;
	string selection = toLowerCase(a_selection);
	regex findChars("(\\\\|/|:|\\*|\\?|\"|<|>|\\|)");
	regex_iterator<string::iterator> myIterator(selection.begin(), selection.end(), findChars);
	regex_iterator<string::iterator> endIterator;
	while (myIterator != endIterator) {
		found = true;
		myIterator++;
	}
	if (int(selection.length()) < 30 && found == false) {
		return true;
	}
	if (selection == "back") {
		return true;
	}
	else {
		return false;
	}
}
/* *********************************************************************
Function Name: verifyStartGame
Purpose: verify start game choice
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - users input in lower case
Algorithm: check if 'play' 'load' 'quit' request
Assistance Received: none
********************************************************************* */
bool Human::verifyStartGame(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "play" || selection == "load" || selection == "quit")
	{
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: verifyNumber
Purpose: verify if input is number
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: none
Algorithm: check if use input is a number bigger than gamerule number or -1
Assistance Received: none
********************************************************************* */
bool Human::verifyNumber(string a_selection)
{
	if (is_number(a_selection) && stoi(a_selection) <= m_gameRule && stoi(a_selection) >= 1)
	{
		return true;
	}
	else if (a_selection == "-1") {
		return true;
	}
	else 
	{
		return false;
	}
}

/* *********************************************************************
Function Name: verifyCoverUncoverSquare
Purpose: verify cover, uncover, or help request
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - users input to lower case
Algorithm: check if user input equals cover uncover or help
Assistance Received: none
********************************************************************* */
bool Human::verifyCoverUncoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "cover" || selection == "uncover" || selection == "help")
	{
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: verifySaveGame
Purpose: verify saveg game choice
Parameters: string a_selection - users input
Return Value: true if valid, false if invalid
Local Variables: string selection - users input in lower case
Algorithm: check if input is 'yes' or 'no'
Assistance Received: none
********************************************************************* */
bool Human::verifySaveGame(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "yes" || selection == "no") return true;
	return false;
}


/* *********************************************************************
Function Name: toLowerCase
Purpose: change a passed string to lower case
Parameters: string a_selection - string to be changed to lower case
Return Value: lower case string
Local Variables: string lower_str - lower case string
Algorithm: go char by char and turn it into a lower case char
Assistance Received: none
********************************************************************* */
string Human::toLowerCase(string a_selection) {
	string lower_str = a_selection;
	transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
	return lower_str;


}

/* *********************************************************************
Function Name: setGameRule
Purpose: set member variable for game rule
Parameters: int a_gameRule - gameRule member variable
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Human::setGameRule(int a_gameRule)
{
	m_gameRule = a_gameRule;
}

/* *********************************************************************
Function Name: is_number
Purpose: check if passed string is a number
Parameters: const string& s - string
Return Value:  true if number, false if not
Local Variables: none
Algorithm: check every char if its a number or not
Assistance Received: none
********************************************************************* */
bool Human::is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
