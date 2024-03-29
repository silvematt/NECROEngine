#ifndef NECROENGINE_H
#define NECROENGINE_H

#include "SDL.h"

#include "Game.h"

#include "Input.h"
#include "AssetsManager.h"
#include "Renderer.h"

#include "Math.h"

class NECROEngine
{
private:
	// Status
	bool isRunning;

	// Game
	NECROGame game;

	// Subsystems
	NECROInput			input;
	NECRORenderer		renderer;
	NECROAssetsManager	assetsManager;
	
public:
	NECROGame&				GetGame();

	NECROInput&				GetInput();
	NECRORenderer&			GetRenderer();
	NECROAssetsManager&		GetAssetsManager();


	int						Init();
	void					Update();
	void					Stop();
	int						Shutdown();
};


// Global access for the Engine 
extern NECROEngine engine;

// Inline functions
inline NECROGame& NECROEngine::GetGame()
{
	return game;
}

inline NECROInput& NECROEngine::GetInput()
{
	return input;
}

inline NECRORenderer & NECROEngine::GetRenderer() 
{
	return renderer;
}

inline NECROAssetsManager& NECROEngine::GetAssetsManager()
{
	return assetsManager;
}

#endif
