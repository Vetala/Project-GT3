#include "MovableObject.h"

MovableObject::MovableObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName) : Object(name, sceneMgr, meshName)
{
	rigidbody = new RigidBody();
}

void MovableObject::Update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{
	Object::update(elapsedTime, input);
	for each(SphereCollider *sCol in sphereColliders)
	{
		sCol->setPositionToParentPosition(mMainNode->getPosition());
	}
}

void MovableObject::HandleCollision(Ogre::Sphere mSphere, MovableObject col, Ogre::Sphere sphere)
{
	Ogre::Vector3 pos = mSphere.getCenter();
	Ogre::Vector3 colPos = sphere.getCenter();
	// get the mtd
	Ogre::Vector3 delta = pos - colPos;
	float d = delta.length();
	// minimum translation distance to push balls apart after intersecting
	Ogre::Vector3 mtd = delta * ((mSphere.getRadius() + sphere.getRadius() - d) / d);

	// resolve intersection --
	// inverse mass quantities
	float im1 = rigidbody->inverseMass;
	float im2 = col.rigidbody->inverseMass;

	// push-pull them apart based off their mass
	pos = pos + (mtd * (im1 / (im1 + im2)));
	colPos = colPos - (mtd * (im2 / (im1 + im2)));
	mMainNode->setPosition(mMainNode->getPosition() + (mtd * (im1 / (im1 + im2))));
	col.mMainNode->setPosition(col.mMainNode->getPosition() - (mtd * (im2 / (im1 + im2))));

	// impact speed
	Ogre::Vector3 v = rigidbody->velocity - col.rigidbody->velocity;
	float vn = v.dotProduct(mtd.normalisedCopy());

	// sphere intersecting but moving away from each other already
	if (vn > 0.0f) return;

	// collision impulse
	float i = (-(1.0f) * vn) / (im1 + im2);
	Ogre::Vector3 impulse = mtd * i;

	float bounce = (physicsMat->bounciness + col.physicsMat->bounciness) / 2;

	// change in momentum
	rigidbody->velocity = (rigidbody->velocity + (impulse * (im1)) * bounce);
	col.rigidbody->velocity = (col.rigidbody->velocity - (impulse * (im2)) * bounce);
}

void MovableObject::HandleCollision(Ogre::Sphere mSphere, Object col, Ogre::Sphere sphere)
{
	Ogre::Vector3 pos = mSphere.getCenter();
	Ogre::Vector3 colPos = sphere.getCenter();
	// get the mtd
	Ogre::Vector3 delta = pos - colPos;
	float d = delta.length();
	// minimum translation distance to push balls apart after intersecting
	Ogre::Vector3 mtd = delta * ((mSphere.getRadius() + sphere.getRadius() - d) / d);

	float im1 = rigidbody->inverseMass;

	// push-pull them apart based off their mass
	pos = pos + mtd;

	mMainNode->setPosition(mMainNode->getPosition() + mtd);

	// impact speed
	Ogre::Vector3 v = rigidbody->velocity;
	float vn = v.dotProduct(mtd.normalisedCopy());

	// sphere intersecting but moving away from each other already
	if (vn > 0.0f) return;

	// collision impulse
	float i = (-1.0f * vn) / 1;
	Ogre::Vector3 impulse = mtd * i;

	float bounce = (physicsMat->bounciness + col.physicsMat->bounciness) / 2;

	// change in momentum
	rigidbody->velocity = (rigidbody->velocity + (impulse * (im1)) * bounce);
}

MovableObject::~MovableObject()
{

}
