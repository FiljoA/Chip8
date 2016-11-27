#pragma once
#include <SFML/Graphics.hpp>
#include <stdint.h>


#define CHIP8_WIDTH    64
#define CHIP8_HEIGHT   32
#define SCHIP8_WIDTH   128
#define SCHIP8_HEIGHT  64
#define MAX_WIDTH SCHIP8_WIDTH
#define MAX_HEIGHT SCHIP8_HEIGHT

#define CHIP8_SPRITESIZE  8
#define SCHIP8_SPRITESIZE 16

#define FONT_LOCATION  0xC8
#define ROM_ENTRY      0x200

class Chip8 {
public:
	Chip8(const char* ROM_DIR, uint8_t upscaleRatio);
	
	void Cycle();
private:
	void LoadROM(const char* ROM_DIR);
	void LoadFont();
	
	void ClearScreen();
	void DrawPixel(uint8_t x, uint8_t y);
	void ErasePixel(uint8_t x, uint8_t y);
	
	//Memory
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
			
			uint16_t opcode;
		};
	};
	
	//Display
	bool display[MAX_WIDTH][MAX_HEIGHT];
	struct Mode {
		uint8_t width;
		uint8_t height;
		uint8_t spriteSize;
	} mode;
	
	sf::RenderWindow* app;
	sf::RectangleShape pixel;
	uint8_t upscale;
	
	//Operations
	void SYSSCR(int offset, char axis); //00CN, 00FB - 00FC
	void SYSCLS(); //00E0
	void RET(); //00EE
	void SYSMODE(char x); //00FE - 00FF
	void SYSEXIT(); //00FD
	void NOP(); //0000 -> Unknown
	void UNKNOWN(); //Unknown
	void JMP(unsigned short address); //1NNN
	void CALL(unsigned short address); //2NNN
	void JE(unsigned short registerX, unsigned char constant); //3XNN
	void JNE(unsigned short registerX, unsigned char constant); //4XNN
	void JE(unsigned short registerX, unsigned short registerY); //5XY0
	void MOV(unsigned char& registerX, const unsigned char& constant); //6XNN
	void ADD(unsigned char& registerX, const unsigned char& constant); //7XNN
	void MOV(unsigned char& registerX, unsigned char& registerY); //8XY0, FX07, FX15-FX18
	void OR(unsigned char& registerX, unsigned char& registerY); //8XY1
	void AND(unsigned char& registerX, unsigned char& registerY); //8XY2
	void XOR(unsigned char& registerX, unsigned char& registerY); //8XY3
	void ADD(unsigned char& registerX, unsigned char& registerY); //8XY4
	void SUB(unsigned char& registerX, unsigned char& registerY); //8XY5
	void SHR(unsigned char& registerX); //8XY6
	void SUBR(unsigned char& registerX, unsigned char& registerY); //8XY7
	void SHL(unsigned short registerX); //8XYE
	void JNE(unsigned char& registerX, unsigned char& registerY); //9XY0
	void MOV(const unsigned short address); //ANNN
	void JMPR(const unsigned short address); //BNNN
	void RDRAND(unsigned char& registerX, const unsigned char& constant); //CXNN
	void SYSDRW(unsigned char X, unsigned char Y, unsigned char N); //DXYN
	void JINE(unsigned char& registerX); //EX9E
	void JINNE(unsigned char& registerX); //EXA1
	void IN(unsigned char& registerX); //FX0A
	void ADD(unsigned char& registerX); //FX1E
	void SYSFONT(unsigned char& registerX); //FX29
	void SYSSFONT(unsigned char& registerX); //FX30
	void BLD(unsigned char& registerX); //FX33
	void SAVE(const unsigned char& X); //FX55
	void RSTOR(const unsigned char& X); //FX65
	void SSAVE(const unsigned char& X); //FX75
	void SRSTOR(const unsigned char& X); //FX85
};