#include "Chip8.h"


const int FRAME_RATE = 60;
const int INS_PER_CYCLE = (FRAME_RATE / 60) * 60;
const int SECONDS_PER_FRAME = FRAME_RATE / 60;

int main(int argc, char **argv)
{
	Chip8 chip8(argv[1], 10);
	while(1) {
		for(int i = 0; i < 60; i++) {
			chip8.Cycle();
		}
		chip8.UpdateTimers(SECONDS_PER_FRAME);
		sf::sleep(sf::seconds(1));
	}
	return 0;
}