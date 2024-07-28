#include<conio.h>	//Console input/output - to get player inputs
#include<iostream>	//Standard Input and Output Library of C++
#include<Windows.h>	//Windows API Library

using std::cout;
using std::endl;
const int width = 80;	//width of the border
const int height = 20;	//height of the border
int SnakeHeadX, SnakeHeadY;	//Snake head coordinates
int fruitX, fruitY;	//Food coordinates
int playerScore;	//storing player score
int tailX[100], tailY[100];	//array to store Tail position
int nTail;	//The length of the tail
enum class eDirection {STOP=0,LEFT, RIGHT, UP, DOWN};	//storing snake's direction
eDirection dir;	//eDirection variable
bool gameOver;	//boolean to check game over

void GameInit() /*Initializing the game variable*/
{
	gameOver = false;
	dir = eDirection::STOP;
	SnakeHeadX = width / 2;	//Location of the snake head (X) at start of the game
	SnakeHeadY = height / 2;	//Location of the snake head (SnakeHeadY) at start of the game
	fruitX = rand() % width;	//Location of fruit (X) at start of the game randomly
	fruitY = rand() % height;	//Location of fruit (SnakeHeadY) at start of the game randomly
	playerScore = 0;
}

void GameRenderer() /*for creating board and rendering*/
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; i++){
		for (int j = 0; j <= width; j++){
			if (j == 0 || j == width) {
				cout << "|";
			}
			if (i == SnakeHeadY && j == SnakeHeadX) {
				cout << "X";	//Print out the head of the snake as 'Y'
			}
			else if (i == fruitY && j == fruitX) {
				cout << "#";	//Represent the fruit as '#'
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++){
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";	//Print out the tail as 'o'
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	//creating bottom border
	for (int i = 0; i < width + 2; i++) {
		cout << "-";
	}
	cout << endl;
	cout << "playerScore: " << playerScore << endl;
}

void GameUpdate()	/*dating the game state*/
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = SnakeHeadX;
	tailY[0] = SnakeHeadY;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir){
	case eDirection::LEFT:
		SnakeHeadX--;
		break;
	case eDirection::RIGHT:
		SnakeHeadX++;
		break;
	case eDirection::UP:
		SnakeHeadY--;
		break;
	case eDirection::DOWN:
		SnakeHeadY++;
		break;
	}

	//Check collision with wall
	if (SnakeHeadX >= width || SnakeHeadX < 0 || SnakeHeadY >= height || SnakeHeadY < 0) {	//Condition for snake hitting the wall - game over
		gameOver = true;
	}
	//Check collision with tail
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == SnakeHeadX && tailY[i] == SnakeHeadY)
			gameOver = true;
	}
	//Check for snake's collision with food
	if (SnakeHeadX == fruitX && SnakeHeadY == fruitY) {
		playerScore += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
void PlayerInput()	/*Handle user input*/
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = eDirection::LEFT;
			break;
		case 'd':
			dir = eDirection::RIGHT;
			break;
		case 'w':
			dir = eDirection::UP;
			break;
		case 's':
			dir = eDirection::DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}


int main() {
	GameInit();
	while (!gameOver){
		GameRenderer();
		PlayerInput();
		GameUpdate();
		Sleep(100);
	}
	system("cls");

	return 0;
}