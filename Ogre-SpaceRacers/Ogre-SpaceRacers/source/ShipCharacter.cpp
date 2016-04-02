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

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, int shipHealth, Ogre::Vector3 positionOffset, int shipBoost, Controls *controls, Ogre::Camera *camera) : Character(name, sceneMgr, meshName, camera)
{
	/**
	*The constructor for a controllable spacechip currently asks for a name, the scene manager, a health amount and a camera
	*The name has to be unique to make sure that the construction of the scene nodes does not overwrite already created scene nodes
	*The SceneManager has to be the main scenemanager
	*The shiphealth has to be set in the constructor at the moment.
	*The camera has to be a predefined camera with a predefined viewport. The constructor asks for a camera to make sure that the camera correctly follows this ship
	*/
	mShipHealth = shipHealth;
	mBoost = shipBoost;
	starting = true;
	finished = false;
	respawning = true;
	baseRespawnTime = 60;
	
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
	player = new Controls();
	player = controls;
}

void ShipCharacter::doDamage(int damage)
{ 
	/**
	*If the player takes damage from hitting an obstacle or being hit by a bullet this function is called.
	*If the players health drops below 0 the player respawns
	*/
	mShipHealth = mShipHealth - damage;
	if (mShipHealth < 1) {
		respawn();
	}
}

void ShipCharacter::boosting()
{
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

void ShipCharacter::respawn() 
{
	/**
	*If the characters health drops below 0 this function is called. The players position is set back.
	*/
	respawning = true;
}

void ShipCharacter::handleCollision(SphereCollider mSphere, Object col, SphereCollider sphere)
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
		MovableObject::handleCollision(mSphere.sphere, col, sphere.sphere);
	}
}

void ShipCharacter::handleCollision(SphereCollider mSphere, MovableObject col, SphereCollider sphere)
{
	/**
	*This handles all the spaceship specific collisions with moving objects
	*/
	if (!sphere.trigger)
	{
		MovableObject::handleCollision(mSphere.sphere, col, sphere.sphere);
	}
}

void ShipCharacter::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	/**
	*In the update function all the inputs are handled and the spaceship is moved/rotated
	*If the player is currently respawning the update does not execute
	*/
	Character::update(elapsedTime, input);
	if (!respawning)
	{
			if (input->isKeyDown(player->shoot)) {
				respawn();
			}
			if(input->isKeyDown(player->boost))
			{
				boosting();
			}
			if (input->isKeyDown(player->forwards)) {
				rigidbody->acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, accelSpeed * elapsedTime);
				if (mShipNode->getOrientation().getPitch() >= Ogre::Radian(-0.1))
				{
					mShipNode->pitch(Ogre::Radian(-pitchSpeed * elapsedTime));
				}
			}
			else {
				if (input->isKeyDown(player->backwards)) {
					rigidbody->acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, -0.5*accelSpeed * elapsedTime);
					if (mShipNode->getOrientation().getPitch() <= Ogre::Radian(0.1))
					{
						mShipNode->pitch(Ogre::Radian(pitchSpeed * elapsedTime));
					}
				}
				else {
					rigidbody->acceleration = 0;
				}
			}
			if (input->isKeyDown(player->left)) {
				turning = true;
				mMainNode->yaw(Ogre::Radian(2 * elapsedTime));
				if (mShipNode->getOrientation().getRoll() >= Ogre::Radian(-0.3))
				{
					mShipNode->roll(Ogre::Radian(-rollSpeed * elapsedTime));
				}
			}
			else {
				if (input->isKeyDown(player->right)) {
					turning = true;
					mMainNode->yaw(Ogre::Radian(-2 * elapsedTime));
					if (mShipNode->getOrientation().getRoll() <= Ogre::Radian(0.3))
					{
						mShipNode->roll(Ogre::Radian(rollSpeed * elapsedTime));
					}
				}
				else {
					turning = false;
				}
			}
		if(mShipNode->getOrientation().getRoll() >Ogre::Radian(0) && !turning)
		{
			mShipNode->roll(Ogre::Radian(-rollSpeed*elapsedTime));
		}
		if (mShipNode->getOrientation().getRoll() < Ogre::Radian(0)&& !turning)
		{
			mShipNode->roll(Ogre::Radian(rollSpeed*elapsedTime));
		}
		lastFrameAcceleration = rigidbody->acceleration;
		rigidbody->velocity += rigidbody->acceleration;
		rigidbody->velocity *= rigidbody->drag;
		mMainNode->translate(rigidbody->velocity);
		mSceneMgr->getSceneNode(mName + "_camera")->setPosition(cameraNodeOffSet * (1 + (rigidbody->velocity.length()*mTightness)));
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
	Ogre::Vector3 fixedY = mMainNode->getPosition();
	fixedY.y = 3;
	//mMainNode->setPosition(fixedY);
}

void ShipCharacter::doGUI(OgreBites::Label* respawnGUI, OgreBites::Label* speedGUI, OgreBites::SdkTrayManager* mTrayMgr)
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
				mTrayMgr->removeWidgetFromTray("Respawn");
			}
		}
	}
	Ogre::StringConverter converter;
	speedGUI->setCaption("Health: " + converter.toString((int)(mShipHealth)) +"\t\t Boost:"+ converter.toString((int)(mBoost))+ "\t\t\tSpeed: " + converter.toString((int)(rigidbody->velocity.length() * 50)));
	speedGUI->show();
}

ShipCharacter::~ShipCharacter() 
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}


