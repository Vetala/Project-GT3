#pragma once
#include "MovableObject.h"
class Bullet :
	public MovableObject
{
protected:
	SphereCollider *s;
	int activeTimer;

public:
	Bullet(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName);
	virtual ~Bullet();
	bool active;
	void setActive(Ogre::SceneNode *mShipNode);
	void setInactive();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void Destroy();
};

