#include <string>

using namespace std;

struct ship
{//The components of a ship
	string name;
	int length;
	int health;
	int startposX;
	int startposY;
	int endposX = 0;
	int endposY = 0;
};

struct fleet
{//The types of ships.
	ship Carrier;
	ship Battleship;
	ship Cruiser;
	ship Submarine;
	ship Destroyer;
};