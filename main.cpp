#include "Chip8.h"


const int FRAME_RATE = 60;
const int INS_PER_CYCLE = (FRAME_RATE / 60) * 60;
const int SECONDS_PER_FRAME = FRAME_RATE / 60;

int main(int argc, char **argv)
{
	Chip8 chip8(argv[1], 10);
	sf::RenderWindow* app = chip8.GetApp();
	
	bool running = true;
	while(running) {
		for(int i = 0; i < 60; i++) {
			chip8.Cycle();
		}
		chip8.UpdateTimers(SECONDS_PER_FRAME);
		sf::sleep(sf::seconds(1));
		
		sf::Event event;
		while(app->pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed:
					running = false;
					break;
				default:
					break;
			}
		}
	}
	return 0;
}