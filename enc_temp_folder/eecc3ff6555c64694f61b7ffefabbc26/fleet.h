#include <string>

using namespace std;

struct ship
{
	string name;
	int length;
	int health;
	int startposX;
	int startposY;
	int endposX = 0;
	int endposY = 0;
};

struct fleet
{
	ship Carrier;
	ship Battleship;
	ship Cruiser;
	ship Submarine;
	ship Destroyer;
};