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
	mShipHealthCap = 200;
	mBoostCap = 2;
	mAmmoCap = 20;
	mShipHealthGain = 50;
	mBoostGain = 1;
	mAmmoGain = 5;
	mStartShipHealth = shipHealth;
	mShipHealth = shipHealth;
	mBoost = shipBoost;
	mLifes = 5;
	shield = false;
	starting = true;
	finished = false;
	respawning = true;
	baseRespawnTime = 120;
	startTime = 3;
	maxVibrateTime = 30;
	vibrateTimer = -1;
	mSceneMgr = sceneMgr;
	mAmmo = 10;
	powerUp = false;
	basePUTimer = 90;
	powerUpTimer = basePUTimer;
	powerUpText = "";
	bullet = NULL;
	soundManager = new SoundManager();
	shieldEntity = mSceneMgr->createEntity(mName + "shield", "Shield.mesh");

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
	shieldEntity->setCastShadows(false);
	mShipNode->attachObject(mEntity);
	SphereCollider *s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * mMainNode->getScale().z));
	s->setPositionToParentPosition(mMainNode->getPosition());
	sphereColliders.push_back(s);
	respawnTimer = baseRespawnTime+ 50;

	//ps = mSceneMgr->createParticleSystem("Particle" + mName, "Examples/GreenyNimbus");
	//mShipNode->attachObject(ps);
}

void ShipCharacter::DoDamage(int damage)
{ 
	/**
	*If the player takes damage from hitting an obstacle or being hit by a bullet this function is called.
	*If the players health drops below 0 the player respawns
	*/
	if (!respawning)
	{
		if (!shield)
		{ 
			int v2 = rand() % 100;
			mShipHealth = mShipHealth - damage;
			if (controllerManager != 0 && damage > 0)
			{
				vibrateTimer = maxVibrateTime;
				controllerManager->Vibrate(playerNumber);
			}
			if (mShipHealth < 1) {
				if (v2 == 1)
				{
					soundManager->Play2D("../../Media/sounds/Wilhelm.wav");
				}
				else
				{
					//soundManager->Play2D("../../Media/sounds/Wilhelm.wav");
				}
				if (mName == "ship1")
				{
					if (mLifes > 0)
					{
						respawnText = "Player 1 has lost a life!";
						Respawn();
					}
					else
					{
						respawnText = "Player 2 wins!";
					}
				}
				else
				{

					if (mLifes > 0)
					{
						respawnText = "Player 2 has lost a life!";
						Respawn();
					}
					else
					{
						respawnText = "Player 1 wins!";
					}
				}
				mLifes--;
			}
		}
		if (shield)
		{
			soundManager->Play2D("../../Media/sounds/collision2.wav");
			mMainNode->detachObject(shieldEntity);
			shield = false;
		}
	}
}

void ShipCharacter::Boost(Ogre::Real elapsedTime)
{
	/**
	*If the player presses the boost key it temporarily gets additional acceleration speed resulting in a higher top speed while the player has boost
	*/
	if (mBoost > 0)
	{
		if (!soundManager->soundEngine->isCurrentlyPlaying("../../Media/sounds/boostUse.wav"))
		{
			soundManager->Play2D("../../Media/sounds/boostUse.wav");
		}
		rigidbody->velocity = mMainNode->getOrientation() * Ogre::Vector3(0, 0, 250*elapsedTime);
		mBoost--;
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
		soundManager->Play2D("../../Media/sounds/shoot.wav");
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
		if (!soundManager->soundEngine->isCurrentlyPlaying("../../Media/sounds/collision.wav"))
		{
			soundManager->Play2D("../../Media/sounds/collision.wav");
		}
		float speedBefore = rigidbody->velocity.length();
		MovableObject::HandleCollision(mSphere.sphere, col, sphere.sphere);
		float speedAfter = rigidbody->velocity.length();
		DoDamage((speedBefore - speedAfter) * 30);
	}
	if (col.mTag == "Powerup")
	{
		Ogre::MaterialPtr m_pMat = mEntity->getSubEntity(0)->getMaterial();
		powerUp = true;
		int v1 = rand() % 100;

		if (v1 <= 24)
		{
			if (mBoost < mBoostCap)
			{
				m_pMat->getTechnique(0)->getPass(0)->setAmbient(255.0f / 255.0f, 243.0f / 255.0f, 112.0f / 255.0f);
				m_pMat->getTechnique(0)->getPass(0)->setDiffuse(255.0f / 255.0f, 243.0f / 255.0f, 112.0f / 255.0f, 0);
				mEntity->setMaterialName(m_pMat->getName());
				powerUpText = "       \t\t   Boost!      \t\t\t       \t\t\t       \t\t\t        ";
				mBoost += mBoostGain;
				if (mBoost > mBoostCap)
				{
					mBoost = mBoostCap;
				}
				powerUpTimer = basePUTimer;
				soundManager->Play2D("../../Media/sounds/boostPickup.mp3");   //TO DO: Make the sound a bit louder
			}
		}

		if (v1 >= 25 && v1 <= 49)
		{
			if (mAmmo < mAmmoCap)
			{
				m_pMat->getTechnique(0)->getPass(0)->setAmbient(112.0f / 255.0f, 125.0f / 255.0f, 255.0f / 255.0f);
				m_pMat->getTechnique(0)->getPass(0)->setDiffuse(112.0f / 255.0f, 125.0f / 255.0f, 255.0f / 255.0f, 0);
				mEntity->setMaterialName(m_pMat->getName());
				powerUpText = "       \t\t         \t\t\t       \t\t\t       \t Ammo! \t\t        ";
				mAmmo += mAmmoGain;
				if (mAmmo > mAmmoCap)
				{
					mAmmo = mAmmoCap;
				}
				powerUpTimer = basePUTimer;
				soundManager->Play2D("../../Media/sounds/ammoPickup.wav");
			}
		}

		if (v1 >= 50 && v1 <= 74)
		{
			if (mShipHealth < mShipHealthCap)
			{
				m_pMat->getTechnique(0)->getPass(0)->setAmbient(255.0f / 255.0f, 112.0f / 255.0f, 196.0f / 255.0f);
				m_pMat->getTechnique(0)->getPass(0)->setDiffuse(255.0f / 255.0f, 112.0f / 255.0f, 196.0f / 255.0f, 0);
				mEntity->setMaterialName(m_pMat->getName());
				powerUpText = "Health!   \t\t\t\t\t         \t\t\t       \t\t\t       \t\t\t        ";
				mShipHealth += mShipHealthGain;
				if (mShipHealth > mShipHealthCap)
				{
					mShipHealth = mShipHealthCap;
				}
				powerUpTimer = basePUTimer;
				soundManager->Play2D("../../Media/sounds/health2.wav");
			}
		}
		if (v1 >= 75)
		{
			if (!shield)
			{
				m_pMat->getTechnique(0)->getPass(0)->setAmbient(112.0f / 255.0f, 255.0f / 255.0f, 171.0f / 255.0f);
				m_pMat->getTechnique(0)->getPass(0)->setDiffuse(112.0f / 255.0f, 255.0f / 255.0f, 171.0f / 255.0f, 0);
				mEntity->setMaterialName(m_pMat->getName());
				powerUpText = "Shielded!";
				powerUpTimer = basePUTimer;
				mMainNode->attachObject(shieldEntity);
				shield = true;
				soundManager->Play2D("../../Media/sounds/powerup.wav");
			}
		}
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
				Boost(elapsedTime);
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
				Boost(elapsedTime);
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

void ShipCharacter::DoGui(OgreBites::Label* respawnGUI, OgreBites::Label* speedGUI, OgreBites::Label* powerUpGUI,  OgreBites::SdkTrayManager* mTrayMgr)
{
	if(powerUp)
	{
		powerUpGUI->show();
		powerUpGUI->setCaption(powerUpText);
		powerUpTimer--;
		if(powerUpTimer < 1)
		{
			powerUpTimer = basePUTimer;
			powerUp = false;
		}
	}
	else
	{
		powerUpGUI->hide();
	}
	if (starting)
	{
		respawnGUI->setCaption("Starting in: " + converter.toString(respawnTimer));
		mTrayMgr->moveWidgetToTray(respawnGUI, OgreBites::TL_CENTER, 0);
		respawnGUI->show();
	}
	else
	{
		if (respawning)
		{
			respawnGUI->setCaption(respawnText + " Respawning in: "+ converter.toString(respawnTimer));
			mTrayMgr->moveWidgetToTray(respawnGUI, OgreBites::TL_CENTER, 0);
			respawnGUI->show();
		}
		else {
			respawnGUI->hide();
			mTrayMgr->removeWidgetFromTray("Respawn");
		}
	}
	speedGUI->setCaption("Health: " + converter.toString((int)(mShipHealth)) +"\t\t Boost:"+ converter.toString((int)(mBoost))
		+ "\t\t\tSpeed: " + converter.toString((int)(rigidbody->velocity.length() * 50))+ "\t\t\t Ammo: " + converter.toString(mAmmo) 
		+ "\t\t\t Lifes: " + converter.toString(mLifes));
	speedGUI->show();
}

ShipCharacter::~ShipCharacter() 
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}


