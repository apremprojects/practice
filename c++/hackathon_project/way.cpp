#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <set>
#include "tinyxml2.h"
#include "node.h"
#include "framebuffer.h"
#include "way.h"
using namespace tinyxml2;
std::map<std::string, COLOR> typeToColor{
	/*Add your own colors to types*/
};
Way::Way() {};
std::vector<Way*> getWays(std::string filename, const std::vector<Node*> &nodes) {
	std::vector <Way*> ways;
	std::map<int, Node*> idToNode;
	std::map<std::string, int> dataDebug;
	for (Node *node : nodes) {
		idToNode[node->id] = node;
	}
	std::cout << "Inside getWays(), about to create XMLDoc...\n";
	XMLDocument doc;
	std::cout << "Loading file...\n";
	auto err = doc.LoadFile(filename.c_str());
	if (err != XML_SUCCESS) {
		std::cout << "Critical error\n";
		return ways;
	}
	std::cout << "Deleting child...\n";
	doc.DeleteChild(doc.FirstChildElement());
	std::cout << "Setting root...\n";
	doc.LoadFile(filename.c_str());
	auto root = doc.FirstChildElement();
	std::cout << "Beginning loop, root name is " << root->Name() << " ...\n";
	while (!root->NoChildren()) {
		auto temp = root->FirstChildElement();//Temp is a potential <way></way> tag
		if (std::string(temp->Name()) == std::string("way")) { //if <way></way>
			Way* way = new Way;
			while (!temp->NoChildren()) { //iterating through <nd></nd>
				auto temp2 = temp->FirstChildElement();
				if (std::string(temp2->Name()) == std::string("nd")) {
					way->nodes.push_back(idToNode[temp2->ToElement()->IntAttribute("ref")]);
				}
				else if (std::string(temp2->Name()) == std::string("tag")) {
                    if (dataDebug.count(temp2->Attribute("k")) == 0) { 
                        dataDebug[temp2->Attribute("k")] = 0;
                    }
                    else {
                        dataDebug[temp2->Attribute("k")] += 1;
                    }
					way->type = std::string(temp2->Attribute("k"));
				}
				ways.push_back(way);
				temp->DeleteChild(temp2);
			}
		}
		root->DeleteChild(temp);
	}
	for (auto i : dataDebug) {
        if (typeToColor.count(i.first) != 0) { 
            std::cout << "name: " << i.first << ", mentions: " << i.second << "\n";
        }
	}
	return ways;
};

void draw(const std::vector<Way*>& ways, FrameBuffer& buf, float minlat, float minlon, float maxlat, float maxlon, float zoomLevel) {
	for (Way* way : ways) {
		for (int i = 0; i < way->nodes.size() - 1; i++) {
			float startX = ((way->nodes[i]->lon - minlon) / (maxlon - minlon)) * 320;
			float startY = 240 - ((way->nodes[i]->lat - minlat) / (maxlat - minlat)) * 240;
			float endX = ((way->nodes[i + 1]->lon - minlon) / (maxlon - minlon)) * 320;
			float endY = 240 - ((way->nodes[i + 1]->lat - minlat) / (maxlat - minlat)) * 240;
			COLOR color = COLOR::SILVER;
			if (way->type.empty() != true) {
				//std::cout << way->type << "\n";
			}
			color = typeToColor[way->type];
			if (typeToColor.count(std::string(way->type)) != 0) {
				//std::cout << "Test\n";
				color = typeToColor.at(std::string(way->type));
			}
            else {
                std::cout << "Unknown way: " << way->type << "\n";
            }
			buf.drawLine(startX, startY, endX, endY, color);
		}
	}
}