/**
* @class Powerup
* @author Explosive Shark Studios
* @date 12/04/2016
* @brief
*
* @section Description
* This class contains the input function to spawn world objects.
*
*/
#include "Powerup.h"

Powerup::Powerup(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Quaternion worldRotation, Ogre::Vector3 objectScale, std::list<Ogre::Sphere *> sphereList) : Object(name, sceneMgr, meshName)
{
	mMainNode->setPosition(worldLocation);		///Sets the world location of the Node
	mMainNode->setOrientation(worldRotation);	///Sets the world rotation of the Node
	mMainNode->setScale(objectScale);			///Sets the scale of the Node
	mMainNode->attachObject(mEntity);			///Attahes the object to its main-node

	SphereCollider *s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * 1));	///Initialises the sphere collision with a scale of 1
	s->trigger = true;	///Sets the collision radius to act as a trigger-zone instead of blocking objects
	s->setPositionToParentPosition(mMainNode->getPosition());	///Sets the Spherecollider position to the center of the main node
	sphereColliders.push_back(s);	///Adds the collider to the collision list

	Inactive = false;	///Initialises the powerup to be active and ready for being picked up the moment it is created in the world
}

void Powerup::Update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::Update(elapsedTime, input);

	if (Inactive == true)
	{
		Cooldown--;		///Whilst the object is inactive, lower the cooldown timer at the update rate
		if (Cooldown <= 1)	///When the cooldown reaches below 1 the powerup must be made active again
		{
			Inactive = false;	///Re-activates the powerup so it can be picked up again
			mMainNode->attachObject(mEntity);	///Re-attaches the mesh and collision objects to the node so they can make the object visible again and get picked up again
		}

	}
}

void Powerup::SetInactive()
{
	Cooldown = 100;	///Sets the time it takes until the powerup can be picked up again
	Inactive = true;	///Turns the powerup inactive so it can not be picked up again during the cooldown time
	mMainNode->detachAllObjects();	///Detaches the mesh and collision objects from the node, making them disappear from view so it appears the object has been picked up
}

Powerup::~Powerup()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}