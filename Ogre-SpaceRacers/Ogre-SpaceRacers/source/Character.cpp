#include "Character.h"

Character::Character(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Camera *camera) : MovableObject(name, sceneMgr, meshName)
{
	cameraNodeOffSet = Ogre::Vector3(0, 0, 0);
	sightOffSet = Ogre::Vector3(0, 0, 1);
	mTightness = 0;

	// Create our camera if it wasn't passed as a parameter
	if (camera == 0) {
		mCamera = mSceneMgr->createCamera(mName);
	}
	else {
		mCamera = camera;
		mCamera->setPosition(0.0, 0.0, 0.0);
	}
}

void Character::Update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{
	MovableObject::Update(elapsedTime, input);
}

Character::~Character()
{
	
}
