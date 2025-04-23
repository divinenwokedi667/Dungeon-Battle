#include "dungeon.h"

Dungeon::Dungeon() {
	boardSize = DEFAULT_SIZE;
	board = new int* [DEFAULT_SIZE];
	chestNum = boardSize * .66;
	goal.first = boardSize - 1;
	goal.second = boardSize - 1;
	winner = false;
	allChests = false;


	for (int i = 0; i < DEFAULT_SIZE; i++) { //initialize dungeon "board"
		board[i] = new int[DEFAULT_SIZE];
	}

}

Dungeon::Dungeon(int size) {
	boardSize = size;
	board = new int*[boardSize];
	chestNum = boardSize * .66;
	goal.first = boardSize - 1;
	goal.second = boardSize - 1;
	winner = false;
	allChests = false;


	for (int i = 0; i < boardSize; i++) { //initialize dungeon "board"
		board[i] = new int[boardSize];
	}


}

Dungeon::~Dungeon() {
	for (int i = 0; i < boardSize; i++) {
		if (board[i]) delete[] board[i];
	}
	if (board) delete[] board;
}

int Dungeon::CreateChests() {
	int success = 0;
	int chestNum = boardSize * .66;
	int randRow;
	int randCol;

	while (chestNum > 0) {
		bool valid = true;
		random_device rd;
		randRow = rd() % boardSize;
		randCol = rd() % boardSize;

		if (chests.find({ randRow, randCol }) == chests.end()) {
			for (int r = randRow - 1; r < randRow + 2; r++) {
				for (int c = randCol - 1; c < randCol + 2; c++) {
					if (chests.find({ r,c }) != chests.end() ||
						randRow == 0 && randCol == 0 ||
						randRow == boardSize - 1 || randCol == boardSize - 1) { //prevents chest from being placed where another chest is or at the start/end
						valid = false;
						break;
					}
				}
				if (!valid) break;
			}
		}
		if (valid) {
			chests[{randRow, randCol}] = rand() % 100 + 10;
			chestNum--;
		}
	}
	
	success = 1;
	return success;
}

int Dungeon::connectPlayer(Player& player) {
	this->p1 = &player;

	bool ret = p1 ? 0 : 1;
	return ret;
}

int Dungeon::collideCheck() {
	pair<int, int> pos = p1->location;

	if (chests.find({ pos.first, pos.second }) != chests.end()) {
		p1->gems += chests[{pos.first, pos.second}];
		cout << "Collected " << chests[{pos.first, pos.second}] << " gems!" << endl;
		chests.erase({ pos.first, pos.second });
	}

	if (chests.empty()) {
		allChests = true;
		cout << "The exit is open! Head there now!" << endl;
	}

	if (allChests && p1->location == goal) {
		winner = true;
		cout << "You win!" << endl;
	}

	return 0;
}

void Dungeon::printBoard() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (p1 && i == p1->location.first && j == p1->location.second) {
				cout << " P ";
			}
			else if (chests.find({ i, j }) != chests.end()) cout << " X ";
			else if (i == boardSize - 1 && j == boardSize - 1) cout << " E ";
			else {
				cout << " O ";
			}
		}
		cout << endl;
	}
}

void Dungeon::handleInput() {
	while (!winner) {
		if (_kbhit()) {
			char key = _getch();

			switch (key) {
			case 72: if (p1->location.first > 0) p1->location.first--; break;  // Up arrow
			case 80: if (p1->location.first < boardSize - 1) p1->location.first++; break;  // Down arrow
			case 75: if (p1->location.second > 0) p1->location.second--; break;  // Left arrow
			case 77: if (p1->location.second < boardSize - 1) p1->location.second++; break;  // Right arrow
			case 27: return;  // Escape key exits loop
			}
			system("cls");
			printBoard();
			collideCheck();
		}
	}
}


Player::Player() : pName("Divine"), lvlReq(DEFAULT_LVLREQ), xp(0), lvl(0), location({ 0,0 }) {
	
}

Player::Player(string name) : pName(name), lvlReq(DEFAULT_LVLREQ), xp(0), lvl(0), location({ 0,0 }) {

}

Player::~Player() {
	pName = {};


}

void Player::setXp(double experience) {
	xp = experience;
}

bool Player::checkLevel(double xp1, double xp2) {
	int initLvl = xp1 / lvlReq;
	int newLvl = xp2 / lvlReq;

	bool ret = xp1 == xp2 ? false : true;

	if (ret) lvl = newLvl;
	return ret;
}

void Player::gainXp(double experience) {
	bool levelUp = checkLevel(xp, xp + experience);
	xp += experience;

	if (levelUp) {
		cout << "You have leveled up to level " << lvl << "!" << endl;
	}
}

void Player::setLvlReq(double req) {
	lvlReq = req;
}