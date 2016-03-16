/**
* @class World_1
* @author Explosive Shark Studios
* @date 15/03/2016
* @brief
*
* @section Description
* This class contains the lists of world objects spawned in World 1.
* The objects in it are listed for their name, mesh, location and scale.
*/

#include "World_1.h"


World_1::World_1(Ogre::SceneManager *mSceneMgr, std::list<Object *> &objectList)
{
	/**
	*The objects in it are listed for their name, mesh, location and scale.
	*creates segments of the world and the finish line
	*/
	std::list<Ogre::Sphere *> sphereList;
	Ogre::Sphere *a = new Ogre::Sphere(Ogre::Vector3(0, 0, 100), 50);
	sphereList.push_back(a);
	Chunk1 = new WorldChunk("World_1", mSceneMgr, "World_1_part1", Ogre::Vector3(0, -6, 150), Ogre::Vector3(3, 3, 3), sphereList);	//Spawns a cluster of rocks to form the first part of world 1
	//Chunk2 = new WorldChunk("World_2", mSceneMgr, "World_1_part2", Ogre::Vector3(0, -6, 150), Ogre::Vector3(3, 3, 3));	//Spawns a cluster of rocks to form the first part of world 2
	//Chunk3 = new WorldChunk("World_3", mSceneMgr, "World_1_part3", Ogre::Vector3(0, -6, 150), Ogre::Vector3(3, 3, 3));	//Spawns a cluster of rocks to form the first part of world 3
	//Chunk4 = new WorldChunk("World_4", mSceneMgr, "World_1_part4", Ogre::Vector3(0, -6, 150), Ogre::Vector3(3, 3, 3));	//Spawns a cluster of rocks to form the first part of world 4
	//Chunk5 = new WorldChunk("World_5", mSceneMgr, "World_1_part5", Ogre::Vector3(0, -6, 150), Ogre::Vector3(3, 3, 3));	//Spawns a cluster of rocks to form the first part of world 5
	
	
	objectList.push_back(Chunk1);

	/*
	objectList.push_back(Chunk2);
	objectList.push_back(Chunk3);
	objectList.push_back(Chunk4);
	objectList.push_back(Chunk5);
	*/
}
