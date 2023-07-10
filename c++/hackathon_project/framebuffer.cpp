#include <vector>
#include <inttypes.h>
#include <iostream>
#include "framebuffer.h"

uint8_t Pixel::Serialize() {
	return (uint8_t)color;
}

void FrameBuffer::setPixel(int x, int y, COLOR color) {
	Pixel pixel(color);
	if (x > 0 && y > 0 && x < 320 && y < 240) {
		buffer[(y * width) + x] = pixel;
	}
}

void FrameBuffer::drawLine(int startX, int startY, int endX, int endY, COLOR color) {
	if (startX > endX) {
		std::swap(startX, endX);
		std::swap(startY, endY);
	}
	if (endX - startX != 0) {
		float x = float(startX);
		float y = float(startY);
		float slope = (float(endY) - float(startY)) / (float(endX) - float(startX));
		while (x <= endX) {
			setPixel(int(x), int(y), color);
			x++;
			y += slope;
		}
	}
	else if (endX - startX == 0) {
		for (int y = startY; y < endY; y++) {
			setPixel(startX, y, color);
		}
	}
	else if (startX == endX && endX == startY) {
		setPixel(startX, startY, color);
	}
}

std::vector<uint8_t> FrameBuffer::Serialize() {
	std::vector<uint8_t> bytes;
	for(Pixel pixel: buffer) {
		bytes.push_back(pixel.Serialize());
	}
	return bytes;
}