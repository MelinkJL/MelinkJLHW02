/**
  * Joshua Melink
  * CSE 274
  * 9/24/2012
  * HW02
  * Draws rectangles to the screen by modifying the surface pixel array that overlap each other.
  * Credit for overall format (method functionality in particular) goes to Brandon Sonoda.
  */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "List.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MelinkJLHW02App : public AppBasic {
  public:
    List* linkedList;
	void setup();
	void mouseDown(MouseEvent event);	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings* settings);
  private:
	Surface* mySurface;
};

static const int appWidth = 800;
static const int appHeight = 600;
static const int textureSize = 1024;

void clearPixelArray(uint8_t* pixelArray);
void showListOnScreen(uint8_t* pixelArray, List* linkedList);
void drawRectangle(uint8_t* pixelArray, int xCoord, int yCoord, int width, int height, Color8u blend);

void MelinkJLHW02App::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth,appHeight);	
	(*settings).setResizable(false);
}

/*
 * Establishes the first image.
 */
void MelinkJLHW02App::setup()
{
	mySurface = new Surface(textureSize, textureSize, false);
	linkedList = new List;
	(*linkedList).sentinel = new Node;
	(*(*linkedList).sentinel).nextNode = (*linkedList).sentinel;
	(*(*linkedList).sentinel).prevNode = (*linkedList).sentinel;
	(*(*linkedList).sentinel).width = appWidth / 5;
	(*(*linkedList).sentinel).height = appHeight / 3;
	Node* addedNode1 = (*linkedList).insertNode((*linkedList).sentinel, appWidth / 6, appHeight / 3);
	Node* addedNode2 = (*linkedList).insertNode(addedNode1, (2 * appWidth) / 6, appHeight / 3);
	Node* addedNode3 = (*linkedList).insertNode(addedNode2, (3 * appWidth) / 6, appHeight / 3);
	Node* addedNode4 = (*linkedList).insertNode(addedNode3, (4 * appWidth) / 6, appHeight / 3);
	(*linkedList).resize();
}

/*
 * Whenever the mouse is clicked on a rectangle it brings that rectangle to the front of the linked list, causing
 * it to overlap the other surrounding rectangles.  *This method does not work.  Everything seems to make sense
 * but for some reason nothing happens on screen when the rectangles are clicked on.*
 * @param event: The event which we are concerned with here is when the user clicks on one of the rectangles.
 */
void MelinkJLHW02App::mouseDown(MouseEvent event)
{
	int mouseX = event.getX();
	int mouseY = event.getY();
	Node* nodeClicked = (*linkedList).onThisRect(mouseX, mouseY);
	if (nodeClicked != 0 && nodeClicked != (*(*linkedList).sentinel).nextNode)
	{
		(*linkedList).moveToFront(nodeClicked);
		(*linkedList).resize();
	}
}

/*
 * Whenever the letter 'r' is pressed on the keyboard, the linked list is reversed, causing the last rectangle
 * (which was previously being overlapped by all other rectangles) to overlap all other rectangles and the first
 * rectangle (which was previously overlapping all other rectangles) to be overlapped by all other rectangles.
 * @param event: The event in which the letter 'r' is pressed on the keyboard.
 */
void MelinkJLHW02App::keyDown(KeyEvent event)
{
	int keyPressed = event.getChar();
	if (keyPressed == 'r')
	{
		(*linkedList).reverse();
		(*linkedList).resize();
	}

}

/*
 * This method is called continuously to update the picture when changes to the linked list are made.
 */
void MelinkJLHW02App::update()
{
  uint8_t* pixelArray = (*mySurface).getData();
  clearPixelArray(pixelArray);
  showListOnScreen(pixelArray, linkedList);
}

void MelinkJLHW02App::draw()
{
	gl::draw(*mySurface);
}

/*
 * Clears the given pixel array by turning the entire array black.
 * @param pixelArray: The pixel array to be modified.
 */
void clearPixelArray(uint8_t* pixelArray)
{
	for (int i = 0; i < textureSize * appWidth * 3; i++)
	{
		pixelArray[i] = 0;
	}
}

/*
 * Displays the linked list on the screen.
 * @param pixelArray: The pixel array to be modified.
 * @param linkedList: The linked list to be displayed on the screen in the form of rectangles.
 */
void showListOnScreen(uint8_t* pixelArray, List* linkedList)
{
	(*linkedList).reverse();  // Reverse list so that last item is being drawn first
	Node* currentNode = (*(*linkedList).sentinel).nextNode;
	while (currentNode != (*linkedList).sentinel)
	{
		drawRectangle(pixelArray, (*currentNode).xCoord, (*currentNode).yCoord, (*currentNode).width, (*currentNode).height, (*currentNode).color);
		currentNode = (*currentNode).nextNode;
	}
	(*linkedList).reverse();  // Reverse the list back to original state
}

/*
 * Draws a rectangle on the screen.
 * @param pixelArray: The pixel array to be modified.
 * @param xCoord: The x-coordinate of the upper-left hand corner of the rectangle.
 * @param xSize: The width of the rectangle.
 * @param yCoord: The y-coordinate of the upper-left hand corner of the rectangle.
 * @param ySize: The height of the rectangle.
 * @param blend: The color to be assigned to the rectangle.
 */
void drawRectangle(uint8_t* pixelArray, int xCoord, int yCoord, int width, int height, Color8u blend)
{
	for (int y = 0; y < textureSize; y++)
	{
		for (int x = 0; x < textureSize; x++)
		{
			if (x > xCoord && x < xCoord + width && y > yCoord && y < yCoord + height)
			{
				int pixel = 3 * (x + y * textureSize);
				pixelArray[pixel] = blend.r;
				pixelArray[pixel + 1] = blend.g;
				pixelArray[pixel + 2] = blend.b;
			}
		}
	}
}

CINDER_APP_BASIC( MelinkJLHW02App, RendererGl )
