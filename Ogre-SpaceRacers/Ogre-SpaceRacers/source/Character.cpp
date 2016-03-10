#include "Character.h"

Character::Character()
{

}

void Character::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{
	MovableObject::update(elapsedTime, input);
}
