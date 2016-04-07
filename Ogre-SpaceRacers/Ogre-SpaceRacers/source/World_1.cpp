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
	Start = new WorldObject("Start", mSceneMgr, "Start_Line", Ogre::Vector3(0, 13, 0), Ogre::Quaternion(1.0f, 0.0f, 1.0f, 0.0f), Ogre::Vector3(5, 5, 7), sphereList);


	//left side start
	Rock1 = new WorldObject("Rock1", mSceneMgr, "Rock3", Ogre::Vector3(80, 2, 0), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock2 = new WorldObject("Rock2", mSceneMgr, "Rock2", Ogre::Vector3(50, 2, 30), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock3 = new WorldObject("Rock3", mSceneMgr, "Rock5", Ogre::Vector3(60, 2, 60), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock4 = new WorldObject("Rock4", mSceneMgr, "Rock3", Ogre::Vector3(60, 2, 100), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock5 = new WorldObject("Rock5", mSceneMgr, "Rock2", Ogre::Vector3(60, 2, 130), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock6 = new WorldObject("Rock6", mSceneMgr, "Rock2", Ogre::Vector3(60, 2, 150), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock31 = new WorldObject("Rock31", mSceneMgr, "Rock2", Ogre::Vector3(70, 2, 180), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock32 = new WorldObject("Rock32", mSceneMgr, "Rock2", Ogre::Vector3(80, 2, 210), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock33 = new WorldObject("Rock33", mSceneMgr, "Rock5", Ogre::Vector3(90, 2, 240), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock34 = new WorldObject("Rock34", mSceneMgr, "Rock5", Ogre::Vector3(110, 2, 270), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock35 = new WorldObject("Rock35", mSceneMgr, "Rock2", Ogre::Vector3(120, 2, 300), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock36 = new WorldObject("Rock36", mSceneMgr, "Rock2", Ogre::Vector3(140, 2, 310), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);	//Edge for now on Left

	Rock43 = new WorldObject("Rock43", mSceneMgr, "Rock2", Ogre::Vector3(110, 2, 280), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock44 = new WorldObject("Rock44", mSceneMgr, "Rock2", Ogre::Vector3(130, 2, 270), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(10, 10, 10), sphereList);
	Rock45 = new WorldObject("Rock45", mSceneMgr, "Rock4", Ogre::Vector3(160, 2, 250), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock46 = new WorldObject("Rock46", mSceneMgr, "Rock5", Ogre::Vector3(190, 2, 230), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock47 = new WorldObject("Rock47", mSceneMgr, "Rock2", Ogre::Vector3(220, 2, 210), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock48 = new WorldObject("Rock48", mSceneMgr, "Rock5", Ogre::Vector3(250, 2, 190), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	//right side start
	Rock7 = new WorldObject("Rock7", mSceneMgr, "Rock3", Ogre::Vector3(-70, 2, 0), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(10, 10, 10), sphereList);
	Rock8 = new WorldObject("Rock8", mSceneMgr, "Rock2", Ogre::Vector3(-70, 2, 30), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock9 = new WorldObject("Rock9", mSceneMgr, "Rock5", Ogre::Vector3(-80, 2, 60), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock10 = new WorldObject("Rock10", mSceneMgr, "Rock3", Ogre::Vector3(-80, 2, 100), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock11 = new WorldObject("Rock11", mSceneMgr, "Rock2", Ogre::Vector3(-70, 2, 130), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock12 = new WorldObject("Rock12", mSceneMgr, "Rock2", Ogre::Vector3(-50, 2, 150), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock13 = new WorldObject("Rock13", mSceneMgr, "Rock2", Ogre::Vector3(-70, 2, 170), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(10, 10, 10), sphereList);
	Rock14 = new WorldObject("Rock14", mSceneMgr, "Rock2", Ogre::Vector3(-70, 2, 190), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock15 = new WorldObject("Rock15", mSceneMgr, "Rock3", Ogre::Vector3(-50, 2, 220), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock16 = new WorldObject("Rock16", mSceneMgr, "Rock5", Ogre::Vector3(-50, 2, 250), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock17 = new WorldObject("Rock17", mSceneMgr, "Rock2", Ogre::Vector3(-50, 2, 270), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock18 = new WorldObject("Rock18", mSceneMgr, "Rock3", Ogre::Vector3(-50, 2, 290), Ogre::Quaternion(1.0f, 0.0f, 1.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Struc1 = new WorldObject("Struc1", mSceneMgr, "Structure1", Ogre::Vector3(-30, 2, 400), Ogre::Quaternion(1.0f, 0.0f, 0.5f, 0.0f), Ogre::Vector3(5, 5, 5), sphereList);

	Rock19 = new WorldObject("Rock19", mSceneMgr, "Rock2", Ogre::Vector3(-80, 2, 340), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock20 = new WorldObject("Rock20", mSceneMgr, "Rock2", Ogre::Vector3(-100, 2, 370), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock21 = new WorldObject("Rock21", mSceneMgr, "Rock4", Ogre::Vector3(-100, 2, 400), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock22 = new WorldObject("Rock22", mSceneMgr, "Rock5", Ogre::Vector3(-80, 2, 425), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock23 = new WorldObject("Rock23", mSceneMgr, "Rock2", Ogre::Vector3(-80, 2, 460), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock24 = new WorldObject("Rock24", mSceneMgr, "Rock3", Ogre::Vector3(-60, 2, 480), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock25 = new WorldObject("Rock25", mSceneMgr, "Rock2", Ogre::Vector3(-50, 2, 480), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock26 = new WorldObject("Rock26", mSceneMgr, "Rock2", Ogre::Vector3(-20, 2, 480), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock27 = new WorldObject("Rock27", mSceneMgr, "Rock4", Ogre::Vector3(10, 2, 480), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock28 = new WorldObject("Rock28", mSceneMgr, "Rock5", Ogre::Vector3(30, 2, 450), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock29 = new WorldObject("Rock29", mSceneMgr, "Rock2", Ogre::Vector3(60, 2, 430), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock30 = new WorldObject("Rock30", mSceneMgr, "Rock5", Ogre::Vector3(90, 2, 430), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock37 = new WorldObject("Rock37", mSceneMgr, "Rock2", Ogre::Vector3(110, 2, 430), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock38 = new WorldObject("Rock38", mSceneMgr, "Rock2", Ogre::Vector3(130, 2, 420), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(10, 10, 10), sphereList);
	Rock39 = new WorldObject("Rock39", mSceneMgr, "Rock4", Ogre::Vector3(160, 2, 400), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock40 = new WorldObject("Rock40", mSceneMgr, "Rock5", Ogre::Vector3(190, 2, 380), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock41 = new WorldObject("Rock41", mSceneMgr, "Rock2", Ogre::Vector3(220, 2, 360), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock42 = new WorldObject("Rock42", mSceneMgr, "Rock5", Ogre::Vector3(250, 2, 340), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList); //Edge for now on Right


	objectList.push_back(Start);
	objectList.push_back(Rock1);
	objectList.push_back(Rock2);
	objectList.push_back(Rock3);
	objectList.push_back(Rock4);
	objectList.push_back(Rock5);
	objectList.push_back(Rock6);

	objectList.push_back(Rock7);
	objectList.push_back(Rock8);
	objectList.push_back(Rock9);
	objectList.push_back(Rock10);
	objectList.push_back(Rock11);
	objectList.push_back(Rock12);
	objectList.push_back(Rock13);
	objectList.push_back(Rock14);
	objectList.push_back(Rock15);
	objectList.push_back(Rock16);
	objectList.push_back(Rock17);
	objectList.push_back(Rock18);

	objectList.push_back(Struc1);

	objectList.push_back(Rock19);
	objectList.push_back(Rock20);
	objectList.push_back(Rock21);
	objectList.push_back(Rock22);
	objectList.push_back(Rock23);
	objectList.push_back(Rock24);
	objectList.push_back(Rock25);
	objectList.push_back(Rock26);
	objectList.push_back(Rock27);
	objectList.push_back(Rock28);
	objectList.push_back(Rock29);
	objectList.push_back(Rock30);

	objectList.push_back(Rock31);
	objectList.push_back(Rock32);
	objectList.push_back(Rock33);
	objectList.push_back(Rock34);
	objectList.push_back(Rock35);
	objectList.push_back(Rock36);
	objectList.push_back(Rock37);
	objectList.push_back(Rock38);
	objectList.push_back(Rock39);
	objectList.push_back(Rock40);
	objectList.push_back(Rock41);
	objectList.push_back(Rock42);
	objectList.push_back(Rock43);
	objectList.push_back(Rock44);
	objectList.push_back(Rock45);
	objectList.push_back(Rock46);
	objectList.push_back(Rock47);
	objectList.push_back(Rock48);
}
