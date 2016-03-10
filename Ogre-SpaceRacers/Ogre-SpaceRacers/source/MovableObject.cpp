#include "MovableObject.h"

MovableObject::MovableObject()
{

}

void MovableObject::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{
	Object::update(elapsedTime, input);
}

