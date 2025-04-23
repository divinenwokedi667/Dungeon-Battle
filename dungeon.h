#include <map>
#include <iostream>
#include <random>
#include <string>
#include <conio.h>
#include <cstdlib>

int const DEFAULT_SIZE = 8;
double const DEFAULT_LVLREQ = 100.0;
using namespace std;

class Dungeon {
	friend class Player;
public:
	Dungeon();
	Dungeon(int size);
	~Dungeon();
	int CreateChests();
	int connectPlayer(Player& player);
	int collideCheck();
	void printBoard();
	void handleInput();
private:
	int boardSize;
	pair<int, int> goal;
	int chestNum;
	int** board;
	bool winner;
	bool allChests;

	Player* p1;
	map<pair<int, int>, int> chests;
};

class Player {
	friend class Dungeon;
public:
	Player();
	Player(string name);
	~Player();
	void setXp(double experience);
	void gainXp(double experience);
	void setLvlReq(double req);
	bool checkLevel(double xp1, double xp2);
protected:
	string pName;
	double xp;
	int gems;
	int lvl;
	double lvlReq;
	pair<int, int> location;
};