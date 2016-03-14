#include "World_1.h"
#include "Object_WorldObject.h"


World_1::World_1(Ogre::SceneManager *mSceneMgr)
{
	//creates rocks
	World1 = new Object_WorldObject("World_1", mSceneMgr, "World_1_part1", (Ogre::Vector3(0, 0, 0)), (Ogre::Vector3(20, 20, 20)));
	World2 = new Object_WorldObject("World_2", mSceneMgr, "World_1_part2", (Ogre::Vector3(750, 0, -100)), (Ogre::Vector3(30, 20, 40)));
}
