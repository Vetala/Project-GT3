#include "Powerup.h"


Powerup::Powerup(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale) : Object(name, sceneMgr, meshName)
{
	//Sets the position and scale of the object
	mMainNode->setPosition(worldLocation);
	mMainNode->setScale(objectScale);

	//Assigns the Model
	mMainNode->attachObject(mEntity);

	SphereCollider *s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * mMainNode->getScale().z));
	s->setPositionToParentPosition(mMainNode->getPosition());
	sphereColliders.push_back(s);
}

void Powerup::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::update(elapsedTime, input);
}

Powerup::~Powerup()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}