#include "ShipCharacter.h"

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth, Ogre::Camera *camera) {
	// Setup basic member references
	mName = name;
	mSceneMgr = sceneMgr;
	mShipHealth = shipHealth;

	respawning = false;
	baseRespawnTime = 60;
	
	velocity = (0, 0, 0); //start velocity
	lastFrameAcceleration = (0, 0, 0);
	rollSpeed = 1; //Speed at which the spaceship rolls when turning
	pitchSpeed = 0.1; //Speed at which the spaceship pitches when accelerating
	speed = 3; //Speed at which the spaceship will accelerate
	damping = 0.98; //factor at which the spaceship will slow down each frame when not accelerating

	cameraNodeOffSet = Ogre::Vector3(0, 30, -50);
	sightOffSet = Ogre::Vector3(0, 0, 20);
	respawnNodeOffSet = Ogre::Vector3(0, 0, -50);
	mTightness = 0.3;
	

	// Setup basic node structure to handle 3rd person cameras
	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mRespawnNode = mMainNode->createChildSceneNode(mName + "_respawn", respawnNodeOffSet);
	mShipNode = mMainNode->createChildSceneNode(mName + "_ship", Ogre::Vector3(0,3,0));
	mCameraNode = mMainNode->createChildSceneNode(mName + "_camera", cameraNodeOffSet);
	mSightNode = mMainNode->createChildSceneNode(mName + "_sight", sightOffSet);
	mCameraNode->setAutoTracking(true, (mSightNode)); // The camera will always look at the camera target
	mCameraNode->setFixedYawAxis(true); // Needed because of auto tracking

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

void ShipCharacter::doDamage(int damage){
	mShipHealth = mShipHealth - damage;
	if (mShipHealth < 1) {
		respawn();
	}
}

void ShipCharacter::respawn() {
	mMainNode->setPosition(mRespawnNode->_getDerivedPosition());
	respawning = true;
}

ShipCharacter::~ShipCharacter() {
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}

void ShipCharacter::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Character::update(elapsedTime, input);
	if (!respawning)
	{
		if (input->isKeyDown(OIS::KC_O)) {
			respawn();
		}
		if (input->isKeyDown(OIS::KC_W)) {
			acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, speed * elapsedTime);
			if (mShipNode->getOrientation().getPitch() >= Ogre::Radian(-0.1))
			{
				mShipNode->pitch(Ogre::Radian(-pitchSpeed * elapsedTime));
			}
			}
		else {
			if (input->isKeyDown(OIS::KC_S)) {
				acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, -0.5*speed * elapsedTime);
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



