#include "Finish.h"

Finish::Finish(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale) : Object(name, sceneMgr, meshName)
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

void Finish::Update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::Update(elapsedTime, input);
}

Finish::~Finish()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}