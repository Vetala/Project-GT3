/**
* @class Rock
* @author Explosive Shark Studios
* @date 29/03/2016
* @brief
*
* @section Description
* This class contains the input function to spawn world objects.
*
*/
#include "WorldObject.h"

WorldObject::WorldObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Quaternion worldRotation, Ogre::Vector3 objectScale, std::list<Ogre::Sphere *> sphereList) : Object(name, sceneMgr, meshName)
{
	mMainNode->setPosition(worldLocation);		//Sets the world location of the Node
	mMainNode->setOrientation(worldRotation);	//Sets the world rotation of the Node
	mMainNode->setScale(objectScale);			//Sets the scale of the Node

	mMainNode->attachObject(mEntity);

	SphereCollider *s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * 0.75 * mMainNode->getScale().z));
	s->setPositionToParentPosition(mMainNode->getPosition());
	physicsMat->bounciness = 0.1;
	sphereColliders.push_back(s);
}

void WorldObject::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::update(elapsedTime, input);
}

WorldObject::~WorldObject()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}