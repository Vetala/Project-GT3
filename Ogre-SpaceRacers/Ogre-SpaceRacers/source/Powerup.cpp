#include "Powerup.h"

Powerup::Powerup(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Quaternion worldRotation, Ogre::Vector3 objectScale, std::list<Ogre::Sphere *> sphereList) : Object(name, sceneMgr, meshName)
{
	mMainNode->setPosition(worldLocation);		//Sets the world location of the Node
	mMainNode->setOrientation(worldRotation);	//Sets the world rotation of the Node
	mMainNode->setScale(objectScale);			//Sets the scale of the Node

	mMainNode->attachObject(mEntity);

	SphereCollider *s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * 1));// mMainNode->getScale().z));
	s->trigger = true;
	s->setPositionToParentPosition(mMainNode->getPosition());
	//physicsMat->bounciness = 0.1;
	sphereColliders.push_back(s);

	Inactive = false;
}

void Powerup::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::update(elapsedTime, input);

	if (Inactive == true)
	{
		Cooldown--;
		if (Cooldown <= 1)
		{
			Inactive = false;
			mMainNode->attachObject(mEntity);
		}

	}
}

void Powerup::SetInactive()
{
	Cooldown = 100;
	Inactive = true;
	mMainNode->detachAllObjects();
}

Powerup::~Powerup()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}