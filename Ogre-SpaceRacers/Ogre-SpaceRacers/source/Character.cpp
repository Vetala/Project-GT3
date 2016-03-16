#include "Character.h"

Character::Character(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::Camera *camera) : MovableObject(name, sceneMgr)
{

}

void Character::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{
	MovableObject::update(elapsedTime, input);
}

Character::~Character()
{

}
