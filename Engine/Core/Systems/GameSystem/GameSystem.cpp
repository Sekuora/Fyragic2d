#include "GameSystem.h"

#include "Log.h"

#include "ECS.h"

#include <iostream>
#include <cassert>

#include <SDL3/SDL.h>
#include <SDL3/SDL_time.h>
#include <SDL3_image/SDL_image.h>

#include <glm/glm.hpp>


using std::cout;
using std::endl;

Game::Game()
{
	isRunning = false;

	Log::Message("Game Constructor Called");

	window = nullptr;
	renderer = nullptr;

	windowWidth = 600;
	windowHeight = 600;

	previousFrameMilliseconds = 0;
	deltaTime = 0;
}

Game::~Game()
{
	Log::Message("Game Destructor Called");
}

void Game::Start()
{

	// Init SDL Video

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		Log::Error("There was an error loading video components: ");
		assert(SDL_WasInit(SDL_INIT_VIDEO));
		return;
	}


	// Create Window and Renderer

	if (!SDL_CreateWindowAndRenderer("Fyragic Engine Game", windowWidth, windowHeight, SDL_WINDOW_BORDERLESS, &window, &renderer))
	{
		Log::Error("There was an error creating a window and renderer: ");
		assert(window);

	}

	// True Fulscreen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	Log::Message("Window Set to Fullscreen");


	isRunning = true;
}

void Game::Run()
{

	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::End()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::ProcessInput()
{
	// Handle Window Events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:

			isRunning = false;
			break;

		case SDL_EVENT_KEY_DOWN:
			if (event.key.key == SDLK_ESCAPE)
			{
				isRunning = false;
			}

			break;
		}
	}
}

void Game::Setup()
{
	
}

void Game::Update()
{
	//while ((SDL_GetTicks() <= previousFrameMilliseconds + FYR_millisecondsPerFrame));
	Uint64 frameTimeToWait = FYR_millisecondsPerFrame - (SDL_GetTicks() - previousFrameMilliseconds);

	if (frameTimeToWait > 0 && frameTimeToWait <= FYR_millisecondsPerFrame)
	{
		SDL_Delay(frameTimeToWait);
	}

	deltaTime = (SDL_GetTicks() - previousFrameMilliseconds) / FYR_milliseconds;
	 
	// Implement constant framerate
	previousFrameMilliseconds = SDL_GetTicks();

}

void Game::Render()
{
	// Screen Background
	SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
	SDL_RenderClear(renderer);

	const char* imagePath = "./Resources/images/tank-tiger-right.png";

	SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);

	//// Rectangle where texture will be rendered
	//SDL_FRect* destRect = new SDL_FRect{ playerPosition.x, playerPosition.y, 32, 32 };

	//// Render Texture
	//if (!SDL_RenderTexture(renderer, texture, NULL, destRect))
	//{
	//	cout << SDL_GetError() << endl;
	//}

	//SDL_DestroyTexture(texture);

	// Pass GameObjects to renderer

	SDL_RenderPresent(renderer);
}
