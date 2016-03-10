#pragma once
#include "BaseApplication.h"

//This is the base class of a Character that can be followed by a camera.
class Character
{
	// Attributes ------------------------------------------------------------------------------
	public:
	Ogre::String mName;
	Ogre::SceneNode *mMainNode; // Character position
	Ogre::SceneNode *mCameraNode; // Camera position
	Ogre::Entity *mEntity; // Character entity
	Ogre::SceneManager *mSceneMgr;
	Ogre::Camera *mCamera;
	// Methods ---------------------------------------------------------------------------------
	Character();
	Ogre::Quaternion getLookPosition() {
		return mCameraNode->_getDerivedOrientation();
	}
	Ogre::SceneNode *getCameraNode() {
		return mCameraNode;
	}
	Ogre::Vector3 getWorldPosition() {
		return mMainNode->_getDerivedPosition();
	}
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);
};

