#include "Chip8.h"
#include <fstream>
#include <cstdlib>
#ifdef SPRITE
  #include <iostream>
#endif
#include <iostream>


Chip8::Chip8(const char* ROM_DIR, uint8_t upscaleRatio) {
	upscale = upscaleRatio;
	app = new sf::RenderWindow(
	         sf::VideoMode(CHIP8_WIDTH * upscale, CHIP8_HEIGHT * upscale),
	         "Chip8");
	pixel.setSize({static_cast<float>(upscale), static_cast<float>(upscale)});
	
	LoadROM(ROM_DIR);
	LoadFont();
	
	PC = ROM_ENTRY;
	SYSMODE(1);
	SYSCLS();
}

Chip8::~Chip8() {
	app->close();
	delete(app);
}

void Chip8::LoadROM(const char* ROM_DIR) {
	std::ifstream ROM;
	ROM.open(ROM_DIR, std::ios::binary);
	for(uint16_t i = 0x200; ROM.get((char&)memory[i]); i++);
}

void Chip8::LoadFont() {
	uint8_t fontData[] = {
		//0 - 0x01
		0x00, 0xF0, 0x90, 0x90, 0x90, 0xF0,
		//1 - 0x07
		0x01, 0x20, 0x60, 0x20, 0x20, 0x70,
		//2 - 0x0D
		0x02, 0xF0, 0x10, 0xF0, 0x80, 0xF0,
		//3 - 0x13
		0x03, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
		//4 - 0x19
		0x04, 0x90, 0x90, 0xF0, 0x10, 0x10,
		//5 - 0x1F
		0x05, 0xF0, 0x80, 0xF0, 0x10, 0xF0,
		//6 - 0x25
		0x06, 0xF0, 0x80, 0xF0, 0x90, 0xF0,
		//7 - 0x2B
		0x07, 0xF0, 0x10, 0x20, 0x40, 0x40,
		//8 - 0x31
		0x08, 0xF0, 0x90, 0xF0, 0x90, 0xF0,
		//9 - 0x37
		0x09, 0xF0, 0x90, 0xF0, 0x10, 0xF0,
		//A - 0x3D
		0x0A, 0xF0, 0x90, 0xF0, 0x90, 0x90,
		//B - 0x43
		0x0B, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
		//C - 0x49
		0x0C, 0xF0, 0x80, 0x80, 0x80, 0xF0,
		//D - 0x4F
		0x0D, 0xE0, 0x90, 0x90, 0x90, 0xE0,
		//E - 0x55
		0x0E, 0xF0, 0x80, 0xF0, 0x80, 0xF0,
		//F - 0x5B
		0x0F, 0xF0, 0x80, 0xF0, 0x80, 0x80,
		//0 - 0x61
		0x00, 0x3C, 0x46, 0xCF, 0xCB, 0xDB, 0xDB, 0xD3, 0xF3, 0x62, 0x3C,
		//1 - 0x6C
		0x01, 0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF,
		//2 - 0x77
		0x02, 0x7C, 0xC6, 0xE3, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xFF,
		//3 - 0x82
		0x03, 0x7E, 0xC3, 0xE3, 0x03, 0x03, 0x1E, 0x03, 0xC3, 0xC3, 0x7E,
		//4 - 0x8D
		0x04, 0x1E, 0x36, 0x66, 0xC6, 0x86, 0xFF, 0x06, 0x06, 0x06, 0x06,
		//5 - 0x98
		0x05, 0xFF, 0xC0, 0xC0, 0xC0, 0xFC, 0x06, 0x03, 0xE3, 0xC7, 0x7E,
		//6 - 0xA3
		0x06, 0x3E, 0x63, 0xC7, 0xC0, 0xC0, 0xFC, 0xC6, 0xC3, 0x63, 0x3E,
		//7 - 0xAE
		0x07, 0xFF, 0xC3, 0xE3, 0x03, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x18,
		//8 - 0xB9
		0x08, 0x7E, 0xC3, 0xC3, 0xC3, 0xC3, 0x7E, 0xC3, 0xC3, 0xC3, 0x7E,
		//9 - 0xC4
		0x09, 0x3C, 0x66, 0xC3, 0xC3, 0x63, 0x3F, 0x03, 0x73, 0x66, 0x3C,
		//A - 0xCF
		0x0A, 0x18, 0x3C, 0x66, 0xC3, 0xC3, 0xC3, 0xFF, 0xC3, 0xC3, 0xC3,
		//B - 0xDA
		0x0B, 0xFE, 0xC3, 0xC3, 0xC3, 0xC3, 0xFC, 0xC3, 0xC3, 0xC3, 0xFE,
		//C - 0xE5
		0x0C, 0x3E, 0x63, 0xC7, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x63, 0x3E,
		//D - 0xF0
		0x0D, 0xFC, 0xC6, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC6, 0xFC,
		//E - 0xFB
		0x0E, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xFE, 0xC0, 0xC0, 0xC0, 0xFF,
		//F - 0x106
		0x0F, 0xFF, 0xFF, 0xC0, 0xC0, 0xF8, 0xF8, 0xC0, 0xC0, 0xC0, 0xC0
	};
	
	for(uint16_t i = 0; i < sizeof(fontData); i++) {
		memory[FONT_LOCATION + i] = fontData[i];
	}
}

void Chip8::Cycle() {
	opcode = memory[PC] << 8 | memory[PC + 1];
	
	#ifdef DEBUG_INS
		std::cout << std::hex << PC << ":" << opcode << std::endl;
	#endif
	
	PC += 2;
	
	//Address
	const unsigned short NNN = opcode & 0x0FFF;
	//8-bit constant
	const unsigned char  NN = opcode & 0x00FF;
	//4-bit constant or right most bit
	const unsigned char   N = opcode & 0x000F;
	//left most bit
	const unsigned char  hi = (opcode & 0xF000) >> 12;
	//Register X
	const unsigned char   X = (opcode & 0x0F00) >> 8;
	//Register Y
	const unsigned char   Y = (opcode & 0x00F0) >> 4;
	
	switch(hi) {
		case 0x0:
			switch(NN) {
				case 0xE0: SYSCLS(); break;
				case 0xEE: RET(); break;
				case 0xFB: SYSSCR(4, 'x'); break;
				case 0xFC: SYSSCR(-4, 'x'); break;
				case 0xFD: SYSEXIT(); break;
				case 0xFE: SYSMODE(1); break;
				case 0xFF: SYSMODE(2); break;
				case 0x00: NOP(); break;
				default:
					if((NN & 0xC0) == 0xC0) {
						SYSSCR(N, 'y');
					} else
						UNKNOWN();
			}
			break;
		case 0x1: JMP(NNN); break;
		case 0x2: CALL(NNN); break;
		case 0x3: JE(V[X], NN); break;
		case 0x4: JNE(V[X], NN); break;
		case 0x5: JE(V[X], V[Y]); break;
		case 0x6: MOV(V[X], NN); break;
		case 0x7: ADD(V[X], NN); break;
		case 0x8:
			switch(N) {
				case 0x0: MOV(V[X], V[Y]); break;
				case 0x1: OR(V[X], V[Y]); break;
				case 0x2: AND(V[X], V[Y]); break;
				case 0x3: XOR(V[X], V[Y]); break;
				case 0x4: ADD(V[X], V[Y]); break;
				case 0x5: SUB(V[X], V[Y]); break;
				case 0x6: SHR(V[X]); break;
				case 0x7: SUBR(V[X], V[Y]); break;
				case 0xE: SHL(V[X]); break;
				default:
					UNKNOWN();
					break;
			};
			break;
		case 0x9: JNE(V[X], V[Y]); break;
		case 0xA: MOV(NNN); break;
		case 0xB: JMPR(NNN); break;
		case 0xC: RDRAND(V[X], NN); break;
		case 0xD: SYSDRW(X, Y, N); break;
		case 0xE:
			switch(NN) {
				case 0x009E: JINE(V[X]); break;
				case 0x00A1: JINNE(V[X]); break;
				default:
					UNKNOWN();
					break;
			};
			break;
		case 0xF:
			switch(NN) {
				case 0x07: MOV(V[X], delayTimer); break;
				case 0x0A: IN(V[X]); break;
				case 0x15: MOV(delayTimer, V[X]); break;
				case 0x18: MOV(soundTimer, V[X]); break;
				case 0x1E: ADD(V[X]); break;
				case 0x29: SYSFONT(V[X]); break;
				case 0x30: SYSSFONT(V[X]); break;
				case 0x33: BLD(V[X]); break;
				case 0x55: SAVE(X); break;
				case 0x65: RSTOR(X); break;
				case 0x75: SSAVE(X); break;
				case 0x85: SRSTOR(X); break;
				default:
					UNKNOWN();
					break;
			};
			break;
		default:
			UNKNOWN();
			break;
	};
}

void Chip8::UpdateTimers(uint8_t timePassed) {
	delayTimer <= 0 ? delayTimer = 0 : delayTimer -= timePassed;
	soundTimer <= 0 ? soundTimer = 0 : soundTimer -= timePassed;
}

void Chip8::UNKNOWN() {
	std::cout << "Unknown OP: " << opcode << std::endl;
}

void Chip8::SYSMODE(char x) {
	switch(x) {
		case 1:
			mode.width = CHIP8_WIDTH;
			mode.height = CHIP8_HEIGHT;
			mode.spriteSize = CHIP8_SPRITESIZE;
			mode.pixelSize = upscale;
			break;
		case 2:
			mode.width = SCHIP8_WIDTH;
			mode.height = SCHIP8_HEIGHT;
			mode.spriteSize = SCHIP8_SPRITESIZE;
			mode.pixelSize = upscale / 2;
			break;
	}
	
	pixel.setSize({mode.pixelSize, mode.pixelSize});
	
	SYSCLS();
}

void Chip8::SYSSCR(int x, char axis) {
	if(axis == 'y') {
		//Shift x down
		for(int j = mode.height - 1; j >= 0; j--) {
			for(int i = 0; i < mode.width; i++) {
				if((j-x) >= 0) {
					display[i][j] = display[i][j-x];
					if(display[i][j]) {
						DrawPixel(i, j);
					}
					else {
						ErasePixel(i, j);
					}
				} else {
					display[i][j] = false;
					ErasePixel(i, j);
				}
			}
		}
	} else if(axis == 'x') {
		//Shift x left
		if(x < 0) {
			for(int i = 0; i < mode.width; i++) {
				for(int j = 0; j < mode.height; j++) {
					if((i-x) < mode.width) {
						display[i][j] = display[i-x][j];
						if(display[i][j]) {
							DrawPixel(i, j);
						}
						else {
							ErasePixel(i, j);
						}
					} else {
						display[i][j] = false;
						ErasePixel(i, j);
					}
				}
			}
		} else if(x > 0) {
			//Shift x right
			for(int i = mode.width - 1; i >= 0; i--) {
				for(int j = 0; j < mode.height; j++) {
					if((i-x) >= 0) {
						display[i][j] = display[i-x][j];
						if(display[i][j]) {
							DrawPixel(i, j);
						}
						else {
							ErasePixel(i, j);
						}
					} else {
						display[i][j] = false;
						ErasePixel(i, j);
					}
				}
			}
		}
	}
}

void Chip8::SYSCLS() {
	for(int i = 0; i < mode.width; i++) {
		for(int j = 0; j < mode.height; j++) {
			display[i][j] = false;
		}
	}
	
	ClearScreen();
}

void Chip8::RET() {
	PC = stack[--SP];
}

void Chip8::SYSEXIT() {
	PC = PC - 2;
}

void Chip8::NOP() {}

void Chip8::JMP(unsigned short address) {
	PC = address;
}

void Chip8::CALL(unsigned short address) {
	stack[SP++] = PC;
	PC = address;
}

void Chip8::JE(unsigned short registerX, unsigned char K) {
	if(registerX == K)
		PC += 2;
}

void Chip8::JNE(unsigned short registerX, unsigned char K) {
	if(registerX != K)
		PC += 2;
}

void Chip8::JE(unsigned short registerX, unsigned short registerY) {
	if(registerX == registerY)
		PC += 2;
}

void Chip8::MOV(unsigned char& registerX, const unsigned char& K) {
	registerX = K;
}

void Chip8::ADD(unsigned char& registerX, const unsigned char& K) {
	registerX += K;
}

void Chip8::MOV(unsigned char& registerX, unsigned char& registerY) {
	registerX = registerY;
}

void Chip8::OR(unsigned char& registerX, unsigned char& registerY) {
	registerX = registerX | registerY;
}

void Chip8::AND(unsigned char& registerX, unsigned char& registerY) {
	registerX = registerX & registerY;
}

void Chip8::XOR(unsigned char& registerX, unsigned char& registerY) {
	registerX = registerX ^ registerY;
}

void Chip8::ADD(unsigned char& registerX, unsigned char& registerY) {
	if((registerX + registerY) > 255) {
		V[0xF] = 1;
		char x;
		x = registerX + registerY;
		registerX = x;
	} else {
		V[0xF] = 0;
		registerX += registerY;
	}
}

void Chip8::SUB(unsigned char& registerX, unsigned char& registerY) {
	if(registerX > registerY) {
		V[0xF] = 1;
		registerX -= registerY;
	} else {
		V[0xF] = 0;
		registerX -= registerY;
	}
}

void Chip8::SHR(unsigned char& registerX) {
	V[0xF] = (registerX & 1);
	registerX >>= 1;
}

void Chip8::SUBR(unsigned char& registerX, unsigned char& registerY) {
	if(registerX < registerY) {
		V[0xF] = 1;
		registerX = registerY - registerX;
	} else {
		V[0xF] = 0;
		registerX = registerY - registerX;
	}
}

void Chip8::SHL(unsigned short registerX) {
	V[0xF] = (registerX & 128);
	registerX <<= 1;
}

void Chip8::JNE(unsigned char& registerX, unsigned char& registerY) {
	if(registerX != registerY)
		PC += 2;
}

void Chip8::MOV(const unsigned short address) {
	I = address;
}

void Chip8::JMPR(const unsigned short address) {
	PC = address + V[0];
}

void Chip8::RDRAND(unsigned char& registerX, const unsigned char& K) {
	registerX = (rand() % 255) & K;
}

void Chip8::SYSDRW(unsigned char X, unsigned char Y, unsigned char N) {
	unsigned short x, y, sprite, spriteHeight;
	
	//In SChip8 mode 16x16 sprites are drawn by setting
	//By setting the N in DXYN to 0
	//Sprites bigger than 8 pixels wide have pixel information
	//stored on 2 memory addresses (memory[i] and memory[i + 1]
	//Therefore on the loop below, i must be incremented by 2
	spriteHeight = (N != 0 ? N : 16);
	
	//Register VF is set to 0 before drawing
	//if collision is detected it's set to 1
	V[0xF] = 0;
	
	y = V[Y];
	
	//Define SPRITE to debug sprite drawing
	for(unsigned int i = 0; i < spriteHeight; i++, y++) {
		sprite = N == 0 ?
				(memory[I + i * 2] << 8) | memory[I + i * 2 + 1]
				: memory[I + i];
		
		y = (y % mode.height);
		x = V[X];

		for(int j = 0; j < (N != 0 ? 8 : 16); j++, x++){
			x = (x % mode.width);
			if(N == 0 ? (sprite & 0x8000) == 0x8000 : (sprite & 0x0080) == 0x0080) {
				if(display[x][y] == false) {
					DrawPixel(x, y);
					display[x][y] = true;
					
					#ifdef SPRITE
						std::cout << "*";
					#endif
				} else if(display[x][y] == true) {
					display[x][y] = false;
					ErasePixel(x, y);
					
					V[0xF] = 1;
					
					#ifdef SPRITE
						std::cout << "x";
					#endif
				}
			} else {
				#ifdef SPRITE
					std::cout << " ";
				#endif
				}
			sprite <<= 1;
		}
		#ifdef SPRITE
			std::cout << "\n";
		#endif
	}

	FlipScreen();
}

void Chip8::JINE(unsigned char& registerX) {
	//if(input.is_key_down(registerX))
		PC += 2;
}

void Chip8::JINNE(unsigned char& registerX) {
	//if(!input.is_key_down(registerX))
		PC += 2;
}

void Chip8::IN(unsigned char& registerX) {
	unsigned char key;
	//key = input.GetKeyPress();
	
	if(key != 16)
		registerX = key;
	else
		PC -= 2;
}

void Chip8::ADD(unsigned char& registerX) {
	I += registerX;
}

void Chip8::SYSFONT(unsigned char& registerX) {
	uint16_t fontLocation;
	fontLocation = FONT_LOCATION + 1;
	for(int i = 0x0; i <= registerX; i++) {
		if(i == registerX)
			I = fontLocation;
		else
			fontLocation += 0x06;
	}
}

void Chip8::SYSSFONT(unsigned char& registerX) {
	uint16_t sfontLocation;
	sfontLocation = FONT_LOCATION + 0x61;
	for(int i = 0x0; i <= registerX; i++) {
		if(i == registerX)
			I = sfontLocation;
		else
			sfontLocation += 0xB;
	}
}

void Chip8::BLD(unsigned char& registerX) {
	memory[I] = (registerX / 100) % 10;
	memory[I + 1] = (registerX / 10) % 10;
	memory[I + 2] = (registerX / 1) % 10;
}

void Chip8::SAVE(const unsigned char& X) {
	for(unsigned int i = 0; i <= X; i++) {
		memory[I+i] = V[i];
	}
}

void Chip8::RSTOR(const unsigned char& X) {
	for(unsigned int i = 0; i <= X; i++) {
		V[i] = memory[I + i];
	}
}

void Chip8::SSAVE(const unsigned char& X) {
	for(int i = 0; i <= X; i++) {
		HP[i] = V[i];
	}
}

void Chip8::SRSTOR(const unsigned char& X) {
	for(int i = 0; i <= X; i++) {
		V[i] = HP[i];
	}
}