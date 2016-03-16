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

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth, Ogre::Camera *camera) : Character(name, sceneMgr, camera)
{
	/**
	*The constructor for a controllable spacechip currently asks for a name, the scene manager, a health amount and a camera
	*The name has to be unique to make sure that the construction of the scene nodes does not overwrite already created scene nodes
	*The SceneManager has to be the main scenemanager
	*The shiphealth has to be set in the constructor at the moment.
	*The camera has to be a predefined camera with a predefined viewport. The constructor asks for a camera to make sure that the camera correctly follows this ship
	*/
	mShipHealth = shipHealth;

	respawning = false;
	baseRespawnTime = 60;
	
	lastFrameAcceleration = (0, 0, 0);
	rollSpeed = 1; //Speed at which the spaceship rolls when turning
	pitchSpeed = 0.1; //Speed at which the spaceship pitches when accelerating
	accelSpeed = 3; //Speed at which the spaceship will accelerate
	damping = 0.98; //factor at which the spaceship will slow down each frame when not accelerating

	cameraNodeOffSet = Ogre::Vector3(0, 30, -50); //The distance between the camera and the spaceship
	sightOffSet = Ogre::Vector3(0, 0, 20); //The position where the camera is looking, used to add some more depth to the view
	respawnNodeOffSet = Ogre::Vector3(0, 0, -50); //The position where the player will respawn 
	mTightness = 0.3; //How tight the camera follows on low speeds. This creates a zoom function which makes the camera zoom out at high speeds but remain zoomed in at low speeds
	
	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mRespawnNode = mMainNode->createChildSceneNode(mName + "_respawn", respawnNodeOffSet);
	mShipNode = mMainNode->createChildSceneNode(mName + "_ship", Ogre::Vector3(0,3,0));
	mCameraNode = mMainNode->createChildSceneNode(mName + "_camera", cameraNodeOffSet);
	mSightNode = mMainNode->createChildSceneNode(mName + "_sight", sightOffSet);
	mCameraNode->setAutoTracking(true, (mSightNode)); // The camera will always look at the camera target
	mCameraNode->setFixedYawAxis(true); // Needed because of auto tracking

	collisionSphere = new Ogre::Sphere(mMainNode->getPosition(), mEntity->getBoundingRadius);

	// Create our camera if it wasn't passed as a parameter
	if (camera == 0) {
		mCamera = mSceneMgr->createCamera(mName);
	}
	else {
		mCamera = camera;
		mCamera->setPosition(0.0, 0.0, 0.0);
	}
	// Attach the Ogre camera to the camera node
	mCameraNode->attachObject(mCamera);
	mCameraNode->setPosition(0, 50, -100);

	// Give this character a shape 
	mEntity = mSceneMgr->createEntity(mName, "Ship2.mesh");
	mEntity->setCastShadows(false);
	mShipNode->attachObject(mEntity);
	respawnTimer = baseRespawnTime;
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

void ShipCharacter::respawn() 
{
	/**
	*If the characters health drops below 0 this function is called. The players position is set back.
	*/
	mMainNode->setPosition(mRespawnNode->_getDerivedPosition());
	respawning = true;
}

void ShipCharacter::handleCollision(MovableObject col)
{
	if (!col.trigger)
	{
		MovableObject::handleCollision(col);
	}
}

void ShipCharacter::handleCollision(Object col)
{
	if (col.mName == "Finish")
	{
		//Finished the race
		puts("Finished!");
	}
	if (!col.trigger)
	{
		MovableObject::handleCollision(col);
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
		if (input->isKeyDown(OIS::KC_O)) {
			respawn();
		}
		if (input->isKeyDown(OIS::KC_W)) {
			acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, accelSpeed * elapsedTime);
			if (mShipNode->getOrientation().getPitch() >= Ogre::Radian(-0.1))
			{
				mShipNode->pitch(Ogre::Radian(-pitchSpeed * elapsedTime));
			}
			}
		else {
			if (input->isKeyDown(OIS::KC_S)) {
				acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, -0.5*accelSpeed * elapsedTime);
				if (mShipNode->getOrientation().getPitch() <= Ogre::Radian(0.1))
				{
					mShipNode->pitch(Ogre::Radian(pitchSpeed * elapsedTime));
				}
			}
			else {
				acceleration = 0;
			}
		}
		if (input->isKeyDown(OIS::KC_A)) {
			turning = true;
			mMainNode->yaw(Ogre::Radian(2 * elapsedTime));
			if (mShipNode->getOrientation().getRoll() >= Ogre::Radian(-0.3))
			{
				mShipNode->roll(Ogre::Radian(-rollSpeed * elapsedTime));
			}
		}
		else {
			if (input->isKeyDown(OIS::KC_D)) {
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
		if (mShipNode->getOrientation().getRoll() <= mShipNode->getInitialOrientation().getRoll()&& turning == false)
		{
			mShipNode->roll(Ogre::Radian(rollSpeed *elapsedTime));
		}
		if (mShipNode->getOrientation().getRoll() >= mShipNode->getInitialOrientation().getRoll() && turning == false)
		{
			mShipNode->roll(Ogre::Radian(-rollSpeed * elapsedTime));
		}
		if (acceleration == lastFrameAcceleration)
		{
			if (mShipNode->getOrientation().getPitch() < mShipNode->getInitialOrientation().getPitch())
			{
				mShipNode->pitch(Ogre::Radian(pitchSpeed*elapsedTime));
			}
			if (mShipNode->getOrientation().getPitch() > mShipNode->getInitialOrientation().getPitch())
			{
				mShipNode->pitch(Ogre::Radian(-pitchSpeed*elapsedTime));
			}
		}
		
		lastFrameAcceleration = acceleration;
		velocity += acceleration;
		velocity *= damping;
		mMainNode->translate(velocity);
		mSceneMgr->getSceneNode(mName + "_camera")->setPosition(cameraNodeOffSet * (1 + (velocity.length()*mTightness)));
	}
	else {
		velocity = (0, 0, 0);
		respawnTimer--;
		if(respawnTimer < 0){
			respawning = false;
			respawnTimer = baseRespawnTime;
		}
	}
}

ShipCharacter::~ShipCharacter() {
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}


