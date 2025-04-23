#include "dungeon.h"

int main() {
	Dungeon dun = Dungeon();
	Player play = Player();

	dun.connectPlayer(play);
	dun.CreateChests();
	dun.printBoard();
	dun.handleInput();


	return 0;
}