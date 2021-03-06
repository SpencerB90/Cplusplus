// TwoPlayerWordGuess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string> //used for string
#include <string.h> //used for char 
#include <fstream> //talking to a file
#include <stdlib.h>
#include <time.h> //random seed
#include <cctype> //used for to lower

using namespace std;
//opening file value used for public 
ifstream file;
// seperate line value used for : in line
string lineOfFile;
string hintWord;
string wordToGuess;
int lineNum;
int endCount = 0;
//all tried letters
string tryed;
//had to use fixed char, hope i input enough space for word to guess from file
char num[35];
//player guess
string guess = "";
//guessed wrong letters
string wrongGuessL;
bool game = true;
int PlayerTwoScore = 0;
int PlayerOneScore = 0;
int temp = 0;

//helper function: 1, for page spacing
void space() {
	cout << endl;
}

//helper function: 2, to pull apart single string and place into hint string and secret word to guess string value 
void seperate() {

	size_t pos = lineOfFile.find(':');

	hintWord = lineOfFile.substr(0, pos);
	wordToGuess = lineOfFile.substr(pos + 1);
}

//helper function: 3, to get rid of spaces before or after begging and ending of word or word phrase
void stripSpaces(string& word) {

	while (true) 
	{
		//sets word to char for beggining spaces
		char c = word[0];
		if (c == ' ') 
		{
			word = word.substr(1);
		}
		else 
		{
			break;
		}
	}

	while (true)
	{
		//sets word to char for ending spaces
		char c = word[word.length() - 1];
		if (c == ' ')
		{
			word = word.substr(0, word.length() - 1);
		}
		else 
		{
			break;
		}
	}
}

//helper function: 4, get number of lines in the full .txt file opened
int numberOfLines(const string& filename) {
	ifstream file;

	file.open(filename);

	if (file.is_open()) 
	{
		int countOfLines = 0;
		while (!file.eof())
		{
			string str;
			getline(file, str);
			ifstream file;
			countOfLines++;
		}
		return countOfLines;
	}
	return 0;
}

//helper function: 5, that opens file and returns one line of text in .txt file passed into main from function, using total lines for parameters of search
string readline(const string& filename, int line) {

	string str;
	ifstream file;

	file.open(filename);

	if (file.is_open()) 
	{
		int countForLines = 0;

		while (!file.eof() && (countForLines < line))
		{
			getline(file, str);
			countForLines++;
		}
	}
	return str;
}

//helper function: 6, to get randomize int then returns int for hint and answer line in .txt file based off 1 to value of total lines in file
int pickRandomWord(int lines) {
	//random seed value
	srand(time(NULL));

	int iSecret = rand() % lines + 1;

	return iSecret;
}

//helper function: 7, that returns count of the letters in secret word minus the spaces for winning game value
int letterCounting() {

	int letterCount = 0;

	for (int i = 0; i < wordToGuess.length(); i++)
	{
		//setting word to guess to char for comparison to itself
		char c = wordToGuess[i];
		if (c == wordToGuess[i] && wordToGuess[i] != ' ')
		{
			letterCount++;
		}
	}
	return letterCount;
}

//helper function: 8, to return bool value that ends game using call to function helper 7 and passed in value of current right letters
bool endIt(int endC) {

	int numCount = letterCounting();

	if (numCount == endC)
	{
		return false;
	}
	return true;
}

//helper function: 9, that returns int for end of game function of right letters guessed, hides then reveals letters in the secret word to guess
int toRevealBlankWord(string& str, string& g) {
	int numRightCount = 0;

	cout << "guess word : ";
	//converting string into char for comparison
	char b = g[0];

	for (size_t i = 0; i < str.length(); i++)
	{
		char c = str[i];
		//double spacing for space inbetween words
		if (c == ' ')
		{
			cout << "  ";
		}
		else if (c == str[i])
		{
			//checking if letter is upper or lower case in guess word and setting error checking for first to lower
			if (isupper(c)) {
				b = toupper(b);
			}
			else if (islower(c)) {
				b = tolower(b);
			}

			//hiding and unhiding secret word to guess letters
			if (b == str[i] || num[i] == str[i])
			{
				num[i] = str[i];
				cout << " " << str[i] << " ";

				//counting letters correct
				numRightCount++;
			}
			else if (num[i] != str[i])
			{
				cout << " _ ";
			}
		}
	}
	return numRightCount;
}

//helper function: 10, that prints out wrong letter choices using bool values to add to list to stop from multiple of same letter
void wrongGuesses(string g) {
	bool isNotThere = true;

	//converting string to char value for comparison
	char y = g[0];

	for (int i = 0; i < wordToGuess.length(); i++)
	{
		//checking if letter is upper or lower case in guess word and setting error checking for first to lower
		if (isupper(wordToGuess[i])) {
			y = toupper(y);
		}
		else if (islower(wordToGuess[i])) {
			y = tolower(y);
		}

		if (y == wordToGuess[i])
		{
			isNotThere = false;
			//breaks out of if/forloop to keep false meaning the letter is in the word
			return;
		}
	}

	if (isNotThere = true)
	{
		cout << "Wrong guess." << endl;
		wrongGuessL += g;
		wrongGuessL += ", ";
	}
}

//helper function: 11, player turn and used to alert player if making same letter choice using recursive function
string playerGo() {

	cout << "Please make a letter guess : ";
	cin >> guess;
	space();

	for (int i = 0; i < tryed.length(); i++)
	{
		if (guess[0] == tryed[i]) 
		{
			cout << "sorry try again, you've already tried this letter" << endl;
			playerGo();
			//kept going into infinate loop of calling function unless return value placed here 
			return guess;
		}
	}
	tryed += guess;
	return guess;
}

//helper function: 12, to keep all letters lowercase
string tolower(string g) {

	for (int i = 0; g[i]; i++)
	{
		g[i] = tolower(g[i]);
	}
	return g;
}

//helper function: 13, revealing winner based off score
void PlayerWin() {

	if (PlayerOneScore > PlayerTwoScore) 
	{
		cout << "Player One Winner!" << endl;		
	}

	else if (PlayerTwoScore > PlayerOneScore) 
	{
		cout << "Player Two Winner!" << endl;		
	}

	else if (PlayerOneScore == PlayerTwoScore)
	{
		cout << "Tie game!" << endl;		
	}
}

int main()
{
	//helper function 4
	lineNum = numberOfLines("answers.txt");

	//helper function 6
	int rand = pickRandomWord(lineNum);
	
	//helper function 5 setting value for helper function 2
	lineOfFile = readline("answers.txt", rand);

	//helper function 2 using lineOfFile value to seperate
	seperate();

	//helper function 3
	stripSpaces(hintWord);
	stripSpaces(wordToGuess);
	space();
	cout << "Welcome to Word Guess" << endl;
	space();
	cout << "Hint: " << hintWord << endl;
	space();
	//helper function 9
	toRevealBlankWord(wordToGuess, guess);

	space();
	space();
	space();

	while (game = true) {
		//player one turn with function helper calls for turn function 11, wrong guess function 10, and to lower for text function 12		
		cout << "Player 1 : ";
		guess = playerGo();
		guess = tolower(guess);		
		wrongGuesses(guess);

		space();
		cout << "Hint: " << hintWord << endl;
		space();
		cout << "wrong letters : " << wrongGuessL << " " << endl;
		space();
		//setting temp value to use for player score and game win value using helper function 9
		temp = toRevealBlankWord(wordToGuess, guess);
		space();
		space();

		//player one score after board reveal
		PlayerOneScore = +temp - PlayerTwoScore;
		cout << "Player One score: " << PlayerOneScore << endl;
		space();
		space();

		//end game function 8 call and values used for it
		endCount = +temp;		
		game = endIt(endCount);
		if (game == false) 
		{		
			PlayerWin();
			break;
		}

		//player Two turn with function helper calls for turn function 11, wrong guess function 10, and to lower for text function 12		
		cout << "Player 2: ";
		guess = playerGo();
		guess = tolower(guess);		
		wrongGuesses(guess);

		space();
		cout << "Hint: " << hintWord << endl;
		space();
		cout << "wrong letters : " << wrongGuessL << " " << endl;
		space();
		//setting temp value to use for player score and game win value helper function 9
		temp = toRevealBlankWord(wordToGuess, guess);
		space();
		space();

		//player two score after board reveal
		PlayerTwoScore = +temp - PlayerOneScore;			
		cout << "Player Two score: " << PlayerTwoScore << endl;
		space();
		space();

		//end game function 8 call and values used for it
		endCount = +temp;		
		game = endIt(endCount);
		if (game == false) 
		{	
			PlayerWin();
			break;			
		}		
	}
}
