#ifndef NODE_H
#define NODE_H
#include <vector>

#include "framebuffer.h"
struct Bounds {
	float minlat = 0;
	float minlon = 0;
	float maxlat = 0;
	float maxlon = 0;
};
class Node {
public:
	Node();
	Node::Node(float _lon, float _lat);
	float lat = 0;
	float lon = 0;
	int id = 0;
};
std::vector<Node*> getNodes(std::string filename);
Bounds getBounds(std::string filename);
void draw(const std::vector<Node*> &nodes, FrameBuffer& buf, float minlat, float minlon, float maxlat, float maxlon);
#endif