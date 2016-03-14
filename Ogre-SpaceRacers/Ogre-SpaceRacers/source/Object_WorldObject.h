#pragma once
#include "Object.h"

class Object_WorldObject : public Object
{
public:

	Ogre::String mMeshName;
	Ogre::Vector3 worldLocation;
	Ogre::Vector3 objectScale;
	

	Object_WorldObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String MeshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale);
	~Object_WorldObject();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
};