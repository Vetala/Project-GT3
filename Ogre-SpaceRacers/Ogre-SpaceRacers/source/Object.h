#pragma once
#include "BaseApplication.h"

class Object
{
public:
	float inverseMass;
	bool trigger;

	Ogre::String mName;
	Ogre::String mMeshName;
	Ogre::SceneNode *mMainNode; // Character position and rotation
	Ogre::Entity *mEntity; // Mesh
	Ogre::Sphere *collisionSphere;
	std::list<Ogre::Sphere *> collisionSphereList;
	std::list<Ogre::Box *> collisionBoxList;
	Ogre::SceneManager *mSceneMgr;

	Object(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName);
	~Object();
	Ogre::Vector3 getWorldPosition() {
		return mMainNode->_getDerivedPosition();
	}
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);
};
