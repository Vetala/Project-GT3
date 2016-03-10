#pragma once
#include "Character.h"

class ShipCharacter : public Character
{

public:
	ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::Camera *camera = 0);
	~ShipCharacter();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void follow(Ogre::SceneNode *node, Ogre::SceneNode *toFollow, Ogre::Vector3 wantedPosition, float lerp);
};


