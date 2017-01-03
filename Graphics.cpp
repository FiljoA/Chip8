#include "Chip8.h"

void Chip8::FlipScreen() {
	app->display();
}

void Chip8::ClearScreen() {
	app->clear();
	FlipScreen();
}

void Chip8::DrawPixel(uint8_t x, uint8_t y) {
	pixel.setFillColor({255, 255, 255, 255});
	pixel.setPosition(x * mode.pixelSize, y * mode.pixelSize);
	app->draw(pixel);
}
void Chip8::ErasePixel(uint8_t x, uint8_t y) {
	pixel.setFillColor({0, 0, 0, 255});
	pixel.setPosition(x * mode.pixelSize, y * mode.pixelSize);
	app->draw(pixel);
}