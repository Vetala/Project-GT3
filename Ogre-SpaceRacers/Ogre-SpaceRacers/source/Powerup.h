#pragma once
#include "Object.h"

class Powerup : public Object
{
public:
	Ogre::Vector3 worldLocation;
	Ogre::Quaternion worldRotation;
	Ogre::Vector3 objectScale;

	float Cooldown;
	bool Inactive;
	
	Powerup(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Quaternion worldRotation, Ogre::Vector3 objectScale, std::list<Ogre::Sphere *> sphereList);
	~Powerup();
	void Update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void SetInactive();
};