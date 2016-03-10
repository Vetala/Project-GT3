#pragma once
#include "Object.h"

class MovableObject : public Object
{
public:
	Ogre::Vector3 velocity;
	Ogre::Vector3 acceleration;
	Ogre::Vector3 force;

	MovableObject();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
};
