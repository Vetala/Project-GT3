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
	void SetActive(Ogre::SceneNode *mShipNode);
	void SetInactive();
	void Update(Ogre::Real elapsedTime, OIS::Keyboard * input);
};

