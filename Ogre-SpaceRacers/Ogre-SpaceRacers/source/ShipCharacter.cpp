#include "ShipCharacter.h"

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, int shipHealth) {
	// Setup basic member references
	mName = name;
	mSceneMgr = sceneMgr;
	mShipHealth = shipHealth

	// Setup basic node structure to handle 3rd person cameras
	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mSightNode = mMainNode->createChildSceneNode(mName + "_sight", Ogre::Vector3(0, 0, 100));
	mCameraNode = mMainNode->createChildSceneNode(mName + "_camera", Ogre::Vector3(0, 50, -100));

	// Give this character a shape 
	mEntity = mSceneMgr->createEntity(mName, "Ship2.mesh");
	mMainNode->attachObject(mEntity);
}

void ShipCharacter::setVisible(bool visible) {
	mMainNode->setVisible(visible);
}

int setHealth(int shipHealth, int damage){
	shipHealth = shipHealth - damage;
	return shipHealth;
}

ShipCharacter::~ShipCharacter() {
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}

void ShipCharacter::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	if (mShipHealth < 1) {
		//insert respawn function here
	}
	if (input->isKeyDown(OIS::KC_W)) {
		mMainNode->translate(mMainNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
		mSightNode->translate(mSightNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
		mCameraNode->translate(mCameraNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
	}
	if (input->isKeyDown(OIS::KC_S)) {
		mMainNode->translate(mMainNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
		mSightNode->translate(mSightNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
		mCameraNode->translate(mCameraNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
	}
	if (input->isKeyDown(OIS::KC_A)) {
		mMainNode->yaw(Ogre::Radian(2 * elapsedTime));
		mSightNode->yaw(Ogre::Radian(2 * elapsedTime));
		mCameraNode->yaw(Ogre::Radian(2 * elapsedTime));
	}
	if (input->isKeyDown(OIS::KC_D)) {
		mMainNode->yaw(Ogre::Radian(-2 * elapsedTime));
		mSightNode->yaw(Ogre::Radian(-2 * elapsedTime));
		mCameraNode->yaw(Ogre::Radian(-2 * elapsedTime));
	}
}



