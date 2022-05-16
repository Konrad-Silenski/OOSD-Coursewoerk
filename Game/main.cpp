#include "Game.h" 
#include<time.h>
#include "Menu.h"

int main() {

	srand(static_cast<unsigned int>(time (0)));

	Menu menu;

	menu.run();


	return 0;
}