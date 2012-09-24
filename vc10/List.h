#include "Node.h"

class List {
  public:    
    Node* sentinel;
	void moveToFront(Node* nodeToMove);
	Node* insertNode(Node* nodeToInsertAfter, int xCoord, int yCoord);
	void reverse();
	Node* onThisRect(int mouseX, int mouseY);
	void resize();
  private:
	bool onRect(int mouseX, int mouseY, Node* rect);
};