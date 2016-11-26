#pragma once
#include <stdint.h>


#define CHIP8_WIDTH    64
#define CHIP8_HEIGHT   32
#define SCHIP8_WIDTH   128
#define SCHIP8_HEIGHT  64
#define MAX_WIDTH SCHIP8_WIDTH
#define MAX_HEIGHT SCHIP8_HEIGHT

#define FONT_LOCATION  0xC8
#define ROM_ENTRY      0x200

class Chip8 {
public:
	Chip8(const char* ROM_DIR);
	
	void NextCycle();
private:
	void LoadROM(const char* ROM_DIR);
	void LoadFont();
	
	union {
		uint16_t memory[0x1000];
		struct {
			uint8_t V[0xF];
			uint8_t HP[0x8];
			uint16_t I;
			uint8_t delayTimer;
			uint8_t soundTimer;
			uint16_t stack[0xF];
			uint8_t SP;
			uint16_t PC;
		};
	};
};