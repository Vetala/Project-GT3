#include "Object.h"

Object::Object(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName)
{
	mName = name;
	mMeshName = meshName;
	mSceneMgr = sceneMgr;
	trigger = false;

	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mEntity = mSceneMgr->createEntity(mName, mMeshName + ".mesh");
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