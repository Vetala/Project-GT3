#pragma once
#include "MovableObject.h"

//This is the base class of a Character that can be followed by a camera.
class Character : public MovableObject
{
public:
	Character();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);

	Ogre::SceneNode *mCameraNode;
	Ogre::SceneNode *mSightNode;
	Ogre::Camera *mCamera;
};

