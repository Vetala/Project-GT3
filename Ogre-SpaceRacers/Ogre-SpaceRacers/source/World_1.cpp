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
#include "Object_WorldObject.h"


World_1::World_1(Ogre::SceneManager *mSceneMgr)
{
	/**
	*The objects in it are listed for their name, mesh, location and scale.
	*creates segments of the world and the finish line
	*/
	
	World1 = new Object_WorldObject("World_1", mSceneMgr, "World_1_part1", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));	//Spawns a cluster of rocks to form the first part of world 1
	World2 = new Object_WorldObject("World_2", mSceneMgr, "World_1_part2", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));	//Spawns a cluster of rocks to form the first part of world 2
	World3 = new Object_WorldObject("World_3", mSceneMgr, "World_1_part3", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));	//Spawns a cluster of rocks to form the first part of world 3
	World4 = new Object_WorldObject("World_4", mSceneMgr, "World_1_part4", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));	//Spawns a cluster of rocks to form the first part of world 4
	World5 = new Object_WorldObject("World_5", mSceneMgr, "World_1_part5", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));	//Spawns a cluster of rocks to form the first part of world 5
	Finish = new Object_WorldObject("Finish", mSceneMgr, "Start_Line", (Ogre::Vector3(200, 10, 700)), (Ogre::Vector3(3, 5, 8)));	//Spawns the Finish at the end of the track
}
