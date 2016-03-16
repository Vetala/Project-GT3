#pragma once
#include "Object.h"

class Finish : public Object
{
public:

	Ogre::Vector3 worldLocation;
	Ogre::Vector3 objectScale;


	Finish(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale);
	~Finish();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
};