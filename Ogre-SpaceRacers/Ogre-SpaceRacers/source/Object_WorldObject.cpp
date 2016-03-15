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

	/**
	*Binds the object name to the mesh
	*/
	mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);

	/**
	*Sets the position and scale of the object
	*/
	mMainNode->setPosition(worldLocation);
	mMainNode->setScale(objectScale);


	/**
	*Assigns the Model.
	*/
	mEntity = mSceneMgr->createEntity(mName, mMeshName + ".mesh");
	mMainNode->attachObject(mEntity);
}