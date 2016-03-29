/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "ShipCharacter.h"
#include "World_1.h"
#include "Finish.h"

//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

private:
	Ogre::String cameraName;
	int shipHealth;
	Ogre::Real rotate;
	Ogre::Real move;
	Ogre::Vector3 startPosition;
	ShipCharacter *ship;
	ShipCharacter *ship2;
	World_1 *world1;
	Finish *finish;
	
	bool isCollision(Ogre::Sphere s, Ogre::Sphere s2);
	void checkCollision();
	void doUpdate(const Ogre::FrameEvent& fe);
	void doGUI();
	std::list<Object *> objectList;
	std::list<ShipCharacter *> shipList;
};
	
//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
