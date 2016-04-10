#pragma once
#include "Physics.h"
#include "BaseApplication.h"

class Object
{
public:
	Ogre::String mName;
	Ogre::String mTag;
	Ogre::String mMeshName;
	Ogre::SceneNode *mMainNode; // Character position and rotation
	Ogre::Entity *mEntity; // Mesh
	std::list<SphereCollider *> sphereColliders;
	std::list<BoxCollider *> boxColliders;
	Ogre::SceneManager *mSceneMgr;
	
	PhysicsMaterial *physicsMat;

	Object(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName);
	~Object();

	Ogre::Vector3 getWorldPosition() {
		return mMainNode->_getDerivedPosition();
	}
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);
};
