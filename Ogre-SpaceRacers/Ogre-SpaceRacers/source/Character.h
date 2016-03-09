#pragma once
#include "BaseApplication.h"

//This is the base class of a Character that can be followed by a camera.
class Character
{
	// Attributes ------------------------------------------------------------------------------
	public:
	Ogre::SceneNode *mMainNode; // Main character node
	Ogre::SceneNode *mSightNode; // "Sight" node - The character is supposed to be looking here
	Ogre::SceneNode *mCameraNode; // Node for the chase camera
	Ogre::Entity *mEntity; // Character entity
	Ogre::SceneManager *mSceneMgr;
	// Methods ---------------------------------------------------------------------------------
	Character();
	Ogre::SceneNode *getSightNode() {
		return mSightNode;
	}
	Ogre::Vector3 getTargetLookPosition() {
		return mSightNode->getPosition();
	}
	Ogre::SceneNode *getCameraNode() {
		return mCameraNode;
	}
	Ogre::Vector3 getWorldPosition() {
		return mMainNode->_getDerivedPosition();
	}
	//void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
};

