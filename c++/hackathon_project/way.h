#ifndef WAY_H
#define WAY_H
#include <vector>
#include <string>
#include "node.h"
#include "framebuffer.h"
class Way {
public:
	Way();
	std::vector<Node*> nodes;
	std::string type;
};
std::vector<Way*> getWays(std::string filename, const std::vector<Node*> &nodes);
void draw(const std::vector<Way*>& ways, FrameBuffer& buf, float minlat, float minlon, float maxlat, float maxlon, float zoomLevel);
#endif