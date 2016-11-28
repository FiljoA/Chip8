#include "Chip8.h"

int main(int argc, char **argv)
{
	Chip8 chip8(argv[1], 10);
	while(1) {
		chip8.Cycle();
		sf::sleep(sf::seconds(0.25));
	}
	return 0;
}