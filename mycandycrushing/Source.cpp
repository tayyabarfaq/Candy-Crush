#include<iostream>
#include<conio.h>
#include<cstdlib>
#include"help.h"
#include<dos.h>
#include<stdlib.h>
#include<time.h>
#include <chrono>
#include <ctime>


using namespace std;

int elapsed = 0; int score = 0;
void Cross(int x, int y)                                            //shape=cross
{
	myLine(x, y, x + 40, y + 26, 255, 192, 203, 20);
	myLine(x + 40, y, x, y + 26, 255, 192, 203, 20);
}

void Rectangle(int x, int y)                                         //shape=square
{
	myRectangle(x, y, x + 50, y + 35, 75, 0, 110, 75, 0, 110);
}

void Circle(int x, int y)                                             //shape=circle
{
	myEllipse(x, y, x + 50, y + 35, 255, 215, 0, 255, 215, 0);
}

void Triangle(int x, int y, int r, int g, int b)                          //shape=triangle
{
	myLine(x, y, x - 23, y + 20, r, g, b, 20);
	myLine(x - 22, y + 20, x + 23, y + 20, r, g, b, 20);
	myLine(x, y, x + 23, y + 20, r, g, b, 20);
}

void Diamond(int x, int y)                                    //shape=diamond
{
	Triangle(x, y - 4, 0, 255, 0);
	Triangle(x, y + 12, 0, 255, 0);
}

void boxes(int x1, int y1, int x2, int y2)
{
	myLine(x1, y1, x2, y2, 255, 255, 255, 1);
	myLine(x1, y1, x1, y2 + 68, 255, 255, 255, 1);
	myLine(x1, y1 + 68, x2, y2 + 68, 255, 255, 255, 1);           //grid lines
	myLine(x2, y1, x2, y2 + 68, 255, 255, 255, 1);
}

void cursor(int x1, int x2, int y, int r, int g, int b)
{
	myLine(x1, y, x2, y, r, g, b, 3);                               //for cursor
	myLine(x1, y, x1, y + 57, r, g, b, 3);
	myLine(x1, y + 57, x2, y + 57, r, g, b, 3);
	myLine(x2, y, x2, y + 57, r, g, b, 3);
}

void Score()
{                                         //prints your score
	gotoxy(90, 13);
	cout << "SCORE: " << score;
}

void time()
{
	gotoxy(90, 15);                   //prints your stopwatch
	cout << "REMAINING TIME: " << 60 - elapsed << " seconds";
}

void mainboard(int array[][8], int row)
{
	Score();
	time();

	myRectangle(35, 10, 720, 570, 255, 255, 255, 54, 69, 79);                //background box


	int a = 0;
	int b = 0;
	for (int i = 0; i < 8; i++)
	{
		a = 0;
		for (int j = 0; j < 8; j++)
		{
			boxes(a + 37, b + 10, a + 121, b + 10);
			a = a + 85;
		}
		b = b + 70;                                        //nested loop for grid lines
	}
	int x = 0;
	int y = 0;
	for (int i = 0; i < 8; i++)
	{
		x = 0;
		for (int j = 0; j < 8; j++)
		{

			//this make sure that no comsecutive three shapes will appear in start
			if (j > 1)
			{
				while (array[i][j] == array[i][j - 1] && array[i][j] == array[i][j - 2])
				{
					array[i][j] = 1 + (rand() % 5);
				}
			}
			if (i > 1)
			{
				while (array[i][j] == array[i - 1][j] && array[i][j] == array[i - 2][j])
				{
					array[i][j] = 1 + (rand() % 5);
				}
			}

			//print random shapes
			if (array[i][j] == 0)
				Rectangle(x + 55, y + 25);

			if (array[i][j] == 1)
				Circle(x + 55, y + 25);

			if (array[i][j] == 2)
				Cross(x + 60, y + 30);

			if (array[i][j] == 3)
				Triangle(x + 77, y + 30, 255, 0, 0);

			if (array[i][j] == 4)
				Diamond(x + 80, y + 30);

			x = x + 85;
		}
		y = y + 70;
	}
}

bool fourshapes(int array[][8], int row)
{
	Score();
	int k = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int temp1, temp2, temp3, temp4;
			//4 consecutive horizontal shapes
			if (j < 5)
			{

				temp1 = array[i][j];
				temp2 = array[i][j + 1];
				temp3 = array[i][j + 2];
				temp4 = array[i][j + 3];

				//check for horizontal shapes
				if (temp1 == temp2 && temp1 == temp3 && temp1 == temp4)
				{
					//fill the empty space of destroyed column by random shapes
					array[0][j] = 1 + (rand() % 5);
					array[0][j + 1] = 1 + (rand() % 5);
					array[0][j + 2] = 1 + (rand() % 5);
					array[0][j + 3] = 1 + (rand() % 5);
				}


				score = score + 100;
				return true;

			}
			//4 vertical shapes
			if (i < 5) {

				temp1 = array[i][j];
				temp2 = array[i + 1][j];
				temp3 = array[i + 2][j];
				temp4 = array[i + 3][j];



				//check for 4 shapes
				if (temp1 == temp2 && temp1 == temp3 && temp1 == temp4)
				{
					//fill the empty space of row by random shapes						
					array[0][j] = 1 + (rand() % 5);
					array[1][j] = 1 + (rand() % 5);
					array[2][j] = 1 + (rand() % 5);
					array[3][j] = 1 + (rand() % 5);

					score = score + 100;
					return true;
				}
			}
		}
	}
	return false;
}


bool threeshapes(int array[][8], int row)
{
	Score();
	int temp = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int temp1, temp2, temp3;

			//check for 3 horizontal shapes 
			if (j < 6)
			{
				temp1 = array[i][j];
				temp2 = array[i][j + 1];
				temp3 = array[i][j + 2];

				//check for 3 horizontal shapes
				if (temp1 == temp2 && temp1 == temp3)
				{


					//fill the empty row by random shapes
					array[i][j] = (rand() % 5);
					array[i][j + 1] = (rand() % 5);
					array[i][j + 2] = (rand() % 5);
				}

				score = score + 100;
				return true;
			}

			//check for 3 vertical shapes
			if (i < 6)
			{

				temp1 = array[i][j];
				temp2 = array[i + 1][j];
				temp3 = array[i + 2][j];




				if (temp1 == temp2 && temp1 == temp3)
				{
					//fill the empty spaces of column by random shapes						
					array[i][j] = (rand() % 5);
					array[i + 1][j] = (rand() % 5);
					array[i + 2][j] = (rand() % 5);
				}
				score = score + 100;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	gotoxy(83, 2);
	cout << "Welcome to CANDY CRUSH";
	gotoxy(83, 4);
	cout << "Following are INSTRUCTIONS: ";
	gotoxy(83, 5);
	cout << "1-Use arrow keys to move cursor. ";
	gotoxy(83, 6);
	cout << "2-Press SPACEBAR to select the shape ";
	gotoxy(83, 7);
	cout << "  you want to swap.";
	gotoxy(83, 8);
	cout << "3-Match minimun of three shapes by ";
	gotoxy(83, 9);
	cout << "  swaping";
	gotoxy(83, 10);
	cout << "4-Score more than 1000 to win";
	gotoxy(83, 11);
	cout << "  before 1 minute. ";

	myRectangle(35, 10, 720, 570, 255, 255, 255, 54, 69, 79);        //background box

	int array[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			array[i][j] = rand() % 5;                                    // for assighning numbers to shapes


	auto start = std::chrono::system_clock::now();                    //stopwatch function
	time();
	Score();


	int x = 0;
	int y = 0;
	for (int i = 0; i < 8; i++)
	{
		x = 0;
		for (int j = 0; j < 8; j++)
		{

			//this make sure that no comsecutive three shapes will appear in start
			if (j > 1)
			{
				while (array[i][j] == array[i][j - 1] && array[i][j] == array[i][j - 2])
				{
					array[i][j] = 1 + (rand() % 5);
				}
			}
			if (i > 1)
			{
				while (array[i][j] == array[i - 1][j] && array[i][j] == array[i - 2][j])
				{
					array[i][j] = 1 + (rand() % 5);
				}
			}

			//print random shapes
			if (array[i][j] == 0)
				Rectangle(x + 55, y + 25);

			if (array[i][j] == 1)
				Circle(x + 55, y + 25);

			if (array[i][j] == 2)
				Cross(x + 60, y + 30);

			if (array[i][j] == 3)
				Triangle(x + 77, y + 30, 255, 0, 0);

			if (array[i][j] == 4)
				Diamond(x + 80, y + 30);

			x = x + 85;
		}
		y = y + 70;
	}

	int a = 0;
	int b = 0;
	for (int i = 0; i < 8; i++)
	{
		a = 0;
		for (int j = 0; j < 8; j++)
		{
			boxes(a + 37, b + 10, a + 121, b + 10);
			a = a + 85;
		}
		b = b + 70;                                        //nested loop for grid lines
	}

	int a1 = 40;
	int a2 = 118;
	int b1 = 15;
	bool swapy = false;
	int row = 0;
	int col = 0;
	while (elapsed < 60)
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;         //update stopwatch
		elapsed = elapsed_seconds.count();
		time();

		swapy = false;
		cursor(a1, a2, b1, 255, 0, 0);
		if (_kbhit())
		{

			int key = 0;
			isCursorKeyPressed(key);
			{
				if (key == 3)
				{
					if (a1 < 620)
					{
						cursor(a1, a2, b1, 54, 69, 79);           //cursor to move right
						a1 = a1 + 85;
						a2 = a2 + 85;
						cursor(a1, a2, b1, 255, 0, 0);
						col++;
					}

					if (GetAsyncKeyState(VK_SPACE))
					{                                               // to swap shapes right
						swap(array[row][col], array[row][col - 1]);

						mainboard(array, 8);

						if (fourshapes(array, 8) == true)
						{
							Score();
							swapy = true;
							mainboard(array, 8);
						}

						else if (threeshapes(array, 8) == true)
						{
							Score();
							swapy = true;
							mainboard(array, 8);
						}

						else if (swapy == false)
						{
							swap(array[row][col], array[row][col - 1]);
							mainboard(array, 8);
						}
					}
				}

				else if (key == 4)
				{
					if (b1 < 500)
					{
						cursor(a1, a2, b1, 54, 69, 79);   //cursor to move down
						b1 = b1 + 70;
						cursor(a1, a2, b1, 255, 0, 0);
						row++;
					}
					if (GetAsyncKeyState(VK_SPACE))
					{				                                 // to swap shapes down
						swap(array[row][col], array[row - 1][col]);

						mainboard(array, 8);

						if (fourshapes(array, 8) == true)
						{
							Score();
							swapy = true;

							mainboard(array, 8);
						}

						else if (threeshapes(array, 8) == true)
						{
							Score();
							swapy = true;
							mainboard(array, 8);
						}
						else if (swapy == false)
						{
							swap(array[row - 1][col], array[row][col]);
							mainboard(array, 8);
						}

					}
				}

				else if (key == 1)
				{
					if (a1 > 120)
					{
						cursor(a1, a2, b1, 54, 69, 79);    //cursor to move left
						a1 = a1 - 85;
						a2 = a2 - 85;
						cursor(a1, a2, b1, 255, 0, 0);
						col--;
					}
					if (GetAsyncKeyState(VK_SPACE))
					{                                               //to swap shape left
						swap(array[row][col], array[row][col + 1]);

						mainboard(array, 8);

						if (fourshapes(array, 8) == true)
						{
							Score();
							swapy = true;
							mainboard(array, 8);
						}

						else if (threeshapes(array, 8) == true)
						{
							Score();
							swapy = true;

							mainboard(array, 8);
						}
						else if (swapy == false)
						{
							swap(array[row][col + 1], array[row][col]);
							mainboard(array, 8);
						}

					}
				}
				else if (key == 2)
				{
					if (b1 > 80)
					{
						cursor(a1, a2, b1, 54, 69, 79);     //cursor to move up
						b1 = b1 - 70;
						cursor(a1, a2, b1, 255, 0, 0);
						row--;
					}
					if (GetAsyncKeyState(VK_SPACE))
					{                                               // to swap shapes up
						swap(array[row][col], array[row + 1][col]);

						mainboard(array, 8);

						if (fourshapes(array, 8) == true)
						{
							Score();
							swapy = true;
							mainboard(array, 8);
						}

						else if (threeshapes(array, 8) == true)
						{
							Score();
							swapy = true;
							mainboard(array, 8);
						}

						else if (swapy == false)
						{
							swap(array[row][col + 1], array[row][col]);
							mainboard(array, 8);
						}

					}
				}
			}
		}
	}
	cout << "GAME OVER" << endl;
	Score();
	if (score > 1000)
		cout << "\n************************ YOU WIN *************";
	else
		cout << "\n************************* YOU LOSE ***********";

	_getch();
	return 0;
}