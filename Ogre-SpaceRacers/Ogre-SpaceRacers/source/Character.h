#pragma once
#include "MovableObject.h"

//This is the base class of a Character that can be followed by a camera.
class Character : public MovableObject
{
public:
	Character(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Camera *camera);
	~Character();
	void Update(Ogre::Real elapsedTime, OIS::Keyboard * input);

	Ogre::SceneNode *mCameraNode;
	Ogre::SceneNode *mSightNode;
	Ogre::Camera *mCamera;

	Ogre::Vector3 cameraNodeOffSet; ///The difference between the camera and the character
	Ogre::Vector3 sightOffSet; ///The spot where the camera is aimed towards, this is always in front of the character to create a depth perspective
	Ogre::Real mTightness; ///The tightness at which the camera follows the character. This creates a zoom effect resulting in the character being closer to the camera if the character has a low speed.
};

