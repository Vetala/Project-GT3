#pragma once
#ifndef __ParticleFX_H__
#define __ParticleFX_H__

#include "Character.h"
#include "Controls.h"
#include "InputManager.h"
#include "Bullet.h"
#include "vector"
#include "SoundManager.h"
struct Keys;

class ShipCharacter : public Character
{
protected:
	int mShipHealth; ///The current health amount this spaceship has
	int mStartShipHealth;///The starting amount of health this spaceship has
	int mShipHealthCap;
	int mShipHealthGain;
	int startTime;
	int mBoost;///The current amount of boost this spaceship has
	int mBoostCap;
	int mBoostGain;
	int playerNumber; ///Used if a controller is connected
	int mAmmo; ///The current amount of ammo this spaceship has
	int mAmmoCap;
	int mAmmoGain;
	Controls *player;///The controls for this player if a XBOX controller is not connected
	InputManager *controllerManager;///The controllermanager which contains the logic used if a XBOX controller is connected
	Ogre::SceneManager *mSceneMgr;
	std::list<Bullet *> &mBulletList;///The bulletlist
	Ogre::StringConverter converter;///A converter which converts numbers to ogre::string to be used in the GUI
	Bullet *bullet;///A single bullet
	SoundManager *soundManager;
	Ogre::String respawnText;
	Ogre::Entity* shieldEntity;
	bool powerUp;
	Ogre::String powerUpText;
	int powerUpTimer;
	int basePUTimer;
	Ogre::ParticleSystem *pEngine;///A particle system displaying the engine emission
	Ogre::ParticleSystem *pCrash;///A particle system displaying a ship explosion
	Ogre::ParticleSystem *pBoost;///A particle system displaying the engine emission at boost level
	Ogre::ParticleSystem *pHit;///A particle system displaying the ship taking damage


public:
	ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, int shipHealth, Ogre::Vector3 positionOffset, 
		int shipBoost, std::list<Bullet *> &bulletList, Controls *controls = 0,InputManager *inputManager = 0,  Ogre::Camera *camera = 0);
	~ShipCharacter();
	void Update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void DoGui(OgreBites::Label* respawnGUI, OgreBites::Label* speedGUI, OgreBites::Label* powerupGUI, OgreBites::SdkTrayManager* mTrayMgr, Ogre::Real elapsedTime);
	void Respawn();
	void Boost(Ogre::Real elapsedTime);
	void Shoot();
	void DoDamage(int damage);
	void HandleCollision(SphereCollider mSphere, MovableObject col, SphereCollider sphere);
	void Forward(Ogre::Real elapsedTime);
	void Backward(Ogre::Real elapsedTime);
	void TurnLeft(Ogre::Real elapsedTime);
	void TurnRight(Ogre::Real elapsedTime);
	void HandleCollision(SphereCollider mSphere, Object col, SphereCollider sphere);
	void Restart();

	int mLifes;
	bool restart;
	Ogre::SceneNode *mRespawnNode; ///The spot where the ship will respawn in case of a crash
	Ogre::SceneNode *mShipNode; ///The ship itself gets a node to make sure certain rotations are only done by the ship and do not use any of the other nodes
	Ogre::Vector3 respawnNodeOffSet; ///The difference between the ship position and the respawn position
	Ogre::Vector3 lastFrameAcceleration; ///The acceleration during the last frame on the ship. This is used to check if the ship is accelerating 
	Ogre::Vector3 mPositionOffset; ///The position difference from the starting position
	Ogre::Radian turned; ///The amount of degrees the ship has turned. Used to turn the ship back after it has stop turning
	Ogre::Real accelSpeed; ///The speed at which the ship accelerates, becomes doubled  if the ship is boosting
	Ogre::Real baseAccel; ///The base acceleration speed the ship has. Used to reset the acceleration speed after boosting
	Ogre::Real respawnTimer; ///The remaining time it takes for the ship to respawn after crashing
	bool respawning; ///a boolean to check if the ship is currently respawning. If the ship is respawning the update function cannot be called upon resulting in no possible movement
	bool starting;///A boolean used to check if the ship is currently starting. Works similarly to the respawning boolean but displays a different text on the gui
	bool finished;///A boolean used to check if the ship has finished. 
	bool turning; ///A boolean to check if the ship is turning or not. Used to check if an animation needs to be played
	bool shield; ///A boolean to check if a shield is up to prevent DoDamage from affecting player health
	bool boosting; ///A boolean to avoid boosting to occur multiple times on the same/consecutive frame
	float rollSpeed;///The speed at which the ship rolls during turning
	float pitchSpeed;///The speed at which the ship pitches during acceleration/decelleration
	int baseRespawnTime;///The max time it can take for a ship to respawn
	int maxVibrateTime;///The max time a controller can vibrate after taking damage
	int boostTimer;///A timer used to avoid boosting to occur multiple times on the same/consecutive  frames
	int vibrateTimer;///Remaining amount of frames the controller is vibrating
	int shootTimer;///Amount of frames between shots
	int hitTimer;///A timer used to show the hit particles for a short amount of time
	bool hitActivateParticle;///A bool to only attach the hit particles once to prevent an error
};
#endif

