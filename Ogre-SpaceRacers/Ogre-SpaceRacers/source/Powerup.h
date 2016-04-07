#pragma once
#include "Object.h"

class Powerup : public Object
{
public:

	Ogre::Vector3 worldLocation;
	Ogre::Vector3 objectScale;


	Powerup(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale);
	~Powerup();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
};