#include <vector>
#include <iostream>
#include <string>
#include "node.h"
#include "framebuffer.h"
#include "tinyxml2.h"
using namespace tinyxml2;
Node::Node() {
}
Node::Node(float _lon, float _lat) : lat(_lat), lon(_lon)  {
}

std::vector<Node*> getNodes(std::string filename) {
	std::cout << "Inside getNodes(), about to create XMLDoc...\n";
	XMLDocument doc;
	std::vector<Node*> nodes;
	std::cout << "Loading file...\n";
	auto err = doc.LoadFile(filename.c_str());
	if (err != XML_SUCCESS) {
		std::cout << "Critical error\n";
		return nodes;
	}
	std::cout << "Deleting child...\n";
	doc.DeleteChild(doc.FirstChildElement());
	std::cout << "Setting root...\n";
	doc.LoadFile(filename.c_str());
	auto root = doc.FirstChildElement();
	std::cout << "Beginning loop, root name is " << root->Name() << " ...\n";
	while (!root->NoChildren()) {
		auto temp = root->FirstChildElement();
		//std::cout << "Potential node:" << temp->Name() << "\n";
		/*TODO
		CHECK IF <node></node>
		If so, create Node, and add it to the vector.
		*/
		if (std::string(temp->Name()) == std::string("node")) {
			//It is <node></node>
			//std::cout << "It is <node></node>\n";
			Node *node = new Node;
			node->lat = temp->ToElement()->FloatAttribute("lat");
			node->lon = temp->ToElement()->FloatAttribute("lon");
			node->id = temp->ToElement()->IntAttribute("id");
			//std::cout << "Created node with lat: " << node.lat << " and " << node.lon << "\n";
			nodes.push_back(node);
		}
		root->DeleteChild(temp);
	}
	return nodes;
}

Bounds getBounds(std::string filename) {
	std::cout << "Inside getBounds(), about to create XMLDoc...\n";
	XMLDocument doc;
	Bounds bound;
	std::cout << "Loading file...\n";
	auto err = doc.LoadFile(filename.c_str());
	if (err != XML_SUCCESS) {
		std::cout << "Critical error\n";
		return bound;
	}
	std::cout << "Deleting child...\n";
	doc.DeleteChild(doc.FirstChildElement());
	std::cout << "Setting root...\n";
	doc.LoadFile(filename.c_str());
	auto root = doc.FirstChildElement()->FirstChildElement();
	bound.minlat = root->FloatAttribute("minlat");
	bound.minlon = root->FloatAttribute("minlon");
	bound.maxlat = root->FloatAttribute("maxlat");
	bound.maxlon = root->FloatAttribute("maxlon");
	std::cout << "BOund" << bound.maxlat << "\n";
	return bound;
};

void draw(const std::vector<Node*> &nodes, FrameBuffer &buf, float minlat, float minlon, float maxlat, float maxlon) {
	for (int i = 0; i < nodes.size() - 1; i++) {
		float startX = ((nodes[i]->lon - minlon) / (maxlon - minlon)) * 320;
		float startY = 240 - ((nodes[i]->lat - minlat) / (maxlat - minlat)) * 240;
		float endX = ((nodes[i + 1]->lon - minlon) / (maxlon - minlon)) * 320;
		float endY = 240 - ((nodes[i+1]->lat - minlat) / (maxlat - minlat)) * 240;
		/*std::cout << "Drawing a line from (" << nodes[i].lon << ", " << nodes[i].lat << ") to (" << nodes[i + 1].lon << ", " << nodes[i + 1].lat << ")\n";
		std::cout << "This translates to drawing a line from (" << startX << "," << startY << ") to (" << endX << "," << endY << ")\n";
		std::cout << "Calling drawline\n";*/
		COLOR color = COLOR::BLACK;
		buf.drawLine(startX, startY, endX, endY, color);
		//std::cout << "Done calling drawline\n";
	}
}