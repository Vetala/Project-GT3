#pragma once
#include "Object.h"

class MovableObject : public Object
{
public:
	Ogre::Vector3 velocity;
	Ogre::Vector3 acceleration;
	Ogre::Vector3 force;
	Ogre::Real damping;

	MovableObject(Ogre::String name, Ogre::SceneManager *sceneMgr);
	~MovableObject();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void handleCollision(MovableObject col);
	void handleCollision(Object col);
};
