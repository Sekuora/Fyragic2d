#include "Game.hpp"

#include <iostream>
#include <cassert>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <glm/glm.hpp>


using std::cout;
using std::endl;

Game::Game()
{
	isRunning = false;

	cout << "Game Constructor Called \n";

	window = nullptr;
	renderer = nullptr;

	windowWidth = 600;
	windowHeight = 600;
}

Game::~Game()
{
	cout << "Game Destructor Called \n";
}

void Game::Start()
{

	// Init SDL Video

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		assert(SDL_WasInit(SDL_INIT_VIDEO));
		return;
	}

	// Set Window Parameters


	// Create Window and Renderer

	if (!SDL_CreateWindowAndRenderer("Fyragic Engine Game", windowWidth, windowHeight, SDL_WINDOW_BORDERLESS, &window, &renderer))
	{
		assert(window && SDL_GetError());
	}

	// True Fulscreen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	cout << "Window Set to Fullscreen\n";


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

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup()
{
	playerPosition = glm::vec2(10.0, 20.0);
	playerVelocity = glm::vec2(1.0, 0.0);
}

void Game::Update()
{
	playerPosition.x += playerVelocity.x;
	playerPosition.y += playerVelocity.y;
}

void Game::Render()
{
	// Screen Background
	SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
	SDL_RenderClear(renderer);

	const char* imagePath = "./Resources/images/tank-tiger-right.png";

	SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);

	// Rectangle where texture will be rendered
	SDL_FRect* destRect = new SDL_FRect{ playerPosition.x, playerPosition.y, 32, 32 };

	// Render Texture
	if (!SDL_RenderTexture(renderer, texture, NULL, destRect))
	{
		cout << SDL_GetError() << endl;
	}

	//SDL_DestroyTexture(texture);

	// Pass GameObjects to renderer

	SDL_RenderPresent(renderer);
}
