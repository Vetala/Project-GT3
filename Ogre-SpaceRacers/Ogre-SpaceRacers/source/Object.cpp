#include "Object.h"

Object::Object(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName)
{
	mName = name;
	mMeshName = meshName;
	mSceneMgr = sceneMgr;

	physicsMat = new PhysicsMaterial();

	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mEntity = mSceneMgr->createEntity(mName, mMeshName + ".mesh");
}

void Object::Update(Ogre::Real elapsedTime, OIS::Keyboard *input)
{

}

void Object::SetVisible(bool visible)
{
	mMainNode->setVisible(visible);
}

Object::~Object()
{

}