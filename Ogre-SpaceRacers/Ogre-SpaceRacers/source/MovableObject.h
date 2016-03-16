#pragma once
#include "Object.h"

class MovableObject : public Object
{
public:
	Ogre::Vector3 velocity;
	Ogre::Vector3 acceleration;
	Ogre::Vector3 force;
	Ogre::Real damping;
	Ogre::Real bounciness;

	MovableObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName);
	~MovableObject();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void handleCollision(Ogre::Sphere mSphere, MovableObject col, Ogre::Sphere sphere);
	void handleCollision(Ogre::Sphere mSphere, Object col, Ogre::Sphere sphere);
};
