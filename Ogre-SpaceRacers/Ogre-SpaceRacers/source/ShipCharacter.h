#pragma once
#include "Character.h"

class ShipCharacter : public Character
{
protected:
	Ogre::String mName;
	int mShipHealth;

public:
	Ogre::SceneNode *mMainNode;
	ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth);
	~ShipCharacter();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);
	int setHealth(int shipHealth, int damage);//if a health pickup is picked up just call upon this function and make the damage negative. There is currently no max health implemented
};


