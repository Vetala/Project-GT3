#pragma once
#include "Character.h"

class ShipCharacter : public Character
{
protected:
	int mShipHealth;

public:
	ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth, Ogre::Camera *camera = 0);
	~ShipCharacter();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);

	Ogre::SceneNode *mRespawnNode;
	Ogre::Vector3 cameraNodeOffSet;
	Ogre::Vector3 respawnNodeOffSet;

	void doDamage(int damage);//if a health pickup is picked up just call upon this function and make the damage negative. There is currently no max health implemented
	bool respawning;
	int respawnTimer;
	int baseRespawnTime;
};


