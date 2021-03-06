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
#include "Powerup.h"
#include "Physics.h"
#include "Controls.h"
#include "InputManager.h"
#include "SoundManager.h"
//---------------------------------------------------------------------------



class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);
	Controls *player1;
	Controls *player2;
	InputManager *inputManager;

protected:
    virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	Ogre::StringConverter converter;
	SoundManager *soundManager;

private:
	Ogre::String cameraName;
	Ogre::String player1Name;
	Ogre::String player2Name;
	Ogre::String player1Ship;
	Ogre::String player2Ship;
	int shipHealth;
	int shipBoost;
	Ogre::Real rotate;
	Ogre::Real move;
	Ogre::Vector3 startPosition;
	ShipCharacter *ship;
	ShipCharacter *ship2;
	World_1 *world1;
	Finish *finish;
	Powerup *powerup;
	
	bool canPause;
	int canPauseTimer;
	bool gameOver;
	int gameOverCount;
	bool isCollision(Ogre::Sphere s, Ogre::Sphere s2);
	void CheckCollision();
	void DoUpdate(const Ogre::FrameEvent& fe);
	void DoGUI(const Ogre::FrameEvent& fe);
	std::list<Object *> objectList;
	std::list<ShipCharacter *> shipList;
	std::list<Powerup *> powerUpList;
	std::list<Bullet *> bulletList;
	
};
	
//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
