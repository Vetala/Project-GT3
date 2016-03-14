#include "World_1.h"
#include "Object_WorldObject.h"


World_1::World_1(Ogre::SceneManager *mSceneMgr)
{
	//creates rocks
	World1 = new Object_WorldObject("World_1", mSceneMgr, "World_1_part1", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));
	World2 = new Object_WorldObject("World_2", mSceneMgr, "World_1_part2", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));
	World3 = new Object_WorldObject("World_3", mSceneMgr, "World_1_part3", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));
	World4 = new Object_WorldObject("World_4", mSceneMgr, "World_1_part4", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));
	World5 = new Object_WorldObject("World_5", mSceneMgr, "World_1_part5", (Ogre::Vector3(0, -6, 150)), (Ogre::Vector3(3, 3, 3)));
}
