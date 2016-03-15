
#pragma once
#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

// No MFC
#define WIN32_LEAN_AND_MEAN

#include "XBOXController.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

// XBOX Controller Class Definition
class InputManager
{
private:
	XBOXController* _controllers[4];
	
public:
	InputManager();

	std::vector<float> GetLeftStick(int playerNumber = -1);
	std::vector<float> GetRightStick(int playerNumber = -1);
	std::vector<float> GetTriggers(int playerNumber = -1);
	bool GetButton(int buttonId, int playerNumber = -1);
	bool IsConnected(int playerNumber);

};

#endif