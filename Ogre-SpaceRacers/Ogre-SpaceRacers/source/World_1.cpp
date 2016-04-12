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


World_1::World_1(Ogre::SceneManager *mSceneMgr, std::list<Object *> &objectList, std::list<Powerup *> &powerUpList)
{
	/**
	*The objects in it are listed for their name, mesh, location, rotation, scale and collision-type list.
	*This class therefore creates mesh objects in the world, including the start and powerups
	*/
	std::list<Ogre::Sphere *> sphereList;
	Start = new WorldObject("Start", mSceneMgr, "Start_Line", Ogre::Vector3(0, 13, 0), Ogre::Quaternion(1.0f, 0.0f, 1.0f, 0.0f), Ogre::Vector3(5, 5, 7), sphereList);

	Powerup1 = new Powerup("Powerup1", mSceneMgr, "PowerUp", Ogre::Vector3(210, 2, 280), Ogre::Quaternion(1.0f, 0.0f, 1.8f, 0.0f), Ogre::Vector3(3, 3, 3), sphereList);
	Powerup2 = new Powerup("Powerup2", mSceneMgr, "PowerUp", Ogre::Vector3(225, 2, 300), Ogre::Quaternion(1.0f, 0.0f, 1.8f, 0.0f), Ogre::Vector3(3, 3, 3), sphereList);


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
	Rock36 = new WorldObject("Rock36", mSceneMgr, "Rock2", Ogre::Vector3(140, 2, 310), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock43 = new WorldObject("Rock43", mSceneMgr, "Rock2", Ogre::Vector3(110, 2, 280), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock44 = new WorldObject("Rock44", mSceneMgr, "Rock2", Ogre::Vector3(130, 2, 270), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(10, 10, 10), sphereList);
	Rock45 = new WorldObject("Rock45", mSceneMgr, "Rock4", Ogre::Vector3(160, 2, 250), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock46 = new WorldObject("Rock46", mSceneMgr, "Rock5", Ogre::Vector3(190, 2, 230), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock47 = new WorldObject("Rock47", mSceneMgr, "Rock2", Ogre::Vector3(220, 2, 210), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock48 = new WorldObject("Rock48", mSceneMgr, "Rock5", Ogre::Vector3(250, 2, 190), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);	
	
	Rock49 = new WorldObject("Rock49", mSceneMgr, "Rock3", Ogre::Vector3(280, 2, 190), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock50 = new WorldObject("Rock50", mSceneMgr, "Rock2", Ogre::Vector3(300, 2, 210), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock51 = new WorldObject("Rock51", mSceneMgr, "Rock5", Ogre::Vector3(330, 2, 230), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock52 = new WorldObject("Rock52", mSceneMgr, "Rock3", Ogre::Vector3(360, 2, 250), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock53 = new WorldObject("Rock53", mSceneMgr, "Rock2", Ogre::Vector3(390, 2, 270), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock54 = new WorldObject("Rock54", mSceneMgr, "Rock2", Ogre::Vector3(410, 2, 290), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock55 = new WorldObject("Rock55", mSceneMgr, "Rock2", Ogre::Vector3(430, 2, 320), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock56 = new WorldObject("Rock56", mSceneMgr, "Rock2", Ogre::Vector3(450, 2, 350), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock57 = new WorldObject("Rock57", mSceneMgr, "Rock5", Ogre::Vector3(470, 2, 380), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock58 = new WorldObject("Rock58", mSceneMgr, "Rock5", Ogre::Vector3(490, 2, 410), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock59 = new WorldObject("Rock59", mSceneMgr, "Rock2", Ogre::Vector3(500, 2, 440), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock60 = new WorldObject("Rock60", mSceneMgr, "Rock2", Ogre::Vector3(500, 2, 470), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock61 = new WorldObject("Rock61", mSceneMgr, "Rock2", Ogre::Vector3(500, 2, 510), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock62 = new WorldObject("Rock62", mSceneMgr, "Rock2", Ogre::Vector3(480, 2, 530), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock63 = new WorldObject("Rock63", mSceneMgr, "Rock5", Ogre::Vector3(460, 2, 550), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock64 = new WorldObject("Rock64", mSceneMgr, "Rock5", Ogre::Vector3(430, 2, 570), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock65 = new WorldObject("Rock65", mSceneMgr, "Rock2", Ogre::Vector3(410, 2, 600), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock66 = new WorldObject("Rock66", mSceneMgr, "Rock2", Ogre::Vector3(390, 2, 620), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	
	Rock67 = new WorldObject("Rock67", mSceneMgr, "Rock2", Ogre::Vector3(360, 2, 650), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock68 = new WorldObject("Rock68", mSceneMgr, "Rock2", Ogre::Vector3(330, 2, 680), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock69 = new WorldObject("Rock69", mSceneMgr, "Rock5", Ogre::Vector3(310, 2, 700), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock70 = new WorldObject("Rock70", mSceneMgr, "Rock5", Ogre::Vector3(290, 2, 720), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock71 = new WorldObject("Rock71", mSceneMgr, "Rock2", Ogre::Vector3(260, 2, 740), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock72 = new WorldObject("Rock72", mSceneMgr, "Rock2", Ogre::Vector3(240, 2, 750), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);	//Edge for now on Left

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
	Rock42 = new WorldObject("Rock42", mSceneMgr, "Rock5", Ogre::Vector3(250, 2, 340), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock73 = new WorldObject("Rock73", mSceneMgr, "Rock2", Ogre::Vector3(270, 2, 370), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock74 = new WorldObject("Rock74", mSceneMgr, "Rock2", Ogre::Vector3(280, 2, 400), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(8, 8, 8), sphereList);
	Rock75 = new WorldObject("Rock75", mSceneMgr, "Rock4", Ogre::Vector3(300, 2, 420), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock76 = new WorldObject("Rock76", mSceneMgr, "Rock5", Ogre::Vector3(330, 2, 450), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock77 = new WorldObject("Rock77", mSceneMgr, "Rock2", Ogre::Vector3(300, 2, 470), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock78 = new WorldObject("Rock78", mSceneMgr, "Rock5", Ogre::Vector3(270, 2, 500), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);

	Rock79 = new WorldObject("Rock79", mSceneMgr, "Rock2", Ogre::Vector3(240, 2, 530), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock80 = new WorldObject("Rock80", mSceneMgr, "Rock2", Ogre::Vector3(210, 2, 550), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(10, 10, 10), sphereList);
	Rock81 = new WorldObject("Rock81", mSceneMgr, "Rock4", Ogre::Vector3(240, 2, 580), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock82 = new WorldObject("Rock82", mSceneMgr, "Rock5", Ogre::Vector3(190, 2, 600), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock83 = new WorldObject("Rock83", mSceneMgr, "Rock2", Ogre::Vector3(220, 2, 620), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);
	Rock84 = new WorldObject("Rock84", mSceneMgr, "Rock5", Ogre::Vector3(250, 2, 340), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);	//Edge for now on Right

	Rock85 = new WorldObject("Rock85", mSceneMgr, "Rock2", Ogre::Vector3(410, 2, 430), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(13, 13, 13), sphereList);
	Rock86 = new WorldObject("Rock86", mSceneMgr, "Rock2", Ogre::Vector3(420, 2, 450), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(10, 10, 10), sphereList);
	Rock87 = new WorldObject("Rock87", mSceneMgr, "Rock5", Ogre::Vector3(400, 2, 470), Ogre::Quaternion(1.0f, 0.0f, 0.0f, 0.0f), Ogre::Vector3(12, 12, 12), sphereList);






	//objectList.push_back(Start);
	powerUpList.push_back(Powerup1);
	powerUpList.push_back(Powerup2);

	Powerup1->mTag = "Powerup";
	Powerup2->mTag = "Powerup";


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

	objectList.push_back(Rock49);
	objectList.push_back(Rock50);
	objectList.push_back(Rock51);
	objectList.push_back(Rock52);
	objectList.push_back(Rock53);
	objectList.push_back(Rock54);
	objectList.push_back(Rock55);
	objectList.push_back(Rock56);
	objectList.push_back(Rock57);
	objectList.push_back(Rock58);
	objectList.push_back(Rock59);
	objectList.push_back(Rock60);
	objectList.push_back(Rock61);
	objectList.push_back(Rock62);
	objectList.push_back(Rock63);
	objectList.push_back(Rock64);
	objectList.push_back(Rock65);
	objectList.push_back(Rock66);
	objectList.push_back(Rock67);
	objectList.push_back(Rock68);
	objectList.push_back(Rock69);
	objectList.push_back(Rock70);
	objectList.push_back(Rock71);
	objectList.push_back(Rock72);
	objectList.push_back(Rock73);
	objectList.push_back(Rock74);
	objectList.push_back(Rock75);
	objectList.push_back(Rock76);
	objectList.push_back(Rock77);
	objectList.push_back(Rock78);
	objectList.push_back(Rock79);
	objectList.push_back(Rock80);
	objectList.push_back(Rock81);
	objectList.push_back(Rock82);
	objectList.push_back(Rock83);
	objectList.push_back(Rock84);
	objectList.push_back(Rock85);
	objectList.push_back(Rock86);
	objectList.push_back(Rock87);
}
