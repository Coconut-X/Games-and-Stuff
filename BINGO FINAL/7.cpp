#define NOMINMAX

#include <iostream>								// basic input output library
#include <fstream>								// basic file handling library
#include <string>								// library for string datatype
#include <cstdlib>								// random fuction library
#include <ctime>								// time library used as seed for srand function
#include <chrono>								// library for adding delay in operations
#include <thread>								// library for threading to perfrom multiple functions in multiple threads
#include <Windows.h>							// library for editing console
#include <stdio.h>								// library for formatting of output
#include <mmsystem.h>							// library for multimedia such as sound
#include "help.h"								// custom library for text functions

#pragma comment(lib,"winmm.lib")

using namespace std;


string name1, name2;							// players names
int input;										// input for board by players
int choice;										// options in menu
int ID;											// unique game id
int sizes = 5;									// game board size
int turn = 0;									// turn counter for player turn
int point1 = 0, point2 = 0;						// counter to count number of any row/col/diagonal which is zero
int win1 = 0, win2 = 0;							// scores of both players
int h1 = 0, h2 = 0;								// variable that stores winner as 1
int board1[50][50], board2[50][50];				// random generated boards of each player
int highScores[10];								//stores top 10 high scores
string nameArray[100];							// store names of high scorers


void sound(const wstring& sound, int mod)
{

	if (mod == 1)
		PlaySound((sound.c_str()), NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound((sound.c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

}

void StopSound()
{
	PlaySound(0, 0, 0);
}

// Prototypes
void Play_Game(int);
void Save_Boards();
void Save_Names();
void Save_Scores(int, int);
void Game_Options();
void Remove_File();
void Main_Menu();
void Display_Board(int[50][50]);
void Dimension();

// Save Names of Player in Files
void Save_Names()
{

	ofstream playername1("player1.txt"), playername2("player2.txt");	// Writing the player name to a file

	if (playername1.is_open() && playername2.is_open())
		playername1 << name1, playername2 << name2;

	playername1.close();
	playername2.close();

	ofstream Turn("player turn.txt");

	if (Turn.is_open())
		Turn << turn;

	Turn.close();

}

// Save Scores of Players in Files
void Save_Scores(int win1, int win2)
{

	ofstream scores1("scores1.txt"), scores2("scores2.txt"), GameID("game id.txt");

	if (scores1.is_open() && scores2.is_open() && GameID.is_open()) {

		scores1 << win1;					// Saving the first player's score to the first file
		scores2 << win2;					// Saving the second player's score to the second file
		GameID << ID;

	}

	scores1.close();
	scores2.close();
	GameID.close();

}

// Save Boards of Players in Files
void Save_Boards()
{

	fstream Board_Size;
	fstream Board1, Board2;

	Board1.open("board1.txt", ios::out);
	Board2.open("board2.txt", ios::out);

	if (Board1.is_open() && Board2.is_open())
		for (int i = 0; i < sizes; i++)
			for (int j = 0; j < sizes; j++)
			{
				Board1 << board1[i][j] << endl;
				Board2 << board2[i][j] << endl;
			}

	Board1.close();
	Board2.close();

	Board_Size.open("board size.txt", ios::out);

	if (Board_Size.is_open())
		Board_Size << sizes;

	Board_Size.close();

}

// Load Data of Players into Variables for Game
void Load_Game(string& name1, string& name2, int board1[50][50], int board2[50][50], int& win1, int& win2, int& ID)
{

	string line1, line2;
	fstream Board1, Board2;
	fstream Board_Size;
	fstream playername1Read, playername2Read;
	fstream scores1, scores2, GameID;

	playername1Read.open("player1.txt", ios::in);
	playername2Read.open("player2.txt", ios::in);

	if (playername1Read.is_open() && playername2Read.is_open())
		while (getline(playername1Read, name1) && getline(playername2Read, name2));

	else {

		cout << "\n\nSave File Does not Exist!!!\nEnter Anything to Continue to Main Menu: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.ignore();
		Main_Menu();

	}

	playername1Read.close();
	playername2Read.close();

	Board_Size.open("board size.txt", ios::in);

	if (Board_Size.is_open()) {
		string x;
		while (getline(Board_Size, x));
		::sizes = stoi(x);
	}

	Board_Size.close();

	scores1.open("scores1.txt", ios::in);
	scores2.open("scores2.txt", ios::in);
	GameID.open("game id.txt", ios::in);

	if (scores1.is_open() && scores2.is_open() && GameID.is_open())
	{
		string x;

		while (getline(scores1, x));
		win1 = stoi(x);

		while (getline(scores2, x));
		win2 = stoi(x);

		while (getline(GameID, x));
		ID = stoi(x);

	}

	scores1.close();
	scores2.close();
	GameID.close();

	Board1.open("board1.txt", ios::in);
	Board2.open("board2.txt", ios::in);

	if (Board1.is_open() && Board2.is_open())
		for (int i = 0; i < sizes; i++)
			for (int j = 0; j < sizes && getline(Board1, line1) && getline(Board2, line2); j++)
			{
				board1[i][j] = stoi(line1);
				board2[i][j] = stoi(line2);
			}

	Board1.close();
	Board2.close();

	Play_Game(turn);

}

// Resets data for Highscores and Game History
void Reset_Data()
{

	remove("high scores.txt");
	remove("Game History.txt");

	cout << "History And High Scores Has Been Reset" << endl;

	this_thread::sleep_for(chrono::milliseconds(1000));

	fstream highscore;

	highscore.open("high scores.txt", ios::out);
	highscore.close();

	Main_Menu();

}

// Deletes Previous Data when new game is saved
void Remove_File()
{

	remove("board1.txt");
	remove("board2.txt");
	remove("player1.txt");
	remove("player2.txt");
	remove("scores1.txt");
	remove("scores2.txt");
	remove("board size.txt");
	remove("player turn.txt");

}

// Simulates F11 key press
void pressF11()
{
	keybd_event(VK_F11, 0, 0, 0);
}

void animatedText(const string& text, int delay)
{

	for (char c : text) {
		cout << c;
		this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	cout << endl;

}

void loading()
{

	system("cls");
	drawText(90, 575, 355, 128, 0, 128, "B I N G O");
	Sleep(1500);
	system("cls");
	drawText(50, 800, 355, 128, 0, 128, "BINGO");

	cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t L  O  A  D  I  N  G    P  L  E  A  S  E    W  A  I  T   " << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t";
	animatedText("|||||||||||||||||||||||||||||||||||||||||||||||||||||", 12);
	system("cls");
	cout << "\n\t\t\t\t\t\t\t\t\t\t\tB	I	N	G	O" << endl << endl << endl;

}

void Print_Bingo(bool load = false) {

	system("cls");
	cout << "\t\t\t\t\t\t\t\t\t\t\tB	I	N	G	O" << endl << endl << endl;

	if (load)
		loading();

}

// Generates Unique ID for each game
void unique_ID(int& id)
{
	id = rand() % (99999999 - 10000000 + 1) + 10000000;
}

// Generates Random Board for Player
void boardGenerator(int size, int board[50][50])
{

	int tempSize = size * size;
	int numbers[50 * 50] = {};

	for (int i = 0; i < size * size; i++)
		numbers[i] = i + 1;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {

			int randomIndex = rand() % tempSize--;
			board[i][j] = numbers[randomIndex];

			for (; randomIndex < tempSize; randomIndex++)
				numbers[randomIndex] = numbers[randomIndex + 1];

		}

}

// Prevents re-entry of number which is already deleted or is not in range of 1-sizes*sizes
bool Zero_Checker(int input)
{

	for (int i = 0; i < sizes; i++)
		for (int j = 0; j < sizes; j++)
			if (board1[i][j] == input)
				return (false);

	return (true);

}

// Places zero in both boards in place of input number by player
void Zero_Generator(int a1[50][50], int a2[50][50], int n)
{

	for (int i = 0; i < sizes; i++)
		for (int j = 0; j < sizes; j++)
		{
			// if input number is found in board, set it to zero in both boards
			if (a1[i][j] == n)
				a1[i][j] = 0;

			if (a2[i][j] == n)
				a2[i][j] = 0;

		}

}

// Displays Board of Player
void Display_Board(int arr[50][50])
{

	cout << endl;
	for (int i = 0; i < sizes; i++)
	{
		cout << "\t";
		for (int j = 0; j < sizes; j++)
			cout << "----------------";
		cout << endl;
		cout << "\t|\t";
		for (int j = 0; j < sizes; j++)
			cout << arr[i][j] << "\t|\t";
		cout << endl;
	}
	cout << "\t";
	for (int j = 0; j < sizes; j++)
		cout << "----------------";
	cout << endl << endl;

}

// Takes username of both players after each game
void username(string& name1, string& name2)
{

	Print_Bingo();
	cin.ignore();

	cout << " Enter Player 1 Name: " << endl;
	cout << "\t\t\t";
	getline(cin, name1);

	cout << endl << " Enter Player 2 Name: " << endl;
	cout << "\t\t\t";
	getline(cin, name2);

	Print_Bingo();

}

// Controls both Players Turns
void Player_Turn(string name, int playersBoard[50][50], int opponentsBoard[50][50])
{

	bool correctInput = true;

	cout << name << "'s Turn:";
	Display_Board(playersBoard);

	// Take Input until User enters Valid Number
	do {

		cout << "Enter a Number,\n\t\t Press -1 to Save and Quit\n\nOption: ";
		cin >> input;

		if (cin.fail()) {

			correctInput = true;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input! Please enter an integer." << endl;

		}
		else if (input == -1) {

			if (name == name1)
				turn = 2;
			else
				turn = 1;

			Save_Names();
			Save_Boards();
			Save_Scores(win1, win2);
			Main_Menu();

		}
		else
			correctInput = (input == 0) ? true : Zero_Checker(input);


		if (correctInput)
			cout << endl << "Please Enter Number Present in Board Above" << endl;

	} while (correctInput);

	// Replacing Input Number with 0
	Zero_Generator(playersBoard, opponentsBoard, input);

}

// Counts how many rows/ columns/ diagonals are zero
void Score_Increaser(int a[50][50], int& s)
{

	bool completeRow, completeCol, completeDiagonal = true, completeAntiDiagonal = true;
	s = 0;

	for (int i = 0; i < sizes; i++) {

		completeRow = true;
		completeCol = true;

		for (int j = 0; j < sizes; j++) {

			if (a[i][j] != 0)
				completeRow = false;
			if (a[j][i] != 0)
				completeCol = false;

		}

		if (a[i][i] != 0)
			completeDiagonal = false;
		if (a[i][sizes - 1 - i] != 0)
			completeAntiDiagonal = false;

		if (completeRow)
			s++;
		if (completeCol)
			s++;

	}

	if (completeDiagonal)
		s++;
	if (completeAntiDiagonal)
		s++;

}

// handles highscores functions
void High_Score(int win1, int win2)
{

	fstream highscore;

	Print_Bingo(true);

	cout << " T O P   H I G H S C O R E S : " << endl << endl;

	highscore.open("high scores.txt", ios::in);

	if (highscore.is_open()) {

		int index = 0;

		while (getline(highscore, nameArray[index]))
			highscore >> highScores[index++], highscore.ignore();

		highscore.close();

		for (int i = 0; i < index; i++)
			for (int j = 0; j < index - i - 1; j++)
				if (highScores[j] < highScores[j + 1])
					swap(nameArray[j], nameArray[j + 1]), swap(highScores[j], highScores[j + 1]);

		for (int i = 0; i < 10 && highScores[i]; i++)
			cout << i + 1 << ". " << nameArray[i] << ": " << highScores[i] << endl;

	}

	cout << endl << endl;

	do {

		cout << " Press 1 to go to Main Menu: ";
		cin >> choice;

		if (cin.fail()) {

			cin.clear();	// If the input is not an integer, clear the error flag and ignore the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Input! Please enter an integer." << endl;
			choice = 0; // Set choice to 0 to repeat the loop

		}

		else if (choice == 1)
			Main_Menu();

		else
			cout << "Invalid Input! Try Again" << endl;

	} while (choice != 1);

}

//history
void history()
{

	fstream History;

	Print_Bingo(true);

	cout << "\n\n\nG A M E   H I S T O R Y : " << endl << endl;

	History.open("Game History.txt", ios::in | ios::app);

	if (History.is_open()) {

		History << "\n";
		History.seekg(0, ios::beg);
		cout << History.rdbuf();

	}
	else
		cout << "Error Opening This File.";

	History.close();

	do {

		cout << "Press 1 to go to Main Menu: ";
		cin >> choice;

		if (cin.fail()) {

			cin.clear();	// If the input is not an integer, clear the error flag and ignore the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Input! Please enter an integer." << endl;
			choice = 0; // Set choice to 0 to repeat the loop

		}

		else if (choice == 1)
			Main_Menu();

		else
			cout << endl << "Invalid Input! Try Again" << endl << endl;

	} while (choice != 1);

}

// Player wins if points are equal to dimension of board
bool winner(string name, int s)
{

	if (s < 1)
		return false;

	cout << name << " Wins" << endl;
	return true;

}

void game_Instructions()
{

	fstream Instructions;

	sound(L"instructions", 2);
	Print_Bingo(true);
	system("cls");
	system("color 06");


	Instructions.open("instructions.txt", ios::in);

	if (Instructions.is_open())
		cout << Instructions.rdbuf();
	else
		cout << "Unable to open the file 'instructions.txt' for reading.\n";

	Instructions.close();


	do {

		cout << " Press 1 to go to Main Menu: ";
		cin >> choice;

		if (cin.fail()) {

			cin.clear(); // If the input is not an integer, clear the error flag and ignore the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Input! Please enter an integer." << endl;
			choice = 0; // Set choice to 0 to repeat the loop

		}

		else if (choice == 1)
			Main_Menu();

		else
			cout << " Invalid Input! Try Again" << endl << endl;

	} while (choice != 1);

}

//Starts Game
void Game_Options()
{

	Print_Bingo();

	for (int i = 0; i < 10; i++)
		cout << endl;

	cout << "Enter an option to continue: \n\t\t1. New Game\n\t\t2. Load Game\n\t\t3. Main Menu" << endl;

	do {

		cin >> choice;

		if (cin.fail()) {

			cin.clear();	// If the input is not an integer, clear the error flag and ignore the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Input! Please enter an integer." << endl;
			choice = 0; // Set back to true to repeat the loop

		}
		else if (choice == 1) {

			unique_ID(ID);
			username(name1, name2);
			Dimension();
			Play_Game(turn);

		}
		else if (choice == 2)
			Load_Game(name1, name2, board1, board2, win1, win2, ID);

		else if (choice == 3)
			Main_Menu();

		else
			cout << "\nInvalid Input\n";

	} while (choice < 1 || choice > 3);

}

void Dimension()
{

	system("color 02");
	Print_Bingo();

	cout << "\n\nEnter dimension for your game" << endl;

	do {

		sizes = 5;

		if (cin >> sizes)
			if (sizes <= 0)
				cout << "\nInvalid Input!: " << endl;
			else
				break;

		else {

			// If the input is not an integer, clear the error flag and ignore the input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Input!: " << endl;

		}

	} while (true);

	boardGenerator(sizes, board1);
	boardGenerator(sizes, board2);

}

void Play_Game(int turn)
{

	fstream highscore, History;

	Remove_File();
	system("color 02");
	system("cls");
	sound(L"fight", 1);
	cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tG A M E	 S T A R T ";
	Sleep(3000);
	sound(L"play game", 2);
	Print_Bingo();

	do {

		if (turn % 2 == 0) {

			Print_Bingo();

			cout << "Game ID: " << ID << endl << endl;

			Player_Turn(name1, board1, board2);
			Score_Increaser(board1, point1);
			Score_Increaser(board2, point2);
			winner(name1, point1);

			if (winner(name1, point1)) {

				Print_Bingo();

				::h1 = 1;
				win1 += 1;

				cout << name1 << " Wins" << endl;
				cout << name1 << "'s Board " << endl;
				Display_Board(board1);
				cout << name1 << "'s Score: " << win1 << endl << endl;
				cout << name2 << "'s Board " << endl;
				Display_Board(board2);
				cout << name2 << "'s Score: " << win2 << endl;

				break;

			}
			else if (winner(name2, point2)) {

				Print_Bingo();

				::h2 = 1;
				win2 += 1;

				cout << name2 << " Wins" << endl;
				cout << name2 << "'s Board " << endl;
				Display_Board(board2);
				cout << name2 << "'s Score: " << win2 << endl << endl;
				cout << name1 << "'s Board " << endl;
				Display_Board(board1);
				cout << name1 << "'s Score: " << win1 << endl << endl;

				break;

			}

		}

		//if random was not even, set it to even so it gets his turn next time
		turn = 2;

		Print_Bingo();

		cout << "Game ID: " << ID << endl << endl;

		Player_Turn(name2, board2, board1);
		Score_Increaser(board2, point2);
		Score_Increaser(board1, point1);
		winner(name2, point2);

		if (winner(name2, point2)) {
			Print_Bingo();

			::h2 = 1;
			win2 += 1;

			cout << name2 << " Wins" << endl;
			cout << name2 << "'s Board " << endl;
			Display_Board(board2);
			cout << name2 << "'s Score: " << win2 << endl << endl;
			cout << name1 << "'s Board " << endl;
			Display_Board(board1);
			cout << name1 << "'s Score: " << win1 << endl << endl;

			break;

		}
		else if (winner(name1, point1)) {

			Print_Bingo();

			::h1 = 1;
			win1 += 1;

			cout << "Game ID: " << ID << endl << endl;
			cout << name1 << " Wins" << endl;
			cout << name1 << "'s Board " << endl;
			Display_Board(board1);
			cout << name1 << "'s Score: " << win1 << endl << endl;
			cout << name2 << "'s Board " << endl;
			Display_Board(board2);
			cout << name2 << "'s Score: " << win2 << endl;

			break;

		}

	} while (true);

	History.open("Game History.txt", ios::out | ios::app);

	if (History.is_open()) {

		History << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tG A M E   I D : " << ID << "\n\t\t\t\t\t\t\t\t Players: \n\t\t\t\t\t\t\t\t\t" << name1 << "\n\t\t\t\t\t\t\t\t\t" << name2 << endl;

		if (h1 > h2)
			History << "\n \t\t\t\t\t\t\t\t Winner: " << name1;
		else
			History << "\n \t\t\t\t\t\t\t\t Winner: " << name2;

		History << "\n\t\t\t\t\t\t\t\t------------------------------------------------------------------------------------------\n\n\n\n";

	}

	History.close();

	highscore.open("high scores.txt", ios::in);

	if (!highscore.is_open()) {

		highscore.close();
		highscore.open("high scores.txt", ios::out);

		if (::h1)
			highscore << name1 << endl << ::h1 << endl;

		else if (::h2)
			highscore << name2 << endl << ::h2 << endl;

		highscore.close();

	}
	else {

		bool flag1 = false, flag2 = false;
		int index = 0;

		while (getline(highscore, nameArray[index]))
			highscore >> highScores[index++], highscore.ignore();

		highscore.close();

		for (int i = 0; i < index; i++)
			if (::h1 && nameArray[i] == name1)
				highScores[i]++, flag1 = true;
			else if (::h2 && nameArray[i] == name2)
				highScores[i]++, flag2 = true;

		if (::h1 && !flag1)
			nameArray[index] = name1, highScores[index++] = 1;

		else if (::h2 && !flag2)
			nameArray[index] = name2, highScores[index++] = 1;

		highscore.open("high scores.txt", ios::out);

		for (int i = 0; i < index; i++)
			highscore << nameArray[i] << endl << highScores[i] << endl;

		highscore.close();

	}

	::h1 = 0;
	::h2 = 0;

	cout << endl << " Select to continue: " << endl;

	do {

		cout << "\t\t1. Play again\n\t\t2. Menu" << endl << endl << " Option: ";
		cin >> choice;

		if (cin.fail()) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Input! Please enter a valid number." << endl;
			choice = 0; // Set choice to 0 to repeat the loop

		}
		else if (choice == 1) {

			boardGenerator(sizes, board1);
			int turn = rand() % (100) + 1;  //generates random number to give turn to any of the player, if random is even, player1 will begin first.
			boardGenerator(sizes, board2);
			Play_Game(turn);

		}
		else if (choice == 2)
			Main_Menu();

		else
			cout << "Invalid Input!" << endl;

	} while (choice != 1 && choice != 2);

}

void Exit_Game()
{

	system("color 0D");
	sound(L"game over", 2);

	Print_Bingo();

	for (int i = 0; i < 10; i++)
		cout << endl;

	cout << "\t\t\t\t\t\t\t\t";

	animatedText("T H A N K\t\tY O U\t\tF O R\t\tP L A Y I N G\t\t:)", 50);
	StopSound();

	for (int i = 0; i < 10; i++)
		cout << endl;

	this_thread::sleep_for(chrono::milliseconds(3000));
	pressF11();

	system("cls");
	cout << "\n\n\n\n\t\t\t\t\t\t C O M E   A G A I N  :)\n\n\n";

	exit(0);

}

void Main_Menu()
{

	srand(time(0));

	sound(L"main", 2);
	system("color E0");
	//system("color BD");

	win1 = 0;
	win2 = 0;

	loading();

	for (int i = 0; i < 10; i++)
		cout << endl;

	cout << "\t\t\t What Would You Like to do\? " << endl << endl;
	cout << "\t\t\t\t\t1. Play Game\n\t\t\t\t\t2. High Score\n\t\t\t\t\t3. Game Instructions\n\t\t\t\t\t4. History\n\t\t\t\t\t5. Reset Game Data(History and Highscores)\n\t\t\t\t\t6. Exit\n\t\t\tOption: ";

	do {

		cin >> choice;

		if (cin.fail()) {

			cin.clear();	// If the input is not an integer, clear the error flag and ignore the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Input! Please enter a valid number.\nOption: " << endl;
			choice = 0; // Set runs to true to repeat the loop

		}
		else if (choice == 1)
			Game_Options();

		else if (choice == 2)
			High_Score(win1, win2);

		else if (choice == 3)
			game_Instructions();

		else if (choice == 4)
			history();

		else if (choice == 5)
			Reset_Data();

		else if (choice == 6)
			Exit_Game();

		else
			cout << "Invalid Input! " << endl << endl;

	} while (choice < 1 || choice > 6);

}

int main()
{

	pressF11();											//game starts with full screen
	system("color E0");									//background and font colour
	
	Main_Menu();

	system("pause");

	return 0;

}