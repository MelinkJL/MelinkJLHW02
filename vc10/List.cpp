#include "List.h"

/*
 * This method moves the provided node to the front of the linked list and fixes the pointers to other nodes.
 * @param nodeToMove: The node to move to the front of the linked list.
 */
void List::moveToFront(Node* nodeToMove)
{
	(*(*nodeToMove).prevNode).nextNode = (*nodeToMove).nextNode;
	(*(*nodeToMove).nextNode).prevNode = (*nodeToMove).prevNode;
	(*(*sentinel).nextNode).prevNode = nodeToMove;
	(*nodeToMove).nextNode = (*sentinel).nextNode;    
	(*sentinel).nextNode = (*(*sentinel).nextNode).prevNode;    
	(*nodeToMove).prevNode = sentinel;
}

/*
 * This method inserts a node after a given node with given x and y-coordinates.
 * @param nodeToInsertAfter: The location of the new node, in relation to the node before it.
 * @param xCoord: The x-coordinate of the new node.
 * @param yCoord: The y-coordinate of the new node.
 * @return: The new node inserted into the linked list.
 */
Node* List::insertNode(Node* nodeToInsertAfter, int xCoord, int yCoord)
{
	Node* tempNode = new Node;
	(*tempNode).nextNode = (*nodeToInsertAfter).nextNode;
	(*tempNode).prevNode = nodeToInsertAfter;
	(*nodeToInsertAfter).nextNode = tempNode;
	(*(*tempNode).nextNode).prevNode = tempNode;
	(*tempNode).xCoord = xCoord;
	(*tempNode).yCoord = yCoord;
	(*tempNode).width = (*sentinel).width;
	(*tempNode).height = (*sentinel).height;
	(*tempNode).color = cinder::Color8u(rand() % 256, rand() % 256, rand() % 256);
	return tempNode;
}

/*
 * This method completely reverses the order of the nodes in the list, making the first node last
 * and the last node first.
 */
void List::reverse()
{
	Node* currentNode = sentinel;
	Node* temp;
	do
	{
		temp = (*currentNode).nextNode;
		(*currentNode).nextNode = (*currentNode).prevNode;
		(*currentNode).prevNode = temp;
		currentNode = (*currentNode).prevNode;
	}
	while (currentNode != sentinel);
}

/*
 * This method checks to see if the mouse was clicked on the given rectangle that is a part
 * of the linked list.
 * @param mouseX: The x-coordinate of the mouse when it was clicked.
 * @param mouseY: The y-coordinate of the mouse when it was clicked.
 * @param rect: The address of the rectangle being evaluated if it was clicked on or not.
 * @return: Returns true if the mouse was clicked on the given rectangle or returns false otherwise.
 */
bool List::onRect(int mouseX, int mouseY, Node* rect)
{
	int deltaX = (*rect).xCoord - mouseX;
	int deltaY = (*rect).yCoord - mouseY;
	if (deltaX <= (*rect).width && deltaY <= (*rect).height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * This method checks to see if the mouse was clicked on any of the rectangles in the linked list.
 * @param mouseX: The x-coordinate of the mouse when it was clicked.
 * @param mouseY: The y-coordinate of the mouse when it was clicked.
 * @return: Returns the address of the node that was clicked on if there was one.  If not, 0 is returned.
 */
Node* List::onThisRect(int mouseX, int mouseY)
{
	Node* currentNode = (*sentinel).nextNode;
	while (currentNode != sentinel)
	{
		if (onRect(mouseX, mouseY, currentNode))
		{
			return currentNode;
		}
		currentNode = (*currentNode).nextNode;
	}
	return 0;
}

/*
 * This method resizes the first rectangle in the linked list to make it slightly larger
 * than the other rectangles.
 */
void List::resize()
{
	Node* currentNode = (*sentinel).nextNode;
	double factor = 10;
	(*currentNode).width = factor + (*sentinel).width;
	(*currentNode).height = factor + (*sentinel).height;
	while (currentNode != (*sentinel).prevNode)
	{
		(*(*currentNode).nextNode).width = (*sentinel).width;
		(*(*currentNode).nextNode).height = (*sentinel).height;
		currentNode = (*currentNode).nextNode;
	}
}