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
#include "Object_WorldObject.h"

Object_WorldObject::Object_WorldObject(Ogre::String name, Ogre::SceneManager *sceneMgr, Ogre::String MeshName, Ogre::Vector3 worldLocation, Ogre::Vector3 objectScale)
{
	mName = name;
	mMeshName = MeshName;
	mSceneMgr = sceneMgr;

	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);	//Attaches the object name to the Node

	mMainNode->setPosition(worldLocation);	//Sets the world location of the Node
	mMainNode->setScale(objectScale);		//Sets the scale of the Node

	mEntity = mSceneMgr->createEntity(mName, mMeshName + ".mesh");  //Creates the model using the given information
	mMainNode->attachObject(mEntity);								//Attaches the model to the Node
}