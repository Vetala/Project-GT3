#include "Finish.h"

Finish::Finish(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale) : Object(name, sceneMgr, meshName)
{
	//Sets the position and scale of the object
	mMainNode->setPosition(worldLocation);
	mMainNode->setScale(objectScale);

	//Assigns the Model
	mMainNode->attachObject(mEntity);

	sphereColliders.push_back(new SphereCollider(true, Ogre::Sphere(mMainNode->getPosition(), mEntity->getBoundingRadius() * objectScale.z)));
}

void Finish::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::update(elapsedTime, input);
}

Finish::~Finish()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}