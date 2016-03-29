#pragma once
#include "BaseApplication.h"

struct SphereCollider {
	bool trigger;
	Ogre::Sphere sphere;
	SphereCollider(bool t, Ogre::Sphere s) {
		trigger = t;
		sphere = s;
	}
};
struct BoxCollider {
	bool trigger;
	Ogre::Box box;
	BoxCollider(bool t, Ogre::Box b) {
		trigger = t;
		box = b;
	}
};

class Object
{
public:
	float inverseMass;
	float mass;

	Ogre::String mName;
	Ogre::String mTag;
	Ogre::String mMeshName;
	Ogre::SceneNode *mMainNode; // Character position and rotation
	Ogre::Entity *mEntity; // Mesh
	std::list<SphereCollider *> sphereColliders;
	std::list<BoxCollider *> boxColliders;
	Ogre::SceneManager *mSceneMgr;

	Object(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName);
	~Object();
	Ogre::Vector3 getWorldPosition() {
		return mMainNode->_getDerivedPosition();
	}
	void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
	void setVisible(bool visible);
};
