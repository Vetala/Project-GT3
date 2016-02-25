/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
	//to declare variables here the variables have to be determined in the header file
	rotate = .13;
	move = 250;
	startPosition = (0, 0, 0);
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}



//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		
	//Creates the ship
	Ogre::Entity* shipEntity = mSceneMgr->createEntity("Ship2.mesh");
	shipEntity->setCastShadows(true);
	Ogre::SceneNode* shipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("shipNode");
	shipNode->setPosition(startPosition);
	shipNode->attachObject(shipEntity);
	shipNode->attachObject(mCamera);
	
	//creates a floor
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
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
    // Create your scene here :)
}
//---------------------------------------------------------------------------
void TutorialApplication::createCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(startPosition+(100,0,100)));
	//mCamera->lookAt(startPosition);
	mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);	
}

void TutorialApplication::createViewports()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
}
//this is where you put all of your input stuff (mouse clicks and keyboard presses)
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	static Ogre::Real toggleTimerLeft = 0.0;
	static Ogre::Real toggleTimerRight = 0.0;

	toggleTimerLeft -= fe.timeSinceLastFrame;
	toggleTimerRight -= fe.timeSinceLastFrame;

	if ((toggleTimerLeft < 0) && mMouse->getMouseState().buttonDown(OIS::MB_Left))
	{
		toggleTimerLeft = 0.5;
		Ogre::Light* light = mSceneMgr->getLight("SpotLight");
		light->setVisible(!light->isVisible());
	}
	if ((toggleTimerRight < 0) && mMouse->getMouseState().buttonDown(OIS::MB_Right))
	{
		toggleTimerRight = 0.5;
		Ogre::Light* light = mSceneMgr->getLight("BackgroundLight");
		light->setVisible(!light->isVisible());
	}
	return true;
}

//This is your Update, it runs every single frame
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	bool ret = BaseApplication::frameRenderingQueued(fe);
	moveShip(fe);
	return ret;
}

void TutorialApplication::moveShip(const Ogre::FrameEvent& fe)
{
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	if (mKeyboard->isKeyDown(OIS::KC_I))
		dirVec.z -= move;
	if (mKeyboard->isKeyDown(OIS::KC_K))
		dirVec.z += move;
	if (mKeyboard->isKeyDown(OIS::KC_U))
		dirVec.y += move;
	if (mKeyboard->isKeyDown(OIS::KC_O))
		dirVec.y -= move;
	if (mKeyboard->isKeyDown(OIS::KC_J))
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			mSceneMgr->getSceneNode("shipNode")->yaw(Ogre::Degree(5 * rotate));
		else
			dirVec.x -= move;
	}

	if (mKeyboard->isKeyDown(OIS::KC_L))
	{
		if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			mSceneMgr->getSceneNode("shipNode")->yaw(Ogre::Degree(-5 * rotate));
		else
			dirVec.x += move;
	}
	mSceneMgr->getSceneNode("shipNode")->translate(
		dirVec * fe.timeSinceLastFrame,
		Ogre::Node::TS_LOCAL);
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
