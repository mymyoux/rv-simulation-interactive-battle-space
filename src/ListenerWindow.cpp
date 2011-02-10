#include "ListenerWindow.h"

ListenerWindow::ListenerWindow(Ogre::Root * root, Ogre::String nameWindow)
{
	this->root = root;
	this->window = this->root->initialise(true, nameWindow);

	Ogre::WindowEventUtilities::addWindowEventListener(this->window, this);
	this->windowResized(this->window);
}

ListenerWindow::~ListenerWindow()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(this->window, this);
	this->windowClosed(this->window);
}

void ListenerWindow::windowResized(Ogre::RenderWindow *rw)
{
	unsigned int width, height, depth;
	int left, top;

	// Adjust mouse clipping area
	/*
	rw->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = this->mouse->getMouseState();
	ms.width = width;
	ms.height = height;
	*/

}

void ListenerWindow::windowClosed(Ogre::RenderWindow *rw)
{
	// Only close for window that created OIS (the main window)
	/*
	if(rw == this->window)
	{
		if(this->inputManager)
		{
			// Unattach OIS before window shutdown (very important under Linux)
			this->inputManager->destroyInputObject(this->mouse);
			this->inputManager->destroyInputObject(this->keyboard);

			OIS::InputManager::destroyInputSystem(this->inputManager);
			this->inputManager = 0;
		}
	}
	*/
}
