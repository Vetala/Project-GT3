#include "Object_WorldObject.h"

Object_WorldObject::Object_WorldObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String MeshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale)
{
	mName = name;
	mMeshName = MeshName;
	mSceneMgr = sceneMgr;

	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);

	mMainNode->setPosition(worldLocation);
	mMainNode->setScale(objectScale);

	//Rock Model
	mEntity = mSceneMgr->createEntity(mName, mMeshName + ".mesh");
	mMainNode->attachObject(mEntity);
}