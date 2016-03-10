#include "ShipCharacter.h"

ShipCharacter::ShipCharacter(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::Camera *camera) {
	// Setup basic member references
	mName = name;
	mSceneMgr = sceneMgr;

	// Setup basic node structure to handle 3rd person cameras
	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);

	mCameraNode = mMainNode->createChildSceneNode(mName + "_cameraNode", Ogre::Vector3(0, 50, -100));
	mCameraNode->setAutoTracking(true, mMainNode); // The camera will always look at the camera target
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
	if (input->isKeyDown(OIS::KC_W)) {
		//mMainNode->setPosition(mMainNode->getPosition() + mMainNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
		mMainNode->translate(mMainNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
		//mCameraNode->translate(mCameraNode->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
	}
	if (input->isKeyDown(OIS::KC_S)) {
		//mMainNode->setPosition(mMainNode->getPosition() + mMainNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
		mMainNode->translate(mMainNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
		//mCameraNode->translate(mCameraNode->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
	}
	if (input->isKeyDown(OIS::KC_A)) {
		mMainNode->yaw(Ogre::Radian(2 * elapsedTime));
		//mCameraNode->yaw(Ogre::Radian(2 * elapsedTime));
	}
	if (input->isKeyDown(OIS::KC_D)) {
		mMainNode->yaw(Ogre::Radian(-2 * elapsedTime));
		//mCameraNode->yaw(Ogre::Radian(-2 * elapsedTime));
	}

	//follow(mCameraNode, mMainNode, Ogre::Vector3(0, 50, -100), 0.01f);
	//float lerp = 0.01f;
	//mCameraNode->setPosition(lerp * mCameraNode->getPosition() + (1 - lerp) * Ogre::Vector3(0, 50, -100));
	//mCameraNode->setOrientation(lerp * mCameraNode->getOrientation() + (1 - lerp) * mMainNode->getOrientation());
}

void ShipCharacter::follow(Ogre::SceneNode *node, Ogre::SceneNode *toFollow, Ogre::Vector3 wantedPosition, float lerp)
{
	//mCameraNode->setPosition(lerp * *node->getPosition + (1 - lerp) * wantedPosition);
	//mCameraNode->setOrientation(lerp * *node->getOrientation + (1 - lerp) * *toFollow->getOrientation);
}


