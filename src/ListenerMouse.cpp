#include "ListenerMouse.h"

ListenerMouse::ListenerMouse()
{
	
}

bool ListenerMouse::mouseMoved(const OIS::MouseEvent &evt) {	

	float mRotateSpeed = 0.1f;

	//this->gestCamera->getCamera()->yaw(Ogre::Degree(-evt.state.X.rel * mRotateSpeed));
	//this->gestCamera->getCamera()->pitch(Ogre::Degree(-evt.state.Y.rel * mRotateSpeed));
		
	return true;
}

bool ListenerMouse::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	
	return true;
}

bool ListenerMouse::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {

	return true;
}
