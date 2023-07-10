#include <iostream>
#include "node.h"
#include "way.h"
#include "serial.h"
#include <string>
#include "framebuffer.h"
#include <windows.h>
#include <inttypes.h>
int main(int argc, char** argv) {
	std::cout << "About to get bounds...\n";
	std::cout << "Filename -> " << argv[1] << "\n";
	Bounds bound = getBounds(argv[1]);
	std::cout << "Bounds: " << bound.minlat << "\n";
	std::cout << "About to run getNodes()...\n";
	auto nodes = getNodes(argv[1]);
	std::cout << "About to run getWays()\n";
	auto ways = getWays(argv[1], nodes);
	std::cout << "About to create framebuffer...\n";
	FrameBuffer buf(240, 320);
	std::cout << "About to draw\n";
	draw(ways, buf, bound.minlat, bound.minlon, bound.maxlat, bound.maxlon, 2);
	std::cout << "Done drawing\n";
	std::vector<uint8_t> nums = buf.Serialize();
	writeStuff(nums);
	return 0;
}