#include "ShipCharacter.h"

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth, Ogre::Camera *camera) {
	// Setup basic member references
	mName = name;
	mSceneMgr = sceneMgr;
	mShipHealth = shipHealth;

	respawning = false;
	baseRespawnTime = 60;
	
	velocity = (0, 0, 0);
	speed = 3;
	cameraNodeOffSet = Ogre::Vector3(0, 30, -50);
	sightOffSet = Ogre::Vector3(0, 0, 20);
	respawnNodeOffSet = Ogre::Vector3(0, 0, -50);
	mTightness = 0.3;
	damping = 0.98;

	// Setup basic node structure to handle 3rd person cameras
	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mRespawnNode = mMainNode->createChildSceneNode(mName + "_respawn", respawnNodeOffSet);
	mCameraNode = mMainNode->createChildSceneNode(mName + "_cameraNode", cameraNodeOffSet);
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
	mMainNode->attachObject(mEntity);
	respawnTimer = baseRespawnTime;
}

void ShipCharacter::doDamage(int damage){
	mShipHealth = mShipHealth - damage;
	if (mShipHealth < 1) {
		//insert respawn function here
		mMainNode->setPosition(mRespawnNode->getPosition());
		respawning = true;
	}
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
			mMainNode->setPosition(mRespawnNode->getPosition());
			respawning = true;
		}
		if (input->isKeyDown(OIS::KC_W)) {
			acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, speed * elapsedTime);
			}
		else {
			if (input->isKeyDown(OIS::KC_S)) {
				acceleration = mMainNode->getOrientation() * Ogre::Vector3(0, 0, -0.5*speed * elapsedTime);
			}
			else {
				acceleration = 0;
			}
		}
		if (input->isKeyDown(OIS::KC_A)) {
			mMainNode->yaw(Ogre::Radian(2 * elapsedTime));
		}
		if (input->isKeyDown(OIS::KC_D)) {
			mMainNode->yaw(Ogre::Radian(-2 * elapsedTime));
		}
		velocity += acceleration;
		velocity *= damping;
		mMainNode->translate(velocity);
		mSceneMgr->getSceneNode(mName + "_cameraNode")->setPosition(cameraNodeOffSet * (1 + (velocity.length()*mTightness)));
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



