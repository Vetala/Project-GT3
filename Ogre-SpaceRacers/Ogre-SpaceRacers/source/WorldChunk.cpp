/**
* @class Object_WorldObject
* @author Explosive Shark Studios
* @date 15/03/2016
* @brief
*
* @section Description
* This class contains the input function to spawn world objects.
* 
*/
#include "WorldChunk.h"

WorldChunk::WorldChunk(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String meshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale, std::list<Ogre::Sphere *> sphereList) : Object(name, sceneMgr, meshName)
{
	mMainNode->setPosition(worldLocation);	//Sets the world location of the Node
	mMainNode->setScale(objectScale);		//Sets the scale of the Node

	mMainNode->attachObject(mEntity);
	
	collisionSphereList = sphereList;
}

void WorldChunk::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
	Object::update(elapsedTime, input);
}

WorldChunk::~WorldChunk()
{
	mMainNode->detachAllObjects();
	delete mEntity;
	mMainNode->removeAndDestroyAllChildren();
	mSceneMgr->destroySceneNode(mName);
}