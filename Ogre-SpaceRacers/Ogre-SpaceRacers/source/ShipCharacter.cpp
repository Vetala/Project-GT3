#include "ShipCharacter.h"

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth) {
	// Setup basic member references
	mName = name;
	mSceneMgr = sceneMgr;
	mShipHealth = shipHealth;

	respawning = false;
	baseRespawnTime = 60;
	sightNodeOffSet = Ogre::Vector3(0, 0, 100);
	cameraNodeOffSet = Ogre::Vector3(0, 50, -100);
	respawnNodeOffSet = Ogre::Vector3(0, 0, -100);

	// Setup basic node structure to handle 3rd person cameras
	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mSightNode = mMainNode->createChildSceneNode(mName + "_sight", sightNodeOffSet);
	mCameraNode = mMainNode->createChildSceneNode(mName + "_camera", cameraNodeOffSet);
	mRespawnNode = mMainNode->createChildSceneNode(mName + "_respawn", respawnNodeOffSet);

	// Give this character a shape 
	mEntity = mSceneMgr->createEntity(mName, "Ship2.mesh");
	mMainNode->attachObject(mEntity);
	respawnTimer = baseRespawnTime;
}

void ShipCharacter::setVisible(bool visible) {
	mMainNode->setVisible(visible);
}

void ShipCharacter::doDamage(int damage){
	mShipHealth = mShipHealth - damage;
}

ShipCharacter::~ShipCharacter() {
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}

void ShipCharacter::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	if (!respawning)
	{
		if (mShipHealth < 1 || input->isKeyDown(OIS::KC_O)) {
			//insert respawn function here
			mMainNode->setPosition(mRespawnNode->getPosition());
			mSightNode->setPosition((mRespawnNode->getPosition()+sightNodeOffSet));
			mCameraNode->setPosition((mRespawnNode->getPosition()+cameraNodeOffSet));
			mRespawnNode->setPosition((mRespawnNode->getPosition()+respawnNodeOffSet));
			respawning = true;
		}
		if (input->isKeyDown(OIS::KC_W)) {
			mMainNode->translate(mMainNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
			mSightNode->translate(mSightNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
			mCameraNode->translate(mCameraNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
			mRespawnNode->translate(mRespawnNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
		}
		if (input->isKeyDown(OIS::KC_S)) {
			mMainNode->translate(mMainNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
			mSightNode->translate(mSightNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
			mCameraNode->translate(mCameraNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
			mRespawnNode->translate(mRespawnNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
		}
		if (input->isKeyDown(OIS::KC_A)) {
			mMainNode->yaw(Ogre::Radian(2 * elapsedTime));
			mSightNode->yaw(Ogre::Radian(2 * elapsedTime));
			mCameraNode->yaw(Ogre::Radian(2 * elapsedTime));
			mRespawnNode->yaw(Ogre::Radian(2 * elapsedTime));
		}
		if (input->isKeyDown(OIS::KC_D)) {
			mMainNode->yaw(Ogre::Radian(-2 * elapsedTime));
			mSightNode->yaw(Ogre::Radian(-2 * elapsedTime));
			mCameraNode->yaw(Ogre::Radian(-2 * elapsedTime));
			mRespawnNode->yaw(Ogre::Radian(-2 * elapsedTime));
		}
	}
	else {
		respawnTimer--;
		if(respawnTimer < 0){
			respawning = false;
			respawnTimer = baseRespawnTime;
		}
	}
}



