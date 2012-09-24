#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

class Node {
  public:
	Node* nextNode;
	Node* prevNode;
	int xCoord;
	int yCoord;
	int width;
	int height;
	cinder::Color8u color;
	void randomizeColor();
};