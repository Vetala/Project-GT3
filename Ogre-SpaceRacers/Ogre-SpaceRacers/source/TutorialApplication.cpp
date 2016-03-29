/**
* @class TutorialApplication
* @author Explosive Shark Studios
* @date 14/03/2016
* @brief
*
* @section Description
* This class is the base class of our game. It contains the initial draw calls aswell as the point where we initialise our update
*/

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
	shipHealth = 100;
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	//If there are performance issues try adjusting the shadowtype to: Ogre::SHADOWTYPE_STENCIL_MODULATIVE.  or Ogre::SHADOWTYPE_TEXTURE_MODULATIVE.

	//creates a floor
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		5000, 5000, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("rockwall.tga");  //WAAROM WERKT DEZE NIET WAT DE FUCK MATERIAL PLEASE, hebben we later toch niet nodig but fug it
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	
	//creates the blue light
	Ogre::Light* spotLight = mSceneMgr->createLight("SpotLight");
	spotLight->setDiffuseColour(0, 0, 1.0);
	spotLight->setSpecularColour(0, 0, 1.0);
	spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	spotLight->setDirection(-1, -1, 0);
	spotLight->setPosition(Ogre::Vector3(200, 200, 0));
	spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

	//creates the background light
	Ogre::Light* directionalLight = mSceneMgr->createLight("BackgroundLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(1, 1, 1));
	directionalLight->setSpecularColour(Ogre::ColourValue(1, 1, 1));
	directionalLight->setDirection(Ogre::Vector3(0, -1, 1));
    // Create your scene here
	ship = new ShipCharacter("Ship1", mSceneMgr, "Ship2", shipHealth, Ogre::Vector3(0, 0, 0), mCamera);
	ship2 = new ShipCharacter("Ship2", mSceneMgr, "Ship2", shipHealth, Ogre::Vector3(10, 0, 0), mCamera2);
	world1 = new World_1(mSceneMgr, objectList);
	finish = new Finish("Finish", mSceneMgr, "Start_Line", Ogre::Vector3(200, 10, 700), Ogre::Vector3(3, 5, 8));
	shipList.push_back(ship);
	shipList.push_back(ship2);
	objectList.push_back(finish);
}

void TutorialApplication::doUpdate(const Ogre::FrameEvent& fe)
{
	for each (ShipCharacter *ship in shipList)
	{
		ship->update(fe.timeSinceLastFrame, mKeyboard);
	}
}

//This is your Update, it runs every single frame
//All gui stuff must be done here otherwise ogre decides that it doesnt want to run anymore
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	bool ret = BaseApplication::frameRenderingQueued(fe);
	checkCollision();
	doUpdate(fe);
	doGUI();
	return ret;
}

void TutorialApplication::doGUI()
{
	ship->doGUI(respawnGUI, speedGUI, mTrayMgr);
	ship2->doGUI(respawnGUI, speedGUI, mTrayMgr);
}

void TutorialApplication::checkCollision()
{
	for each (ShipCharacter *ship in shipList)
	{
		for each (Ogre::Sphere *sphere in ship->collisionSphereList)
		{
			for each (ShipCharacter *ship2 in shipList)
			{
				if (ship != ship2)
				{
					for each (Ogre::Sphere *sphere2 in ship2->collisionSphereList)
					{
						bool col = isCollision(*sphere, *sphere2);
						if (col)
						{
							ship->handleCollision(*sphere, static_cast<MovableObject>(*ship2), *sphere2);
							ship2->handleCollision(*sphere2, static_cast<MovableObject>(*ship), *sphere);
						}
					}
				}
			}

			for each (Object *object in objectList)
			{
				for each (Ogre::Sphere *sphere2 in object->collisionSphereList)
				{
					bool col = isCollision(*sphere, *sphere2);
					if (col)
					{
						ship->handleCollision(*sphere, *object, *sphere2);
					}
				}
			}
		}
	}
}

bool TutorialApplication::isCollision(Ogre::Sphere s, Ogre::Sphere s2)
{
	return s.intersects(s2);
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
