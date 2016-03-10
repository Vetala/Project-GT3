#pragma once
#include "Character.h"

class ShipCharacter : public Character
{
protected:
	Ogre::String mName;
	int mShipHealth;

public:
	Ogre::SceneNode *mMainNode;
	Ogre::SceneNode *mRespawnNode;
	Ogre::Vector3 cameraNodeOffSet;
	Ogre::Vector3 sightNodeOffSet;
	Ogre::Vector3 respawnNodeOffSet;

	ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth);
	~ShipCharacter();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);

	void doDamage(int damage);//if a health pickup is picked up just call upon this function and make the damage negative. There is currently no max health implemented
	bool respawning;
	int respawnTimer;
	int baseRespawnTime;
};


