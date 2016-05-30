#pragma once
#include "BaseApplication.h"
#include <stdio.h>
#include <irrKlang.h>

#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

class SoundManager
{
public:
	ISoundEngine* soundEngine;

	SoundManager() 
	{
		soundEngine = createIrrKlangDevice();
	}

	void Play2D(const char* soundFileName)
	{
		soundEngine->play2D(soundFileName);
	}
	void Play2D(const char* soundFileName, bool loop)
	{
		soundEngine->play2D(soundFileName, loop);
	}

	void Pause2D(bool pause)
	{
		soundEngine->setAllSoundsPaused(pause);
	}

	~SoundManager()
	{
		soundEngine->drop();
	}

protected:

private:
};