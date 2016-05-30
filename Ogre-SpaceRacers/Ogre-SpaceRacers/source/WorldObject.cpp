/**
* @class WorldObject
* @author Explosive Shark Studios
* @date 12/04/2016
* @brief
*
* @section Description
* This class contains the input function to spawn world objects.
*
*/
#include "WorldObject.h"

WorldObject::WorldObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Quaternion worldRotation, Ogre::Vector3 objectScale, std::list<Ogre::Sphere *> sphereList) : Object(name, sceneMgr, meshName)
{
	mMainNode->setPosition(worldLocation);		///Sets the world location of the Node
	mMainNode->setOrientation(worldRotation);	///Sets the world rotation of the Node
	mMainNode->setScale(objectScale);			///Sets the scale of the Node
	mMainNode->attachObject(mEntity);			///Attahes the object to its main-node

	SphereCollider *s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * 0.75 * mMainNode->getScale().z));	///Initialises the sphere collision with a scale of 0.75 times the Z scale, a scale of 0.75 was the most realistic size for current object scaling
	s->setPositionToParentPosition(mMainNode->getPosition());	///Sets the Spherecollider position to the center of the main node
	physicsMat->bounciness = 0.02f;	///Sets a bounce effect for when the ship collides with the collider, knocking it back
	sphereColliders.push_back(s);	///Adds the collider to the collision list
}

void WorldObject::Update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::Update(elapsedTime, input);
}

WorldObject::~WorldObject()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}