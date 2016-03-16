#include "Finish.h"

Finish::Finish(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String MeshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale) : Object(name, sceneMgr)
{
	mMeshName = MeshName;

	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);

	//Sets the position and scale of the object
	mMainNode->setPosition(worldLocation);
	mMainNode->setScale(objectScale);

	//Assigns the Model
	mEntity = mSceneMgr->createEntity(mName, mMeshName + ".mesh");
	mMainNode->attachObject(mEntity);

	trigger = true;
	collisionSphere = new Ogre::Sphere(mMainNode->getPosition(), mEntity->getBoundingRadius());
}

void Finish::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{

}

Finish::~Finish()
{

}