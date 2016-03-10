#pragma once
#include "BaseApplication.h"

class Object
{
public:
	float inverseMass;

	Ogre::String mName;
	Ogre::SceneNode *mMainNode; // Character position and rotation
	Ogre::Entity *mEntity; // Mesh
	Ogre::SceneManager *mSceneMgr;

	Object();
	Ogre::Vector3 getWorldPosition() {
		return mMainNode->_getDerivedPosition();
	}
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);
};
