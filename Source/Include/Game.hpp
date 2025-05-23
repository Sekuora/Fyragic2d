#pragma once

class SDL_Window;
class SDL_Renderer;

class Game
{

public:
	Game();
	~Game();

	// Entry Point
	void Start();

	// Runtime game process
	void Run();

	// End
	void End();

	// Pre Process Setup
	void Setup();

	// Process Functions
	void ProcessInput();
	void Update();
	void Render();


	unsigned int windowWidth;
	unsigned int windowHeight;

private:
	/**
	* @brief SDL Window for Fyragic Engine Games
	**/
	SDL_Window* window;

	/**
	* @brief SDL Renderer for Window
	**/
	SDL_Renderer* renderer;

	/**
	* Check Is Running
	**/
	bool isRunning;

};
