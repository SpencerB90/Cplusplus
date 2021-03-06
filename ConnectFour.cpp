// ConnectFour.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;

int winValue;
int boardRow;
int boardCol;
//while game loop value
bool game = true;
int playOne;
int playTwo;
//pointer to a pointer
char** gameBoard;
//char values for winner print out
char letter;

//creates the memory in 2d array for board
void createGB() {
	//10 pointers to rows
	gameBoard = new char*[boardRow];

	//sets pointers for the columns
	for (int i = 0; i < boardRow; i++)
	{
		gameBoard[i] = new char[boardCol];
	}

}

//initiates the board spaces in 2d array
void intboard() {
	for (int i = 0; i < boardRow; ++i)
	{
		for (int j = 0; j < boardCol; ++j)
		{
			gameBoard[i][j] = ' ';
		}
	}
}

//helper 1 - checks values for player input using recursion of calling function in function
int getTurnInput(char Player)
{
	int column;

	cout << "Player '" << Player << "' what column number do you choose? : ";
	cin >> column;

	//check value inside column boundries
	if (column < 1 || column > boardCol)
	{
		cout << "Please select between 1 and " << boardCol << "\n";
		return getTurnInput(Player);
	}

	//check if the top most row of the selected column is empty
	if (gameBoard[0][column - 1] != ' ')
	{
		cout << "Column full, Please Select A Different Column.\n";
		return getTurnInput(Player);
	}
	return column;
}

//prints out player chose in 2d array on game board
void playerGo(int column, char g) {

	//decremented to put value to start 1 less for 0 start point in array
	column = column - 1;

	for (int i = (boardRow - 1); i >= 0; i--)
	{
		if (gameBoard[i][column] == ' ') {
			gameBoard[i][column] = g;
			break;
		}
	}

}

//helper 2 - top, bottom of board layout
void dash(int column) {	
	//corrects for print out of dashs for layout acuracy
	column = column - 1;

	for (int i = 0; i < column; i++)
	{
		cout << "----";
	}
	//ends spacing of dashes to keep layout
	cout << "-----" << endl;
}

//helper 3 - to align numbers in center of column in game
void num(int column) {

	if (column <= 10) {
		for (int i = 1; i <= column; i++)
		{
			cout << "  " << i << " ";
		}
		cout << endl;
	}
	else if (column == 11) {
		for (int i = 1; i <= column -1; i++)
		{
			cout << "  " << i << " ";
		}
		for (int i = 1; i <= 1; i++)
		{
			cout << " " << "11" << " ";
		}
		cout << endl;
	}
	else if (column == 12) {
		for (int i = 1; i <= column - 2; i++)
		{
			cout << "  " << i << " ";
		}
		for (int i = 11; i <= 12; i++)
		{
			cout << " " << i << " ";
		}
		cout << endl;
	}	
}

//prints out game board using helper functions 2 & 3 and 2d array memory created
void printBoard() {
	dash(boardCol);

	for (int i = 0; i < boardRow; i++)
	{
		for (int j = 0; j < boardCol; j++)
		{
			cout << "|  " << gameBoard[i][j];
		}
		cout << "|" << endl;
		dash(boardCol);
	}
	num(boardCol);
}

//makes sure game win value is within board size values
int checkGameSpec(int winGameV) {

	while (winGameV < 3 || winGameV > 12) {
		cout << "Please enter a number between 3 to 12 : ";
		cin >> winGameV;
	}
	return winGameV;
}

//makes sure values passed for board row or column are within game win and board size values
int checkBoard(int rC, int gameWinV) {

	while (rC < gameWinV || rC > 12) {
		cout << "Please enter a number between " << gameWinV << " to 12 : ";
		cin >> rC;
	}
	return rC;
}

//helper 4 - horizontal win check: goes through values to check if either 'X' or 'O' in a column,
//decrementing column -1 to check values equal to gameSpec using bcount value
bool horizontalWin(char playerChar) {

	int bcount = 0;
	for (int i = 0; i < boardRow; i++)
	{
		for (int j = 0; j < boardCol; j++) {

			if (gameBoard[i][j] == playerChar) {
				if (gameBoard[i][j - 1] == playerChar) {
					bcount++;
					if (bcount + 1 == winValue) {
						return true;
					}
				}
			}
		}
	}		
	return false;	
}

//helper 5 - vertical win check: goes through values to check if either 'X' or 'O' in a row,
// decrementing -1 to row checking values equal to gameSpec using bcount value
bool verticalWin(char playerChar) {	

	int bcount = 0;
	for (int i = 0; i < boardRow; i++)
	{
		for (int j = 0; j < boardCol; j++) {

			if (gameBoard[i][j] == playerChar) {
				//so check dosent go below 0
				if (i-1<0){}
				else if (gameBoard[i -1][j] == playerChar) {
					bcount++;
					if (bcount + 1 == winValue) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

//helper 6 - diagonal up win check: goes through values to check if either 'X' or 'O',
// decrementing - 1 up in row and incrementing + 1 in column up equal to gameSpec for win using bcount value
bool diagonalWinUp(char playerChar) {
int bcount = 0;

	for (int i = 0; i < boardRow; i++)
	{
		for (int j = 0; j < boardCol; j++) {

			if (gameBoard[i][j] == playerChar) {
				//so board check dosent go negative
				if (i - 1 < 0) {}
				else if (gameBoard[i - 1][j + 1] == playerChar) {
					bcount++;
					if (bcount + 1 == winValue) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

//helper 7 - diagonal down win check: goes through values to check if either 'X' or 'O' in a row,
// incementing +1 in row and in column down equal to gameSpec for win using bcount value
bool diagonalWinDown(char playerChar) {
	int bcount = 0;

	for (int i = 0; i < boardRow; i++)
	{
		for (int j = 0; j < boardCol; j++) {

			if (gameBoard[i][j] == playerChar) {
				//checks so count dosent go over board value 
				if (i + 1 >= boardRow) {}
				else if (gameBoard[i + 1][j + 1] == playerChar) {
					bcount++;
					if (bcount + 1 == winValue) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

//helper 8 - tie check: reads through board values to check if any spaces are left on the board
bool tie() {
	int bcount = 0;
	for (int i = 0; i < boardRow; i++)
	{
		for (int j = 0; j < boardCol; j++) {
			if (gameBoard[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

//calls helper functions 4,5,6,7,& 8 for end game true or false
//passes player char value and uses if statements for screen print out based on bool return 
bool winTieCheck(char player) {
	bool h = horizontalWin(player);
	bool v = verticalWin(player);
	bool d = diagonalWinUp(player);
	bool d2 = diagonalWinDown(player);
	bool t = tie();

	if (h == true || v == true || d == true || d2 == true) {
		cout << "Player " << player << " Wins!" << endl;
		return false;
	}
	else if(t == true) {
		cout << "Players Tie!" << endl;
		return false;
	}	
	return true;	
}

//helper 9 - page set up and readabiltity
void space() {
	cout << endl;
}

int main ()
{//collapsible space in code
#pragma region Setup
	//ask user for win input: excepts & checks value
	cout << "Welcome to Connect-X \n Please enter how many in a row to win game from 3 to 12 : ";
	cin >> winValue;
	winValue = checkGameSpec(winValue);
	space();
	
	//asks user for row value: excepts & checks value
	cout << "Please enter how many rows you would like the board to have : ";	
	cin >> boardRow;
	boardRow = checkBoard(boardRow, winValue);
	space();

	//asks user for column value: excepts & checks value
	cout << "Please enter how many columns you would like the board to have : ";	
	cin >> boardCol;
	boardCol = checkBoard(boardCol, winValue);
	space();

	//start game printout, calls functions to : create, initialize, & print board & adds print out space
	cout << "GAME START\n" << endl;
	createGB();
	intboard();	
	printBoard();
	space();
#pragma endregion
	while (game == true)
	{	
		//player 1: column check function, add player choice function
		playOne = getTurnInput('X');
		playerGo(playOne , 'X');
		letter = 'X';		
		
		space();
		printBoard();
		space();
		game = winTieCheck(letter);

		if (game == false)
		{
			break;
		}

		//player 2: column check function, add player choice function
		playTwo = getTurnInput('O');
		playerGo(playTwo , 'O');
		letter = 'O';			
		
		space();
		printBoard();
		space();
		game = winTieCheck(letter);

		if (game == false) {
			break;
		}
	}
	delete gameBoard;
	//delete second gameboard 	
	/*for (int i = 0; i < boardRow; ++i) {
		delete[] gameBoard[i];
	}*/
	
}


