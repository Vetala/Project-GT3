#include "Object.h"

Object::Object()
{

}

void Object::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{

}

void Object::setVisible(bool visible)
{
	mMainNode->setVisible(visible);
}
