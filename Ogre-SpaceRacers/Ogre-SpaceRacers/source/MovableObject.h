#pragma once
#include "Object.h"

class MovableObject : public Object
{
public:
	RigidBody *rigidbody;

	MovableObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName);
	~MovableObject();
	void Update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void HandleCollision(Ogre::Sphere mSphere, MovableObject col, Ogre::Sphere sphere);
	void HandleCollision(Ogre::Sphere mSphere, Object col, Ogre::Sphere sphere);
};
