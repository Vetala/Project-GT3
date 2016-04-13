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
	soundManager = new SoundManager();
	soundManager->Play2D("../../Media/sounds/getout.ogg", true);

	shipHealth = 100;
	shipBoost = 100;
	//Setting controls for both players
	player1 = new Controls();
	player1->forwards = OIS::KeyCode(OIS::KC_W);
	player1->backwards = OIS::KeyCode(OIS::KC_S);
	player1->left = OIS::KeyCode(OIS::KC_A);
	player1->right = OIS::KeyCode(OIS::KC_D);
	player1->boost = OIS::KeyCode(OIS::KC_LSHIFT);
	player1->shoot = OIS::KeyCode(OIS::KC_E);

	player2 = new Controls();
	player2->forwards = OIS::KeyCode(OIS::KC_UP);
	player2->backwards = OIS::KeyCode(OIS::KC_DOWN);
	player2->left = OIS::KeyCode(OIS::KC_LEFT);
	player2->right = OIS::KeyCode(OIS::KC_RIGHT);
	player2->boost = OIS::KeyCode(OIS::KC_RSHIFT);
	player2->shoot = OIS::KeyCode(OIS::KC_PERIOD);

	player1Name = "Ship1";
	player2Name = "Ship2";
	player1Ship = "Ship";
	player2Ship = "Ship3";

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
	inputManager = new InputManager;

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
	if (inputManager->IsConnected(0))
	{
		ship = new ShipCharacter(player1Name, mSceneMgr, player1Ship, shipHealth, Ogre::Vector3(0, 0, 0), shipBoost, bulletList, 0, inputManager, mCamera);
	}
	else
	{
		ship = new ShipCharacter(player1Name, mSceneMgr, player1Ship, shipHealth, Ogre::Vector3(0, 0, 0), shipBoost, bulletList, player1, 0, mCamera);
	}
	if (inputManager->IsConnected(1))
	{
		ship2 = new ShipCharacter(player2Name, mSceneMgr, player2Ship, shipHealth, Ogre::Vector3(10, 0, 0), shipBoost, bulletList, 0, inputManager, mCamera2);
	}
	else
	{
		ship2 = new ShipCharacter(player2Name, mSceneMgr, player2Ship, shipHealth, Ogre::Vector3(10, 0, 0), shipBoost, bulletList, player2, 0, mCamera2);
	}
	world1 = new World_1(mSceneMgr, objectList, powerUpList);
	finish = new Finish("Finish", mSceneMgr, "Start_Line", Ogre::Vector3(200, 10, 700), Ogre::Vector3(3, 5, 8));
	shipList.push_back(ship);
	shipList.push_back(ship2);
	objectList.push_back(finish);
	for (int i = 0; i < 40; i++)
	{
		Bullet *bullet;
		Ogre::String bulletName;
		bulletName = "bullets" + converter.toString(bulletList.size());
		bullet = new Bullet(bulletName, mSceneMgr, "Bullet");
		bulletList.push_back(bullet);
	}
}

void TutorialApplication::DoUpdate(const Ogre::FrameEvent& fe)
{
	for each (ShipCharacter *ship in shipList)
	{
		ship->Update(fe.timeSinceLastFrame, mKeyboard);
	}
	for each (Bullet *bullet in bulletList)
	{
		bullet->Update(fe.timeSinceLastFrame, mKeyboard);
	}
	for each (Powerup *powerup in powerUpList)
	{
		powerup->Update(fe.timeSinceLastFrame, mKeyboard);
	}
}

//This is your Update, it runs every single frame
//All gui stuff must be done here otherwise ogre decides that it doesnt want to run anymore
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	bool ret = BaseApplication::frameRenderingQueued(fe);
	CheckCollision();
	DoUpdate(fe);
	DoGUI();
	return ret;
}

void TutorialApplication::DoGUI()
{
	ship->DoGui(respawnGUI, speedGUI, mTrayMgr);
	ship2->DoGui(respawnGUI2, speedGUI2, mTrayMgr);
}

void TutorialApplication::CheckCollision()
{
	for each (ShipCharacter *ship in shipList)
	{
		for each (SphereCollider *sCol in ship->sphereColliders)
		{
			for each (Bullet *b in bulletList)
			{
				if (b->active == true)
				{
					for each (SphereCollider *sCol2 in b->sphereColliders)
					{
						bool col = isCollision(sCol->sphere, sCol2->sphere);
						if (col)
						{
							ship->DoDamage(25);
							b->SetInactive();
						}
					}
				}
			}
			for each (ShipCharacter *ship2 in shipList)
			{
				if (ship != ship2)
				{
					for each (SphereCollider *sCol2 in ship2->sphereColliders)
					{
						bool col = isCollision(sCol->sphere, sCol2->sphere);
						if (col)
						{
							ship->HandleCollision(*sCol, static_cast<MovableObject>(*ship2), *sCol2);
							ship2->HandleCollision(*sCol2, static_cast<MovableObject>(*ship), *sCol);
						}
					}
				}
			}

			for each (Object *object in objectList)
			{
				for each (SphereCollider *sCol2 in object->sphereColliders)
				{
					bool col = isCollision(sCol->sphere, sCol2->sphere);
					if (col)
					{
						ship->HandleCollision(*sCol, *object, *sCol2);
					}
				}
			}
			for each (Powerup *powerUp in powerUpList)
			{
				if (powerUp->Inactive == false){
					for each (SphereCollider *sCol2 in powerUp->sphereColliders)
					{
						bool col = isCollision(sCol->sphere, sCol2->sphere);
						if (col)
						{
							ship->HandleCollision(*sCol, *powerUp, *sCol2);
							powerUp->SetInactive();
						}
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
