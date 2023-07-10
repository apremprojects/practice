#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <vector>
#include <inttypes.h>
enum class COLOR {
	BLACK = 0x00,
	WHITE = 0xFF,
	RED = 0xE0,
	BLUE = 0x1D,
	GREEN = 0x04,
	YELLOW = 0xEF,
	ORANGE = 0xE4,
	PURPLE = 0x9A,
	PINK = 0xFD,
	CYAN = 0x1F,
	BROWN = 0x41,
	GRAY = 0x4A,
	GOLD = 0xC5,
	SILVER = 0x06B,
	MAGENTA = 0xF9,
	LIME = 0x25,
	TEAL = 0x17,
	NAVY = 0x08,
	OLIVE = 0x84,
	MAROON = 0x80,
	FUCHSIA = 0xF2,
	INDIGO = 0x10,
	AQUA = 0x9F
};
class Pixel {
public:
	Pixel(COLOR _color) : color(_color) {}
	uint8_t Serialize();
private:
	COLOR color;
};
class FrameBuffer {
public:
	FrameBuffer(int _height, int _width) {
		height = _height;
		width = _width;
		buffer.reserve(_height * _width);
		for (int i = 0; i < _height * _width; i++) {
			Pixel pixel(COLOR::WHITE);
			buffer.push_back(pixel);
		}
	};
	void setPixel(int x, int y, COLOR color);
	void drawLine(int startX, int startY, int endX, int endY, COLOR color);
	std::vector<uint8_t> Serialize();
private:
	std::vector<Pixel> buffer;
	int height = 0;
	int width = 0;
};
#endif