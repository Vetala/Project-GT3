#pragma once
#include "BaseApplication.h"

class ExtendedCamera
{
protected:
	Ogre::SceneNode *mTargetNode; // The camera target
	Ogre::SceneNode *mCameraNode; // The camera itself
	Ogre::Camera *mCamera; // Ogre camera

	Ogre::SceneManager *mSceneMgr;
	Ogre::String mName;

	bool mOwnCamera; // To know if the ogre camera binded has been created outside or inside of this class

	Ogre::Real mTightness; // Determines the movement of the camera, 1 means tight movement, while 0 means no movement
public:
	ExtendedCamera();
	ExtendedCamera(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::Camera *camera = 0) {
		// Basic member references setup
		mName = name;
		mSceneMgr = sceneMgr;

		// Create the camera's node structure
		mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
		mTargetNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName + "_target");
		mCameraNode->setAutoTracking(true, mTargetNode); // The camera will always look at the camera target
		mCameraNode->setFixedYawAxis(true); // Needed because of auto tracking

											// Create our camera if it wasn't passed as a parameter
		if (camera == 0) {
			mCamera = mSceneMgr->createCamera(mName);
			mOwnCamera = true;
		}
		else {
			mCamera = camera;
			// just to make sure that mCamera is set to 'origin' (same position as the mCameraNode)
			mCamera->setPosition(0.0, 0.0, 0.0);
			mOwnCamera = false;
		}
		// ... and attach the Ogre camera to the camera node
		mCameraNode->attachObject(mCamera);
		mCameraNode->setPosition(0, 0, 0);
		// Default tightness
		mTightness = 0.05f;
	}

	~ExtendedCamera()
	{
		mCameraNode->detachAllObjects();
		if (mOwnCamera)
			delete mCamera;
		mSceneMgr->destroySceneNode(mName);
		mSceneMgr->destroySceneNode(mName + "_target");
	}

	void setTightness(Ogre::Real tightness) {
		mTightness = tightness;
	}

	Ogre::Real getTightness() {
		return mTightness;
	}

	Ogre::Vector3 getCameraPosition() {
		return mCameraNode->getPosition();
	}

	void update(Ogre::Real elapsedTime, Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition) {
		// Handle movement
		Ogre::Vector3 displacement;

		displacement = (cameraPosition - mCameraNode->getPosition()) * mTightness;
		mCameraNode->translate(displacement);

		displacement = (targetPosition - mTargetNode->getPosition()) * mTightness;
		mTargetNode->translate(displacement);
	}
};

