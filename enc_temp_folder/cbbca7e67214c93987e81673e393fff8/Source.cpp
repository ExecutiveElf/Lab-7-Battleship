/* Benjamin Roe
 C++ Fall 2019
 Due November 14
 Lab 7 Battleship
For this lab you will make a simple battleship game. If you’re not familiar with the game,
some quick internet searches should help. For this lab, you will need four 10 x 10 grids
(two for the user and two for the computer). The program will begin with setup. The program
will need to randomly place the computers 5 ships, making sure the ships do not overlap or
go off the board.
*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "fleet.h"
//Just declaring functions, as one does.
void waterfill(char friendlyboard[][10], char friendlytarget[][10], char enemyboard[][10]);
void playerShips(char friendlyboard[][10], char enemyboard[][10]);
void print(char friendlyboard[][10], char enemyboard[][10]);
void enemyShips(char friendlyboard[][10], char enemyboard[][10]);
int playerAttack(char friendlyboard[][10], char friendlytarget[][10], char enemyboard[][10]);
int enemyAttack(char friendlyboard[][10], char friendlytarget[][10], char enemyboard[][10]);

int main()
{
	srand(time(NULL)); //Random Seed for Enemy Behavior
	char friendlyboard[10][10];
	char friendlytarget[10][10];
	char enemyboard[10][10];
	waterfill(friendlyboard, friendlytarget, enemyboard); //Initializes the boards to be all water.
	print(friendlyboard, enemyboard); //Displays the boards.
	playerShips(friendlyboard, enemyboard); //Places player ships.
	enemyShips(friendlyboard, enemyboard); //Places enemy ships.
	print(friendlyboard, friendlytarget); //Redisplays the boards.
	/*This do-while loop is supposed to determine when the player has won or lost but instead 
	it crashes the program a turn after it is intended to activate*/
	do{} while (playerAttack(friendlyboard, friendlytarget, enemyboard) == 0 && enemyAttack(friendlyboard, friendlytarget, enemyboard) == 0);
	if (playerAttack(friendlyboard, enemyboard, friendlytarget) == 1)
	{
		cout << "You win!\n\n";
	}
	else if (enemyAttack(friendlyboard, friendlytarget, enemyboard) == 1)
	{
		cout << "You lose!\n\n";
	}
	return 0;
}

void waterfill(char friendlyboard[][10], char friendlytarget[][10], char enemyboard[][10])
{ //Initializes the three arrays (yes, I know it said 4, sorry) to all be filled with water.
	for (int flood2 = 0; flood2 < 10; flood2++)
	{
		for (int flood1 = 0; flood1 < 10; flood1++)
		{
			friendlyboard[flood1][flood2] = '~';
			friendlytarget[flood1][flood2] = '~';
			enemyboard[flood1][flood2] = '~';
		}
	}
	cout << endl;
}

void print (char friendlyboard[][10], char friendlytarget[][10])
{//Displays and formats the player's home board and their targeting board into a nice and pretty little arrangement.
	cout << setw(16) << "      1 2 3 4 5 6 7 8 9 10" << setw(36) << "1 2 3 4 5 6 7 8 9 10";
	cout << endl << setw(16) << "     ____________________" << setw(36) << " ____________________";
	cout << endl << setw(5) << "1|";
	for (int flood2 = 0; flood2 < 10; flood2++)
	{
		for (int flood1 = 0; flood1 < 10; flood1++)
		{
			cout << " " << friendlyboard[flood1][flood2]; //Extra space to make it look better.
		}
		if (flood2 < 9)
		{
			cout << setw(15) << flood2 + 1 << "|";
			for (int flood1 = 0; flood1 < 10; flood1++)
			{
				cout << " " << friendlytarget[flood1][flood2];
			}
			cout << endl << setw(4) << flood2 + 2 << "|";
		}
	}
	cout << setw(15) <<  10 << "|";
	for (int flood1 = 0; flood1 < 10; flood1++)
	{
		cout << " " << friendlytarget[flood1][9];
	}
	cout << endl << endl;
}

void playerShips(char friendlyboard[][10], char enemyboard[][10])
{
	int direction;
	ship fFleet[5];

	fFleet[4].name = "Carrier";
	fFleet[3].name = "Battleship";
	fFleet[2].name = "Cruiser";
	fFleet[1].name = "Submarine";
	fFleet[0].name = "Destroyer";

	for (int i = 4; i >= 0; i--)//Initializes the components of all of the ships.
	{
		fFleet[i].startposX = 0;
		fFleet[i].startposY = 0;
		if (i > 1)
		{
			fFleet[i].length = i;
			fFleet[i].health = i;
		}
		else
		{
			fFleet[i].length = i + 1;
			fFleet[i].health = i + 1;
		}
	}


	for (int i = 4; i >= 0; i--) /*Puts restrictions on where ships can be placed. Unfortunantly the parts intended to prevent
								 */
	{
		cout << endl << "You will be placing the " << fFleet[i].name << ". \nFirst input which column, and then which row you would like to place its start position." << endl << endl;
		cin >> fFleet[i].startposX >> fFleet[i].startposY;
		while (friendlyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1] == '#'
			|| fFleet[i].startposX - 1 > 9 || fFleet[i].startposX - 1 < 0 
			|| fFleet[i].startposY - 1 > 9 || fFleet[i].startposY - 1 < 0
			|| friendlyboard[fFleet[i].startposX - 1][fFleet[i].startposY] != '~'
			&& friendlyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 2] != '~'
			&& friendlyboard[fFleet[i].startposX][fFleet[i].startposY - 1] != '~'
			&& friendlyboard[fFleet[i].startposX - 2][fFleet[i].startposY - 1] != '~')
		{
			cout << "The ship cannot be placed there!" << endl;
			cin >> fFleet[i].startposX >> fFleet[i].startposY;
		}
		cout << endl;
		friendlyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1] = '#';
		cout << "What direction would you like the ship to point?" << endl;
			if (fFleet[i].startposY - fFleet[i].length > 0)
				cout << "	1: Up" << endl;
			if (fFleet[i].startposY + fFleet[i].length < 11)
				cout << "	2: Down" << endl;
			if (fFleet[i].startposX + fFleet[i].length < 11)
				cout << "	3: Right" << endl;
			if (fFleet[i].startposX - fFleet[i].length > 0)
				cout << "	4: Left" << endl;
		cout << endl;
		cin >> direction;
		bool directioncheck = 1;
		int k = 0;
		while (directioncheck == 1)
		{
			switch (direction)
			{
			case 1: //Checks if a ship can go up.
			{
				if (fFleet[i].startposY - fFleet[i].length > 0)
				{
					for (int m = fFleet[i].length; m >= 0; m--)
					{
						friendlyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1 - m] = '#';
					}
					directioncheck = 0;
					break;
				}
				cout << "The ship cannot be placed there! \n \n";
				cin >> direction;
				continue;
			}
			case 2: //Checks if a ship can go down.
			{
				if (fFleet[i].startposY + fFleet[i].length < 11)
				{
					for (int m = fFleet[i].length; m >= 0; m--)
					{
						friendlyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1 + m] = '#';
					}
					directioncheck = 0;
					break;
				}
				cout << "The ship cannot be placed there! \n \n";
				cin >> direction;
				continue;
			}
			case 3: //Checks if a ship can go right.
			{
				if (fFleet[i].startposX + fFleet[i].length < 11)
				{
					for (fFleet[i]; fFleet[i].length >= 0; fFleet[i].length--)
					{
						friendlyboard[fFleet[i].startposX - 1 + fFleet[i].length][fFleet[i].startposY - 1] = '#';
					}
					directioncheck = 0;
					break;
				}
				cout << "The ship cannot be placed there!" << endl << endl;
				cin >> direction;
				continue;
			}
			case 4: //Checks if a ship can go left.
			{
				if (fFleet[i].startposX - fFleet[i].length > 0)
				{
					for (fFleet[i]; fFleet[i].length >= 0; fFleet[i].length--)
					{
						friendlyboard[fFleet[i].startposX - 1 - fFleet[i].length][fFleet[i].startposY - 1] = '#';
					}
					directioncheck = 0;
					break;
				}
				cout << "The ship cannot be placed there!" << endl << endl;
				cin >> direction;
				continue;
			}
			}
		}
		print(friendlyboard, enemyboard);
	}
}

void enemyShips(char friendlyboard[][10], char enemyboard[][10])
{
	cout << "\n Computer opponent's ships will now be genrated. Input anything to continue. \n \n";
	string prompt;
	cin >> prompt;
	int direction;
	ship fFleet[5];

	fFleet[4].name = "Carrier";
	fFleet[3].name = "Battleship";
	fFleet[2].name = "Cruiser";
	fFleet[1].name = "Submarine";
	fFleet[0].name = "Destroyer";

	for (int i = 4; i >= 0; i--)
	{
		fFleet[i].startposX = 0;
		fFleet[i].startposY = 0;
		if (i > 1)
		{
			fFleet[i].length = i;
			fFleet[i].health = i;
		}
		else
		{
			fFleet[i].length = i + 1;
			fFleet[i].health = i + 1;
		}
	}


	for (int i = 4; i >= 0; i--)
	{
		
		fFleet[i].startposX = rand() % 10 + 1;
		fFleet[i].startposY = rand() % 10 + 1;
		cout << endl;
		while (enemyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1] == '#')
		{
			fFleet[i].startposX = rand() % 10 + 1;
			fFleet[i].startposY = rand() % 10 + 1;
		}
		enemyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1] = '#';
		bool directioncheck = 1;
		while (directioncheck == 1)
		{
			direction = rand() % 3 + 1;
			switch (direction)
			{
			case 1: //Checks if a ship can go up.
			{
				if (fFleet[i].startposY - fFleet[i].length > -1)
				{
					for (fFleet[i]; fFleet[i].length >= 0; fFleet[i].length--)
					{
						enemyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1 - fFleet[i].length] = '#';
					}
					directioncheck = 0;
					break;
				}
				direction = rand() % 3 + 1;
				continue;
			}
			case 2: //Checks if a ship can go down.
			{
				if (fFleet[i].startposY + fFleet[i].length < 11)
				{
					for (fFleet[i]; fFleet[i].length >= 0; fFleet[i].length--)
					{
						enemyboard[fFleet[i].startposX - 1][fFleet[i].startposY - 1 + 0 - fFleet[i].length] = '#';
					}
					directioncheck = 0;
					break;
				}
				direction = rand() % 3 + 1;
				continue;
			}
			case 3: //Checks if a ship can go right.
			{
				if (fFleet[i].startposX + fFleet[i].length < 11)
				{
					for (fFleet[i]; fFleet[i].length >= 0; fFleet[i].length--)
					{
						enemyboard[fFleet[i].startposX - 1 + fFleet[i].length][fFleet[i].startposY - 1] = '#';
					}
					directioncheck = 0;
					break;
				}
				direction = rand() % 3 + 1;
				continue;
			}
			case 4: //Checks if a ship can go left.
			{
				if (fFleet[i].startposX - fFleet[i].length > -1)
				{
					for (fFleet[i]; fFleet[i].length >= 0; fFleet[i].length--)
					{
						enemyboard[fFleet[i].startposX - 1 - fFleet[i].length][fFleet[i].startposY - 1] = '#';
					}
					directioncheck = 0;
					break;
				}

				direction = rand() % 3 + 1;
				continue;
			}
			}
		}
	}
}

int playerAttack(char friendlyboard[][10], char friendlytarget[][10], char enemyboard[][10])
{
	int targetX;
	int targetY;
	cout << "It is your turn. To target a postion, first enter its collumn, then its row.\n\n";
	cin >> targetX >> targetY;
	while (enemyboard[targetX - 1][targetY - 1] == 'H' || enemyboard[targetX - 1][targetY - 1] == 'M' 
		|| targetX > 10 || targetX < 1 || targetY > 10 || targetY < 1)
	{
		cout << "Cannot fire there. Please input different coordinates. \n";
		cin >> targetX >> targetY;
	}
	if (enemyboard[targetX - 1][targetY - 1] == '#')
	{
		cout << "Hit! \n";
		enemyboard[targetX - 1][targetY - 1] = 'H';
	}
	if (enemyboard[targetX - 1][targetY - 1] == '~')
	{
		cout << "Miss! \n";
		enemyboard[targetX - 1][targetY - 1] = 'M';
	}
	friendlytarget[targetX - 1][targetY - 1] = enemyboard[targetX - 1][targetY - 1];
	print(friendlyboard, friendlytarget);
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (enemyboard[j][i] == '#')
			{
				cout << "The enemy will now attack. Input anything to continue.\n\n";
				string buffer;
				cin >> buffer;
				return 0;
			}
		}
	}
	return 1;
}

int enemyAttack(char friendlyboard[][10], char friendlytarget[][10], char enemyboard[][10])
{
	int targetX = rand() % 10 + 1;
	int targetY = rand() % 10 + 1;
	while (friendlyboard[targetX - 1][targetY - 1] == 'H' || friendlyboard[targetX - 1][targetY - 1] == 'M'
		|| targetX > 10 || targetX < 1 || targetY > 10 || targetY < 1)
	{
		targetX = rand() % 10 + 1;
		targetY = rand() % 10 + 1;
	}
	if (friendlyboard[targetX - 1][targetY - 1] == '#')
	{
		cout << "The enemy got a hit! \n";
		friendlyboard[targetX - 1][targetY - 1] = 'H';
	}
	if (friendlyboard[targetX - 1][targetY - 1] == '~')
	{
		cout << "The enemy missed! \n";
		friendlyboard[targetX - 1][targetY - 1] = 'M';
	}
	print(friendlyboard, friendlytarget);
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (friendlyboard[j][i] == '#')
			{
				return 0;
			}
		}
	}
	string buffer;
	cin >> buffer;
	return 1;
}