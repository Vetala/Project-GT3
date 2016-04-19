#include "Bullet.h"
#include "ShipCharacter.h"


Bullet::Bullet(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName) : MovableObject(name, sceneMgr, meshName)
{
	mSceneMgr = sceneMgr;
	s = new SphereCollider(false, Ogre::Sphere(Ogre::Vector3(0, 0, 0), mEntity->getBoundingRadius() * mMainNode->getScale().z));
	sphereColliders.push_back(s);
	SetInactive();
}


Bullet::~Bullet()
{
}

void Bullet::SetActive(Ogre::SceneNode *mShipNode)
{
	mMainNode->setPosition(mShipNode->getPosition());
	mMainNode->setOrientation(mShipNode->getOrientation());
	mMainNode->attachObject(mEntity);
	mMainNode->translate((mMainNode->getOrientation() * Ogre::Vector3(0, 0, 5)));
	mEntity->setCastShadows(false);
	s->setPositionToParentPosition(mMainNode->getPosition());
	active = true;
	activeTimer = 20;
}

void Bullet::SetInactive()
{
	active = false;
	mMainNode->detachAllObjects();
	mMainNode->setPosition(Ogre::Vector3(-60000, 0, 0));
	s->setPositionToParentPosition(mMainNode->getPosition());
}

void Bullet::Update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	if (active)
	{
		rigidbody->velocity = mMainNode->getOrientation() * Ogre::Vector3(0, 0, 600 * elapsedTime);
		mMainNode->translate(rigidbody->velocity);
		s->setPositionToParentPosition(mMainNode->getPosition());
		activeTimer--;
		if(activeTimer < 1)
		{
			SetInactive();
		}
	}
}