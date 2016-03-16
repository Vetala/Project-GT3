#include "Object.h"

Object::Object(Ogre::String name, Ogre::SceneManager *sceneMgr)
{
	mName = name;
	mSceneMgr = sceneMgr;
	trigger = false;
}

void Object::update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{

}

void Object::setVisible(bool visible)
{
	mMainNode->setVisible(visible);
}

Object::~Object()
{

}