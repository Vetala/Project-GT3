#include "InputManager.h"
#include <vector>

///<summary>
/// Example implementation of controller input.
/// Needs redesign in case additional controllers are added.
///</summary>

InputManager::InputManager()
{
	_controllers[0] = new XBOXController(1);
	_controllers[1] = new XBOXController(2);
	_controllers[2] = new XBOXController(3);
	_controllers[3] = new XBOXController(4);
}


std::vector<float> InputManager::GetLeftStick(int playerNumber)
{
	std::vector<float> lvalue(2, 0);

	if(playerNumber != -1) playerNumber = abs(playerNumber - 1) % 4;

	for (int i = ((playerNumber == -1) ? 0 : playerNumber); i < ((playerNumber == -1) ? 4 : playerNumber+1); i++)
	{

		if (!((_controllers[i]->GetState().Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controllers[i]->GetState().Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(_controllers[i]->GetState().Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				_controllers[i]->GetState().Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)))
		{
			lvalue.at(1) = _controllers[i]->GetState().Gamepad.sThumbLY;
			lvalue.at(0) = _controllers[i]->GetState().Gamepad.sThumbLX;
			_controllers[i]->Vibrate(65535, 0);
		}
	}

	return lvalue;
}

std::vector<float> InputManager::GetRightStick(int playerNumber)
{
	std::vector<float> rvalue(2, 0);

	if (playerNumber != -1) playerNumber = abs(playerNumber - 1) % 4;

	for (int i = ((playerNumber == -1) ? 0 : playerNumber); i < ((playerNumber == -1) ? 4 : playerNumber + 1); i++)
	{

		if (!((_controllers[i]->GetState().Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			_controllers[i]->GetState().Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(_controllers[i]->GetState().Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				_controllers[i]->GetState().Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)))
		{
			rvalue.at(1) = _controllers[i]->GetState().Gamepad.sThumbRX;
			rvalue.at(0) = _controllers[i]->GetState().Gamepad.sThumbRY;
			_controllers[i]->Vibrate(65535, 0);
		}
	}

	return rvalue;
}

std::vector<float> InputManager::GetTriggers(int playerNumber)
{
	std::vector<float> tvalue(2, 0);

	if (playerNumber != -1) playerNumber = abs(playerNumber - 1) % 4;

	for (int i = ((playerNumber == -1) ? 0 : playerNumber); i < ((playerNumber == -1) ? 4 : playerNumber + 1); i++)
	{

		tvalue[0] = (float)_controllers[i]->GetState().Gamepad.bLeftTrigger / 255;
		tvalue[1] = (float)_controllers[i]->GetState().Gamepad.bRightTrigger / 255;
		if (tvalue[0] != 0.0f || tvalue[1] != 0.0f)
		{
			_controllers[i]->Vibrate(65535, 0);
		}
	}
	return tvalue;
}

bool InputManager::GetButton(int buttonId, int playerNumber /* = -1*/)
{

	if (playerNumber != -1) playerNumber = abs(playerNumber - 1) % 4;

	for (int i = ((playerNumber == -1) ? 0 : playerNumber); i < ((playerNumber == -1) ? 4 : playerNumber + 1); i++)
	{
		if (_controllers[i]->IsConnected() && _controllers[i]->GetState().Gamepad.wButtons & buttonId)
		{
			_controllers[i]->Vibrate(65535, 0);
			return true;
		}

	}
	return false;
}

bool InputManager::IsConnected(int playerNumber)
{
	return _controllers[playerNumber]->IsConnected();
}