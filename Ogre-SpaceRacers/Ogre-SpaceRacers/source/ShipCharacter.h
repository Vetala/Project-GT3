#pragma once
#include "Character.h"

class ShipCharacter : public Character
{
protected:
	int mShipHealth;

public:
	ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, int shipHealth, Ogre::Camera *camera = 0);
	~ShipCharacter();
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void respawn();
	void doDamage(int damage);
	void handleCollision(Ogre::Sphere mSphere, MovableObject col, Ogre::Sphere sphere);
	void handleCollision(Ogre::Sphere mSphere, Object col, Ogre::Sphere sphere);

	Ogre::SceneNode *mRespawnNode; ///The spot where the ship will respawn in case of a crash
	Ogre::SceneNode *mShipNode; ///the ship itself gets a node to make sure certain rotations are only done by the ship and do not use any of the other nodes
	Ogre::Vector3 respawnNodeOffSet; ///The difference between the ship position and the respawn position
	Ogre::Vector3 lastFrameAcceleration; ///the acceleration during the last frame on the ship. This is used to check if the ship is accelerating 
	Ogre::Radian turned; ///The amount of degrees the ship has turned. Used to turn the ship back after it has stop turning
	float accelSpeed; ///the speed at which the ship accelerates

	bool respawning; ///a boolean to check if the ship is currently respawning. If the ship is respawning the update function cannot be called upon resulting in no possible movement
	bool turning; ///a boolean to check if the ship is turning or not. Used to check if an animation needs to be played
	int respawnTimer;///The remaining time it takes for the ship to respawn after crashing
	float rollSpeed;///the speed at which the ship rolls during turning
	float pitchSpeed;///the speed at which the ship pitches during acceleration/decelleration
	int baseRespawnTime;///the max time it can take for a ship to respawn
};


