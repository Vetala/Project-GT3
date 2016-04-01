#pragma once
#include <OIS/OISKeyboard.h>

struct Controls
{
	OIS::KeyCode forwards;
	OIS::KeyCode backwards;
	OIS::KeyCode left;
	OIS::KeyCode right;
	OIS::KeyCode boost;
	OIS::KeyCode shoot;
	Controls()
	{
		forwards = OIS::KC_0;
		backwards = OIS::KC_0;
		left = OIS::KC_0;
		right = OIS::KC_0;
		boost = OIS::KC_0;
		shoot = OIS::KC_0;
	}
};
