#pragma once
#include "Character.h"

class ShipCharacter : public Character
{
protected:
	Ogre::String mName;

public:
	Ogre::SceneNode *mMainNode;
	ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr);
	~ShipCharacter();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);
};


