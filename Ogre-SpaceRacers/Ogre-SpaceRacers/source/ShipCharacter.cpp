/**
* @class ShipCharacter
* @author Explosive Shark Studios
* @date 14/03/2016
* @brief
*
* @section Description
* This class contains all information regarding a spaceship character. 
* It handles the input and contains multiple physics elements which are used to move the character
*/
#include "ShipCharacter.h"

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, int shipHealth, Ogre::Vector3 positionOffset, 
	int shipBoost, std::list<Bullet *> &bulletList, Controls *controls,InputManager *inputManager ,Ogre::Camera *camera) 
	: Character(name, sceneMgr, meshName, camera), mBulletList(bulletList)
{
	/**
	*The constructor for a controllable spacechip currently asks for a name, the scene manager, a health amount and a camera
	*The name has to be unique to make sure that the construction of the scene nodes does not overwrite already created scene nodes
	*The SceneManager has to be the main scenemanager
	*The shiphealth is the maximum amount of health this ship has, this is set in the constructor because different shiptypes can have different max health
	*The positionOffset is the difference between the base starting position in on the racetrack and the starting position this spaceship should have
	*The shipBoost is the maximum and starting amount of boost the ship has. 
	*the bulletList reference is a list which contains all bullets. This is used to monitor which bullets are currently active and update them accordingly
	*The controls is the control struct set for this spaceship.This is given in the construct to allow for changes to be made between races, can be 0 if a controller is used
	*The inputManager is only given if a controller is connected for this player. Can be 0 if there are no controllers for this player
	*The camera has to be a predefined camera with a predefined viewport. The constructor asks for a camera to make sure that the camera correctly 
	*follows this ship. Can be 0
	*
	*/
	mStartShipHealth = shipHealth;
	mShipHealth = shipHealth;
	mBoost = shipBoost;
	starting = true;
	finished = false;
	respawning = true;
	baseRespawnTime = 60;
	maxVibrateTime = 30;
	vibrateTimer = -1;
	mSceneMgr = sceneMgr;
	mAmmo = 10;
	bullet = NULL;
	soundManager = new SoundManager();

	if(inputManager != 0)
	{
		controllerManager = new InputManager();
		controllerManager = inputManager;
		if(mName == "Ship1")
		{
			playerNumber = 0;
		}
		if(mName == "Ship2")
		{
			playerNumber = 1;
		}
	}
	if (controls != 0)
	{
		player = new Controls();
		player = controls;
	}
	
	lastFrameAcceleration = (0, 0, 0);
	rollSpeed = 1; //Speed at which the spaceship rolls when turning
	pitchSpeed = 0.1f; //Speed at which the spaceship pitches when accelerating
	baseAccel = 3;
	accelSpeed = baseAccel; //Speed at which the spaceship will accelerate
	rigidbody->drag = 0.98; //factor at which the spaceship will slow down each frame when not accelerating

	mPositionOffset = positionOffset;
	cameraNodeOffSet = Ogre::Vector3(0, 30, -50); //The distance between the camera and the spaceship
	sightOffSet = Ogre::Vector3(0, 0, 20); //The position where the camera is looking, used to add some more depth to the view
	mTightness = 0.3; //How tight the camera follows on low speeds. This creates a zoom function which makes the camera zoom out at high speeds but remain zoomed in at low speeds
	respawnNodeOffSet = Ogre::Vector3(0, 0, -50); //The position where the player will respawn 

	mMainNode->translate(positionOffset);
	mRespawnNode = mMainNode->createChildSceneNode(mName + "_respawn", respawnNodeOffSet);
	mShipNode = mMainNode->createChildSceneNode(mName + "_ship", Ogre::Vector3(0,3,0));
	mSightNode = mMainNode->createChildSceneNode(mName + "_sight", sightOffSet);
	mCameraNode = mMainNode->createChildSceneNode(mName + "_camera", cameraNodeOffSet);
	mCameraNode->setAutoTracking(true, (mSightNode)); // The camera will always look at the camera target
	mCameraNode->setFixedYawAxis(true); // Needed because of auto tracking
	mCameraNode->setPosition(0, 50, -100);
	mCameraNode->attachObject(mCamera);	// Attach the Ogre camera to the camera node

	// Give this character a shape 
	mEntity->setCastShadows(false);
	mShipNode->attachObject(mEntity);
	SphereCollider *s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * mMainNode->getScale().z));
	s->setPositionToParentPosition(mMainNode->getPosition());
	sphereColliders.push_back(s);
	respawnTimer = baseRespawnTime;
}

void ShipCharacter::DoDamage(int damage)
{ 
	/**
	*If the player takes damage from hitting an obstacle or being hit by a bullet this function is called.
	*If the players health drops below 0 the player respawns
	*/
	if (!respawning)
	{
		mShipHealth = mShipHealth - damage;
		if (controllerManager != 0)
		{
			vibrateTimer = maxVibrateTime;
			controllerManager->Vibrate(playerNumber);
		}
		if (mShipHealth < 1) {
			Respawn();
		}
	}
}

void ShipCharacter::Boost()
{
	/**
	*If the player presses the boost key it temporarily gets additional acceleration speed resulting in a higher top speed while the player has boost
	*/
	if (mBoost > 0)
	{
		mBoost--;
		accelSpeed = baseAccel * 2;
	}
	else
	{
		accelSpeed = baseAccel;
	}

}

void ShipCharacter::Respawn() 
{
	/**
	*If the characters health drops below 0 this function is called. The players position is set back.
	*/
	respawning = true;
	mShipHealth = mStartShipHealth;
}

void ShipCharacter::Shoot()
{
	/**
	*If the character can shoot the ship shoots a bullet.
	*/
	if (mAmmo > 0 && shootTimer < 0)
	{
		for each (Bullet *b in mBulletList)
		{
			if (b->active == false)
			{
				bullet = b;
			}
		}
		bullet->SetActive(mMainNode);
		shootTimer = 10;
		mAmmo--;
		soundManager->Play2D("../../Media/sounds/explosion.wav");
	}
}

void ShipCharacter::HandleCollision(SphereCollider mSphere, Object col, SphereCollider sphere)
{
	/**
	*This handles all the spaceship specific collisions with non moving objects
	*/
	if (col.mName == "Finish")
	{
		//Finished the race
		finished = true;
		respawning = true;
		mMainNode->setPosition(mPositionOffset);
		rigidbody->velocity = Ogre::Vector3(0,0,0);
		rigidbody->acceleration = Ogre::Vector3(0, 0, 0);
		mMainNode->resetOrientation();
	}
	if (!sphere.trigger)
	{
		float speedBefore = rigidbody->velocity.length();
		MovableObject::HandleCollision(mSphere.sphere, col, sphere.sphere);
		float speedAfter = rigidbody->velocity.length();
		DoDamage((speedBefore - speedAfter) * 10);
	}
	if (col.mTag == "Powerup")
	{
		int v1 = rand() % 100;

		if (v1 <= 33)
		{
			mBoost += 100;
		}

		if (v1 >= 34 && v1 <= 66)
		{
			mAmmo += 10;
		}

		if (v1 >= 67)
		{
			mShipHealth += 100;
		}
		soundManager->Play2D("../../Media/sounds/bell.wav");
	}
}

void ShipCharacter::HandleCollision(SphereCollider mSphere, MovableObject col, SphereCollider sphere)
{
	/**
	*This handles all the spaceship specific collisions with moving objects
	*/
	if (!sphere.trigger)
	{
		MovableObject::HandleCollision(mSphere.sphere, col, sphere.sphere);
	}
}

void ShipCharacter::Forward(Ogre::Real elapsedTime)
{
	rigidbody->acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, accelSpeed * elapsedTime);
	if (mShipNode->getOrientation().getPitch() >= Ogre::Radian(-0.1))
	{
		mShipNode->pitch(Ogre::Radian(-pitchSpeed * elapsedTime));
	}
}

void ShipCharacter::Backward(Ogre::Real elapsedTime)
{
	rigidbody->acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, -0.5*accelSpeed * elapsedTime);
	if (mShipNode->getOrientation().getPitch() <= Ogre::Radian(0.1))
	{
		mShipNode->pitch(Ogre::Radian(pitchSpeed * elapsedTime));
	}
}

void ShipCharacter::TurnLeft(Ogre::Real elapsedTime)
{
	turning = true;
	mMainNode->yaw(Ogre::Radian(2 * elapsedTime));
	if (mShipNode->getOrientation().getRoll() >= Ogre::Radian(-0.3))
	{
		mShipNode->roll(Ogre::Radian(-rollSpeed * elapsedTime));
	}
}

void ShipCharacter::TurnRight(Ogre::Real elapsedTime)
{
	turning = true;
	mMainNode->yaw(Ogre::Radian(-2 * elapsedTime));
	if (mShipNode->getOrientation().getRoll() <= Ogre::Radian(0.3))
	{
		mShipNode->roll(Ogre::Radian(rollSpeed * elapsedTime));
	}
}

void ShipCharacter::Update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	/**
	*In the update function all the inputs are handled and the spaceship is moved/rotated
	*If the player is currently respawning the update does not execute
	*/
	Character::Update(elapsedTime, input);
	if (!respawning)
	{
		if (player != 0)
		{
			if (input->isKeyDown(player->shoot)) {
				Shoot();
			}
			if (input->isKeyDown(player->boost))
			{
				Boost();
			}
			if (input->isKeyDown(player->forwards)) {
				Forward(elapsedTime);
			}
			else {
				if (input->isKeyDown(player->backwards)) {
					Backward(elapsedTime);
				}
				else {
					rigidbody->acceleration = 0;
				}
			}
			if (input->isKeyDown(player->left)) {
				TurnLeft(elapsedTime);
			}
			else {
				if (input->isKeyDown(player->right)) {
					TurnRight(elapsedTime);
				}
				else {
					turning = false;
				}
			}
		}
		if (controllerManager != 0)
		{
			if (controllerManager->GetButton(0x0100,playerNumber)) {
				Shoot();
			}
			if (controllerManager->GetButton(0x0200,playerNumber))
			{
				Boost();
			}
			if (controllerManager->GetButton(0x1000,playerNumber)) {
				Forward(elapsedTime);
			}
			else {
				if (controllerManager->GetButton(0x2000, playerNumber)) {
					Backward(elapsedTime);
				}
				else {
					rigidbody->acceleration = 0;
				}
			}
			if (controllerManager->GetLeftStick(playerNumber).at(0)<0) {
				TurnLeft(elapsedTime);
			}
			else {
				if (controllerManager->GetLeftStick(playerNumber).at(0)>0) {
					TurnRight(elapsedTime);
				}
				else {
					turning = false;
				}
			}
		}
	}
	else {
		rigidbody->velocity = (0, 0, 0);
		respawnTimer--;
		if(respawnTimer < 0){
			if (!starting && !finished)
			{
				mMainNode->setPosition(mRespawnNode->_getDerivedPosition());
			}
			respawning = false;
			starting = false;
			finished = false;
			respawnTimer = baseRespawnTime;
		}
	}
	if (mShipNode->getOrientation().getRoll() >Ogre::Radian(0) && !turning)
	{
		mShipNode->roll(Ogre::Radian(-rollSpeed*elapsedTime));
	}
	if (mShipNode->getOrientation().getRoll() < Ogre::Radian(0) && !turning)
	{
		mShipNode->roll(Ogre::Radian(rollSpeed*elapsedTime));
	}
	lastFrameAcceleration = rigidbody->acceleration;
	rigidbody->velocity += rigidbody->acceleration;
	rigidbody->velocity *= rigidbody->drag;
	mMainNode->translate(rigidbody->velocity);
	mSceneMgr->getSceneNode(mName + "_camera")->setPosition(cameraNodeOffSet * (1 + (rigidbody->velocity.length()*mTightness)));
	accelSpeed = baseAccel;
	Ogre::Vector3 fixedY = mMainNode->getPosition();
	fixedY.y = 3;
	if(vibrateTimer > 0)
	{
		vibrateTimer--;
	}
	if(vibrateTimer == 0)
	{
		vibrateTimer--;
		controllerManager->StopVibrate(playerNumber);
	}
	mMainNode->setPosition(fixedY);
	shootTimer--;
}

void ShipCharacter::DoGui(OgreBites::Label* respawnGUI, OgreBites::Label* speedGUI, OgreBites::SdkTrayManager* mTrayMgr)
{
	if (starting)
	{
		respawnGUI->setCaption("Starting");
		mTrayMgr->moveWidgetToTray(respawnGUI, OgreBites::TL_CENTER, 0);
		respawnGUI->show();
	}
	else
	{
		if (finished)
		{
			respawnGUI->setCaption("Finished!");
			mTrayMgr->moveWidgetToTray(respawnGUI, OgreBites::TL_CENTER, 0);
			respawnGUI->show();
		}
		else {
			if (respawning)
			{
				respawnGUI->setCaption("Respawning...");
				mTrayMgr->moveWidgetToTray(respawnGUI, OgreBites::TL_CENTER, 0);
				respawnGUI->show();
			}
			else {
				respawnGUI->hide();
				if(mName == "Ship1")
				{
					mTrayMgr->removeWidgetFromTray("Respawn");
				}
				if(mName == "Ship2")
				{
					mTrayMgr->removeWidgetFromTray("Respawn2");
				}
			}
		}
	}
	speedGUI->setCaption("Health: " + converter.toString((int)(mShipHealth)) +"\t\t Boost:"+ converter.toString((int)(mBoost))
		+ "\t\t\tSpeed: " + converter.toString((int)(rigidbody->velocity.length() * 50))+ "\t\t\t Ammo: " + converter.toString(mAmmo));
	speedGUI->show();
}

ShipCharacter::~ShipCharacter() 
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}


