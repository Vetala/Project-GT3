#include "MovableObject.h"

MovableObject::MovableObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName) : Object(name, sceneMgr, meshName)
{
	velocity = (0, 0, 0);
	acceleration = (0, 0, 0);
	force = (0, 0, 0);
	damping = 1;
}

void MovableObject::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{
	Object::update(elapsedTime, input);
	collisionSphere->setCenter(mMainNode->getPosition());
}

void MovableObject::handleCollision(MovableObject col)
{

}

void MovableObject::handleCollision(Object col)
{
	puts("Collision");
}

MovableObject::~MovableObject()
{

}
