#pragma once
#include "Object.h"

class WorldChunk : public Object
{
public:
	Ogre::Vector3 worldLocation;
	Ogre::Vector3 objectScale;

	WorldChunk(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale, std::list<Ogre::Sphere *> sphereList);
	~WorldChunk();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
};